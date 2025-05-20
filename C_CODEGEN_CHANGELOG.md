
# Change log of MERA 2.0 : Release 3.11

* Fixed a crash issue noted with TFLiteSpaceToBatchNd and TFLiteBatchToSpaceNd operators
* New operators supported - TFLiteSquaredDifference, TFLiteHardSwish for both FP32 & Int8 data types
* Added License headers for the kernel library files
* Enhancement to C_Codegen to handle TFLite models with incorrect output shape for any operators

# Change log of MERA 2.0 : Release 3.10

* Enhancements to C_Codegen for Python environment
* Udpate the buffer size calculation for CMSIS API calls to use <CMSIS_API_NAME>_get_buffer_size(), to make it forward compatible with newer CMSIS versions
* Changes to C_Codegen to print IR only when provided with `--log` CLI option
* Fix to provide the correct bias layout size for FullyConnectedBias and Conv2d layers
* Resolved the "inja error" observed with a few models
* Resolved the compiler warnings related for "unused parameters" in the kernel libraries
* Fix to handle models with tensor names that are not valid in C compiler
* Fix to prevent map::at error observed with certain models


# Change log of MERA 2.0 : Release 3.9

* Added support for Floating point input for the listed operators:
  - TFLiteSqrt
  - TFLiteRSqrt

* Added support for Floating point and Int8 input for the operators:
  - TransposeConv2dBias
  - TFLitePad
  - TFLitePadV2
  - TFLiteFullyConnected  (PS: FC without Bias)

* Fixes
  - the result of the TFLiteTransposeConv2d op with Valid padding
  - compilation errors caused with the PRelu op template
  - the result mismatch issues caused for the Add, Mul, and Sum ops
  - addressed few compilier warnings

* Support for Conv and FullyConnected ops with hybrid models, where inputs are FP32 and weights(alone) are Int8

* Inference result threshold for a mismatch error has been set at a value of `2` for Int8, and `0.00001` for FP32 models



# Change log of MERA 2.0 : Release 3.8

* Added support for Floating point input for the listed operators:
  - TFLiteResizeBilinear
  - Upsampling
  - TFLiteMirrorPad
  - TFLitePow
  - TFLiteAbs

* Added support for Int8 input for the listed operators:
  - TFLiteSum
  - TFLiteAbs
  - TFLiteQuantize (int8 to uint8)

* Refactored the listed operators to support broadcasting:
  - TFLiteMinimum (Int8 & FP32)
  - TFLiteQAdd (Int8)
  - TFLiteSub (Int8)
  - TFLiteMul (Int8)

* The `c_codegen` and `mera_tflite2c.py` have been updated to replace the `c_only` option with a new option `x86` to generate all the files requried for testing on x86 platform

* Updated `c_codegen` to generate only the Int8 kernel libraries for quantized models and only the FP32 kernel libraries for FP32 models

* Fix memory buffer usage algorithm to avoid using any live memory allocated

* Inference result threshold for a mismatch error has been set at a value of `1` for Int8, and `0.00001` for FP32 models


# Change log of MERA 2.0 : Release 3.7.1

* Added support for Floating point input for the listed operators:
  - TFLiteExp
  - TFLiteNeg
  - TFLiteLogSoftmax
  - TFLiteLog
  - LeakyReLUFp
  - TFLiteQConv2dBias
  - TFLiteTransposeConv2d
  - TFLiteSub
  - TFLiteMean
  - TFLiteSum
  - TFLitePRelu
  - ReduceMax
  - TFLiteSpaceToBatchNd
  - TFLiteBatchToSpaceNd
  - TFLiteTranspose
  - TFLiteSigmoid

  * Added support for Relu, Relu6, and PRelu as independent operators, for both Int and FP32 inputs

  * Added support of axis field for ReduceMax operator

  * The StridedSlice operator has been refactored to handle negative stride values and mask options


# Change log of MERA 2.0 : Release 3.6.1

* Identify the name of the unsupported operator in error messages

* Fixed root cause of below error messages:
  - `what():  map::at`
  - `what():  vector::_M_range_check: __n (which is 0) >= this->size() (which is 0)`



# Change log of MERA 2.0 : Release 3.6

* Added support for Floating point input for the listed operators:
  - TFLiteQConv2dBias
  - TFLiteFullyConnectedBias
  - TFLiteSoftmax
  - TFLiteMaxPool
  - TFLiteQAdd
  - TFLiteMul
  - TFLiteSlice
  - TFLiteStridedSlice
  - TFLiteTanh
  - TFLiteAveragePool
  - TFLiteMinimum
  - TFLiteConcatenate
  - TFLitePack
  - TFLiteSqueeze
  - TFLiteRelu
  - TFLiteRelu6
  - SPLIT
  - SPLIT_V
  - UNPACK
  - SHAPE
  - RESHAPE
  - EXPAND_DIMS

* The `c_codegen` binary has a new option - `c_only` to generate only the .c and .h files. (The other files are not generated)

* Fix to avoid invalid variable names of input/output/intermediate buffer variables in the `compute_*` 'C' files generated

* The `mera_tflite2c.py` has been update with the new option for `c_codegen`



# Change log of MERA 2.0 : Release 3.5

* Included support for several TFLite operators with int8 operands:
  - TFLiteLogSoftmax
  - TFLiteNeg
  - TFLiteLog
  - TFLiteExp
  - TFLiteSpaceToBatchNd
  - TFLiteBatchToSpaceNd
  - TFLiteTranspose
  - TFLiteMirrorPad
  - TFLiteResizeBilinear
  - Upsampling
  - LeakyReLU
  
* Enhancement to support saving model weights and inputs to either ROM/Flash or RAM, based on new compiler option

* Included the MLPerf scripts updated for the current release

* Fix for the incorrect padding for TFLiteMaxPool operator

* Update to TFLiteConcatenate operator to support inputs of rank of 2 & 3
