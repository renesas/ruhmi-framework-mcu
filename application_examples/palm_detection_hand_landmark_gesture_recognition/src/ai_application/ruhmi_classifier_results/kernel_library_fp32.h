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

#ifndef __KERNEL_LIBRARY_FP32__
#define __KERNEL_LIBRARY_FP32__

#include <stdint.h>
#include <float.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#include "kernel_library_utils.h"

/****************************************************************************/
/*                      Floating Point Utility Functions                    */
/****************************************************************************/

void CalculateActivationRangeFp(FusedActivation activation,
                              float* activation_min, float* activation_max);
float ActivationFunctionWithMinMaxFp(float x, float output_activation_min,
                                      float output_activation_max);
void ComputeInterpolationValues(const float value, const float scale,
  const bool half_pixel_centers, int32_t input_size, float* scaled_value,
  int32_t* lower_bound, int32_t* upper_bound);

/****************************************************************************/
/*                           Floating Point Operators                       */
/****************************************************************************/

void ConvFp(const float* input_data, float* output_data, const int32_t* input_shape,
  const int32_t* output_shape, const int32_t* filter_shape, const float* filter_data,
  const int32_t* bias_shape, const float* bias_data, const int32_t* conv_params,
  int32_t activation);
void DepthWiseConvFp(const float* input_data, float* output_data, const int32_t* input_shape,
  const int32_t* output_shape, const int32_t* filter_shape, const float* filter_data,
  const int32_t* bias_shape, const float* bias_data, const int32_t* conv_params,
  int32_t activation);
void TransposeConvFp(const float* input_data, float* output_data, const int32_t* input_shape,
  const int32_t* output_shape, const int32_t* filter_shape, const float* filter_data,
  const int32_t* conv_params, int32_t activation, const float* bias_data);
void FullyConnectedFp(const float* input_data, float* output_data, const int32_t* input_shape,
  const int32_t* output_shape, int32_t output_dims_count, const int32_t* weights_shape,
  int32_t weights_dims_count, const float* weights_data, const int32_t* bias_shape,
  const float* bias_data, int32_t activation);
void SoftmaxFp(const float* input_data, float* output_data, const int32_t* input_shape,
  int32_t input_dims_count, const int32_t* output_shape, int32_t beta);
void MaxpoolFp(const float* input_data, float* output_data, const int32_t* input_shape,
  const int32_t* output_shape, const int32_t* pool_params, int32_t activation);

void AddFp(const float* input1_data, const float* input2_data, float* output_data,
  const int32_t* input1_shape, int32_t input1_dims, const int32_t* input2_shape,
  int32_t input2_dims, const int32_t* output_shape, int32_t output_dims,
  int32_t activation);
void AddBasicFp(const int32_t* input1_shape, const float* input1_data,
  int32_t input1_dims, const float* input2_data, float* output_data,
  int32_t activation);
void BroadcastAdd6DSlowFp(const int32_t* input1_shape, const float* input1_data,
  int32_t input1_dims, const int32_t* input2_shape, const float* input2_data,
  int32_t input2_dims, const int32_t* output_shape, float* output_data,
  int32_t output_dims, int32_t activation);
bool ReduceDimensionsForBroadcastFp(const int32_t* input1_dims,
  int32_t num_input1_dims, const int32_t* input2_dims, int32_t num_input2_dims,
  int32_t* compressed_input1_stride, int32_t* compressed_input2_stride,
  int32_t* compressed_output_shape);
void BroadcastAddRecursiveDimensionsFp(
  int dimension, int32_t* input1_offset_p, int32_t* input2_offset_p,
  int32_t* output_offset, int32_t* compressed_input1_stride,
  int32_t* compressed_input2_stride, int32_t* compressed_output_shape,
  int32_t activation, const float* input1_data, const float* input2_data,
  float* output_data);
void AddBroadcastFp(const float* input_data, const float* broadcast_data,
  float* output_data, int32_t size, int32_t activation);
void AddElementwiseFp(const float* input1_data, const float* input2_data, float* output_data,
  int32_t size, int32_t activation);

void SubFp(const float* input1_data, const float* input2_data, float* output_data,
  const int32_t* input1_shape, int32_t input1_dims, const int32_t* input2_shape,
  int32_t input2_dims, const int32_t* output_shape, int32_t output_dims,
  int32_t activation);
void SubBasicFp(const int32_t* input1_shape, const float* input1_data,
  int32_t input1_dims, const float* input2_data, float* output_data,
  int32_t activation);
void BroadcastSubSlow(const int32_t* input1_shape, const float* input1_data,
  int32_t input1_dims, const int32_t* input2_shape, const float* input2_data,
  int32_t input2_dims, const int32_t* output_shape, float* output_data,
  int32_t output_dims, int32_t activation);
void BroadcastSubRecursiveDimensionsFp(
    int dimension, int32_t* input1_offset_p, int32_t* input2_offset_p,
    int32_t* output_offset, int32_t* compressed_input1_stride,
    int32_t* compressed_input2_stride, int32_t* compressed_output_shape,
    int32_t activation, const float* input1_data, const float* input2_data,
    float* output_data);
void SubBroadcast1Fp(const float* input_data, const float* broadcast_data,
                         float* output_data, int32_t size, int32_t activation);
void SubBroadcast2Fp(const float* input_data, const float* broadcast_data,
                         float* output_data, int32_t size, int32_t activation);
void SubElementwiseFp(const float* input1_data, const float* input2_data, float* output_data,
                    int32_t size, int32_t activation);

void MulFp(const float* input1_data, const float* input2_data, float* output_data,
  const int32_t* input1_shape, int32_t input1_dims, const int32_t* input2_shape,
  int32_t input2_dims, const int32_t* output_shape, int32_t output_dims,
  int32_t activation);
bool ProcessBroadcastShapes(const int32_t* input1, int32_t input1_dims,
  const int32_t* input2, int32_t input2_dims, int32_t* broadcast_category);
void MulBasicFp(const int32_t* input1_shape, const float* input1_data,
  int32_t input1_dims, const float* input2_data, float* output_data,
  int32_t activation);
void BroadcastMul6DSlow(const int32_t* input1_shape, const float* input1_data,
  int32_t input1_dims, const int32_t* input2_shape, const float* input2_data,
  int32_t input2_dims, const int32_t* output_shape, float* output_data,
  int32_t output_dims, int32_t activation);
void BroadcastMulRecursiveDimensions(int dimension, const float* input1_data,
  const float* input2_data, float* output_data, uint32_t* input1_offset_p,
  uint32_t* input2_offset_p, uint32_t* output_offset, const NdArrayDesc* desc1,
  const NdArrayDesc* desc2, const int32_t* extended_output_shape_dims);

void DivFp(const float* input1_data, const float* input2_data, float* output_data,
  const int32_t* input1_shape, int32_t input1_dims, const int32_t* input2_shape,
  int32_t input2_dims, const int32_t* output_shape, int32_t output_dims,
  int32_t activation);
void DivBasicFp(const int32_t* input1_shape, const float* input1_data,
  int32_t input1_dims, const float* input2_data, float* output_data,
  int32_t activation);
void BroadcastDiv6DSlow(const int32_t* input1_shape, const float* input1_data,
  int32_t input1_dims, const int32_t* input2_shape, const float* input2_data,
  int32_t input2_dims, const int32_t* output_shape, float* output_data,
  int32_t output_dims, int32_t activation);
void BroadcastDivRecursiveDimensions(int dimension, const float* input1_data,
  const float* input2_data, float* output_data, uint32_t* input1_offset_p,
  uint32_t* input2_offset_p, uint32_t* output_offset, const NdArrayDesc* desc1,
  const NdArrayDesc* desc2, const int32_t* extended_output_shape_dims);

void SliceFp(const float* input, float* output, const int32_t* begin,
  const int32_t* size_orig, const int32_t* in_shape, int32_t dims);
void StridedSliceFp(const float* input, float* output, const int32_t* begin_orig,
  const int32_t* end_orig, const int32_t* strides, const int32_t* in_shape, int32_t in_dims,
  const int32_t* out_shape, int32_t out_dims, TfLiteStridedSliceParams str_slc_prams);
void PackFp(const float **inputs, uint32_t inp_count, float *output,
  uint32_t size, uint32_t slice_size, uint32_t stride);
void TanhFp(const float* input, float* output, uint32_t size);
bool AvgpoolFp(const float* input_data, float* output_data, const int32_t* input_shape,
  const int32_t* output_shape, const int32_t* pool_params, int32_t activation);
void MinimumFp(const float* input_1, const float* input_2,  float* output,
  const int32_t* input1_shape, int32_t input1_dims, const int32_t* input2_shape,
  int32_t input2_dims, const int32_t* output_shape, int32_t output_dims);
void ReduceMaxFp(const float* input, float* output, const int32_t* in_shape, const int32_t in_num_dims,
   int32_t out_size, const int32_t* axis, const int32_t num_axis);

void Concatenation_fp32_w(const float *input, const uint16_t input_x, const uint16_t input_y,
  const uint16_t input_z, const uint16_t input_w, float *output, const uint32_t offset_w);
void Concatenation_fp32_x(const float *input, const uint16_t input_x, const uint16_t input_y,
  const uint16_t input_z, const uint16_t input_w, float *output, const uint16_t output_x, const uint32_t offset_x);
void Concatenation_fp32_y(const float *input, const uint16_t input_x, const uint16_t input_y,
  const uint16_t input_z, const uint16_t input_w, float *output, const uint16_t output_y, const uint32_t offset_y);
void Concatenation_fp32_z(const float *input, const uint16_t input_x, const uint16_t input_y,
  const uint16_t input_z, const uint16_t input_w, float *output, const uint16_t output_z, const uint32_t offset_z);

void ExpFp(const float *input, float *output, uint32_t size);
void NegFp(const float *input, float *output, uint32_t size);
void LogSoftmaxFp(const float *input, float *output, const int32_t *shape, const int32_t num_dims);
void LeakyReluFp(const float *input, float *output, uint32_t size, float alpha);
void LogFp(const float *input, float *output, uint32_t size);

void MeanFp(const float* input, float* output, const int32_t* in_shape,
  const int32_t in_num_dims, const int32_t* out_shape, int32_t out_size,
  const int32_t* axis, const int32_t num_axis, bool keep_dims);
void MeanFp_case1(const float* input_data, float* output_data, const int32_t* input_shape,
  const int32_t* output_shape);
void SumFp(const float* input, float* output, const int32_t* in_shape,
  const int32_t in_num_dims, const int32_t* out_shape, int32_t out_size,
  const int32_t* axis, const int32_t num_axis, bool keep_dims);

void PReluFp(const float *input, const int32_t *in_shape, int32_t in_dims, float *output,
  const int32_t *out_shape, int32_t out_dims, const float *alpha, const int32_t *alpha_shape,
  int32_t alpha_dims);
void ReluFp(const float *input, float *output, uint32_t size);
void Relu6Fp(const float *input, float *output,const uint32_t size);

void SpaceToBatchNdFp(const float* input1_data, const int32_t* in_shape, int32_t in_num_dims,
  float* output_data, const int32_t* out_shape, const int32_t* block_shape, const int32_t* pad);
void BatchToSpaceNdFp(const float* input1_data, const int32_t* in_shape, int32_t in_num_dims,
  float* output_data, const int32_t* out_shape, const int32_t* block_shape, const int32_t* crops);
void TransposeFp(const float* input, float* output, int32_t size, int32_t rank, int32_t* strides,
  int32_t* next_dim_sizes, int32_t* dim_sizes);
void SigmoidFp(const float* input, float* output, const uint32_t size);

void ResizeBilinearFp(const float* input_data, const int32_t* input_shape, int32_t in_dims,
  const int32_t* size_data, const int32_t* size_shape, int32_t size_dims, float* output_data,
  const int32_t* output_shape, int32_t out_dims, bool half_pixel_centers, bool align_corners);
void UpsamplingNearestNeighborFp(const float* input, const int32_t* input_shape, int32_t input_dims,
  float* output, const int32_t* output_shape, int32_t output_dims, bool align_corners, bool half_pixel_centers);
void MirrorPadFp(const float* input_data, const int32_t* input_dims, int* input_dims_num_elements,
  const int num_dims, float* output_data, const int output_size, int* output_dims_num_elements,
  const int32_t* padding_matrix, const int offset);

void PowFp(const float* input1, int32_t input1_size, const int32_t* input1_shape,
  int32_t input1_dims, const float* input2, int32_t input2_size,
  int32_t input2_dims, const int32_t* input2_shape, float* output,
  int32_t output_dims, const int32_t* output_shape);
void AbsFp(const float* input, float* output, const uint32_t size);
void PadFp(int32_t left_padding_count, int32_t *left_padding,
  int32_t right_padding_count, int32_t *right_padding,
  int32_t *ext_input_shape, const float *input_data,
  const float pad_value, const int32_t *ext_output_shape,
  float *output_data);

void SqrtFp(const float* input, float* output, uint32_t size);
void RsqrtFp(const float* input, float* output, uint32_t size);

float SquaredDifferenceFpOp(float input1, float input2);
void SquaredDifferenceBroadcast1Fp(const float* input1, const float* input2,
  float* output, int size);
void SquaredDifferenceBroadcast2Fp(const float* input1, const float* input2,
  float* output, int size);
void ElementWiseSquaredDifferenceFp(const float* input1, const float* input2,
  float* output, int size);
void BroadcastRecursiveDimensionsFp(
  const float* input1, int32_t* input1_offset_p, int32_t* compressed_input1_stride,
  const float* input2, int32_t* input2_offset_p, int32_t* compressed_input2_stride,
  float* output, int32_t* output_offset, int32_t* compressed_output_shape,
  int dimension);
void BroadcastSquaredDifference6DSlowFp(
  const float* input1, const int32_t* input1_shape, int32_t input1_dims,
  const float* input2, const int32_t* input2_shape, int32_t input2_dims,
  float* output, const int32_t* output_shape, int32_t output_dims);
void SquaredDifferenceFp(const float* input1, const int32_t* input1_shape,
  uint32_t input1_dims, uint32_t input1_size, const float* input2,
  const int32_t* input2_shape, uint32_t input2_dims, float* output,
  const int32_t* output_shape, uint32_t output_dims);

void HardSwishFp(const float* input, const int32_t* input_shape,
  int32_t input_dims, float* output);

void BroadcastComparison4DSlowImpl(const float* input_1,
  const int32_t* input1_shape, int32_t input1_dims, const float* input_2,
  const int32_t* input2_shape, int32_t input2_dims, int8_t* output,
  const int32_t* output_shape, int32_t output_dims);
void GreaterFp(const float* input1, const int32_t* input1_shape, int32_t input1_dims,
  const float* input2, const int32_t* input2_shape, int32_t input2_dims, int8_t* output,
  const int32_t* output_shape, int32_t output_dims);

void BroadcastSelect5DSlow(const float* input1, const int32_t* input1_shape,
  int32_t input1_dims, const float* input2, const int32_t* input2_shape,
  int32_t input2_dims, const int8_t* condition, const int32_t* condition_shape,
  int32_t condition_dims, float* output, const int32_t* output_shape,
  int32_t output_dims);
void SelectV2Fp(const float* input1, const int32_t* input1_shape, int32_t input1_dims,
  const float* input2, const int32_t* input2_shape, int32_t input2_dims,
  const int8_t* condition, const int32_t* condition_shape, int32_t condition_dims,
  float* output, const int32_t* output_shape, int32_t output_dims);

float TfLiteExpm1(float x);
void EluFp(const float* input_data, const int32_t* input_shape,
  int32_t input_dims, float* output_data);
void GatherFp(const float* input, const int32_t* input_shape,
  int32_t input_dims, const int32_t* coords, const int32_t* coords_shape,
  int32_t coords_dims, int32_t axis, int32_t batch_dims, float *output);
void MaximumFp(const float* input_1, const float* input_2,  float* output,
  const int32_t* input1_shape, int32_t input1_dims, const int32_t* input2_shape,
  int32_t input2_dims, const int32_t* output_shape, int32_t output_dims);

#endif   /*  __KERNEL_LIBRARY_FP32__ */
