#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "model.h"

// CPU compute declarations
#include "sub_0000_invoke.h"

// Buffers for CPU units

// Arenas for CPU units

  // Model input pointers
int8_t* GetModelInputPtr_image_input() {
  return (int8_t*) (sub_0000_arena + sub_0000_address_image_input);
}


  // Model output pointers
int8_t* GetModelOutputPtr_Identity_70275() {
  return (int8_t*) (sub_0000_arena + sub_0000_address_Identity_70275);
}

int8_t* GetModelOutputPtr_Identity_1_70284() {
  return (int8_t*) (sub_0000_arena + sub_0000_address_Identity_1_70284);
}


void RunModel(bool clean_outputs) {
  // Buffers for NPU units
  int8_t* buf_image_input = (int8_t*) (sub_0000_arena + sub_0000_address_image_input);
  int8_t* buf_Identity_70275 = (int8_t*) (sub_0000_arena + sub_0000_address_Identity_70275);
  int8_t* buf_Identity_1_70284 = (int8_t*) (sub_0000_arena + sub_0000_address_Identity_1_70284);

// NPU Unit
  sub_0000_invoke(clean_outputs);

}
