#include <stddef.h>
#include <stdint.h>

// NPU unit addresses
#include "sub_0000_tensors.h"

// Arenas for NPU units
extern uint8_t sub_0000_arena[kArenaSize_sub_0000];

// Buffers


void RunModel(bool clean_outputs);

  // Model input pointers
int8_t* GetModelInputPtr_image_input();

  // Model output pointers
int8_t* GetModelOutputPtr_Identity_70275();
int8_t* GetModelOutputPtr_Identity_1_70284();

