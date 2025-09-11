#ifndef __KERNEL_LIBRARY_INT__
#define __KERNEL_LIBRARY_INT__

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <math.h>

#include "kernel_library_utils.h"


/****************************************************************************/
/*                               Integer Operators                          */
/****************************************************************************/

void AffineQuantizeFloatToInt8(const float* input, int8_t* output, uint32_t size, int8_t output_zp, float output_scale);
void AffineDequantizeUInt8ToFloat(const uint8_t* input, float* output, uint32_t size, int8_t input_zp, float input_scale);
void AffineDequantizeInt8ToFloat(const int8_t* input, float* output, uint32_t size, int8_t input_zp, float input_scale);
void Requantize(const uint8_t* input, int8_t* output, uint32_t size, int32_t multiplier, int32_t shift,
  int32_t input_zp, int32_t output_zp);
void RequantizeInt8ToUint8(const int8_t* input_data, uint8_t* output_data,
  uint32_t size, int32_t multiplier, int32_t shift, int32_t input_zp,
  int32_t output_zp);
void Sigmoid(const int8_t *input, int8_t *output, uint32_t size,
  int32_t input_zp, float input_scale, int32_t output_zp, float output_scale);
void Minimum(const int8_t* input_1, const int8_t* input_2,  int8_t* output,
  const int32_t* input1_shape, int32_t input1_dims, const int32_t* input2_shape,
  int32_t input2_dims, const int32_t* output_shape, int32_t output_dims);
void Tanh(const int8_t* input, int8_t* output, uint32_t size, float input_scale, int8_t input_zp,
  float output_scale, int8_t output_zp);

void Slice(const int8_t* input, int8_t* output, const int32_t* begin, const int32_t* size,
  const int32_t* in_shape, int32_t dims);
void StridedSlice(const int8_t* input, int8_t* output, const int32_t* begin_orig,
  const int32_t* end_orig, const int32_t* strides, const int32_t* in_shape, int32_t in_dims,
  const int32_t* out_shape, int32_t out_dims, TfLiteStridedSliceParams str_slc_params);

void Pack(const int8_t **inputs, uint32_t inp_count, int8_t* output, uint32_t size, uint32_t slice_size, uint32_t stride);
void Mean(const int8_t* input, int8_t* output, const int32_t* in_shape, const int32_t in_num_dims,
  int32_t input_zp, int32_t out_size, int32_t output_multiplier, int32_t output_shift, int32_t output_zp,
  const int32_t* axis, const int32_t num_axis);
void Sum(const int8_t* input, int8_t* output, const int32_t* in_shape, int32_t in_num_dims,
  int32_t input_zp, int32_t out_size, int32_t output_multiplier, int32_t output_shift,
  int32_t output_zp, const int32_t* axis, int32_t num_axis);
void ReduceMax(const int8_t* input, int8_t* output, const int32_t* in_shape, const int32_t in_num_dims,
   int32_t out_size, const int32_t* axis, const int32_t num_axis);
void Exp(const int8_t *input, int8_t *output, uint32_t size, 
  int32_t input_zp, float input_scale, int32_t output_zp, float output_scale);
void Log(const int8_t *input, int8_t *output, uint32_t size, 
  int32_t input_zp, float input_scale, int32_t output_zp, float output_scale);
void Neg(const float* input,  float* output, uint32_t size);
void LeakyRelu(const int8_t* input, int8_t* output, uint32_t size, int32_t input_zp, int32_t output_zp,
  int32_t output_multiplier_alpha, int32_t output_shift_alpha, int32_t output_multiplier_identity,
  int32_t output_shift_identity);
void LogSoftMax(const int8_t* input, int8_t* output, const int32_t* in_shape, const int32_t in_num_dims,
  int32_t input_zp, float input_scale, int32_t output_zp, float output_scale);
void SpaceToBatchNd(const int8_t* input1_data, int8_t* output_data, const int32_t* block_shape, const int32_t* pad,
  const int32_t* in_shape, const int32_t in_num_dims, const int32_t* out_shape, int32_t output_zp);
void BatchToSpaceNd(const int8_t* input1_data, int8_t* output_data, const int32_t* block_shape, const int32_t* crops,
  const int32_t* in_shape, const int32_t in_num_dims, const int32_t* out_shape, int32_t output_zp);
void Transpose(const int8_t *input, int8_t *output, int32_t size, int32_t rank, int32_t *strides, 
  int32_t *next_dim_sizes, int32_t *dim_sizes);
void ResizeBilinear(const int8_t* input_data, int8_t* output_data, const int32_t* input_shape,
  const int32_t* output_shape, bool half_pixel_centers, bool align_corners);
void MirrorPad(const int32_t* padding_matrix,
  const int* input_dims, int* output_dims_num_elements,
  int* input_dims_num_elements, const int8_t* input_data,
  int8_t* output_data, const int offset, const int num_dims,
  const int output_size);
void UpsamplingNearestNeighbor(const int8_t *input, int8_t *output, const int32_t *in_shape,
  const int32_t *out_shape, const bool align_corners,  const bool half_pixel_centers);

void PRelu(const int8_t* input, const int32_t *in_shape, int32_t in_dims, int32_t input_zp,
  int8_t* output, const int32_t *out_shape, int32_t out_dims, int32_t output_zp,
  const int8_t *alpha, const int32_t *alpha_shape, int32_t alpha_dims, int32_t alpha_zp,
  int32_t output_multiplier_alpha, int32_t output_shift_alpha, int32_t output_multiplier_identity,
  int32_t output_shift_identity);
void Relu(const int8_t *input, int8_t *output, uint32_t size, int32_t input_zp,
  float output_scale, int32_t output_zp, int32_t output_multiplier, int32_t output_shift);
void Relu6(const int8_t *input, int8_t *output, uint32_t size, int32_t input_zp,
  float input_scale, int32_t output_zp, float output_scale);

void Abs(const int8_t* input, int32_t input_zp, int32_t size, int8_t* output,
  int32_t output_zp, int32_t multiplier, int32_t shift);
void Mul(const int8_t* input1, const int32_t* input1_shape, int32_t input1_dims,
  const int8_t* input2, const int32_t* input2_shape, int32_t input2_dims, int8_t* output,
  const int32_t* output_shape, int32_t output_dims, ArithmeticParams quant_params);

void Sub(const int8_t* input1, const int8_t* input2, int8_t* output,
  const int32_t* input1_shape, int32_t input1_dims, const int32_t* input2_shape,
  int32_t input2_dims, const int32_t* output_shape, int32_t output_dims,
  ArithmeticParams quant_params);
void SubElementwise(const int8_t* input1_data, const int8_t* input2_data,
  int8_t* output_data, int32_t size, ArithmeticParams quant_params);
void BroadcastSubSlowInt8(const int32_t* input1_shape, const int8_t* input1_data,
  int32_t input1_dims, const int32_t* input2_shape, const int8_t* input2_data,
  int32_t input2_dims, const int32_t* output_shape, int8_t* output_data,
  int32_t output_dims, ArithmeticParams quant_params);
bool ReduceDimensionsForBroadcast(const int32_t* input1_dims, int32_t num_input1_dims,
  const int32_t* input2_dims, int32_t num_input2_dims, size_t* compressed_input1_stride,
  size_t* compressed_input2_stride, size_t* compressed_output_shape);
void BroadcastSubRecursiveDimensions(int dimension, int32_t* input1_offset_p, int32_t* input2_offset_p,
  int32_t* output_offset, size_t* compressed_input1_stride, size_t* compressed_input2_stride,
  size_t* compressed_output_shape, ArithmeticParams quant_params, const int8_t* input1_data,
  const int8_t* input2_data, int8_t* output_data);
void SubBroadcast(const int8_t* input_data, const int8_t* broadcast_data,
  int8_t* output_data, int32_t size, ArithmeticParams quant_params);

int8_t AddOp(int8_t input1, int8_t input2, ArithmeticParams quant_params);
void BroadcastInput1(const int8_t* input1, const int8_t* input2, int8_t* output,
  ArithmeticParams quant_params, int size);
void BroadcastInput2(const int8_t* input1, const int8_t* input2, int8_t* output,
  ArithmeticParams quant_params, int size);
void ElementWise(const int8_t* input1, const int8_t* input2, int8_t* output,
  ArithmeticParams quant_params, int size);
void BroadcastAddRecursiveDimensions(const int8_t* input1, size_t* input1_offset_p,
  size_t* compressed_input1_stride, const int8_t* input2, size_t* input2_offset_p,
  size_t* compressed_input2_stride, int8_t* output, size_t* output_offset,
  size_t* compressed_output_shape, ArithmeticParams quant_params, int dimension);
void BroadcastBinaryFunction6DSlow(const int8_t* input1, const int32_t* input1_shape,
  int32_t input1_dims, const int8_t* input2, const int32_t* input2_shape,
  int32_t input2_dims, int8_t* output, const int32_t* output_shape, int32_t output_dims,
  ArithmeticParams quant_params);
void Add(const int8_t* input1, const int32_t* input1_shape, int32_t input1_dims,
  const int8_t* input2, const int32_t* input2_shape, int32_t input2_dims, int8_t* output,
  const int32_t* output_shape, int32_t output_dims, ArithmeticParams quant_params);
void Pad(int32_t left_padding_count, int32_t *left_padding,
  int32_t right_padding_count, int32_t *right_padding,
  int32_t *ext_input_shape, const int8_t *input_data,
  const int8_t pad_value, const int32_t *ext_output_shape,
  int8_t *output_data);

#endif /*  __KERNEL_LIBRARY_INT__ */
