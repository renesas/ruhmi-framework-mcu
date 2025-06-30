/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/**********************************************************************************************************************
 * File Name    : display_thread_entry.c
 * Version      : .
 * Description  : The display thread operations.
 *********************************************************************************************************************/
/***************************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 ***************************************************************************************************************************/
#include "camera_display_thread.h"
#include <stdio.h>
#include <string.h>

#include "application_config.h"
#include "ai_application_config.h"

#include "camera_layer.h"
#include "camera_utils.h"
#include "display_layer.h"

#include "console_output.h"

#include "common_util.h"

#include "time_counter.h"

/***************************************************************************************************************************
 * Macro definitions
 ***************************************************************************************************************************/
#define DISPLAY_THREAD_YIELD    (20U)

/***************************************************************************************************************************
 * Typedef definitions
 ***************************************************************************************************************************/

/***************************************************************************************************************************
 * Imported global variables and functions (from other files)
 ***************************************************************************************************************************/

void do_face_reconition_screen(bool ai_result_new);
void do_image_classification_screen(bool ai_result_new);
/***************************************************************************************************************************
 * Exported global variables and functions (to be accessed by other files)
 ***************************************************************************************************************************/

extern int8_t model_buffer_int8[AI_INPUT_IMAGE_WIDTH * AI_INPUT_IMAGE_HEIGHT * AI_INPUT_IMAGE_BYTE_PER_PIXEL];
extern uint32_t model_buffer_int8_size;

/***************************************************************************************************************************
 * Private global variables and functions
 ***************************************************************************************************************************/

static volatile uint32_t time_counter_start = 0;
static volatile uint32_t time_counter_end = 0;

FSP_CPP_HEADER
void console_output(bool ai_result_new);
#if (ENABLE_AI_INFERENCE_RESULT_CONSOLE_OUTPUT == 1)
static void console_output_ai_inference_result(bool ai_result_new);
#endif
#if (ENABLE_PROCESSING_TIME_RESULT_CONSOLE_OUTPUT == 1)
static void console_output_processing_time(void);
#endif
FSP_CPP_FOOTER

/*********************************************************************************************************************
 *  display thread entry function
 *               This thread initializes all the hardware and display the camera input to the mipi lcd.
 *  @param[IN]   void *pvParameters: not used
 *  @retval      None
***********************************************************************************************************************/
void camera_display_thread_entry(void *pvParameters)
{
    fsp_err_t fsp_status = FSP_SUCCESS;
    bool ai_result_updated = false;

    FSP_PARAMETER_NOT_USED(pvParameters);

    // Initialize modules for console output
    fsp_status = console_output_init();
    if (FSP_SUCCESS != fsp_status)
    {
        handle_error(VISION_AI_APP_ERR_CONSOLE_OPEN);
    }

    // Initialize external IRQ
    fsp_status = external_irq_configure();
    if (FSP_SUCCESS != fsp_status)
    {
        handle_error(VISION_AI_APP_ERR_EXTERNAL_IRQ_INIT);
    }

    // Output low to enable MIPI I/F on the EK-RA8P1
    R_IOPORT_PinWrite(&g_ioport_ctrl, MIPI_IF_EN, BSP_IO_LEVEL_LOW);

#if (ENABLE_LCD_DISPLAY_OUTPUT == 1)
    // Clear display image buffer
    display_image_buffer_initialize();

    // Initialize the 2D draw engine
    fsp_status = drw_init();
    if(FSP_SUCCESS != fsp_status)
    {
        handle_error(VISION_AI_APP_ERR_GRAPHICS_INIT);
    }

    // Initialize the display peripheral module and connected LCD display
    fsp_status = display_init();
    if(FSP_SUCCESS == fsp_status)
    {
        // Set display initialization complete flag
        xEventGroupSetBits(g_ai_app_event, HARDWARE_DISPLAY_INIT_DONE);
    }
    else
    {
        handle_error(VISION_AI_APP_ERR_GRAPHICS_INIT);
    }
#else
    // Clear display image buffer
    display_image_buffer_initialize();

    // Set display initialization complete flag
    xEventGroupSetBits(g_ai_app_event, HARDWARE_DISPLAY_INIT_DONE);
#endif

#if (ENABLE_CAMERA_INPUT == 1)
    // Clear camera image buffer
    camera_image_buffer_initialize();

    // Initialize the camera capture peripheral module and connected camera
    fsp_status = camera_init(false);
    if(FSP_SUCCESS == fsp_status)
    {
        // Set camera initialization complete flag
        xEventGroupSetBits(g_ai_app_event, HARDWARE_CAMERA_INIT_DONE);
    }
    else
    {
        handle_error(VISION_AI_APP_ERR_CAMERA_INIT);
    }
#else
    // Clear camera image buffer
    camera_image_buffer_initialize();

    // Set camera initialization complete flag
    xEventGroupSetBits(g_ai_app_event, HARDWARE_CAMERA_INIT_DONE);
#endif

    // Initialize timers for measuring each processing time
    TimeCounter_Init();
    TimeCounter_CountReset();

    // Wait for all required hardware and software initialization complete
    xEventGroupWaitBits(g_ai_app_event, (HARDWARE_DISPLAY_INIT_DONE | HARDWARE_CAMERA_INIT_DONE | HARDWARE_ETHOSU_INIT_DONE | SOFTWARE_AI_INFERENCE_INIT_DONE), pdFALSE, pdTRUE, portMAX_DELAY);

#if (ENABLE_CAMERA_INPUT == 1)
    // Start camera capture
    camera_capture_start();
#endif

    while (true)
    {
#if (ENABLE_CAMERA_INPUT == 1)
        // Wait for camera data input
        xEventGroupWaitBits(g_ai_app_event, CAMERA_CAPTURE_COMPLETED, pdTRUE, pdTRUE, portMAX_DELAY);

        time_counter_start = TimeCounter_CurrentCountGet();

        // Post processing for camera image capture. After this process is completed, user app can take an image from camera_capture_image_rgb565[].
        camera_capture_post_process();

        time_counter_end = TimeCounter_CurrentCountGet();
        application_processing_time.camera_post_processing_time_ms = TimeCounter_CountValueConvertToMs(time_counter_start, time_counter_end);
#endif
        time_counter_start = TimeCounter_CurrentCountGet();

        // Create an image for AI inference

        image_rgb565_to_rgb888(&camera_capture_image_rgb565[0], &model_buffer_int8[0],
                             CAMERA_CAPTURE_IMAGE_WIDTH, CAMERA_CAPTURE_IMAGE_HEIGHT, AI_INPUT_IMAGE_WIDTH, AI_INPUT_IMAGE_HEIGHT);

#if (BSP_CFG_DCACHE_ENABLED == 1)
        // Clean cache data because this buffer will be accessed by NPU hardware in subsequent process
        SCB_CleanDCache_by_Addr((uint8_t *)&model_buffer_int8[0], (int32_t)model_buffer_int8_size);
#endif

        time_counter_end = TimeCounter_CurrentCountGet();
        application_processing_time.ai_inference_pre_processing_time_ms = TimeCounter_CountValueConvertToMs(time_counter_start, time_counter_end);

        // Set AI inference input image ready flag. AI inference thread may waiting this flag set.
        xEventGroupSetBits(g_ai_app_event, AI_INFERENCE_INPUT_IMAGE_READY);

        // Make a change for immediate task switch
        vTaskDelay(1);

        // Check if new AI inference result is arrived
        ai_result_updated = ((xEventGroupGetBits(g_ai_app_event) & AI_INFERENCE_RESULT_UPDATED) != 0) ? true : false;
        xEventGroupClearBits(g_ai_app_event, AI_INFERENCE_RESULT_UPDATED);

#if (ENABLE_LCD_DISPLAY_OUTPUT == 1)
        // Display camera image and AI inference result on display screen

        do_image_classification_screen(ai_result_updated);
#endif

        // Output the result to Terminal Software
        console_output(ai_result_updated);

        vTaskDelay(DISPLAY_THREAD_YIELD);
    }
}

/*********************************************************************************************************************
 *  AI inference output function
 *  @param      None
 *  @retval     None
***********************************************************************************************************************/
void console_output(bool ai_result_new)
{
#if (ENABLE_CONSOLE_OUTPUT_SCREEN_CLEAR == 1)
    sprintf (sprintf_buffer, "%s%s", "\x1b[2J", "\x1b[H");
    print_to_console(sprintf_buffer);
#endif

#if (ENABLE_PROCESSING_TIME_RESULT_CONSOLE_OUTPUT == 1)
        console_output_processing_time();
#endif

#if (ENABLE_AI_INFERENCE_RESULT_CONSOLE_OUTPUT == 1)
        console_output_ai_inference_result(ai_result_new);
#endif
}

#if (ENABLE_AI_INFERENCE_RESULT_CONSOLE_OUTPUT == 1)
/*********************************************************************************************************************
 *  Ai inference output function
 *  @param      None
 *  @retval     None
***********************************************************************************************************************/
void console_output_ai_inference_result(bool ai_result_new)
{

}
#endif

#if (ENABLE_PROCESSING_TIME_RESULT_CONSOLE_OUTPUT == 1)
/*********************************************************************************************************************
 *  Processing time output function
 *  @param      None
 *  @retval     None
***********************************************************************************************************************/
void console_output_processing_time(void)
{
    sprintf (sprintf_buffer, "\r\nProcessing time:\r\n");
    print_to_console(sprintf_buffer);

    sprintf (sprintf_buffer, "  Camera image capture vsync period : %4d ms, %4d fps\r\n",
            application_processing_time.camera_image_capture_time_ms, TimeCounter_ConvertFromMsToFps(application_processing_time.camera_image_capture_time_ms));
    print_to_console(sprintf_buffer);
    sprintf (sprintf_buffer, "  Camera post processing time       : %4d ms, %4d fps\r\n",
            application_processing_time.camera_post_processing_time_ms, TimeCounter_ConvertFromMsToFps(application_processing_time.camera_post_processing_time_ms));
    print_to_console(sprintf_buffer);
    sprintf (sprintf_buffer, "  AI inference pre processing time  : %4d ms, %4d fps\r\n",
            application_processing_time.ai_inference_pre_processing_time_ms, TimeCounter_ConvertFromMsToFps(application_processing_time.ai_inference_pre_processing_time_ms));
    print_to_console(sprintf_buffer);
    sprintf (sprintf_buffer, "  AI inference time                 : %4d ms, %4d fps\r\n",
            application_processing_time.ai_inference_time_ms, TimeCounter_ConvertFromMsToFps(application_processing_time.ai_inference_time_ms));
    print_to_console(sprintf_buffer);
    sprintf (sprintf_buffer, "  LCD display vsync period          : %4d ms, %4d fps\r\n",
            application_processing_time.lcd_display_update_refresh_ms, TimeCounter_ConvertFromMsToFps(application_processing_time.lcd_display_update_refresh_ms));
    print_to_console(sprintf_buffer);
}
#endif
