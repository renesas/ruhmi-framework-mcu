/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/**********************************************************************************************************************
 * File Name    : face_detection_screen_mipi.c
 * Version      : .
 * Description  : The face detection screen display on mipi lcd.
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

void  do_face_reconition_screen(bool ai_result_new);
uint8_t face_count = 0;

static uint8_t exe_count_print_static_text = 0;

/***************************************************************************************************************************
 * Private global variables and functions
 ***************************************************************************************************************************/
static d2_point top_left_x[AI_MAX_DETECTION_NUM];
static d2_point top_left_y[AI_MAX_DETECTION_NUM];
static d2_point bottom_right_x[AI_MAX_DETECTION_NUM];
static d2_point bottom_right_y[AI_MAX_DETECTION_NUM];

static void print_static_text (void);
static void draw_bounding_box(uint8_t i);
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
 *  			 This function picks the index of the detection result which has a bounding box and
 *  			 uses DRW to render a red bounding box on the mipi lcd.
 *  @param[IN]   i: index of the detection result which has detected a face
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
 *  @param[IN]   i: index of the detection result which has detected a face
 *  @retval     None
***********************************************************************************************************************/
static void calculate_and_draw_bounding_box(uint8_t i)
{
    face_count++;

    float camera_capture_image_downscaling_for_ai = (float)CAMERA_CAPTURE_IMAGE_HEIGHT / (float)AI_INPUT_IMAGE_HEIGHT;

    /* these are the coordinate in a 480x480 space for AI coordinate*/
    signed short scaled_x = (signed short)(g_ai_detection[i].m_x * camera_capture_image_downscaling_for_ai);
    signed short scaled_y = (signed short)(g_ai_detection[i].m_y * camera_capture_image_downscaling_for_ai);
    signed short scaled_w = (signed short)(g_ai_detection[i].m_w * camera_capture_image_downscaling_for_ai);
    signed short scaled_h = (signed short)(g_ai_detection[i].m_h * camera_capture_image_downscaling_for_ai);

    top_left_x[i]     = (d2_point)((((CAMERA_CAPTURE_IMAGE_WIDTH - CAMERA_CAPTURE_IMAGE_HEIGHT) / 2) + scaled_x) * CAMERA_IMAGE_SCALING);
    top_left_y[i]     = (d2_point)(scaled_y * CAMERA_IMAGE_SCALING);
    bottom_right_x[i] = (d2_point)((((CAMERA_CAPTURE_IMAGE_WIDTH - CAMERA_CAPTURE_IMAGE_HEIGHT) / 2) + scaled_x + scaled_w) * CAMERA_IMAGE_SCALING);
    bottom_right_y[i] = (d2_point)((scaled_y + scaled_h) * CAMERA_IMAGE_SCALING);

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
	print_bg_font_18(d2_handle, 820,  90, DISPLAY_FONT_SCALING, (char*)"Yolo-");
	print_bg_font_18(d2_handle, 820, 120, DISPLAY_FONT_SCALING, (char*)"fastest");

	/*show inference time in ms*/
	print_bg_font_18(d2_handle, 820, 200, DISPLAY_FONT_SCALING, (char*)"Inference");
	print_bg_font_18(d2_handle, 820, 230, DISPLAY_FONT_SCALING, (char*)"time:");

	/*print the number of faces detected */
	print_bg_font_18(d2_handle, 820, 350, DISPLAY_FONT_SCALING, (char*)"No of ");
	print_bg_font_18(d2_handle, 820, 380, DISPLAY_FONT_SCALING, (char*)"Faces:");
}

/*********************************************************************************************************************
 *  print_inf_time_and_number_faces function
 *  This function prints the time used in the previously finished inference and the number of faces detected.
 *  @param   	None
 *  @retval     None
***********************************************************************************************************************/
static void print_inf_time_and_number_faces(void)
{
	/* The face_detection_inference_time is acquired in UseCaseHandler_obj.cc.
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
	num_str[0] += (char) (face_count / 10);
	num_str[1] +=  (char) (face_count % 10);
	print_bg_font_18(d2_handle, 820, 430, DISPLAY_FONT_SCALING, (char*)num_str);

}

/*********************************************************************************************************************
 *  do_face_reconition_screen function: display the camera image and face detection result on the mipi lcd
 *  @param       None
 *  @retval      None
***********************************************************************************************************************/
void  do_face_reconition_screen(bool ai_result_new)
{
    vision_ai_app_err_t vision_ai_status = VISION_AI_APP_SUCCESS;

    if(!(xEventGroupGetBits(g_ai_app_event) & DISPLAY_PAUSE))
    {
        /* Wait for vertical blanking period */
        xEventGroupWaitBits(g_ai_app_event, GLCDC_VSYNC, pdFALSE, pdTRUE, 1);

        graphics_start_frame();

        /* show static information */
        display_camera_image();

        /* Print static test */
        if(exe_count_print_static_text < 2)
        {
            print_static_text();
            exe_count_print_static_text++;
        }

        /* if a new inference has finished, update the detection result: bounding box and number of faces */
        if(ai_result_new)
        {
            face_count = 0;
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

        print_inf_time_and_number_faces();

        /* Wait for previous frame rendering to finish, then finalize this frame and flip the buffers */
        graphics_end_frame();
    }
}
