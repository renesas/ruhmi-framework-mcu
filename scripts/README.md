# RUHMI Framework AI MCU Compiler Scripts

This directory contains scripts for compiling and deploying AI models to Renesas RA8xx Microcontrollers (MCU) and Ethos-U NPUs.

## MCU Model Compiler

`mcu_compile.py` is the unified script for compiling and deploying AI models. It handles the whole pipeline: quantization (FP32 -> INT8), C-code generation (MERA/CMSIS-NN/Vela), and optional host-based validation.

### Key Features

1.  **Unified Workflow**: Supports TFLite, ONNX, and PyTorch (Executorch) models.
2.  **Quantization**: Quantizes FP32 models to INT8 using calibration data with --quantize argument.
3.  **NPU Support**: Partitions the graph and compiles ARM Ethos-U55 subgraphs using Vela compiler.
4.  **External Memory**:
    *   **NPU**: `--external` enables Vela's `enable_ospi` flag for OSPI memory placement.
    *   **CPU**: `--external` adds `_external` suffix to the output directory.
    *   **Auto-Detection**: Models larger than `--memory-threshold` auto-trigger external memory mode.
5.  **Host Testing**: `--x86` generates pybind11 bindings for PC testing. `--host-evaluate` runs automated validation.

### Suported conversion options  
![](../docs/assets/conversion_options.gif)


### Usage

```bash
python mcu_compile.py <model_path> <output_dir> [options]
```

#### Positional Arguments

| Argument | Description |
| :--- | :--- |
| `model_path` | Path to the model file (.tflite, .onnx, .pte) or directory with multiple models to evaluate. |
| `output_dir` | Directory where the generated artifacts will be saved. |

#### Full Argument List

| Argument | Default | Description |
| :--- | :--- | :--- |
| **Target** | | |
| `--npu` | `False` | Compile for Ethos-U55 NPU (Requires INT8 model). |
| `--cpu` | `False` | Compile for Cortex-M CPU (CMSIS-NN). |
| **Precision** | | |
| `--quantize` | `False` | Enable quantization (FP32 -> INT8). |
| `--calib-data` | `None` | Path to calibration data (.npy) for quantization. Random data used if not provided. |
| `--calib-num` | `5` | Number of random calibration samples to generate if no data provided. |
| **Memory & Optimization** | | |
| `--external` | `False` | Force external memory mode. NPU: enables Vela OSPI. CPU: directory naming only. Auto-enabled for large models. |
| `--memory-threshold` | `0.8` | Size threshold (MB) to auto-detect large models requiring external memory. |
| `--memory-mode` | `Sram_Only` | (NPU only) Vela memory mode. Choices: `Sram_Only`, `Shared_Sram`.Choose `Shared_Sram` when the tensor arena access is faster than weights access (e.g., internal SRAM for the arena, external memory for weights).|
| `--optimization` | `Performance` | (NPU only) Vela optimization target. Choices: `Performance`, `Size`. |
| `--weight-loc` | `Flash` | Weight storage location. Choices: `Flash`, `Iram`. |
| **Output & Naming** | | |
| `--suffix` | `""` | Suffix to append to generating C function names (useful for multiple models). |
| `--result` | `""` | Path to write JUnit XML test results. |
| **Host Testing** | | |
| `--x86` | `False` | Generate x86 pybind11 bindings for manual host testing. |
| `--host-evaluate` | `False` | Build and run on PC to validate accuracy (CPU only, implies --x86). |
| `--ref-data` | `False` | Generate reference input/output data (.npy) for testing on target. |
| **Advanced** | | |
| `--onnx-dims` | `""` | Freeze dynamic ONNX dimensions (e.g., `batch=1,width=224`). |


**Naming Convention:** `{model_name}_{TARGET}[_external][_quantized]`

*   **{model_name}**: Derived from the input file (without extension). Spaces in the filename are replaced with underscores (e.g. `my model.tflite` → `my_model_CPU`).
*   **{TARGET}**: `CPU` or `NPU`.
*   **_external**: Appended if model needs external memory (auto-detected or via `--external`).
*   **_quantized**: Appended if `--quantize` is used.


#### Deployment examples

**For NPU Deployment (Standard):**
```bash
python mcu_compile.py my_model.tflite output/ --npu --quantize
```

**For CPU Deployment (Standard):**
```bash
python mcu_compile.py my_model.tflite output/ --cpu --quantize 
```

**For Large Models (External Memory):**
```bash
python mcu_compile.py my_large_model.tflite output/ --npu --quantize --external
```

**Deploy + Generate x86 bindings for manual testing:**
```bash
python mcu_compile.py my_model.tflite output/ --cpu --x86
```

### Generated Artifact View

The generated output directory contains the generated C code and various artifacts. Here is an example structure for a NPU deployment:

```text
ad_large_int8_npu
└── deploy
    ├── build
    │   └── MCU
    │       ├── ad_large_int8_after_canonicalization.dot
    │       ├── ad_large_int8_subgraphs.dot
    │       ├── compilation
    │       │   ├── mera.plan
    │       │   ├── src  --> **Where the source code lives**
    │       │   │   ├── ethosu_common.h
    │       │   │   ├── hal_entry.c
    │       │   │   ├── model.c
    │       │   │   ├── model.h
    │       │   │   ├── sub_0000_command_stream.c
    │       │   │   ├── sub_0000_command_stream.h
    │       │   │   ├── sub_0000_invoke.c
    │       │   │   ├── sub_0000_invoke.h
    │       │   │   ├── sub_0000_model_data.c
    │       │   │   ├── sub_0000_model_data.h
    │       │   │   ├── sub_0000_tensors.c
    │       │   │   ├── sub_0000_tensors.h
    │       │   │   └── sub_0000__ARM_ETHOS_U55_C_CODEGEN    
    │       ├── constants
    │       ├── deploy_cfg.json
    │       ├── io_desc.json
    │       ├── ir_dumps
    │       └── model_subgraphs.json --> **JSON file for mera_visualizer**
    ├── logs
    ├── model
```

The generated C code under **"build/MCU/compilation/src"** can be incorporated into an e2 studio project.  
You can refer to [Guide to the generated C source code](/docs/runtime_api.md) to study how to use the output file from AI MCU compiler.  


### Helper Utilities

#### Model Metrics Analysis (`scripts/utils/check_model_metrics.py`)

A helper script is provided to analyze memory usage (RAM/Flash) and operation counts (MACs) of compiled models.

```bash
python scripts/utils/check_model_metrics.py <path_to_deploy_dir>
```

See [scripts/utils/README.md](utils/README.md) for more details.


### How to Handle Multiple Models

When porting multiple models into a single application, you must convert each model individually. To avoid naming conflicts in the generated C code, you should assign a unique suffix to each model's output functions using the `--suffix` option.

**Example:**

```bash
# Deploy Model A (CPU only) with suffix "_func1"
python mcu_compile.py model_a.tflite deploy_output/ --cpu --quantize --suffix _func1

# Deploy Model B (NPU enabled) with suffix "_func2"
python mcu_compile.py model_b.tflite deploy_output/ --npu --quantize --suffix _func2
```

This ensures that the generated functions (e.g., `compute_sub_0000_func1`, `compute_sub_0000_func2`) have unique names and can coexist in the same project.

