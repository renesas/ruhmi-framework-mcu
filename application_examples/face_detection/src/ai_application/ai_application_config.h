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
/* AI input image */

#if AI_DEMO == (FACE_DETECTION)
    #define AI_INPUT_IMAGE_WIDTH              (192)
    #define AI_INPUT_IMAGE_HEIGHT             (192)
    #define AI_INPUT_IMAGE_BYTE_PER_PIXEL     (1)
    /* This definition selects how many faces will be presented in the detection result */
    #define AI_MAX_DETECTION_NUM              (20)
#else
    #define AI_INPUT_IMAGE_WIDTH              (224)
    #define AI_INPUT_IMAGE_HEIGHT             (224)
    #define AI_INPUT_IMAGE_BYTE_PER_PIXEL     (3)
    /* This definition selects how many objects will be presented in the detection result */
    #define AI_MAX_DETECTION_NUM              (5)
#endif

#endif /* AI_APPLICATION_CONFIG_H_ */
