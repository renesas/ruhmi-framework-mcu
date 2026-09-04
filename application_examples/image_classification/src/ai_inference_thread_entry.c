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
#define AI_THREAD_YIELD                     (25)

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

extern vision_ai_app_err_t image_classification(void);

/***************************************************************************************************************************
 * Exported global variables and functions (to be accessed by other files)
 ***************************************************************************************************************************/

st_ai_classification_point_t g_ai_classification[AI_MAX_DETECTION_NUM] = {};

/***************************************************************************************************************************
 * Private global variables and functions
 ***************************************************************************************************************************/


/* Categories tracked by class ID across frames, independent of g_ai_classification[]
 * (which only ever holds this frame's *displayed* Top-N, derived from this pool). Kept
 * separate so a category's smoothed confidence survives even on frames where it briefly
 * drops out of the raw per-frame Top-N. */
typedef struct
{
    bool           b_valid;
    bool           b_seen_this_frame;
    unsigned short category;
    float          smoothed_prob;
} st_class_pool_slot_t;

static st_class_pool_slot_t g_class_pool[AI_CLASS_POOL_SIZE] = {};

/* Find the pool slot already tracking `category`, or a slot to start tracking it in.
 * Preference order: exact match > free slot > evict the weakest slot not already
 * touched earlier in this same frame's batch (so one frame's own results can never
 * evict each other -- guaranteed possible since AI_CLASS_POOL_SIZE > AI_MAX_DETECTION_NUM). */
static st_class_pool_slot_t* find_or_alloc_pool_slot(unsigned short category)
{
    for (int i = 0; i < AI_CLASS_POOL_SIZE; i++)
    {
        if (g_class_pool[i].b_valid && (g_class_pool[i].category == category))
        {
            return &g_class_pool[i];
        }
    }
    for (int i = 0; i < AI_CLASS_POOL_SIZE; i++)
    {
        if (!g_class_pool[i].b_valid)
        {
            return &g_class_pool[i];
        }
    }
    st_class_pool_slot_t* p_lowest = NULL;
    for (int i = 0; i < AI_CLASS_POOL_SIZE; i++)
    {
        if (!g_class_pool[i].b_seen_this_frame &&
            ((NULL == p_lowest) || (g_class_pool[i].smoothed_prob < p_lowest->smoothed_prob)))
        {
            p_lowest = &g_class_pool[i];
        }
    }
    return p_lowest;
}

/*********************************************************************************************************************
 *  Read one of this frame's raw Top-N classification results (index 0 = highest raw
 *  probability) into the class pool above, smoothing each category's confidence across
 *  frames by class ID. On the last index of the batch (index == total_count - 1), the pool
 *  is re-sorted and the smoothed Top-N is published to g_ai_classification[] for the
 *  display thread.
 *  @param[IN]   index: index of the result in this frame's raw Top-N list
 *  @param[IN]   category: class ID reported by the classifier for this result
 *  @param[IN]   probability: this frame's raw (or dequantized) score for that class
 *  @param[IN]   total_count: number of results in this frame's raw Top-N list (the caller's
 *               results.size(), i.e. whatever GetTopNResults() actually returned this frame --
 *               NOT assumed to equal AI_MAX_DETECTION_NUM, so a mismatch between the two can
 *               never silently break the "did we just process the last result" check below).
 *  @retval      None
***********************************************************************************************************************/
void update_classification_result(unsigned index, unsigned short category, float probability, unsigned total_count)
{
    if (0 == index)
    {
        for (int i = 0; i < AI_CLASS_POOL_SIZE; i++)
        {
            g_class_pool[i].b_seen_this_frame = false;
        }
    }

    st_class_pool_slot_t* p_slot = find_or_alloc_pool_slot(category);
    if (NULL != p_slot)
    {
        if (p_slot->b_valid && (p_slot->category == category))
        {
            p_slot->smoothed_prob += AI_CLASS_SMOOTHING_ALPHA * (probability - p_slot->smoothed_prob);
        }
        else
        {
            /* First time this category has been seen: show it immediately, nothing to smooth against yet. */
            p_slot->b_valid = true;
            p_slot->category = category;
            p_slot->smoothed_prob = probability;
        }
        p_slot->b_seen_this_frame = true;
    }

    if ((0 != total_count) && (index == (total_count - 1)))
    {
        /* Categories not seen this frame drift down instead of vanishing outright,
         * so a class that only briefly drops out of the raw Top-N doesn't flicker away. */
        for (int i = 0; i < AI_CLASS_POOL_SIZE; i++)
        {
            if (g_class_pool[i].b_valid && !g_class_pool[i].b_seen_this_frame)
            {
                g_class_pool[i].smoothed_prob *= AI_CLASS_DECAY_ALPHA;
                if (g_class_pool[i].smoothed_prob < AI_CLASS_MIN_PROB)
                {
                    g_class_pool[i].b_valid = false;
                }
            }
        }

        /* Selection sort of the valid pool slots by smoothed probability, descending.
         * AI_CLASS_POOL_SIZE is tiny (default 10), so an O(n^2) sort is cheap here. */
        uint8_t order[AI_CLASS_POOL_SIZE];
        uint8_t valid_count = 0;
        for (uint8_t i = 0; i < AI_CLASS_POOL_SIZE; i++)
        {
            if (g_class_pool[i].b_valid)
            {
                order[valid_count++] = i;
            }
        }
        for (uint8_t a = 0; a < valid_count; a++)
        {
            uint8_t best = a;
            for (uint8_t b = (uint8_t)(a + 1); b < valid_count; b++)
            {
                if (g_class_pool[order[b]].smoothed_prob > g_class_pool[order[best]].smoothed_prob)
                {
                    best = b;
                }
            }
            uint8_t tmp = order[a]; order[a] = order[best]; order[best] = tmp;
        }

        for (uint32_t slot = 0; slot < AI_MAX_DETECTION_NUM; slot++)
        {
            if (slot < valid_count)
            {
                g_ai_classification[slot].category = g_class_pool[order[slot]].category;
                g_ai_classification[slot].prob = g_class_pool[order[slot]].smoothed_prob;
            }
            else
            {
                g_ai_classification[slot].category = 0;
                g_ai_classification[slot].prob = 0.0f;
            }
        }

        float sum = 1e-6f;
        for (uint32_t i = 0; i < AI_MAX_DETECTION_NUM; i++) {
            sum += g_ai_classification[i].prob;
        }
        for (uint32_t i = 0; i < AI_MAX_DETECTION_NUM; i++) {
            g_ai_classification[i].prob /= sum;
        }
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
            memset(&g_ai_classification[i], 0, sizeof(g_ai_classification[i]));
        }
        

        // Execute AI inference (image classification)
        INFERENCE_START_INDICATE_LED;
        vision_ai_status = image_classification();

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
