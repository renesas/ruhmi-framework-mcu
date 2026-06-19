/*
 * This file is developed by EdgeCortix Inc. to be used with certain Renesas Electronics Hardware only.
 *
 * Copyright © 2025 EdgeCortix Inc. Licensed to Renesas Electronics Corporation with the
 * right to sublicense under the Apache License, Version 2.0.
 *
 * This file also includes source code originally developed by the Renesas Electronics Corporation.
 * The Renesas disclaimer below applies to any Renesas-originated portions for usage of the code.
 *
 * The Renesas Electronics Corporation
 * DISCLAIMER
 * This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No
 * other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
 * applicable laws, including copyright laws.
 * THIS SOFTWARE IS PROVIDED 'AS IS' AND RENESAS MAKES NO WARRANTIES REGARDING
 * THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM
 * EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES
 * SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS
 * SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
 * Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of
 * this software. By using this software, you agree to the additional terms and conditions found by accessing the
 * following link:
 * http://www.renesas.com/disclaimer
 *
 * Changed from original python code to C source code.
 * Copyright (C) 2017 Renesas Electronics Corporation. All rights reserved.
 *
 * This file also includes source codes originally developed by the TensorFlow Authors which were distributed under the following conditions.
 *
 * The TensorFlow Authors
 * Copyright 2023 The Apache Software Foundation
 *
 * This product includes software developed at
 * The Apache Software Foundation (http://www.apache.org/).
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "model.h"

/* D-cache maintenance — SCB_Clean/InvalidateDCache_by_Addr come from hal_data.h */
#include "hal_data.h"

// CPU compute declarations
#include "sub_0000_invoke.h"
#include "compute_sub_0001.h"
#include "sub_0002_invoke.h"

// Buffers for CPU units
int8_t buf_serving_default_input_0[110592];
int8_t buf_model_10_tf_concat_concat_70407[2016];
int8_t buf_model_10_tf_math_add_157_Add_model_10_tf_compat_v1_squeeze_Squeeze_5_model_10_tf_math_divide_truediv_model_10_tf_math_divide_truediv_y__Const_81_70416[36288];
int8_t buf_model_10_tf_compat_v1_gather_1_GatherV2__70409[2016];
int8_t buf_model_10_tf_strided_slice_1_StridedSlice_70419[4032];
int8_t buf_model_10_tf_strided_slice_StridedSlice_70421[4032];
int8_t buf_PartitionedCall_3_70410[2016];
int8_t buf_PartitionedCall_1_70417[4032];
int8_t buf_PartitionedCall_2_70418[4032];
int8_t buf_PartitionedCall_0_70424[8064];

// Arenas for CPU units
__attribute__((aligned(16), section(".sdram"))) uint8_t compute_arena_sub_0001[kBufferSize_sub_0001];

  // Model input pointers
int8_t* GetModelInputPtr_serving_default_input_0() {
  return (int8_t*) (sub_0000_arena + sub_0000_address_serving_default_input_0);
}


  // Model output pointers
int8_t* GetModelOutputPtr_PartitionedCall_3_70410() {
  return (int8_t*) (sub_0002_arena + sub_0002_address_PartitionedCall_3_70410);
}

int8_t* GetModelOutputPtr_PartitionedCall_1_70417() {
  return buf_PartitionedCall_1_70417;
}

int8_t* GetModelOutputPtr_PartitionedCall_2_70418() {
  return buf_PartitionedCall_2_70418;
}

int8_t* GetModelOutputPtr_PartitionedCall_0_70424() {
  return (int8_t*) (sub_0002_arena + sub_0002_address_PartitionedCall_0_70424);
}


void RunModel(bool clean_outputs) {
  // Buffers for NPU units
  int8_t* buf_model_10_tf_concat_concat_70407 = (int8_t*) (sub_0000_arena + sub_0000_address_model_10_tf_concat_concat_70407);
  int8_t* buf_model_10_tf_math_add_157_Add_model_10_tf_compat_v1_squeeze_Squeeze_5_model_10_tf_math_divide_truediv_model_10_tf_math_divide_truediv_y__Const_81_70416 = (int8_t*) (sub_0000_arena + sub_0000_address_model_10_tf_math_add_157_Add_model_10_tf_compat_v1_squeeze_Squeeze_5_model_10_tf_math_divide_truediv_model_10_tf_math_divide_truediv_y__Const_81_70416);
  int8_t* buf_PartitionedCall_3_70410 = (int8_t*) (sub_0002_arena + sub_0002_address_PartitionedCall_3_70410);
  int8_t* buf_PartitionedCall_0_70424 = (int8_t*) (sub_0002_arena + sub_0002_address_PartitionedCall_0_70424);

// NPU Unit 0: NPU1 writes outputs into sub_0000_arena
  sub_0000_invoke(clean_outputs);

  // FIX: Invalidate D-cache so CPU reads fresh NPU1 outputs from sub_0000_arena
  // (NPU writes bypass D-cache; without this CPU sees stale pre-inference data)
  SCB_InvalidateDCache_by_Addr((uint32_t *)sub_0000_arena, (int32_t)kArenaSize_sub_0000);

// CPU Unit: reads sub_0000_arena outputs, writes 3 tensors that NPU2 needs.
// FIX: Write those 3 tensors directly into sub_0002_arena at the exact offsets
// that sub_0002_invoke expects, instead of into disconnected CPU global buffers.
  compute_sub_0001(
    compute_arena_sub_0001,
    buf_model_10_tf_concat_concat_70407,
    buf_model_10_tf_math_add_157_Add_model_10_tf_compat_v1_squeeze_Squeeze_5_model_10_tf_math_divide_truediv_model_10_tf_math_divide_truediv_y__Const_81_70416,
    buf_PartitionedCall_1_70417,
    buf_PartitionedCall_2_70418,
    /* FIX: write directly into sub_0002_arena instead of orphaned CPU buffers */
    (int8_t *)(sub_0002_arena + sub_0002_address_model_10_tf_compat_v1_gather_1_GatherV2__70409),
    (int8_t *)(sub_0002_arena + sub_0002_address_model_10_tf_strided_slice_1_StridedSlice_70419),
    (int8_t *)(sub_0002_arena + sub_0002_address_model_10_tf_strided_slice_StridedSlice_70421)
  );

  // FIX: Clean D-cache so NPU2 sees the CPU outputs just written into sub_0002_arena
  SCB_CleanDCache_by_Addr((uint32_t *)sub_0002_arena, (int32_t)kArenaSize_sub_0002);

// NPU Unit 2: NPU2 reads from sub_0002_arena inputs, writes final outputs to sub_0002_arena
  sub_0002_invoke(clean_outputs);

}
