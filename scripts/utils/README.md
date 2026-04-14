# Check Model Metrics (`check_model_metrics.py`)

This script analyzes the memory requirements (RAM and Flash) and operations (MACs) for models compiled with the MERA/RUHMI toolchain. It provides a platform-aware analysis for both CPU and NPU targets.

## Usage

```bash
python check_model_metrics.py <path_to_deploy_dir>
```

**Argument:**
`<path_to_deploy_dir>`: The root directory containing the `deploy` folder (or the `deploy` folder itself). The script expects the standard structure: `deploy/build/MCU/...`

## Metrics Explanation

| Metric | Description | Note |
| :--- | :--- | :--- |
| **RAM (Tensor Arena)** | Peak runtime memory usage (activation buffers). | Buffers are reused between subgraphs. Reported size is the **MAX** requirement. |
| **Flash (Parameters)** | Total storage size for weights and biases. | All constants are stored simultaneously (**SUM**). |
| **MAC Operations** | Total Multiply-Accumulate operations. | Proxy for computational complexity. |
| **NPU Acceleration** | Percentage of operations offloaded to NPU. | `(NPU MACs / Total MACs) * 100` |
| **NPU Node Coverage** | Percentage of operators offloaded to NPU. | `(NPU Nodes / Total Nodes) × 100` Includes all node types, even zero-MAC ops like reshape, strided_slice, etc. Can be lower than NPU Acceleration if CPU runs post-processing layers. |


## Example Output

```text
Memory Analysis for: output_test/<model>_NPU

Platform: NPU
RAM (Tensor Arena)   :      258,048 bytes  (0.25 MB)
Flash (Parameters)   :    1,651,952 bytes  (1.58 MB)
MAC Operations       :  192,854,016 ops    (192.85 M)
NPU Acceleration     :        100.0%      (192,854,016 / 192,854,016 ops)
NPU Node Coverage    :       100.0%      (36 / 36 nodes, 0 CPU fallback)
```
> **Note:** In same cases the NPU % may not be accurate, refer to the Vela output during `mcu_compily.py` script usage.
