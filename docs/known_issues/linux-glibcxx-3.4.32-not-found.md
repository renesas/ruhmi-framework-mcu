# [Linux] GLIBCXX_3.4.32 not found

## Symptom

Running host-evaluation flows can fail with an error similar to:

`GLIBCXX_3.4.32 not found`

## Root Cause

The system GNU C++ runtime (`libstdc++`) is older than the version expected by the generated binaries or toolchain dependencies.

## Resolution

Update `libstdc++` and `libgcc` packages:

```bash
sudo add-apt-repository ppa:ubuntu-toolchain-r/test
sudo apt-get update
sudo apt-get install libstdc++6 libgcc-s1
```

Optional cleanup/upgrade after installation:

```bash
sudo apt-get upgrade
sudo apt-get dist-upgrade
```

## Verification

Re-run your compile/host-evaluate command and confirm the GLIBCXX error no longer appears.
