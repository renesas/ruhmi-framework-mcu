/*
 * gesture_classify.c
 *
 * MLP-based gesture recognition from 21 hand landmark points.
 * Uses the MERA-compiled keypoint_classifier model (FP32, CPU).
 *
 * Preprocessing (matches the original Python pipeline):
 *   1. Subtract wrist (point 0) from all 21 keypoints  -> relative coords
 *   2. Flatten to 42 floats  [x0,y0, x1,y1, ... x20,y20]
 *   3. Divide by max |value| -> all values in [-1, +1]
 *
 * Model:  Dense(42->20,ReLU) -> Dense(20->10,ReLU) -> Dense(10->3) -> Softmax
 * Output: 3 classes  [Open, Close, Pointer]
 *
 * Arena: 128 bytes (trivial)
 */

#include <stddef.h>
#include <math.h>

#include "gesture_classify.h"
#include "../ruhmi_classifier_results/compute_sub_0000_classifier.h"

/* 128-byte arena for the MLP - tiny, lives as static */
static uint8_t classifier_arena[kBufferSize_sub_0000_classifier];

/* Minimum softmax confidence to accept a gesture */
#define GESTURE_CONFIDENCE_THRESHOLD  0.6f

/* ------------------------------------------------------------------ */
/* Gesture classification                                             */
/* ------------------------------------------------------------------ */

gesture_t gesture_classify(const landmark_result_t* lm)
{
    if (lm == NULL || lm->num_points < 21) {
        return GESTURE_UNKNOWN;
    }

    /* Step 1: subtract wrist and flatten to 42 floats */
    float input[42];
    float base_x = lm->pts[0].x;
    float base_y = lm->pts[0].y;

    for (int i = 0; i < 21; i++) {
        input[i * 2 + 0] = lm->pts[i].x - base_x;
        input[i * 2 + 1] = lm->pts[i].y - base_y;
    }

    /* Step 2: normalize by max absolute value */
    float max_val = 0.0f;
    for (int i = 0; i < 42; i++) {
        float a = fabsf(input[i]);
        if (a > max_val) max_val = a;
    }
    if (max_val > 1e-6f) {
        float inv = 1.0f / max_val;
        for (int i = 0; i < 42; i++) {
            input[i] *= inv;
        }
    }

    /* Step 3: run MERA-compiled MLP */
    float output[3];
    compute_sub_0000_classifier(classifier_arena, input, output);

    /* Step 4: argmax with confidence threshold */
    int best = 0;
    for (int i = 1; i < 3; i++) {
        if (output[i] > output[best]) best = i;
    }

    if (output[best] < GESTURE_CONFIDENCE_THRESHOLD) {
        return GESTURE_UNKNOWN;
    }

    return (gesture_t)best;
}

/* ------------------------------------------------------------------ */
/* Gesture name strings                                               */
/* ------------------------------------------------------------------ */

static const char* gesture_names[] = {
    "Open",         /* GESTURE_OPEN    = 0 */
    "Close",        /* GESTURE_CLOSE   = 1 */
    "Pointer",      /* GESTURE_POINTER = 2 */
};

const char* gesture_name(gesture_t g)
{
    if (g >= GESTURE_COUNT) return "";
    return gesture_names[g];
}
