# Windows Setup Guide: MinGW Clang + CMake for MERA Host Evaluation

In `mcu_compile.py` scripts, there is an option to test the generated C-code on the host. We are providing this simple guide based on internal experience setting up the required software on Windows 11. This is just a reference; there are multiple ways to set up CMake to enable on-host evaluation.

## 1. Install MSYS2

Download and install from https://www.msys2.org/ (Use the default installation path: `C:\msys64`).

## 2. Install MinGW Clang + Make

Open the **MSYS2 UCRT64** terminal (not the regular MSYS2 terminal) and run:

```bash
pacman -S mingw-w64-ucrt-x86_64-clang mingw-w64-ucrt-x86_64-make
```

> **Note:** You may see SSL certificate errors from `mirror.msys2.org` — these can be ignored as long as the packages still install successfully (check for the `installing ...` lines at the end).

## 3. Add MinGW to Windows PATH

You must add the MinGW binary folder to your system PATH.
**Important:** The `mcu_compile.py` script specifically looks for `C:\msys64\ucrt64\bin` to load required Python extension DLLs, so ensure you use this path.

**Option A (PowerShell):**
```powershell
[Environment]::SetEnvironmentVariable("Path", $env:Path + ";C:\msys64\ucrt64\bin", "User")
```

**Option B (GUI):**
Press `Win`, type "Environment Variables", click "Edit the system environment variables" > "Environment Variables" > Select `Path` > Edit > New > Add `C:\msys64\ucrt64\bin`.

## 4. Add CMake to Windows PATH

CMake may already be installed (e.g., via Visual Studio) but **not on PATH**. Check with:

```powershell
& "C:\Program Files\CMake\bin\cmake.exe" --version
```

If it exists but `cmake --version` doesn't work, add it to your PATH:

```powershell
[Environment]::SetEnvironmentVariable("Path", $env:Path + ";C:\Program Files\CMake\bin", "User")
```

If CMake is not installed at all, open PowerShell and run:

```powershell
winget install Kitware.CMake
```

## 5. Restart your terminal

**Close and reopen** your PowerShell or VS Code terminal so the new PATH takes effect.

## 6. Verify everything works

```powershell
clang++.exe --version
mingw32-make.exe --version
cmake --version
```

All three should return version info. *(Note: The MSYS2 `make` package provides the `mingw32-make.exe` executable, which CMake expects on Windows).*

## 7. Virtual environment note

If using a Python venv, reactivate it after restarting the terminal:

```powershell
.\.venv\Scripts\Activate.ps1
```

If you get a script execution error, run this once (permanently):

```powershell
Set-ExecutionPolicy -Scope CurrentUser -ExecutionPolicy RemoteSigned
```

---

## Troubleshooting

| Issue | Solution |
|-------|----------|
| `running scripts is disabled` when activating venv | Run `Set-ExecutionPolicy -Scope CurrentUser -ExecutionPolicy RemoteSigned` (one-time) |
| `No compatible C++ compiler found` | Install `mingw-w64-ucrt-x86_64-clang` via MSYS2 and add `C:\msys64\ucrt64\bin` to PATH |
| `CMAKE_MAKE_PROGRAM is not set` | Install `mingw-w64-ucrt-x86_64-make` via MSYS2 (same bin directory) |
| `cmake not found` / cmake silently skipped | Add `C:\Program Files\CMake\bin` to PATH |
| PATH changes not taking effect | **Restart the terminal** — `[Environment]::SetEnvironmentVariable` only affects new sessions |
| SSL errors during `pacman` install | Can be ignored if packages still install (corporate proxy/firewall issue) |
| `DLL load failed while importing py_compute` | Ensure MinGW is installed at `C:\msys64` so Python can locate the UCRT runtimes. |
