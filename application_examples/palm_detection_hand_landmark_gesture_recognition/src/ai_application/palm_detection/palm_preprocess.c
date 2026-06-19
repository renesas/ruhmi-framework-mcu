/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "palm_preprocess.h"

#include <math.h>
#include <stddef.h>
#include <string.h>

static inline int clamp_int(int v, int lo, int hi) {
    if (v < lo) return lo;
    if (v > hi) return hi;
    return v;
}

static inline uint8_t sample_u8_bilinear(
    const uint8_t* src,
    int src_w,
    int src_h,
    int c,
    float x,
    float y
) {
    const int x0 = clamp_int((int)floorf(x), 0, src_w - 1);
    const int y0 = clamp_int((int)floorf(y), 0, src_h - 1);
    const int x1 = clamp_int(x0 + 1, 0, src_w - 1);
    const int y1 = clamp_int(y0 + 1, 0, src_h - 1);

    const float dx = x - (float)x0;
    const float dy = y - (float)y0;

    const size_t i00 = ((size_t)y0 * (size_t)src_w + (size_t)x0) * 3u + (size_t)c;
    const size_t i10 = ((size_t)y0 * (size_t)src_w + (size_t)x1) * 3u + (size_t)c;
    const size_t i01 = ((size_t)y1 * (size_t)src_w + (size_t)x0) * 3u + (size_t)c;
    const size_t i11 = ((size_t)y1 * (size_t)src_w + (size_t)x1) * 3u + (size_t)c;

    const float v00 = (float)src[i00];
    const float v10 = (float)src[i10];
    const float v01 = (float)src[i01];
    const float v11 = (float)src[i11];

    const float v0 = v00 + dx * (v10 - v00);
    const float v1 = v01 + dx * (v11 - v01);
    const float v = v0 + dy * (v1 - v0);

    int iv = (int)lrintf(v);
    iv = clamp_int(iv, 0, 255);
    return (uint8_t)iv;
}

static int preprocess_common(
    const uint8_t* src_u8,
    const palm_preprocess_config_t* cfg,
    palm_preprocess_meta_t* meta,
    void* dst,
    int output_int8
) {
    if (!src_u8 || !cfg || !dst) return -1;
    if (cfg->src_w <= 0 || cfg->src_h <= 0 || cfg->dst_w <= 0 || cfg->dst_h <= 0) return -2;

    const float ash = (float)cfg->dst_h / (float)cfg->src_h;
    const float asw = (float)cfg->dst_w / (float)cfg->src_w;
    const float s = (asw < ash) ? asw : ash;

    const int resized_w = (int)((float)cfg->src_w * s);
    const int resized_h = (int)((float)cfg->src_h * s);

    const int start_x = (int)((float)cfg->dst_w * 0.5f - (float)resized_w * 0.5f);
    const int start_y = (int)((float)cfg->dst_h * 0.5f - (float)resized_h * 0.5f);

    if (meta) {
        meta->square_standard_size = (cfg->src_h > cfg->src_w) ? cfg->src_h : cfg->src_w;
        meta->square_padding_half_size = (cfg->src_h > cfg->src_w)
            ? (cfg->src_h - cfg->src_w) / 2
            : (cfg->src_w - cfg->src_h) / 2;
        meta->resized_w = resized_w;
        meta->resized_h = resized_h;
        meta->start_x = start_x;
        meta->start_y = start_y;
    }

    if (output_int8) {
        // Quantized padding must represent float 0.0, i.e. input zero-point.
        // For this model zero-point is -128. Filling with 0 would represent ~0.5
        // after dequantization and severely distort background content.
        const int zp_fill = clamp_int(cfg->input_zero_point, -128, 127);
        const size_t n = (size_t)cfg->dst_w * (size_t)cfg->dst_h * 3u;
        for (size_t i = 0; i < n; ++i) {
            ((int8_t*)dst)[i] = (int8_t)zp_fill;
        }
    } else {
        memset(dst, 0, (size_t)cfg->dst_w * (size_t)cfg->dst_h * 3u * sizeof(float));
    }

    const float inv_s = 1.0f / s;

    for (int dy = 0; dy < resized_h; ++dy) {
        for (int dx = 0; dx < resized_w; ++dx) {
            const int out_x = start_x + dx;
            const int out_y = start_y + dy;

            const float src_x = ((float)dx + 0.5f) * inv_s - 0.5f;
            const float src_y = ((float)dy + 0.5f) * inv_s - 0.5f;

            uint8_t pix[3];
            pix[0] = sample_u8_bilinear(src_u8, cfg->src_w, cfg->src_h, 0, src_x, src_y);
            pix[1] = sample_u8_bilinear(src_u8, cfg->src_w, cfg->src_h, 1, src_x, src_y);
            pix[2] = sample_u8_bilinear(src_u8, cfg->src_w, cfg->src_h, 2, src_x, src_y);

            // python path converts BGR -> RGB via [..., ::-1]
            uint8_t rgb[3];
            if (cfg->input_is_bgr) {
                rgb[0] = pix[2];
                rgb[1] = pix[1];
                rgb[2] = pix[0];
            } else {
                rgb[0] = pix[0];
                rgb[1] = pix[1];
                rgb[2] = pix[2];
            }

            const float r = (float)rgb[0] / 255.0f;
            const float g = (float)rgb[1] / 255.0f;
            const float b = (float)rgb[2] / 255.0f;

            if (cfg->layout == PALM_LAYOUT_NHWC) {
                const size_t base = ((size_t)out_y * (size_t)cfg->dst_w + (size_t)out_x) * 3u;
                if (output_int8) {
                    const float inv_scale = (cfg->input_scale > 0.0f) ? (1.0f / cfg->input_scale) : 1.0f;
                    int qr = (int)lrintf(r * inv_scale + (float)cfg->input_zero_point);
                    int qg = (int)lrintf(g * inv_scale + (float)cfg->input_zero_point);
                    int qb = (int)lrintf(b * inv_scale + (float)cfg->input_zero_point);
                    qr = clamp_int(qr, -128, 127);
                    qg = clamp_int(qg, -128, 127);
                    qb = clamp_int(qb, -128, 127);
                    ((int8_t*)dst)[base + 0] = (int8_t)qr;
                    ((int8_t*)dst)[base + 1] = (int8_t)qg;
                    ((int8_t*)dst)[base + 2] = (int8_t)qb;
                } else {
                    ((float*)dst)[base + 0] = r;
                    ((float*)dst)[base + 1] = g;
                    ((float*)dst)[base + 2] = b;
                }
            } else {
                const size_t plane = (size_t)cfg->dst_w * (size_t)cfg->dst_h;
                const size_t idx = (size_t)out_y * (size_t)cfg->dst_w + (size_t)out_x;
                if (output_int8) {
                    const float inv_scale = (cfg->input_scale > 0.0f) ? (1.0f / cfg->input_scale) : 1.0f;
                    int qr = (int)lrintf(r * inv_scale + (float)cfg->input_zero_point);
                    int qg = (int)lrintf(g * inv_scale + (float)cfg->input_zero_point);
                    int qb = (int)lrintf(b * inv_scale + (float)cfg->input_zero_point);
                    qr = clamp_int(qr, -128, 127);
                    qg = clamp_int(qg, -128, 127);
                    qb = clamp_int(qb, -128, 127);
                    ((int8_t*)dst)[0 * plane + idx] = (int8_t)qr;
                    ((int8_t*)dst)[1 * plane + idx] = (int8_t)qg;
                    ((int8_t*)dst)[2 * plane + idx] = (int8_t)qb;
                } else {
                    ((float*)dst)[0 * plane + idx] = r;
                    ((float*)dst)[1 * plane + idx] = g;
                    ((float*)dst)[2 * plane + idx] = b;
                }
            }
        }
    }

    return 0;
}

int palm_preprocess_u8_to_int8(
    const uint8_t* src_u8,
    const palm_preprocess_config_t* cfg,
    int8_t* dst_i8,
    palm_preprocess_meta_t* meta
) {
    return preprocess_common(src_u8, cfg, meta, dst_i8, 1);
}

int palm_preprocess_u8_to_f32(
    const uint8_t* src_u8,
    const palm_preprocess_config_t* cfg,
    float* dst_f32,
    palm_preprocess_meta_t* meta
) {
    return preprocess_common(src_u8, cfg, meta, dst_f32, 0);
}
