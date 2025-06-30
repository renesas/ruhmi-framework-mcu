/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/**********************************************************************************************************************
 * File Name    : application_config.h
 * Description  : This file defines the macro of the application configuration.
 **********************************************************************************************************************/
#ifndef APPLICATION_CONFIG_H__
#define APPLICATION_CONFIG_H__

/* Select demo */
#define AI_DEMO                             (IMAGE_CLASSIFICATION)

// ###################### MEMORY ALLOCATION ######################
/* Defines for memory allocation options */
#define ALLOCATE_TO_ONCHIP_ROM              0
#define ALLOCATE_TO_ONCHIP_RAM              1
#define ALLOCATE_TO_SDRAM                   2 // Buffer will be located in ".sdram"
#define ALLOCATE_TO_SDRAM_INITIAL_IN_OSPI   3 // Buffer will be located in ".sdram_ospi_data.data"
#define ALLOCATE_TO_OSPI                    4 // Buffer will be located in ".ospi_device_1.data"

/* Selection of target memory space for application buffer */
#define DISPLAY_BUFFER_ALLICATION           /* Defined in user_common_data.c. Generally, setting the memory allocation on FSP Configurator. */

#define CAMERA_CAPTURE_BUFFER_ALLOCATION    ALLOCATE_TO_ONCHIP_RAM       /* Option: OnchipRAM or SDRAM */
#define CAMERA_TEMPORARY_BUFFER_ALLOCATION  ALLOCATE_TO_ONCHIP_RAM       /* Option: OnchipRAM or SDRAM */
#define CAMERA_IMAGE_ALLOCATION             ALLOCATE_TO_ONCHIP_RAM  /* Option: OnchipRAM or SDRAM */

#define AI_INPUT_IMAGE_ALLOCATION           ALLOCATE_TO_SDRAM  /* Option: OnchipRAM or SDRAM */
#define AI_MODEL_ALLOCATION                 ALLOCATE_TO_SDRAM_INITIAL_IN_OSPI  /* Option: OnchipROM, OnchipRAM, SDRAM(IntialOSPI) or OSPI */

// ################## FUNCTION ENABLEMENT SETTING ################
#define ENABLE_CAMERA_INPUT                          (1) // 0: Disabled, 1: Enabled
#define ENABLE_LCD_DISPLAY_OUTPUT                    (1) // 0: Disabled, 1: Enabled

#define ENABLE_INFERENCE_RUNNING_LED                 (1) // 0: Disabled, 1: Enabled
#define ENABLE_CAMERA_CAPTURE_RUNNING_LED            (0) // 0: Disabled, 1: Enabled

#define ENABLE_CONSOLE_OUTPUT_SCREEN_CLEAR           (1) // 0: Disabled, 1: Enabled. If you'd like to keep a log data, set 0 (disabled).
#define ENABLE_AI_INFERENCE_RESULT_CONSOLE_OUTPUT    (1) // 0: Disabled, 1: Enabled
#define ENABLE_PROCESSING_TIME_RESULT_CONSOLE_OUTPUT (1) // 0: Disabled, 1: Enabled

// ------------------ Internal auto config ------------------
#if ((AI_MODEL_ALLOCATION) == (ALLOCATE_TO_OSPI))
#define REQUIRE_OSPI_OPEN
#elif ((AI_MODEL_ALLOCATION) == (ALLOCATE_TO_SDRAM_INITIAL_IN_OSPI))
#define REQUIRE_OSPI_OPEN
#define REQUIRE_OSPI_MEMORY_COPY_TO_SDRAM
#endif

#endif /* APPLICATION_CONFIG_H__ */
