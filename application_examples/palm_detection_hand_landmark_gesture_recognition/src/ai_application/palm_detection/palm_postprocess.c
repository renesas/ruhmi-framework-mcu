/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/


#include "palm_postprocess.h"

#include <math.h>
#include <stddef.h>

static inline float maxf(float a, float b) { return (a > b) ? a : b; }
static inline float minf(float a, float b) { return (a < b) ? a : b; }

static float normalize_radians(float angle) {
    return angle - 2.0f * PALM_PI * floorf((angle + PALM_PI) / (2.0f * PALM_PI));
}

static float iou_xyxy(const float* a, const float* b) {
    // a,b = [x1,y1,x2,y2]
    const float ix1 = maxf(a[0], b[0]);
    const float iy1 = maxf(a[1], b[1]);
    const float ix2 = minf(a[2], b[2]);
    const float iy2 = minf(a[3], b[3]);

    const float iw = maxf(0.0f, ix2 - ix1);
    const float ih = maxf(0.0f, iy2 - iy1);
    const float inter = iw * ih;

    const float area_a = maxf(0.0f, a[2] - a[0]) * maxf(0.0f, a[3] - a[1]);
    const float area_b = maxf(0.0f, b[2] - b[0]) * maxf(0.0f, b[3] - b[1]);
    const float uni = area_a + area_b - inter;

    return (uni <= 0.0f) ? 0.0f : (inter / uni);
}

void palm_dequantize_i8(
    const int8_t* src,
    int count,
    float scale,
    int zero_point,
    float* dst
) {
    if (!src || !dst || count <= 0) return;
    for (int i = 0; i < count; ++i) {
        dst[i] = ((float)src[i] - (float)zero_point) * scale;
    }
}

int palm_postprocess_pre_nms(
    const float* boxes_xyxy,
    const float* scores,
    const float* kp0_xy,
    const float* kp2_xy,
    int num_anchors,
    const palm_postprocess_config_t* cfg,
    palm_box_t* out_boxes,
    int out_capacity
) {
    if (!boxes_xyxy || !scores || !kp0_xy || !kp2_xy || !cfg || !out_boxes) return -1;
    if (num_anchors <= 0 || out_capacity <= 0) return 0;

    // Selection-sort-like process on filtered candidates (no malloc).
    // 1) gather valid indices up to num_anchors in temp arrays on stack if reasonable.
    // We avoid VLAs for portability and do two-pass greedy selection instead.

    int out_count = 0;

    // Keep list of already selected anchor indices (in original anchor space).
    // out_capacity is max_dets at runtime (usually <= 100), so this is small.
    int selected_idx[256];
    if (cfg->max_dets > 256 || out_capacity > 256) {
        // Keep implementation simple and safe without dynamic allocation.
        return -2;
    }

    const int target = (cfg->max_dets < out_capacity) ? cfg->max_dets : out_capacity;

    // Greedy NMS by repeatedly picking best remaining score.
    for (int det = 0; det < target; ++det) {
        int best_i = -1;
        float best_s = -1.0f;

        for (int i = 0; i < num_anchors; ++i) {
            const float s = scores[i];
            if (s < cfg->score_thresh) continue;

            // skip if already selected
            int already = 0;
            for (int k = 0; k < out_count; ++k) {
                if (selected_idx[k] == i) {
                    already = 1;
                    break;
                }
            }
            if (already) continue;

            // NMS check against selected boxes
            const float* bi = &boxes_xyxy[(size_t)i * 4u];
            int suppressed = 0;
            for (int k = 0; k < out_count; ++k) {
                const int j = selected_idx[k];
                const float* bj = &boxes_xyxy[(size_t)j * 4u];
                if (iou_xyxy(bi, bj) > cfg->iou_thresh) {
                    suppressed = 1;
                    break;
                }
            }
            if (suppressed) continue;

            if (s > best_s) {
                best_s = s;
                best_i = i;
            }
        }

        if (best_i < 0) break;

        selected_idx[out_count] = best_i;

        const float* b = &boxes_xyxy[(size_t)best_i * 4u];
        const float x1 = b[0];
        const float y1 = b[1];
        const float x2 = b[2];
        const float y2 = b[3];

        const float box_w = maxf(0.0f, x2 - x1);
        const float box_h = maxf(0.0f, y2 - y1);
        const float box_size = maxf(box_w, box_h);
        const float box_x = x1 + 0.5f * box_w;
        const float box_y = y1 + 0.5f * box_h;

        out_boxes[out_count].pd_score = scores[best_i];
        out_boxes[out_count].box_x = box_x;
        out_boxes[out_count].box_y = box_y;
        out_boxes[out_count].box_size = box_size;
        out_boxes[out_count].kp0_x = kp0_xy[(size_t)best_i * 2u + 0u];
        out_boxes[out_count].kp0_y = kp0_xy[(size_t)best_i * 2u + 1u];
        out_boxes[out_count].kp2_x = kp2_xy[(size_t)best_i * 2u + 0u];
        out_boxes[out_count].kp2_y = kp2_xy[(size_t)best_i * 2u + 1u];

        out_count++;
    }

    return out_count;
}

int palm_boxes_to_rotated_hands(
    const palm_box_t* boxes,
    int box_count,
    int image_h,
    int square_standard_size,
    int square_padding_half_size,
    palm_rotated_hand_t* out_hands,
    int out_capacity
) {
    if (!boxes || !out_hands || image_h <= 0 || out_capacity <= 0) return -1;

    int count = 0;
    for (int i = 0; i < box_count && count < out_capacity; ++i) {
        const float box_size = boxes[i].box_size;
        if (box_size <= 0.0f) continue;

        const float kp02_x = boxes[i].kp2_x - boxes[i].kp0_x;
        const float kp02_y = boxes[i].kp2_y - boxes[i].kp0_y;

        const float sqn_rr_size = 2.9f * box_size;
        float rotation = 0.5f * PALM_PI - atan2f(-kp02_y, kp02_x);
        rotation = normalize_radians(rotation);

        const float sqn_rr_center_x = boxes[i].box_x + 0.5f * box_size * sinf(rotation);
        float sqn_rr_center_y = boxes[i].box_y - 0.5f * box_size * cosf(rotation);

        sqn_rr_center_y =
            (sqn_rr_center_y * (float)square_standard_size - (float)square_padding_half_size) /
            (float)image_h;

        out_hands[count].sqn_rr_size = sqn_rr_size;
        out_hands[count].rotation = rotation;
        out_hands[count].sqn_rr_center_x = sqn_rr_center_x;
        out_hands[count].sqn_rr_center_y = sqn_rr_center_y;
        count++;
    }

    return count;
}
