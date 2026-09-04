/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/**********************************************************************************************************************
 * File Name    : ai_application_config.h
 * Description  : .
 *********************************************************************************************************************/

#ifndef AI_APPLICATION_CONFIG_H_
#define AI_APPLICATION_CONFIG_H_

// ###################### AI INFERENCE SETTING ######################
/* AI input image */
#define AI_INPUT_IMAGE_WIDTH          (192)
#define AI_INPUT_IMAGE_HEIGHT         (192)
#define AI_INPUT_IMAGE_BYTE_PER_PIXEL (1)

/* This definition selects how many faces will be presented in the detection result */
#define AI_MAX_DETECTION_NUM          (20)

/* Two-speed exponential moving average applied to each detection box (x/y/w/h) across
 * frames, to reduce visible jitter from per-frame inference noise without making the box
 * feel sluggish. Per axis, the raw move (this frame's value minus the currently displayed
 * value) picks which factor is used -- see AI_DETECTION_DEADZONE_PX below for the cutoff:
 *   - AI_DETECTION_SMOOTHING_ALPHA_SLOW: used for small moves (noise / a few overlapping
 *     candidate boxes flickering by a few pixels on an otherwise still face). Keep this low
 *     so that flicker cancels out; the box still creeps towards slow real motion, just gently.
 *   - AI_DETECTION_SMOOTHING_ALPHA_FAST: used once a move is bigger than the dead zone, i.e.
 *     treated as genuine motion. Keep this high so the box actually keeps up with a moving face.
 * Range (0, 1] for both: closer to 1.0 = snappier/more jitter, closer to 0.0 = smoother/more lag.
 * A new detection (no previous box at that slot) is shown at its raw position immediately. */
#define AI_DETECTION_SMOOTHING_ALPHA_SLOW  (0.15f)
#define AI_DETECTION_SMOOTHING_ALPHA_FAST  (0.6f)

/* Per-axis threshold (in AI input pixels, 192x192 space) deciding whether a frame-to-frame
 * move is "noise" (use the slow alpha above) or "real motion" (use the fast alpha above).
 * Increase if the box still flickers on a still face, decrease if real movement feels like
 * it's not being picked up as "fast" soon enough. */
#define AI_DETECTION_DEADZONE_PX       (10)

// ################# AI MODEL INSTALLATION SETTING ##################


#endif /* AI_APPLICATION_CONFIG_H_ */
