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

#include "./ai_application/palm_detection/palm_preprocess.h"

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

void do_detection_screen(bool ai_result_new);

/* Landmark filter tuning currently compiled in — defined in MainLoop_obj.cc,
 * reported by console_output_processing_time() below. */
const char * hand_tuning_tag(void);

/***************************************************************************************************************************
 * Exported global variables and functions (to be accessed by other files)
 ***************************************************************************************************************************/

extern int8_t model_buffer_int8[AI_INPUT_IMAGE_WIDTH * AI_INPUT_IMAGE_HEIGHT * AI_INPUT_IMAGE_BYTE_PER_PIXEL];
extern uint32_t model_buffer_int8_size;

/* Palm preprocess meta — needed later for postprocess coordinate remapping */
palm_preprocess_meta_t g_palm_preprocess_meta;

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

        // Post processing for camera image capture
        camera_capture_post_process();

        time_counter_end = TimeCounter_CurrentCountGet();
        application_processing_time.camera_post_processing_time_ms = TimeCounter_CountValueConvertToMs(time_counter_start, time_counter_end);
#endif
        time_counter_start = TimeCounter_CurrentCountGet();

        /* Fast RGB565 → INT8 RGB letterbox preprocess (nearest-neighbor, integer math)
         * Camera: 640x480, Model: 192x192×3
         * Letterbox: scale = min(192/640, 192/480) = 0.3 → resized 192×144, pad 24 top/bottom
         */
        {
            const uint16_t *src16 = (const uint16_t *)&camera_capture_image_rgb565[0];
            int8_t *dst = (int8_t *)&model_buffer_int8[0];

            const int src_w = CAMERA_CAPTURE_IMAGE_WIDTH;
            const int src_h = CAMERA_CAPTURE_IMAGE_HEIGHT;
            const int dst_w = AI_INPUT_IMAGE_WIDTH;
            const int dst_h = AI_INPUT_IMAGE_HEIGHT;

            const int32_t scale_w = (dst_w << 16) / src_w;
            const int32_t scale_h = (dst_h << 16) / src_h;
            const int32_t scale = (scale_w < scale_h) ? scale_w : scale_h;

            const int resized_w = (int)((((int64_t)src_w * scale) + (1 << 15)) >> 16);
            const int resized_h = (int)((((int64_t)src_h * scale) + (1 << 15)) >> 16);
            const int start_x = (dst_w - resized_w) / 2;
            const int start_y = (dst_h - resized_h) / 2;

            memset(dst, (uint8_t)(-128), (size_t)(dst_w * dst_h * 3));

            const int32_t inv_scale_x = (src_w << 16) / resized_w;
            const int32_t inv_scale_y = (src_h << 16) / resized_h;

            for (int dy = 0; dy < resized_h; dy++)
            {
                const int out_y = start_y + dy;
                const int sy = (int)(((int64_t)dy * inv_scale_y) >> 16);
                const uint16_t *src_row = &src16[sy * src_w];
                int8_t *dst_row = &dst[(out_y * dst_w + start_x) * 3];

                for (int dx = 0; dx < resized_w; dx++)
                {
                    const int sx = (int)(((int64_t)dx * inv_scale_x) >> 16);
                    const uint16_t px = src_row[sx];

                    uint8_t r = (uint8_t)(((px >> 11) & 0x1F) << 3);
                    uint8_t g = (uint8_t)(((px >> 5)  & 0x3F) << 2);
                    uint8_t b = (uint8_t)(( px        & 0x1F) << 3);

                    dst_row[dx * 3 + 0] = (int8_t)(r - 128);
                    dst_row[dx * 3 + 1] = (int8_t)(g - 128);
                    dst_row[dx * 3 + 2] = (int8_t)(b - 128);
                }
            }

            g_palm_preprocess_meta.square_standard_size = (src_h > src_w) ? src_h : src_w;
            g_palm_preprocess_meta.square_padding_half_size = (src_h > src_w) ? (src_h - src_w) / 2 : (src_w - src_h) / 2;
            g_palm_preprocess_meta.resized_w = resized_w;
            g_palm_preprocess_meta.resized_h = resized_h;
            g_palm_preprocess_meta.start_x = start_x;
            g_palm_preprocess_meta.start_y = start_y;
        }

#if (BSP_CFG_DCACHE_ENABLED == 1)
        SCB_CleanDCache_by_Addr((uint8_t *)&model_buffer_int8[0], (int32_t)model_buffer_int8_size);
#endif

        time_counter_end = TimeCounter_CurrentCountGet();
        application_processing_time.ai_inference_pre_processing_time_ms = TimeCounter_CountValueConvertToMs(time_counter_start, time_counter_end);

        // Set AI inference input image ready flag
        xEventGroupSetBits(g_ai_app_event, AI_INFERENCE_INPUT_IMAGE_READY);

        // Make a change for immediate task switch
        vTaskDelay(1);

        // Check if new AI inference result is arrived
        ai_result_updated = ((xEventGroupGetBits(g_ai_app_event) & AI_INFERENCE_RESULT_UPDATED) != 0) ? true : false;
        xEventGroupClearBits(g_ai_app_event, AI_INFERENCE_RESULT_UPDATED);

#if (ENABLE_LCD_DISPLAY_OUTPUT == 1)
        do_detection_screen(ai_result_updated);
#endif

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
    uint8_t detected_palm_count = 0;

    sprintf (sprintf_buffer, "\r\nAI inference result:\r\n");
    print_to_console(sprintf_buffer);

    if(ai_result_new)
    {
        sprintf (sprintf_buffer, "  New data\r\n\r\n");
        print_to_console(sprintf_buffer);
    }
    else
    {
        sprintf (sprintf_buffer, "  Last detected data\r\n\r\n");
        print_to_console(sprintf_buffer);
    }

    for(uint8_t i = 0; i < AI_MAX_DETECTION_NUM; i++)
    {
        if((g_ai_detection[i].m_x != 0) && (g_ai_detection[i].m_y != 0))
        {
            sprintf (sprintf_buffer, "  Palm count %2d: x=%4d, y=%4d, w=%4d, h=%4d\r\n",
                     detected_palm_count, g_ai_detection[i].m_x, g_ai_detection[i].m_y, g_ai_detection[i].m_w, g_ai_detection[i].m_h);
            print_to_console(sprintf_buffer);

            detected_palm_count++;
        }
    }

    if(detected_palm_count == 0)
    {
        sprintf (sprintf_buffer, "  No palm detected. Show your palm at the front of the camera.\r\n");
        print_to_console(sprintf_buffer);
    }
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

    /* Landmark filter tuning currently compiled in, so a captured log says
     * which build produced it. Defined in MainLoop_obj.cc alongside the
     * constants it reports. */
    sprintf (sprintf_buffer, "  Tuning                            : %s\r\n", hand_tuning_tag());
    print_to_console(sprintf_buffer);
}
#endif
