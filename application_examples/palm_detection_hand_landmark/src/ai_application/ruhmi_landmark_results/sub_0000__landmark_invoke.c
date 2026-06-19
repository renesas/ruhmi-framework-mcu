#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "common_data.h"

#include "sub_0000__landmark_tensors.h"
#include "sub_0000__landmark_command_stream.h"
#include "sub_0000__landmark_model_data.h"

#include "sub_0000__landmark_invoke.h"

// Include Ethos-U driver headers (Assumed to be available)
#include "ethosu_driver.h"

// Landmark arena is aliased to sub_0000_arena (shared SRAM) via macro in header
// No separate allocation needed — palm & landmark never run simultaneously
// Fast scratch arena not used for Ethos-U55
//  We will not create it for now and reuse the address of the other arena
// __attribute__((aligned(16))) static uint8_t sub_0000__landmark_fast_scratch[1003520];
uint8_t* sub_0000__landmark_fast_scratch = sub_0000__landmark_arena;

int sub_0000__landmark_invoke(bool clean_outputs) {
  // Initialize base addresses and sizes
  uint64_t base_addrs[7] = {0};
  size_t base_addrs_size[7] = {0};
  int num_base_addrs = 7;

  // Variables for command stream
  uint8_t* cms_data = NULL;
  int cms_size = 0;

  // Prepare base_addrs and base_addrs_size arrays
  // Buffer sub_0000__landmark_model with size 1258592 and address: 4294967295
  base_addrs[0] = (uint64_t)(uintptr_t)sub_0000__landmark_model_data;
  base_addrs_size[0] = sub_0000__landmark_model_data_size;
  // Buffer sub_0000__landmark_arena with size 1003520 and address: 0
  base_addrs[1] = (uint64_t)(uintptr_t) (sub_0000__landmark_arena+0);
  base_addrs_size[1] = 1003520;

  // Buffer sub_0000__landmark_fast_scratch with size 1003520 and address: 0
  base_addrs[2] = (uint64_t)(uintptr_t) (sub_0000__landmark_arena+0);
  base_addrs_size[2] = 1003520;

  // Buffer input_tensor_0 with size 150528 and address: 401408
  base_addrs[3] = (uint64_t)(uintptr_t) (sub_0000__landmark_arena+401408);
  base_addrs_size[3] = 150528;

  // Buffer output_tensor_0 with size 63 and address: 1152
  if (clean_outputs) {
    memset(sub_0000__landmark_arena + 1152, 0, 63);
  }
  base_addrs[4] = (uint64_t)(uintptr_t) (sub_0000__landmark_arena+1152);
  base_addrs_size[4] = 63;

  // Buffer output_tensor_1 with size 1 and address: 1216
  if (clean_outputs) {
    memset(sub_0000__landmark_arena + 1216, 0, 1);
  }
  base_addrs[5] = (uint64_t)(uintptr_t) (sub_0000__landmark_arena+1216);
  base_addrs_size[5] = 1;

  // Buffer output_tensor_2 with size 1 and address: 1232
  if (clean_outputs) {
    memset(sub_0000__landmark_arena + 1232, 0, 1);
  }
  base_addrs[6] = (uint64_t)(uintptr_t) (sub_0000__landmark_arena+1232);
  base_addrs_size[6] = 1;

  // Command stream data
  cms_data = (uint8_t*)sub_0000__landmark_command_stream;
  cms_size = (int) sub_0000__landmark_command_stream_size;

  // Invoke the Ethos-U driver
  if (num_base_addrs > 8) {
    num_base_addrs = 8;
  }
  int result = ethosu_invoke_v3(&g_ethosu0, cms_data, cms_size, base_addrs, base_addrs_size, num_base_addrs, NULL);

  if (result == -1) {
    // Ethos-U invocation failed
    return -1;
  }

  return 0;
}
