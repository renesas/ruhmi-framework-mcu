/*
 * landmark_display.h
 *
 * Global landmark result storage, shared between AI inference thread
 * and display thread.
 */
#ifndef LANDMARK_DISPLAY_H_
#define LANDMARK_DISPLAY_H_

#include "landmark_postprocess.h"

#ifndef AI_MAX_DETECTION_NUM
#include "ai_application_config.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Global landmark results — one per detection slot.
 * Written by AI inference thread, read by display thread. */
extern landmark_result_t g_landmark_results[AI_MAX_DETECTION_NUM];

/* Store a landmark result for a given detection index */
void update_landmark_result(uint16_t det_index, const landmark_result_t* lm);

#ifdef __cplusplus
}
#endif

#endif /* LANDMARK_DISPLAY_H_ */
