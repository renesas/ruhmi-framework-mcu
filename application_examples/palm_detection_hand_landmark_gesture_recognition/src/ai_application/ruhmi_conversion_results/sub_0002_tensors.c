#include "sub_0002_tensors.h"

const TensorInfo sub_0002_tensors[] = {
  { "_split_1_command_stream", 2, 848, "COMMAND_STREAM", 0xffffffff },
  { "_split_1_flash", 3, 288, "MODEL", 0xffffffff },
  { "_split_1_scratch", 4, 22176, "ARENA", 0x0 },
  { "_split_1_scratch_fast", 5, 22176, "FAST_SCRATCH", 0x0 },
  { "model_10_tf_compat_v1_gather_1_GatherV2__70409", 6, 2016, "INPUT_TENSOR", 0x0 },
  { "model_10_tf_strided_slice_1_StridedSlice_70419", 7, 4032, "INPUT_TENSOR", 0x17a0 },
  { "model_10_tf_strided_slice_StridedSlice_70421", 8, 4032, "INPUT_TENSOR", 0x7e0 },
  { "PartitionedCall_3_70410", 1, 2016, "OUTPUT_TENSOR", 0x0 },
  { "PartitionedCall_0_70424", 0, 8064, "OUTPUT_TENSOR", 0x2760 },
};

const size_t sub_0002_tensors_count = sizeof(sub_0002_tensors) / sizeof(sub_0002_tensors[0]);

// Addresses for each input and output buffer inside of the arena
const uint32_t sub_0002_address_model_10_tf_compat_v1_gather_1_GatherV2__70409 = 0x0;
const uint32_t sub_0002_address_model_10_tf_strided_slice_1_StridedSlice_70419 = 0x17a0;
const uint32_t sub_0002_address_model_10_tf_strided_slice_StridedSlice_70421 = 0x7e0;
const uint32_t sub_0002_address_PartitionedCall_3_70410 = 0x0;
const uint32_t sub_0002_address_PartitionedCall_0_70424 = 0x2760;

