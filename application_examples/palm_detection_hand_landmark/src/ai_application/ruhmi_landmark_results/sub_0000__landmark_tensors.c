#include "sub_0000__landmark_tensors.h"

const TensorInfo sub_0000__landmark_tensors[] = {
  { "_split_1_command_stream", 3, 6924, "COMMAND_STREAM", 0xffffffff },
  { "_split_1_flash", 4, 1258592, "MODEL", 0xffffffff },
  { "_split_1_scratch", 5, 1003520, "ARENA", 0x0 },
  { "_split_1_scratch_fast", 6, 1003520, "FAST_SCRATCH", 0x0 },
  { "serving_default_input_0", 7, 150528, "INPUT_TENSOR", 0x62000 },
  { "PartitionedCall_0_70174", 0, 63, "OUTPUT_TENSOR", 0x480 },
  { "PartitionedCall_2_70172", 2, 1, "OUTPUT_TENSOR", 0x4c0 },
  { "PartitionedCall_1_70170", 1, 1, "OUTPUT_TENSOR", 0x4d0 },
};

const size_t sub_0000__landmark_tensors_count = sizeof(sub_0000__landmark_tensors) / sizeof(sub_0000__landmark_tensors[0]);

// Addresses for each input and output buffer inside of the arena
const uint32_t sub_0000__landmark_address_serving_default_input_0 = 0x62000;
const uint32_t sub_0000__landmark_address_PartitionedCall_0_70174 = 0x480;
const uint32_t sub_0000__landmark_address_PartitionedCall_2_70172 = 0x4c0;
const uint32_t sub_0000__landmark_address_PartitionedCall_1_70170 = 0x4d0;

