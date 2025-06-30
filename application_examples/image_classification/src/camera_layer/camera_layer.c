/*
 * Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
/**********************************************************************************************************************
 * File Name    : camera_layer.c
 * Version      : .
 * Description  : .
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * IMPORTANT NOTICE : This version of sample project contains preliminary version of MIPI-CSI and VIN module control code.
 *                    The code is under development and can be used for AS-IS use only. Any configuration change may
 *                    cause operation failure, for example timing setting.
 *                    Recommend to check MCU Hardware User's Manual if you need a modification.
 *********************************************************************************************************************/
#include "hal_data.h"
#include "common_data.h"

#include "common_util.h"

#include "camera_layer.h"
#include "camera_utils.h"

#include "application_config.h"

#include "mipicsi_vin_hal_driver.h"
#include "mipicsi_vin_hal_driver_config.h"

#include "time_counter.h"

#define BSP_I2C_SLAVE_ADDR_CAMERA   (0x3C) /* Slave address for OV Camera Module */

#define REG_PRODUCT_ID_H            (0x300a)
#define REG_PRODUCT_ID_L            (0x300b)

#define CORRECT_PRODUCT_ID_H        (0x56) // OV5640
#define CORRECT_PRODUCT_ID_L_REV1A  (0x40)
#define CORRECT_PRODUCT_ID_L_REV2A  (0x41)
#define CORRECT_PRODUCT_ID_L_REV2C  (0x4C)

#define REG_SYS                     (0x3012)
#define REG_SYS_SOFT_RESET_BIT_MASK (0x80)

#define CONFIG_TABLE_END_DETECT     (0xFFFF)
#define REQUEST_SOFTWARE_WAIT       (0xAAAA) // Please ensure if this value is listed in command list of your camera.

// Configuration for brightness and contrast
#if (CAMERA_CONFIG_BRIGHTNESS == CONFIG_BRIGHTNESS_MINUS_3)
#define REG_BRIGHTNESS_ENABLE (0x04)
#define REG_BRIGHTNESS_SIGN   (0x09)
#define REG_BRIGHTNESS_VALUE  (0x30)
#elif (CAMERA_CONFIG_BRIGHTNESS == CONFIG_BRIGHTNESS_MINUS_2)
#define REG_BRIGHTNESS_ENABLE (0x04)
#define REG_BRIGHTNESS_SIGN   (0x09)
#define REG_BRIGHTNESS_VALUE  (0x20)
#elif (CAMERA_CONFIG_BRIGHTNESS == CONFIG_BRIGHTNESS_MINUS_1)
#define REG_BRIGHTNESS_ENABLE (0x04)
#define REG_BRIGHTNESS_SIGN   (0x09)
#define REG_BRIGHTNESS_VALUE  (0x10)
#elif (CAMERA_CONFIG_BRIGHTNESS == CONFIG_BRIGHTNESS_ZERO)
#define REG_BRIGHTNESS_ENABLE (0x04)
#define REG_BRIGHTNESS_SIGN   (0x01)
#define REG_BRIGHTNESS_VALUE  (0x00)
#elif (CAMERA_CONFIG_BRIGHTNESS == CONFIG_BRIGHTNESS_PLUS_1)
#define REG_BRIGHTNESS_ENABLE (0x04)
#define REG_BRIGHTNESS_SIGN   (0x01)
#define REG_BRIGHTNESS_VALUE  (0x10)
#elif (CAMERA_CONFIG_BRIGHTNESS == CONFIG_BRIGHTNESS_PLUS_2)
#define REG_BRIGHTNESS_ENABLE (0x04)
#define REG_BRIGHTNESS_SIGN   (0x01)
#define REG_BRIGHTNESS_VALUE  (0x20)
#elif (CAMERA_CONFIG_BRIGHTNESS == CONFIG_BRIGHTNESS_PLUS_3)
#define REG_BRIGHTNESS_ENABLE (0x04)
#define REG_BRIGHTNESS_SIGN   (0x01)
#define REG_BRIGHTNESS_VALUE  (0x30)
#else
#define REG_BRIGHTNESS_ENABLE (0x00)
#define REG_BRIGHTNESS_SIGN   (0x00)
#define REG_BRIGHTNESS_VALUE  (0x00)
#endif

#if (CAMERA_CONFIG_CONTRAST == CONFIG_CONTRAST_MINUS_3)
#define REG_CONTRAST_ENABLE        (0x40)
#define REG_CONTRAST_SETTING_1     (0x14)
#define REG_CONTRAST_SETTING_2     (0x14)
#elif (CAMERA_CONFIG_CONTRAST == CONFIG_CONTRAST_MINUS_2)
#define REG_CONTRAST_ENABLE        (0x40)
#define REG_CONTRAST_SETTING_1     (0x18)
#define REG_CONTRAST_SETTING_2     (0x18)
#elif (CAMERA_CONFIG_CONTRAST == CONFIG_CONTRAST_MINUS_1)
#define REG_CONTRAST_ENABLE        (0x40)
#define REG_CONTRAST_SETTING_1     (0x1c)
#define REG_CONTRAST_SETTING_2     (0x1c)
#elif (CAMERA_CONFIG_CONTRAST == CONFIG_CONTRAST_ZERO)
#define REG_CONTRAST_ENABLE        (0x40)
#define REG_CONTRAST_SETTING_1     (0x00)
#define REG_CONTRAST_SETTING_2     (0x20)
#elif (CAMERA_CONFIG_CONTRAST == CONFIG_CONTRAST_PLUS_1)
#define REG_CONTRAST_ENABLE        (0x40)
#define REG_CONTRAST_SETTING_1     (0x10)
#define REG_CONTRAST_SETTING_2     (0x24)
#elif (CAMERA_CONFIG_CONTRAST == CONFIG_CONTRAST_PLUS_2)
#define REG_CONTRAST_ENABLE        (0x40)
#define REG_CONTRAST_SETTING_1     (0x18)
#define REG_CONTRAST_SETTING_2     (0x28)
#elif (CAMERA_CONFIG_CONTRAST == CONFIG_CONTRAST_PLUS_3)
#define REG_CONTRAST_ENABLE        (0x40)
#define REG_CONTRAST_SETTING_1     (0x1c)
#define REG_CONTRAST_SETTING_2     (0x2c)
#else
#define REG_CONTRAST_ENABLE        (0x00)
#define REG_CONTRAST_ENABLE        (0x00)
#define REG_CONTRAST_SETTING_1     (0x00)
#define REG_CONTRAST_SETTING_2     (0x00)
#endif

#define REG_VALUE_5580 (REG_BRIGHTNESS_ENABLE)
#define REG_VALUE_5585 (REG_CONTRAST_SETTING_1)
#define REG_VALUE_5586 (REG_CONTRAST_SETTING_2)
#define REG_VALUE_5587 (REG_BRIGHTNESS_VALUE)
#define REG_VALUE_5588 (REG_BRIGHTNESS_SIGN)
#define REG_VALUE_501D (REG_CONTRAST_ENABLE)

// Configuration for image size
// Note: The following address and offset calculation is for system that enables Scaling function
//       (can be configured with 0x5001.Bit5). For Scaling disabled system, please update the code.
#define X_OV5640_PHYSICAL_PIXEL_SIZE (2624)
#define Y_OV5640_PHYSICAL_PIXEL_SIZE (1964)
#if (CAMERA_IMAGE_PORTRAIT_ENABLE == 1)
#define X_ISP_INPUT_SIZE (1440)
#define Y_ISP_INPUT_SIZE (1920)
#else
#define X_ISP_INPUT_SIZE (2560)
#define Y_ISP_INPUT_SIZE (1920)
#endif
#define X_ADDR_START ((X_OV5640_PHYSICAL_PIXEL_SIZE - X_ISP_INPUT_SIZE) / 2)
#define Y_ADDR_START ((Y_OV5640_PHYSICAL_PIXEL_SIZE - Y_ISP_INPUT_SIZE) / 2)
#define X_ADDR_END   (X_ADDR_START + X_ISP_INPUT_SIZE)
#define Y_ADDR_END   (Y_ADDR_START + Y_ISP_INPUT_SIZE)
#define X_OFFSET     0x0010
#define Y_OFFSET     0x0010

static const st_ov_reg_t cam_config_table_normal_mode[] =
{
 { 0x3103, 0x11 }, // SCCB system control
 { 0x3008, 0x82 }, // software reset

 { REQUEST_SOFTWARE_WAIT, 0xFF }, // Request software wait for 255 msec. Should be 500 msec?

 { 0x3008, 0x42 }, // software power down
 { 0x3103, 0x03 }, // SCCB system control

 { REQUEST_SOFTWARE_WAIT, 5 },

 { 0x3017, 0x00 }, // set Frex, Vsync, Href, PCLK, D[9:6] input
 { 0x3018, 0x00 }, // set d[5:0], GPIO[1:0] input
 { 0x3034, 0x10 | MIPI_BIT_MODE }, // MIPI 8-bit mode

 { 0x3037, 0x13 }, // PLL
 { 0x302c, 0xc2 }, // Bit1: FREX-enable, Bit6~7: output drive-1x
 { 0x3108, 0x01 }, // Bit0~1: SCLK root-pll/2, Bit2~3: slk2x root-pll, Bit4~5: PCLK root-pll

 { 0x3630, 0x2e }, { 0x3632, 0xe2 }, { 0x3633, 0x23 }, { 0x3621, 0xe0 }, // Unknown
 { 0x3704, 0xa0 }, { 0x3703, 0x5a }, { 0x3715, 0x78 }, { 0x3717, 0x01 }, // Unknown
 { 0x370b, 0x60 }, { 0x3705, 0x1a }, { 0x3905, 0x02 }, { 0x3906, 0x10 }, // Unknown
 { 0x3901, 0x0a }, { 0x3731, 0x12 }, { 0x3600, 0x08 }, { 0x3601, 0x33 }, // Unknown
 { 0x302d, 0x60 }, { 0x3620, 0x52 }, { 0x371b, 0x20 }, { 0x471c, 0x50 }, // Unknown

 { 0x3a18, 0x00 }, // gain ceiling
 { 0x3a19, 0xf8 }, // gain ceiling

 { 0x3635, 0x1c }, { 0x3634, 0x40 }, { 0x3622, 0x01 }, // Unknown

 // 50Hz/60Hz
 { 0x3c04, 0x28 }, // Threshold low sum
 { 0x3c05, 0x98 }, // Threshold high sum
 { 0x3c06, 0x00 }, // Lightmeter1 threshold H
 { 0x3c07, 0x08 }, // Lightmeter1 threshold L
 { 0x3c08, 0x00 }, // Lightmeter2 threshold H
 { 0x3c09, 0x1c }, // Lightmeter2 threshold L
 { 0x3c0a, 0x9c }, // Sample number H
 { 0x3c0b, 0x40 }, // Sample number L

 // Mirror and Flip
 { 0x3820, 0x41 }, // default: 0x40 | (B1:Sensor vflip, B2: ISP vflip)
 { 0x3821, 0x01 }, // default: 0x00 | (B0:Horizontal binning, B1:Sensor mirror, B2: ISP mirror)

 // Image windowing (ISP input size)
 { 0x3800, ((X_ADDR_START >> 8) & 0xFF) }, // Xstart H
 { 0x3801, (X_ADDR_START & 0xFF) },        // Xstart L
 { 0x3802, ((Y_ADDR_START >> 8) & 0xFF) }, // Ystart H
 { 0x3803, (Y_ADDR_START & 0xFF) },        // Ystart L
 { 0x3804, ((X_ADDR_END >> 8) & 0xFF) },   // Xend H
 { 0x3805, (X_ADDR_END & 0xFF) },          // Xend L
 { 0x3806, ((Y_ADDR_END >> 8) & 0xFF) },   // Yend H
 { 0x3807, (Y_ADDR_END & 0xFF) },          // Yend L
 // Pre-slacing size
 { 0x3810, ((X_OFFSET >> 8) & 0xFF) }, // ISP X offset H
 { 0x3811, (X_OFFSET & 0xFF) },        // ISP X offset L
 { 0x3812, ((Y_OFFSET >> 8) & 0xFF) }, // ISP Y offset H
 { 0x3813, (Y_OFFSET & 0xFF) },        // ISP Y offset L
 // Data output size (after scaling)
 { 0x3808, ((CAMERA_ACTIVE_IMAGE_WIDTH >> 8) & 0xFF) },  // Xout size_high- 0x0280(640)
 { 0x3809, (CAMERA_ACTIVE_IMAGE_WIDTH & 0xFF) },         // Xout size_low
 { 0x380a, ((CAMERA_ACTIVE_IMAGE_HEIGHT >> 8) & 0xFF) }, // Yout size_high- 0x01E0(480)
 { 0x380b, (CAMERA_ACTIVE_IMAGE_HEIGHT & 0xFF) },        // Yout size_low

 // timing
 { 0x3814, 0x31 }, // Horizontal odd/even subsample incr
 { 0x3815, 0x31 }, // Vertical odd/even subsample incr

 // timing
 { 0x3708, 0x64 }, // B50
 { 0x4001, 0x02 }, // BLC start line
 { 0x4005, 0x1a }, // BLC always update
 { 0x3000, 0x00 }, // system reset 0
 { 0x3002, 0x1c }, // system reset 2
 { 0x3004, 0xff }, // clock enable 00
 { 0x3006, 0xc3 }, // clock enable 2

#if (MIPI_NUM_LANES == 2)
 { 0x300e, 0x44 }, // MIPI control, 2 lane, MIPI enable
#elif
#error Untested Configuration
 { 0x300e, 0x24 }, // MIPI control, 1 lane, MIPI enable
#else
#error Invalid lane configuration
#endif

 { 0x302e, 0x08 }, // Unknown

#if (VIN_INPUT_FORMAT == 0) // INPUT_FORMAT_YUV422_8_BIT
 { 0x4300, 0x32 }, // YUV 422, YUYV
#elif (VIN_INPUT_FORMAT == 1) // INPUT_FORMAT_YUV422_10_BIT
#error Untested Configuration
 enum ov5640_format_t format = ov5640_yuv422;
 { 0x4300, 0x32 }, // YUV 422, YUYV
#elif (VIN_INPUT_FORMAT == 2) // INPUT_FORMAT_RAW8
#error Untested Configuration
 { 0x4300, 0xf8 }, // RAW
#elif (VIN_INPUT_FORMAT == 3) // INPUT_FORMAT_RGB888
#error Untested Configuration
 { 0x4300, 0x22 }, // YUV444/RGB888
#endif

 { 0x501f, 0x00 }, // ISP format: ISP YUV 422
 { 0x4407, 0x04 }, // JPEG QS
 { 0x5000, 0xa7 }, // ISP control, Lenc on, gamma on, BPC on, WPC on, CIP on

 { 0x3406, 0x01 }, // Bit0: AWB gain manual enable
 { 0x3400, 0x06 },
 { 0x3401, 0x80 },
 { 0x3402, 0x04 },
 { 0x3403, 0x00 },
 { 0x3404, 0x06 },
 { 0x3405, 0x00 },

 // AWB
 { 0x5180, 0xff }, { 0x5181, 0xf2 }, { 0x5182, 0x00 }, { 0x5183, 0x14 },
 { 0x5184, 0x25 }, { 0x5185, 0x24 }, { 0x5186, 0x16 }, { 0x5187, 0x16 },
 { 0x5188, 0x16 }, { 0x5189, 0x62 }, { 0x518a, 0x62 }, { 0x518b, 0xf0 },
 { 0x518c, 0xb2 }, { 0x518d, 0x50 }, { 0x518e, 0x30 }, { 0x518f, 0x30 },
 { 0x5190, 0x50 }, { 0x5191, 0xf8 }, { 0x5192, 0x04 }, { 0x5193, 0x70 },
 { 0x5194, 0xf0 }, { 0x5195, 0xf0 }, { 0x5196, 0x03 }, { 0x5197, 0x01 },
 { 0x5198, 0x04 }, { 0x5199, 0x12 }, { 0x519a, 0x04 }, { 0x519b, 0x00 },
 { 0x519c, 0x06 }, { 0x519d, 0x82 }, { 0x519e, 0x38 },

 // Color matrix
 { 0x5381, 0x1e }, { 0x5382, 0x5b }, { 0x5383, 0x14 }, { 0x5384, 0x06 },
 { 0x5385, 0x82 }, { 0x5386, 0x88 }, { 0x5387, 0x7c }, { 0x5388, 0x60 },
 { 0x5389, 0x1c }, { 0x538a, 0x01 }, { 0x538b, 0x98 },

 //Sharp&Noise
 { 0x5300, 0x08 }, { 0x5301, 0x30 }, { 0x5302, 0x3f }, { 0x5303, 0x10 },
 { 0x5304, 0x08 }, { 0x5305, 0x30 }, { 0x5306, 0x18 }, { 0x5307, 0x28 },
 { 0x5309, 0x08 }, { 0x530a, 0x30 }, { 0x530b, 0x04 }, { 0x530c, 0x06 },

 // Gamma
 { 0x5480, 0x01 }, { 0x5481, 0x06 }, { 0x5482, 0x12 }, { 0x5483, 0x24 },
 { 0x5484, 0x4a }, { 0x5485, 0x58 }, { 0x5486, 0x65 }, { 0x5487, 0x72 },
 { 0x5488, 0x7d }, { 0x5489, 0x88 }, { 0x548a, 0x92 }, { 0x548b, 0xa3 },
 { 0x548c, 0xb2 }, { 0x548d, 0xc8 }, { 0x548e, 0xdd }, { 0x548f, 0xf0 },
 { 0x5490, 0x15 },

 // UV adjust, brightness, contrast
 { 0x5580, 0x06 | REG_VALUE_5580 },
 { 0x5583, 0x40 },
 { 0x5584, 0x20 },
 { 0x5589, 0x10 },
 { 0x558a, 0x00 },
 { 0x558b, 0xf8 },
 { 0x5585, REG_VALUE_5585 },
 { 0x5586, REG_VALUE_5586 },
 { 0x5587, REG_VALUE_5587 },
 { 0x5588, REG_VALUE_5588 },
 { 0x501d, REG_VALUE_501D },

 // Lens shading
 { 0x5000, 0xa7 }, { 0x5800, 0x20 }, { 0x5801, 0x19 }, { 0x5802, 0x17 },
 { 0x5803, 0x16 }, { 0x5804, 0x18 }, { 0x5805, 0x21 }, { 0x5806, 0x0F },
 { 0x5807, 0x0A }, { 0x5808, 0x07 }, { 0x5809, 0x07 }, { 0x580a, 0x0A },
 { 0x580b, 0x0C }, { 0x580c, 0x0A }, { 0x580d, 0x03 }, { 0x580e, 0x01 },
 { 0x580f, 0x01 }, { 0x5810, 0x03 }, { 0x5811, 0x09 }, { 0x5812, 0x0A },
 { 0x5813, 0x03 }, { 0x5814, 0x01 }, { 0x5815, 0x01 }, { 0x5816, 0x03 },
 { 0x5817, 0x08 }, { 0x5818, 0x10 }, { 0x5819, 0x0A }, { 0x581a, 0x06 },
 { 0x581b, 0x06 }, { 0x581c, 0x08 }, { 0x581d, 0x0E }, { 0x581e, 0x22 },
 { 0x581f, 0x18 }, { 0x5820, 0x13 }, { 0x5821, 0x12 }, { 0x5822, 0x16 },
 { 0x5823, 0x1E }, { 0x5824, 0x64 }, { 0x5825, 0x2A }, { 0x5826, 0x2C },
 { 0x5827, 0x2A }, { 0x5828, 0x46 }, { 0x5829, 0x2A }, { 0x582a, 0x26 },
 { 0x582b, 0x24 }, { 0x582c, 0x26 }, { 0x582d, 0x2A }, { 0x582e, 0x28 },
 { 0x582f, 0x42 }, { 0x5830, 0x40 }, { 0x5831, 0x42 }, { 0x5832, 0x08 },
 { 0x5833, 0x28 }, { 0x5834, 0x26 }, { 0x5835, 0x24 }, { 0x5836, 0x26 },
 { 0x5837, 0x2A }, { 0x5838, 0x44 }, { 0x5839, 0x4A }, { 0x583a, 0x2C },
 { 0x583b, 0x2a }, { 0x583c, 0x46 }, { 0x583d, 0xCE },

 // AVG
 { 0x5688, 0x22 }, { 0x5689, 0x22 }, { 0x568a, 0x42 }, { 0x568b, 0x24 },
 { 0x568c, 0x42 }, { 0x568d, 0x24 }, { 0x568e, 0x22 }, { 0x568f, 0x22 },
 { 0x5025, 0x00 }, // Unknown

 // AEC target
 { 0x3a0f, 0x30 }, // stable in H
 { 0x3a10, 0x28 }, // stable in L
 { 0x3a1b, 0x30 }, // stable out H
 { 0x3a1e, 0x28 }, // stable out L
 { 0x3a11, 0x61 }, // fast zone H
 { 0x3a1f, 0x10 }, // fast zone L

 { 0x4800, 0x24 }, // MIPI Control 00
 { 0x3007, 0XFB }, // Disable DVP PCLK and enable others

 // Timing control
 { 0x380c, 0x07 }, { 0x380d, 0x68 }, { 0x380e, 0x03 }, { 0x380f, 0xd8 },

 // 5060Hz detector
 { 0x3c01, 0xb4 }, { 0x3c00, 0x04 }, { 0x3a08, 0x00 }, { 0x3a09, 0x93 },
 { 0x3a0e, 0x06 }, { 0x3a0a, 0x00 }, { 0x3a0b, 0x7b }, { 0x3a0d, 0x08 },

 // AEC/AGC power down domain control
 { 0x3a00, 0x3c }, { 0x3a02, 0x05 }, { 0x3a03, 0xc4 }, { 0x3a14, 0x05 },
 { 0x3a15, 0xc4 },

 { 0x3618, 0x00 }, { 0x3612, 0x29 }, { 0x3708, 0x64 }, { 0x3709, 0x52 }, // Unknown
 { 0x370c, 0x03 }, // Unknown

 { 0x4004, 0x02 }, // BLC line number
 { 0x4713, 0x03 }, // JPEG mode 3
 { 0x460b, 0x35 }, // debug
 { 0x460c, 0x22 }, // VFIFO, PCLK manual
 { 0x4837, 0x0a }, // MIPI global timing
 { 0x3824, 0x01 }, // add by bright
 { 0x5001, 0xa3 }, // Bit0: AWB enable, Bit1: Color matrix enable, Bit2: UV average enable
                   // Bit5: Scaling enable, Bit7: SDE enable

 { 0x3406, 0x00 }, //awbinit
 { 0x3503, 0x00 }, //awbinit

 // wake up
 { 0x3008, 0x02 },

 { REQUEST_SOFTWARE_WAIT, 5 },

 // Disable ISP and DVP Test Pattern Mode
 { 0x503D, 0x00 },
 { 0x4741, 0x00 },

 /* End of file marker (0xFFFF) */
 {CONFIG_TABLE_END_DETECT, 0x00ff}
};

static const st_ov_reg_t cam_config_table_test_mode[] =
{
 // ISP Test Pattern Mode
 { 0x503D, 0x80 }, // Enable test pattern with standard eight color bar
// { 0x503D, 0x84 }, // Enable test pattern with gradual change at vertical mode 1
// { 0x503D, 0x88 }, // Enable test pattern with gradual change at horizontal
// { 0x503D, 0x8c }, // Enable test pattern with gradual change at vertical mode 2

 /* End of file marker (0xFFFF) */
 {CONFIG_TABLE_END_DETECT, 0x00ff}
};

/*
 * Camera image buffer:
 *  There are three buffers prepared for camera capture
 *  - camera_capture_buffer               : Contains capture data.
 *  - camera_capture_image_rgb565         : Contains the copied capture data. This data/buffer can be used for subsequent process.
 */

// Camera capture image buffer must be 128 byte alignment for MIPI-CSI (VIN) module operation
#if (CAMERA_CAPTURE_BUFF_NUMBER == 2)
#if (CAMERA_CAPTURE_BUFFER_ALLOCATION == ALLOCATE_TO_ONCHIP_RAM)
uint8_t camera_capture_buffer[2][CAMERA_ACTIVE_IMAGE_WIDTH * CAMERA_ACTIVE_IMAGE_HEIGHT * CAMERA_IMAGE_BYTE_PER_PIXEL + IMAGE_BUFFER_PADDING] BSP_ALIGN_VARIABLE(128);
#elif (CAMERA_CAPTURE_BUFFER_ALLOCATION == ALLOCATE_TO_SDRAM)
uint8_t camera_capture_buffer[2][CAMERA_ACTIVE_IMAGE_WIDTH * CAMERA_ACTIVE_IMAGE_HEIGHT * CAMERA_IMAGE_BYTE_PER_PIXEL + IMAGE_BUFFER_PADDING] BSP_PLACE_IN_SECTION(".sdram") BSP_ALIGN_VARIABLE(128);
#else
#error "Add your preferred buffer definition"
#endif
uint32_t camera_capture_buffer_size = sizeof(camera_capture_buffer) / 2;
#else
#if (CAMERA_CAPTURE_BUFFER_ALLOCATION == ALLOCATE_TO_ONCHIP_RAM)
uint8_t camera_capture_buffer[CAMERA_ACTIVE_IMAGE_WIDTH * CAMERA_ACTIVE_IMAGE_HEIGHT * CAMERA_IMAGE_BYTE_PER_PIXEL + IMAGE_BUFFER_PADDING] BSP_ALIGN_VARIABLE(128);
#elif (CAMERA_CAPTURE_BUFFER_ALLOCATION == ALLOCATE_TO_SDRAM)
uint8_t camera_capture_buffer[CAMERA_ACTIVE_IMAGE_WIDTH * CAMERA_ACTIVE_IMAGE_HEIGHT * CAMERA_IMAGE_BYTE_PER_PIXEL + IMAGE_BUFFER_PADDING] BSP_PLACE_IN_SECTION(".sdram") BSP_ALIGN_VARIABLE(128);
#else
#error "Add your preferred buffer definition"
#endif
uint32_t camera_capture_buffer_size = sizeof(camera_capture_buffer);
#endif

#if (CAMERA_IMAGE_ALLOCATION == ALLOCATE_TO_ONCHIP_RAM)
uint8_t camera_capture_image_rgb565[CAMERA_CAPTURE_IMAGE_WIDTH  * CAMERA_CAPTURE_IMAGE_HEIGHT * CAMERA_IMAGE_BYTE_PER_PIXEL] BSP_ALIGN_VARIABLE(8);
#elif (CAMERA_IMAGE_ALLOCATION == ALLOCATE_TO_SDRAM)
uint8_t camera_capture_image_rgb565[CAMERA_CAPTURE_IMAGE_WIDTH  * CAMERA_CAPTURE_IMAGE_HEIGHT * CAMERA_IMAGE_BYTE_PER_PIXEL] BSP_PLACE_IN_SECTION(".sdram") BSP_ALIGN_VARIABLE(8);
#else
#error "Add your preferred buffer definition"
#endif
uint32_t camera_capture_image_rgb565_size = sizeof(camera_capture_image_rgb565);

uint8_t camera_buffer_capture_active_layer = 0;
uint8_t camera_buffer_next_layer = 0;

#if (ENABLE_CAMERA_CAPTURE_RUNNING_LED == 1)
static volatile bool cam_capture_end_led_status = false;
#endif

void (* camera_user_callback)(void * p_args);

FSP_CPP_HEADER
static fsp_err_t bsp_camera_write_array (st_ov_reg_t * array);

static void      ov5640_mipi_virtual_channel_set(uint32_t vchannel);
static fsp_err_t ov5640_configure_clocks(void);
static void      ov5640_stream_on(void);
static void      ov5640_stream_off(void);

void g_cam_mipicsi_vin_user_callback(vin_event_t vin_event, mipicsi_event_status_t mipicsi_event);
FSP_CPP_FOOTER

#if (BSP_CFG_RTOS == 0) // Non RTOS
#define SOFTWARE_DELAY_MS(x)  R_BSP_SoftwareDelay(x, BSP_DELAY_UNITS_MILLISECONDS)
#elif (BSP_CFG_RTOS == 2) // FreeRTOS
#define SOFTWARE_DELAY_MS(x)  vTaskDelay(pdTICKS_TO_MS(x))
#endif

fsp_err_t camera_init (bool use_test_mode)
{
    fsp_err_t fsp_status = FSP_SUCCESS;

    uint8_t reg_val1          = 0;
    uint8_t reg_val2          = 0;

    /* Perform hardware reset */
    R_IOPORT_PinWrite(&g_ioport_ctrl, CAM_RST, BSP_IO_LEVEL_LOW);

    SOFTWARE_DELAY_MS(100);

    /* Release reset pin */
    R_IOPORT_PinWrite(&g_ioport_ctrl, CAM_RST, BSP_IO_LEVEL_HIGH);

    R_GPT_Open(&g_cam_clk_ctrl, &g_cam_clk_cfg);
    R_GPT_Start(&g_cam_clk_ctrl);

    /* Hardware reset module */
    if(BSP_IO_PORT_FF_PIN_FF != CAM_PWDN_PIN)
    {
        R_IOPORT_PinWrite(&g_ioport_ctrl, CAM_PWDN_PIN, (bsp_io_level_t) POWER_DOWN);
        SOFTWARE_DELAY_MS(40);
        R_IOPORT_PinWrite(&g_ioport_ctrl, CAM_PWDN_PIN, (bsp_io_level_t) POWER_UP);
    }

    SOFTWARE_DELAY_MS(10);

    /* Only open if not opened */
    i2c_master_status_t i2c_status;
    R_IIC_MASTER_StatusGet(&g_cam_i2c_master_ctrl, &i2c_status);
    if (i2c_status.open != true) // I2c not open
    {
        fsp_status = R_IIC_MASTER_Open(&g_cam_i2c_master_ctrl, &g_cam_i2c_master_cfg);
        if(fsp_status != FSP_SUCCESS)
        {
            return FSP_ERR_INTERNAL;
        }
    }

    // Set I2C slave address
    R_IIC_MASTER_SlaveAddressSet(&g_cam_i2c_master_ctrl, BSP_I2C_SLAVE_ADDR_CAMERA, I2C_MASTER_ADDR_MODE_7BIT);

    // Hardware connection check with product ID check
    rdSensorReg16_8(REG_PRODUCT_ID_H, &reg_val1); // PIDH  PID MSB
    rdSensorReg16_8(REG_PRODUCT_ID_L, &reg_val2); // PIDH  PID LSB REV2c - 0x4C, REV2a = 0x41, REV1a=0x40 otherwise error

    if (!((reg_val2 == CORRECT_PRODUCT_ID_L_REV1A) || (reg_val2 == CORRECT_PRODUCT_ID_L_REV2A) || (reg_val2 == CORRECT_PRODUCT_ID_L_REV2C)))
    {
        return FSP_ERR_HW_LOCKED;
    }

    // Setup the Camera
    fsp_status = bsp_camera_write_array((st_ov_reg_t *) &cam_config_table_normal_mode);

    // JDG - Clock related settings
    if(FSP_SUCCESS == fsp_status)
    {
        fsp_status = ov5640_configure_clocks();
    }

    if(FSP_SUCCESS == fsp_status)
    {
        ov5640_mipi_virtual_channel_set(MIPI_VIRTUAL_CHANNEL);
    }

    // Enabling ISP Test Pattern Mode
    if(FSP_SUCCESS == fsp_status)
    {
        if(use_test_mode)
        {
            /* TEST PATTERN */
            fsp_status = bsp_camera_write_array((st_ov_reg_t *) &cam_config_table_test_mode);
        }
    }

    if(FSP_SUCCESS == fsp_status)
    {
        ov5640_stream_off();

        SOFTWARE_DELAY_MS(5);

        mipicsi_vin_callback_set(g_cam_mipicsi_vin_user_callback);
        fsp_status = mipicsi_vin_module_configure();
    }

    if(FSP_SUCCESS == fsp_status)
    {
        SOFTWARE_DELAY_MS(5);

        ov5640_stream_on();
    }

    return fsp_status;
}

static fsp_err_t bsp_camera_write_array (st_ov_reg_t * array)
{
    fsp_err_t fsp_status = FSP_SUCCESS;
#if CAMERA_CONFIG_WRITE_VERIFY
    uint8_t read_value;
#endif

    while (CONFIG_TABLE_END_DETECT != array->reg_num)
    {
        if(array->reg_num != REQUEST_SOFTWARE_WAIT)
        {
            wrSensorReg16_8(array->reg_num, array->value);

#if CAMERA_CONFIG_WRITE_VERIFY
            rdSensorReg16_8(array->reg_num, &read_value);

            if (read_value == array->value)
            {
                CAMERA_I2C_DEBUG ("Write ADDR:[0x%04x] Data:[[GREEN]0x%02x[WHITE]]\r\n",array->reg_num,array->value);
            }
            else
            {
                CAMERA_I2C_DEBUG ("Write ADDR:[0x%04x] Data:[[RED]0x%02x[WHITE]]\r\n",array->reg_num,array->value);
                fsp_status = FSP_ERR_INVALID_DATA;
                break;
            }
#endif
        }
        else
        {
            SOFTWARE_DELAY_MS(array->value);
        }

        array++;
    }

    return fsp_status;
}

static fsp_err_t ov5640_configure_clocks()
{
    /* 0x3035 SC PLL CONTRL1 0x11 RW (Default: 0x11)
     * <TBD> 0 is div 16 according to linux driver */
    uint8_t sys_clock_div = 1;  // Bit[7:4]: System clock divider
    uint8_t mipi_clock_div = 2; // Bit[3:0]: Scale divider for MIPI
    uint8_t reg_3035_value = (uint8_t)(sys_clock_div << 4 | mipi_clock_div << 0);

    wrSensorReg16_8(0x3035, reg_3035_value); // Sys Clock Div: 1 --- MIPI Clock Div: 2

    /* 0x3036 SC PLL CONTRL2 0x69 RW  (Default: 0x38)*/
    uint8_t pll_multiplier = 140; // Bit[7:0]: PLL multiplier (4~252, even integer from 128+)
    uint8_t reg_3036_value = (uint8_t)(pll_multiplier);

    wrSensorReg16_8(0x3036, reg_3036_value);  // PLL Multiplier: 140

    /* 0x3037 SC PLL CONTRL3 0x03 RW (Default: 0x13)*/
    uint8_t pll_root_div = 2; // Bit[4]: PLL root divider --- 0: Bypass, 1: Divided by 2
    uint8_t pll_pre_div = 3;  // Bit[3:0]: PLL pre-divider: 1,2,3,4,6,8
    uint8_t reg_3037_value = (uint8_t)((pll_root_div==2) << 4 | (pll_pre_div) << 0);

    wrSensorReg16_8(0x3037, reg_3037_value); // PLL 2x-root-div: Enabled --- PLL Pre-div: 3

    if(!((pll_pre_div == 1) || (pll_pre_div == 2) || (pll_pre_div == 3) || \
         (pll_pre_div == 4) || (pll_pre_div == 6) || (pll_pre_div == 8)))
    { return FSP_ERR_ASSERTION; }

    /* 0x3108 SYSTEM ROOT DIVIDER 0x16 RW - Pad Clock Divider for SCCB Clock (Default: 0x01)*/
    uint8_t pclk_root_div   = 1; // Bit[5:4]: PCLK root divider (00: 1, 01: 2, 10: 4, 11: 8)
    uint8_t sclk2x_root_div = 1; // Bit[3:2]: sclk2x root divider (00: 1, 01: 2, 10: 4, 11: 8)
    uint8_t sclk_root_div   = 2; // Bit[1:0]: SCLK root divider (00: 1, 01: 2, 10: 4, 11: 8)
    uint8_t reg_3108_div_lut[] = {0xF, 0, 1, 0xF, 2, 0xF, 0xF, 0xF, 3}; // 1, 2, 4, 8 are valid
    uint8_t reg_3108_value = (uint8_t)(reg_3108_div_lut[pclk_root_div] << 4 | \
            reg_3108_div_lut[sclk2x_root_div] << 2 | \
            reg_3108_div_lut[sclk_root_div] << 0);

    wrSensorReg16_8(0x3108, reg_3108_value); // system divider

    if(!(reg_3108_div_lut[pclk_root_div] < 0xF)){ return FSP_ERR_ASSERTION; }
    if(!(reg_3108_div_lut[sclk2x_root_div] < 0xF)){ return FSP_ERR_ASSERTION; }
    if(!(reg_3108_div_lut[sclk_root_div] < 0xF)){ return FSP_ERR_ASSERTION; }

    uint32_t base_pll_hz = (((uint32_t)MIPI_XCLK_HZ / (pll_root_div * pll_pre_div)) * pll_multiplier);
    if(!(800000000 >= base_pll_hz)){ return FSP_ERR_ASSERTION; }

    uint32_t sys_clk_hz = base_pll_hz/ (uint32_t)(sys_clock_div  * sclk2x_root_div * sclk_root_div); (void)sys_clk_hz;
    uint32_t mipi_clk_hz = base_pll_hz / (uint32_t)(mipi_clock_div * pclk_root_div);
    if(!(sys_clk_hz >= mipi_clk_hz)){ return FSP_ERR_ASSERTION; }

    return FSP_SUCCESS;
}

/**
 * @brief  Set MIPI VirtualChannel
 * @param  pObj  pointer to component object
 * @param  vchannel virtual channel for Mipi Mode
 * @retval Component status
 */
void ov5640_mipi_virtual_channel_set(uint32_t vchannel)
{
    uint8_t tmp;
    rdSensorReg16_8(0x4814, &tmp);

    tmp = tmp & (uint8_t)~(3 << 6);
    tmp = tmp | (uint8_t)(vchannel << 6);
    wrSensorReg16_8(0x4814, tmp);
}

void ov5640_stream_on(void)
{
    wrSensorReg16_8(0x4202, 0x00);
}

void ov5640_stream_off(void)
{
    wrSensorReg16_8(0x4202, 0x0f);
}

void camera_user_callback_set(void (* p_callback)(void * p_args))
{
    camera_user_callback = p_callback;
}

void camera_image_buffer_initialize(void)
{
    memset(camera_capture_buffer, 0x0, sizeof(camera_capture_buffer));
    memset(camera_capture_image_rgb565, 0x0, sizeof(camera_capture_image_rgb565));
}

void camera_capture_start(void)
{
    camera_buffer_capture_active_layer = camera_buffer_next_layer;

#if (CAMERA_CAPTURE_BUFF_NUMBER == 2)
    mipicsi_vin_capture_start(&camera_capture_buffer[camera_buffer_capture_active_layer][0]);
#else
    mipicsi_vin_capture_start(&camera_capture_buffer[0]);
#endif
}

void camera_data_buffer_switch(void)
{
    camera_buffer_next_layer = (camera_buffer_capture_active_layer == 0) ? 1 : 0;
}

uint32_t camera_data_ready_buffer_pointer_get(void)
{
    uint8_t read_buffer = (camera_buffer_capture_active_layer == 0) ? 1 : 0;

#if (CAMERA_CAPTURE_BUFF_NUMBER == 2)
    return (uint32_t)&camera_capture_buffer[read_buffer][0];
#else
    FSP_PARAMETER_NOT_USED(buff_switch);
    return (uint32_t)&camera_capture_buffer[0];
#endif
}

void camera_capture_post_process(void)
{
    // Switch camera buffer
    camera_data_buffer_switch();

#if (BSP_CFG_DCACHE_ENABLED == 1)
    // Invalidate cache data for camera capture image buffer since its content may be updated by capture hardware
    SCB_InvalidateDCache_by_Addr((uint8_t *)camera_data_ready_buffer_pointer_get(), (int32_t)(camera_capture_buffer_size));
#endif

    // Copy the image data to the buffer that will be accessed in subsequent process
    memcpy(&camera_capture_image_rgb565[0], (void *)camera_data_ready_buffer_pointer_get(), camera_capture_image_rgb565_size);
}

static uint32_t last_vin_frame_end = 0;

void g_cam_mipicsi_vin_user_callback(vin_event_t vin_event, mipicsi_event_status_t mipicsi_event)
{
    BaseType_t xHigherPriorityTaskWoken, xResult;
    xHigherPriorityTaskWoken = pdFALSE;

    if(vin_event & VIN_EVENT_VFS)
    {
        application_processing_time.camera_image_capture_time_ms = TimeCounter_CountValueConvertToMs(last_vin_frame_end, TimeCounter_CurrentCountGet());
        last_vin_frame_end = TimeCounter_CurrentCountGet();

        /* Set camera data ready flag */
        xResult = xEventGroupSetBitsFromISR(g_ai_app_event, CAMERA_CAPTURE_COMPLETED, &xHigherPriorityTaskWoken);
        if( xResult != pdFAIL )
        {
          /* If xHigherPriorityTaskWoken is now set to pdTRUE then a context
          switch should be requested.  The macro used is port specific and will
          be either portYIELD_FROM_ISR() or portEND_SWITCHING_ISR() - refer to
          the documentation page for the port being used. */
          portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
        }

        camera_capture_start();

#if (ENABLE_CAMERA_CAPTURE_RUNNING_LED == 1)
        cam_capture_end_led_status = !cam_capture_end_led_status;
        if(cam_capture_end_led_status)
        {
            CAMERA_CAPTURE_END_INDICATE_LED_ON;
        }
        else
        {
            CAMERA_CAPTURE_END_INDICATE_LED_OFF;
        }
#endif
    }

    FSP_PARAMETER_NOT_USED(vin_event);
    FSP_PARAMETER_NOT_USED(mipicsi_event);
}
