#include <stddef.h>
#include <stdint.h>

// NPU unit addresses
#include "sub_0000_tensors.h"
#include "sub_0002_tensors.h"

// Arenas for NPU units
extern uint8_t sub_0000_arena[kArenaSize_sub_0000];
extern uint8_t sub_0002_arena[kArenaSize_sub_0002];

// Buffers


void RunModel(bool clean_outputs);

  // Model input pointers
int8_t* GetModelInputPtr_serving_default_input_1_0();

  // Model output pointers
int8_t* GetModelOutputPtr_StatefulPartitionedCall_0_70098();

