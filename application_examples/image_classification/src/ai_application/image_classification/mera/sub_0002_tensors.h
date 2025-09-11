#ifndef __SUB_0002_TENSORS_H__
#define __SUB_0002_TENSORS_H__

#include <stddef.h>
#include <stdint.h>
#include "ethosu_common.h"

extern const TensorInfo sub_0002_tensors[];
extern const size_t sub_0002_tensors_count;

#define kArenaSize_sub_0002 8096

// Addresses for each input and output buffer inside of the arena
extern const uint32_t sub_0002_address_mobilenet_0_25_224_global_average_pooling2d_Mean_70092;
extern const uint32_t sub_0002_address_StatefulPartitionedCall_0_70098;


#endif // __SUB_0002_TENSORS_H__
