#ifndef __SUB_0000_TENSORS_H__
#define __SUB_0000_TENSORS_H__

#include <stddef.h>
#include <stdint.h>
#include "ethosu_common.h"

extern const TensorInfo sub_0000_tensors[];
extern const size_t sub_0000_tensors_count;

#define kArenaSize_sub_0000 442368

// Addresses for each input and output buffer inside of the arena
extern const uint32_t sub_0000_address_image_input;
extern const uint32_t sub_0000_address_Identity_1_70284;
extern const uint32_t sub_0000_address_Identity_70275;


#endif // __SUB_0000_TENSORS_H__
