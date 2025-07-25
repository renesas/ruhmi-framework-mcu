# Guide to the generated C source code

After compiling the model with the provided Python code, several files will be generated in the deployment directory. These include deployment artifacts created during compilation that are useful to retain for debugging and inspection. The most important output from the RUHMI framework is located under:
```<deployment_directory>/build/MCU/compilation/src```.  
This directory contains the model converted into C99 source code files, ready to be integrated into your MCU project.

> NOTE:
> The generated code only supports [FSP6.0.0](https://github.com/renesas/fsp/releases/tag/v6.0.0) with [CMSIS-NN 7.0.0](https://github.com/ARM-software/CMSIS-NN/releases).  

## Reference example of the folder structure
```
 models_int8/  
  ├── ad_medium_int8.tflite
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
```

  [Tips]    
  hal_entry.c: Auto-generated example of a possible entry point on Renesas e2 studio project to get the user a starting point on how to run the model. This generated code intended to be used as a reference by the user.  
  It should be helpfull to understand how to use the output source code with refering the following discription.  

## Runtime API - CPU only deployment
When a model is converted into source code with RUHMI[^1] framework without Ethos-U support, all the operators in the model be mapped to run on CPU only.   
In this case, the generated code will refer to a single subgraph **compute_sub_0000<suffix>**, by default, when no suffix is provided, the name of the header that need to included on your application entry point is **compute_sub_0000.h**.  

This header, **model.h** provides the declaration of a C function that if called will run the model with the provided inputs and write the results on the provided output buffers:  

[^1]: RUHMI Framework is powered by EdgeCortix© MERA™.

### Definition of input/output buffers (in the file of model.h)
```
   enum BufferSize_sub_0000 {
     kBufferSize_sub_0000 = <intermediate_buffers_size>
   };

   void compute_sub_0000(
     // buffer for intermediate results
     uint8_t* main_storage, // should provide at least <intermediate_buffers_size> bytes of storage

     // inputs
     const int8_t <input_name>[xxx], // 1,224,224,3

     // outputs
     int8_t <output_name>[xxx]  // 1,1000
   );
```

It provides to the user the possibility of providing a buffer to hold intermediate outputs of the model. And this size if provided in compilation time as the value ```kBufferSize_sub_0000``` so the user can use this size to allocate the buffer on the stack, the heap or a custom data section.

### Code example  
```
  int8_t output_buffer[1000];    //StatefulPartitionedCall_0_70016;

  compute_sub_0000(compute_buffer, input_buffer, output_buffer);  
```

## Runtime API - CPU + Ethos-U deployment
If Ethos-U support is enabled during conversion into source code with the compiler then an arbitrary amount of subgraphs for either CPU or Ethos-U will be generated. Each of these subgraphs will correspond to generated C functions to run the corresponding section of the model on CPU or Ethos. Each function call will get its inputs from previous outputs of other subgraphs and write its outputs on buffers that are designated to became again inputs to other
functions and so on. To make easier for the user to invoke these models where CPU and NPU are involved, the generated code will automate this process and provide a single function that will orchestrate the calls to the different computation
units named ```void RunModel(bool clean_outputs)``` and helpers to access to each of the input and output areas at model level not per subgraph level. The runtime API header when Ethos-U is enabled can be found on a file named model.h
under the same directory ```<deployment_directory>/build/MCU/compilation/src```.

For example, after enabling Ethos-U support for a model with two inputs and three outputs, RUHMI framework provides the next runtime API:  

### Definition of input/output buffers (in the file of model.h)
```
void RunModel(bool clean_outputs);

  // Model input pointers
float* GetModelInputPtr_input_1();

  // Model output pointers
float* GetModelOutputPtr_Identity_70029();
```

### Code example  
```
memcpy(GetModelInputPtr_input_1(), model_input0, model_input_SIZE0);  //Set the input model to the pointer for the compiler  
                                                                      //WIll be set the output data to the GetModelOutputPtr_Identity_70029()  
RunModel();  //Execution  
```
The function GetModelInputPtr_input1 provides access to the buffer where the user can write the first input of the model.  
Those input and output pointer shall de defined in ```model.h``` which generated by the compiler. You shall refer to the definition dependingn on your model.  

To run the model and all the CPU or NPU units needed to be invoked to do inference with the deployed model, the user should invoke to the ```RunModel()``` function. The parameter ```clean_outputs``` should be used only for debugging purposes because it will set to zero all the output buffers used by an NPU unit before invoking it. Recommended value for the parameter ```clean_outputs``` is ```false```, as it will not incur into extra time expend on clearing these buffers.  

