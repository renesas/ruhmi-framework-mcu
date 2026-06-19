#ifndef __SUB_0000__LANDMARK_INVOKE_H__
#define __SUB_0000__LANDMARK_INVOKE_H__

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

// Landmark arena shares SRAM with palm arena (they never run simultaneously)
extern uint8_t sub_0000_arena[];
#define sub_0000__landmark_arena sub_0000_arena

// Fast scratch arena not used for Ethos-U55
// We will not create it for now and reuse the address of the other arena
extern uint8_t* sub_0000__landmark_fast_scratch; // size: 1003520

int sub_0000__landmark_invoke(bool clean_outputs);


#endif // __SUB_0000__LANDMARK_INVOKE_H__
