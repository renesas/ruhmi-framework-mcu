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
#include <string.h>
#include <math.h>

extern "C" {
#include "time_counter.h"
#include "wrapper.h"
#include "landmark_wrapper.h"
#include "palm_postprocess.h"
#include "palm_preprocess.h"
#include "landmark_preprocess.h"
#include "landmark_postprocess.h"
#include "./ai_application/ruhmi_conversion_results/sub_0000_tensors.h"
#include "./ai_application/ruhmi_conversion_results/sub_0002_tensors.h"
#include "./ai_application/ruhmi_landmark_results/sub_0000__landmark_tensors.h"
extern uint8_t sub_0000_arena[];
extern uint8_t sub_0002_arena[];
#define sub_0000__landmark_arena sub_0000_arena  /* shared SRAM — never run simultaneously */
void update_detection_result(uint16_t index, signed short  x, signed short  y, signed short  w, signed short  h);
#include "landmark_display.h"

/* Camera RGB565 buffer — declared in camera_layer.h */
extern uint8_t camera_capture_image_rgb565[];

/* Palm preprocess meta — declared in camera_display_thread_entry.c */
extern palm_preprocess_meta_t g_palm_preprocess_meta;
}

#define IMAGE_DATA_SIZE  (AI_INPUT_IMAGE_WIDTH * AI_INPUT_IMAGE_HEIGHT * AI_INPUT_IMAGE_BYTE_PER_PIXEL)
extern int8_t model_buffer_int8[IMAGE_DATA_SIZE];

/* Maximum number of hands to run landmark on (limit to reduce SDRAM bus load) */
#define MAX_LANDMARK_HANDS  2

/* Palm model quantization parameters (from RUHMI perf eval) */
#define PALM_NUM_ANCHORS       2016
#define PALM_SCORES_SCALE      0.00390625f
#define PALM_SCORES_ZP         (-128)
#define PALM_BOXES_SCALE       0.0070548211f
#define PALM_BOXES_ZP          (-80)
#define PALM_KP_SCALE          0.005439954f
#define PALM_KP_ZP             (-106)

/* Static buffers for dequantized outputs — keep in SRAM to avoid SDRAM bus contention with LCD */
static float dequant_scores[PALM_NUM_ANCHORS];
static float dequant_boxes[PALM_NUM_ANCHORS * 4];
static float dequant_kp0[PALM_NUM_ANCHORS * 2];
static float dequant_kp2[PALM_NUM_ANCHORS * 2];
static palm_box_t palm_results[MAX_LANDMARK_HANDS];

/* Landmark model INT8 input tensor (224×224×3 = 150528 bytes)
 * Moved to SDRAM to free SRAM for the shared arena.
 * Only accessed by CPU briefly (preprocess + memcpy), not during NPU inference. */
static int8_t landmark_input_buf[LANDMARK_INPUT_SIZE] BSP_ALIGN_VARIABLE(32) BSP_PLACE_IN_SECTION(BSP_UNINIT_SECTION_PREFIX ".sdram_noinit");


/*********************************************************************************************************************
 *  main_loop_palm_detection function: runs palm detection inference and post-processing.
 *  @param[IN]   None
 *  @retval      true   successful execution.
 *               false  handler call failed.
***********************************************************************************************************************/
bool main_loop_palm_detection()
{
    /* Start pipeline timer (covers pre-copy + inference + post-processing + landmark) */
    volatile uint32_t pipeline_start = TimeCounter_CurrentCountGet();

    /* Copy the AI input image to tensor arena */
    memcpy((void*)mera_input_ptr(), (const void*)model_buffer_int8, IMAGE_DATA_SIZE);

    /* Execute AI inference */
    mera_invoke();

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
    pp_cfg.max_dets     = MAX_LANDMARK_HANDS;

    int num_dets = palm_postprocess_pre_nms(
        dequant_boxes, dequant_scores, dequant_kp0, dequant_kp2,
        PALM_NUM_ANCHORS, &pp_cfg, palm_results, MAX_LANDMARK_HANDS
    );

    /* Clear all detection slots */
    for (uint16_t i = 0; i < AI_MAX_DETECTION_NUM; i++)
    {
        update_detection_result(i, 0, 0, 0, 0);
        /* Clear landmark result for this slot */
        landmark_result_t empty_lm;
        memset(&empty_lm, 0, sizeof(empty_lm));
        update_landmark_result(i, &empty_lm);
    }

    /* Convert normalized [0,1] palm boxes to camera pixel coords (640×480)
     * using actual letterbox parameters, then store for display. */
    if (num_dets > 0)
    {
        const int resized_w = g_palm_preprocess_meta.resized_w;   /* 192 */
        const int resized_h = g_palm_preprocess_meta.resized_h;   /* 144 */
        const int start_x   = g_palm_preprocess_meta.start_x;    /*   0 */
        const int start_y   = g_palm_preprocess_meta.start_y;    /*  24 */

        for (int i = 0; i < num_dets; i++)
        {
            float cx = palm_results[i].box_x;
            float cy = palm_results[i].box_y;
            float sz = palm_results[i].box_size;

            /* Map from [0,1] model space → 192×192 pixels → undo letterbox → camera pixels */
            float px_x1 = (cx - 0.5f * sz) * (float)AI_INPUT_IMAGE_WIDTH;
            float px_y1 = (cy - 0.5f * sz) * (float)AI_INPUT_IMAGE_HEIGHT;
            float px_w  = sz * (float)AI_INPUT_IMAGE_WIDTH;
            float px_h  = sz * (float)AI_INPUT_IMAGE_HEIGHT;

            float cam_x1 = (px_x1 - (float)start_x) / (float)resized_w * (float)CAM_VGA_WIDTH;
            float cam_y1 = (px_y1 - (float)start_y) / (float)resized_h * (float)CAM_VGA_HEIGHT;
            float cam_w  = px_w / (float)resized_w * (float)CAM_VGA_WIDTH;
            float cam_h  = px_h / (float)resized_h * (float)CAM_VGA_HEIGHT;

            if (cam_x1 < 0) cam_x1 = 0;
            if (cam_y1 < 0) cam_y1 = 0;
            if (cam_x1 + cam_w > CAM_VGA_WIDTH)  cam_w = (float)CAM_VGA_WIDTH  - cam_x1;
            if (cam_y1 + cam_h > CAM_VGA_HEIGHT) cam_h = (float)CAM_VGA_HEIGHT - cam_y1;

            update_detection_result((uint16_t)i,
                (signed short)cam_x1, (signed short)cam_y1,
                (signed short)cam_w,  (signed short)cam_h);
        }

        /* ---------------------------------------------------------------
         * HAND LANDMARK PIPELINE
         * Convert palm keypoints → rotated hand rectangles → run landmark model
         * Uses the same keypoint-based computation as the working perf_eval:
         *   1. Remap kp0/kp2 from model [0,1] → camera pixel coords
         *   2. Center = midpoint of kp0 and kp2
         *   3. Size from kp0↔kp2 distance: rr_size = sqrt(dist²×2.8)×2
         *   4. Angle = atan2(dy, dx) − π/2
         *   5. Normalize for landmark_preprocess
         * --------------------------------------------------------------- */
        const int resized_w_lm = g_palm_preprocess_meta.resized_w;
        const int resized_h_lm = g_palm_preprocess_meta.resized_h;
        const int start_x_lm   = g_palm_preprocess_meta.start_x;
        const int start_y_lm   = g_palm_preprocess_meta.start_y;
        const float scale_lm   = (float)resized_w_lm / (float)CAM_VGA_WIDTH; /* 192/640 = 0.3 */

        palm_rotated_hand_t hands[MAX_LANDMARK_HANDS];
        int num_hands = 0;
        for (int i = 0; i < num_dets && num_hands < MAX_LANDMARK_HANDS; i++)
        {
            /* Remap kp0, kp2 from model-normalised [0,1] to camera pixel coords */
            float kp0_xp = palm_results[i].kp0_x * (float)AI_INPUT_IMAGE_WIDTH / scale_lm;
            float kp0_yp = (palm_results[i].kp0_y * (float)AI_INPUT_IMAGE_HEIGHT - (float)start_y_lm) / scale_lm;
            float kp2_xp = palm_results[i].kp2_x * (float)AI_INPUT_IMAGE_WIDTH / scale_lm;
            float kp2_yp = (palm_results[i].kp2_y * (float)AI_INPUT_IMAGE_HEIGHT - (float)start_y_lm) / scale_lm;

            float dx_p = kp2_xp - kp0_xp;
            float dy_p = kp2_yp - kp0_yp;
            float dist  = sqrtf(dx_p * dx_p + dy_p * dy_p);
            float angle = atan2f(dy_p, dx_p) - 1.5707963f; /* − π/2 */

            float cx_p = (kp0_xp + kp2_xp) * 0.5f;
            float cy_p = (kp0_yp + kp2_yp) * 0.5f;

            float rr_size = sqrtf(dist * dist * 2.8f) * 2.0f;

            const float ref_dim = (float)((CAM_VGA_WIDTH > CAM_VGA_HEIGHT)
                                           ? CAM_VGA_WIDTH : CAM_VGA_HEIGHT);

            hands[num_hands].sqn_rr_size     = rr_size / ref_dim;
            hands[num_hands].rotation        = angle;
            hands[num_hands].sqn_rr_center_x = cx_p / (float)CAM_VGA_WIDTH;
            hands[num_hands].sqn_rr_center_y = cy_p / (float)CAM_VGA_HEIGHT;
            num_hands++;
        }

        /* Landmark preprocess config — camera provides RGB565, 640×480 */
        landmark_preprocess_config_t lm_cfg;
        lm_cfg.img_w = CAM_VGA_WIDTH;
        lm_cfg.img_h = CAM_VGA_HEIGHT;
        lm_cfg.input_is_bgr = 0;
        lm_cfg.input_is_rgb565 = 1;

        for (int hi = 0; hi < num_hands; hi++)
        {
            landmark_preprocess_meta_t lm_meta;

            /* 1. Preprocess: crop rotated hand from camera RGB565, resize to 224×224 INT8 */
            int ret = landmark_preprocess(
                (const void*)camera_capture_image_rgb565,
                &lm_cfg, &hands[hi],
                landmark_input_buf, &lm_meta
            );
            if (ret < 0) continue;

            /* 2. Copy to landmark model input tensor */
            memcpy((void*)landmark_input_ptr(), (const void*)landmark_input_buf, LANDMARK_INPUT_SIZE);

#if (BSP_CFG_DCACHE_ENABLED == 1)
            SCB_CleanDCache_by_Addr((uint32_t*)sub_0000__landmark_arena, (int32_t)kArenaSize_sub_0000__landmark);
#endif

            /* 3. Run landmark inference */
            landmark_invoke();

#if (BSP_CFG_DCACHE_ENABLED == 1)
            SCB_InvalidateDCache_by_Addr((uint32_t*)sub_0000__landmark_arena, (int32_t)kArenaSize_sub_0000__landmark);
#endif

            /* 4. Postprocess: dequantize + threshold + remap to camera coords */
            landmark_result_t lm_result;
            int valid = landmark_postprocess(
                landmark_output_xyz_ptr(),
                landmark_output_score_ptr(),
                landmark_output_hand_ptr(),
                &lm_meta,
                0.5f,   /* score threshold */
                &lm_result
            );

            if (valid > 0)
            {
                update_landmark_result((uint16_t)hi, &lm_result);
            }
        }
    }

    /* Record full pipeline time (pre + palm inference + post + landmark) */
    application_processing_time.ai_inference_time_ms = TimeCounter_CountValueConvertToMs(pipeline_start, TimeCounter_CurrentCountGet());

    return true;
}
