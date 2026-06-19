/*
 * SPDX-FileCopyrightText: Copyright 2022 Arm Limited and/or its affiliates <open-source-office@arm.com>
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "log_macros.h"
#include "common_util.h"

extern "C" {
#include "time_counter.h"
#include "wrapper.h"
#include "palm_postprocess.h"
#include "sub_0000_tensors.h"
#include "sub_0002_tensors.h"
extern uint8_t sub_0000_arena[];
extern uint8_t sub_0002_arena[];
void update_detection_result(uint16_t index, signed short  x, signed short  y, signed short  w, signed short  h);
}

#define IMAGE_DATA_SIZE  (AI_INPUT_IMAGE_WIDTH * AI_INPUT_IMAGE_HEIGHT * AI_INPUT_IMAGE_BYTE_PER_PIXEL)
extern int8_t model_buffer_int8[IMAGE_DATA_SIZE];

/* Palm model quantization parameters (from RUHMI perf eval) */
#define PALM_NUM_ANCHORS       2016
#define PALM_SCORES_SCALE      0.00390625f
#define PALM_SCORES_ZP         (-128)
#define PALM_BOXES_SCALE       0.0070548211f
#define PALM_BOXES_ZP          (-80)
#define PALM_KP_SCALE          0.005439954f
#define PALM_KP_ZP             (-106)

/* Static buffers for dequantized outputs — placed in SDRAM to save SRAM */
static float dequant_scores[PALM_NUM_ANCHORS]     BSP_PLACE_IN_SECTION(".sdram");
static float dequant_boxes[PALM_NUM_ANCHORS * 4]  BSP_PLACE_IN_SECTION(".sdram");
static float dequant_kp0[PALM_NUM_ANCHORS * 2]    BSP_PLACE_IN_SECTION(".sdram");
static float dequant_kp2[PALM_NUM_ANCHORS * 2]    BSP_PLACE_IN_SECTION(".sdram");
static palm_box_t palm_results[AI_MAX_DETECTION_NUM];


/*********************************************************************************************************************
 *  main_loop_palm_detection function: runs palm detection inference and post-processing.
 *  @param[IN]   None
 *  @retval      true	successful execution.
 *  			 false	handler call failed.
***********************************************************************************************************************/
bool main_loop_palm_detection()
{
    /* Copy the AI input image to tensor arena */
    memcpy((void*)mera_input_ptr(), (const void*)model_buffer_int8, IMAGE_DATA_SIZE);

    volatile uint32_t old_counter = TimeCounter_CurrentCountGet();

    /* Execute AI inference */
    mera_invoke();

    application_processing_time.ai_inference_time_ms = TimeCounter_CountValueConvertToMs(old_counter, TimeCounter_CurrentCountGet());

#if (BSP_CFG_DCACHE_ENABLED == 1)
    /* Invalidate only NPU arenas so CPU sees fresh output (don't invalidate entire cache in RTOS!) */
    SCB_InvalidateDCache_by_Addr((uint32_t*)sub_0000_arena, (int32_t)kArenaSize_sub_0000);
    SCB_InvalidateDCache_by_Addr((uint32_t*)sub_0002_arena, (int32_t)kArenaSize_sub_0002);
#endif

    /* Get output pointers */
    int8_t* out_scores = mera_output_scores_ptr();   /* [2016]   */
    int8_t* out_boxes  = mera_output_boxes_ptr();     /* [2016,4] */
    int8_t* out_kp0    = mera_output_kp0_ptr();       /* [2016,2] */
    int8_t* out_kp2    = mera_output_kp2_ptr();       /* [2016,2] */

    /* Dequantize all outputs to float */
    palm_dequantize_i8(out_scores, PALM_NUM_ANCHORS,     PALM_SCORES_SCALE, PALM_SCORES_ZP, dequant_scores);
    palm_dequantize_i8(out_boxes,  PALM_NUM_ANCHORS * 4, PALM_BOXES_SCALE,  PALM_BOXES_ZP,  dequant_boxes);
    palm_dequantize_i8(out_kp0,    PALM_NUM_ANCHORS * 2, PALM_KP_SCALE,     PALM_KP_ZP,     dequant_kp0);
    palm_dequantize_i8(out_kp2,    PALM_NUM_ANCHORS * 2, PALM_KP_SCALE,     PALM_KP_ZP,     dequant_kp2);

    /* Run NMS post-processing */
    palm_postprocess_config_t pp_cfg;
    pp_cfg.score_thresh = 0.45f;
    pp_cfg.iou_thresh   = 0.30f;
    pp_cfg.max_dets     = AI_MAX_DETECTION_NUM;

    int num_dets = palm_postprocess_pre_nms(
        dequant_boxes, dequant_scores, dequant_kp0, dequant_kp2,
        PALM_NUM_ANCHORS, &pp_cfg, palm_results, AI_MAX_DETECTION_NUM
    );

    /* Clear all detection slots */
    for (uint16_t i = 0; i < AI_MAX_DETECTION_NUM; i++)
    {
        update_detection_result(i, 0, 0, 0, 0);
    }

    /* Convert normalized [0,1] palm boxes to 192x192 pixel space for display */
    if (num_dets > 0)
    {
        for (int i = 0; i < num_dets; i++)
        {
            float cx = palm_results[i].box_x;
            float cy = palm_results[i].box_y;
            float sz = palm_results[i].box_size;

            /* Expand box by 2.9× to cover full hand (palm box only covers palm) */
            float hand_sz = sz * 2.9f;

            /* box_x/y/size are in normalized [0,1] coordinates of the 192x192 input */
            float x1 = (cx - 0.5f * hand_sz) * (float)AI_INPUT_IMAGE_WIDTH;
            float y1 = (cy - 0.5f * hand_sz) * (float)AI_INPUT_IMAGE_HEIGHT;
            float w  = hand_sz * (float)AI_INPUT_IMAGE_WIDTH;
            float h  = hand_sz * (float)AI_INPUT_IMAGE_HEIGHT;

            /* Clamp */
            if (x1 < 0) x1 = 0;
            if (y1 < 0) y1 = 0;
            if (x1 + w > AI_INPUT_IMAGE_WIDTH)  w = AI_INPUT_IMAGE_WIDTH  - x1;
            if (y1 + h > AI_INPUT_IMAGE_HEIGHT) h = AI_INPUT_IMAGE_HEIGHT - y1;

            update_detection_result((uint16_t)i,
                (signed short)x1, (signed short)y1,
                (signed short)w,  (signed short)h);
        }
    }

    return true;
}
