#!/usr/bin/env python3
# SPDX-License-Identifier: BSD-3-Clause

"""MCU model compilation script."""

__version__ = "1.1.0"

import os
import sys
import json
import shutil
import stat
import subprocess
import random
import gc
from pathlib import Path
from dataclasses import dataclass
from enum import Enum
from typing import Optional, List, Dict, Any
from multiprocessing import Process, Queue
from argparse import ArgumentParser, Namespace
import numpy as np

# MERA imports
import mera
from mera import Platform, Target, quantizer

# Reproducibility
RANDOM_SEED = 42
np.random.seed(RANDOM_SEED)
random.seed(RANDOM_SEED)

# Default ONNX symbolic dimensions (for freezing dynamic shapes to static)
SYMBOLIC_DIMS = {
    'batch': 1,
    'batch_size': 1,
    'width': 224,
    'height': 224,
    'num_channels': 3,
    'N': 1,
}

# Default OSPI threshold (MB) - models larger than this auto-enable OSPI for NPU
DEFAULT_OSPI_THRESHOLD_MB = 0.8

# Platform detection
import platform as plt

# Global Windows compiler detection flags (set at startup)
has_mingw_clang = False
has_mvs_clang = False


# =============================================================================
# Data Classes
# =============================================================================

class Status(Enum):
    """Model processing status."""
    IN_PROGRESS = 1
    ERROR_LOAD = 2
    ERROR_QUANTIZER = 3
    ERROR_PSNR = 4
    ERROR_DEPLOY = 5
    ERROR_RUNTIME = 6
    ERROR_VALIDATION = 7
    SUCCESS = 8


@dataclass
class CompileResult:
    """Result of compiling a single model."""
    model_name: str
    model_path: Path
    output_dir: Path
    status: Status = Status.IN_PROGRESS
    last_error: str = ''
    needs_external_memory: bool = False

# =============================================================================
# Windows Compiler Detection
# =============================================================================

def get_mingw_by_path():
    """Search for MinGW compiler (clang) in PATH on Windows."""
    mingw_paths = []
    probe_list = ["mingw"]
    for raw_path in os.environ.get("PATH", "").split(";"):
        clean_path = (os.path.normpath(raw_path)).strip()
        if clean_path.count(":") > 1 or (not os.path.exists(clean_path)):
            continue
        stop_loop = False
        for dir_files in os.listdir(clean_path):
            for search_string in probe_list:
                if search_string in dir_files:
                    full_exe_path = os.path.join(clean_path, "clang++.exe")
                    if os.path.exists(full_exe_path):
                        mingw_paths.append(clean_path)
                    stop_loop = True
            if stop_loop:
                break
    return mingw_paths


def find_mvs_vswhere():
    """Find Visual Studio's vswhere.exe on Windows."""
    progrs = os.environ.get("ProgramFiles(x86)", "C:\\Program Files (x86)")
    vswhere = Path(progrs) / "Microsoft Visual Studio" / "Installer" / "vswhere.exe"
    return str(vswhere) if vswhere.exists() else None


def get_mvs_clang_version(path):
    """Get clang version from Visual Studio installation."""
    try:
        output = subprocess.check_output([path, "--version"], encoding="utf-8")
        return output
    except subprocess.CalledProcessError:
        return ""


def is_mvs_clang_installed():
    """Check if Visual Studio is available and clang is installed."""
    vswhere = find_mvs_vswhere()
    if not vswhere:
        return 0
    try:
        outJson = subprocess.check_output([
            vswhere, "-latest", "-products", "*",
            "-requires", "Microsoft.VisualStudio.Component.VC.Llvm.Clang",
            "-format", "json"
        ], encoding="mbcs")
        outJsonObj = json.loads(outJson)
        if outJsonObj:
            m_vers = outJsonObj[0].get("installationVersion").split(".")[0]
            year = outJsonObj[0]["catalog"].get("productLineVersion").split(".")[0]
            ident = f"Visual Studio {m_vers} {year}"
            tmpP = outJsonObj[0].get("installationPath", "")
            clangPath = os.path.join(tmpP, "VC", "Tools", "Llvm", "x64", "bin", "clang.exe")
            if os.path.isfile(clangPath):
                os.environ["CMAKE_GENERATOR"] = ident
                os.environ["CMAKE_GENERATOR_TOOLSET"] = "ClangCl"
            else:
                return 0
        return len(outJsonObj) > 0
    except subprocess.CalledProcessError:
        return 0


def detect_windows_compilers():
    """Detect available Windows compilers at startup."""
    global has_mingw_clang, has_mvs_clang
    
    if plt.system() != "Windows":
        return
    
    mingw_paths = get_mingw_by_path()
    has_mingw_clang = len(mingw_paths) > 0
    
    if not has_mingw_clang:
        has_mvs_clang = is_mvs_clang_installed() > 0
    
    if has_mingw_clang:
        print(f"  Found MinGW Clang: {mingw_paths[0]}")
    elif has_mvs_clang:
        print("  Found MSVC Clang")
    else:
        print("  Warning: No compatible C++ compiler found for host evaluation")

# =============================================================================
# Warning message  
# =============================================================================

def print_warning(message):
    RED = "\033[91m"
    RESET = "\033[0m"
    print(f"{RED}{message}{RESET}")

# =============================================================================
# Model Detection
# =============================================================================

def get_model_format(model_path: Path) -> str:
    """Detect model format from file extension."""
    suffix = model_path.suffix.lower()
    if suffix == '.tflite':
        return 'tflite'
    elif suffix == '.onnx':
        return 'onnx'
    elif suffix == '.pte':
        return 'executorch'
    elif suffix == '.mera':
        return 'mera'
    else:
        raise ValueError(f"Unsupported model format: {suffix}")


def is_model_quantized(model_path: Path) -> bool:
    """
    Check if a model is already quantized (INT8).
    
    For TFLite: Use TensorFlow Lite interpreter to check tensor dtypes
    For ONNX: Check input/output tensor types using onnx library
    For PTE: Assume FP32 (INT8 .pte not supported by MERA)
    For MERA: Always quantized
    """
    model_format = get_model_format(model_path)
    
    if model_format == 'mera':
        return True

    if model_format == 'tflite':
        try:
            import tensorflow as tf
            interpreter = tf.lite.Interpreter(model_path=str(model_path))
            interpreter.allocate_tensors()
            
            # Check input/output dtypes first
            input_details = interpreter.get_input_details()
            for inp in input_details:
                dtype = inp['dtype']
                if dtype in [np.int8, np.uint8]:
                    return True
            
            output_details = interpreter.get_output_details()
            for out in output_details:
                dtype = out['dtype']
                if dtype in [np.int8, np.uint8]:
                    return True
            
            # Check ALL tensors for hybrid models (FP32 I/O but INT8 internals)
            # These are common: input is float for preprocessing, but weights are INT8
            tensor_details = interpreter.get_tensor_details()
            int8_count = 0
            total_count = len(tensor_details)
            for t in tensor_details:
                if t['dtype'] in [np.int8, np.uint8]:
                    int8_count += 1
            
            # If majority of tensors are INT8/UINT8, consider it quantized
            if int8_count > total_count * 0.5:
                print(f"  Detected hybrid quantized model: {int8_count}/{total_count} INT8 tensors")
                return True
            
            return False
        except Exception as e:
            print(f"  Warning: Could not check TFLite quantization: {e}")
            # Fallback to filename check
            if 'int8' in model_path.name.lower() or 'quant' in model_path.name.lower():
                print(f"  Fallback: Detected INT8 via filename: {model_path.name}")
                return True
            return False
    
    elif model_format == 'onnx':
        try:
            import onnx
            from onnx import TensorProto
            
            model = onnx.load(str(model_path))
            int8_types = [TensorProto.INT8, TensorProto.UINT8]
            
            for inp in model.graph.input:
                if inp.type.tensor_type.elem_type in int8_types:
                    return True
            
            for out in model.graph.output:
                if out.type.tensor_type.elem_type in int8_types:
                    return True
            
            for initializer in model.graph.initializer:
                if initializer.data_type in int8_types:
                    return True
            
            return False
        except ImportError:
            # onnx library not installed
            # We assume FP32 so that MERA will attempt to load and (re)quantize it.
            # Direct INT8 ONNX deployment often fails on NPU without going through Quantizer.
            print("  Note: onnx library not installed, assuming FP32 model")
            return False
        except Exception as e:
            print(f"  Warning: Could not check ONNX quantization: {e}")
            return False
    
    elif model_format == 'executorch':
        return False  # Assume FP32
    
    return False


# =============================================================================
# Model Loading
# =============================================================================

def load_model(deployer, model_path: Path, symbolic_dims: Dict[str, int] = None):
    """
    Load a model using MERA ModelLoader.
    
    Args:
        deployer: MERA Deployer instance
        model_path: Path to model file
        symbolic_dims: ONNX symbolic dimensions mapping (freezes to static)
        
    Returns:
        Loaded MERA model
    """
    model_format = get_model_format(model_path)
    loader = mera.ModelLoader(deployer)
    
    if model_format == 'tflite':
        return loader.from_tflite(str(model_path))
    elif model_format == 'onnx':
        dims = symbolic_dims or SYMBOLIC_DIMS
        return loader.from_onnx(str(model_path), shape_mapping=dims)
    elif model_format == 'executorch':
        return loader.from_executorch(str(model_path))
    elif model_format == 'mera':
        return loader.from_quantized_mera(str(model_path))
    else:
        raise ValueError(f"Unsupported model format: {model_format}")


# =============================================================================
# Calibration Data
# =============================================================================

def load_calibration_data(calib_path: Path, mera_model, num_samples: int) -> List[Dict]:
    """
    Load calibration data from file/directory or generate random data.
    
    Args:
        calib_path: Path to .npy file or directory of .npy files (None for random)
        mera_model: Loaded MERA model for input shape info
        num_samples: Number of calibration samples
        
    Returns:
        List of input data dictionaries
    """
    if calib_path is not None and calib_path.exists():
        if calib_path.is_file():
            data = np.load(str(calib_path), allow_pickle=True)
            
            if calib_path.suffix == '.npz':
                keys = list(data.keys())
                target_key = next((k for k in ['data', 'inputs', 'images'] if k in keys), keys[0])
                data_array = data[target_key]
                
                if len(data_array.shape) > 1:
                    input_name = list(mera_model.input_desc.all_inputs.keys())[0]
                    return [{input_name: data_array[i]} for i in range(min(len(data_array), num_samples))]
            
            if isinstance(data, np.ndarray) and data.dtype == object:
                return list(data)[:num_samples]
            else:
                input_name = list(mera_model.input_desc.all_inputs.keys())[0]
                return [{input_name: data}]
        else:
            npy_files = list(calib_path.glob("*.npy"))[:num_samples]
            input_name = list(mera_model.input_desc.all_inputs.keys())[0]
            return [{input_name: np.load(str(f))} for f in npy_files]
    
    # Generate random calibration data
    data = []
    for _ in range(num_samples):
        input_data = {}
        for name, inp in mera_model.input_desc.all_inputs.items():
            dtype = np.dtype(inp.input_type)
            if np.issubdtype(dtype, np.integer):
                input_data[name] = np.random.randint(0, 128, size=inp.input_shape, dtype=dtype)
            elif np.issubdtype(dtype, np.floating):
                input_data[name] = np.random.uniform(0.0, 1.0, size=inp.input_shape).astype(dtype)
            else:
                raise ValueError(f"Unsupported input dtype: {dtype}")
        data.append(input_data)
    return data


# =============================================================================
# Quantization
# =============================================================================

def quantize_model(
    model_path: Path,
    output_dir: Path,
    platform: Platform,
    calib_data: List[Dict],
    symbolic_dims: Dict[str, int] = None
) -> Optional[Path]:
    """
    Quantize a FP32 model to INT8 using MERA Quantizer.
    
    Args:
        model_path: Path to FP32 model
        output_dir: Directory to save quantized model
        platform: Target platform (MCU_CPU or MCU_ETHOS)
        calib_data: Calibration data for quantization
        symbolic_dims: ONNX symbolic dimensions
        
    Returns:
        Path to quantized .mera model, or None on error
    """
    output_dir.mkdir(parents=True, exist_ok=True)
    
    with mera.Deployer(str(output_dir), overwrite=True) as deployer:
        mera_model = load_model(deployer, model_path, symbolic_dims)
        
        qtzer = mera.Quantizer(
            deployer,
            mera_model,
            quantizer_config=quantizer.QuantizerConfigPresets.MCU,
            mera_platform=platform
        )
        
        qty = qtzer.calibrate(calib_data).quantize().evaluate_quality(calib_data[:1])
        Q = qty[0].out_summary()[0]
        
        print(f"  Quantization quality: PSNR={Q['psnr']:.2f}, Score={Q['score']:.2f}")
        
        if Q["psnr"] < 5:
            print(f"  WARNING: PSNR too low ({Q['psnr']:.2f}), quantization may have issues")
        
        qtz_path = output_dir / 'model.mera'
        qtzer.save_to(qtz_path)
        
        return qtz_path


# =============================================================================
# Reference Data Generation
# =============================================================================

def generate_reference_data(
    model_path: Path,
    output_dir: Path,
    calib_data: List[Dict] = None
) -> None:
    """
    Run model on MERA Interpreter to generate reference inputs/outputs.
    Saves inputs.npy and outputs.npy to output_dir.
    """
    output_dir.mkdir(parents=True, exist_ok=True)
    
    with mera.Deployer(str(output_dir), overwrite=True) as deployer:
        mera_model = load_model(deployer, model_path)
        
        # Get input data
        input_data = None
        
        if calib_data and len(calib_data) > 0:
            # Check if keys match
            calib_keys = set(calib_data[0].keys())
            model_keys = set(mera_model.input_desc.all_inputs.keys())
            
            if calib_keys == model_keys:
                input_data = calib_data[0]
            elif len(calib_keys) == 1 and len(model_keys) == 1:
                # Remap single input (common case: quantization changed tensor name)
                old_key = list(calib_keys)[0]
                new_key = list(model_keys)[0]
                print(f"  Note: Remapping input '{old_key}' -> '{new_key}' for reference generation")
                input_data = {new_key: calib_data[0][old_key]}
            else:
                print(f"  Warning: Input mismatch (Calib: {calib_keys} vs Model: {model_keys}). Generating new random data.")
                input_data = None
        
        if input_data is None:
            input_data = load_calibration_data(None, mera_model, 1)[0]
            
        print(f"  Generating reference data on Host...")
        deploy = deployer.deploy(mera_model, mera_platform=Platform.MCU_CPU, target=Target.MERAInterpreter)
        runner = deploy.get_runner()
        runner.set_input(input_data).run()
        output_data = runner.get_outputs()
        
        np.save(str(output_dir / 'inputs.npy'), input_data)
        
        if output_data:
            outputs = np.empty(len(output_data), object)
            outputs[:] = output_data
        else:
            outputs = []
        np.save(str(output_dir / 'outputs.npy'), outputs, allow_pickle=True)


# =============================================================================
# Deployment
# =============================================================================

def deploy_model(
    model_path: Path,
    output_dir: Path,
    platform: Platform,
    vela_config: Dict[str, Any],
    mcu_config: Dict[str, Any],
    symbolic_dims: Dict[str, int] = None,
    enable_ref_data: bool = False
) -> bool:
    """
    Deploy a model to MCU C-code using MERA.
    
    Args:
        model_path: Path to model (.tflite, .onnx, .pte, or .mera)
        output_dir: Output directory for C-code
        platform: Target platform
        vela_config: ARM Vela configuration (includes enable_ospi for NPU)
        mcu_config: MCU C-code generation configuration
        symbolic_dims: ONNX symbolic dimensions
        enable_ref_data: Generate reference I/O data
        
    Returns:
        True on success, False on error
    """
    # On Windows, previous cmake builds may leave read-only .git dirs that
    # MERA's overwrite cannot remove. Force-clean before deploying.
    if output_dir.exists():
        shutil.rmtree(output_dir, onerror=rm_readonly)
    output_dir.mkdir(parents=True, exist_ok=True)
    
    with mera.Deployer(str(output_dir), overwrite=True) as deployer:
        mera_model = load_model(deployer, model_path, symbolic_dims)
        
        ref_data = enable_ref_data and model_path.suffix.lower() == '.tflite'
        
        deployer.deploy(
            mera_model,
            mera_platform=platform,
            target=Target.MCU,
            vela_config=vela_config,
            mcu_config=mcu_config,
            enable_ref_data=ref_data
        )
    
    return True


# =============================================================================
# Memory Calculation
# =============================================================================


def needs_external_memory(memory_bytes: int, threshold_mb: float = 0.8) -> bool:
    """Check if model needs external memory based on size threshold."""
    threshold_bytes = threshold_mb * 1024 * 1024
    return memory_bytes > threshold_bytes




# =============================================================================
# Host Evaluation (Optional)
# =============================================================================

def rm_readonly(func, path, exc_info):
    """Handle read-only files during rmtree."""
    try:
        os.chmod(path, stat.S_IWRITE)
        func(path)
    except Exception as e:
        print(f"  Warning: Failed to remove {path}: {e}")


def _run_model_in_subprocess(build_dir: str, ref_inputs_path: str, ref_outputs_path: str, out_q: Queue):
    """
    Run compiled model in subprocess and compare outputs.
    """
    import math
    
    # On Windows, Python 3.8+ requires explicit DLL directory registration
    # for extension modules (.pyd) that depend on MinGW/UCRT runtime DLLs.
    if plt.system() == "Windows" and hasattr(os, 'add_dll_directory'):
        mingw_bin = r"C:\msys64\ucrt64\bin"
        if os.path.isdir(mingw_bin):
            os.add_dll_directory(mingw_bin)
        # Also add the build directory itself (where the .pyd and .dll files live)
        for dll_dir in [build_dir] + [str(p.parent) for p in Path(build_dir).rglob("*.pyd")]:
            if os.path.isdir(dll_dir):
                os.add_dll_directory(dll_dir)
    
    sys.path.insert(0, build_dir)
    
    compare_files = list(Path(build_dir).rglob("compare.exe")) + list(Path(build_dir).rglob("compare"))
    if not compare_files:
        out_q.put((False, "compare executable not found", [], []))
        return
    
    py_compute_dir = str(compare_files[0].parent)
    if py_compute_dir not in sys.path:
        sys.path.insert(0, py_compute_dir)
    
    try:
        import py_compute as c
        
        inp = list(np.load(ref_inputs_path, allow_pickle=True).item().items())[0][1]
        ref_outs = np.load(ref_outputs_path, allow_pickle=True)
        
        got_outs = c.compute(inp)
        
        matches = []
        psnrs = []
        mses = []
        
        for ref_out, got_out in zip(ref_outs, got_outs):
            diff = ref_out.astype(np.float32) - got_out.astype(np.float32)
            max_val = np.abs(diff).max()
            mse = np.mean(diff ** 2)
            
            if mse == 0:
                psnr = 100.0
            elif max_val == 0:
                psnr = 0.0
            else:
                psnr = 20 * math.log10(max_val) - 10 * math.log10(mse)
            
            match = (mse <= 0.1 or psnr >= 28)
            matches.append(match)
            psnrs.append(psnr)
            mses.append(mse)
        
        out_q.put((all(matches), "", psnrs, mses))
        
    except Exception as e:
        out_q.put((False, str(e), [], []))


def run_host_evaluation(deploy_qtz_path: Path, deploy_mcu_path: Path) -> tuple:
    """
    Build and run C-code on host to validate outputs against MERA Interpreter.
    
    Returns:
        tuple: (success: bool, error_msg: str, psnrs: list, mses: list)
    """
    cmake_file = None
    for dirpath, _, filenames in os.walk(deploy_mcu_path):
        if "CMakeLists.txt" in filenames:
            cmake_file = Path(dirpath) / "CMakeLists.txt"
            break
    
    if cmake_file is None:
        print("    Warning: No CMakeLists.txt found, skipping host evaluation")
        return (True, "No CMakeLists.txt found, skipping", [], [])
    
    source_dir = cmake_file.parent
    build_dir = source_dir / "build"
    
    if build_dir.exists():
        shutil.rmtree(build_dir, onerror=rm_readonly)
    build_dir.mkdir(parents=True, exist_ok=True)
    
    cmsis_path = os.environ.get("CMSISNN_SOURCE_DIR")
    if cmsis_path and os.path.isdir(cmsis_path):
        os.environ["CMSIS_REPO_GIT_REPOSITORY_ENV"] = cmsis_path.replace("\\", "/")
    
    pybind_path = os.environ.get("PYBIND11_SOURCE_DIR")
    if pybind_path and os.path.isdir(pybind_path):
        os.environ["PYBIND11_REPO_GIT_REPOSITORY_ENV"] = pybind_path.replace("\\", "/")
    
    cmake_cmd = ["cmake", "-DBUILD_PY_BINDINGS=ON"]
    
    if plt.system() == "Windows":
        if has_mingw_clang:
            cmake_cmd.extend(["-G", "MinGW Makefiles", "-DCMAKE_C_COMPILER=clang", "-DCMAKE_CXX_COMPILER=clang++"])
    
    cmake_cmd.append("..")
    
    try:
        # Configure
        subprocess.run(cmake_cmd, cwd=build_dir, check=True)
        
        # Build - limit parallelism to prevent memory exhaustion on laptops
        num_jobs = str(max(4, (os.cpu_count() or 8) // 2))
        subprocess.run(["cmake", "--build", ".", "--parallel", num_jobs], 
                       cwd=build_dir, check=True)
        
        print("    Host build successful")
        
    except subprocess.CalledProcessError as e:
        return (False, f"Build failed: {e}", [], [])
    except FileNotFoundError:
        print("    Warning: cmake not found on PATH, skipping host evaluation")
        return (True, "cmake not found, skipping", [], [])
    
    ref_inputs_path = deploy_qtz_path / "ref_qtz" / "inputs.npy"
    ref_outputs_path = deploy_qtz_path / "ref_qtz" / "outputs.npy"
    
    if not ref_inputs_path.exists() or not ref_outputs_path.exists():
        print("    Warning: Reference data not found, skipping output comparison")
        print(f"    Looked in: {deploy_qtz_path / 'ref_qtz'}")
        return (True, "", [], [])
    
    try:
        out_q = Queue()
        p = Process(
            target=_run_model_in_subprocess,
            args=(str(build_dir), str(ref_inputs_path), str(ref_outputs_path), out_q)
        )
        p.start()
        p.join(timeout=120)
        
        if p.is_alive():
            p.terminate()
            return (False, "Evaluation timed out", [], [])
        
        success, error_msg, psnrs, mses = out_q.get()
        
        if success:
            print(f"    Validation passed: PSNRs={psnrs}, MSEs={mses}")
        else:
            print(f"    Validation failed: {error_msg}")
        
        return (success, error_msg, psnrs, mses)
        
    except Exception as e:
        return (False, str(e), [], [])


# =============================================================================
# Main Compilation Flow
# =============================================================================

def compile_model(
    model_path: Path,
    output_dir: Path,
    args
) -> CompileResult:
    """
    Main compilation flow for a single model.
    
    This simplified version does NOT inject memory attributes.
    For NPU, it uses Vela's enable_ospi flag.
    """
    result = CompileResult(
        model_name=model_path.stem,
        model_path=model_path,
        output_dir=output_dir
    )
    
    # Cache parsed ONNX dims once for the entire compile flow
    onnx_dims = parse_onnx_dims(args.onnx_dims)
    
    print(f"\n{'='*60}")
    print(f"Compiling: {model_path.name}")
    print(f"{'='*60}")
    
    try:
        model_format = get_model_format(model_path)
        is_quantized = is_model_quantized(model_path)
        
        print(f"  Format: {model_format}")
        print(f"  Quantized: {is_quantized}")
        
        use_npu = args.npu
        use_quantize = args.quantize
        
        # Warn if INT8 ONNX/Executorch — these must be FP32 and quantized by MERA
        if is_quantized and model_format in ['onnx', 'executorch']:
            print_warning(f"  ⚠️  WARNING: INT8 {model_format} models cannot be deployed directly!")
            print(f"           Please provide FP32 model and use --quantize for MERA quantization.")
        
        if use_npu and not use_quantize and not is_quantized:
            print_warning("  ⚠️  WARNING: Model is FP32 - CANNOT run on NPU!")
            print("           NPU (Ethos-U) requires INT8. MERA will fallback to CPU.")
            print("           Use --quantize flag or provide INT8 model for actual NPU execution.")
        
        file_size_bytes = model_path.stat().st_size
        effective_size = file_size_bytes // 4 if (use_quantize and not is_quantized) else file_size_bytes
        needs_ext_mem = args.external or needs_external_memory(effective_size, args.memory_threshold)
        if needs_ext_mem and not args.external:
            file_size_mb = file_size_bytes / (1024 * 1024)
            print(f"  Auto-detected external memory need for large model ({file_size_mb:.2f} MB)")
        
        platform = Platform.MCU_ETHOS if use_npu else Platform.MCU_CPU
        print(f"  Platform: {platform}")
        
        vela_config = {
            'enable_ospi': needs_ext_mem and use_npu,
            'sys_config': 'RA8P1',
            'memory_mode': args.memory_mode,
            'accel_config': 'ethos-u55-256',
            'optimise': args.optimization,
            'verbose_all': False,
        }
        
        mcu_config = {
            'suffix': args.suffix,
            'weight_location': args.weight_loc.lower(),
            'use_x86': args.x86 or args.host_evaluate,
        }
        
        result.needs_external_memory = needs_ext_mem
        if needs_ext_mem:
            if use_npu:
                print(f"  External memory: Vela OSPI enabled")
            else:
                print(f"  External memory: flagged (directory suffix only)")
        
        deploy_model_path = model_path
        qtz_dir = output_dir / "quantization"
        calib_data = None
        
        if use_quantize and not is_quantized:
            print(f"  Quantizing model...")
            
            calib_path = Path(args.calib_data) if args.calib_data else None
            
            with mera.Deployer(str(qtz_dir), overwrite=True) as temp_deployer:
                temp_model = load_model(temp_deployer, model_path, onnx_dims)
                calib_data = load_calibration_data(calib_path, temp_model, args.calib_num)
            
            qtz_path = quantize_model(
                model_path,
                qtz_dir,
                platform,
                calib_data,
                onnx_dims
            )
            
            if qtz_path is None:
                result.status = Status.ERROR_QUANTIZER
                result.last_error = "Quantization failed"
                return result
            
            deploy_model_path = qtz_path
            print(f"  Quantized model: {qtz_path}")
        
        print(f"  Deploying model...")
        deploy_dir = output_dir / "deploy"
        
        deploy_model(
            deploy_model_path,
            deploy_dir,
            platform,
            vela_config,
            mcu_config,
            onnx_dims,
            args.ref_data
        )
        # Errors from deploy_model propagate as exceptions and are caught below
        
        print(f"  C-code generated in: {deploy_dir}")
        print(f"  ✅ Compilation complete: {deploy_dir}")
        artifacts_deploy_dir = deploy_dir
        
        if args.host_evaluate and not use_npu:
            qtz_ref_path = qtz_dir if use_quantize else output_dir / "deploy_qtz"
            
            ref_data_dir = qtz_ref_path
            if not (ref_data_dir / "ref_qtz" / "inputs.npy").exists():
                ref_calib_data = calib_data if use_quantize else None
                final_ref_dir = qtz_ref_path / "ref_qtz"
                generate_reference_data(deploy_model_path, final_ref_dir, ref_calib_data)
            
            print(f"  Running host evaluation...")
            success, error_msg, psnrs, mses = run_host_evaluation(qtz_ref_path, artifacts_deploy_dir)
            if not success:
                result.status = Status.ERROR_VALIDATION
                result.last_error = f"Host evaluation failed: {error_msg}"
                return result
        
        result.status = Status.SUCCESS
        print(f"  SUCCESS")
        
    except ValueError as e:
        result.status = Status.ERROR_DEPLOY
        result.last_error = str(e)
        print(f"  VALIDATION ERROR: {e}")
        
    except Exception as e:
        result.status = Status.ERROR_DEPLOY
        result.last_error = str(e)
        print(f"  ERROR: {e}")
    
    return result


def parse_onnx_dims(dims_str: str) -> Dict[str, int]:
    """Parse ONNX dimensions string like 'batch=1,width=224' (freezes to static values)."""
    if not dims_str:
        return SYMBOLIC_DIMS.copy()
    
    dims = SYMBOLIC_DIMS.copy()
    try:
        for item in dims_str.split(','):
            key, value = item.split('=')
            dims[key.strip()] = int(value.strip())
    except ValueError:
        print(f"Warning: Could not parse ONNX dims '{dims_str}', using defaults")
    
    return dims


# =============================================================================
# JUnit XML Output
# =============================================================================

def write_junit_xml(results: List[CompileResult], output_path: Path):
    """Write JUnit XML report."""
    try:
        from junitparser import TestCase, TestSuite, JUnitXml, Error
    except ImportError:
        print("Warning: junitparser not installed, skipping XML output")
        return
    
    suite = TestSuite(output_path.stem)
    
    for result in results:
        # Use the output folder name (e.g. model_NPU_external_quantized) as case name
        # so run_benchmark_v3's _lookup_metrics can match it directly to the deploy folder.
        case_name = result.output_dir.name + result.model_path.suffix
        test_case = TestCase(case_name)
        if result.status != Status.SUCCESS:
            test_case.result = [Error(result.last_error, result.status.name)]
        suite.add_testcase(test_case)
    
    xml = JUnitXml()
    xml.add_testsuite(suite)
    xml.write(str(output_path))
    print(f"JUnit XML written to: {output_path}")


# =============================================================================
# Config YAML Loading
# =============================================================================

def _parse_yaml_bool(value, field_name: str) -> bool:
    """Parse YAML bool values with support for common string/int representations."""
    if isinstance(value, bool):
        return value

    if isinstance(value, int):
        if value in (0, 1):
            return bool(value)
        print(f"Error: '{field_name}' must be a boolean (true/false), got integer: {value}")
        sys.exit(1)

    if isinstance(value, str):
        normalized = value.strip().lower()
        if normalized in ('true', 'yes', 'y', 'on', '1'):
            return True
        if normalized in ('false', 'no', 'n', 'off', '0'):
            return False
        print(f"Error: '{field_name}' must be a boolean, got string: '{value}'")
        sys.exit(1)

    print(f"Error: '{field_name}' must be a boolean, got type: {type(value).__name__}")
    sys.exit(1)

def load_config(config_path: str) -> Namespace:
    """
    Load compile configuration from a YAML file and return an args-compatible Namespace.

    Expected YAML structure:
        model_path: /path/to/model.tflite
        output_dir: /path/to/output
        target: cpu          # 'cpu' or 'npu'  (required)
        quantize: false
        external: false
        memory_threshold: 0.8
        calib_data: ''
        calib_num: 5
        memory_mode: Sram_Only
        optimization: Performance
        weight_loc: Flash
        suffix: ''
        onnx_dims: ''
        ref_data: false
        x86: false
        host_evaluate: false
        result: ''
        verbose: false
    """
    try:
        import yaml
    except ImportError:
        print("Error: PyYAML is not installed. Install it with: pip install pyyaml")
        sys.exit(1)

    config_file = Path(config_path)
    if not config_file.exists():
        print(f"Error: Config file does not exist: {config_file}")
        sys.exit(1)

    with open(config_file, 'r', encoding='utf-8') as f:
        cfg = yaml.safe_load(f)

    if cfg is None:
        print("Error: Config file is empty.")
        sys.exit(1)

    # -------------------------------------------------------------------------
    # Validate required fields
    # -------------------------------------------------------------------------
    if 'model_path' not in cfg:
        print("Error: 'model_path' is required in the config file.")
        sys.exit(1)
    if 'output_dir' not in cfg:
        print("Error: 'output_dir' is required in the config file.")
        sys.exit(1)

    target = str(cfg.get('target', '')).lower()
    if target not in ('cpu', 'npu'):
        print("Error: 'target' must be either 'cpu' or 'npu' in the config file.")
        sys.exit(1)

    # -------------------------------------------------------------------------
    # Validate choice fields
    # -------------------------------------------------------------------------
    memory_mode = cfg.get('memory_mode', 'Sram_Only')
    if memory_mode not in ('Sram_Only', 'Shared_Sram'):
        print(f"Error: 'memory_mode' must be 'Sram_Only' or 'Shared_Sram', got: '{memory_mode}'")
        sys.exit(1)

    optimization = cfg.get('optimization', 'Performance')
    if optimization not in ('Performance', 'Size'):
        print(f"Error: 'optimization' must be 'Performance' or 'Size', got: '{optimization}'")
        sys.exit(1)

    weight_loc = cfg.get('weight_loc', 'Flash')
    if weight_loc not in ('Flash', 'Iram'):
        print(f"Error: 'weight_loc' must be 'Flash' or 'Iram', got: '{weight_loc}'")
        sys.exit(1)

    # -------------------------------------------------------------------------
    # Build Namespace that mirrors the argparse output
    # -------------------------------------------------------------------------
    args = Namespace(
        model_path=str(cfg['model_path']),
        output_dir=str(cfg['output_dir']),
        # target flags
        cpu=(target == 'cpu'),
        npu=(target == 'npu'),
        # quantization
        quantize=_parse_yaml_bool(cfg.get('quantize', False), 'quantize'),
        # external memory
        external=_parse_yaml_bool(cfg.get('external', False), 'external'),
        memory_threshold=float(cfg.get('memory_threshold', 0.8)),
        # calibration
        calib_data=str(cfg.get('calib_data', '')),
        calib_num=int(cfg.get('calib_num', 5)),
        # MERA configuration
        memory_mode=memory_mode,
        optimization=optimization,
        weight_loc=weight_loc,
        suffix=str(cfg.get('suffix', '')),
        # ONNX options
        onnx_dims=str(cfg.get('onnx_dims', '')),
        # evaluation
        ref_data=_parse_yaml_bool(cfg.get('ref_data', False), 'ref_data'),
        x86=_parse_yaml_bool(cfg.get('x86', False), 'x86'),
        host_evaluate=_parse_yaml_bool(cfg.get('host_evaluate', False), 'host_evaluate'),
        # output
        result=str(cfg.get('result', '')),
        verbose=_parse_yaml_bool(cfg.get('verbose', False), 'verbose'),
    )

    return args


# =============================================================================
# CLI Argument Parser
# =============================================================================

def create_parser() -> ArgumentParser:
    """Create argument parser."""
    parser = ArgumentParser(
        prog='mcu_compile.py',
        description='MCU model compilation script (supports YAML config or CLI args)'
    )
    
    # Positional arguments (optional if YAML config is used)
    parser.add_argument('model_path', type=str, nargs='?',
                        help='Path to model file (.tflite, .onnx, .pte) or directory, or path to YAML config file')
    parser.add_argument('output_dir', type=str, nargs='?',
                        help='Output directory for compiled C-code')
    
    # Target platform (required for CLI mode)
    target_group = parser.add_mutually_exclusive_group(required=False)
    target_group.add_argument('--cpu', action='store_true',
                              help='Deploy for CPU (CMSIS-NN)')
    target_group.add_argument('--npu', action='store_true',
                              help='Deploy for NPU (Ethos-U55, requires INT8)')
    
    # Quantization (opt-in: without --quantize, model deploys as-is)
    parser.add_argument('--quantize', action='store_true',
                        help='Quantize FP32 model to INT8 before deploy')
    
    # External memory flag
    parser.add_argument('--external', action='store_true',
                        help='Force external memory mode (enables Vela OSPI for NPU)')
    
    # Memory threshold for auto-detection
    parser.add_argument('--memory-threshold', type=float, default=0.8,
                        help='Threshold in MB for auto-detecting external memory need (default: 0.8)')
    
    # Quantization options
    parser.add_argument('--calib-data', type=str, default='',
                        help='Path to calibration data (.npy file or directory)')
    parser.add_argument('--calib-num', type=int, default=5,
                        help='Number of calibration samples (default: 5)')
    
    # MERA configuration
    parser.add_argument('--memory-mode', type=str, default='Sram_Only',
                        choices=['Sram_Only', 'Shared_Sram'],
                        help='Vela memory mode (default: Sram_Only)')
    parser.add_argument('--optimization', type=str, default='Performance',
                        choices=['Performance', 'Size'],
                        help='Vela optimization target (default: Performance)')
    parser.add_argument('--weight-loc', type=str, default='Flash',
                        choices=['Flash', 'Iram'],
                        help='Weight storage location (default: Flash)')
    parser.add_argument('--suffix', type=str, default='',
                        help='Suffix for generated source files')
    
    # ONNX options
    parser.add_argument('--onnx-dims', type=str, default='',
                        help='ONNX symbolic dimensions to freeze (e.g., batch=1,width=224)')
    
    # Evaluation options
    parser.add_argument('--ref-data', action='store_true',
                        help='Generate reference I/O data for testing')
    parser.add_argument('--x86', action='store_true',
                        help='Generate x86 pybind11 bindings for manual host testing (implied by --host-evaluate)')
    parser.add_argument('--host-evaluate', action='store_true',
                        help='Build and run on host to validate outputs (CPU only, implies --x86)')
    
    # Output options
    parser.add_argument('--result', type=str, default='',
                        help='Path for JUnit XML output')
    parser.add_argument('--version', action='version', version=f'%(prog)s {__version__}')
    return parser


# =============================================================================
# Main
# =============================================================================

def main():
    detect_windows_compilers()
    
    parser = create_parser()
    
    # Check if first argument is a YAML config file
    if len(sys.argv) >= 2 and Path(sys.argv[1]).suffix.lower() in ('.yaml', '.yml'):
        print("Using YAML configuration mode...")
        args = load_config(sys.argv[1])
        input_mode = 'yaml'
    else:
        # Parse CLI arguments
        args = parser.parse_args()
        input_mode = 'cli'
        
        # Validate CLI mode: require both model_path and output_dir, and target
        if not args.model_path or not args.output_dir:
            print("Error: model_path and output_dir are required in CLI mode")
            parser.print_help()
            sys.exit(1)
        
        if not args.cpu and not args.npu:
            print("Error: --cpu or --npu is required in CLI mode")
            parser.print_help()
            sys.exit(1)
    
    model_path = Path(args.model_path).resolve()
    output_dir = Path(args.output_dir).resolve()
    
    if not model_path.exists():
        print(f"Error: Model path does not exist: {model_path}")
        sys.exit(1)
    
    if model_path.is_file():
        model_files = [model_path]
    else:
        model_files = (
            list(model_path.rglob("*.tflite")) +
            list(model_path.rglob("*.onnx")) +
            list(model_path.rglob("*.pte"))
        )
    
    if len(model_files) == 0:
        print(f"Error: No models found in: {model_path}")
        sys.exit(1)
    
    print(f"Found {len(model_files)} model(s)")
    print(f"Input mode: {input_mode.upper()}")
    
    results = []
    for model_file in model_files:
        target_str = "NPU" if args.npu else "CPU"
        
        # Check for external memory requirement (same logic as compile_model)
        effective_size = model_file.stat().st_size // 4 if args.quantize else model_file.stat().st_size
        needs_ext = args.external or needs_external_memory(effective_size, args.memory_threshold)
        
        ext_str = "_external" if needs_ext else ""
        quant_str = "_quantized" if args.quantize else ""
        
        safe_stem = model_file.stem.replace(' ', '_')
        base_dir_name = f"{safe_stem}_{target_str}{ext_str}{quant_str}{args.suffix}"
        model_output_dir = output_dir / base_dir_name
        
        result = compile_model(model_file, model_output_dir, args)
        results.append(result)
        
        # Force garbage collection to prevent memory buildup
        gc.collect()
    
    # Print summary
    print(f"\n{'='*60}")
    print("Summary")
    print(f"{'='*60}")
    
    success_count = sum(1 for r in results if r.status == Status.SUCCESS)
    print(f"Success: {success_count}/{len(results)}")
    
    for result in results:
        status_str = "SUCCESS" if result.status == Status.SUCCESS else f"ERROR: {result.last_error}"
        ext_str = " [EXTERNAL]" if result.needs_external_memory else ""
        print(f"  {result.model_name}: {status_str}{ext_str}")
    
    if args.result:
        write_junit_xml(results, Path(args.result))
    
    if success_count < len(results):
        sys.exit(1)


if __name__ == '__main__':
    main()
