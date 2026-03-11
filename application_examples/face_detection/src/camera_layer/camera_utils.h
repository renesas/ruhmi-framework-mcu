/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/**********************************************************************************************************************
 * File Name    : camera_utils.h
 * Version      : .
 * Description  : .
 *********************************************************************************************************************/
#ifndef __CAMERA_COMMON_H__
#define __CAMERA_COMMON_H__

#include "common_util.h"

FSP_CPP_HEADER
vision_ai_app_err_t image_rgb565_to_int8 (const void * p_input_image_buff, void * p_output_image_buff,
                                     uint16_t in_width, uint16_t in_height, uint16_t out_width, uint16_t out_height);
vision_ai_app_err_t rotate_16bit_image_90_degrees(uint8_t * p_input_image_buff, uint8_t * p_output_image_buff, int input_width, int input_height);
FSP_CPP_FOOTER

#endif /* End of __CAMERA_UTILS_H__ */
