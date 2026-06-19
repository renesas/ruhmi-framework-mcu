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

#include "kernel_library_fp32.h"

/****************************************************************************/
/*                     Floating Point Utility Functions                     */
/****************************************************************************/

void CalculateActivationRangeFp(FusedActivation activation,
                              float* activation_min, float* activation_max) {
  if (activation == ActRelu) {
    *activation_min = 0;
    *activation_max = FLT_MAX;
  } else if (activation == ActRelu6) {
    *activation_min = 0;
    *activation_max = 6;
  } else if (activation == ActReluN1To1) {
    *activation_min = -1;
    *activation_max = 1;
  } else {
    *activation_min = -FLT_MAX;
    *activation_max = FLT_MAX;
  }
}

inline float ActivationFunctionWithMinMaxFp(float x, float output_activation_min,
                                      float output_activation_max) {
  x = (x > output_activation_min ) ? x : output_activation_min;
  x = (x < output_activation_max ) ? x : output_activation_max;
  return x;
}

inline void ComputeInterpolationValues(const float value, const float scale,
  const bool half_pixel_centers, int32_t input_size, float* scaled_value,
  int32_t* lower_bound, int32_t* upper_bound) {
  if (half_pixel_centers) {
    *scaled_value = (value + 0.5f) * scale - 0.5f;
  } else {
    *scaled_value = value * scale;
  }
  float scaled_value_floor = floor(*scaled_value);
  *lower_bound = ((int32_t) scaled_value_floor > (int32_t) 0) ?
          ((int32_t) scaled_value_floor) : ((int32_t) 0);
  *upper_bound = ((int32_t) (ceil(*scaled_value)) < input_size - 1) ?
          ( (int32_t) (ceil(*scaled_value))) : (input_size - 1);
}

/****************************************************************************/
/*                          Floating Point Operators                        */
/****************************************************************************/

// Ported from TF
void ConvFp(const float* input_data, float* output_data, const int32_t* input_shape,
  const int32_t* output_shape, const int32_t* filter_shape, const float* filter_data,
  const int32_t* bias_shape, const float* bias_data, const int32_t* conv_params,
  int32_t activation) {
  (void)bias_shape;
  const int stride_width = conv_params[0];
  const int stride_height = conv_params[1];
  const int dilation_width_factor = conv_params[2];
  const int dilation_height_factor = conv_params[3];
  const int pad_width = conv_params[4];
  const int pad_height = conv_params[5];
  float output_activation_min;
  float output_activation_max;

  CalculateActivationRangeFp(activation, &output_activation_min, &output_activation_max);

  const int batches = input_shape[0];
  const int input_depth = input_shape[3];
  const int output_depth = output_shape[3];
  const int input_height = input_shape[1];
  const int input_width = input_shape[2];
  const int filter_height = filter_shape[1];
  const int filter_width = filter_shape[2];
  const int filter_input_depth = filter_shape[3];
  const int groups = input_depth / filter_input_depth;
  const int filters_per_group = output_depth / groups;
  const int output_height = output_shape[1];
  const int output_width = output_shape[2];

  for (int batch = 0; batch < batches; ++batch) {
    for (int out_y = 0; out_y < output_height; ++out_y) {
      const int in_y_origin = (out_y * stride_height) - pad_height;
      for (int out_x = 0; out_x < output_width; ++out_x) {
        const int in_x_origin = (out_x * stride_width) - pad_width;
        for (int out_channel = 0; out_channel < output_depth; ++out_channel) {
          int group = out_channel / filters_per_group;
          float total = 0.f;
          for (int filter_y = 0; filter_y < filter_height; ++filter_y) {
            const int in_y = in_y_origin + dilation_height_factor * filter_y;
            for (int filter_x = 0; filter_x < filter_width; ++filter_x) {
              const int in_x = in_x_origin + dilation_width_factor * filter_x;

              // Zero padding by omitting the areas outside the image.
              const bool is_point_inside_image =
                  (in_x >= 0) && (in_x < input_width) && (in_y >= 0) &&
                  (in_y < input_height);

              if (!is_point_inside_image) {
                continue;
              }
              for (int in_channel = 0; in_channel < filter_input_depth;
                   ++in_channel) {
                float input_value =
                    input_data[Offset(input_shape, batch, in_y, in_x,
                                      in_channel + group * filter_input_depth)];
                float filter_value = filter_data[Offset(
                    filter_shape, out_channel, filter_y, filter_x, in_channel)];
                total += (input_value * filter_value);
              }
            }
          }
          float bias_value = 0.0f;
          if (bias_data) {
            bias_value = bias_data[out_channel];
          }
          output_data[Offset(output_shape, batch, out_y, out_x, out_channel)] =
              ActivationFunctionWithMinMaxFp(total + bias_value,
                                           output_activation_min,
                                           output_activation_max);
        }
      }
    }
  }
}

// Ported from TF
void DepthWiseConvFp(const float* input_data, float* output_data, const int32_t* input_shape,
  const int32_t* output_shape, const int32_t* filter_shape, const float* filter_data,
  const int32_t* bias_shape, const float* bias_data, const int32_t* conv_params,
  int32_t activation) {
  (void)bias_shape;
  const int stride_width = conv_params[0];
  const int stride_height = conv_params[1];
  const int dilation_width_factor = conv_params[2];
  const int dilation_height_factor = conv_params[3];
  const int pad_width = conv_params[4];
  const int pad_height = conv_params[5];
  const int depth_multiplier = conv_params[6];
  float output_activation_min;
  float output_activation_max;

  CalculateActivationRangeFp(activation, &output_activation_min, &output_activation_max);

  const int batches = input_shape[0];
  const int input_depth = input_shape[3];
  const int input_height = input_shape[1];
  const int input_width = input_shape[2];
  const int filter_height = filter_shape[1];
  const int filter_width = filter_shape[2];
  const int output_height = output_shape[1];
  const int output_width = output_shape[2];

  for (int b = 0; b < batches; ++b) {
    for (int out_y = 0; out_y < output_height; ++out_y) {
      for (int out_x = 0; out_x < output_width; ++out_x) {
        for (int ic = 0; ic < input_depth; ++ic) {
          for (int m = 0; m < depth_multiplier; m++) {
            const int oc = m + ic * depth_multiplier;
            const int in_x_origin = (out_x * stride_width) - pad_width;
            const int in_y_origin = (out_y * stride_height) - pad_height;
            float total = 0.f;
            for (int filter_y = 0; filter_y < filter_height; ++filter_y) {
              for (int filter_x = 0; filter_x < filter_width; ++filter_x) {
                const int in_x = in_x_origin + dilation_width_factor * filter_x;
                const int in_y =
                    in_y_origin + dilation_height_factor * filter_y;
                // If the location is outside the bounds of the input image,
                // use zero as a default value.
                if ((in_x >= 0) && (in_x < input_width) && (in_y >= 0) &&
                    (in_y < input_height)) {
                  float input_value =
                      input_data[Offset(input_shape, b, in_y, in_x, ic)];
                  float filter_value = filter_data[Offset(
                      filter_shape, 0, filter_y, filter_x, oc)];
                  total += (input_value * filter_value);
                }
              }
            }
            float bias_value = 0.0f;
            if (bias_data) {
              bias_value = bias_data[oc];
            }
            output_data[Offset(output_shape, b, out_y, out_x, oc)] =
                ActivationFunctionWithMinMaxFp(total + bias_value,
                                             output_activation_min,
                                             output_activation_max);
          }
        }
      }
    }
  }
}

// Ported from TF
void TransposeConvFp(const float* input_data, float* output_data, const int32_t* input_shape,
  const int32_t* output_shape, const int32_t* filter_shape, const float* filter_data,
  const int32_t* conv_params, int32_t activation, const float* bias_data) {

  const int stride_width = conv_params[0];
  const int stride_height = conv_params[1];
  const int pad_width = conv_params[2];
  const int pad_height = conv_params[3];
  float output_activation_min;
  float output_activation_max;

  CalculateActivationRangeFp(activation, &output_activation_min, &output_activation_max);

  const int batches = input_shape[0];
  const int input_depth = input_shape[3];
  const int output_depth = output_shape[3];
  const int input_height = input_shape[1];
  const int input_width = input_shape[2];
  const int filter_height = filter_shape[1];
  const int filter_width = filter_shape[2];
  const int output_height = output_shape[1];
  const int output_width = output_shape[2];

  // Although transpose convolution simplifies to convolution with transposed
  // weights for strides of 1, non-unitary striding complicates matters. To
  // keep this reference implementation as clear as possible, we use a
  // "scatter" access pattern, where we loop through all the input elements,
  // computing their influence on the output, rather than looping through the
  // output elements in the typical "gather" access pattern of a conv. We
  // therefore must initialize the output array to zero.
  const int num_elements = FlatSize(output_shape, 4);
  for (int i = 0; i < num_elements; i++) {
    output_data[i] = 0.0f;
  }

  // Loop through input elements one at a time.
  for (int batch = 0; batch < batches; ++batch) {
    for (int in_y = 0; in_y < input_height; ++in_y) {
      for (int in_x = 0; in_x < input_width; ++in_x) {
        for (int in_channel = 0; in_channel < input_depth; ++in_channel) {
          // Loop through the output elements it will influence
          const int out_x_origin = (in_x * stride_width) - pad_width;
          const int out_y_origin = (in_y * stride_height) - pad_height;
          for (int filter_y = 0; filter_y < filter_height; ++filter_y) {
            for (int filter_x = 0; filter_x < filter_width; ++filter_x) {
              for (int out_channel = 0; out_channel < output_depth;
                   ++out_channel) {
                // Compute output element location
                const int out_x = out_x_origin + filter_x;
                const int out_y = out_y_origin + filter_y;
                // We cannot accumulate out of bounds
                if ((out_x >= 0) && (out_x < output_width) && (out_y >= 0) &&
                    (out_y < output_height)) {
                  float input_value = input_data[Offset(
                      input_shape, batch, in_y, in_x, in_channel)];
                  float filter_value =
                      filter_data[Offset(filter_shape, out_channel, filter_y,
                                         filter_x, in_channel)];
                  output_data[Offset(output_shape, batch, out_y, out_x,
                                     out_channel)] +=
                      input_value * filter_value;
                }
              }
            }
          }
        }
      }
    }
  }

  for (int batch = 0; batch < batches; ++batch) {
    for (int out_y = 0; out_y < output_height; ++out_y) {
      for (int out_x = 0; out_x < output_width; ++out_x) {
        for (int out_channel = 0; out_channel < output_depth; ++out_channel) {
          float acc = output_data[Offset(output_shape, batch, out_y, out_x,
                                         out_channel)];
          if (bias_data) acc += bias_data[out_channel];

          output_data[Offset(output_shape, batch, out_y, out_x, out_channel)] =
              ActivationFunctionWithMinMaxFp(acc, output_activation_min,
                                           output_activation_max);
        }
      }
    }
  }
}

// Ported from TF
void FullyConnectedFp(const float* input_data, float* output_data, const int32_t* input_shape,
  const int32_t* output_shape, int32_t output_dims_count, const int32_t* weights_shape,
  int32_t weights_dims_count, const float* weights_data, const int32_t* bias_shape,
  const float* bias_data, int32_t activation) {
  (void)input_shape;
  (void)bias_shape;
  float output_activation_min;
  float output_activation_max;

  CalculateActivationRangeFp(activation, &output_activation_min, &output_activation_max);

  const int batches = FlatSizeSkipDim(output_shape, output_dims_count, output_dims_count - 1);
  const int output_depth = weights_shape[weights_dims_count - 2];
  const int accum_depth = weights_shape[weights_dims_count - 1];
  for (int b = 0; b < batches; ++b) {
    for (int out_c = 0; out_c < output_depth; ++out_c) {
      float total = 0.f;
      for (int d = 0; d < accum_depth; ++d) {
        total += input_data[b * accum_depth + d] *
                 weights_data[out_c * accum_depth + d];
      }
      float bias_value = 0.0f;
      if (bias_data) {
        bias_value = bias_data[out_c];
      }
      output_data[out_c + output_depth * b] = ActivationFunctionWithMinMaxFp(
          total + bias_value, output_activation_min, output_activation_max);
    }
  }
}

// Ported from TF
void SoftmaxFp(const float* input_data, float* output_data, const int32_t* input_shape,
  int32_t input_dims_count, const int32_t* output_shape, int32_t beta) {
  (void)output_shape;
  const int trailing_dim = input_dims_count - 1;
  const int outer_size = FlatSizeSkipDim(input_shape, input_dims_count, trailing_dim);
  const int depth = input_shape[trailing_dim];

  for (int i = 0; i < outer_size; ++i) {
    float max = -FLT_MAX;
    for (int c = 0; c < depth; ++c) {
      float input_value = input_data[i * depth + c];
      max =  max > input_value ? max : input_value;
    }

    // Compute sum.
    float sum = 0.f;
    for (int c = 0; c < depth; ++c) {
      const float exp_c = exp((input_data[i * depth + c] - max) * (float)beta);
      output_data[i * depth + c] = exp_c;
      sum += exp_c;
    }

    // Compute result.
    for (int c = 0; c < depth; ++c) {
      output_data[i * depth + c] = output_data[i * depth + c] / sum;
    }
  }
}

// Ported from TF
void MaxpoolFp(const float* input_data, float* output_data, const int32_t* input_shape,
  const int32_t* output_shape, const int32_t* pool_params, int32_t activation) {
  float output_activation_min;
  float output_activation_max;
  CalculateActivationRangeFp(activation, &output_activation_min, &output_activation_max);

  const int batches = input_shape[0];
  const int depth = input_shape[3];
  const int input_height = input_shape[1];
  const int input_width = input_shape[2];
  const int output_height = output_shape[1];
  const int output_width = output_shape[2];
  const int stride_height = pool_params[3];
  const int stride_width = pool_params[2];
  for (int batch = 0; batch < batches; ++batch) {
    for (int out_y = 0; out_y < output_height; ++out_y) {
      for (int out_x = 0; out_x < output_width; ++out_x) {
        for (int channel = 0; channel < depth; ++channel) {
          const int in_x_origin =
              (out_x * stride_width) - pool_params[4];
          const int in_y_origin =
              (out_y * stride_height) - pool_params[5];
          const int filter_x_start = (0 > -in_x_origin) ? 0 : -in_x_origin;
          const int filter_x_end =
              (pool_params[0] < input_width - in_x_origin) ? pool_params[0] : input_width - in_x_origin;
          const int filter_y_start = (0 > -in_y_origin) ? 0 : -in_y_origin;
          const int filter_y_end =
              (pool_params[1] < input_height - in_y_origin) ? pool_params[1] : input_height - in_y_origin;
          float max = -FLT_MAX;
          for (int filter_y = filter_y_start; filter_y < filter_y_end;
               ++filter_y) {
            for (int filter_x = filter_x_start; filter_x < filter_x_end;
                 ++filter_x) {
              const int in_x = in_x_origin + filter_x;
              const int in_y = in_y_origin + filter_y;
              max = (max > input_data[Offset(input_shape, batch, in_y, in_x, channel)]) ? max : \
                          input_data[Offset(input_shape, batch, in_y, in_x, channel)];
            }
          }
          output_data[Offset(output_shape, batch, out_y, out_x, channel)] =
              ActivationFunctionWithMinMaxFp(max, output_activation_min,
                                           output_activation_max);
        }
      }
    }
  }
}

// Ported from TF
void AddFp(const float* input1_data, const float* input2_data, float* output_data,
  const int32_t* input1_shape, int32_t input1_dims, const int32_t* input2_shape,
  int32_t input2_dims, const int32_t* output_shape, int32_t output_dims,
  int32_t activation) {

  if (HaveSameShapes(input1_shape, input1_dims, input2_shape, input2_dims)) {
    AddBasicFp(input1_shape, input1_data, input1_dims, input2_data, output_data,
      activation);
  } else {
    BroadcastAdd6DSlowFp(input1_shape, input1_data, input1_dims, input2_shape,
      input2_data, input2_dims, output_shape, output_data, output_dims, activation);
  }
}

// Supporting function for Add op
void AddBasicFp(const int32_t* input1_shape, const float* input1_data,
  int32_t input1_dims, const float* input2_data, float* output_data,
  int32_t activation) {
  float output_activation_min;
  float output_activation_max;
  CalculateActivationRangeFp(activation, &output_activation_min, &output_activation_max);

  const int flat_size = FlatSize(input1_shape, input1_dims);
  for (int i = 0; i < flat_size; ++i) {
    output_data[i] = ActivationFunctionWithMinMaxFp(
        input1_data[i] + input2_data[i], output_activation_min, output_activation_max);
  }
}

// Supporting function for Add op
void BroadcastAdd6DSlowFp(const int32_t* input1_shape, const float* input1_data,
  int32_t input1_dims, const int32_t* input2_shape, const float* input2_data,
  int32_t input2_dims, const int32_t* output_shape, float* output_data,
  int32_t output_dims, int32_t activation) {
  (void)output_shape;
  (void)output_dims;
  int32_t compressed_input1_stride[kMaxBroadcastDim];
  int32_t compressed_input2_stride[kMaxBroadcastDim];
  int32_t compressed_output_shape[kMaxBroadcastDim] = {1, 1, 1, 1, 1, 1};
  bool broadcastable_shape = ReduceDimensionsForBroadcastFp(
      input1_shape, input1_dims, input2_shape, input2_dims, compressed_input1_stride,
      compressed_input2_stride, compressed_output_shape);
  // Skip broadcasting for degenerate shapes.
  if (!broadcastable_shape) {
    return;
  }

  int32_t input1_offset = 0;
  int32_t input2_offset = 0;
  int32_t output_offset = 0;
  BroadcastAddRecursiveDimensionsFp(kMaxBroadcastDim - 1, &input1_offset,
    &input2_offset, &output_offset, compressed_input1_stride, compressed_input2_stride,
    compressed_output_shape, activation, input1_data, input2_data, output_data);
}

// Supporting function for Add, SquaredDifference ops
bool ReduceDimensionsForBroadcastFp(const int32_t* input1_dims, int32_t num_input1_dims,
  const int32_t* input2_dims, int32_t num_input2_dims, int32_t* compressed_input1_stride,
  int32_t* compressed_input2_stride, int32_t* compressed_output_shape) {

  int num_compressed_dims = 0;
  int compressed_input1_shape[kMaxBroadcastDim] = {1, 1, 1, 1, 1, 1};
  int compressed_input2_shape[kMaxBroadcastDim] = {1, 1, 1, 1, 1, 1};
  bool broadcast_input1 = false;
  bool broadcast_input2 = false;
  bool first_nonunit = true;
  const int32_t num_common_dims = (num_input1_dims < num_input2_dims) ? num_input1_dims
                                      : num_input2_dims;
  for (int32_t i = 1; i <= num_common_dims; i++) {
    const int32_t input1_dim = input1_dims[num_input1_dims - i];
    const int32_t input2_dim = input2_dims[num_input2_dims - i];
    if (input1_dim == 0 || input2_dim == 0) {
      return false;
    }
    if (input1_dim == 1 && input2_dim == 1) {
      continue;
    }

    if (input1_dim == 1) {
      if (!broadcast_input1) {
        broadcast_input1 = true;
        broadcast_input2 = false;
        num_compressed_dims++;
      }
      compressed_input2_shape[num_compressed_dims - 1] *= input2_dim;
      compressed_output_shape[num_compressed_dims - 1] *= input2_dim;
    } else if (input2_dim == 1) {
      if (!broadcast_input2) {
        broadcast_input1 = false;
        broadcast_input2 = true;
        num_compressed_dims++;
      }
      compressed_input1_shape[num_compressed_dims - 1] *= input1_dim;
      compressed_output_shape[num_compressed_dims - 1] *= input1_dim;
    } else {
      if (broadcast_input1 || broadcast_input2 || first_nonunit) {
        broadcast_input1 = false;
        broadcast_input2 = false;
        num_compressed_dims++;
      }
      compressed_input1_shape[num_compressed_dims - 1] *= input1_dim;
      compressed_input2_shape[num_compressed_dims - 1] *= input1_dim;
      compressed_output_shape[num_compressed_dims - 1] *= input1_dim;
    }
    first_nonunit = false;
  }
  if (num_input1_dims > num_input2_dims) {
    if (!broadcast_input2) {
      num_compressed_dims++;
    }
    for (int32_t i = 0; i < num_input1_dims - num_input2_dims; i++) {
      const int32_t input1_dim = input1_dims[i];
      if (input1_dim == 0) {
        return false;
      }
      compressed_input1_shape[num_compressed_dims - 1] *= input1_dim;
      compressed_output_shape[num_compressed_dims - 1] *= input1_dim;
    }
  } else if (num_input2_dims > num_input1_dims) {
    if (!broadcast_input1) {
      num_compressed_dims++;
    }
    for (int32_t i = 0; i < num_input2_dims - num_input1_dims; i++) {
      const int32_t input2_dim = input2_dims[i];
      if (input2_dim == 0) {
        return false;
      }
      compressed_input2_shape[num_compressed_dims - 1] *= input2_dim;
      compressed_output_shape[num_compressed_dims - 1] *= input2_dim;
    }
  }
  num_compressed_dims = (num_compressed_dims > 1) ? num_compressed_dims : 1;

  int input1_stride = 1;
  int input2_stride = 1;
  for (int i = 0; i < kMaxBroadcastDim; ++i) {
    compressed_input1_stride[i] = input1_stride;
    input1_stride *= compressed_input1_shape[i];
    compressed_input2_stride[i] = input2_stride;
    input2_stride *= compressed_input2_shape[i];
  }
  for (int i = 0; i < kMaxBroadcastDim; ++i) {
    if (compressed_input1_shape[i] != compressed_input2_shape[i]) {
      if (compressed_input1_shape[i] == 1) {
        compressed_input1_stride[i] = 0;
      } else {
        compressed_input2_stride[i] = 0;
      }
    }
  }
  return true;
}

// Supporting function for Add op
inline void BroadcastAddRecursiveDimensionsFp(
    int dimension, int32_t* input1_offset_p, int32_t* input2_offset_p,
    int32_t* output_offset, int32_t* compressed_input1_stride,
    int32_t* compressed_input2_stride, int32_t* compressed_output_shape,
    int32_t activation, const float* input1_data, const float* input2_data,
    float* output_data) {
  if (dimension > 0) {
    for (int32_t c = 0; c < compressed_output_shape[dimension]; ++c) {
      int32_t input1_offset_c = *input1_offset_p;
      int32_t input2_offset_c = *input2_offset_p;
      BroadcastAddRecursiveDimensionsFp(
          dimension - 1, &input1_offset_c, &input2_offset_c, output_offset,
          compressed_input1_stride, compressed_input2_stride,
          compressed_output_shape, activation, input1_data,
          input2_data, output_data);
      *input1_offset_p += compressed_input1_stride[dimension];
      *input2_offset_p += compressed_input2_stride[dimension];
    }
  } else {
    bool input1_is_broadcast = compressed_input1_stride[dimension] == 0;
    bool input2_is_broadcast = compressed_input2_stride[dimension] == 0;
    const float* input1_data_ptr = input1_data + *input1_offset_p;
    const float* input2_data_ptr = input2_data + *input2_offset_p;
    float* output_data_ptr = output_data + *output_offset;
    if (input1_is_broadcast) {
      // input1 is broadcast.
      AddBroadcastFp(input2_data_ptr, input1_data_ptr, output_data_ptr,
                      compressed_output_shape[dimension], activation);
      *input2_offset_p += compressed_output_shape[dimension];
    } else if (input2_is_broadcast) {
      // input2 is broadcast.
      AddBroadcastFp(input1_data_ptr, input2_data_ptr, output_data_ptr,
                      compressed_output_shape[dimension], activation);
      *input1_offset_p += compressed_output_shape[dimension];
    } else {
      // Add element-wise.
      AddElementwiseFp(input1_data_ptr, input2_data_ptr, output_data_ptr,
                        compressed_output_shape[dimension], activation);
      *input1_offset_p += compressed_output_shape[dimension];
      *input2_offset_p += compressed_output_shape[dimension];
    }
    *output_offset += compressed_output_shape[dimension];
  }
}

// Supporting function for Add op
inline void AddBroadcastFp(const float* input_data, const float* broadcast_data,
                         float* output_data, int32_t size, int32_t activation) {
  float output_activation_min;
  float output_activation_max;
  CalculateActivationRangeFp(activation, &output_activation_min, &output_activation_max);

  for (int32_t c = 0; c < size; ++c) {
    output_data[c] = ActivationFunctionWithMinMaxFp(
        input_data[c] + broadcast_data[0], output_activation_min, output_activation_max);
  }
}

// Supporting function for Add op
void AddElementwiseFp(const float* input1_data, const float* input2_data, float* output_data,
                    int32_t size, int32_t activation) {
  float output_activation_min;
  float output_activation_max;
  CalculateActivationRangeFp(activation, &output_activation_min, &output_activation_max);

  for (int32_t c = 0; c < size; ++c) {
    output_data[c] = ActivationFunctionWithMinMaxFp(
        input1_data[c] + input2_data[c], output_activation_min, output_activation_max);
  }
}

// Ported from TF
void SubFp(const float* input1_data, const float* input2_data, float* output_data,
  const int32_t* input1_shape, int32_t input1_dims, const int32_t* input2_shape,
  int32_t input2_dims, const int32_t* output_shape, int32_t output_dims,
  int32_t activation) {

  if (HaveSameShapes(input1_shape, input1_dims, input2_shape, input2_dims)) {
    SubBasicFp(input1_shape, input1_data, input1_dims, input2_data, output_data,
      activation);
  } else {
    BroadcastSubSlow(input1_shape, input1_data, input1_dims, input2_shape,
      input2_data, input2_dims, output_shape, output_data, output_dims, activation);
  }
}

// Supporting function for Sub op
void SubBasicFp(const int32_t* input1_shape, const float* input1_data,
  int32_t input1_dims, const float* input2_data, float* output_data,
  int32_t activation) {
  float output_activation_min;
  float output_activation_max;
  CalculateActivationRangeFp(activation, &output_activation_min, &output_activation_max);

  const int flat_size = FlatSize(input1_shape, input1_dims);
  for (int i = 0; i < flat_size; ++i) {
    output_data[i] = ActivationFunctionWithMinMaxFp(
        input1_data[i] - input2_data[i], output_activation_min, output_activation_max);
  }
}

void BroadcastSubSlow(const int32_t* input1_shape, const float* input1_data,
  int32_t input1_dims, const int32_t* input2_shape, const float* input2_data,
  int32_t input2_dims, const int32_t* output_shape, float* output_data,
  int32_t output_dims, int32_t activation) {
  (void)output_shape;
  (void)output_dims;
  int32_t compressed_input1_stride[kMaxBroadcastDim];
  int32_t compressed_input2_stride[kMaxBroadcastDim];
  int32_t compressed_output_shape[kMaxBroadcastDim] = {1, 1, 1, 1, 1, 1};
  bool broadcastable_shape = ReduceDimensionsForBroadcastFp(
      input1_shape, input1_dims, input2_shape, input2_dims, compressed_input1_stride,
      compressed_input2_stride, compressed_output_shape);
  // Skip broadcasting for degenerate shapes.
  if (!broadcastable_shape) {
    return;
  }

  int32_t input1_offset = 0;
  int32_t input2_offset = 0;
  int32_t output_offset = 0;
  BroadcastSubRecursiveDimensionsFp(kMaxBroadcastDim - 1, &input1_offset,
    &input2_offset, &output_offset, compressed_input1_stride, compressed_input2_stride,
    compressed_output_shape, activation, input1_data, input2_data, output_data);
}

// Supporting function for Sub op
inline void BroadcastSubRecursiveDimensionsFp(
    int dimension, int32_t* input1_offset_p, int32_t* input2_offset_p,
    int32_t* output_offset, int32_t* compressed_input1_stride,
    int32_t* compressed_input2_stride, int32_t* compressed_output_shape,
    int32_t activation, const float* input1_data, const float* input2_data,
    float* output_data) {
  if (dimension > 0) {
    for (int32_t c = 0; c < compressed_output_shape[dimension]; ++c) {
      int32_t input1_offset_c = *input1_offset_p;
      int32_t input2_offset_c = *input2_offset_p;
      BroadcastSubRecursiveDimensionsFp(
          dimension - 1, &input1_offset_c, &input2_offset_c, output_offset,
          compressed_input1_stride, compressed_input2_stride,
          compressed_output_shape, activation, input1_data,
          input2_data, output_data);
      *input1_offset_p += compressed_input1_stride[dimension];
      *input2_offset_p += compressed_input2_stride[dimension];
    }
  } else {
    bool input1_is_broadcast = compressed_input1_stride[dimension] == 0;
    bool input2_is_broadcast = compressed_input2_stride[dimension] == 0;
    const float* input1_data_ptr = input1_data + *input1_offset_p;
    const float* input2_data_ptr = input2_data + *input2_offset_p;
    float* output_data_ptr = output_data + *output_offset;
    if (input1_is_broadcast) {
      // input1 is broadcast.
      SubBroadcast1Fp(input1_data_ptr, input2_data_ptr, output_data_ptr,
                      compressed_output_shape[dimension], activation);
      *input2_offset_p += compressed_output_shape[dimension];
    } else if (input2_is_broadcast) {
      // input2 is broadcast.
      SubBroadcast2Fp(input1_data_ptr, input2_data_ptr, output_data_ptr,
                      compressed_output_shape[dimension], activation);
      *input1_offset_p += compressed_output_shape[dimension];
    } else {
      // Sub element-wise.
      SubElementwiseFp(input1_data_ptr, input2_data_ptr, output_data_ptr,
                        compressed_output_shape[dimension], activation);
      *input1_offset_p += compressed_output_shape[dimension];
      *input2_offset_p += compressed_output_shape[dimension];
    }
    *output_offset += compressed_output_shape[dimension];
  }
}

// Supporting function for Sub op
inline void SubBroadcast1Fp(const float* input_data, const float* broadcast_data,
                         float* output_data, int32_t size, int32_t activation) {
  float output_activation_min;
  float output_activation_max;
  CalculateActivationRangeFp(activation, &output_activation_min, &output_activation_max);

  for (int32_t c = 0; c < size; ++c) {
    output_data[c] = ActivationFunctionWithMinMaxFp(
        input_data[0] - broadcast_data[c], output_activation_min, output_activation_max);
  }
}

// Supporting function for Sub op
inline void SubBroadcast2Fp(const float* input_data, const float* broadcast_data,
                         float* output_data, int32_t size, int32_t activation) {
  float output_activation_min;
  float output_activation_max;
  CalculateActivationRangeFp(activation, &output_activation_min, &output_activation_max);

  for (int32_t c = 0; c < size; ++c) {
    output_data[c] = ActivationFunctionWithMinMaxFp(
        input_data[c] - broadcast_data[0], output_activation_min, output_activation_max);
  }
}

// Supporting function for Sub op
void SubElementwiseFp(const float* input1_data, const float* input2_data, float* output_data,
                    int32_t size, int32_t activation) {
  float output_activation_min;
  float output_activation_max;
  CalculateActivationRangeFp(activation, &output_activation_min, &output_activation_max);

  for (int32_t c = 0; c < size; ++c) {
    output_data[c] = ActivationFunctionWithMinMaxFp(
        input1_data[c] - input2_data[c], output_activation_min, output_activation_max);
  }
}

// Ported from TF
void MulFp(const float* input1_data, const float* input2_data, float* output_data,
  const int32_t* input1_shape, int32_t input1_dims, const int32_t* input2_shape,
  int32_t input2_dims, const int32_t* output_shape, int32_t output_dims,
  int32_t activation) {
  int32_t broadcast_category;
  if (ProcessBroadcastShapes(input1_shape, input1_dims, input2_shape, input2_dims,
        &broadcast_category)) {
    BroadcastMul6DSlow(input1_shape, input1_data, input1_dims, input2_shape, input2_data,
      input2_dims, output_shape, output_data, output_dims, activation);
  } else {
    MulBasicFp(input1_shape, input1_data, input1_dims, input2_data, output_data,
      activation);
  }
}

// Supporting function for Mul op
bool ProcessBroadcastShapes(const int32_t* input1, int32_t input1_dims,
  const int32_t* input2, int32_t input2_dims, int32_t* broadcast_category) {

  const int dims_count = input1_dims > input2_dims ? input1_dims : input2_dims;
  *broadcast_category = kGenericBroadcast;

  int32_t extended_shape0[dims_count];
  int32_t extended_shape1[dims_count];
  ExtendedShape(input1, input1_dims, extended_shape0, dims_count);
  ExtendedShape(input2, input2_dims, extended_shape1, dims_count);

  // Check for "exact" match, implicitly accepting any scalar shapes.
  if (memcmp(extended_shape0, extended_shape1, dims_count * sizeof(int32_t)) == 0) {
    *broadcast_category = kNonBroadcast;
    return false;
  }

  for (int i = dims_count - 1; i >= 0; --i) {
    if (extended_shape0[i] == extended_shape1[i]) {
      continue;
    } else if (extended_shape0[i] == 1) {
      *broadcast_category = kFirstInputBroadcastsFast;
      break;
    } else if (extended_shape1[i] == 1) {
      *broadcast_category = kSecondInputBroadcastsFast;
      break;
    } else {
      // This case is erroneous: there is a dimension that does not match and
      // is not a broadcast from one shape to the other.
      *broadcast_category = kGenericBroadcast;
      return true;
    }
  }

  if (*broadcast_category != kFirstInputBroadcastsFast &&
      *broadcast_category != kSecondInputBroadcastsFast) {
    // This is unreachable because at least one else clause in the above loop
    // must be reached.
    *broadcast_category = kNonBroadcast;
    return false;
  }

  // From this point it is assumed contractually that corresponding dimensions
  // in shape0 and shape1 are either (a) equal or (b) one or other equals 1.
  const bool swap_inputs = *broadcast_category == kSecondInputBroadcastsFast;
  const int32_t* shape_a = swap_inputs ? extended_shape1 : extended_shape0;
  const int32_t* shape_b = swap_inputs ? extended_shape0 : extended_shape1;

  int i = dims_count - 1;
  int broadcast_shape[5];
  broadcast_shape[0] = 1;
  broadcast_shape[1] = 1;
  broadcast_shape[2] = 1;
  broadcast_shape[3] = 1;
  broadcast_shape[4] = 1;
  // y_0 is greedy: include dims if both or neither equal 1: in other words,
  // test for equality rather than (shape_a->Dims(i) != 1).
  while (i >= 0 && shape_a[i] == shape_b[i]) {
    broadcast_shape[4] *= shape_b[i];
    --i;
  }
  // Here either input_a or input_b has dim of 1 (if i >= 0).  If it is input_b
  // that has the unit dimension, the next two loops are not entered.
  while (i >= 0 && shape_a[i] == 1) {
    broadcast_shape[3] *= shape_b[i];
    --i;
  }
  while (i >= 0 && shape_a[i] == shape_b[i]) {
    broadcast_shape[2] *= shape_a[i];
    --i;
  }
  // Here either input_a or input_b has dim of 1 (if i >= 0).
  while (i >= 0 && shape_b[i] == 1) {
    broadcast_shape[1] *= shape_a[i];
    --i;
  }
  while (i >= 0 && shape_a[i] == shape_b[i]) {
    broadcast_shape[0] *= shape_b[i];
    --i;
  }

  // Rarer case is when the broadcast dimensions cannot be handled by a fivefold
  // loop.
  if (i >= 0) {
    *broadcast_category = kGenericBroadcast;
  }
  return true;
}

// Supporting function for Mul op
void MulBasicFp(const int32_t* input1_shape, const float* input1_data,
  int32_t input1_dims, const float* input2_data, float* output_data,
  int32_t activation) {
  (void)activation;
  const int flat_size = FlatSize(input1_shape, input1_dims);
  for (int i = 0; i < flat_size; ++i) {
    output_data[i] = input1_data[i] * input2_data[i];
  }
}

// Supporting function for Mul op
void BroadcastMul6DSlow(const int32_t* input1_shape, const float* input1_data,
  int32_t input1_dims, const int32_t* input2_shape, const float* input2_data,
  int32_t input2_dims, const int32_t* output_shape, float* output_data,
  int32_t output_dims, int32_t activation) {
  (void)activation;
  NdArrayDesc desc1, desc2;
  NdArrayDescsForElementwiseBroadcast(input1_shape, input1_dims, input2_shape,
    input2_dims, &desc1, &desc2, kMaxMulBroadcastDim);

  int32_t extended_output_shape_dims[kMaxMulBroadcastDim];
  ExtendedShape(output_shape, output_dims, extended_output_shape_dims, kMaxMulBroadcastDim);

  uint32_t input1_offset = 0;
  uint32_t input2_offset = 0;
  uint32_t output_offset = 0;
  BroadcastMulRecursiveDimensions( 0, input1_data, input2_data, output_data,
    &input1_offset, &input2_offset, &output_offset, &desc1, &desc2,
    extended_output_shape_dims);
}

// Supporting function for Mul op
void BroadcastMulRecursiveDimensions(int dimension, const float* input1_data,
  const float* input2_data, float* output_data, uint32_t* input1_offset_p,
  uint32_t* input2_offset_p, uint32_t* output_offset, const NdArrayDesc* desc1,
  const NdArrayDesc* desc2, const int32_t* extended_output_shape_dims) {
  if (dimension == kMaxMulBroadcastDim - 1) {
    for (int c = 0; c < extended_output_shape_dims[dimension]; ++c) {
      const float input1_val = input1_data[*input1_offset_p];
      const float input2_val = input2_data[*input2_offset_p];
      output_data[*output_offset] = input1_val * input2_val;
      *input1_offset_p += desc1->strides[dimension];
      *input2_offset_p += desc2->strides[dimension];
      ++(*output_offset);
    }
  } else {
    for (int a = 0; a < extended_output_shape_dims[dimension]; ++a) {
      uint32_t input1_offset_c = *input1_offset_p;
      uint32_t input2_offset_c = *input2_offset_p;
      BroadcastMulRecursiveDimensions(
          dimension + 1, input1_data, input2_data, output_data,
          &input1_offset_c, &input2_offset_c, output_offset, desc1, desc2,
          extended_output_shape_dims);
      *input1_offset_p += desc1->strides[dimension];
      *input2_offset_p += desc2->strides[dimension];
    }
  }
}

// Ported from TF
void DivFp(const float* input1_data, const float* input2_data, float* output_data,
  const int32_t* input1_shape, int32_t input1_dims, const int32_t* input2_shape,
  int32_t input2_dims, const int32_t* output_shape, int32_t output_dims,
  int32_t activation) {
  int32_t broadcast_category;
  if (ProcessBroadcastShapes(input1_shape, input1_dims, input2_shape, input2_dims,
        &broadcast_category)) {
    BroadcastDiv6DSlow(input1_shape, input1_data, input1_dims, input2_shape, input2_data,
      input2_dims, output_shape, output_data, output_dims, activation);
  } else {
    DivBasicFp(input1_shape, input1_data, input1_dims, input2_data, output_data,
      activation);
  }
}

// Supporting function for Div op
void DivBasicFp(const int32_t* input1_shape, const float* input1_data,
  int32_t input1_dims, const float* input2_data, float* output_data,
  int32_t activation) {
  (void)activation;
  const int flat_size = FlatSize(input1_shape, input1_dims);
  for (int i = 0; i < flat_size; ++i) {
    output_data[i] = input1_data[i] / input2_data[i];
  }
}

// Supporting function for Div op
void BroadcastDiv6DSlow(const int32_t* input1_shape, const float* input1_data,
  int32_t input1_dims, const int32_t* input2_shape, const float* input2_data,
  int32_t input2_dims, const int32_t* output_shape, float* output_data,
  int32_t output_dims, int32_t activation) {
  (void)activation;
  NdArrayDesc desc1, desc2;
  NdArrayDescsForElementwiseBroadcast(input1_shape, input1_dims, input2_shape,
    input2_dims, &desc1, &desc2, kMaxMulBroadcastDim);

  int32_t extended_output_shape_dims[kMaxMulBroadcastDim];
  ExtendedShape(output_shape, output_dims, extended_output_shape_dims, kMaxMulBroadcastDim);

  uint32_t input1_offset = 0;
  uint32_t input2_offset = 0;
  uint32_t output_offset = 0;
  BroadcastDivRecursiveDimensions( 0, input1_data, input2_data, output_data,
    &input1_offset, &input2_offset, &output_offset, &desc1, &desc2,
    extended_output_shape_dims);
}

// Supporting function for Div op
void BroadcastDivRecursiveDimensions(int dimension, const float* input1_data,
  const float* input2_data, float* output_data, uint32_t* input1_offset_p,
  uint32_t* input2_offset_p, uint32_t* output_offset, const NdArrayDesc* desc1,
  const NdArrayDesc* desc2, const int32_t* extended_output_shape_dims) {
  if (dimension == kMaxMulBroadcastDim - 1) {
    for (int c = 0; c < extended_output_shape_dims[dimension]; ++c) {
      const float input1_val = input1_data[*input1_offset_p];
      const float input2_val = input2_data[*input2_offset_p];
      output_data[*output_offset] = input1_val / input2_val;
      *input1_offset_p += desc1->strides[dimension];
      *input2_offset_p += desc2->strides[dimension];
      ++(*output_offset);
    }
  } else {
    for (int a = 0; a < extended_output_shape_dims[dimension]; ++a) {
      uint32_t input1_offset_c = *input1_offset_p;
      uint32_t input2_offset_c = *input2_offset_p;
      BroadcastDivRecursiveDimensions(
          dimension + 1, input1_data, input2_data, output_data,
          &input1_offset_c, &input2_offset_c, output_offset, desc1, desc2,
          extended_output_shape_dims);
      *input1_offset_p += desc1->strides[dimension];
      *input2_offset_p += desc2->strides[dimension];
    }
  }
}

// Adaptation from Renesas library
void SliceFp(const float* input, float* output, const int32_t* begin,
  const int32_t* size, const int32_t* in_shape, int32_t dims) {
  if (dims == 4) {
    int n_offset = in_shape[1] * in_shape[2] * in_shape[3];
    int h_offset = in_shape[2] * in_shape[3];
    int w_offset = in_shape[3];
    int end[4] = {
      ((size[0] == -1) ? in_shape[0] : begin[0]+size[0]),
      ((size[1] == -1) ? in_shape[1] : begin[1]+size[1]),
      ((size[2] == -1) ? in_shape[2] : begin[2]+size[2]),
      ((size[3] == -1) ? in_shape[3] : begin[3]+size[3])
    };

    for (int iItr0 = begin[0]; iItr0 < end[0]; iItr0++) {
      for (int iItr1 = begin[1]; iItr1 < end[1]; iItr1++) {
        for (int iItr2 = begin[2]; iItr2 < end[2]; iItr2++) {
          for (int iItr3 = begin[3]; iItr3 < end[3]; iItr3++) {
            *(output++) =  input[ (iItr0 * n_offset) + (iItr1 * h_offset) +
                (iItr2 * w_offset) + (iItr3)];
          }
        }
      }
    }
  } else if (dims == 3) {
    int h_offset = in_shape[1] * in_shape[2];
    int w_offset = in_shape[2];
    int end[3] = {
      ((size[0] == -1) ? in_shape[0] : begin[0]+size[0]),
      ((size[1] == -1) ? in_shape[1] : begin[1]+size[1]),
      ((size[2] == -1) ? in_shape[2] : begin[2]+size[2])
    };

    for (int iItr0 = begin[0]; iItr0 < end[0]; iItr0++) {
      for (int iItr1 = begin[1]; iItr1 < end[1]; iItr1++) {
        for (int iItr2 = begin[2]; iItr2 < end[2]; iItr2++) {
          *(output++) =  input[(iItr0 * h_offset) + (iItr1 * w_offset) + (iItr2)];
        }
      }
    }
  } else {
    int w_offset = in_shape[1];
    int end[2] = {
      ((size[0] == -1) ? in_shape[0] : begin[0]+size[0]),
      ((size[1] == -1) ? in_shape[1] : begin[1]+size[1])
    };

    for (int iItr0 = begin[0]; iItr0 < end[0]; iItr0++) {
      for (int iItr1 = begin[1]; iItr1 < end[1]; iItr1++) {
        *(output++) =  input[(iItr0 * w_offset) + (iItr1 )];
      }
    }
  }
}

// Ported from TF
void StridedSliceFp(const float* input, float* output, const int32_t* begin_orig,
  const int32_t* end_orig, const int32_t* strides, const int32_t* in_shape,
  int32_t in_dims, const int32_t* out_shape, int32_t out_dims,
  TfLiteStridedSliceParams str_slc_params) {

  StridedSliceParams params_copy = BuildStridedSliceParams(begin_orig, end_orig, strides,
        str_slc_params, in_dims);
  params_copy.offset = 0;

  int32_t input_shape[5];
  int32_t output_shape[5];
  ExtendedShape(in_shape, in_dims, input_shape, 5);
  ExtendedShape(out_shape, out_dims, output_shape, 5);

  // Reverse and pad to 5 dimensions because that is what the runtime code
  // requires (ie. all shapes must be 5D and are given backwards).
  StridedSlicePadIndices(&params_copy, in_dims, 5);

  const int start_0 = StridedSliceStartForAxis(&params_copy, input_shape, 0);
  const int stop_0 = StridedSliceEndForAxis(&params_copy, input_shape, 0, start_0);
  const int start_1 = StridedSliceStartForAxis(&params_copy, input_shape, 1);
  const int stop_1 = StridedSliceEndForAxis(&params_copy, input_shape, 1, start_1);
  const int start_2 = StridedSliceStartForAxis(&params_copy, input_shape, 2);
  const int stop_2 = StridedSliceEndForAxis(&params_copy, input_shape, 2, start_2);
  const int start_3 = StridedSliceStartForAxis(&params_copy, input_shape, 3);
  const int stop_3 = StridedSliceEndForAxis(&params_copy, input_shape, 3, start_3);
  const int start_4 = StridedSliceStartForAxis(&params_copy, input_shape, 4);
  const int stop_4 = StridedSliceEndForAxis(&params_copy, input_shape, 4, start_4);

  // With a static_cast it is not possible to initialize
  // a variable of type 'const int *'
  // with an rvalue of type 'const int32_t *' (aka 'const long *').
  // reinterpret_cast is required to handle this casting.
  const int* shape = input_shape;
  const int* stride = params_copy.strides;
  const bool inner_stride_is_1 = params_copy.strides[4] == 1;
  int output_ptr=0;

  for (int offset_0 = start_0; lc(stop_0, stride[0], offset_0);
       offset_0 += stride[0]) {
    for (int offset_1 = start_1; lc(stop_1, stride[1], offset_1);
         offset_1 += stride[1]) {
      for (int offset_2 = start_2; lc(stop_2, stride[2], offset_2);
           offset_2 += stride[2]) {
        for (int offset_3 = start_3; lc(stop_3, stride[3], offset_3);
             offset_3 += stride[3]) {
          // When the stride is 1, the inner loop is equivalent to the
          // optimized slice inner loop. Otherwise, it is identical to the
          // strided_slice reference implementation inner loop.
          if (inner_stride_is_1) {
            const int len = stop_4 - start_4;
            int index = start_4 + offset_3 * shape[4] +
                        offset_2 * shape[3] * shape[4] +
                        offset_1 * shape[2] * shape[3] * shape[4] +
                        offset_0 * shape[1] * shape[2] * shape[3] * shape[4];
            if (len > 0) {
              memcpy(output+output_ptr, input+index, sizeof(float) * len);
              output_ptr += len;
            }
          } else {
            for (int offset_4 = start_4; lc(stop_4, stride[4], offset_4);
                 offset_4 += stride[4]) {
              int index = offset_4 + offset_3 * shape[4] +
                          offset_2 * shape[3] * shape[4] +
                          offset_1 * shape[2] * shape[3] * shape[4] +
                          offset_0 * shape[1] * shape[2] * shape[3] * shape[4];
              output[output_ptr] = input[index];
              ++output_ptr;
            }
          }
        }
      }
    }
  }
}

void PackFp(const float **inputs, uint32_t inp_count, float *output, uint32_t size,
  uint32_t slice_size, uint32_t stride) {
  (void)inp_count;
  uint32_t out_ind = 0;
  uint32_t inp_ind = 0;
  uint32_t laps = 0;
  const float* curr_inp;

  while (out_ind < size) {
    curr_inp = inputs[inp_ind / stride];

    if (slice_size == 1) {
      output[out_ind] = curr_inp[(inp_ind % stride)];
    } else {
      memcpy(output + out_ind, curr_inp + (inp_ind % stride), slice_size*sizeof(float));
    }

    out_ind += slice_size;
    inp_ind += stride;
    if (inp_ind >= size) {
      laps++;
      inp_ind = laps * slice_size;
    }
  }
}

// Ported from Renesas library
void TanhFp(const float* input, float* output, uint32_t size) {
  for (uint32_t i = 0; i < size; i++) {
    float val = input[i];
    float result = tanh(val);
    output[i] = result;
  }
}

// Ported from TF
bool AvgpoolFp(const float* input_data, float* output_data, const int32_t* input_shape,
  const int32_t* output_shape, const int32_t* pool_params, int32_t activation) {
  float output_activation_min;
  float output_activation_max;
  CalculateActivationRangeFp(activation, &output_activation_min, &output_activation_max);

  const int batches = input_shape[0];
  const int depth = input_shape[3];
  const int input_height = input_shape[1];
  const int input_width = input_shape[2];
  const int output_height = output_shape[1];
  const int output_width = output_shape[2];
  const int stride_height = pool_params[3];
  const int stride_width = pool_params[2];
  for (int batch = 0; batch < batches; ++batch) {
    for (int out_y = 0; out_y < output_height; ++out_y) {
      for (int out_x = 0; out_x < output_width; ++out_x) {
        for (int channel = 0; channel < depth; ++channel) {
          const int in_x_origin =
              (out_x * stride_width) - pool_params[4];
          const int in_y_origin =
              (out_y * stride_height) - pool_params[5];
          // Compute the boundaries of the filter region clamped so as to
          // ensure that the filter window fits in the input array.
          const int filter_x_start = (0 > -in_x_origin) ? 0 : -in_x_origin;;
          const int filter_x_end =
              (pool_params[0] < input_width - in_x_origin) ? pool_params[0] : input_width - in_x_origin;
          const int filter_y_start = (0 > -in_y_origin) ? 0 : -in_y_origin;
          const int filter_y_end =
              (pool_params[1] < input_height - in_y_origin) ? pool_params[1] : input_height - in_y_origin;
          float total = 0.f;
          float filter_count = 0;
          for (int filter_y = filter_y_start; filter_y < filter_y_end;
               ++filter_y) {
            for (int filter_x = filter_x_start; filter_x < filter_x_end;
                 ++filter_x) {
              const int in_x = in_x_origin + filter_x;
              const int in_y = in_y_origin + filter_y;
              total +=
                  input_data[Offset(input_shape, batch, in_y, in_x, channel)];
              filter_count++;
            }
          }
          if (filter_count == 0) {
            return false;
          }
          const float average = total / filter_count;
          output_data[Offset(output_shape, batch, out_y, out_x, channel)] =
              ActivationFunctionWithMinMaxFp(average, output_activation_min,
                                           output_activation_max);
        }
      }
    }
  }
  return true;
}

void MinimumFp(const float* input_1, const float* input_2,  float* output,
  const int32_t* input1_shape, int32_t input1_dims, const int32_t* input2_shape,
  int32_t input2_dims, const int32_t* output_shape, int32_t output_dims) {
  bool simple_mode = false;

  // Broadcast if all the dimensions of the input 1 & 2 don't match
  if (input1_dims == input2_dims) {
    for (int i=0; i < input1_dims; i++) {
      if (input1_shape[i] != input2_shape[i]) {
        simple_mode = false;
        break;
      } else {
        simple_mode = true;
      }
    }
  }

  if (simple_mode) {
    int flat_size = FlatSize(input1_shape, input1_dims);
    for (int i = 0; i < flat_size; ++i) {
      output[i] = (input_1[i] < input_2[i]) ? input_1[i] : input_2[i];
    }
  } else {
    NdArrayDesc desc1, desc2, output_desc;
    int32_t extended_out_shape[5];

    NdArrayDescsForElementwiseBroadcast(input1_shape, input1_dims, input2_shape,
      input2_dims, &desc1, &desc2, 5);
    ExtendedShape(output_shape, output_dims, extended_out_shape, 5);
    CopyDimsToDesc(extended_out_shape, &output_desc, 5);

    int indexes[5] = {0};
    for (indexes[0] = 0; indexes[0] < output_desc.extents[0]; ++indexes[0]) {
      for (indexes[1] = 0; indexes[1] < output_desc.extents[1]; ++indexes[1]) {
        for (indexes[2] = 0; indexes[2] < output_desc.extents[2]; ++indexes[2]) {
          for (indexes[3] = 0; indexes[3] < output_desc.extents[3]; ++indexes[3]) {
            for (indexes[4] = 0; indexes[4] < output_desc.extents[4]; ++indexes[4]) {
              float inp_1 = input_1[SubscriptToIndexArr5(desc1, indexes)];
              float inp_2 = input_2[SubscriptToIndexArr5(desc2, indexes)];
              output[SubscriptToIndexArr5(output_desc, indexes)] =
                  inp_1 < inp_2 ? inp_1 : inp_2;
            }
          }
        }
      }
    }
  }
}

void ReduceMaxFp(const float* input, float* output, const int32_t* in_shape, const int32_t in_num_dims,
  int32_t out_size, const int32_t* axis, const int32_t num_axis) {
  int resolved_axis[num_axis];

  int32_t num_resolved_axis = 0;
  ResolveAxis(in_num_dims, axis, num_axis, resolved_axis, &num_resolved_axis);

  int temp_index[5] = {0};

  float initial_value = -INFINITY;
  for (int32_t i = 0; i < out_size; i++) {
    output[i] = initial_value;
  }

  // Reduce
  do {
    int32_t input_offset =
        ReducedOutputOffset(in_num_dims, in_shape, temp_index, 0, NULL);
    int32_t output_offset = ReducedOutputOffset(in_num_dims, in_shape,
                                                temp_index, num_resolved_axis, resolved_axis);
    output[output_offset] = (output[output_offset] > input[input_offset])
                            ? output[output_offset] : input[input_offset];
  } while (NextIndex(in_num_dims, in_shape, temp_index));
}

void Concatenation_fp32_w(const float *input, const uint16_t input_x, const uint16_t input_y,
  const uint16_t input_z, const uint16_t input_w, float *output, const uint32_t offset_w) {

  const uint32_t input_copy_size = input_x * input_y * input_z * input_w * sizeof(float);

  output += offset_w * (input_x * input_y * input_z);

  memcpy(output, input, input_copy_size);
}

void Concatenation_fp32_x(const float *input, const uint16_t input_x, const uint16_t input_y,
  const uint16_t input_z, const uint16_t input_w, float *output, const uint16_t output_x, const uint32_t offset_x) {

  const uint32_t num_iterations = input_y * input_z * input_w;

  output += offset_x;

  uint32_t i;

  // Copy per row
  for (i = 0; i < num_iterations; ++i) {
    memcpy(output, input, input_x * sizeof(float));
    input += input_x;
    output += output_x;
  }
}

void Concatenation_fp32_y(const float *input, const uint16_t input_x, const uint16_t input_y,
  const uint16_t input_z, const uint16_t input_w, float *output, const uint16_t output_y, const uint32_t offset_y) {

  const uint32_t num_iterations = input_z * input_w;
  const uint32_t input_copy_size = input_x * input_y;
  const uint32_t output_stride = input_x * output_y;

  output += offset_y * input_x;
  uint32_t i;

  // Copy per tile
  for (i = 0; i < num_iterations; ++i) {
    memcpy(output, input, input_copy_size * sizeof(float));
    input += input_copy_size;
    output += output_stride;
  }
}

void Concatenation_fp32_z(const float *input, const uint16_t input_x, const uint16_t input_y,
  const uint16_t input_z, const uint16_t input_w, float *output, const uint16_t output_z, const uint32_t offset_z) {
  const uint32_t input_copy_size = input_x * input_y * input_z;

  const uint32_t output_stride = input_x * input_y * output_z;

  output += offset_z * (input_x * input_y);

  uint32_t i;

  for (i = 0; i < input_w; ++i) {
    memcpy(output, input, input_copy_size * sizeof(float));
    input += input_copy_size;
    output += output_stride;
  }
}

void ExpFp(const float *input, float *output, uint32_t size) {
  for (uint32_t i=0; i<size; i++) {
    output[i] = expf(input[i]);
  }
}

void NegFp(const float *input, float *output, uint32_t size) {
  for (uint32_t i = 0; i < size; ++i) {
    output[i] = -input[i];
  }
}

// Ported from TF
void LogSoftmaxFp(const float *input, float *output, const int32_t *shape, const int32_t num_dims) {
  uint32_t depth, outer_size;
  if(num_dims == 4) {
    depth = shape[3];
    outer_size = shape[0] * shape[1] * shape[2];
  } else if(num_dims == 3) {
    depth = shape[2];
    outer_size = shape[0] * shape[1];
  } else if(num_dims == 2) {
    depth = shape[1];
    outer_size = shape[0];
  } else {
    depth = shape[0];
    outer_size = shape[0];
  }

  float max_element, sum = 0;

  for (uint32_t i=0; i<outer_size; i++) {
    max_element = input[i*depth];
    for (uint32_t j=0; j<depth; j++) {
      max_element = (input[i*depth + j] > max_element) ? (input[i*depth + j]) : max_element;
    }
    sum = 0;
    for (uint32_t j=0; j<depth; j++) {
      sum += exp(input[i*depth + j] - max_element);
    }
    for (uint32_t j=0; j<depth; j++) {
      float res = input[i*depth + j] - max_element - log(sum);
      output[i*depth + j] = res;
    }
  }
}

void LeakyReluFp(const float *input, float *output, uint32_t size, float alpha) {
  for (uint32_t i=0; i<size; i++) {
    float result = (input[i] >= 0) ? (input[i]) : (alpha * input[i]);
    output[i] = result;
  }
}

void LogFp(const float *input, float *output, uint32_t size) {
  for (uint32_t i = 0; i < size; i++) {
    if (input[i] < 0.0) {
      output[i] = NAN;
    } else {
      output[i] = logf(input[i]);
    }
  }
}

void MeanFp(const float* input, float* output, const int32_t* in_shape,
  const int32_t in_num_dims, const int32_t* out_shape, int32_t out_size,
  const int32_t* axis, const int32_t num_axis, bool keep_dims) {

  // Special case mean implementation exists for 4D mean across axes 1 and 2.
  bool special_case_4d_axes_1_and_2 = in_num_dims == 4 && num_axis == 2 &&
      ((axis[0] == 1 && axis[1] == 2) || (axis[0] == 2 && axis[1] == 1));

  if (keep_dims && special_case_4d_axes_1_and_2) {
    MeanFp_case1(input, output, in_shape, out_shape);
  } else {
    int temp_index[kMaxNumberOfAxis]={0};
    float temp_sum[out_size];
    int32_t resolved_axis[kMaxNumberOfReducedAxis]={0};

    memset(temp_sum, 0, sizeof(temp_sum));
    memset(output, 0, out_size * sizeof(float));

    int32_t num_resolved_axis = 0;
    if (!ResolveAxis(in_num_dims, axis, num_axis, resolved_axis,
                      &num_resolved_axis)) {
      return;
    }

    // Reduce
    do {
      uint32_t input_offset =
          ReducedOutputOffset(in_num_dims, in_shape, temp_index, 0, NULL);
      uint32_t output_offset = ReducedOutputOffset(in_num_dims, in_shape,
                                temp_index, num_resolved_axis, resolved_axis);
      temp_sum[output_offset] = temp_sum[output_offset] + input[input_offset];
    } while (NextIndex(in_num_dims, in_shape, temp_index));

    // Calculate Mean
    uint32_t num_elements_in_axis = 1;
    for (int idx = 0; idx < num_resolved_axis; ++idx) {
      uint32_t current = (uint32_t) in_shape[resolved_axis[idx]];
      num_elements_in_axis *= current;
    }
    if (num_elements_in_axis > 0) {
      for (uint32_t idx = 0; idx < (uint32_t) out_size; ++idx) {
        output[idx] = (float)(temp_sum[idx] / (float)(num_elements_in_axis));
      }
    }
  }
}

void MeanFp_case1(const float* input_data, float* output_data, const int32_t* input_shape,
  const int32_t* output_shape) {

  const int output_batch = output_shape[0];
  const int output_depth = output_shape[3];

  const int input_height = input_shape[1];
  const int input_width = input_shape[2];

  for (int out_b = 0; out_b < output_batch; ++out_b) {
    for (int out_d = 0; out_d < output_depth; ++out_d) {
      float value = 0;
      for (int in_h = 0; in_h < input_height; ++in_h) {
        for (int in_w = 0; in_w < input_width; ++in_w) {
          value += input_data[Offset(input_shape, out_b, in_h, in_w, out_d)];
        }
      }
      output_data[Offset(output_shape, out_b, 0, 0, out_d)] =
          value / (input_width * input_height);
    }
  }
}

void SumFp(const float* input, float* output, const int32_t* in_shape,
  const int32_t in_num_dims, const int32_t* out_shape, int32_t out_size,
  const int32_t* axis, const int32_t num_axis, bool keep_dims) {
  (void)out_shape;
  (void)keep_dims;
  int temp_index[kMaxNumberOfAxis]={0};
  int32_t resolved_axis[kMaxNumberOfReducedAxis]={0};

  memset(output, 0, out_size * sizeof(float));

  int32_t num_resolved_axis = 0;
  if (!ResolveAxis(in_num_dims, axis, num_axis, resolved_axis,
                    &num_resolved_axis)) {
    return;
  }

  // Reduce
  do {
    uint32_t input_offset =
        ReducedOutputOffset(in_num_dims, in_shape, temp_index, 0, NULL);
    uint32_t output_offset = ReducedOutputOffset(in_num_dims, in_shape,
                              temp_index, num_resolved_axis, resolved_axis);
    output[output_offset] = output[output_offset] + input[input_offset];
  } while (NextIndex(in_num_dims, in_shape, temp_index));
}

void PReluFp(const float *input, const int32_t *in_shape, int32_t in_dims, float *output,
  const int32_t *out_shape, int32_t out_dims, const float *alpha, const int32_t *alpha_shape,
  int32_t alpha_dims) {

  int32_t extended_shape[4]={0};
  NdArrayDesc desc1,desc2;

  ExtendedShape(out_shape, out_dims, extended_shape, 4);
  NdArrayDescsForElementwiseBroadcast(in_shape, in_dims, alpha_shape, alpha_dims, &desc1, &desc2, 4);

  for (int b = 0; b < extended_shape[0]; ++b) {
    for (int y = 0; y < extended_shape[1]; ++y) {
      for (int x = 0; x < extended_shape[2]; ++x) {
        for (int c = 0; c < extended_shape[3]; ++c) {
          int32_t out_idx = Offset(extended_shape, b, y, x, c);
          int in1_idx = SubscriptToIndex(desc1, b, y, x, c);
          int in2_idx = SubscriptToIndex(desc2, b, y, x, c);
          float in1_val = input[in1_idx];
          float in2_val = alpha[in2_idx];
          output[out_idx] = (in1_val >= 0.0f) ? (in1_val) : (in1_val * in2_val);
        }
      }
    }
  }
}

void ReluFp(const float *input, float *output, uint32_t size) {
  for (uint32_t i = 0; i < size; i++) {
    output[i] = (input[i] > 0.0f) ? (input[i]) : (0.0f);
  }
}

void Relu6Fp(const float *input, float *output,const uint32_t size) {
  for (uint32_t i = 0; i < size; i++) {
    output[i] = (input[i] > 6.0f) ? (6.0f) : ( (input[i] < 0.0f) ? (0.0f) : (input[i]));
  }
}

void SpaceToBatchNdFp(const float* input_data, const int32_t* unextended_input1_shape,
  int32_t in_num_dims, float* output_data, const int32_t* unextended_output_shape,
  const int32_t* block_shape, const int32_t* pad) {

  int32_t input_batch_size, input_height, input_width, depth, output_batch_size, output_height, output_width;
  int32_t block_shape_height, block_shape_width, padding_top, padding_left;

  int32_t in_shape[4] = {0};
  int32_t out_shape[4] = {0};

  ExtendShapeSpaceToBatch(unextended_input1_shape, in_num_dims, in_shape);
  ExtendShapeSpaceToBatch(unextended_output_shape, in_num_dims, out_shape);

  input_batch_size = in_shape[0];
  input_height = in_shape[1];
  input_width = in_shape[2];
  output_batch_size = out_shape[0];
  output_height = out_shape[1];
  output_width = out_shape[2];
  block_shape_height = block_shape[0];
  padding_top = pad[0];
  depth = in_shape[3];

  if (in_num_dims == 4) {
    block_shape_width = block_shape[1];
    padding_left = pad[2];
  } else { /* in_num_dims is 3 here */
    block_shape_width = 1;
    padding_left = 0;
  }

  // For uint8 quantized, the correct padding "zero value" is the output offset.
  const float pad_value = 0;

  for (int out_b = 0; out_b < output_batch_size; ++out_b) {
    int input_batch = out_b % input_batch_size;
    int shift_w = (out_b / input_batch_size) % block_shape_width;
    int shift_h = (out_b / input_batch_size) / block_shape_width;
    for (int out_h = 0; out_h < output_height; ++out_h) {
      for (int out_w = 0; out_w < output_width; ++out_w) {
        float* out = output_data + Offset(out_shape, out_b, out_h, out_w, 0);
        if (out_h * block_shape_height + shift_h < padding_top ||
            out_h * block_shape_height + shift_h >=
                padding_top + input_height ||
            out_w * block_shape_width + shift_w < padding_left ||
            out_w * block_shape_width + shift_w >= padding_left + input_width) {
          memset(out, pad_value, depth * sizeof(float));
        } else {
          const float* in =
              input_data +
              Offset(in_shape, input_batch,
                     (out_h * block_shape_height + shift_h) - padding_top,
                     (out_w * block_shape_width + shift_w) - padding_left, 0);
          memcpy(out, in, depth * sizeof(float));
        }
      }
    }
  }
}

void BatchToSpaceNdFp(const float* input_data, const int32_t* unextended_input1_shape,
  int32_t in_num_dims, float* output_data, const int32_t* unextended_output_shape,
  const int32_t* block_shape, const int32_t* crops) {

  int32_t input_batch_size, input_height, input_width, depth, output_batch_size, output_height, output_width;
  int32_t block_shape_height, block_shape_width, crops_top, crops_left;

  int32_t in_shape[4] = {0};
  int32_t out_shape[4] = {0};

  ExtendShapeBatchToSpace(unextended_input1_shape, in_num_dims, in_shape);
  ExtendShapeBatchToSpace(unextended_output_shape, in_num_dims, out_shape);

  input_batch_size = in_shape[0];
  input_height = in_shape[1];
  input_width = in_shape[2];
  output_batch_size = out_shape[0];
  output_height = out_shape[1];
  output_width = out_shape[2];
  block_shape_height = block_shape[0];
  crops_top = crops[0];
  depth = in_shape[3];

  if (in_num_dims == 4) {
    block_shape_width = block_shape[1];
    crops_left = crops[2];
  } else { /* in_num_dims is 3 here */
    block_shape_width = 1;
    crops_left = 0;
  }

  for (int in_batch = 0; in_batch < input_batch_size; ++in_batch) {
    const int out_batch = in_batch % output_batch_size;
    const int spatial_offset = in_batch / output_batch_size;
    for (int in_h = 0; in_h < input_height; ++in_h) {
      const int out_h = in_h * block_shape_height +
                        spatial_offset / block_shape_width - crops_top;
      if (out_h < 0 || out_h >= output_height) {
        continue;
      }
      for (int in_w = 0; in_w < input_width; ++in_w) {
        const int out_w = in_w * block_shape_width +
                          spatial_offset % block_shape_width - crops_left;
        if (out_w < 0 || out_w >= output_width) {
          continue;
        }
        float* out = output_data + Offset(out_shape, out_batch, out_h, out_w, 0);
        const float* in =
            input_data + Offset(in_shape, in_batch, in_h, in_w, 0);
        memcpy(out, in, depth * sizeof(float));
      }
    }
  }
}

void TransposeFp(const float* input, float* output, int32_t size, int32_t rank,
  int32_t* strides, int32_t* next_dim_sizes, int32_t* dim_sizes) {

  int inp_ind;
  int out_ind = 0;
  int local_offset;
  while (out_ind < size) {
    inp_ind = 0;
    for (int i = 0; i < rank; i++) {
      local_offset = out_ind % next_dim_sizes[i];
      inp_ind += strides[i] * (int)(local_offset / dim_sizes[i]);
    }
    output[out_ind] = input[inp_ind];
    out_ind++;
  }
}

void SigmoidFp(const float* input, float* output, const uint32_t size) {

  const float cutoff_upper = 16.619047164916992188f;
  const float cutoff_lower = -9.f;

  for (uint32_t i = 0; i < size; i++) {
    float val = input[i];
    float result;
    if (val > cutoff_upper) {
      result = 1.0f;
    } else if (val < cutoff_lower) {
      result = expf(val);
    } else {
      result = 1.f / (1.f + expf(-val));
    }
    output[i] = result;
  }
}

void ResizeBilinearFp(const float* input_data, const int32_t* input_shape, int32_t in_dims,
  const int32_t* size_data, const int32_t* size_shape, int32_t size_dims, float* output_data,
  const int32_t* output_shape, int32_t out_dims, bool half_pixel_centers, bool align_corners) {
  (void)size_data;

  int32_t extended_input_shape[4] = {0};
  int32_t extended_size_shape[4] = {0};
  int32_t extended_output_shape[4] = {0};

  ExtendedShape(input_shape, in_dims, extended_input_shape, 4);
  ExtendedShape(size_shape, size_dims, extended_size_shape, 4);
  ExtendedShape(output_shape, out_dims, extended_output_shape, 4);

  int32_t batches = extended_input_shape[0];
  int32_t input_height = extended_input_shape[1];
  int32_t input_width = extended_input_shape[2];
  int32_t depth = extended_input_shape[3];

  int32_t output_height = extended_output_shape[1];
  int32_t output_width = extended_output_shape[2];

  float height_scale = (float)(input_height) / output_height;
  float width_scale = (float)(input_width) / output_width;
  if (align_corners && output_height > 1) {
    height_scale = (float)(input_height - 1) / (output_height - 1);
  }
  if (align_corners && output_width > 1) {
    width_scale = (float)(input_width - 1) / (output_width - 1);
  }
  const float rounding_offset = .0f;

  for (int b = 0; b < batches; ++b) {
    for (int y = 0; y < output_height; ++y) {
      float input_y;
      int32_t y0, y1;
      ComputeInterpolationValues(y, height_scale, half_pixel_centers,input_height,
            &input_y, &y0, &y1);
      for (int x = 0; x < output_width; ++x) {
        float input_x;
        int32_t x0, x1;
        ComputeInterpolationValues(x, width_scale, half_pixel_centers, input_width,
            &input_x, &x0, &x1);
        for (int c = 0; c < depth; ++c) {
          float interpolation =
              (float)(input_data[Offset(extended_input_shape, b, y0, x0, c)] *
                                 (1 - (input_y - y0)) * (1 - (input_x - x0)) +
                             input_data[Offset(extended_input_shape, b, y1, x0, c)] *
                                 (input_y - y0) * (1 - (input_x - x0)) +
                             input_data[Offset(extended_input_shape, b, y0, x1, c)] *
                                 (1 - (input_y - y0)) * (input_x - x0) +
                             input_data[Offset(extended_input_shape, b, y1, x1, c)] *
                                 (input_y - y0) * (input_x - x0) +
                             rounding_offset);
          output_data[Offset(extended_output_shape, b, y, x, c)] = interpolation;
        }
      }
    }
  }
}

void UpsamplingNearestNeighborFp(const float* input, const int32_t* input_shape, int32_t input_dims,
  float* output, const int32_t* output_shape, int32_t output_dims, bool align_corners, bool half_pixel_centers) {

  int32_t extended_input_shape[4] = {0};
  int32_t extended_output_shape[4] = {0};

  ExtendedShape(input_shape, input_dims, extended_input_shape, 4);
  ExtendedShape(output_shape, output_dims, extended_output_shape, 4);

  int32_t batches = extended_input_shape[0];
  int32_t input_height = extended_input_shape[1];
  int32_t input_width = extended_input_shape[2];
  int32_t depth = extended_input_shape[3];

  int32_t output_height = output_shape[1];
  int32_t output_width = output_shape[2];

  const int col_offset = extended_input_shape[3];
  const int row_offset = extended_input_shape[2] * col_offset;
  const int batch_offset = extended_input_shape[1] * row_offset;

  const float* input_ptr = input;
  float* output_ptr = output;

  for (int b = 0; b < batches; ++b) {
    for (int y = 0; y < output_height; ++y) {
      int32_t in_y = GetNearestNeighbor(y, input_height, output_height, align_corners, half_pixel_centers);
      const float* y_input_ptr = input_ptr + in_y * row_offset;

      for (int x = 0; x < output_width; ++x) {
        int32_t in_x = GetNearestNeighbor(x, input_width, output_width, align_corners, half_pixel_centers);
        const float* x_input_ptr = y_input_ptr + in_x * col_offset;
        memcpy(output_ptr, x_input_ptr, depth * sizeof(float));
        output_ptr += depth;
      }
    }
    input_ptr += batch_offset;
  }
}

void MirrorPadFp(const float* input_data, const int32_t* input_dims, int* input_dims_num_elements,
  const int num_dims, float* output_data, const int output_size, int* output_dims_num_elements,
  const int32_t* padding_matrix, const int offset) {

  for (int i = 0; i < output_size; ++i) {
    output_data[i] = input_data[GetFlatIndex(
        i, num_dims, padding_matrix, input_dims, output_dims_num_elements,
        input_dims_num_elements, offset)];
  }
}

void PowFp(const float* input1, int32_t input1_size, const int32_t* input1_shape,
  int32_t input1_dims, const float* input2, int32_t input2_size,
  int32_t input2_dims, const int32_t* input2_shape, float* output,
  int32_t output_dims, const int32_t* output_shape) {
  (void)input1_size;
  (void)input2_size;
  int32_t extended_input1_shape[4] = {0};
  int32_t extended_input2_shape[4] = {0};
  int32_t extended_output_shape[4] = {0};

  ExtendedShape(input1_shape, input1_dims, extended_input1_shape, 4);
  ExtendedShape(input2_shape, input2_dims, extended_input2_shape, 4);
  ExtendedShape(output_shape, output_dims, extended_output_shape, 4);

  NdArrayDesc desc1, desc2;
  NdArrayDescsForElementwiseBroadcast(input1_shape, input1_dims, input2_shape, input2_dims, &desc1, &desc2, 4);

  for (int b = 0; b < extended_output_shape[0]; ++b) {
    for (int y = 0; y < extended_output_shape[1]; ++y) {
      for (int x = 0; x < extended_output_shape[2]; ++x) {
        for (int c = 0; c < extended_output_shape[3]; ++c) {
          int32_t out_idx = Offset(extended_output_shape, b, y, x, c);
          int in1_idx = SubscriptToIndex(desc1, b, y, x, c);
          int in2_idx = SubscriptToIndex(desc2, b, y, x, c);
          float in1_val = input1[in1_idx];
          float in2_val = input2[in2_idx];
          output[out_idx] = pow(in1_val, in2_val);
        }
      }
    }
  }
}

void AbsFp(const float* input, float* output, const uint32_t size) {
  for (uint32_t i = 0; i < size; i++) {
    output[i] = (input[i] >= 0) ? (input[i]) : (-input[i]);
  }
}

void SqrtFp(const float* input, float* output, uint32_t size) {
  for (size_t i = 0; i < size; ++i) {
    if (input[i] >= 0.0) {
      output[i] = sqrt(input[i]);
    } else {
      output[i] = NAN;
    }
  }
}

void RsqrtFp(const float* input, float* output, uint32_t size) {
  for (size_t i = 0; i < size; ++i) {
    if (input[i] > 0.0) {
      output[i] = (1.f / sqrt(input[i]));
    } else {
      output[i] = NAN;
    }
  }
}

// Ported from TF
void PadFp(int32_t left_padding_count, int32_t *left_padding,
             int32_t right_padding_count, int32_t *right_padding,
             int32_t *ext_input_shape, const float *input_data,
             const float pad_value, const int32_t *ext_output_shape,
             float *output_data) {
  (void)ext_input_shape;
  // Runtime calls are currently fixed at 5 dimensions. Copy inputs so we can
  // pad them to 5 dims (yes, we are "padding the padding").
  int left_padding_copy[PadKernelMaxDimensionCount];
  for (int i = 0; i < PadKernelMaxDimensionCount; i++) {
    left_padding_copy[i] = 0;
  }
  for (int i = 0; i < left_padding_count; ++i) {
    left_padding_copy[i + PadKernelMaxDimensionCount -
                      left_padding_count] = left_padding[i];
  }
  int right_padding_copy[PadKernelMaxDimensionCount];
  for (int i = 0; i < PadKernelMaxDimensionCount; i++) {
    right_padding_copy[i] = 0;
  }
  for (int i = 0; i < right_padding_count; ++i) {
    right_padding_copy[i + PadKernelMaxDimensionCount -
                       right_padding_count] =
        right_padding[i];
  }

  const int output_batch = ext_output_shape[0];
  const int output_plane = ext_output_shape[1];
  const int output_height = ext_output_shape[2];
  const int output_width = ext_output_shape[3];
  const int output_depth = ext_output_shape[4];

  const int left_b_padding = left_padding_copy[0];
  const int left_p_padding = left_padding_copy[1];
  const int left_h_padding = left_padding_copy[2];
  const int left_w_padding = left_padding_copy[3];
  const int left_d_padding = left_padding_copy[4];

  const int right_b_padding = right_padding_copy[0];
  const int right_p_padding = right_padding_copy[1];
  const int right_h_padding = right_padding_copy[2];
  const int right_w_padding = right_padding_copy[3];
  const int right_d_padding = right_padding_copy[4];

  const float* in_ptr = input_data;
  float* out_ptr = output_data;
  for (int out_b = 0; out_b < output_batch; ++out_b) {
    for (int out_p = 0; out_p < output_plane; ++out_p) {
      for (int out_h = 0; out_h < output_height; ++out_h) {
        for (int out_w = 0; out_w < output_width; ++out_w) {
          for (int out_d = 0; out_d < output_depth; ++out_d) {
            if (out_b < left_b_padding ||
                out_b >= output_batch - right_b_padding ||
                out_p < left_p_padding ||
                out_p >= output_plane - right_p_padding ||
                out_h < left_h_padding ||
                out_h >= output_height - right_h_padding ||
                out_w < left_w_padding ||
                out_w >= output_width - right_w_padding ||
                out_d < left_d_padding ||
                out_d >= output_depth - right_d_padding) {
              *out_ptr++ = pad_value;
            } else {
              *out_ptr++ = *in_ptr++;
            }
          }
        }
      }
    }
  }
}

// Supporting function for Squared Difference op
float SquaredDifferenceFpOp(float input1, float input2) {
  const float difference = input1 - input2;
  return difference * difference;
}

// Supporting function for Squared Difference op
void SquaredDifferenceBroadcast1Fp(const float* input1, const float* input2,
  float* output, int size) {

  for (int i = 0; i < size; ++i) {
    output[i] = SquaredDifferenceFpOp(input1[0], input2[i]);
  }
}

// Supporting function for Squared Difference op
void SquaredDifferenceBroadcast2Fp(const float* input1, const float* input2,
  float* output, int size) {

  for (int i = 0; i < size; ++i) {
    output[i] = SquaredDifferenceFpOp(input1[i], input2[0]);
  }
}

// Supporting function for Squared Difference op
void ElementWiseSquaredDifferenceFp(const float* input1, const float* input2,
  float* output, int size) {

  for (int i = 0; i < size; ++i) {
    output[i] = SquaredDifferenceFpOp(input1[i], input2[i]);
  }
}

// Supporting function for Squared Difference op
inline void BroadcastRecursiveDimensionsFp(
  const float* input1, int32_t* input1_offset_p, int32_t* compressed_input1_stride,
  const float* input2, int32_t* input2_offset_p, int32_t* compressed_input2_stride,
  float* output, int32_t* output_offset, int32_t* compressed_output_shape,
  int dimension) {

  if (dimension > 0) {
    for (int32_t c = 0; c < compressed_output_shape[dimension]; ++c) {
      int32_t input1_offset_c = *input1_offset_p;
      int32_t input2_offset_c = *input2_offset_p;
      BroadcastRecursiveDimensionsFp(input1, &input1_offset_c, compressed_input1_stride,
        input2, &input2_offset_c, compressed_input2_stride, output, output_offset,
        compressed_output_shape, dimension - 1);

      *input1_offset_p += compressed_input1_stride[dimension];
      *input2_offset_p += compressed_input2_stride[dimension];
    }
  } else {
    bool input1_is_broadcast = compressed_input1_stride[dimension] == 0;
    bool input2_is_broadcast = compressed_input2_stride[dimension] == 0;
    const float* input1_ptr = input1 + *input1_offset_p;
    const float* input2_ptr = input2 + *input2_offset_p;
    float* output_ptr = output + *output_offset;
    if (input1_is_broadcast) {
      // input1 is broadcast.
      SquaredDifferenceBroadcast1Fp(input1_ptr, input2_ptr, output_ptr, compressed_output_shape[dimension]);
      *input2_offset_p += compressed_output_shape[dimension];
    } else if (input2_is_broadcast) {
      // input2 is broadcast.
      SquaredDifferenceBroadcast2Fp(input1_ptr, input2_ptr, output_ptr, compressed_output_shape[dimension]);
      *input1_offset_p += compressed_output_shape[dimension];
    } else {
      ElementWiseSquaredDifferenceFp(input1_ptr, input2_ptr, output_ptr, compressed_output_shape[dimension]);
      *input1_offset_p += compressed_output_shape[dimension];
      *input2_offset_p += compressed_output_shape[dimension];
    }
    *output_offset += compressed_output_shape[dimension];
  }
}

// Supporing function for Squared Difference op
void BroadcastSquaredDifference6DSlowFp(
  const float* input1, const int32_t* input1_shape, int32_t input1_dims,
  const float* input2, const int32_t* input2_shape, int32_t input2_dims,
  float* output, const int32_t* output_shape, int32_t output_dims) {
  (void)output_shape;
  (void)output_dims;

  int32_t compressed_input1_stride[kMaxBroadcastDim];
  int32_t compressed_input2_stride[kMaxBroadcastDim];
  int32_t compressed_output_shape[kMaxBroadcastDim] = {1, 1, 1, 1, 1, 1};
  bool broadcastable_shape = ReduceDimensionsForBroadcastFp(input1_shape, input1_dims, input2_shape,
                              input2_dims, compressed_input1_stride, compressed_input2_stride,
                              compressed_output_shape);
  // Skip broadcasting for degenerate shapes.
  if (!broadcastable_shape) {
    return;
  }

  int32_t input1_offset = 0;
  int32_t input2_offset = 0;
  int32_t output_offset = 0;
  BroadcastRecursiveDimensionsFp(input1, &input1_offset, compressed_input1_stride,
        input2, &input2_offset, compressed_input2_stride, output, &output_offset,
        compressed_output_shape, kMaxBroadcastDim - 1);
}

// Ported from TF
void SquaredDifferenceFp(const float* input1, const int32_t* input1_shape,
  uint32_t input1_dims, uint32_t input1_size, const float* input2,
  const int32_t* input2_shape, uint32_t input2_dims, float* output,
  const int32_t* output_shape, uint32_t output_dims) {

  if (!HaveSameShapes(input1_shape, input1_dims, input2_shape, input2_dims)) {
    BroadcastSquaredDifference6DSlowFp(input1, input1_shape, input1_dims, input2,
        input2_shape, input2_dims, output, output_shape, output_dims);
  } else {
    ElementWiseSquaredDifferenceFp(input1, input2, output, input1_size);
  }
}

// Ported from TF
void HardSwishFp(const float* input, const int32_t* input_shape,
  int32_t input_dims, float* output) {

  int matching_size = FlatSize(input_shape, input_dims);
  const float* in_end = input + matching_size;

  for (; input < in_end; input++, output++) {
    const float in = *input;
    *output = in * (MinFp(6, MaxFp(0, in + 3))) / 6;
  }
}

// Ported from TF
void BroadcastComparison4DSlowImpl(const float* input_1,
  const int32_t* input1_shape, int32_t input1_dims, const float* input_2,
  const int32_t* input2_shape, int32_t input2_dims, int8_t* output,
  const int32_t* output_shape, int32_t output_dims) {

  NdArrayDesc desc1;
  NdArrayDesc desc2;

  NdArrayDescsForElementwiseBroadcast(input1_shape, input1_dims, input2_shape,
    input2_dims, &desc1, &desc2, 4);

  int32_t extended_output_shape[4];
  ExtendedShape(output_shape, output_dims, extended_output_shape, 4);

  for (int b = 0; b < extended_output_shape[0]; ++b) {
    for (int y = 0; y < extended_output_shape[1]; ++y) {
      for (int x = 0; x < extended_output_shape[2]; ++x) {
        for (int c = 0; c < extended_output_shape[3]; ++c) {
          output[Offset(extended_output_shape, b, y, x, c)] =
              (input_1[SubscriptToIndex(desc1, b, y, x, c)] >
                input_2[SubscriptToIndex(desc2, b, y, x, c)]);
        }
      }
    }
  }
}

// Ported from TF
void GreaterFp(const float* input1, const int32_t* input1_shape, int32_t input1_dims,
  const float* input2, const int32_t* input2_shape, int32_t input2_dims, int8_t* output,
  const int32_t* output_shape, int32_t output_dims) {

  if (!HaveSameShapes(input1_shape, input1_dims, input2_shape, input2_dims)) {
    BroadcastComparison4DSlowImpl(input1, input1_shape, input1_dims,
      input2, input2_shape, input2_dims, output, output_shape, output_dims);
  } else {
    int32_t size = FlatSize(input1_shape, input1_dims);
    for (int i = 0; i < size; ++i) {
      output[i] = (input1[i] > input2[i]);
    }
  }
}

void BroadcastSelect5DSlow(const float* input1, const int32_t* input1_shape,
  int32_t input1_dims, const float* input2, const int32_t* input2_shape,
  int32_t input2_dims, const int8_t* condition, const int32_t* condition_shape,
  int32_t condition_dims, float* output, const int32_t* output_shape,
  int32_t output_dims) {

  NdArrayDesc desc_condition, desc_x, desc_y, desc_output;

  int32_t extended_output_shape[5];

  ExtendedShape(output_shape, output_dims, extended_output_shape, 5);
  CopyDimsToDesc(extended_output_shape, &desc_output, 5);

  NdArrayDescsForElementwiseBroadcast1(input1_shape, input1_dims, input2_shape, input2_dims,
                                      condition_shape, condition_dims, &desc_x, &desc_y, &desc_condition, 5);

  for (int n = 0; n < desc_output.extents[0]; ++n) {
    int out_idx_n = desc_output.extents[1] * n;
    int cond_idx_n = desc_condition.strides[0] * n;
    int in_idx1_n = desc_x.strides[0] * n;
    int in_idx2_n = desc_y.strides[0] * n;
    for (int b = 0; b < desc_output.extents[1]; ++b) {
      int out_idx_b = (out_idx_n + b) * desc_output.extents[2];
      int cond_idx_b = cond_idx_n + desc_condition.strides[1] * b;
      int in_idx1_b = in_idx1_n + desc_x.strides[1] * b;
      int in_idx2_b = in_idx2_n + desc_y.strides[1] * b;
      for (int y = 0; y < desc_output.extents[2]; ++y) {
        int out_idx_y = (out_idx_b + y) * desc_output.extents[3];
        int cond_idx_y = cond_idx_b + desc_condition.strides[2] * y;
        int in_idx1_y = in_idx1_b + desc_x.strides[2] * y;
        int in_idx2_y = in_idx2_b + desc_y.strides[2] * y;
        for (int x = 0; x < desc_output.extents[3]; ++x) {
          int out_idx = (out_idx_y + x) * desc_output.extents[4];
          int cond_idx = cond_idx_y + desc_condition.strides[3] * x;
          int in_idx1 = in_idx1_y + desc_x.strides[3] * x;
          int in_idx2 = in_idx2_y + desc_y.strides[3] * x;
          for (int c = 0; c < desc_output.extents[4]; ++c) {
            output[out_idx] = condition[cond_idx] ? input1[in_idx1] : input2[in_idx2];
            out_idx++;
            cond_idx += desc_condition.strides[4];
            in_idx1 += desc_x.strides[4];
            in_idx2 += desc_y.strides[4];
          }
        }
      }
    }
  }
}

void SelectV2Fp(const float* input1, const int32_t* input1_shape, int32_t input1_dims,
  const float* input2, const int32_t* input2_shape, int32_t input2_dims,
  const int8_t* condition, const int32_t* condition_shape, int32_t condition_dims,
  float* output, const int32_t* output_shape, int32_t output_dims) {

  int8_t same_shape = HaveSameShapes(input1_shape, input1_dims, input2_shape, input2_dims) &&
    HaveSameShapes(input1_shape, input1_dims, condition_shape, condition_dims);

  if (!same_shape) {
    BroadcastSelect5DSlow(input1, input1_shape, input1_dims,
      input2, input2_shape, input2_dims, condition, condition_shape,
      condition_dims, output, output_shape, output_dims);
  } else {
    int32_t flatsize = FlatSize(input1_shape, input1_dims);
    for (int32_t i = 0; i < flatsize; ++i) {
      output[i] = condition[i] ? input1[i] : input2[i];
    }
  }
}

float TfLiteExpm1(float x) {
  return expf(x) - 1.0f;
}

// Ported from TF
void EluFp(const float* input_data, const int32_t* input_shape,
  int32_t input_dims, float* output_data) {

  const int flat_size = FlatSize(input_shape, input_dims);
  for (int i = 0; i < flat_size; ++i) {
    const float val = input_data[i];
    output_data[i] = val < 0.0f ? TfLiteExpm1(val) : val;
  }
}

// Ported from TF
void GatherFp(const float* input, const int32_t* input_shape,
  int32_t input_dims, const int32_t* coords, const int32_t* coords_shape,
  int32_t coords_dims, int32_t axis, int32_t batch_dims, float *output) {

  if (axis < 0) {
    axis += input_dims;
  }
  if (batch_dims < 0) {
    batch_dims += coords_dims;
  }

  const int axis_size = input_shape[axis];
  int batch_size = 1;

  for (int i = 0; i < batch_dims; ++i) {
    batch_size *= input_shape[i];
  }
  int outer_size = 1;
  for (int i = batch_dims; i < axis; ++i) {
    outer_size *= input_shape[i];
  }
  int inner_size = 1;
  for (int i = axis + 1; i < input_dims; ++i) {
    inner_size *= input_shape[i];
  }
  int coord_size = 1;
  for (int i = batch_dims; i < coords_dims; ++i) {
    coord_size *= coords_shape[i];
  }

  for (int batch = 0; batch < batch_size; ++batch) {
    for (int outer = 0; outer < outer_size; ++outer) {
      for (int coord = 0; coord < coord_size; ++coord) {
        memcpy(output + (((batch * outer_size) + outer) * coord_size + coord) * inner_size,
               input + (((batch * outer_size) + outer) * axis_size + coords[batch * coord_size + coord]) *
               inner_size, sizeof(float) * inner_size);
      }
    }
  }
}

// Ported from TF
void MaximumFp(const float* input_1, const float* input_2,  float* output,
  const int32_t* input1_shape, int32_t input1_dims, const int32_t* input2_shape,
  int32_t input2_dims, const int32_t* output_shape, int32_t output_dims) {
  bool simple_mode = false;

  // Broadcast if all the dimensions of the input 1 & 2 don't match
  if (input1_dims == input2_dims) {
    for (int i=0; i < input1_dims; i++) {
      if (input1_shape[i] != input2_shape[i]) {
        simple_mode = false;
        break;
      } else {
        simple_mode = true;
      }
    }
  }

  if (simple_mode) {
    int flat_size = FlatSize(input1_shape, input1_dims);
    for (int i = 0; i < flat_size; ++i) {
      output[i] = (input_1[i] > input_2[i]) ? input_1[i] : input_2[i];
    }
  } else {
    NdArrayDesc desc1, desc2, output_desc;
    int32_t extended_out_shape[5];

    NdArrayDescsForElementwiseBroadcast(input1_shape, input1_dims, input2_shape,
      input2_dims, &desc1, &desc2, 5);
    ExtendedShape(output_shape, output_dims, extended_out_shape, 5);
    CopyDimsToDesc(extended_out_shape, &output_desc, 5);

    int indexes[5] = {0};
    for (indexes[0] = 0; indexes[0] < output_desc.extents[0]; ++indexes[0]) {
      for (indexes[1] = 0; indexes[1] < output_desc.extents[1]; ++indexes[1]) {
        for (indexes[2] = 0; indexes[2] < output_desc.extents[2]; ++indexes[2]) {
          for (indexes[3] = 0; indexes[3] < output_desc.extents[3]; ++indexes[3]) {
            for (indexes[4] = 0; indexes[4] < output_desc.extents[4]; ++indexes[4]) {
              float inp_1 = input_1[SubscriptToIndexArr5(desc1, indexes)];
              float inp_2 = input_2[SubscriptToIndexArr5(desc2, indexes)];
              output[SubscriptToIndexArr5(output_desc, indexes)] =
                  inp_1 > inp_2 ? inp_1 : inp_2;
            }
          }
        }
      }
    }
  }
}