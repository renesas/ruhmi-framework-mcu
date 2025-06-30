/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/**********************************************************************************************************************
 * File Name    : image_classification_screen_mipi.c
 * Version      : .
 * Description  : The image classification screen display on mipi lcd.
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
#include "Labels.h"

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

void  do_image_classification_screen(bool ai_result_new);

static uint8_t exe_count_print_static_text = 0;

static char local_str[5][32] = {0};
static char local_prob[5][8] = {0};

/***************************************************************************************************************************
 * Private global variables and functions
 ***************************************************************************************************************************/
static void print_static_text (void);
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
 *  print_static_text function
 *  This function prints the static text which does not change based on inference result.
 *  @param   	None
 *  @retval     None
***********************************************************************************************************************/
static void print_static_text(void)
{
	/* show model information */
	print_bg_font_18(d2_handle, 820,  50, DISPLAY_FONT_SCALING, (char*)"Model:");
	print_bg_font_18(d2_handle, 820,  90, DISPLAY_FONT_SCALING, (char*)"MobileNet");
	print_bg_font_18(d2_handle, 820, 120, DISPLAY_FONT_SCALING, (char*)"V1");

	/*show inference time in ms*/
	print_bg_font_18(d2_handle, 820, 200, DISPLAY_FONT_SCALING, (char*)"Inference");
	print_bg_font_18(d2_handle, 820, 230, DISPLAY_FONT_SCALING, (char*)"time:");
}

/*********************************************************************************************************************
 *  print_inf_time function
 *  This function prints the time used in the previously finished inference.
 *  @param      None
 *  @retval     None
***********************************************************************************************************************/
static void print_inf_time(void)
{
    uint32_t time = (uint32_t)(application_processing_time.ai_inference_time_ms); // ms

    // Clear last draw
    print_bg_font_18(d2_handle, 820, 280, DISPLAY_FONT_SCALING,  "             ");
    //print_bg_font_18(d2_handle, 820, 430, DISPLAY_FONT_SCALING,  "       ");

    // update string on display
    char time_str[8] = {'0', '0', '0', '0', ' ', 'm', 's', '\0'};
    time_str[0] += (char)(time / 1000);
    time_str[1] += (char)((time / 100) % 10);
    time_str[2] += (char)((time / 10) % 10);
    time_str[3] += (char)(time % 10);
    print_bg_font_18(d2_handle, 820, 280, DISPLAY_FONT_SCALING, (char*)time_str);
}

void process_str(const char* input, char* output, int max_len) {
    int i;
    for (i = 0; input[i] != '\0' && i < max_len - 1; i++) {
        if (input[i] == ',') {
            break;
        }
        output[i] = input[i];
    }
    for(; i < max_len - 1; i++){
        output[i] = ' ';
    }
    output[max_len - 1] = '\0';
}

/*********************************************************************************************************************
 *  do_image_classification_screen function: display the camera image and image classification result on the mipi lcd
 *  @param       None
 *  @retval      None
***********************************************************************************************************************/
void do_image_classification_screen(bool ai_result_new)
{
    vision_ai_app_err_t vision_ai_status = VISION_AI_APP_SUCCESS;
    const char** labels = getLabelPtr();
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
        d2_point vpos = 320;
        d2_point hpos = 830;
        /* if a new inference has finished, update the detection result: bounding box and number of faces */
        if(ai_result_new)
        {
            for(uint8_t i = 0; i < AI_MAX_DETECTION_NUM; i++)
            {
                //print_bg_font_18(d2_handle, 820, 300 + 30*i, DISPLAY_FONT_SCALING, (char*)"Inference");
#define MAX_STR_LEN 15
                char processed_str[MAX_STR_LEN] = {0};

                process_str(labels[g_ai_classification[i].category], processed_str, MAX_STR_LEN);
                sprintf(local_str[i],"%s            ", processed_str);
                local_str[i][MAX_STR_LEN] = '\0';
                memset(&local_str[i][strlen(processed_str)], ' ', strlen(local_str[i])-1);

                sprintf(local_prob[i],"%02d%%  ", (size_t)(g_ai_classification[i].prob * 100.0f));
                local_prob[i][5] = '\0';
                print_bg_font_18(d2_handle, hpos, vpos + 30*i, NORMAL_FONT_SCALING, (char*)local_prob[i]);
                print_bg_font_18(d2_handle, hpos + 50, vpos + 30*i, NORMAL_FONT_SCALING, (char*)local_str[i]);
            }
        }

        print_inf_time();

        /* Wait for previous frame rendering to finish, then finalize this frame and flip the buffers */
        graphics_end_frame();
    }
}
