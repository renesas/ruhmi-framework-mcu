
import os
import sys
import subprocess
import importlib
import textwrap
import numpy as np
import random

from pathlib import Path
from argparse import ArgumentParser
from dataclasses import dataclass
from enum import Enum

import mera
from mera import Platform, Target, quantizer

RANDOM_SEED = 42
np.random.seed(RANDOM_SEED)
random.seed(RANDOM_SEED)


SYMBOLIC_DIMS = {
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


#
# Compiles generated C99 source code and compares against the results
# of running the quantized models on the MERA Interpreter
#
def build_and_run(model: Model):
    cmake_file_path = None
    for dirpath, _, filenames in os.walk(model.deploy_mcu_path):
        if "CMakeLists.txt" in filenames:
            cmake_file_path = os.path.join(dirpath, "CMakeLists.txt")
            break
    if cmake_file_path is None:
        model.last_error = 'No CMakeLists.txt file found'
        model.status = Status.ERROR_DEPLOY

    source_dir = os.path.dirname(str(cmake_file_path))
    build_dir = os.path.join(source_dir, "build")
    if not os.path.exists(build_dir):
        os.mkdir(build_dir)
    try:
        subprocess.run(["cmake", "-DBUILD_PY_BINDINGS=ON", ".."], cwd=build_dir, check=True)
        subprocess.run(["cmake", "--build", ".", "--parallel", "32"], cwd=build_dir, check=True)
    except Exception as e:
        model.last_error = str(e)
        model.status = Status.ERROR_DEPLOY
        return

    added_to_sys_path = False
    exectutable_dir = str((list(Path(build_dir).rglob("compare.exe")) + list(Path(build_dir).rglob("compare")))[0].parent)
    try:
        if exectutable_dir not in sys.path:
            sys.path.insert(0, exectutable_dir)
            added_to_sys_path = True
        if "py_compute" in sys.modules:
            del sys.modules["py_compute"]
        try:
            importlib.import_module("py_compute")
        except ImportError as e:
            model.last_error = str(e)
            model.status = Status.ERROR_DEPLOY
            return

        script = textwrap.dedent(f"""
            import numpy as np
            import math
            import py_compute as c

            inp = list(np.load((Path("{model.deploy_qtz_path.resolve().as_posix()}")/Path("ref_qtz")/Path("inputs.npy")).resolve(), allow_pickle=True).item().items())[0][1]
            ref_out = list(np.load((Path("{model.deploy_qtz_path.resolve().as_posix()}")/Path("ref_qtz")/Path("outputs.npy")).resolve(), allow_pickle=True).item().items())[0][1]
            got_out = c.compute(inp)[0]
            mse = np.mean((ref_out.flatten() - got_out.flatten()) ** 2)

            max_val = ref_out.max() - got_out.min()
            psnr = 0
            if mse == 0:
                psnr = 100.0
            elif max_val == 0:
                psnr = 0.0
            else:
                psnr = 20 * math.log10(max_val) - 10 * math.log10(mse)

            matches = (mse <= 0.1 or psnr >= 28)
        """)

        exec(script, globals())
        ref_out = globals().get("ref_out")
        got_out = globals().get("got_out")
        mse = globals().get("mse")
        psnr = globals().get("psnr")

        if globals().get("matches"):
            model.status = Status.SUCCESS
        else:
            model.last_error = f'Mismatch(MSE={mse} PSNR={psnr})'
            model.status = Status.ERROR_MISMATCH
    except Exception as e:
        model.last_error = str(e)
        model.status = Status.ERROR_DEPLOY
        return
    finally:
        if added_to_sys_path and exectutable_dir in sys.path:
            sys.path.remove(exectutable_dir)


#
# Sets a threshold for enabling ospi support depending on the model size
#
def needs_ospi(file, size_mb):
    return os.path.getsize(file) / (1024 * 1024) > size_mb


#
# Compiles a quantized model for MCU/Ethos 
#
def deploy_mcu(model, model_path, result_path, with_ethos, with_ref_data=False):
    try:
        deploy_dir = Path(result_path)
        with mera.Deployer(str(deploy_dir), overwrite=True) as deployer:
            if model_path.suffix == '.mera':
                mera_model = mera.ModelLoader(deployer).from_quantized_mera(model_path)
            elif model_path.suffix == '.tflite':
                mera_model = mera.ModelLoader(deployer).from_tflite(model_path)
            elif with_ref_data:
                print("Generation of reference data only supported for TFLite models: skipping")
                return
            else:
                raise ValueError("Only MERA quantized and TFLite models are supported on this demo script")

            platform = Platform.MCU_ETHOS if with_ethos else Platform.MCU_CPU

            # ARM Vela options
            # only effective if Platform.MCU_ETHOS is selected, ignored otherwise
            vela_config = {}
            vela_config['enable_ospi'] = needs_ospi(model_path, 1.5)
            vela_config['sys_config'] = 'RA8P1'
            vela_config['memory_mode'] = 'Sram_Only'
            vela_config['accel_config'] = 'ethos-u55-256'
            vela_config['optimise'] = 'Performance'
            vela_config['verbose_all'] = False

            # MCU C code generation options
            mcu_config = {}
            mcu_config['suffix'] = ''
            mcu_config['weight_location'] = 'flash' # other option is: 'iram'

            # On other scripts we could use False and it will not generate
            # x86 related source code (python bindings for example),
            # but the current script relies on this option to be able to test
            # the generated C code outputs against the MERA Interpreter results
            mcu_config['use_x86'] = True

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
            output_data = runner.get_outputs_dict()
            return {'inputs': input_data, 'outputs': output_data}
    except Exception as e:
        model.status = Status.ERROR_RUNTIME
        model.last_error = str(e)
        return {'inputs': None, 'outputs': None}


def main():
    arg_p = ArgumentParser('MCU quantization and deployment demo')
    arg_p.add_argument('models_path', type=str, help='Path to fp32 models')
    arg_p.add_argument('deploy_dir', type=str, help='Directory for storing the results')
    arg_p.add_argument('-c', '--calib_num', type=int, default=5, help='Number of random calibration samples to use')
    arg_p.add_argument('-e','--ethos', action='store_true', help='Deploy for Ethos-U55')
    arg_p.add_argument('-r','--ref_data', action='store_true', help='Generate reference data in C99 source code format')
    args = arg_p.parse_args()

    models_path = Path(args.models_path).resolve()
    deploy_dir = Path(args.deploy_dir).resolve()

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

    for name, model in models.items():
        #
        # Quantize the model
        #
        quantization_platform = Platform.MCU_ETHOS if args.ethos else Platform.MCU_CPU
        qtzed_path = quantize(model, model.model_path, model.quantization_path, quantization_platform,
                              quantizer.QuantizerConfigPresets.MCU, args.calib_num)
        if model.last_error or not qtzed_path:
            continue

        #
        # Deploy the quantized model, run it and save inputs/output as reference data
        #
        ref_data = deploy_and_run(model, qtzed_path, model.deploy_qtz_path,
                                  Platform.MCU_CPU, Target.MERAInterpreter)
        ref_data_path = model.deploy_qtz_path / 'ref_qtz'
        ref_data_path.mkdir(parents=True, exist_ok=True)
        np.save(str(ref_data_path / 'inputs.npy'), ref_data['inputs'])
        np.save(str(ref_data_path / 'outputs.npy'), ref_data['outputs'])
        if model.last_error:
            continue

        #
        # Deploy for MCU / ETHOS
        #
        deploy_mcu(model, qtzed_path, model.deploy_mcu_path, args.ethos)
        if model.last_error:
            continue

        # Optional (only needed for debugging and testing)
        # Generate reference data in form of C99 source code
        # Note we will use the original TFLite format unquantized model
        # and run it with the TFLite runtime (selecting the TFLite's reference kernels)
        if args.ref_data:
            deploy_mcu(model, model.model_path, model.ref_data_path, args.ethos, with_ref_data=True)
            if model.last_error:
                continue

        #
        # Build generated C source code and compare against outputs produced by the quantized model
        # If Ethos support was enabled we will only generate the C99 source code
        #
#       if not args.ethos:     // removed once
#          build_and_run(model)     // removed once

    #
    # Print a summary
    #
    for name, model in models.items():
        if model.last_error:
            print(f'{model.model_path.suffix},{name},Error,{model.last_error}')
        else:
            print(f'{model.model_path.suffix},{name},Success')


if __name__ == '__main__':
  main()

