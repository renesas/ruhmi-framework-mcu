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
int8_t model_buffer_int8[AI_INPUT_IMAGE_WIDTH * AI_INPUT_IMAGE_HEIGHT * AI_INPUT_IMAGE_BYTE_PER_PIXEL] BSP_ALIGN_VARIABLE(32);
#elif (AI_INPUT_IMAGE_ALLOCATION == ALLOCATE_TO_SDRAM)
int8_t model_buffer_int8[AI_INPUT_IMAGE_WIDTH * AI_INPUT_IMAGE_HEIGHT * AI_INPUT_IMAGE_BYTE_PER_PIXEL] BSP_PLACE_IN_SECTION(".sdram")  BSP_ALIGN_VARIABLE(32);
#else
#error "Add your preferred buffer definition"
#endif
uint32_t model_buffer_int8_size = sizeof(model_buffer_int8);

extern vision_ai_app_err_t palm_detection (void);

/***************************************************************************************************************************
 * Exported global variables and functions (to be accessed by other files)
 ***************************************************************************************************************************/

st_ai_detection_point_t g_ai_detection[AI_MAX_DETECTION_NUM] = {};

/* Staging copy, written by the AI thread while a frame is being computed and
 * copied over the array above once the whole frame is ready.
 *
 * It exists because the display thread reads g_ai_detection every refresh with
 * no lock, while the AI thread used to clear it and then spend the whole
 * inference filling it back in. Both branches of do_detection_screen() skip a
 * slot whose m_x/m_y are zero, so for the entire duration of palm_detection()
 * -- tens of milliseconds -- there was nothing for the display to draw, and
 * the boxes blinked out on any refresh that landed in that window.
 *
 * Keeping the previous frame's boxes up until a complete new set is ready is
 * also what the "Human movement is slower than the mipi lcd refresh rate"
 * comment in the display code always intended. */
static st_ai_detection_point_t s_stage_detection[AI_MAX_DETECTION_NUM] = {};

void update_detection_result(uint16_t index, signed short  x, signed short  y, signed short  w, signed short  h);

/***************************************************************************************************************************
 * Private global variables and functions
 ***************************************************************************************************************************/


/*********************************************************************************************************************
 *  Read the detection result to a buffer which will be used by the mipi display function.
 *  @param[IN]   index: index of the image in the result list
 *  @param[IN]   x: x coordinate of the bottom left corner
 *  @param[IN]   y: y coordinate of the bottom left corner
 *  @param[IN]   w: width of the detection
 *  @param[IN]   h: height of the detection
 *  @retval      None
***********************************************************************************************************************/
void update_detection_result(uint16_t index, signed short  x, signed short  y, signed short  w, signed short  h)
{
    if(index < AI_MAX_DETECTION_NUM)
    {
        s_stage_detection[index].m_x = x;
        s_stage_detection[index].m_y = y;
        s_stage_detection[index].m_w = w;
        s_stage_detection[index].m_h = h;
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

        /* restart detection statistics for each inference.
         * Only the staging copy is cleared -- what is already on screen stays
         * valid until this frame has a complete set to replace it with. */
        for(int i = 0; i < AI_MAX_DETECTION_NUM; i++)
        {
            memset(&s_stage_detection[i], 0, sizeof(s_stage_detection[i]));
        }

        // Execute AI inference (palm detection)
        INFERENCE_START_INDICATE_LED;
        vision_ai_status = palm_detection();
        INFERENCE_END_INDICATE_LED;

        if(VISION_AI_APP_ERR_AI_INFERENCE == vision_ai_status)
        {
            handle_error(VISION_AI_APP_ERR_AI_INFERENCE);
        }

        /* Publish the whole frame at once, so the display never sees a partly
         * filled set of boxes. A handful of small structs is short enough to
         * hold the scheduler off for; letting the display preempt midway is
         * the race this replaced. */
        taskENTER_CRITICAL();
        for(int i = 0; i < AI_MAX_DETECTION_NUM; i++)
        {
            g_ai_detection[i] = s_stage_detection[i];
        }
        taskEXIT_CRITICAL();

        xEventGroupSetBits(g_ai_app_event, AI_INFERENCE_RESULT_UPDATED);

        /*
         * Yield to the display thread. The AI thread does not need to run faster than human reaction and response time,
         * so a relatively larger delay is used. This value should not be too low; otherwise, the display thread
         * is negatively influenced. This value should be reevaluated if the system is updated.
         */
        vTaskDelay(AI_THREAD_YIELD);
    }
}
