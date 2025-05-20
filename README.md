

# RUHMI 2.3.1 Release - MCU

The present package provides the RUHMI software stack with support for MCUs and Ethos-U55 support.
=======


## Software stack overview

 * `sample_e2studio_ethos_projects` contains e2Studio projects for Renesas RA8P1 boards showcasing
    inference of several ML models deployed using the RUHMI compiler with the Ethos support enabled.

 * `install` contains PIP package of RUHMI 2.3.1 MCU
 * `scripts` contains python scripts to showcase the RUHMI API for model quantization and deployment
    of TFLite, ONNX and Torch models on MCU and Ethos targets
 * `models_fp32` directory with the models used on the RUHMI Quantizer + MCU demo
 * `models_fp32_ethos` directory with the models used on the RUHMI Quantizer + Ethos-U55 demo
 * `models_int8` directory with third-party quantized models used for the RUHMI MCU deployment demo

## e2Studio Projects

Under the directory `sample_e2studio_ethos_projects` you can find pre-generated projects for different
models of interest as Wav2Letter, RNNoise, Yolo and others.

These should be ready to use out of the box from an installation of e2studio that contains FSP 5.7.0
and support for the EK-RA8P1 WSB boards with device R7KA8P1KFLCAC.

The versions of e2studio and components used are:

```
  Version: 2024-10 (24.10.0)
  Build Id: R20241003-1714

  Board:  	EK-RA8P1 WSB
  Device:  	R7KA8P1KFLCAC
  Core:  	CPU0
  Toolchain:  	LLVM for ARM
  Toolchain Version:  	18.1.3
  FSP Version:  	5.7.0

  Board Support Package Common Files  	v5.7.0
  Arm CMSIS Version 6 - Core (M)  	v6.1.0+fsp.5.7.0
  Ethos-u core driver  	v24.8.0+fsp.5.7.0
  Arm DSP Library Source  	v1.16.2+fsp.5.7.0
  Ethos-u core inference process  	v24.8.0+fsp.5.7.0
  Arm NN Library Source  	v6.0.0+fsp.5.7.0
  Octa Serial Peripheral Interface Flash  	v5.7.0
  Ethos-U Driver Wrapper Implementation  	v5.7.0
```

### Vela version

The version of ARM Vela compiler used to compile those subgraphs assigned to the Ethos-U55 target is 4.2.0.
Note that when installing the RUHMI 2.3.1 PIP package it will automatically pull Vela 4.2 as a dependency.

## RUHMI Installation

Under the directory `install` PIPs package is provded.
In order to install RUHMI 2.3.1 MCU on supported environment you will need:

 * A machine with Ubuntu 22.04 installation is recommended as this was the version used for testing
 * A working installation of PyEnv or other Python virtual environment management system that provides
   Python version 3.10.15 (recommended altough other versions might work as well)

### Installation steps

#### System dependencies necessary for the demos

Please install:

```bash
sudo apt update; sudo apt install build-essential cmake
```

#### Notes about PyEnv installation

If you don't have a working Python virtual environment management system you can get one with the following
steps:

```bash
# pyenv dependencies
sudo apt update; sudo apt install build-essential libssl-dev zlib1g-dev \
libbz2-dev libreadline-dev libsqlite3-dev curl git cmake \
libncursesw5-dev xz-utils tk-dev libxml2-dev libxmlsec1-dev libffi-dev liblzma-dev

# actual installation of PyEnv (check post-install notes)
curl https://pyenv.run | bash
```

Note the post-installation steps shown at the end of the installation script
necessary to make PyEnv available on the system.

#### Python Virtual Environment for RUHMI

We need to create a virtual environment suitable for RUHMI:

```bash
MENV=mera-env; pyenv install 3.10.15 && pyenv virtualenv 3.10.15 $MENV && pyenv activate $MENV && \
pip install --upgrade pip && \
pip install decorator typing_extensions psutil attrs pybind11
```

Your prompt should now show that you are under a virtual environment `mera-env`:

```bash
(mera-env) user@compute-01:~$
```

#### Install RUHMI

Finally install RUHMI on the virtual environment `mera-env`:

```bash
cd install/
pip install ./RUHMI-2.3.1+pkg.1503-cp310-cp310-manylinux_2_27_x86_64.whl
```


At this point MERA should be ready to use. You can confirm with the following example:

```bash
python -c "import mera;print(dir(mera))"
```

##### Windows requirements

Note that we also provide the a version for Windows under the same directory `install`.
The PIP package of RUHMI 2.3.1 MCU for windows was tested with:

 * Windows 11
 * VisualStudio Professional 2022

Only requirement is to install the C++ runtime libraries.
Please download and install [this package](https://aka.ms/vs/17/release/vc_redist.x64.exe).

### How to deploy models with RUHMI 2.3.1 MCU

The following shows how to use the RUHMI deployment API to compile an already quantized TFLite model on a board with Ethos-U55 support:

```python
import os
import mera

from mera import Platform, Target

def needs_ospi(file, size_mb):
    return os.path.getsize(file) / (1024 * 1024) > size_mb

def deploy_mcu(model_path, deploy_dir, with_ethos, with_ospi, with_ref_data):
    try:
        with mera.Deployer(deploy_dir, overwrite=True) as deployer:
            model = mera.ModelLoader(deployer).from_tflite(model_path)

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

            # On other scripts we could use True and it will not generate
            # x86 related source code (python bindings for example)
            mcu_config['use_x86'] = False

            # generation of reference data from original model format
            # using the original runtime is only supported for TFLite models
            enable_ref_data = with_ref_data and model_path.suffix == '.tflite'

            deployer.deploy(model,
                            mera_platform=platform,
                            target=Target.MCU,
                            vela_config=vela_config,
                            mcu_config=mcu_config,
                            enable_ref_data=enable_ref_data)

    except Exception as e:
        print(str(e))
```

This release provides some models, if the models provided are for example:

```
models_int8/
├── ad_medium_int8.tflite
├── kws_micronet_m.tflite
├── mobilenet_v2_1.0_224_INT8.tflite
├── person-det.tflite
├── rnnoise_INT8.tflite
├── vww4_128_128_INT8.tflite
├── wav2letter_int8.tflite
└── yolo-fastest_192_face_v4.tflite
```

then by running the provided script `scripts/mcu_deploy.py`:

```bash
cd scripts/

# deploy already quantized TFLite models for the MCU target
python mcu_deploy.py --ref_data ../models_int8 deploy_qtzed_ethos

# deploy already quantized TFLite models for the Ethos-U55 target
python mcu_deploy.py --ethos --ref_data ../models_int8 deploy_qtzed_ethos
```

you will get the following results:

```
deploy_qtzed_ethos
├── ad_medium_int8_no_ospi
├── kws_micronet_m_no_ospi
├── mobilenet_v2_1.0_224_INT8_ospi
├── person-det_no_ospi
├── rnnoise_INT8_no_ospi
├── vww4_128_128_INT8_no_ospi
├── wav2letter_int8_ospi
└── yolo-fastest_192_face_v4_no_ospi
```

Each of the directories contain a deployment of the corresponding model for MCU + Ethos-U55 target:

```
├── person-det_no_ospi
│   ├── build
│   │   └── MCU
│   │       ├── compilation
│   │       │   ├── mera.plan
│   │       │   ├── src # compilation results: C source code + C++ testing support code
│   │       │   │   ├── CMakeLists.txt
│   │       │   │   ├── compare.cpp
│   │       │   │   ├── compute_sub_0000.c # CPU subgraph generated C source code
│   │       │   │   ├── compute_sub_0000.h
│   │       │   │   ├── ...
│   │       │   │   ├── ethosu_common.h
│   │       │   │   ├── hal_entry.c          # HAL entry example
│   │       │   │   ├── kernel_library_int.c # kernel library if CPU subgraphs are present
│   │       │   │   ├── ...
│   │       │   │   ├── model.c
│   │       │   │   ├── model.h
│   │       │   │   ├── model_io_data.c
│   │       │   │   ├── model_io_data.h
│   │       │   │   ├── python_bindings.cpp
│   │       │   │   ├── sub_0001_command_stream.c # Ethos-U55 subgraph generated C source code
│   │       │   │   ├── sub_0001_command_stream.h
│   │       │   │   ├── sub_0001_invoke.c
│   │       │   │   ├── sub_0001_invoke.h
│   │       │   │   └── ...
│   │       │   ├── ...
│   │       ├── deploy_cfg.json
│   │       ├── ir_dumps
│   │       │   ├── person-det_can.dot
│   │       │   ├── ...
│   │       ├── person-det_after_canonicalization.dot
│   │       └── person-det_subgraphs.dot
│   ├── logs
│   ├── model
│   │   └── input_desc.json
│   └── project.mdp
```

Please reference to the provided pre-generated e2studio projects to see how the generated C code
under `build/MCU/compilation/src` can be incorporated into a e2studio project.

### Quantize and deploy models with RUHMI 2.3.1 MCUs

If the starting point it is a Float32 precision model it is possible to use the RUHMI Quantizer
to first quantize the model and finally deploy with MCU/Ethos-U55 support.

The following is a sample of how to quantize a model with the RUHMI Quantizer API:

```python
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
    qtzer = mera.Quantizer(deployer,mera_model,quantizer_config=quantizer_config,mera_platform=platform)
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
```

Once quantized, we can deploy the quantized model with minor detail of using `.from_quantized_mera()`:
instead of `.from_tflite()`:

```python
with mera.Deployer(str(deploy_dir), overwrite=True) as deployer:

    mera_model = mera.ModelLoader(deployer).from_quantized_mera(model_path)

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
```

### Full quantization demo

We provide a script that given a model (either with .tflite, .onnx or .pte extension) will:

 * calibrate and quantize the model with random data
 * deploy the model for the MCU C Codegen target and generate C source code
 * compile the auto-generated Python bindings for the C source code
 * execute the C source code through the Python bindings
 * compare the RUHMI Interpreter results and the C source code results

To run this script:

```bash
cd scripts/

# deploy for MCU only
python mcu_quantize.py ../models_fp32 deploy_mcu

# deploy for MCU+Ethos-U55
python mcu_quantize.py -e ../models_fp32_ethos deploy_ethos
```

