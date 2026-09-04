/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/**********************************************************************************************************************
 * File Name    : ai_inference_thread_entry.c
 * Description  : This file defines the entry function of the ai thread and activates the inference. It also includes
 *                the image pre processing before inference.
 **********************************************************************************************************************/
#include "ai_inference_thread.h"

#include <stdio.h>
#include <math.h>
#include "common_util.h"
#include "common_data.h"

#include "camera_layer.h"
#include "camera_utils.h"

#include "application_config.h"
#include "ai_application_config.h"

#include "time_counter.h"

/***************************************************************************************************************************
 * Macro definitions
 ***************************************************************************************************************************/
#define AI_THREAD_YIELD                     (1U)

/***************************************************************************************************************************
 * Typedef definitions
 ***************************************************************************************************************************/
/***************************************************************************************************************************
 * Imported global variables and functions (from other files)
 ***************************************************************************************************************************/

/* Inference engine input buffer */
#if (AI_INPUT_IMAGE_ALLOCATION == ALLOCATE_TO_ONCHIP_RAM)
int8_t model_buffer_int8[AI_INPUT_IMAGE_WIDTH * AI_INPUT_IMAGE_HEIGHT * AI_INPUT_IMAGE_BYTE_PER_PIXEL] BSP_ALIGN_VARIABLE(8);
#elif (AI_INPUT_IMAGE_ALLOCATION == ALLOCATE_TO_SDRAM)
int8_t model_buffer_int8[AI_INPUT_IMAGE_WIDTH * AI_INPUT_IMAGE_HEIGHT * AI_INPUT_IMAGE_BYTE_PER_PIXEL] BSP_PLACE_IN_SECTION(".sdram")  BSP_ALIGN_VARIABLE(8);
#else
#error "Add your preferred buffer definition"
#endif
uint32_t model_buffer_int8_size = sizeof(model_buffer_int8);

extern vision_ai_app_err_t face_detection (void);

/***************************************************************************************************************************
 * Exported global variables and functions (to be accessed by other files)
 ***************************************************************************************************************************/

st_ai_detection_point_t g_ai_detection[AI_MAX_DETECTION_NUM] = {};

void update_detection_result(uint16_t index, signed short  x, signed short  y, signed short  w, signed short  h);

/***************************************************************************************************************************
 * Private global variables and functions
 ***************************************************************************************************************************/


/* Per-slot smoothing state, indexed the same as g_ai_detection[]. Kept separate so it
 * survives the per-frame clear-to-zero of g_ai_detection[] done by the caller. */
typedef struct
{
    bool  b_valid;
    float x;
    float y;
    float w;
    float h;
} st_ai_detection_filter_t;

static st_ai_detection_filter_t g_ai_detection_filter[AI_MAX_DETECTION_NUM] = {};

/*********************************************************************************************************************
 *  Read the face detection result to a buffer which will be used by the mipi display function.
 *  Applies a dead zone plus an exponential moving average to (x,y,w,h) to smooth out
 *  frame-to-frame jitter in the raw inference output before it reaches the display layer.
 *  @param[IN]   index: index of the image in the result list
 *  @param[IN]   x: x coordinate of the bottom left corner
 *  @param[IN]   y: y coordinate of the bottom left corner
 *  @param[IN]   w: width of the face detected
 *  @param[IN]   h: height of the face detected
 *  @retval      None
***********************************************************************************************************************/
void update_detection_result(uint16_t index, signed short  x, signed short  y, signed short  w, signed short  h)
{
    if(index < AI_MAX_DETECTION_NUM)
    {
        st_ai_detection_filter_t * const p_filter = &g_ai_detection_filter[index];

        /* (0,0,0,0) is the "no detection this slot" sentinel used throughout the app.
         * Reset the filter so a face that leaves and later re-enters the frame snaps
         * to its new position instead of smoothing in from its old, stale one. */
        if ((0 == x) && (0 == y) && (0 == w) && (0 == h))
        {
            p_filter->b_valid = false;
            g_ai_detection[index].m_x = 0;
            g_ai_detection[index].m_y = 0;
            g_ai_detection[index].m_w = 0;
            g_ai_detection[index].m_h = 0;
            return;
        }

        if (!p_filter->b_valid)
        {
            /* First detection at this slot: show it immediately, nothing to smooth against yet. */
            p_filter->b_valid = true;
            p_filter->x = (float)x;
            p_filter->y = (float)y;
            p_filter->w = (float)w;
            p_filter->h = (float)h;
        }
        else
        {
            /* Two-speed EMA instead of a hard dead zone: a hard "ignore small moves
             * entirely" dead zone froze the box until enough real movement had piled up
             * to cross the threshold in one comparison, then jumped to catch up -- looked
             * sluggish. Now every frame nudges the box at least a little, just by a much
             * smaller factor for small moves (still strong enough to cancel a persistent
             * few-pixel flicker between two overlapping candidate boxes) and a bigger
             * factor once the move is large enough to be genuine motion, so the box
             * actually tracks a moving face instead of catching up in jumps. */
            float dx = (float)x - p_filter->x;
            float dy = (float)y - p_filter->y;
            float dw = (float)w - p_filter->w;
            float dh = (float)h - p_filter->h;

            float alpha_x = (fabsf(dx) > AI_DETECTION_DEADZONE_PX) ? AI_DETECTION_SMOOTHING_ALPHA_FAST : AI_DETECTION_SMOOTHING_ALPHA_SLOW;
            float alpha_y = (fabsf(dy) > AI_DETECTION_DEADZONE_PX) ? AI_DETECTION_SMOOTHING_ALPHA_FAST : AI_DETECTION_SMOOTHING_ALPHA_SLOW;
            float alpha_w = (fabsf(dw) > AI_DETECTION_DEADZONE_PX) ? AI_DETECTION_SMOOTHING_ALPHA_FAST : AI_DETECTION_SMOOTHING_ALPHA_SLOW;
            float alpha_h = (fabsf(dh) > AI_DETECTION_DEADZONE_PX) ? AI_DETECTION_SMOOTHING_ALPHA_FAST : AI_DETECTION_SMOOTHING_ALPHA_SLOW;

            p_filter->x += alpha_x * dx;
            p_filter->y += alpha_y * dy;
            p_filter->w += alpha_w * dw;
            p_filter->h += alpha_h * dh;
        }

        g_ai_detection[index].m_x = (signed short)p_filter->x;
        g_ai_detection[index].m_y = (signed short)p_filter->y;
        g_ai_detection[index].m_w = (signed short)p_filter->w;
        g_ai_detection[index].m_h = (signed short)p_filter->h;
    }
}

#include "tensorflow/lite/micro/cortex_m_generic/debug_log_callback.h"

static void print_log(const char* s)
{
    printf("%s\n", s);
}

/*********************************************************************************************************************
 *  AI thread entry function. The image will be processed prior to inference.
 *  The image processing and inference is repeatedly carried out in this thread.
 *  @param[IN]      void *pvParameters, contains TaskHandle_t, not used.
 *  @retval      None
***********************************************************************************************************************/
void ai_inference_thread_entry(void *pvParameters)
{
    FSP_PARAMETER_NOT_USED (pvParameters);

    vision_ai_app_err_t vision_ai_status = VISION_AI_APP_SUCCESS;

    /* Wait for display and camera initialization complete */
    xEventGroupWaitBits(g_ai_app_event, (HARDWARE_DISPLAY_INIT_DONE | HARDWARE_CAMERA_INIT_DONE), pdFALSE, pdTRUE, portMAX_DELAY);

    RM_ETHOSU_Open(&g_rm_ethosu0_ctrl, &g_rm_ethosu0_cfg);

    xEventGroupSetBits(g_ai_app_event, HARDWARE_ETHOSU_INIT_DONE);

    RegisterDebugLogCallback(print_log);

    xEventGroupSetBits(g_ai_app_event, SOFTWARE_AI_INFERENCE_INIT_DONE);

    while (true)
    {
        xEventGroupWaitBits(g_ai_app_event, AI_INFERENCE_INPUT_IMAGE_READY, pdTRUE, pdTRUE, portMAX_DELAY);

        /* restart face detection statistics for each inference */
        for(int i = 0; i < AI_MAX_DETECTION_NUM; i++)
        {
            memset(&g_ai_detection[i], 0, sizeof(g_ai_detection[i]));
        }

        // Execute AI inference (face detection)
        INFERENCE_START_INDICATE_LED;
        vision_ai_status = face_detection();
        INFERENCE_END_INDICATE_LED;

        if(VISION_AI_APP_ERR_AI_INFERENCE == vision_ai_status)
        {
            handle_error(VISION_AI_APP_ERR_AI_INFERENCE);
        }

        xEventGroupSetBits(g_ai_app_event, AI_INFERENCE_RESULT_UPDATED);

        /*
         * Yield to the display thread. The AI thread does not need to run faster than human reaction and response time,
         * so a relatively larger delay is used. This value should not be too low; otherwise, the display thread
         * is negatively influenced. This value should be reevaluated if the system is updated.
         */
        vTaskDelay(AI_THREAD_YIELD);
    }
}
