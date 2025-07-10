
# Installation  

In order to install the software tool, the installation file below shall be used. 
RUHMI framework[^1] includes MERA IPs supported by EdgeCortix, so you will see the files and some discriptions with the name of MERA included.
Also, the version number included in the file name like 2.3.2 depens on MERA IP.  
Download the installation files from the repository, then move on to the installation guide according to your system type;
[Installation guide for Ubuntu Linux](#installation---Ubuntu-Linux), [Installation guide for Windows](#installation---Windows)
```
\install\mera-2.4.0+pkg.1756-cp310-cp310-manylinux_2_27_x86_64.whl  
\install\mera-2.4.0+pkg.179-cp310-cp310-win_amd64.whl  
```

# Installation - Ubuntu Linux  
In order to install RUHMI on supported environment, you will need:
* A machine with Ubuntu 22.04 installation is recommended as this was the version used for testing.
* A working installation of PyEnv or other Python virtual environment management system that provides Python
version 3.10.x.

**Prepare the environment**  
System dependencies necessary to create environments and run demos:  

```
sudo apt update; sudo apt install build-essential cmake python3-venv python3-pip
```

**Recommended: use the default Python installation**  
Because MERA software stack is compatible by default with the base system Python version provided by Ubuntu 22.04
we can create a virtual environment as follows:

```
python3 -m venv mera-env
source mera-env/bin/activate
pip install --upgrade pip && pip install decorator typing_extensions psutil attrs pybind11
```

Your prompt should now show that you are under a virtual environment mera-env:
(mera-env) user@compute:~$

**Alternative: PyEnv installation**  
If PyEnv is preffered over the base system Python installation you can get started with:

```
# pyenv dependencies
sudo apt update; sudo apt install build-essential libssl-dev zlib1g-dev \  
libbz2-dev libreadline-dev libsqlite3-dev curl git cmake \  
libncursesw5-dev xz-utils tk-dev libxml2-dev libxmlsec1-dev libffi-dev liblzma-dev  
# actual installation of PyEnv  
curl https://pyenv.run | bash  
```

The installation of PyEnv recommends to do some post-installation steps that involve to modify your .bashrc file in
order to easily create virtual environments:

```
echo 'export PYENV_ROOT="$HOME/.pyenv"' >> ~/.bashrc  
echo '[[ -d $PYENV_ROOT/bin ]] && export PATH="$PYENV_ROOT/bin:$PATH"' >> ~/.bashrc  
echo 'eval "$(pyenv init - bash)"' >> ~/.bashrc  
```

To create a Python Virtual Environment for MERA named “mera-env” using PyEnv:  

```
MENV=mera-env; pyenv install 3.10.15 && pyenv virtualenv 3.10.15 $MENV && pyenv activate $MENV && \  
pip install --upgrade pip && \  
pip install decorator typing_extensions psutil attrs pybind11  
```

Your prompt should now show that you are under a virtual environment mera-env:  
(mera-env) user@compute:~$  

**Install MERA**  
Finally install MERA on the virtual environment mera-env:  

```
pip install ./mera-2.4.0+pkg.1756-cp310-cp310-manylinux_2_27_x86_64.whl  
```

where the versions may vary depending on the MERA release used.  
At this point MERA should be ready to use. You can confirm with the following example:  

```
python -c "import mera;print(dir(mera))"  
```

# Installation - Windows  

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
Biuild the vertual environment for Python  
```
PS C:\work> py -3.10 -m venv .venv  
```

Activate the vurtual environment as following   
Before activating the vertual environment, you may need to change the execution policy for shell execution.  
```
PS C:\work> Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope Process  
PS C:\work> .venv\Scripts\Activate.ps1  
```
**Install MERA into Windows**  
Copy the install directory including the installation file into the current folder.  
The file name may vary depending on the release version.

Install RUHMI AI Compiler into the virtual environment.
Also, install required dependencies.
```
(.venv) PS C:\work> cd install
(.venv) PS C:\work\install> python -m pip install .\mera-2.4.0+pkg.179-cp310-cp310-win_amd64.whl   
(.venv) PS C:\work\install> python -m pip install onnx==1.17.0 tflite==2.18.0
```

Please check that all your path settings of your environment are correct. After installation you should be able to
successfully complete the following commands.
```
(.venv) PS C:\work\install> vela --version
4.2.0
(.venv) PS C:\work\install> python -c "import mera;print(dir(mera))"
['Deployer', 'InputDescription', 'InputDescriptionContainer', 'Layout', 'MERADeployer', 'MeraModel', 'MeraTvmDeployment', 'MeraTvmModelRunner', 'MeraTvmPrjDeployment', 'ModelLoader', 'ModelQuantizer', 'Platform', 'PowerMetrics', 'QuantizationQualityMetrics', 'Quantizer', 'TVMDeployer', 'Target', '__builtins__', '__cached__', '__doc__', '__file__', '__loader__', '__name__', '__package__', '__path__', '__spec__', '__version__', 'calculate_quantization_quality', 'deploy', 'deploy_project', 'get_mera_dna_version', 'get_mera_tvm_version', 'get_mera_version', 'get_versions', 'load_mera_deployment', 'mera_deployment', 'mera_model', 'mera_platform', 'mera_quantizer', 'metrics', 'model', 'quantization_quality', 'quantizer', 'version']  
```

[^1]: RUHMI Framework is powered by EdgeCortix® MERA™.
