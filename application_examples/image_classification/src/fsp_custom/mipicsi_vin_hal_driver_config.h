/*
 * Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
/**********************************************************************************************************************
 * File Name    : mipicsi_vin_hal_drvier_config.h
 * Version      : .
 * Description  : .
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * IMPORTANT NOTICE : This version of sample project contains preliminary version of MIPI-CSI and VIN module control code.
 *                    The code is under development and can be used only for AS-IS use.
 *                    Any configuration change (for example, clock / timing setting) may cause operation failure.
 *                    Recommend to check MCU Hardware User's Manual if you need a modification.
 *                    Also the HAL driver API and its usage note are subject to change.
 *********************************************************************************************************************/
#ifndef MIPICSI_VIN_HAL_DRIVER_CONFIG_H__
#define MIPICSI_VIN_HAL_DRIVER_CONFIG_H__

#define MIPICSI_DBG_IRQ_PRIORITY (12)
#define MIPICSI_RX_IRQ_PRIORITY  (12)
#define MIPICSI_DL_IRQ_PRIORITY  (12)
#define MIPICSI_VC_IRQ_PRIORITY  (12)
#define MIPICSI_PM_IRQ_PRIORITY  (12)
#define MIPICSI_GST_IRQ_PRIORITY (12)
#define MIPICSI_DBG_IRQ_PRIORITY (12)
#define VIN_IRQ_PRIORITY         (12)
#define VIN_ERR_PRIORITY         (12)

/*
 * VIN_INPUT_FORMAT
 *  0 : YUV422_8_BIT
 *  1 : YUV422_10_BIT // Not tested
 *  2 : RAW8          // Not tested
 *  3 : RGB888        // Not tested
 */
#define VIN_INPUT_FORMAT         (0)

/*
 * VIN_OUTPUT_FORMAT
 *  0 : YUV
 *  1 : RGB565
 *  2 : RGB888
 *  3 : RGB1555
 *  4 : RGB8888
 */
#define VIN_OUTPUT_FORMAT        (1)

#define MIPI_NUM_LANES           (2) // Only two data line case is supported in this sample project
#define MIPI_VIRTUAL_CHANNEL     (0) // Only channel 0 is supported in this sample project
#define MIPI_BIT_MODE            (8) // 8: 8-bit, 10: 10-bit
                                     // Only MIPI 8-bit mode is supported in this sample project

#define MIPI_XCLK_HZ                  (24000000) // 24 MHz
#define OV5640_HSCLK_MHZ              (280)      // 280 Mbps

#endif /* MIPICSI_VIN_HAL_DRIVER_CONFIG_H__ */
