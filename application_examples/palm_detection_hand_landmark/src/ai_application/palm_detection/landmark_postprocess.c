/*
 * landmark_postprocess.c
 *
 * Dequantize hand-landmark INT8 outputs, apply score threshold, and
 * remap the 21 XYZ keypoints from the 224×224 tensor coordinate space
 * back to original image pixel coordinates.
 *
 * Matches the Python pipeline in hand_landmark.py __postprocess():
 *   1. Dequantize score → threshold
 *   2. Dequantize XYZ [63] → normalized coords in 224×224
 *   3. rrn_lms / input_h  → [0..1] range
 *   4. rescaled_xy = (lm * 224 - half_pad) / resize_scale → crop-local px
 *   5. Rotate crop-local px back to original image using rotation matrix
 *   6. Translate by (cx - rotated_half_w, cy - rotated_half_h)
 */

#include "landmark_postprocess.h"

#include <math.h>
#include <string.h>

/* ------------------------------------------------------------------ */
/* Helpers                                                            */
/* ------------------------------------------------------------------ */

static inline float dequant(int8_t val, float scale, int zp) {
    return ((float)val - (float)zp) * scale;
}

/* ------------------------------------------------------------------ */
/* Main function                                                      */
/* ------------------------------------------------------------------ */

int landmark_postprocess(
    const int8_t* xyz_i8,
    const int8_t* score_i8,
    const int8_t* hand_i8,
    const landmark_preprocess_meta_t* meta,
    float score_thresh,
    landmark_result_t* result)
{
    if (!xyz_i8 || !score_i8 || !hand_i8 || !meta || !result) return -1;

    memset(result, 0, sizeof(*result));

    /* 1. Dequantize scalar outputs */
    const float hand_score = dequant(score_i8[0], LANDMARK_SCORE_SCALE, LANDMARK_SCORE_ZP);
    const float handedness = dequant(hand_i8[0],  LANDMARK_HAND_SCALE,  LANDMARK_HAND_ZP);

    result->hand_score = hand_score;
    result->handedness = handedness;
    result->num_points = LANDMARK_NUM_POINTS;

    /* 2. Threshold check */
    if (hand_score < score_thresh) {
        return 0;  /* no valid hand */
    }

    /* 3. Dequantize XYZ landmarks */
    float xyz[LANDMARK_XYZ_LEN];
    for (int i = 0; i < LANDMARK_XYZ_LEN; ++i) {
        xyz[i] = dequant(xyz_i8[i], LANDMARK_XYZ_SCALE, LANDMARK_XYZ_ZP);
    }

    /* 4. Normalize to [0..1] by dividing by input_h (=224) */
    const float inv_h = 1.0f / (float)LANDMARK_INPUT_H;
    for (int i = 0; i < LANDMARK_XYZ_LEN; ++i) {
        xyz[i] *= inv_h;
    }

    /* 5. For each of the 21 keypoints, remap to original image coords.
     *
     *    Python equivalent:
     *      rescaled_xy[:,0] = (lm_x * 224 - half_pad_w) / resize_scale_w
     *      rescaled_xy[:,1] = (lm_y * 224 - half_pad_h) / resize_scale_h
     *    Then rotate by -angle around crop center, translate to image coords.
     */
    const float scale_w = meta->resize_scale_w;
    const float scale_h = meta->resize_scale_h;
    const float angle   = meta->angle_rad;
    const float cx      = meta->cx;
    const float cy      = meta->cy;
    const float rect_w  = meta->rect_w;
    const float rect_h  = meta->rect_h;

    /* Rotation matrix for rotating points from crop-local to image coords.
     * Same rotation direction as preprocess (clockwise by angle). */
    const float cos_a = cosf(angle);
    const float sin_a = sinf(angle);

    /* Compute the rotated bounding box size (for the final translation).
     * Python: bound_w = h*|sin| + w*|cos|, bound_h = h*|cos| + w*|sin|
     * The crop is rect_w × rect_h before resize. After resize it becomes
     * resized_w × resized_h, then un-resized back to rect_w × rect_h for
     * coordinate remapping. The rotation bounding box is computed on the
     * crop dimensions. */
    const float abs_cos = fabsf(cos_a);
    const float abs_sin = fabsf(sin_a);

    /* crop-local dimensions (before resize) */
    const float crop_w = rect_w / scale_w;   /* same as resized_w in pixels... */
    const float crop_h = rect_h / scale_h;   /* but we use rect/scale for consistency */

    /* Actually, the Python path works with the view_image which is the
     * resized crop un-scaled back to original crop size. The rotation
     * bounding box is:
     *   width  = crop_h/scale_h, height = crop_w/scale_w  (the un-resized crop)
     *   No — let's follow Python exactly.
     *
     * Python does:
     *   rescaled_xy[:,0] = (lm_x * input_w - half_pad_w) / resize_scale_w
     *   rescaled_xy[:,1] = (lm_y * input_h - half_pad_h) / resize_scale_h
     *   Then rotates the view_image (which has shape = original crop dims)
     *   Then translates by (cx - rotated_half_w, cy - rotated_half_h)
     *
     * The view_image size = original crop before resize.
     */
    const float view_w = rect_w;
    const float view_h = rect_h;
    const float bound_w = view_h * abs_sin + view_w * abs_cos;
    const float bound_h = view_h * abs_cos + view_w * abs_sin;

    /* The rotation matrix used in Python (cv2.getRotationMatrix2D):
     * Rotates around (view_w/2, view_h/2) by -angle degrees, then shifts
     * so the full rotated image fits.
     *
     * For our purposes we can directly compute:
     *   crop_local_x, crop_local_y → in crop coordinates (0..view_w, 0..view_h)
     *   Rotate around (view_w/2, view_h/2) by -angle
     *   Add (bound_w/2 - view_w/2, bound_h/2 - view_h/2) offset
     *   Then translate to image coords by adding (cx - bound_w/2, cy - bound_h/2)
     *
     * Combined: rotate around (view_w/2, view_h/2) then add (cx - view_w/2, cy - view_h/2)?
     * No. Let me simplify:
     *   rel_x = crop_local_x - view_w/2
     *   rel_y = crop_local_y - view_h/2
     *   rotated_x = rel_x * cos(-angle) - rel_y * sin(-angle) = rel_x*cos_a + rel_y*sin_a
     *   rotated_y = rel_x * sin(-angle) + rel_y * cos(-angle) = -rel_x*sin_a + rel_y*cos_a
     *   image_x = rotated_x + bound_w/2 + cx - bound_w/2 = rotated_x + cx
     *   image_y = rotated_y + bound_h/2 + cy - bound_h/2 = rotated_y + cy
     *
     * Wait — Python does:
     *   hand_landmarks[:,0] = keypoints[:,0] + rcx - rotated_half_w
     *   hand_landmarks[:,1] = keypoints[:,1] + rcy - rotated_half_h
     * where keypoints are after rotation_matrix transform, and
     *   rotated_half_w = bound_w/2, rotated_half_h = bound_h/2
     * and rotation_matrix already includes the offset to center in bound.
     *
     * So the full chain is:
     *   coord_in_rotated_image = rotation_matrix @ [crop_x, crop_y, 1]
     *   final_x = coord_in_rotated_image_x + cx - bound_w/2
     *   final_y = coord_in_rotated_image_y + cy - bound_h/2
     *
     * rotation_matrix = cv2.getRotationMatrix2D((view_w/2, view_h/2), -angle_deg, 1)
     * with extra translation to center in (bound_w, bound_h):
     *   M[0,2] += bound_w/2 - view_w/2
     *   M[1,2] += bound_h/2 - view_h/2
     *
     * So: M @ [x, y, 1] =
     *   x' = cos_a*(x - view_w/2) + sin_a*(y - view_h/2) + bound_w/2
     *   y' = -sin_a*(x - view_w/2) + cos_a*(y - view_h/2) + bound_h/2
     *   (Note: cv2 rotation by -angle means cos(-angle)=cos_a, sin(-angle)=-sin_a
     *    but angle in our convention is already the rotation angle, so we negate)
     *
     * final_x = x' + cx - bound_w/2 = cos_a*(x-vw/2) + sin_a*(y-vh/2) + cx
     * final_y = y' + cy - bound_h/2 = -sin_a*(x-vw/2) + cos_a*(y-vh/2) + cy
     *
     * (where cv2 uses angle in degrees, counterclockwise-positive, but we
     *  negate it so effectively: cos_neg = cos(angle), sin_neg = -sin(angle))
     */

    /* Note on angle convention:
     * Python: angle = degrees(rotation), then cv2 rotates by -angle.
     * cv2.getRotationMatrix2D rotates counterclockwise by the given angle.
     * So rotating by -angle_deg means clockwise rotation by angle_deg.
     * cos(-a) = cos(a), sin(-a) = -sin(a)
     */
    const float cos_neg = cos_a;    /* cos(-angle) = cos(angle) */
    const float sin_neg = -sin_a;   /* sin(-angle) = -sin(angle) */

    const float half_vw = view_w * 0.5f;
    const float half_vh = view_h * 0.5f;

    for (int i = 0; i < LANDMARK_NUM_POINTS; ++i) {
        const float lm_x = xyz[i * 3 + 0];  /* normalized [0..1] */
        const float lm_y = xyz[i * 3 + 1];

        /* Remap from 224×224 tensor to crop-local pixel coords */
        const float crop_x = (lm_x * (float)LANDMARK_INPUT_W - (float)meta->half_pad_w) / scale_w;
        const float crop_y = (lm_y * (float)LANDMARK_INPUT_H - (float)meta->half_pad_h) / scale_h;

        /* Rotate and translate to original image coords */
        const float rel_x = crop_x - half_vw;
        const float rel_y = crop_y - half_vh;

        const float img_x = cos_neg * rel_x + sin_neg * rel_y + cx;
        const float img_y = -sin_neg * rel_x + cos_neg * rel_y + cy;

        result->pts[i].x = (int32_t)lrintf(img_x);
        result->pts[i].y = (int32_t)lrintf(img_y);
    }

    return 1;  /* valid hand found */
}
