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

#include "application_config.h"

// ###################### AI INFERENCE SETTING ######################
    #define AI_INPUT_IMAGE_WIDTH              (224)
    #define AI_INPUT_IMAGE_HEIGHT             (224)
    #define AI_INPUT_IMAGE_BYTE_PER_PIXEL     (3)
    /* This definition selects how many objects will be presented in the detection result */
    #define AI_MAX_DETECTION_NUM              (5)

    /* Classification result smoothing: raw per-frame Top-N results are noisy enough
     * (camera framing, int8 quantization) that near-tied classes can swap ranking every
     * frame. Categories are tracked by class ID across frames in a small pool and their
     * displayed confidence is an exponential moving average instead of the raw per-frame
     * value, so the displayed Top-N settles down instead of flickering.
     *   - AI_CLASS_POOL_SIZE: number of categories tracked at once. Must stay bigger than
     *     AI_MAX_DETECTION_NUM so a single frame's results can never evict each other.
     *   - AI_CLASS_SMOOTHING_ALPHA: EMA strength when a tracked category is seen again this
     *     frame. Closer to 1.0 = tracks the latest score almost immediately (snappier, more
     *     flicker). Closer to 0.0 = smoother, more lag.
     *   - AI_CLASS_DECAY_ALPHA: multiplier applied to a tracked category's smoothed score for
     *     every frame it does NOT appear in the raw Top-N, so a category that's no longer
     *     being seen fades out instead of lingering forever from one lucky frame.
     *   - AI_CLASS_MIN_PROB: once a decaying category's smoothed score drops below this, its
     *     pool slot is freed for reuse. */
    #define AI_CLASS_POOL_SIZE                (10)
    #define AI_CLASS_SMOOTHING_ALPHA          (0.3f)
    #define AI_CLASS_DECAY_ALPHA              (0.6f)
    #define AI_CLASS_MIN_PROB                 (0.001f)

#endif /* AI_APPLICATION_CONFIG_H_ */
