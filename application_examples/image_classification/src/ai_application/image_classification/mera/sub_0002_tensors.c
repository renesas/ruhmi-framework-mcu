#include "sub_0002_tensors.h"

const TensorInfo sub_0002_tensors[] = {
  { "_split_1_command_stream", 1, 2016, "COMMAND_STREAM", 0xffffffff },
  { "_split_1_flash", 2, 250256, "MODEL", 0xffffffff },
  { "_split_1_scratch", 3, 8096, "ARENA", 0x0 },
  { "_split_1_scratch_fast", 4, 8096, "FAST_SCRATCH", 0x0 },
  { "mobilenet_0_25_224_global_average_pooling2d_Mean_70092", 5, 256, "INPUT_TENSOR", 0x3f0 },
  { "StatefulPartitionedCall_0_70098", 0, 1000, "OUTPUT_TENSOR", 0xfd0 },
};

const size_t sub_0002_tensors_count = sizeof(sub_0002_tensors) / sizeof(sub_0002_tensors[0]);

// Addresses for each input and output buffer inside of the arena
const uint32_t sub_0002_address_mobilenet_0_25_224_global_average_pooling2d_Mean_70092 = 0x3f0;
const uint32_t sub_0002_address_StatefulPartitionedCall_0_70098 = 0xfd0;

