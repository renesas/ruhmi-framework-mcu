# How to deploy models  
The sample script shows how to use the deployment API to compile an already quantized TFLite model on a board with Ethos-U55 support.  

## Deploy to CPU only   
By running the provided script **scripts/mcu_deploy.py**. we can compile the model for MCU only:  
```
  cd scripts/  
  # deploy for CPU only  
  python mcu_deploy.py --ref_data ../models_int8 deploy_qtzed  
```

This release provides some tested models, if the models provided are for example:  
```
  models_int8/  
  ├── ad_medium_int8.tflite
  ├── kws_micronet_m.tflite
  ├── mobilenet_v2_1.0_224_INT8.tflite
  ├── person-det.tflite
  ├── rnnoise_INT8.tflite
  ├── vww4_128_128_INT8.tflite
  ├── wav2letter_int8.tflite
  ├── yolo-fastest_192_face_v4.tflite
```

## Deploy to CPU with Ethos U55 supported    
When enabling Ethos-U support:  
```
cd scripts/   
# deploy for CPU+Ethos-U55  
python mcu_deploy.py --ethos --ref_data ../models_int8 deploy_qtzed_ethos  
 ```

you will get the following results:
```
    deploy_qtzed
    ├── ad_medium_int8_no_ospi
    ├── kws_micronet_m_no_ospi
    ├── mobilenet_v2_1.0_224_INT8_ospi
    ├── person-det_no_ospi
    ├── rnnoise_INT8_no_ospi
    ├── vww4_128_128_INT8_no_ospi
    ├── wav2letter_int8_ospi
    ├── yolo-fastest_192_face_v4_no_ospi
```

When Ethos-U support is enabled, each of the directories contain a deployment of the corresponding model for MCU + Ethos-U55 platform:  
```
└── [ad_medium_int8_no_ospi]  # an example for "ad_medium_int8_no_ospi"  
    ├── build  
        ├── MCU  
            ├── compilation  
                ├── mera.plan  
                ├── src     # compilation results: C source code and C++ testing support code # HAL entry example  
                    ├── CMakeLists.txt  
                    ├── compare.cpp  
                    ├── compute_sub_0000.c # CPU subgraph generated C source code  
                    ├── compute_sub_0000.h  
                    ├── ...  
                    ├── ethosu_common.h  
                    ├── hal_entry.c  
                    ├── kernel_library_int.c # kernel library if CPU subgraphs are present  
                    ├──  ...  
                    ├── model.c  
                    ├── model.h  
                    ├── model_io_data.c  
                    ├── model_io_data.h  
                    ├── python_bindings.cpp  
                    ├── sub_0001_command_stream.c # Ethos-U55 subgraph generated C source code  
                    ├── sub_0001_command_stream.h  
                    ├── sub_0001_invoke.c  
                    ├── sub_0001_invoke.h  
                    ├──  ...  
                ├──  ...  
            ├── deploy_cfg.json  
            ├── ir_dumps  
                ├── person-det_can.dot  
                ├── ...  
            ├── person-det_after_canonicalization.dot  
            ├── person-det_subgraphs.dot  
    ├── logs  
    ├──　model  
        ├── input_desc.json  
    ├── project.mdp  
```
  
The generated C code under **"build/MCU/compilation/src"** can be incorporated into a e2studio project.  
You can refer to [the runtime API specification](doc/runtime_api.md) to study how to use the output file from RUHMI Framework.  

# How to quantize and deploy models 
If the starting point it is a Float32 precision model, it is possible to use the Quantizer to first quantize the model and finally deploy with MCU/Ethos-U55 support.
The sample script with using the Quantizer can be refred.

To run the script:
```
cd scripts/
# deploy for CPU only
python mcu_quantize.py ../models_fp32 deploy_mcu

# deploy for CPU+Ethos-U55
python mcu_quantize.py -e ../models_fp32_ethos deploy_ethos
```

The generated C code under **"build/MCU/compilation/src"** can be incorporated into a e2studio project.  
You can refer to [the runtime API specification](doc/runtime_api.md) to study how to use the output file from RUHMI Framework.  


