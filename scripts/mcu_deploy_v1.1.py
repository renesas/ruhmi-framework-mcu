import os
import mera

from mera import Platform, Target
from argparse import ArgumentParser
from pathlib import Path
import sys


def needs_ospi(file, size_mb):
    return os.path.getsize(file) / (1024 * 1024) > size_mb

def deploy_mcu(model_path, deploy_dir, with_ethos, with_ospi, with_ref_data):

    try:
        with mera.Deployer(deploy_dir, overwrite=True) as deployer:
            model = mera.ModelLoader(deployer).from_tflite(model_path)

            platform = Platform.MCU_ETHOS if with_ethos else Platform.MCU_CPU

            # ARM Vela options
            # only effective if Platform.MCU_ETHOS is selected, ignored otherwise
            vela_config = {}
            vela_config['enable_ospi'] = with_ospi
            vela_config['sys_config'] = 'RA8P1'
            vela_config['memory_mode'] = 'Sram_Only'
            vela_config['accel_config'] = 'ethos-u55-256'
            vela_config['optimise'] = 'Performance'
            vela_config['verbose_all'] = False

            # MCU C code generation options
            mcu_config = {}
            mcu_config['suffix'] = '_net1'
            mcu_config['weight_location'] = 'flash' # other option is: 'iram'

            # On other scripts we could use True and it will not generate
            # x86 related source code (python bindings for example)
            mcu_config['use_x86'] = False

            # generation of reference data from original model format
            # using the original runtime is only supported for TFLite models
            enable_ref_data = with_ref_data and model_path.suffix == '.tflite'

            deployer.deploy(model,
                            mera_platform=platform,
                            target=Target.MCU,
                            vela_config=vela_config,
                            mcu_config=mcu_config,
                            enable_ref_data=enable_ref_data)

    except Exception as e:
        print(str(e))

UNSUPPORTED_EXTS = {".onnx", ".pte"}
EXIT_UNAVAILABLE = getattr(os, "EX_UNAVAILABLE", 69)  # portable fallback


def exit_unavailable(msg: str, code: int = EXIT_UNAVAILABLE):

    red, reset = "\033[1;31m", "\033[0m"
    label = f"{red}UNAVAILABLE{reset}" if sys.stderr.isatty() else "UNAVAILABLE"
    print(f"\n{label}: {msg}\n", file=sys.stderr)
    sys.exit(code)

def abort_if_unsupported_present(models_dir: Path):

    bad = sorted(p for p in models_dir.rglob("*")
                 if p.is_file() and p.suffix.lower() in UNSUPPORTED_EXTS)
    if bad:
        print("Found unsupported model files:", file=sys.stderr)
        for p in bad:
            print(f"  - {p}", file=sys.stderr)
        exit_unavailable(
            "Feature not available yet. Direct deployment supports only FP32/INT8 .tflite.\n"
            "For .onnx or .pte, quantize with mcu_quantize.py first."
        )

def main():
   # Abort early if any .onnx or .pte are present

  arg_p = ArgumentParser('mcu_run')
  arg_p.add_argument('models_dir', type=str, help='Path to directory with TFLite models')
  arg_p.add_argument('deploy_dir', type=str, help='Directory for CCodegen deployment')
  arg_p.add_argument('--ethos', action='store_true', help='Enable Ethos codegen')
  arg_p.add_argument('--ospi', action='store_true', help='Use SPI memory')
  arg_p.add_argument('--ref_data', action='store_true', help='Generate reference data for testing')
  args = arg_p.parse_args()
  models_dir = Path(args.models_dir).resolve()
  deploy_dir = Path(args.deploy_dir).resolve()
  abort_if_unsupported_present(models_dir)

  models = models_dir.rglob("*.tflite")

  for model in models:
      deploy_name = model.stem
      enable_ospi = args.ospi or needs_ospi(model, 1.5)
      out_dir = deploy_dir / (deploy_name + ("_ospi" if enable_ospi else "_no_ospi"))
      print(f"Compiling {deploy_name}...", flush=True)
      deploy_mcu(model, out_dir, args.ethos, enable_ospi, args.ref_data)

if __name__ == '__main__':
  main()
