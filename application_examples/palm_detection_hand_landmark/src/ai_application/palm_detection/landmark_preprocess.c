/*
 * landmark_preprocess.c
 *
 * Crop a rotated palm rectangle from the source image, resize with
 * keep-aspect padding to 224×224, and quantize to INT8 NHWC.
 *
 * Supports both RGB888 (uint8_t*) and RGB565 (uint16_t*) source inputs.
 * For the camera+LCD project the source is the raw RGB565 camera buffer,
 * avoiding an intermediate RGB888 conversion.
 */

#include "landmark_preprocess.h"

#include <math.h>
#include <stddef.h>
#include <string.h>

/* ------------------------------------------------------------------ */
/* Helpers                                                            */
/* ------------------------------------------------------------------ */

static inline int clamp_i(int v, int lo, int hi) {
    if (v < lo) return lo;
    if (v > hi) return hi;
    return v;
}

/* Bilinear sample from HWC RGB888 uint8 image, channel c */
static inline uint8_t sample_bilinear_rgb888(
    const uint8_t* img, int w, int h,
    int ch, float x, float y)
{
    int x0 = (int)floorf(x);
    int y0 = (int)floorf(y);
    int x1 = x0 + 1;
    int y1 = y0 + 1;

    x0 = clamp_i(x0, 0, w - 1);
    x1 = clamp_i(x1, 0, w - 1);
    y0 = clamp_i(y0, 0, h - 1);
    y1 = clamp_i(y1, 0, h - 1);

    float dx = x - floorf(x);
    float dy = y - floorf(y);

    float v00 = (float)img[((size_t)y0 * w + x0) * 3 + ch];
    float v10 = (float)img[((size_t)y0 * w + x1) * 3 + ch];
    float v01 = (float)img[((size_t)y1 * w + x0) * 3 + ch];
    float v11 = (float)img[((size_t)y1 * w + x1) * 3 + ch];

    float top = v00 + dx * (v10 - v00);
    float bot = v01 + dx * (v11 - v01);
    float val = top + dy * (bot - top);

    return (uint8_t)clamp_i((int)lrintf(val), 0, 255);
}

/* Extract R, G, B (8-bit) from a single RGB565 pixel */
static inline void rgb565_to_rgb888(uint16_t px, uint8_t* r, uint8_t* g, uint8_t* b) {
    *r = (uint8_t)(((px >> 11) & 0x1F) << 3);
    *g = (uint8_t)(((px >> 5)  & 0x3F) << 2);
    *b = (uint8_t)(( px        & 0x1F) << 3);
}

/* Bilinear sample from RGB565 image, return one RGB888 channel (0=R, 1=G, 2=B) */
static inline uint8_t sample_bilinear_rgb565(
    const uint16_t* img, int w, int h,
    int ch, float x, float y)
{
    int x0 = (int)floorf(x);
    int y0 = (int)floorf(y);
    int x1 = x0 + 1;
    int y1 = y0 + 1;

    x0 = clamp_i(x0, 0, w - 1);
    x1 = clamp_i(x1, 0, w - 1);
    y0 = clamp_i(y0, 0, h - 1);
    y1 = clamp_i(y1, 0, h - 1);

    float dx = x - floorf(x);
    float dy = y - floorf(y);

    /* Decode all 4 pixels */
    uint8_t r, g, b;
    float vals[4];
    uint16_t px;

    px = img[(size_t)y0 * w + x0];
    rgb565_to_rgb888(px, &r, &g, &b);
    vals[0] = (ch == 0) ? (float)r : (ch == 1) ? (float)g : (float)b;

    px = img[(size_t)y0 * w + x1];
    rgb565_to_rgb888(px, &r, &g, &b);
    vals[1] = (ch == 0) ? (float)r : (ch == 1) ? (float)g : (float)b;

    px = img[(size_t)y1 * w + x0];
    rgb565_to_rgb888(px, &r, &g, &b);
    vals[2] = (ch == 0) ? (float)r : (ch == 1) ? (float)g : (float)b;

    px = img[(size_t)y1 * w + x1];
    rgb565_to_rgb888(px, &r, &g, &b);
    vals[3] = (ch == 0) ? (float)r : (ch == 1) ? (float)g : (float)b;

    float top = vals[0] + dx * (vals[1] - vals[0]);
    float bot = vals[2] + dx * (vals[3] - vals[2]);
    float val = top + dy * (bot - top);

    return (uint8_t)clamp_i((int)lrintf(val), 0, 255);
}

/* ------------------------------------------------------------------ */
/* Main function                                                      */
/* ------------------------------------------------------------------ */

int landmark_preprocess(
    const void* src,
    const landmark_preprocess_config_t* cfg,
    const palm_rotated_hand_t* hand,
    int8_t* dst_i8,
    landmark_preprocess_meta_t* meta)
{
    if (!src || !cfg || !hand || !dst_i8) return -1;

    const int img_w = cfg->img_w;
    const int img_h = cfg->img_h;
    if (img_w <= 0 || img_h <= 0) return -2;

    const int is_rgb565 = cfg->input_is_rgb565;

    /* ---------------------------------------------------------------
     * 1. Convert palm_rotated_hand_t → pixel-coord rotated rect
     * --------------------------------------------------------------- */
    const float cx  = hand->sqn_rr_center_x * (float)img_w;
    const float cy  = hand->sqn_rr_center_y * (float)img_h;

    const float ref = (float)((img_w > img_h) ? img_w : img_h);
    float crop_size = hand->sqn_rr_size * ref;
    if (crop_size < 1.0f) crop_size = 1.0f;

    const float rect_w = crop_size;
    const float rect_h = crop_size;
    const float angle  = hand->rotation;

    /* ---------------------------------------------------------------
     * 2. Compute keep-aspect resize parameters
     * --------------------------------------------------------------- */
    const float scale_w = (float)LANDMARK_INPUT_W / rect_w;
    const float scale_h = (float)LANDMARK_INPUT_H / rect_h;
    const float s = (scale_w < scale_h) ? scale_w : scale_h;

    const int resized_w = (int)(rect_w * s);
    const int resized_h = (int)(rect_h * s);

    const int pad_w = LANDMARK_INPUT_W - resized_w;
    const int pad_h = LANDMARK_INPUT_H - resized_h;
    const int half_pad_w = pad_w / 2;
    const int half_pad_h = pad_h / 2;

    if (meta) {
        meta->cx      = cx;
        meta->cy      = cy;
        meta->rect_w  = rect_w;
        meta->rect_h  = rect_h;
        meta->angle_rad    = angle;
        meta->resize_scale_w = s;
        meta->resize_scale_h = s;
        meta->half_pad_w     = half_pad_w;
        meta->half_pad_h     = half_pad_h;
    }

    /* ---------------------------------------------------------------
     * 3. Fill output tensor with zero-point value (= -128)
     * --------------------------------------------------------------- */
    memset(dst_i8, (int)(int8_t)(-128), (size_t)LANDMARK_INPUT_SIZE);

    /* ---------------------------------------------------------------
     * 4. Single-pass inverse-mapping
     * --------------------------------------------------------------- */
    const float cos_a = cosf(angle);
    const float sin_a = sinf(angle);
    const float inv_s = 1.0f / s;

    for (int oy = 0; oy < resized_h; ++oy) {
        for (int ox = 0; ox < resized_w; ++ox) {
            const float crop_x = ((float)ox + 0.5f) * inv_s;
            const float crop_y = ((float)oy + 0.5f) * inv_s;

            const float rel_x = crop_x - rect_w * 0.5f;
            const float rel_y = crop_y - rect_h * 0.5f;

            const float src_x = cx + rel_x * cos_a - rel_y * sin_a;
            const float src_y = cy + rel_x * sin_a + rel_y * cos_a;

            if (src_x < -0.5f || src_x >= (float)img_w ||
                src_y < -0.5f || src_y >= (float)img_h) {
                continue;
            }

            uint8_t r, g, b;

            if (is_rgb565) {
                const uint16_t* src16 = (const uint16_t*)src;
                r = sample_bilinear_rgb565(src16, img_w, img_h, 0, src_x, src_y);
                g = sample_bilinear_rgb565(src16, img_w, img_h, 1, src_x, src_y);
                b = sample_bilinear_rgb565(src16, img_w, img_h, 2, src_x, src_y);
            } else {
                const uint8_t* src_u8 = (const uint8_t*)src;
                uint8_t pix[3];
                pix[0] = sample_bilinear_rgb888(src_u8, img_w, img_h, 0, src_x, src_y);
                pix[1] = sample_bilinear_rgb888(src_u8, img_w, img_h, 1, src_x, src_y);
                pix[2] = sample_bilinear_rgb888(src_u8, img_w, img_h, 2, src_x, src_y);

                if (cfg->input_is_bgr) {
                    r = pix[2]; g = pix[1]; b = pix[0];
                } else {
                    r = pix[0]; g = pix[1]; b = pix[2];
                }
            }

            /* Quantize: scale=1/255, zp=-128 → int8 = uint8 - 128 */
            const int dst_x = half_pad_w + ox;
            const int dst_y = half_pad_h + oy;
            const size_t base = ((size_t)dst_y * LANDMARK_INPUT_W + dst_x) * 3;

            dst_i8[base + 0] = (int8_t)((int)r - 128);
            dst_i8[base + 1] = (int8_t)((int)g - 128);
            dst_i8[base + 2] = (int8_t)((int)b - 128);
        }
    }

    return 0;
}
