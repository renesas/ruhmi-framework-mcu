
import os
import sys
import subprocess
import importlib
import textwrap
import random
import platform as plt
import shutil
import json
import stat
import re
import numpy as np

from pathlib import Path
from argparse import ArgumentParser
from dataclasses import dataclass
from enum import Enum
from multiprocessing import Process, Queue

import mera
from mera import Platform, Target, quantizer

py_module_path = os.getenv("PY_MODULES_DIR")
if py_module_path and py_module_path not in sys.path:
    sys.path.insert(0, py_module_path)
    from  onnxSpy import analyze_model, print_analyze_results
    has_onnx_spy = True
else:
    has_onnx_spy = False

RANDOM_SEED = 42
np.random.seed(RANDOM_SEED)
random.seed(RANDOM_SEED)

# globals
args = None
mcu_config      = { }
has_mvs_clang   = False
has_mingw_clang = False

# please define unset onnx model variables here
SYMBOLIC_DIMS = {
    'batch' : 1,
    'batch_size' : 1,
    'width' : 224,
    'height' : 224,
    'num_channels' : 3,
    'N' : 1,
    'unk__6578' : 1,
    'unk__6579' : 1,
    'unk__6580' : 1,
}


class Status(Enum):
    IN_PROGRESS = 1
    ERROR_QUANTIZER = 2
    ERROR_PSNR = 3
    ERROR_DEPLOY = 4
    ERROR_RUNTIME = 5
    ERROR_MISMATCH = 6
    SUCCESS = 7


@dataclass
class Model:
    model_name: str
    model_path: Path
    deploy_qtz_path: Path
    deploy_mcu_path: Path
    quantization_path: Path
    ref_data_path: Path
    last_error: str = ''
    status: Status = Status.IN_PROGRESS

##
# START: helper functions
##

# search for MinGW compiler (clang)
def get_mingw_by_path():
    mingw_paths = []
    probe_list = ["mingw"]
    for raw_path in os.environ.get("PATH", "").split(";") :
        clean_path = (os.path.normpath(raw_path)).strip()
        if clean_path.count(":") > 1 or (not os.path.exists(clean_path)) :
            continue  # Skip this lines
        stop_loop = False
        for dir_files in os.listdir(clean_path):
            for search_string in probe_list:
                if search_string in dir_files:
                    full_exe_path = os.path.join(clean_path,"clang++.exe")
                    if (os.path.exists(full_exe_path)) :
                        mingw_paths.append(clean_path)
                        # possible enhacement on this point get major and minor
                        # version numbers and sort by it
                    stop_loop = True
            if stop_loop:
                break
    return mingw_paths

# check if Visual Studio is available and clang is installed

def find_mvs_vswhere():
    progrs  = os.environ.get("ProgramFiles(x86)", "C:\\Program Files (x86)")
    vswhere = Path(progrs) / "Microsoft Visual Studio" / "Installer" / "vswhere.exe"
    return str(vswhere) if vswhere.exists() else None

def get_mvs_clang_version(path):
    try:
        output = subprocess.check_output([path, "--version"], encoding="utf-8")
        return output
    except subprocess.CalledProcessError:
        return ""

def is_mvs_clang_installed():
    vswhere = find_mvs_vswhere()
    if not vswhere:
        return 0
    try:
        outJson = subprocess.check_output([ vswhere,
                                            "-latest", "-products", "*",
                                            "-requires", "Microsoft.VisualStudio.Component.VC.Llvm.Clang",
                                            "-format", "json" ],
                                            encoding="mbcs")
        outJsonObj = json.loads(outJson)
        print(f"Look for development tools")
        if outJsonObj :
            m_vers = outJsonObj[0].get("installationVersion").split(".")[0]
            year   = outJsonObj[0]["catalog"].get("productLineVersion").split(".")[0]
            ident  = f"Visual Studio {m_vers} {year}"
            tmpP = outJsonObj[0].get("displayName", "")
            print(f"    {tmpP}")
            tmpP = outJsonObj[0].get("installationVersion", "")
            print(f"    Version: {tmpP}")
            tmpP = outJsonObj[0].get("installationPath", "")
            clangPath = os.path.join(tmpP, "VC", "Tools", "Llvm", "x64", "bin", "clang.exe")
            if os.path.isfile(clangPath):
                clangVersion = get_mvs_clang_version(clangPath)
                print(f"    Clang  : {clangVersion}")
                os.environ["CMAKE_GENERATOR"] = ident
                os.environ["CMAKE_GENERATOR_TOOLSET"] = "ClangCl"
                #os.environ["CMAKE_C_STANDARD"] = "99"
            else :
                print(f"    Clang  : - not installed -")
                return 0
        return len(outJsonObj) > 0
    except subprocess.CalledProcessError:
        return 0

## function for onnx info print

def onnx_info(path):
    global has_onnx_spy
    fileName = os.path.basename(path)
    if has_onnx_spy:
        print(f"\nModel: {fileName}")
        result = analyze_model(path)
        print_analyze_results(result)
        print(f"\n")
#
# on error function for delete of protected files
# (called by shutil.rmtree)
#
def rm_readonly(func, path, exc_info):
    try:
        os.chmod(path, stat.S_IWRITE)
        func(path)
    except Exception as e:
        print(f"rm_readonly failed for {path}: {e}")

##
## END: helper functions
##

def run_model(model, build_dir, out_q, has_mingw_clang_v):
    # add some python module search pathes, whih are project depending
    sys.path.insert(0, build_dir)
    # We are searching for py_compute.*.pyd which is in the same direcory as <compare|compare.exe>
    # So lets use the simple way to find it
    py_compute_dir = str((list(Path(build_dir).rglob("compare.exe")) + list(Path(build_dir).rglob("compare")))[0].parent)
    if py_compute_dir not in sys.path:
        sys.path.insert(0, py_compute_dir)

    if plt.system() == "Windows":
        if (has_mingw_clang_v) :
            mingw_paths = get_mingw_by_path()
            if len(mingw_paths) > 0:
                os.add_dll_directory(mingw_paths[0])

    import numpy as np
    import math
    import py_compute as c

    inp = list(np.load(f"{model.deploy_qtz_path}/ref_qtz/inputs.npy", allow_pickle=True).item().items())[0][1]
    ref_outs = np.load(f"{model.deploy_qtz_path}/ref_qtz/outputs.npy", allow_pickle=True)

    got_outs = c.compute(inp)

    matches = []
    psnrs = []
    mses = []
    for ref_out, got_out in zip(ref_outs, got_outs):
        diff = ref_out.astype(np.float32) - got_out.astype(np.float32)
        max_val = np.abs(diff).max()
        mse = np.mean(diff ** 2)

        psnr = 0
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
    out_q.put((matches, psnrs, mses))


#
# Compiles generated C99 source code and compares against the results
# of running the quantized models on the MERA Interpreter
#
def build_and_run(model: Model):
    cmake_file_path = None
    global args
    global has_mingw_clang
    global has_mvs_clang

    for dirpath, _, filenames in os.walk(model.deploy_mcu_path):
        if "CMakeLists.txt" in filenames:
            cmake_file_path = os.path.join(dirpath, "CMakeLists.txt")
            break
    if cmake_file_path is None:
        model.last_error = 'No CMakeLists.txt file found'
        model.status = Status.ERROR_DEPLOY

    source_dir = os.path.dirname(str(cmake_file_path))
    build_dir = os.path.join(source_dir, "build")

    # remove old build dir
    if os.path.exists(build_dir):
        shutil.rmtree(build_dir, onerror=rm_readonly)
    if not os.path.exists(build_dir):
        os.mkdir(build_dir)

    cmd_arg = "cmake -DBUILD_PY_BINDINGS=ON"
    # add mingw64 support on windows
    if plt.system() == "Windows":
        if (has_mingw_clang) :
            cmd_arg = cmd_arg + " -G \"MinGW Makefiles\" -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_MAKE_PROGRAM=mingw32-make"
            #CMSIS setting is -Ofast (avoid warnings --> -O3)
            #additional possible options compiler -fno-lto linker -fno-lto (-DCMAKE_INTERPROCEDURAL_OPTIMIZATION=OFF for the moment)
            cmd_arg = cmd_arg + " -DCMAKE_INTERPROCEDURAL_OPTIMIZATION=OFF"
            cmd_arg = cmd_arg + " -DCMSIS_OPTIMIZATION_LEVEL=-O3"
        else:
           if not has_mvs_clang :
              return

    cmsis_path = os.environ.get("CMSISNN_SOURCE_DIR")
    if  cmsis_path and  os.path.isdir(cmsis_path) :
        #cmd_arg=cmd_arg + " -DFETCHCONTENT_SOURCE_DIR_CMSISNN=" + cmsis_path
        os.environ["CMSIS_REPO_GIT_REPOSITORY_ENV"] = cmsis_path.replace("\\","/")

    pybin_path = os.environ.get("PYBIND11_SOURCE_DIR")
    if pybin_path and os.path.isdir(pybin_path) :
        #cmd_arg=cmd_arg + " -DFETCHCONTENT_SOURCE_DIR_PYBIND11=" + pybin_path
        os.environ["PYBIND11_REPO_GIT_REPOSITORY_ENV"] = pybin_path.replace("\\","/")

    cmd_arg=cmd_arg + " .."
    #+ " --trace-expand"
    #print(f"{cmd_arg}")

    try:
        #subprocess.run(["cmake", "-DBUILD_PY_BINDINGS=ON", ".."], cwd=build_dir, check=True)
        subprocess.run( cmd_arg, cwd=build_dir, check=True, shell=True)
        subprocess.run(["cmake", "--build", ".", "--parallel", "32"], cwd=build_dir, check=True)
    except Exception as e:
        model.last_error = str(e)
        model.status = Status.ERROR_DEPLOY
        return

    added_to_sys_path = False
    try:
        out_q = Queue()
        p = Process(target=run_model, args=(model, build_dir, out_q, has_mingw_clang))
        p.start()
        p.join()
        matches, psnrs, mses = out_q.get()
        print (f"matches: {matches}, psnr: {psnrs}, mse {mses}")
        if all(matches):
            model.status = Status.SUCCESS
        else:
            model.last_error = f'Mismatch(MSEs={mses} PSNRs={psnrs})'
            model.status = Status.ERROR_MISMATCH
    except Exception as e:
        model.last_error = str(e)
        model.status = Status.ERROR_DEPLOY
        return
    finally:
        if added_to_sys_path and build_dir in sys.path:
            sys.path.remove(build_dir)


#
# Sets a threshold for enabling ospi support depending on the model size
#
def needs_ospi(file, size_mb):
    return os.path.getsize(file) / (1024 * 1024) > size_mb


#
# Compiles a quantized model for MCU/Ethos
#
def deploy_mcu(model, model_path, result_path, with_ethos, with_ospi=False, with_ref_data=False):
    global args
    global has_mvs_clang

    try:
        deploy_dir = Path(result_path)

        #remove old build dir
        build_dir = os.path.join(deploy_dir, "build")
        if os.path.exists(build_dir):
            shutil.rmtree(build_dir, onerror=rm_readonly)

        with mera.Deployer(str(deploy_dir), overwrite=True) as deployer:
            if model_path.suffix == '.mera':
                mera_model = mera.ModelLoader(deployer).from_quantized_mera(model_path)
            elif model_path.suffix == '.tflite':
                mera_model = mera.ModelLoader(deployer).from_tflite(model_path)
            elif with_ref_data:
                print("Only MERA quantized and TFLite models are supported on this demo script")
                return
            elif model_path.suffix == '.pte':
                mera_model = mera.ModelLoader(deployer).from_executorch(model_path)
            elif model_path.suffix == '.onnx':
                onnx_info(str(model_path))
                mera_model = mera.ModelLoader(deployer).from_onnx(model_path, shape_mapping=SYMBOLIC_DIMS)
            else:
                raise ValueError("Model file extension not supported: " + model_path.suffix)

            platform = Platform.MCU_ETHOS if with_ethos else Platform.MCU_CPU

            # ARM Vela options
            # only effective if Platform.MCU_ETHOS is selected, ignored otherwise
            vela_config = {}
            vela_config['enable_ospi']  = with_ospi
            vela_config['sys_config']   = 'RA8P1'
            vela_config['memory_mode']  = args.memory_mode
            vela_config['accel_config'] = 'ethos-u55-256'
            vela_config['optimise']     = args.optimization_mode
            vela_config['verbose_all']  = False

            # MCU C code generation options
            global mcu_config
            mcu_config['suffix']          = args.suffix
            mcu_config['weight_location'] = args.weight_loc.lower() # other option is: 'iram'

            # generation of reference data from original model format
            # using the original runtime is only supported for TFLite models
            enable_ref_data = with_ref_data and model_path.suffix == '.tflite'

            deployer.deploy(mera_model,
                            mera_platform=platform,
                            target=Target.MCU,
                            vela_config=vela_config,
                            mcu_config=mcu_config,
                            enable_ref_data=enable_ref_data)
    except Exception as e:
            model.status = Status.ERROR_DEPLOY
            model.last_error = str(e)


#
# Generates input/output reference data for a given model
#
def generate_input_data(mera_model, num_samples):
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
                raise ValueError("Input reference data: datatype not supported: " + str(dtype))
        data.append(input_data)
    return data

#
# Quantize a Torch/TFLite/ONNX model
#
def quantize(model, model_path, result_path, platform, quantizer_config, num_cal):
    try:
        deploy_dir = Path(result_path)
        with mera.Deployer(str(deploy_dir), overwrite=True) as deployer:
            if model_path.suffix == '.tflite':
                mera_model = mera.ModelLoader(deployer).from_tflite(str(model_path))
            elif model_path.suffix == '.onnx':
                onnx_info(str(model_path))
                mera_model = mera.ModelLoader(deployer).from_onnx(str(model_path), shape_mapping=SYMBOLIC_DIMS)
            elif model_path.suffix == '.pte':
                mera_model = mera.ModelLoader(deployer).from_executorch(str(model_path))
            else:
                raise ValueError("Unsupported model format: " + model_path.suffix)

            cal_data = generate_input_data(mera_model, num_cal)
            qtzer = mera.Quantizer(deployer, mera_model, quantizer_config=quantizer_config, mera_platform=platform)
            qtz_path = Path(result_path)
            res_path = qtz_path / 'model.mera'
            qty = qtzer.calibrate(cal_data).quantize().evaluate_quality(cal_data[:1])
            Q = qty[0].out_summary()[0]
            if Q["psnr"] < 5:
                model.status = Status.ERROR_PSNR
                model.last_error = f'PSNR too low: {Q["psnr"]}'
                return {'inputs': None, 'outputs': None}

            qtzer.save_to(res_path)
            print(f'Successfully quantized model with quality: {Q["psnr"]} psnr, {Q["score"]} score')
            return res_path
    except Exception as e:
        model.status = Status.ERROR_QUANTIZER
        model.last_error = str(e)
        return None


#
# Deploy and runs a model creating input data if necessary
#
def deploy_and_run(model, model_path, result_path, platform, target, ref_input_data=None):
    try:
        deploy_dir = Path(result_path)
        with mera.Deployer(str(deploy_dir), overwrite=True) as deployer:
            if model_path.suffix == '.tflite':
                mera_model = mera.ModelLoader(deployer).from_tflite(str(model_path))
            elif model_path.suffix == '.onnx':
                onnx_info(str(model_path))
                mera_model = mera.ModelLoader(deployer).from_onnx(str(model_path), shape_mapping=SYMBOLIC_DIMS)
            elif model_path.suffix == '.pte':
                mera_model = mera.ModelLoader(deployer).from_executorch(str(model_path))
            elif model_path.suffix == '.mera':
                mera_model = mera.ModelLoader(deployer).from_quantized_mera(str(model_path))
            else:
                raise ValueError("Unsupported model format: " + model_path.suffix)

            input_data = ref_input_data
            if ref_input_data is None:
                input_data = generate_input_data(mera_model, 1)[0]
            deploy = deployer.deploy(mera_model, mera_platform=platform, target=target)
            runner = deploy.get_runner()
            runner.set_input(input_data).run()
            output_data = runner.get_outputs()
            return {'inputs': input_data, 'outputs': output_data}
    except Exception as e:
        model.status = Status.ERROR_RUNTIME
        model.last_error = str(e)
        return {'inputs': None, 'outputs': None}


def main():
    arg_p = ArgumentParser('mcu_quantize.py - MCU quantization and deployment demo')
    arg_p.add_argument('models_path', type=str, help='Path to fp32 models')
    arg_p.add_argument('deploy_dir', type=str, help='Directory for storing the results')
    arg_p.add_argument('-c', '--calib_num', type=int, default=5, help='Number of random calibration samples to use')
    arg_p.add_argument('-e', '--ethos', action='store_true', help='Deploy for Ethos-U55')
    arg_p.add_argument('-r', '--ref_data', action='store_true', help='Generate reference data in C99 source code format')
    arg_p.add_argument('-f', '--fp32', action='store_true', help='Deploy for MCU with FP32 precision skip quantization')

    arg_p.add_argument('--ospi', action='store_true', help='Use OSPI memory')
    arg_p.add_argument('--no_host_evaluate', action='store_true', help='Disable compilation on host machine for reference evaluation')
    arg_p.add_argument('--suffix', type=str, default='', help="Add the suffix to the output source code when converting for CPU")
    choices_memory_mode = ["Sram_Only","Shared_Sram"]
    arg_p.add_argument('--memory_mode', choices=choices_memory_mode, default=choices_memory_mode[0], help="vela option for model storage Sram_Only/Shared_Sram")
    choices_optimization_mode = ["Performance","Size"]
    arg_p.add_argument('--optimization_mode', choices=choices_optimization_mode, default=choices_optimization_mode[0], help="vela optimization target Performance/Size")
    choices_weight_loc = ["Flash","Iram"]
    arg_p.add_argument('--weight_loc', choices=choices_weight_loc, default=choices_weight_loc[0], help="C-Code only option for model storage")
    arg_p.add_argument('--set_onnx_parameter', type=str, default='batch=1',metavar="<name>=<value>[,<name>=<value>]+" , help="set dynamic variable of onnx models ( e.g., --set_onnx_parameter batch=1,width=224,height=224 )")
    arg_p.add_argument('--msc', action='store_true', help='Use Microsoft Studio Code Clang instead of MinGW')

    arg_p.add_argument('--result', type=str, default='', help="Name of the result file")

    global args
    global mcu_config
    global has_mvs_clang
    global has_mingw_clang

    args = arg_p.parse_args()

    models_path = Path(args.models_path).resolve()
    deploy_dir  = Path(args.deploy_dir).resolve()
    if args.result:
        result_path = Path(args.result).resolve()


    # On other scripts we could use False and it will not generate
    # x86 related source code (python bindings for example),
    # but the current script relies on this option to be able to test
    # the generated C code outputs against the MERA Interpreter results
    mcu_config['use_x86'] = True

    #
    # get system information about available compiler
    #
    has_mvs_clang   = False
    has_mingw_clang = False
    has_cmake    = bool(shutil.which("cmake"))
    has_git      = bool(shutil.which("git"))

    if ( args.no_host_evaluate or (not has_cmake) or (not has_git) ):
        mcu_config['use_x86'] = False

    if plt.system() == "Windows":
        # priority is MINGW fall back to Microsoft Visual Studio with clang package if existing
        if args.msc:
            mingw_paths = [ ]
        else:
            mingw_paths = get_mingw_by_path()

        if len(mingw_paths) == 0:
            has_mvs_clang = is_mvs_clang_installed()
        else:
            has_mingw_clang = True

        has_compiler = bool(has_mvs_clang or has_mingw_clang)

        if ( not has_compiler ):
            mcu_config['use_x86'] = False
    else:
        has_compiler = bool(shutil.which("cl")) or bool(shutil.which("g++")) or bool(shutil.which("clang++"))
        if ( not has_compiler ):
            mcu_config['use_x86'] = False

        if ( not args.no_host_evaluate )and ( not mcu_config['use_x86'] ) :
            print( "Info: Disable cross compilation and validation on host machine")
            print(f"      has     cmake   : {has_cmake}")
            print(f"      has     git     : {has_git}")
            print(f"      has c++ compiler: {has_compiler}\n")

    #
    # set onnx dimension parameter
    #
    if args.set_onnx_parameter:
        try:
            symbolic_dims_in = dict(re.split(r'[=]', item) for item in args.set_onnx_parameter.split(","))
            symbolic_dims_dict = {k: int(v) for k, v in symbolic_dims_in.items()}
        except ValueError:
            print("Error: Make sure all entries are in key:value format and values are integers.")
        SYMBOLIC_DIMS.update(symbolic_dims_dict)

    #
    # create directories to store results for each model
    #
    models = {}
    models_path = \
        list(models_path.rglob("*.tflite")) + \
        list(models_path.rglob("*.onnx")) + \
        list(models_path.rglob("*.pte"))

    for i, model_path in enumerate(models_path):
        model_name = f'model_{i:03d}_' + model_path.stem
        deploy_qtz_path = deploy_dir / model_name / 'deploy_qtz'
        deploy_mcu_path = deploy_dir / model_name / 'deploy_mcu'
        qtz_path = deploy_dir / model_name / 'quantization'
        ref_data_path = deploy_dir / model_name / 'reference_data'
        deploy_qtz_path.mkdir(parents=True, exist_ok=True)
        deploy_mcu_path.mkdir(parents=True, exist_ok=True)
        qtz_path.mkdir(parents=True, exist_ok=True)
        ref_data_path.mkdir(parents=True, exist_ok=True)
        status = Model(model_name, model_path, deploy_qtz_path, deploy_mcu_path, qtz_path, ref_data_path)
        models[model_name] = status

    use_quantizer = False if args.fp32 else True

    for name, model in models.items():
        #
        # Quantize the model
        #
        if use_quantizer:
            quantization_platform = Platform.MCU_ETHOS if args.ethos else Platform.MCU_CPU
            qtzed_path = quantize(model, model.model_path, model.quantization_path, quantization_platform,
                                  quantizer.QuantizerConfigPresets.MCU, args.calib_num)
            if model.status != Status.IN_PROGRESS or not qtzed_path:
                continue

        #
        # Deploy the quantized model, run it and save inputs/output as reference data
        #
        model_path = qtzed_path if use_quantizer else model.model_path
        ref_data = deploy_and_run(model, model_path, model.deploy_qtz_path,
                                  Platform.MCU_CPU, Target.MERAInterpreter)
        ref_data_path = model.deploy_qtz_path / 'ref_qtz'
        ref_data_path.mkdir(parents=True, exist_ok=True)
        np.save(str(ref_data_path / 'inputs.npy'), ref_data['inputs'])
        if ref_data['outputs']:
            outputs = np.empty(len(ref_data['outputs']), object)
            outputs[:] = ref_data['outputs']
        else:
            outputs = []
        np.save(str(ref_data_path / 'outputs.npy'), outputs, allow_pickle=True)
        if model.status != Status.IN_PROGRESS:
            continue

        #
        # Deploy for MCU / ETHOS
        #
        # auto detection or force by option
        enable_ospi = args.ospi or needs_ospi(model_path, 1.5)
        deploy_mcu(model, model_path, model.deploy_mcu_path, args.ethos, with_ospi=enable_ospi)
        if model.status != Status.IN_PROGRESS:
            continue

        # Optional (only needed for debugging and testing)
        # Generate reference data in form of C99 source code
        # Note we will use the original TFLite format unquantized model
        # and run it with the TFLite runtime (selecting the TFLite's reference kernels)
        if args.ref_data:
            deploy_mcu(model, model.model_path, model.ref_data_path, args.ethos, with_ospi=False, with_ref_data=True)
            if model.status != Status.IN_PROGRESS:
                continue

        #
        # Build generated C source code and compare against outputs produced by the quantized model
        # If Ethos support was enabled we will only generate the C99 source code
        #
        if (not args.ethos) and ( mcu_config['use_x86'] is True ) :
            build_and_run(model)
        else:
            model.status = Status.SUCCESS

    #
    # Print a summary
    #
    print("\nSummary:")
    for name, model in models.items():
        if model.status != Status.SUCCESS:
            print(f'{model.model_path.suffix},{name},Error,{model.last_error}')
        else:
            print(f'{model.model_path.suffix},{name},Success')

    if args.result:
        from junitparser import TestCase, TestSuite, JUnitXml, Skipped, Error

        suite = TestSuite(result_path.stem)
        for name, model in models.items():
            test_case = TestCase(name + model.model_path.suffix)
            if model.status != Status.SUCCESS:
                test_case.result = [Error(model.last_error, model.status.name)]
            suite.add_testcase(test_case)

        xml = JUnitXml()
        xml.add_testsuite(suite)
        xml.write(result_path)


if __name__ == '__main__':
  main()
