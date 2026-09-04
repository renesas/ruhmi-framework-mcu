/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/**********************************************************************************************************************
 * File Name    : detection_screen_mipi.c
 * Version      : .
 * Description  : The palm detection screen display on mipi lcd.
 *********************************************************************************************************************/
/***************************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 ***************************************************************************************************************************/

#include "hal_data.h"
#include <stdio.h>

#include "common_util.h"

#include "camera_layer.h"
#include "display_layer.h"
#include "bg_font_18_full.h"

#include "time_counter.h"

#include "display_layer_config.h"

#include "application_config.h"
#include "ai_application_config.h"

/***************************************************************************************************************************
 * Macro definitions
 * Refer to the application note for the physical definition of these values
 ***************************************************************************************************************************/

/***************************************************************************************************************************
 * Typedef definitions
 ***************************************************************************************************************************/

/***************************************************************************************************************************
 * Imported global variables and functions (from other files)
 ***************************************************************************************************************************/

/***************************************************************************************************************************
 * Exported global variables and functions (to be accessed by other files)
 ***************************************************************************************************************************/

void  do_detection_screen(bool ai_result_new);
uint8_t detection_count = 0;

uint8_t exe_count_print_static_text = 0;

/***************************************************************************************************************************
 * Private global variables and functions
 ***************************************************************************************************************************/
static d2_point top_left_x[AI_MAX_DETECTION_NUM];
static d2_point top_left_y[AI_MAX_DETECTION_NUM];
static d2_point bottom_right_x[AI_MAX_DETECTION_NUM];
static d2_point bottom_right_y[AI_MAX_DETECTION_NUM];

/* Surface DRW display-list exhaustion, which is otherwise completely silent.
 *
 * DAVE2D builds its display list in blocks of 51 entries taken from the
 * FreeRTOS heap. When a block allocation fails, dave_dlist.c records
 * D2_NOMEMORY and then simply does not chain the next block, discarding the
 * rest of the frame -- and nothing in this project checks any d2_* return
 * value, so the only evidence is content quietly missing from the screen.
 *
 * That ceiling matters more here than the small amount of drawing suggests:
 * AI_MAX_DETECTION_NUM is 8, so a busy frame is 32 box lines, and the sidebar
 * text is expensive in its own right -- print_bg_font_18() costs a
 * d2_setblitsrc plus a d2_blitcopy for every single character. The sidebar is
 * also drawn last, which makes it the first thing dropped.
 *
 * Reported by console_output_processing_time(); non-zero means a frame was
 * truncated and the FreeRTOS heap needs raising. Switched by
 * ENABLE_DRW_ERROR_CONSOLE_OUTPUT in application_config.h, which is where the
 * console side can see it too.
 *
 * The variable itself is defined unconditionally on purpose: guarding it as
 * well would turn switching the feature off into an undefined-reference link
 * error from the extern in camera_display_thread_entry.c, and four bytes is
 * not worth that trap. */
int32_t g_drw_last_error = 0;

static void print_static_text (void);
static void draw_bounding_box(uint8_t i);
static void calculate_and_draw_bounding_box(uint8_t i);
static void display_camera_image(void);

/*********************************************************************************************************************
 *  display_camera_image function
 *               This function selects the rotated camera image buffer in QVGA mode 240x320 format and
 *               displays in VGA 480x640 format at the center of the mipi lcd.
 *  @param      None
 *  @retval     None.
***********************************************************************************************************************/
static void display_camera_image(void)
{
#if (BSP_CFG_DCACHE_ENABLED == 1)
    // Clean cache data for camera capture image buffer because this buffer will be accessed by DRW hardware
    SCB_CleanDCache_by_Addr(&camera_capture_image_rgb565[0], (int32_t)(camera_capture_image_rgb565_size));
#endif

    /* Specify camera input. */
    /* Note: The MIPI-DSI display panel of EK-RA8D1 prefers 90-degrees counter-clock-wised rotated image. Therefore input raw data of camera capture image. */
    d2_setblitsrc(d2_handle, (void *)&camera_capture_image_rgb565[0], CAMERA_CAPTURE_IMAGE_WIDTH, CAMERA_CAPTURE_IMAGE_WIDTH, CAMERA_CAPTURE_IMAGE_HEIGHT, d2_mode_rgb565);

    /* display as VGA 640x480 on mipi lcd */
    d2_blitcopy(d2_handle,
                (d2_s32) CAMERA_CAPTURE_IMAGE_WIDTH, (d2_s32) CAMERA_CAPTURE_IMAGE_HEIGHT, // Source width/height
                (d2_blitpos) 0, (d2_blitpos) 0,                                          // Source position
                (d2_width) ((uint32_t)(CAMERA_CAPTURE_IMAGE_WIDTH * CAMERA_IMAGE_SCALING) << 4), (d2_width) ((uint32_t)(CAMERA_CAPTURE_IMAGE_HEIGHT * CAMERA_IMAGE_SCALING) << 4),   // Destination size width/height
                (d2_point) (0 << 4), (d2_point) (0 << 4), // Destination offset position
                d2_tm_filter);
}

/*********************************************************************************************************************
 *  draw_bounding_box function
 *               This function picks the index of the detection result which has a bounding box and
 *               uses DRW to render a red bounding box on the mipi lcd.
 *  @param[IN]   i: index of the detection result
 *  @retval     None
***********************************************************************************************************************/
static void draw_bounding_box(uint8_t i)
{
    d2_setcolor(d2_handle, 0, AI_INFERENCE_RESULT_BOUNDING_BOX_COLOR);

    d2_renderline(d2_handle, (d2_point) ((top_left_x[i]) << 4), (d2_point) ((top_left_y[i])<< 4), (d2_point) ((bottom_right_x[i]) << 4), (d2_point) ((top_left_y[i]) << 4), (d2_point) (2 << 4), 0);
    d2_renderline(d2_handle, (d2_point) ((bottom_right_x[i]) << 4), (d2_point) ((top_left_y[i]) << 4), (d2_point) ((bottom_right_x[i]) << 4), (d2_point) ((bottom_right_y[i]) << 4), (d2_point) (2 << 4), 0);
    d2_renderline(d2_handle, (d2_point) ((bottom_right_x[i]) << 4), (d2_point) ((bottom_right_y[i]) << 4), (d2_point) ((top_left_x[i]) << 4), (d2_point) ((bottom_right_y[i]) << 4), (d2_point) (2 << 4), 0);
    d2_renderline(d2_handle, (d2_point) ((top_left_x[i]) << 4), (d2_point) ((bottom_right_y[i]) << 4), (d2_point) ((top_left_x[i]) << 4), (d2_point) ((top_left_y[i]) << 4), (d2_point) (2 << 4), 0);
}

/*********************************************************************************************************************
 *  calculate_and_draw_bounding_box function
 *  This function takes the ai inference boundary box center of the image and scales it to the 480x640
 *  mipi lcd center area as a bounding box.
 *  @param[IN]   i: index of the detection result
 *  @retval     None
***********************************************************************************************************************/
static void calculate_and_draw_bounding_box(uint8_t i)
{
    detection_count++;

    /* m_x/y/w/h are in camera pixel coords (640x480), so this is a plain scale
     * to display coords.
     *
     * It used to multiply by CAMERA_CAPTURE_IMAGE_HEIGHT / AI_INPUT_IMAGE_HEIGHT
     * and add (640-480)/2, which assumed the model had been fed a 480x480
     * centre crop of the camera frame. The preprocessing in
     * camera_display_thread_entry.c does not do that -- it letterboxes the full
     * 640x480 into 192x192, leaving 24 blank rows top and bottom -- so the box
     * came out about 25% too small and offset from the hand. The conversion now
     * happens in MainLoop_obj.cc where the letterbox parameters are known,
     * which is also how the landmark projects do it. */
    top_left_x[i]     = (d2_point)((float)g_ai_detection[i].m_x * CAMERA_IMAGE_SCALING);
    top_left_y[i]     = (d2_point)((float)g_ai_detection[i].m_y * CAMERA_IMAGE_SCALING);
    bottom_right_x[i] = (d2_point)((float)(g_ai_detection[i].m_x + g_ai_detection[i].m_w) * CAMERA_IMAGE_SCALING);
    bottom_right_y[i] = (d2_point)((float)(g_ai_detection[i].m_y + g_ai_detection[i].m_h) * CAMERA_IMAGE_SCALING);

    draw_bounding_box(i);
}

/*********************************************************************************************************************
 *  print_static_text function
 *  This function prints the static text which does not change based on inference result.
 *  @param      None
 *  @retval     None
***********************************************************************************************************************/
static void print_static_text(void)
{
    /* show model information */
    print_bg_font_18(d2_handle, 820,  50, DISPLAY_FONT_SCALING, (char*)"Model:");
    print_bg_font_18(d2_handle, 820,  90, DISPLAY_FONT_SCALING, (char*)"Palm");
    print_bg_font_18(d2_handle, 820, 120, DISPLAY_FONT_SCALING, (char*)"Detection");

    /*show inference time in ms*/
    print_bg_font_18(d2_handle, 820, 200, DISPLAY_FONT_SCALING, (char*)"Inference");
    print_bg_font_18(d2_handle, 820, 230, DISPLAY_FONT_SCALING, (char*)"time:");

    /*print the number of palms detected */
    print_bg_font_18(d2_handle, 820, 350, DISPLAY_FONT_SCALING, (char*)"No of ");
    print_bg_font_18(d2_handle, 820, 380, DISPLAY_FONT_SCALING, (char*)"Hands:");
}

/*********************************************************************************************************************
 *  print_inf_time_and_detections function
 *  This function prints the time used in the previously finished inference and the number of palms detected.
 *  @param      None
 *  @retval     None
***********************************************************************************************************************/
static void print_inf_time_and_detections(void)
{
       /* The inference_time is acquired in MainLoop_obj.cc.
     * This time does not include the pre and post processing routine.
     * It is the time used for inference only.
     */

    uint32_t time = (uint32_t)(application_processing_time.ai_inference_time_ms); // ms

    // Clear last draw
    print_bg_font_18(d2_handle, 820, 280, DISPLAY_FONT_SCALING,  "             ");
    print_bg_font_18(d2_handle, 820, 430, DISPLAY_FONT_SCALING,  "       ");

    // update string on display
    char time_str[8] = {'0', '0', '0', '0', ' ', 'm', 's', '\0'};
    time_str[0] += (char)(time / 1000);
    time_str[1] += (char)((time / 100) % 10);
    time_str[2] += (char)((time / 10) % 10);
    time_str[3] += (char)(time % 10);
    print_bg_font_18(d2_handle, 820, 280, DISPLAY_FONT_SCALING, (char*)time_str);

    char num_str[3] = {'0', '0', '\0'};
    num_str[0] += (char) (detection_count / 10);
    num_str[1] +=  (char) (detection_count % 10);
    print_bg_font_18(d2_handle, 820, 430, DISPLAY_FONT_SCALING, (char*)num_str);

}

/*********************************************************************************************************************
 *  do_detection_screen function: display the camera image and palm detection result on the mipi lcd
 *  @param       None
 *  @retval      None
***********************************************************************************************************************/
void  do_detection_screen(bool ai_result_new)
{
    vision_ai_app_err_t vision_ai_status = VISION_AI_APP_SUCCESS;

    if(!(xEventGroupGetBits(g_ai_app_event) & DISPLAY_PAUSE))
    {
        /* Clear stale vsync flag, then wait for the NEXT vsync so the
         * GLCDC has finished scanning the front-buffer before we touch it. */
        xEventGroupClearBits(g_ai_app_event, GLCDC_VSYNC);
        xEventGroupWaitBits(g_ai_app_event, GLCDC_VSYNC, pdTRUE, pdTRUE, portMAX_DELAY);

        graphics_start_frame();

        /* show static information */
        display_camera_image();

        /* Print static test */
        if(exe_count_print_static_text < 2)
        {
            print_static_text();
            exe_count_print_static_text++;
        }

        /* if a new inference has finished, update the detection result: bounding box and number of palms */
        if(ai_result_new)
        {
            detection_count = 0;
            for(uint8_t i = 0; i < AI_MAX_DETECTION_NUM; i++)
            {
                if((g_ai_detection[i].m_x != 0) && (g_ai_detection[i].m_y != 0))
                {
                    calculate_and_draw_bounding_box(i);
                }
            }
        }
        else
        {
            /* Human movement is slower than the mipi lcd refresh rate. Keep the previous bounding box until a new inference is finished. */
            for(uint8_t i = 0; i < AI_MAX_DETECTION_NUM; i++)
            {
                if((g_ai_detection[i].m_x != 0) && (g_ai_detection[i].m_y != 0))
                {
                    draw_bounding_box(i);
                }
            }
        }

        print_inf_time_and_detections();

#if (ENABLE_DRW_ERROR_CONSOLE_OUTPUT == 1)
        {
            /* Read before the flip: d2_geterror returns and clears the delayed
             * code recorded while the list was being built. */
            const d2_s32 err = d2_geterror(d2_handle);
            if (0 != err)
            {
                g_drw_last_error = (int32_t)err;
            }
        }
#endif

        /* Wait for previous frame rendering to finish, then finalize this frame and flip the buffers */
        graphics_end_frame();
    }
}
