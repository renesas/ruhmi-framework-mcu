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

// ###################### MEMORY ALLOCATION ######################
/* Defines for memory allocation options */
#define ALLOCATE_TO_ONCHIP_ROM                 1 // Buffer will be located in MRAM section
#define ALLOCATE_TO_ONCHIP_RAM                 2 // Buffer will be located in SRAM, initial data is copied from MRAM
#define ALLOCATE_TO_SDRAM                      3 // Buffer will be located in SDRAM section
#define ALLOCATE_TO_SDRAM_INITIAL_IN_OSPI      4 // Buffer will be located in SDRAM, initial data is copied from OSPI section
#define ALLOCATE_TO_OSPI                       5 // Buffer will be located in OSPI
#define ALLOCATE_TO_ONCHIP_RAM_INITIAL_IN_OSPI 6 // Buffer will be located in SRAM, initial data is copied from OSPI section

/* Selection of target memory space for application buffer */
#define CAMERA_CAPTURE_BUFFER_ALLOCATION    /* Defined by r_vin configuration property. */
#define CAMERA_IMAGE_ALLOCATION             ALLOCATE_TO_ONCHIP_RAM  /* Option: OnchipRAM or SDRAM */

#define DISPLAY_BUFFER_ALLICATION           /* Defined by r_glcdc configuration property. */

#define AI_INPUT_IMAGE_ALLOCATION           ALLOCATE_TO_SDRAM  /* Palm model needs 110KB, too large for SRAM */
#define AI_MODEL_ALLOCATION                 ALLOCATE_TO_SDRAM_INITIAL_IN_OSPI  /* Palm model data in OSPI, copied to SDRAM */
#define TENSOR_ARENA_ALLOCATION             ALLOCATE_TO_ONCHIP_RAM  /* Option: OnchipRAM or SDRAM */

// ################## FUNCTION ENABLEMENT SETTING ################
#define ENABLE_CAMERA_INPUT                          (1) // 0: Disabled, 1: Enabled
#define ENABLE_LCD_DISPLAY_OUTPUT                    (1) // 0: Disabled, 1: Enabled

#define ENABLE_INFERENCE_RUNNING_LED                 (1) // 0: Disabled, 1: Enabled
#define ENABLE_CAMERA_CAPTURE_RUNNING_LED            (0) // 0: Disabled, 1: Enabled

#define ENABLE_CONSOLE_OUTPUT_SCREEN_CLEAR           (1) // 0: Disabled, 1: Enabled. If you'd like to keep a log data, set 0 (disabled).
#define ENABLE_AI_INFERENCE_RESULT_CONSOLE_OUTPUT    (1) // 0: Disabled, 1: Enabled
#define ENABLE_PROCESSING_TIME_RESULT_CONSOLE_OUTPUT (1) // 0: Disabled, 1: Enabled

#define ENABLE_OSPI_8BIT_MODE                        (0) // 0: Disabled, 1: Enabled

// ------------------ Internal auto config ------------------
#if ((AI_MODEL_ALLOCATION) == (ALLOCATE_TO_OSPI))
#define REQUIRE_OSPI_OPEN
#elif ((AI_MODEL_ALLOCATION) == (ALLOCATE_TO_SDRAM_INITIAL_IN_OSPI))
#define REQUIRE_OSPI_OPEN
#define REQUIRE_OSPI_MEMORY_COPY_TO_SDRAM
#elif ((AI_MODEL_ALLOCATION) == (ALLOCATE_TO_ONCHIP_RAM_INITIAL_IN_OSPI))
#define REQUIRE_OSPI_OPEN
#endif

#endif /* APPLICATION_CONFIG_H__ */
