#include "sub_0000_tensors.h"

const TensorInfo sub_0000_tensors[] = {
  { "_split_1_command_stream", 0, 2892, "COMMAND_STREAM", 0xffffffff },
  { "_split_1_flash", 1, 248544, "MODEL", 0xffffffff },
  { "_split_1_scratch", 2, 401408, "ARENA", 0x0 },
  { "_split_1_scratch_fast", 3, 401408, "FAST_SCRATCH", 0x0 },
  { "serving_default_input_1_0", 5, 150528, "INPUT_TENSOR", 0x31000 },
  { "mobilenet_0_25_224_conv_pw_13_relu_Relu6_mobilenet_0_25_224_conv_pw_13_bn_FusedBatchNormV3_mobilenet_0_25_224_conv_pw_13_Conv2D_70091", 4, 12544, "OUTPUT_TENSOR", 0x0 },
};

const size_t sub_0000_tensors_count = sizeof(sub_0000_tensors) / sizeof(sub_0000_tensors[0]);

// Addresses for each input and output buffer inside of the arena
const uint32_t sub_0000_address_serving_default_input_1_0 = 0x31000;
const uint32_t sub_0000_address_mobilenet_0_25_224_conv_pw_13_relu_Relu6_mobilenet_0_25_224_conv_pw_13_bn_FusedBatchNormV3_mobilenet_0_25_224_conv_pw_13_Conv2D_70091 = 0x0;

