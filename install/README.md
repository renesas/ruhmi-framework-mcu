
# Installation

RUHMI Framework[^1] AI MCU compiler includes MERA IPs supported by EdgeCortix, so you will see files and descriptions with the name MERA included.
The version number in the file name (e.g., 2.5.0) corresponds to the MERA IP version.

Select your installation guide:
- [Installation guide for Ubuntu Linux](#installation---ubuntu-linux)
- [Installation guide for Windows](#installation---windows)

## Installation - Ubuntu Linux

In order to install RUHMI on a supported environment, you will need:

- A machine with Ubuntu 22.04 (recommended, as this was the version used for testing)
- A working installation of PyEnv or other Python virtual environment management system that provides Python version 3.10.x

**Prepare the environment**  
System dependencies necessary to create environments and run demos:  

```
sudo apt update; sudo apt install build-essential cmake python3-venv python3-pip
```

**Recommended: use the default Python installation**  
Because MERA software stack is compatible by default with the base system Python version provided by Ubuntu 22.04
we can create a virtual environment as follows:

```
sudo add-apt-repository -yu ppa:ubuntu-toolchain-r/test
sudo add-apt-repository ppa:deadsnakes/ppa
sudo apt update && sudo apt upgrade
sudo apt-get install -q -y --only-upgrade libstdc++6 libgcc-s1
sudo apt update && sudo apt upgrade
sudo apt install -y build-essential gcc-13 g++-13
sudo apt-get install python3.10 python3.10-venv python3.10-dev python3-pip
python3.10 -m venv mera-env
source mera-env/bin/activate
pip install --upgrade pip && pip install decorator typing_extensions psutil attrs pybind11 cmake junitparser
```

Your prompt should now show that you are under a virtual environment mera-env:
(mera-env) user@compute:~$

> **Note:** Alternative such as Pyenvs can also be used.

**Install MERA**

Download and install MERA on the virtual environment:

```bash
# Download the wheel file
wget https://github.com/renesas/ruhmi-framework-mcu/raw/main/install/mera-2.5.0+pkg.3577-cp310-cp310-manylinux_2_27_x86_64.whl

# Install MERA
pip install ./mera-2.5.0+pkg.3577-cp310-cp310-manylinux_2_27_x86_64.whl
```

> [**TIP**]
> The version number may vary depending on the MERA release. Check the [install directory](https://github.com/renesas/ruhmi-framework-mcu/tree/main/install) for the latest version.

At this point MERA should be ready to use. You can confirm with:

```
python -c "import mera;print(dir(mera))"  
```

## Installation - Windows

The software stack is also provided as PIP package compatible with Windows 11 or 10.  
The only requirement needed on Windows are C++ runtime libraries.   
Please download and install [this package](https://aka.ms/vs/17/release/vc_redist.x64.exe)   

Install Python3.10 from [Python3.10](https://www.python.org/downloads/release/python-3105/)  

Open **PowerShell** from the windows start menu.
Create and move to the working folder. Assuming C:\work is the current folder in the following process.   
```
PS <current directory>> cd C:\work   
```

**Prepare the virtual environment**

Build the virtual environment for Python
```
py -3.10 -m venv .venv  
```

Activate the virtual environment as follows.
Before activating the virtual environment, you may need to change the execution policy for shell execution.
```
[Environment]::SetEnvironmentVariable('CONVERSION_TOOL_E2STUDIO_PLUGIN_PYTHON_VENV_LOC', "$(Get-Location)", 'User') 
Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope Process  
.venv\Scripts\Activate.ps1  
```
You will see the prompt as "(.venv) PS C:\work>"

**Install MERA into Windows**

Download and install RUHMI AI Compiler into the virtual environment:

```powershell
# Download the wheel file
Invoke-WebRequest -Uri "https://github.com/renesas/ruhmi-framework-mcu/raw/main/install/mera-2.5.0+pkg.3577-cp310-cp310-win_amd64.whl" -OutFile "mera-2.5.0+pkg.3577-cp310-cp310-win_amd64.whl"

# Install MERA and dependencies
python -m pip install .\mera-2.5.0+pkg.3577-cp310-cp310-win_amd64.whl
python -m pip install onnx==1.17.0 tflite==2.18.0
```

> [TIP]
> The version number may vary depending on the MERA release. Check the [install directory](https://github.com/renesas/ruhmi-framework-mcu/tree/main/install) for the latest version.

Please check that all your path settings of your environment are correct. After installation you should be able to
successfully complete the following commands.
```
python -c "import mera; print(mera.__version__)"  
2.5.0+pkg.3019

vela --version
4.2.0

python -c "import mera;print(dir(mera))"
['Deployer', 'InputDescription', 'InputDescriptionContainer', 'Layout', 'MERADeployer', 'MeraModel', 'MeraTvmDeployment', 'MeraTvmModelRunner', 'MeraTvmPrjDeployment', 'ModelLoader', 'ModelQuantizer', 'Platform', 'PowerMetrics', 'QuantizationQualityMetrics', 'Quantizer', 'TVMDeployer', 'Target', '__builtins__', '__cached__', '__doc__', '__file__', '__loader__', '__name__', '__package__', '__path__', '__spec__', '__version__', 'calculate_quantization_quality', 'deploy', 'deploy_project', 'get_mera_dna_version', 'get_mera_tvm_version', 'get_mera_version', 'get_versions', 'load_mera_deployment', 'mera_deployment', 'mera_model', 'mera_platform', 'mera_quantizer', 'metrics', 'model', 'quantization_quality', 'quantizer', 'version']  
```

## MERA Visualizer

The framework includes a visualizer tool (MERA Visualizer) with an interactive web interface for visualizing device compatibility (model partitioning) and performance metrics.

**Installation**

Ensure your MERA virtual environment is activated, then install the visualizer wheel found in the install directory:

```bash
# Linux
pip install mera_visualizer-2.5.0-py3-none-any.whl

# Windows
python -m pip install .\mera_visualizer-2.5.0-py3-none-any.whl
```

**Usage**

Start the visualizer web server:

```bash
mera_visualizer
```

This will start a local server (default: http://127.0.0.1:5000).

📖 For detailed usage instructions and features, see the [Visualizer Guide](../docs/visualizer/README.md).

[^1]: RUHMI Framework AI MCU Compiler is powered by EdgeCortix® MERA™.
