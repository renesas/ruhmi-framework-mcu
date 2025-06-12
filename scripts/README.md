# How to deploy models  
The following code shows how to use the deployment API to compile an already quantized TFLite model on a board with Ethos-U55 support:

```
import os
import mera
from mera import Platform, Target
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
vela_config['enable_ospi'] = needs_ospi(model_path, 1.5)
vela_config['sys_config'] = 'RA8P1'
vela_config['memory_mode'] = 'Sram_Only'
vela_config['accel_config'] = 'ethos-u55-256'
vela_config['optimise'] = 'Performance'
vela_config['verbose_all'] = False
# MCU C code generation options
mcu_config = {}
mcu_config['suffix'] = ''
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
```

This release provides some tested models, if the models provided are for example:

models_int8/
  ad_medium_int8.tflite
  kws_micronet_m.tflite
  mobilenet_v2_1.0_224_INT8.tflite
  person-det.tflite
  rnnoise_INT8.tflite
  vww4_128_128_INT8.tflite
  wav2letter_int8.tflite
  yolo-fastest_192_face_v4.tflite

then by running the provided script scripts/mcu_deploy.py we can compile the model for MCU only:

```
cd scripts/
python mcu_deploy.py --ref_data ../models_int8 deploy_qtzed
```

you will get the following results:

deploy_qtzed
  ad_medium_int8_no_ospi
  kws_micronet_m_no_ospi
  mobilenet_v2_1.0_224_INT8_ospi
  person-det_no_ospi
  rnnoise_INT8_no_ospi
  vww4_128_128_INT8_no_ospi
  wav2letter_int8_ospi
  yolo-fastest_192_face_v4_no_ospi

same but enabling Ethos-U support:

```
cd scripts/
python mcu_deploy.py --ethos --ref_data ../models_int8 deploy_qtzed_ethos

When Ethos-U support is enabled, each of the directories contain a deployment of the corresponding model for MCU + Ethos-U55 target:

```
person-det_no_ospi
  build
  MCU
  compilation
  mera.plan
  src # compilation results: C source code and C++ testing support code
  CMakeLists.txt
  compare.cpp
compute_sub_0000.c # CPU subgraph generated C source code
compute_sub_0000.h
...
ethosu_common.h
hal_entry.c # HAL entry example
kernel_library_int.c # kernel library if CPU subgraphs are present
...
model.c
model.h
model_io_data.c
model_io_data.h
python_bindings.cpp
sub_0001_command_stream.c # Ethos-U55 subgraph generated C source code
sub_0001_command_stream.h
sub_0001_invoke.c
sub_0001_invoke.h
...
...
deploy_cfg.json
ir_dumps
person-det_can.dot
...
person-det_after_canonicalization.dot
person-det_subgraphs.dot
logs
model
input_desc.json
project.mdp

Please reference to the provided pre-generated e2studio projects to see how the generated C code under build/MCU/compilation/src can be incorporated into a e2studio project.

# How to Quantize and deploy models
If the starting point it is a Float32 precision model it is possible to use the MERA Quantizer to first quantize the model and finally deploy with MCU/Ethos-U55 support.

The following is a sample of how to quantize a model with the MERA Quantizer API:

```
with mera.Deployer(str(deploy_dir), overwrite=True) as deployer:
if model_path.suffix == '.tflite':
mera_model = mera.ModelLoader(deployer).from_tflite(str(model_path))
elif model_path.suffix == '.onnx':
mera_model = mera.ModelLoader(deployer).from_onnx(str(model_path), shape_mapping=SYMBOLIC_DIMS)
elif model_path.suffix == '.pte':
mera_model = mera.ModelLoader(deployer).from_executorch(str(model_path))
else:
raise ValueError("Unsupported model format: " + model_path.suffix)
cal_data = generate_input_data(mera_model, num_cal)
qtzer = mera.Quantizer(deployer,mera_model,quantizer_config=quantizer_config,mera_platform=platform)
qtz_path = Path(result_path)
res_path = qtz_path / 'model.mera'
qty = qtzer.calibrate(cal_data).quantize().evaluate_quality(cal_data[:1])
Q = qty[0].out_summary()[0]
if Q["psnr"] < 5:
model.status = Status.ERROR_PSNR
model.last_error = f'PSNR too low: {Q["psnr"]}'
return {'inputs': None, 'outputs': None}
qtzer.save_to(res_path)
print(f'Successfully quantized model with quality: {Q["psnr"]} psnr, {Q["score"]} score')
return res_path
```

Once quantized, we can deploy the quantized model by using using .from_quantized_mera() instead of .from_tflite():

```
with mera.Deployer(str(deploy_dir), overwrite=True) as deployer:
mera_model = mera.ModelLoader(deployer).from_quantized_mera(model_path)
platform = Platform.MCU_ETHOS if with_ethos else Platform.MCU_CPU
# ARM Vela options
# only effective if Platform.MCU_ETHOS is selected, ignored otherwise
vela_config = {}
vela_config['enable_ospi'] = needs_ospi(model_path, 1.5)
vela_config['sys_config'] = 'RA8P1'
vela_config['memory_mode'] = 'Sram_Only'
vela_config['accel_config'] = 'ethos-u55-256'
vela_config['optimise'] = 'Performance'
vela_config['verbose_all'] = False
# MCU C code generation options
mcu_config = {}
mcu_config['suffix'] = ''
mcu_config['weight_location'] = 'flash' # other option is: 'iram'
# On other scripts we could use False and it will not generate
# x86 related source code (python bindings for example),
mcu_config['use_x86'] = True
# generation of reference data from original model format
# using the original runtime is only supported for TFLite models
enable_ref_data = with_ref_data and model_path.suffix == '.tflite'
deployer.deploy(mera_model,
mera_platform=platform,
target=Target.MCU,
vela_config=vela_config,
mcu_config=mcu_config,
enable_ref_data=enable_ref_data)
```

# Full quantization demo

We provide a script that given a model (either with .tflite, .onnx or .pte extension) will:
* calibrate and quantize the model with random data
* deploy the model for the MCU C Codegen target and generate C source code
* compile the auto-generated Python bindings for the C source code
* execute the C source code through the Python bindings
* compare the MERA Interpreter results and the C source code results

To run this script:

```
cd scripts/
# deploy for MCU only
python mcu_quantize.py ../models_fp32 deploy_mcu
# deploy for MCU+Ethos-U55
python mcu_quantize.py -e ../models_fp32_ethos deploy_ethos
```

