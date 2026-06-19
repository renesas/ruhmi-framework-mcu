/*
 * gesture_classify.h
 *
 * MLP-based gesture recognition from 21 hand landmark points.
 * Uses a MERA-compiled keypoint classifier model (FP32, CPU).
 * Model labels: Open, Close, Pointer  (retrain to add more)
 */
#ifndef GESTURE_CLASSIFY_H_
#define GESTURE_CLASSIFY_H_

#include "landmark_postprocess.h"   /* landmark_point_t, landmark_result_t */

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    GESTURE_OPEN = 0,       /* Open palm               🖐 */
    GESTURE_CLOSE,          /* Closed fist             ✊ */
    GESTURE_POINTER,        /* Pointing / index up     ☝️ */
    GESTURE_COUNT           /* Number of gestures        */
} gesture_t;

#define GESTURE_UNKNOWN  GESTURE_COUNT  /* alias for "none detected" */

/**
 * Classify a gesture from 21 hand landmark points using MLP model.
 * Normalizes landmarks (wrist-relative, max-abs scaled) then runs
 * the MERA-compiled keypoint_classifier via compute_sub_0000_classifier().
 *
 * @param lm   Pointer to a valid landmark result (num_points == 21)
 * @return     Detected gesture enum, or GESTURE_UNKNOWN if confidence < threshold
 */
gesture_t gesture_classify(const landmark_result_t* lm);

/**
 * Get a human-readable string for a gesture.
 *
 * @param g    Gesture enum value
 * @return     Static string like "Open", "Close", "Pointer"
 */
const char* gesture_name(gesture_t g);

#ifdef __cplusplus
}
#endif

#endif /* GESTURE_CLASSIFY_H_ */
