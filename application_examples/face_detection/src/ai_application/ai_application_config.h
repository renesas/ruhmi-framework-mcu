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

// ################# AI MODEL INSTALLATION SETTING ##################


#endif /* AI_APPLICATION_CONFIG_H_ */
