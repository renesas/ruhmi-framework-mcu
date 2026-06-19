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
#include "./ai_application/palm_detection/landmark_display.h"

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

static void print_static_text (void);
static void draw_bounding_box(uint8_t i);
static void draw_landmark_points(uint8_t det_idx);
static void calculate_and_draw_bounding_box(uint8_t i);
static void display_camera_image(void);

/*********************************************************************************************************************
 *  display_camera_image function
 *  			 This function selects the rotated camera image buffer in QVGA mode 240x320 format and
 *  			 displays in VGA 480x640 format at the center of the mipi lcd.
 *  @param   	None
 *  @retval     None.
***********************************************************************************************************************/
static void display_camera_image(void)
{
#if (BSP_CFG_DCACHE_ENABLED == 1)
    // Clean cache data for camera capture image buffer because this buffer will be accessed by DRW hardware
    SCB_CleanDCache_by_Addr(&camera_capture_image_rgb565[0], (int32_t)(camera_capture_image_rgb565_size));
#endif

	/* Specify camera input. */
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
 *  			 This function picks the index of the detection result which has a bounding box and
 *  			 uses DRW to render a red bounding box on the mipi lcd.
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
 *  draw_landmark_points function
 *  Draws the 21 hand landmark keypoints as small green circles on the LCD.
 *  Landmark coordinates are in camera space (640x480) and are scaled to display.
 *  @param[IN]   det_idx: detection slot index
 *  @retval      None
***********************************************************************************************************************/
static void draw_landmark_points(uint8_t det_idx)
{
    const landmark_result_t* lm = &g_landmark_results[det_idx];
    if (lm->num_points <= 0 || lm->hand_score < 0.5f) return;

    /* Green color for keypoints */
    d2_setcolor(d2_handle, 0, 0x0000FF00);

    for (int k = 0; k < lm->num_points; k++)
    {
        /* Landmark points are in camera pixel coords (640x480).
         * Scale to display coords using CAMERA_IMAGE_SCALING. */
        d2_point dx = (d2_point)((float)lm->pts[k].x * CAMERA_IMAGE_SCALING);
        d2_point dy = (d2_point)((float)lm->pts[k].y * CAMERA_IMAGE_SCALING);

        /* Draw a small filled circle (radius = 3 display pixels) */
        d2_rendercircle(d2_handle,
            (d2_point)(dx << 4), (d2_point)(dy << 4),
            (d2_width)(3 << 4), (d2_width)(0));
    }

    /* Draw skeleton lines connecting key joints (optional but nice visual) */
    /* Hand skeleton connections: wrist→thumb, wrist→index, etc. */
    static const int skeleton[][2] = {
        {0,1},{1,2},{2,3},{3,4},         /* thumb */
        {0,5},{5,6},{6,7},{7,8},         /* index */
        {0,9},{9,10},{10,11},{11,12},    /* middle */
        {0,13},{13,14},{14,15},{15,16},  /* ring */
        {0,17},{17,18},{18,19},{19,20},  /* pinky */
        {5,9},{9,13},{13,17}             /* palm cross */
    };

    d2_setcolor(d2_handle, 0, 0x0000FF00);
    for (int s = 0; s < 23; s++)
    {
        int a = skeleton[s][0];
        int b = skeleton[s][1];
        d2_point ax = (d2_point)((float)lm->pts[a].x * CAMERA_IMAGE_SCALING);
        d2_point ay = (d2_point)((float)lm->pts[a].y * CAMERA_IMAGE_SCALING);
        d2_point bx = (d2_point)((float)lm->pts[b].x * CAMERA_IMAGE_SCALING);
        d2_point by = (d2_point)((float)lm->pts[b].y * CAMERA_IMAGE_SCALING);

        d2_renderline(d2_handle,
            (d2_point)(ax << 4), (d2_point)(ay << 4),
            (d2_point)(bx << 4), (d2_point)(by << 4),
            (d2_point)(1 << 4), 0);
    }
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

    /* m_x/y/w/h are now in camera pixel coords (640×480).
     * Just scale directly to display coords. */
    top_left_x[i]     = (d2_point)((float)g_ai_detection[i].m_x * CAMERA_IMAGE_SCALING);
    top_left_y[i]     = (d2_point)((float)g_ai_detection[i].m_y * CAMERA_IMAGE_SCALING);
    bottom_right_x[i] = (d2_point)((float)(g_ai_detection[i].m_x + g_ai_detection[i].m_w) * CAMERA_IMAGE_SCALING);
    bottom_right_y[i] = (d2_point)((float)(g_ai_detection[i].m_y + g_ai_detection[i].m_h) * CAMERA_IMAGE_SCALING);

    draw_bounding_box(i);
}

/*********************************************************************************************************************
 *  print_static_text function
 *  This function prints the static text which does not change based on inference result.
 *  @param   	None
 *  @retval     None
***********************************************************************************************************************/
static void print_static_text(void)
{
	/* show model information */
	print_bg_font_18(d2_handle, 820,  50, DISPLAY_FONT_SCALING, (char*)"Model:");
	print_bg_font_18(d2_handle, 820,  90, DISPLAY_FONT_SCALING, (char*)"Hand");
	print_bg_font_18(d2_handle, 820, 120, DISPLAY_FONT_SCALING, (char*)"Landmark");

	/*show pipeline time in ms*/
	print_bg_font_18(d2_handle, 820, 200, DISPLAY_FONT_SCALING, (char*)"Pipeline");
	print_bg_font_18(d2_handle, 820, 230, DISPLAY_FONT_SCALING, (char*)"time:");

	/*print the number of palms detected */
	print_bg_font_18(d2_handle, 820, 350, DISPLAY_FONT_SCALING, (char*)"No of ");
	print_bg_font_18(d2_handle, 820, 380, DISPLAY_FONT_SCALING, (char*)"Hands:");
}

/*********************************************************************************************************************
 *  print_inf_time_and_detections function
 *  This function prints the time used in the previously finished inference and the number of palms detected.
 *  @param   	None
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
                /* Draw landmark keypoints if available */
                draw_landmark_points(i);
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
                draw_landmark_points(i);
            }
        }

        print_inf_time_and_detections();

        /* Wait for previous frame rendering to finish, then finalize this frame and flip the buffers */
        graphics_end_frame();
    }
}
