# RUHMI Framework AI MCU Compiler

**Robust Unified Heterogeneous Model Integration** - A framework for AI model optimization and deployment, this GitHub provides the AI MCU Compiler for Renesas embedded platforms powered by EdgeCortix® MERA™.

[![License](https://img.shields.io/badge/License-See%20LICENSE.md-blue.svg)](LICENSE.md)
[![Platform](https://img.shields.io/badge/Platform-Linux%20%7C%20Windows-lightgrey.svg)]()
[![Python](https://img.shields.io/badge/Python-3.10-green.svg)]()

## Table of Contents

- [Introduction](#introduction)
- [Quick Start](#quick-start)
- [Workflow](#ruhmi-framework-workflow)
- [Supported Platforms](#supported-embedded-platforms)
- [Installation](#installation---ubuntu-linux)
- [Model Compilation](#model-compilation)
- [Generated C Source Code](#guide-to-the-generated-c-source-code)
- [API Documentation](#ai-model-compiler-api-specification)
- [Support](#support)

## Introduction

RUHMI Framework[^1] provides a compiler and the necessary tools to convert machine learning models into C source code compatible with a range of Renesas MCUs powered by Arm Ethos-U NPUs.
The software stack generates C source code while ensuring compatibility and tight integration with Renesas e2 studio.
It also ships with Mera Quantizer, a post-training static INT8 quantizer, allowing more demanding models to meet the memory and latency constraints typical of microcontrollers and Ethos-U accelerators.

[^1]: RUHMI Framework's AI MCU Compiler is powered by EdgeCortix® MERA™.

## RUHMI Framework Workflow
![](docs/material/workflow_ruhmi.GIF)


## Quick Start

Get up and running in 5 steps (Ubuntu Linux / WSL):

```bash
# 1. Clone the repository
git clone https://github.com/renesas/ruhmi-framework-mcu.git
cd ruhmi-framework-mcu

# 2. Create and activate virtual environment
python3.10 -m venv mera-env
source mera-env/bin/activate

# 3. Install dependencies and MERA
pip install --upgrade pip
pip install decorator typing_extensions psutil attrs pybind11 cmake junitparser
pip install ./install/mera-2.5.0+pkg.3019-cp310-cp310-manylinux_2_27_x86_64.whl

# 4. Download a sample model
wget https://raw.githubusercontent.com/mlcommons/tiny/master/benchmark/training/anomaly_detection/trained_models/ad01_int8.tflite
mkdir -p models_int8 && mv ad01_int8.tflite models_int8/

# 5. Deploy the model to C code
cd scripts
python mcu_deploy.py --ethos --ref_data ../models_int8 ../deploy_output
```

Your compiled C source code will be in `deploy_output/ad01_int8_no_ospi/build/MCU/compilation/src/`.

📖 For detailed installation instructions, see the [Installation Guide](install/README.md).


## Supported Embedded Platforms

- Renesas MCU RA8P1 series
- Renesas MCU RA8xx series (non-NPU devices)

## Supported Operating Systems

RUHMI supports two operating systems. This section outlines the prerequisites. For detailed installation instructions, refer to the [Installation Guide](/install/README.md).

## Installation - Ubuntu Linux

In order to install RUHMI Framework on a supported environment you will need:

- A machine with Ubuntu 22.04 (recommended, as this was the version used for testing)
- A working installation of PyEnv or other Python virtual environment management system that provides Python version 3.10.x

## Installation - Windows

The software stack is also provided as a PIP package compatible with Windows 11.
In order to install RUHMI Framework on a supported environment you will need:

- A machine with Windows 10 or 11 (Windows 11 is recommended, as this was the version used for testing)
- A working installation of PyEnv or other Python virtual environment management system that provides Python version 3.10.x
- Microsoft C++ runtime libraries

## Model Compilation

Sample scripts are provided for common use cases:

**Deploy models:**
- Deploy to CPU only
- Deploy to CPU with Ethos-U55 support

**Quantize and deploy models:**
- Deploy to CPU only
- Deploy to CPU with Ethos-U55 support

📖 [Detailed guide on executing model compilation with sample scripts](scripts/README.md)

## Guide to the Generated C Source Code

After processing a model, you will find several files in your deployment directory. This includes some deployment artifacts generated during compilation that are worth keeping for debugging purposes.

The most important output is found under the directory `<deployment_directory>/build/MCU/compilation/src`.
This directory contains the model converted into a set of C99 source code files.

📖 [Guide to the generated C source code](docs/runtime_api.md)

## AI Model Compiler API Specification

You may want to use customized methods to quantize and optimize your model with your expertise. For your needs, you can refer to the API specification for the model compiler.

📖 [AI model compiler API](https://renesas.github.io/ruhmi-framework-mcu/mera_api.html)

## Support

### Operator Support

Please refer to the [Operator Support](/docs/operator_support.md) documentation to understand what operators are supported by the framework.

### Tips

If you see any warnings during installation or while running the sample scripts, refer to [Tips](./docs/tips.md).


### Error List

If an error occurs during compile/runtime operation, please refer to the [Error List](./docs/error_list.md).

### Inquiries

If you have any questions, please contact [Renesas Technical Support](https://www.renesas.com/support).
You can also open an [issue](https://github.com/renesas/ruhmi-framework-mcu/issues) on GitHub.


