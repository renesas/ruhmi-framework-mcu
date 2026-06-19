/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/


#ifndef PALM_PREPROCESS_H_
#define PALM_PREPROCESS_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    PALM_LAYOUT_NHWC = 0,
    PALM_LAYOUT_NCHW = 1,
} palm_tensor_layout_t;

typedef struct {
    int src_w;
    int src_h;
    int dst_w;
    int dst_h;

    // Quantization for INT8 model input.
    float input_scale;
    int input_zero_point;

    // Camera feed format (if 1: input is BGR; if 0: input is RGB).
    int input_is_bgr;

    // Output tensor layout expected by model.
    palm_tensor_layout_t layout;
} palm_preprocess_config_t;

typedef struct {
    // Used by post-processing center-y remap (same as python code).
    int square_standard_size;
    int square_padding_half_size;

    // Letterbox area in destination tensor.
    int resized_w;
    int resized_h;
    int start_x;
    int start_y;
} palm_preprocess_meta_t;

// Preprocess uint8 image -> INT8 model tensor.
// src_u8: interleaved HWC 3-channel image.
// dst_i8 size must be:
//   NHWC: dst_h * dst_w * 3
//   NCHW: 3 * dst_h * dst_w
int palm_preprocess_u8_to_int8(
    const uint8_t* src_u8,
    const palm_preprocess_config_t* cfg,
    int8_t* dst_i8,
    palm_preprocess_meta_t* meta
);

// Optional helper for float models (normalized [0,1]).
int palm_preprocess_u8_to_f32(
    const uint8_t* src_u8,
    const palm_preprocess_config_t* cfg,
    float* dst_f32,
    palm_preprocess_meta_t* meta
);

#ifdef __cplusplus
}
#endif

#endif  // PALM_PREPROCESS_H_
