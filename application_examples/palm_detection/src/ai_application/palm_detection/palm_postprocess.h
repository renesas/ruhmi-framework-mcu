/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef PALM_POSTPROCESS_H_
#define PALM_POSTPROCESS_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef PALM_PI
#define PALM_PI 3.14159265358979323846f
#endif

typedef struct {
    // [pd_score, box_x, box_y, box_size, kp0_x, kp0_y, kp2_x, kp2_y]
    float pd_score;
    float box_x;
    float box_y;
    float box_size;
    float kp0_x;
    float kp0_y;
    float kp2_x;
    float kp2_y;
} palm_box_t;

typedef struct {
    // Same convention as python app:
    // [sqn_rr_size, rotation, sqn_rr_center_x, sqn_rr_center_y]
    float sqn_rr_size;
    float rotation;
    float sqn_rr_center_x;
    float sqn_rr_center_y;
} palm_rotated_hand_t;

typedef struct {
    float score_thresh;   // e.g., 0.6
    float iou_thresh;     // e.g., 0.5
    int max_dets;         // e.g., 100
} palm_postprocess_config_t;

// Dequant helper for int8 tensors.
void palm_dequantize_i8(
    const int8_t* src,
    int count,
    float scale,
    int zero_point,
    float* dst
);

// Equivalent of palm_pre_nms_postprocess() in python.
// Inputs are normalized float tensors:
//   boxes_xyxy: [N,4], scores:[N], kp0_xy:[N,2], kp2_xy:[N,2]
// Returns number of detections written to out_boxes.
int palm_postprocess_pre_nms(
    const float* boxes_xyxy,
    const float* scores,
    const float* kp0_xy,
    const float* kp2_xy,
    int num_anchors,
    const palm_postprocess_config_t* cfg,
    palm_box_t* out_boxes,
    int out_capacity
);

// Equivalent of _to_rotated_hands() in python app.
// image_h: original camera image height.
// square_standard_size and square_padding_half_size come from preprocess meta.
int palm_boxes_to_rotated_hands(
    const palm_box_t* boxes,
    int box_count,
    int image_h,
    int square_standard_size,
    int square_padding_half_size,
    palm_rotated_hand_t* out_hands,
    int out_capacity
);

#ifdef __cplusplus
}
#endif

#endif  // PALM_POSTPROCESS_H_
