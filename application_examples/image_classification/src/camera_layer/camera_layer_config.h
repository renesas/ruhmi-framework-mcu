/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/**********************************************************************************************************************
 * File Name    : camera_layer_config.h
 * Version      : .
 * Description  : .
 *********************************************************************************************************************/
#ifndef __CAMERA_LAYER_CONFIG_H__
#define __CAMERA_LAYER_CONFIG_H__

#include "hal_data.h"
#include "camera_layer.h"

#if defined(BOARD_RA8D1_EK)
#define CAM_PWDN_PIN BSP_IO_PORT_07_PIN_04
#define CAMERA_TYPE (0) // 0: OV3640
#elif defined(BOARD_RA8P1_EK)
#define CAM_PWDN_PIN BSP_IO_PORT_FF_PIN_FF /* Please check user's manual and update as needed */
#define CAMERA_TYPE (1) // 1: OV5640
#else
#define CAM_PWDN_PIN <Define pin of camera power down pin>
#define CAMERA_TYPE <Check you camera type> // 0: OV3640, 1: OV5640
#endif

#define CAMERA_IMAGE_PORTRAIT_ENABLE (0) // 0: Disabled (Landscape image), 1: Enabled (Portrait image)
                                         // Note: Please check and re-configure image capture module configuration as needed

#if (CAMERA_IMAGE_PORTRAIT_ENABLE == 0)
#define CAMERA_ACTIVE_IMAGE_WIDTH    (320) // Raw camera capture image width in pixel
#define CAMERA_ACTIVE_IMAGE_HEIGHT   (240) // Raw camera capture image height in pixel
#define CAMERA_CAPTURE_IMAGE_WIDTH   (CAMERA_ACTIVE_IMAGE_WIDTH)  // Camera capture image width in pixel. The image will be used for subsequent processing.
#define CAMERA_CAPTURE_IMAGE_HEIGHT  (CAMERA_ACTIVE_IMAGE_HEIGHT) // Camera capture image height in pixel. The image will be used for subsequent processing.
#else
#define CAMERA_ACTIVE_IMAGE_WIDTH    (480) // Raw camera capture image width in pixel
#define CAMERA_ACTIVE_IMAGE_HEIGHT   (640) // Raw camera capture image height in pixel
#define CAMERA_CAPTURE_IMAGE_WIDTH   (CAMERA_ACTIVE_IMAGE_HEIGHT) // Camera capture image width in pixel. The image will be used for subsequent processing.
#define CAMERA_CAPTURE_IMAGE_HEIGHT  (CAMERA_ACTIVE_IMAGE_WIDTH)  // Camera capture image height in pixel. The image will be used for subsequent processing.
#endif

#define CAMERA_IMAGE_BYTE_PER_PIXEL  (2) // 2:YUV/RGB565/RGB1555, 4:RGB888/RGB8888

#define CAMERA_CAPTURE_BUFF_NUMBER   (2) // 1: Single buffer, 2: Double buffer

#define CAMERA_CONFIG_WRITE_VERIFY   (0) // 0: Disabled, 1: Enabled
#define DEBUG_CAMERA_I2C_COMM_OUTPUT (0) // 0: Disabled, 1: Enabled

#define CAMERA_CONFIG_BRIGHTNESS     (CONFIG_BRIGHTNESS_ZERO)
#define CAMERA_CONFIG_CONTRAST       (CONFIG_CONTRAST_ZERO)

#if (DEBUG_CAMERA_I2C_COMM_OUTPUT == 1)
#define CAMERA_I2C_DEBUG(fn_, ...)   APP_PRINT((fn_), ##__VA_ARGS__)
#else
#define CAMERA_I2C_DEBUG(...)
#endif

// ------------------ Internal auto config ------------------
#define IMAGE_BUFFER_PADDING (CAMERA_ACTIVE_IMAGE_WIDTH * CAMERA_IMAGE_BYTE_PER_PIXEL * 10)  // 10 lines buffer between image frames for better memory view

#endif /* End of __CAMERA_LAYER_CONFIG_H__ */
