# [Linux] CMake 3.24 or higher is required

## Symptom

Model compilation with host-evaluation can fail with one of these messages:

- `Command '['cmake', '-DBUILD_PY_BINDINGS=ON', '..']' returned non-zero exit status 1`
- `CMake 3.24 or higher is required. You are running version 3.22.1`

## Root Cause

The host environment CMake version is below the minimum required by generated build scripts.

## Resolution

Install a newer CMake release (Kitware APT repository):

```bash
cmake --version
wget -O - https://apt.kitware.com/keys/kitware-archive-latest.asc 2>/dev/null | gpg --dearmor - | sudo tee /etc/apt/trusted.gpg.d/kitware.gpg >/dev/null
sudo apt-add-repository "deb https://apt.kitware.com/ubuntu/ $(lsb_release -cs) main"
sudo apt update
sudo apt install cmake
cmake --version
```

## Verification

`cmake --version` should report 3.24+.

Then rerun the compilation command that previously failed.
