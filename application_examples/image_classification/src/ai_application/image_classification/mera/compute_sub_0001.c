#include <stdint.h>

#include "compute_sub_0001.h"

#include "arm_nn_types.h"
#include "arm_nnfunctions.h"
#include "kernel_library_utils.h"

#include "kernel_library_int.h" 

 

void compute_sub_0001(
  // buffer for intermediate results
  uint8_t* main_storage, // should provide at least 1 bytes of storage

  // inputs
  
  const int8_t mobilenet_0_25_224_conv_pw_13_relu_Relu6_mobilenet_0_25_224_conv_pw_13_bn_FusedBatchNormV3_mobilenet_0_25_224_conv_pw_13_Conv2D_70091[12544], // 1,7,7,256
  

  // outputs
  
  int8_t mobilenet_0_25_224_global_average_pooling2d_Mean_70092[256]  // 1,1,1,256
  
) {
  // Buffers allocated on the main storage (note: depends on the execution order)
  

  // Parameters
  
  
  static const int32_t Int32VecConstant_70001[2] = { // 2
    1, 2, 
  };
  
  

  
  //
// Mean
//
int32_t in_shape_mobilenet_0_25_224_conv_pw_13_relu_Relu6_mobilenet_0_25_224_conv_pw_13_bn_FusedBatchNormV3_mobilenet_0_25_224_conv_pw_13_Conv2D_70091[4] = { 1, 7, 7, 256,  };

Mean(mobilenet_0_25_224_conv_pw_13_relu_Relu6_mobilenet_0_25_224_conv_pw_13_bn_FusedBatchNormV3_mobilenet_0_25_224_conv_pw_13_Conv2D_70091, mobilenet_0_25_224_global_average_pooling2d_Mean_70092, in_shape_mobilenet_0_25_224_conv_pw_13_relu_Relu6_mobilenet_0_25_224_conv_pw_13_bn_FusedBatchNormV3_mobilenet_0_25_224_conv_pw_13_Conv2D_70091, 4,
  -128, // input zp
  256, // output size
  1073741824, // output multiplier
  1, // output shift
  -128, // output zp
  Int32VecConstant_70001, 2); // axes id and axes dims

  
}
