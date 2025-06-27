## If you see some warning at running the sample scripts, you can refer the tips below depending on the message in display.
**[Linux]   For Linux version**  
**[Winows]  For Windows version**  


### **[Linux]** `GLIBCXX_3.4.32' not found` occered at running the script like "python mcu_deploy.py --ethos --ref_data ../models_int8 deploy_qtzed_ethos"

Basically, just do the following commands: Firstly, install:
```
sudo apt-get install libstdc++6
```

This should already be installed by default, but try it anyway. If it doesn't solve it, just do the following:
```
sudo add-apt-repository ppa:ubuntu-toolchain-r/test 
sudo apt-get update
sudo apt-get upgrade
sudo apt-get dist-upgrade
```

### **[Linux]** .tflite,model_000_ad01_fp32,Error,Command '['cmake', '-DBUILD_PY_BINDINGS=ON', '..']' returned non-zero exit status 1.

This issue comes from the version of cmake.
Please follow the next topic.

### **[Linux]** CMake Error at CMakeLists.txt:1 (cmake_minimum_required):
  CMake 3.24 or higher is required.  You are running version 3.22.1
  In order to install any higher version, you can refer to below steps.

```
$ cmake --version  # Confirm the current version
$ wget -O - https://apt.kitware.com/keys/kitware-archive-latest.asc 2>/dev/null | gpg --dearmor - | sudo tee /etc/apt/trusted.gpg.d/kitware.gpg >/dev/null
$ sudo apt-add-repository "deb https://apt.kitware.com/ubuntu/ $(lsb_release -cs) main"
$ sudo apt update
$ sudo apt install cmake
$ cmake --version   # Check the updated version, to be revised.
```


