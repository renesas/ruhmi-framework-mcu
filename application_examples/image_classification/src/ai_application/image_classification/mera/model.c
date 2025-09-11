#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "model.h"

// CPU compute declarations
#include "sub_0000_invoke.h"
#include "compute_sub_0001.h"
#include "sub_0002_invoke.h"

// Buffers for CPU units

// Arenas for CPU units
uint8_t compute_arena_sub_0001[kBufferSize_sub_0001];

  // Model input pointers
int8_t* GetModelInputPtr_serving_default_input_1_0() {
  return (int8_t*) (sub_0000_arena + sub_0000_address_serving_default_input_1_0);
}


  // Model output pointers
int8_t* GetModelOutputPtr_StatefulPartitionedCall_0_70098() {
  return (int8_t*) (sub_0002_arena + sub_0002_address_StatefulPartitionedCall_0_70098);
}


void RunModel(bool clean_outputs) {
  // Buffers for NPU units
  int8_t* buf_serving_default_input_1_0 = (int8_t*) (sub_0000_arena + sub_0000_address_serving_default_input_1_0);
  int8_t* buf_mobilenet_0_25_224_conv_pw_13_relu_Relu6_mobilenet_0_25_224_conv_pw_13_bn_FusedBatchNormV3_mobilenet_0_25_224_conv_pw_13_Conv2D_70091 = (int8_t*) (sub_0000_arena + sub_0000_address_mobilenet_0_25_224_conv_pw_13_relu_Relu6_mobilenet_0_25_224_conv_pw_13_bn_FusedBatchNormV3_mobilenet_0_25_224_conv_pw_13_Conv2D_70091);
  int8_t* buf_mobilenet_0_25_224_global_average_pooling2d_Mean_70092 = (int8_t*) (sub_0002_arena + sub_0002_address_mobilenet_0_25_224_global_average_pooling2d_Mean_70092);
  int8_t* buf_StatefulPartitionedCall_0_70098 = (int8_t*) (sub_0002_arena + sub_0002_address_StatefulPartitionedCall_0_70098);

// NPU Unit
  sub_0000_invoke(clean_outputs);

// CPU Unit
  compute_sub_0001(compute_arena_sub_0001, buf_mobilenet_0_25_224_conv_pw_13_relu_Relu6_mobilenet_0_25_224_conv_pw_13_bn_FusedBatchNormV3_mobilenet_0_25_224_conv_pw_13_Conv2D_70091, buf_mobilenet_0_25_224_global_average_pooling2d_Mean_70092  );

// NPU Unit
  sub_0002_invoke(clean_outputs);

}
