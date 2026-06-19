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
 */

#include <stdint.h>

#include "compute_sub_0001.h"

#include "arm_nn_types.h"
#include "arm_nnfunctions.h"
#include "kernel_library_utils.h"

#include "kernel_library_int.h" 

 

void compute_sub_0001(
  // buffer for intermediate results
  uint8_t* main_storage, // should provide at least 2021 bytes of storage

  // inputs
  
  const int8_t model_10_tf_concat_concat_70407[2016], // 1,2016,1
  
  const int8_t model_10_tf_math_add_157_Add_model_10_tf_compat_v1_squeeze_Squeeze_5_model_10_tf_math_divide_truediv_model_10_tf_math_divide_truediv_y__Const_81_70416[36288], // 2016,18
  

  // outputs
  
  int8_t PartitionedCall_1_70417[4032] , // 2016,2
  
  int8_t PartitionedCall_2_70418[4032] , // 2016,2
  
  int8_t model_10_tf_compat_v1_gather_1_GatherV2__70409[2016] , // 2016
  
  int8_t model_10_tf_strided_slice_1_StridedSlice_70419[4032] , // 2016,2
  
  int8_t model_10_tf_strided_slice_StridedSlice_70421[4032]  // 2016,2
  
) {
  // Buffers allocated on the main storage (note: depends on the execution order)
    
  
  int8_t* model_10_tf_compat_v1_gather_GatherV2__70408 = (int8_t *) &main_storage[0]; // 2016,1 == 2016
  
  

  // Parameters
  
  
  static const int32_t Int32VecConstant_70008_0[1] = { // 1
    0, 
  };
  
  static const int32_t Int32VecConstant_70008_1[1] = { // 1
    0, 
  };
  
  static const int32_t Int32VecConstant_70011_0[2] = { // 2
    0, 4, 
  };
  
  static const int32_t Int32VecConstant_70011_1[2] = { // 2
    0, 4, 
  };
  
  static const int32_t Int32VecConstant_70012[2] = { // 2
    0, 6, 
  };
  
  static const int32_t Int32VecConstant_70013_0[2] = { // 2
    1, 1, 
  };
  
  static const int32_t Int32VecConstant_70013_1[2] = { // 2
    1, 1, 
  };
  
  static const int32_t Int32VecConstant_70013_2[2] = { // 2
    1, 1, 
  };
  
  static const int32_t Int32VecConstant_70013_3[2] = { // 2
    1, 1, 
  };
  
  static const int32_t Int32VecConstant_70014[2] = { // 2
    0, 8, 
  };
  
  static const int32_t Int32VecConstant_70015[2] = { // 2
    0, 10, 
  };
  
  static const int32_t Int32VecConstant_70016_0[2] = { // 2
    0, 2, 
  };
  
  static const int32_t Int32VecConstant_70016_1[2] = { // 2
    0, 2, 
  };
  
  static const int32_t Int32VecConstant_70017[2] = { // 2
    0, 0, 
  };
  
  







//
// Strided Slice
//
{
TfLiteStridedSliceParams str_slc_params = {
  3,   // begin_mask
  1,   // end_mask
  0,   // ellipsis_mask
  0,   // new_axis_mask
  0   // shrink_axis_mask
};

int32_t input_shape[2] = { 2016, 18,  };

int32_t output_shape[2] = { 2016, 2,  };

StridedSlice(model_10_tf_math_add_157_Add_model_10_tf_compat_v1_squeeze_Squeeze_5_model_10_tf_math_divide_truediv_model_10_tf_math_divide_truediv_y__Const_81_70416,  // input data
  model_10_tf_strided_slice_StridedSlice_70421,      // output data
  Int32VecConstant_70017,       // begin
  Int32VecConstant_70016_1,         // end
  Int32VecConstant_70013_3,     // strides
  input_shape,    // input shape
  2,         // input dimensions
  output_shape,    // output shape
  2,   // output dimensions
  str_slc_params);    // strided slice params
}

//
// Strided Slice
//
{
TfLiteStridedSliceParams str_slc_params = {
  1,   // begin_mask
  1,   // end_mask
  0,   // ellipsis_mask
  0,   // new_axis_mask
  0   // shrink_axis_mask
};

int32_t input_shape[2] = { 2016, 18,  };

int32_t output_shape[2] = { 2016, 2,  };

StridedSlice(model_10_tf_math_add_157_Add_model_10_tf_compat_v1_squeeze_Squeeze_5_model_10_tf_math_divide_truediv_model_10_tf_math_divide_truediv_y__Const_81_70416,  // input data
  model_10_tf_strided_slice_1_StridedSlice_70419,      // output data
  Int32VecConstant_70016_0,       // begin
  Int32VecConstant_70011_1,         // end
  Int32VecConstant_70013_2,     // strides
  input_shape,    // input shape
  2,         // input dimensions
  output_shape,    // output shape
  2,   // output dimensions
  str_slc_params);    // strided slice params
}

//
// Gather
//
{
const int32_t in_shape_model_10_tf_compat_v1_gather_GatherV2__70408[3] = { 1, 2016, 1,  };

const int32_t indices_shape_Int32VecConstant_70008_1[1] = { 1,  };

Gather(
  model_10_tf_concat_concat_70407,  // input data
  in_shape_model_10_tf_compat_v1_gather_GatherV2__70408,  // input shape
  3,  // input dims
  Int32VecConstant_70008_1,      // indices data
  indices_shape_Int32VecConstant_70008_1,  // indices shape
  1,  // indices dims
  0,  // axis
  0,  // batch dims
  model_10_tf_compat_v1_gather_GatherV2__70408);      // output data
}

//
// Gather
//
{
const int32_t in_shape_model_10_tf_compat_v1_gather_1_GatherV2__70409[2] = { 2016, 1,  };

const int32_t indices_shape_Int32VecConstant_70008_0[1] = { 1,  };

Gather(
  model_10_tf_compat_v1_gather_GatherV2__70408,  // input data
  in_shape_model_10_tf_compat_v1_gather_1_GatherV2__70409,  // input shape
  2,  // input dims
  Int32VecConstant_70008_0,      // indices data
  indices_shape_Int32VecConstant_70008_0,  // indices shape
  1,  // indices dims
  1,  // axis
  0,  // batch dims
  model_10_tf_compat_v1_gather_1_GatherV2__70409);      // output data
}

//
// Strided Slice
//
{
TfLiteStridedSliceParams str_slc_params = {
  1,   // begin_mask
  1,   // end_mask
  0,   // ellipsis_mask
  0,   // new_axis_mask
  0   // shrink_axis_mask
};

int32_t input_shape[2] = { 2016, 18,  };

int32_t output_shape[2] = { 2016, 2,  };

StridedSlice(model_10_tf_math_add_157_Add_model_10_tf_compat_v1_squeeze_Squeeze_5_model_10_tf_math_divide_truediv_model_10_tf_math_divide_truediv_y__Const_81_70416,  // input data
  PartitionedCall_2_70418,      // output data
  Int32VecConstant_70014,       // begin
  Int32VecConstant_70015,         // end
  Int32VecConstant_70013_1,     // strides
  input_shape,    // input shape
  2,         // input dimensions
  output_shape,    // output shape
  2,   // output dimensions
  str_slc_params);    // strided slice params
}

//
// Strided Slice
//
{
TfLiteStridedSliceParams str_slc_params = {
  1,   // begin_mask
  1,   // end_mask
  0,   // ellipsis_mask
  0,   // new_axis_mask
  0   // shrink_axis_mask
};

int32_t input_shape[2] = { 2016, 18,  };

int32_t output_shape[2] = { 2016, 2,  };

StridedSlice(model_10_tf_math_add_157_Add_model_10_tf_compat_v1_squeeze_Squeeze_5_model_10_tf_math_divide_truediv_model_10_tf_math_divide_truediv_y__Const_81_70416,  // input data
  PartitionedCall_1_70417,      // output data
  Int32VecConstant_70011_0,       // begin
  Int32VecConstant_70012,         // end
  Int32VecConstant_70013_0,     // strides
  input_shape,    // input shape
  2,         // input dimensions
  output_shape,    // output shape
  2,   // output dimensions
  str_slc_params);    // strided slice params
}

}
