#ifndef LANDMARK_POSTPROCESS_H_
#define LANDMARK_POSTPROCESS_H_

#include <stdint.h>
#include "landmark_preprocess.h"   /* landmark_preprocess_meta_t */

#ifdef __cplusplus
extern "C" {
#endif

/* ------------------------------------------------------------------ */
/* Hand-landmark model outputs (INT8):                                */
/*   PartitionedCall_0  [1,63]  21 XYZ  scale=1.1077, zp=-43         */
/*   PartitionedCall_1  [1, 1]  hand_score  scale=0.003906, zp=-128  */
/*   PartitionedCall_2  [1, 1]  handedness  scale=0.003906, zp=-128  */
/* ------------------------------------------------------------------ */

#define LANDMARK_NUM_POINTS  21
#define LANDMARK_XYZ_LEN     (LANDMARK_NUM_POINTS * 3)   /* 63 */

/* Quantization parameters (from TFLite model) */
#define LANDMARK_XYZ_SCALE     1.1076668f
#define LANDMARK_XYZ_ZP        (-43)
#define LANDMARK_SCORE_SCALE   0.00390625f
#define LANDMARK_SCORE_ZP      (-128)
#define LANDMARK_HAND_SCALE    0.00390625f
#define LANDMARK_HAND_ZP       (-128)

typedef struct {
    int32_t x;   /* pixel X in original image */
    int32_t y;   /* pixel Y in original image */
} landmark_point_t;

typedef struct {
    float hand_score;           /* sigmoid-like score 0..1 */
    float handedness;           /* 0 = left, 1 = right */
    int   num_points;           /* always 21 */
    landmark_point_t pts[LANDMARK_NUM_POINTS];
} landmark_result_t;

/**
 * Dequantize + threshold + remap 21 landmarks back to original image coords.
 *
 * @param xyz_i8       INT8 output [63], from GetModelOutputPtr__landmark_PartitionedCall_0_70174
 * @param score_i8     INT8 output [1],  from GetModelOutputPtr__landmark_PartitionedCall_1_70170
 * @param hand_i8      INT8 output [1],  from GetModelOutputPtr__landmark_PartitionedCall_2_70172
 * @param meta         Preprocess metadata (cx, cy, rect_w, angle, resize_scale, pad)
 * @param score_thresh Minimum hand score to accept (e.g. 0.5)
 * @param result       [out] Filled if score > threshold
 * @return 1 if a valid hand was found (score > threshold), 0 otherwise, <0 on error
 */
int landmark_postprocess(
    const int8_t* xyz_i8,
    const int8_t* score_i8,
    const int8_t* hand_i8,
    const landmark_preprocess_meta_t* meta,
    float score_thresh,
    landmark_result_t* result
);

#ifdef __cplusplus
}
#endif

#endif /* LANDMARK_POSTPROCESS_H_ */
