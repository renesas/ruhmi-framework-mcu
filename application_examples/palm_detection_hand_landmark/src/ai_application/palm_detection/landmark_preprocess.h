#ifndef LANDMARK_PREPROCESS_H_
#define LANDMARK_PREPROCESS_H_

#include <stdint.h>
#include "palm_postprocess.h"   /* palm_rotated_hand_t */

#ifdef __cplusplus
extern "C" {
#endif

/* ------------------------------------------------------------------ */
/* Hand-landmark model input: [1, 224, 224, 3]  INT8  NHWC            */
/*   quant: scale = 1/255 ≈ 0.003921569,  zero_point = -128          */
/*   i.e. int8_val = (int8_t)(uint8_pixel - 128)                     */
/* ------------------------------------------------------------------ */
#define LANDMARK_INPUT_W   224
#define LANDMARK_INPUT_H   224
#define LANDMARK_INPUT_C   3
#define LANDMARK_INPUT_SIZE (LANDMARK_INPUT_W * LANDMARK_INPUT_H * LANDMARK_INPUT_C)

/* Scale factor applied to the palm bounding-box size to get the     */
/* hand-landmark crop rectangle (same as Python pipeline).            */
#define LANDMARK_CROP_SCALE  2.6f

typedef struct {
    /* Original image dimensions */
    int img_w;
    int img_h;

    /* 1 = source image is BGR (camera), 0 = already RGB */
    int input_is_bgr;

    /* 1 = source is RGB565 (uint16_t*), 0 = source is RGB888 (uint8_t*) */
    int input_is_rgb565;
} landmark_preprocess_config_t;

typedef struct {
    /* Pixel-coordinate rect that was cropped (for postprocess remap) */
    float cx;           /* center x in original image pixels */
    float cy;           /* center y in original image pixels */
    float rect_w;       /* crop rect width  in pixels */
    float rect_h;       /* crop rect height in pixels */
    float angle_rad;    /* rotation in radians */

    /* keep-aspect resize metadata inside the 224×224 tensor */
    float resize_scale_w;   /* resized_w / crop_w */
    float resize_scale_h;   /* resized_h / crop_h */
    int   half_pad_w;       /* horizontal padding / 2 */
    int   half_pad_h;       /* vertical   padding / 2 */
} landmark_preprocess_meta_t;

/**
 * Crop a rotated rectangle from the source image, resize with keep-aspect
 * padding to 224×224, and quantize to INT8.
 *
 * Supports both RGB888 (uint8_t*) and RGB565 (uint16_t*) source images
 * controlled by cfg->input_is_rgb565.
 *
 * @param src        Source image pointer (cast to void* — actual type depends
 *                   on cfg->input_is_rgb565: uint8_t* for RGB888, uint16_t* for RGB565).
 * @param cfg        Image dimensions and format.
 * @param hand       Rotated hand rect from palm postprocess.
 * @param dst_i8     Output INT8 NHWC tensor, must be >= LANDMARK_INPUT_SIZE.
 * @param meta       [out] Metadata for postprocess coordinate remap.
 * @return 0 on success, <0 on error.
 */
int landmark_preprocess(
    const void* src,
    const landmark_preprocess_config_t* cfg,
    const palm_rotated_hand_t* hand,
    int8_t* dst_i8,
    landmark_preprocess_meta_t* meta
);

#ifdef __cplusplus
}
#endif

#endif /* LANDMARK_PREPROCESS_H_ */
