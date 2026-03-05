# Tutorials

Hands-on tutorials for the RUHMI Framework AI Compiler for MCU.

## Available Tutorials

| Tutorial | Description | Difficulty |
|----------|-------------|------------|
| [CIFAR-10 Quantization Workflow](Quantization_Workflow_CIFAR10/CIFAR10_RUHMI_Tutorial.ipynb) | End-to-end workflow: train a CNN, quantize with MERA & Tflite, deploy to C-code, and validate accuracy across FP32 & INT8 variants for Tflite and Mera | Beginner |

## Prerequisites

All tutorials run as Jupyter Notebooks and require a **MERA virtual environment**.  
If you don't have one set up yet, follow the [Installation Guide](../../install/README.md) first.

### Additional Tutorial Dependencies

Tutorials may require extra Python packages beyond the base MERA installation.  
Install them inside your activated `mera-env`:

```bash
source mera-env/bin/activate
pip install ipykernel scipy scikit-learn tensorflow matplotlib seaborn
```

### Jupyter Kernel Setup

Register your MERA environment as a Jupyter kernel:

```bash
python -m ipykernel install --user --name=mera-env --display-name "Python (MERA Env)"
jupyter notebook
```

> [!IMPORTANT]
> In the Jupyter interface, select **Kernel → Change Kernel → Python (MERA Env)** to ensure the notebook uses the correct environment.


