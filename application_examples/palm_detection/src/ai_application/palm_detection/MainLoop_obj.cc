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

#include <math.h>
#include <string.h>
#include <stdio.h>

extern "C" {
#include "time_counter.h"
#include "wrapper.h"
#include "palm_postprocess.h"
#include "palm_preprocess.h"
extern palm_preprocess_meta_t g_palm_preprocess_meta;

/* Forward-declared rather than #include "console_output.h", which would
 * redeclare sprintf_buffer (already visible via common_util.h) with a
 * different language linkage and fail to compile. */
vision_ai_app_err_t print_to_console(char * p_data);
#include "sub_0000_tensors.h"
#include "sub_0002_tensors.h"
extern uint8_t sub_0000_arena[];
extern uint8_t sub_0002_arena[];
void update_detection_result(uint16_t index, signed short  x, signed short  y, signed short  w, signed short  h);
}

#define IMAGE_DATA_SIZE  (AI_INPUT_IMAGE_WIDTH * AI_INPUT_IMAGE_HEIGHT * AI_INPUT_IMAGE_BYTE_PER_PIXEL)
extern int8_t model_buffer_int8[IMAGE_DATA_SIZE];

/* Frame geometry. Taken from the camera_size_list_t enum in common_util.h
 * rather than camera_layer_config.h, because that header includes
 * camera_layer.h before defining the sizes camera_layer.h needs, so it only
 * compiles from translation units that already defined them. */
#define CAM_W_F   ((float)CAM_VGA_WIDTH)    /* 640 */
#define CAM_H_F   ((float)CAM_VGA_HEIGHT)   /* 480 */

/* How far the palm box is grown to cover the whole hand, and how far its
 * centre is moved from the palm towards the fingers.
 *
 * Both come from a measurement rather than from the upstream constants. With a
 * spread hand held still and upright the model reported a palm box of size 117
 * with its centre at y=272, while the hand itself occupied y=101..355 and
 * x=233..405 (camera pixels). That makes the hand 253 px across at its widest,
 * i.e. 2.17 palm boxes, and puts its centre half a palm box above the palm
 * centre.
 *
 * 2.9 -- the figure upstream MediaPipe and palm_boxes_to_rotated_hands() use --
 * is right for the crop fed to a landmark model, which wants margin on every
 * side. Here the box is what the user sees, so it should sit close to the hand:
 * 2.4 leaves roughly 30 px above the fingertips and finishes level with the
 * wrist. Raise it towards 2.9 for more margin, lower it towards 2.2 to cut in
 * tighter. */
#define PALM_HAND_EXPAND       2.4f
#define PALM_HAND_SHIFT        0.5f

/* TEMPORARY. Prints the decoded palm geometry in camera pixels so the box
 * placement can be set from what the model actually reports, instead of from
 * an assumed convention.
 *
 * Two rounds of adjusting the expansion and the shift got the direction right
 * but not the magnitude: matching the hand in a captured frame would need a
 * shift of about 1.3 * box_size, where upstream MediaPipe uses 0.5. A gap that
 * large is not a tuning error, it means box_x/box_y/box_size do not mean what
 * the code assumes -- most likely because palm_postprocess_pre_nms() reads the
 * raw tensor as xyxy corners, while BlazePalm natively emits centre/size.
 *
 * kp0 should land on the wrist and kp2 on the base of the middle finger. If
 * they do, the keypoints are decoded correctly and only the box fields are
 * suspect. If they do not, the whole decode is.
 *
 * All values are camera pixels (640x480). Multiply by 1.25 for screen pixels.
 * Set to 0 once the geometry is settled. */
#define PALM_GEOM_MEASURE      (0)
#define PALM_GEOM_LOG_STRIDE   (8)

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

/* ===========================================================================
 * 1 Euro filter (Casiez et al., CHI 2012)
 *
 * A plain EMA forces a choice between "steady when still" and "responsive when
 * moving". The 1 Euro filter avoids it by making the cutoff frequency track
 * the estimated speed of the signal: heavy smoothing while the input sits
 * still, almost none while it moves fast.
 *
 * Same implementation as the landmark projects, so the tuning constants below
 * mean the same thing there and here.
 *
 * All state is caller-owned; zero-initialised state means "not started yet",
 * so memset(0) is a complete reset.
 * ======================================================================== */
typedef struct
{
    float x_prev;
    float dx_prev;
    int   initialized;
} one_euro_t;

static inline float one_euro_alpha(float cutoff, float dt)
{
    const float tau = 1.0f / (2.0f * PALM_PI * cutoff);
    return 1.0f / (1.0f + (tau / dt));
}

static inline float one_euro_filter(one_euro_t * p_f, float x, float dt,
                                    float min_cutoff, float beta, float d_cutoff)
{
    if (!p_f->initialized)
    {
        p_f->x_prev      = x;
        p_f->dx_prev     = 0.0f;
        p_f->initialized = 1;
        return x;
    }

    /* Derivative, itself low-passed so quantisation noise in the input does
     * not leak into the speed estimate and open the cutoff up. */
    const float dx      = (x - p_f->x_prev) / dt;
    const float alpha_d = one_euro_alpha(d_cutoff, dt);
    const float dx_hat  = (alpha_d * dx) + ((1.0f - alpha_d) * p_f->dx_prev);
    p_f->dx_prev = dx_hat;

    /* Cutoff rises with speed, then an ordinary first-order low-pass. */
    const float cutoff = min_cutoff + (beta * fabsf(dx_hat));
    const float alpha  = one_euro_alpha(cutoff, dt);
    const float x_hat  = (alpha * x) + ((1.0f - alpha) * p_f->x_prev);
    p_f->x_prev = x_hat;

    return x_hat;
}

/* Tuning. Everything fed to the filters is normalised to the frame, so "speed"
 * is in frames/second. min_cutoff dominates while the hand is still (lower =
 * steadier), beta dominates while it moves (higher = less lag).
 *
 * What is actually being removed here is not general noise but the INT8 output
 * stepping between adjacent quantisation levels. Measured with a hand held
 * still, the reported box width took only the values 113/117/121/125/129 --
 * five levels exactly 4 px apart, and one LSB of the box regression output is
 * PALM_BOXES_SCALE * PALM_HAND_EXPAND * 192 = 3.93 px. Every visible step was
 * the model flipping by one LSB, magnified 2.9x by the hand expansion and then
 * 3.125x again by the display scaling: 12 px of box jump on screen per LSB.
 *
 * Size gets a gentler setting than the centre because a hand's apparent size
 * changes far more slowly than its position, so it can afford more smoothing
 * without feeling sluggish.
 *
 * These match the landmark projects' crop-rectangle stage. Note this pipeline
 * updates them roughly 3x more often (every frame at ~39 ms, against once per
 * detector run at ~114 ms there), so the same cutoff smooths noticeably harder
 * here -- lower them further only if the box still shimmers. */
#define FILT_CENTER_MIN_CUTOFF   (0.2f)
#define FILT_CENTER_BETA         (6.0f)
#define FILT_SIZE_MIN_CUTOFF     (0.15f)
#define FILT_SIZE_BETA           (3.0f)
#define FILT_D_CUTOFF            (2.0f)

/* Used for the first frame and whenever the measured interval is not usable. */
#define FILT_NOMINAL_DT_S        (0.04f)

/* A slot is dropped after this many consecutive frames without a match, so a
 * hand that leaves the frame does not keep a filter warm for the next one that
 * happens to appear nearby. */
#define SLOT_MAX_MISSES          (3u)

/* How close a detection has to be to a slot's last centre to be treated as the
 * same hand, as a fraction of the palm size. Comfortably larger than the
 * distance a hand covers in one frame, and comfortably smaller than the gap
 * between two hands that are both in frame. */
#define SLOT_MATCH_FACTOR        (0.75f)

/* Per-hand filter state.
 *
 * Detections cannot simply be filtered by their index: palm_postprocess_pre_nms
 * emits them ordered by score, so with two hands in frame the slot a hand lands
 * in swaps as soon as their scores cross, and an index-keyed filter would then
 * blend two different hands together. Each detection is instead matched to the
 * nearest slot from the previous frame. */
typedef struct
{
    bool       active;
    uint8_t    misses;
    float      cx;          /* last filtered centre, normalised [0,1] */
    float      cy;
    one_euro_t f_cx;
    one_euro_t f_cy;
    one_euro_t f_size;
} palm_slot_t;

static palm_slot_t s_slot[AI_MAX_DETECTION_NUM];

static void palm_slot_reset(palm_slot_t * p_slot)
{
    memset(p_slot, 0, sizeof(*p_slot));
}



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

#if (BSP_CFG_DCACHE_ENABLED == 1)
    /* Write the freshly copied input back to RAM before the NPU reads it.
     *
     * The NPU is a bus master and does not snoop the CPU's write-back D-cache,
     * so without this it reads whatever RAM held before the memcpy above.
     *
     * Note that camera_display_thread_entry.c already cleans model_buffer_int8
     * after preprocessing, but that is the *source* of the copy; the CPU reads
     * it through the cache and gets the right bytes either way. What the NPU
     * actually reads is the destination, and nothing was writing that back.
     *
     * The symptom is easy to misread: the copy is 110 KB, far larger than the
     * L1 D-cache, so most lines have already been evicted naturally by the time
     * the copy finishes. Only the last ~16-32 KB written -- the bottom of the
     * image -- is still sitting dirty in cache, so detection quietly degrades
     * in the lower part of the frame and nowhere else.
     *
     * Only the input tensor needs cleaning; nothing else in this arena was
     * written by the CPU this frame, and RunModel() handles its own two
     * internal hand-offs (NPU1 output -> CPU, CPU -> NPU2). */
    SCB_CleanDCache_by_Addr((uint32_t*)mera_input_ptr(), (int32_t)IMAGE_DATA_SIZE);
#endif

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

    /* Frame interval for the filters. The detector runs once per frame here, so
     * this is just the loop period; it is measured rather than assumed because
     * the 1 Euro speed term is in units of frames per second. */
    float dt_s;
    {
        static uint32_t s_prev_tick = 0u;
        static bool     s_have_prev = false;
        const uint32_t  now = TimeCounter_CurrentCountGet();

        const uint32_t dt_ms = s_have_prev
                             ? TimeCounter_CountValueConvertToMs(s_prev_tick, now)
                             : 0u;
        s_prev_tick = now;
        s_have_prev = true;

        /* Guard both ends: 0 ms would divide by zero in the derivative, and a
         * long stall (a paused debugger, say) would otherwise register as a
         * huge dt and snap the filters wide open. */
        dt_s = ((dt_ms == 0u) || (dt_ms > 200u))
             ? FILT_NOMINAL_DT_S
             : ((float)dt_ms / 1000.0f);
    }

    /* Letterbox geometry, needed to get from the model's normalised
     * coordinates back to camera pixels. */
    const float lb_scale   = (float)g_palm_preprocess_meta.resized_w
                           / CAM_W_F;      /* 192/640 = 0.3 */
    const float lb_start_y = (float)g_palm_preprocess_meta.start_y;  /* 24 */

    /* Convert palm boxes to camera pixel coords for display */
    bool matched[AI_MAX_DETECTION_NUM] = { false };

    if (num_dets > 0)
    {
        for (int i = 0; i < num_dets; i++)
        {
            const float sz = palm_results[i].box_size;

            /* Move the box off the palm and onto the hand.
             *
             * box_x/box_y is the centre of the *palm*, and the hand extends
             * from it in the direction the fingers point, so expanding about
             * that centre spends half the box below the wrist and still falls
             * short of the fingertips -- which is exactly the "box is much
             * bigger than the hand, yet the top of the fingers is not covered"
             * case. Measured on a typical frame here the shortfall is 0.5 *
             * box_size = 21 px of the 192 input, i.e. 65 px on screen at each
             * end.
             *
             * The correction is upstream MediaPipe's shift_y, and this project
             * already carries the code for it: palm_boxes_to_rotated_hands()
             * in palm_postprocess.c does the same thing, but nothing ever
             * called it. kp0 is the wrist and kp2 the middle-finger base, so
             * their difference gives the direction the hand points, and the
             * centre moves half a palm along it.
             *
             * The drawn box stays axis-aligned because that is all
             * draw_bounding_box() can render; only the centre is corrected. */
            /* Undo the letterbox first: everything below works in camera
             * pixels, which is the only space where x and y share a scale.
             *
             * The model input is not a crop of the camera image, it is the
             * whole 640x480 frame scaled by 0.3 into a 192x192 square with 24
             * blank rows above and below. So a normalised y from the model
             * covers 192 rows of which only the middle 144 are picture, and
             * the two axes are NOT interchangeable in that space: the same
             * normalised distance means 640 px horizontally but only 480 px
             * vertically. Computing the hand's angle there would skew it, and
             * skewing the angle skews the shift that depends on it. */
            const float kp0_xp = palm_results[i].kp0_x * (float)AI_INPUT_IMAGE_WIDTH  / lb_scale;
            const float kp0_yp = ((palm_results[i].kp0_y * (float)AI_INPUT_IMAGE_HEIGHT) - lb_start_y) / lb_scale;
            const float kp2_xp = palm_results[i].kp2_x * (float)AI_INPUT_IMAGE_WIDTH  / lb_scale;
            const float kp2_yp = ((palm_results[i].kp2_y * (float)AI_INPUT_IMAGE_HEIGHT) - lb_start_y) / lb_scale;

            const float box_xp = palm_results[i].box_x * (float)AI_INPUT_IMAGE_WIDTH  / lb_scale;
            const float box_yp = ((palm_results[i].box_y * (float)AI_INPUT_IMAGE_HEIGHT) - lb_start_y) / lb_scale;
            const float sz_p   = sz * (float)AI_INPUT_IMAGE_WIDTH / lb_scale;

            /* Move the centre off the palm and onto the hand, along the line
             * from the wrist to the base of the middle finger.
             *
             * The two keypoints are the other way round from what their names
             * suggest. Upstream MediaPipe -- and palm_boxes_to_rotated_hands()
             * in palm_postprocess.c, which follows it -- takes kp0 as the wrist
             * and kp2 as the middle-finger base. Measured on this model with a
             * hand held upright, kp0 came out at y=223 and kp2 at y=327: kp2 is
             * the lower of the two, so kp2 is the wrist and kp0 the finger
             * base. Following the documented convention pushed the box half a
             * palm DOWNWARDS, away from the fingers, which is why the box kept
             * missing the fingertips while overshooting past the wrist.
             *
             * Taking the direction straight from the keypoints rather than
             * reconstructing an angle avoids the question entirely: no atan2,
             * no target-angle convention, and it holds for a hand at any
             * orientation. The drawn box is axis-aligned, so the angle itself
             * was never needed -- only which way to move the centre. */
            float dir_x = kp0_xp - kp2_xp;      /* wrist -> finger base */
            float dir_y = kp0_yp - kp2_yp;
            const float dir_len = sqrtf((dir_x * dir_x) + (dir_y * dir_y));

            if (dir_len > 1.0f)
            {
                dir_x /= dir_len;
                dir_y /= dir_len;
            }
            else
            {
                /* Degenerate keypoints: leave the box on the palm rather than
                 * shifting it in an arbitrary direction. */
                dir_x = 0.0f;
                dir_y = 0.0f;
            }

            /* Normalised by the camera frame for the filters, so the tuning
             * constants keep their usual meaning. */
            float cx = (box_xp + (PALM_HAND_SHIFT * sz_p * dir_x)) / CAM_W_F;
            float cy = (box_yp + (PALM_HAND_SHIFT * sz_p * dir_y)) / CAM_H_F;
            float hand_sz = (sz_p * PALM_HAND_EXPAND) / CAM_W_F;

#if (PALM_GEOM_MEASURE == 1)
            {
                static uint32_t s_geom_log = 0;

                if (((s_geom_log % PALM_GEOM_LOG_STRIDE) == 0) && (i == 0))
                {
                    /* box_* as decoded, before any expansion or shift. */
                    sprintf(sprintf_buffer,
                            "[GEOM] box c=(%4d,%4d) size=%4d | kp0=(%4d,%4d) kp2=(%4d,%4d) | side=%4d shift=%4d\r\n",
                            (int)lrintf(box_xp), (int)lrintf(box_yp), (int)lrintf(sz_p),
                            (int)lrintf(kp0_xp), (int)lrintf(kp0_yp),
                            (int)lrintf(kp2_xp), (int)lrintf(kp2_yp),
                            (int)lrintf(sz_p * PALM_HAND_EXPAND),
                            (int)lrintf(0.5f * sz_p));
                    print_to_console(sprintf_buffer);
                }
                s_geom_log++;
            }
#endif

            /* Match to the nearest slot carried over from the previous frame. */
            int   slot      = -1;
            float best_d2   = 0.0f;
            const float lim = SLOT_MATCH_FACTOR * hand_sz;

            for (int k = 0; k < AI_MAX_DETECTION_NUM; k++)
            {
                if (!s_slot[k].active || matched[k]) continue;

                const float ddx = cx - s_slot[k].cx;
                const float ddy = cy - s_slot[k].cy;
                const float d2  = (ddx * ddx) + (ddy * ddy);

                if ((d2 <= (lim * lim)) && ((slot < 0) || (d2 < best_d2)))
                {
                    slot    = k;
                    best_d2 = d2;
                }
            }

            if (slot < 0)
            {
                /* A hand that was not there last frame: take a free slot and
                 * start its filters from this measurement, so a new box
                 * appears where the hand is rather than drifting in. */
                for (int k = 0; k < AI_MAX_DETECTION_NUM; k++)
                {
                    if (!s_slot[k].active && !matched[k]) { slot = k; break; }
                }
                if (slot < 0) continue;      /* no slot free; drop this one */

                palm_slot_reset(&s_slot[slot]);
                s_slot[slot].active = true;
            }

            matched[slot]        = true;
            s_slot[slot].misses  = 0u;

            cx      = one_euro_filter(&s_slot[slot].f_cx, cx, dt_s,
                                      FILT_CENTER_MIN_CUTOFF, FILT_CENTER_BETA, FILT_D_CUTOFF);
            cy      = one_euro_filter(&s_slot[slot].f_cy, cy, dt_s,
                                      FILT_CENTER_MIN_CUTOFF, FILT_CENTER_BETA, FILT_D_CUTOFF);
            hand_sz = one_euro_filter(&s_slot[slot].f_size, hand_sz, dt_s,
                                      FILT_SIZE_MIN_CUTOFF, FILT_SIZE_BETA, FILT_D_CUTOFF);

            s_slot[slot].cx = cx;
            s_slot[slot].cy = cy;

            /* Out in camera pixel coords (640x480), which is what the
             * display now expects -- same contract as the landmark projects. */
            const float side = hand_sz * CAM_W_F;

            float x1 = (cx * CAM_W_F)  - (0.5f * side);
            float y1 = (cy * CAM_H_F) - (0.5f * side);
            float w  = side;
            float h  = side;

            /* Clamp */
            if (x1 < 0) x1 = 0;
            if (y1 < 0) y1 = 0;
            if (x1 + w > CAM_W_F)  w = CAM_W_F - x1;
            if (y1 + h > CAM_H_F) h = CAM_H_F - y1;

            /* A box clamped away to nothing, or pushed off the edge entirely,
             * is not something the display can show: it treats a top-left of
             * (0,0) as "no detection", and a negative extent would draw
             * inside-out. */
            if ((w <= 0.0f) || (h <= 0.0f)) continue;

            update_detection_result((uint16_t)i,
                (signed short)x1, (signed short)y1,
                (signed short)w,  (signed short)h);
        }
    }

    /* Retire slots that went unmatched for a few frames running. */
    for (int k = 0; k < AI_MAX_DETECTION_NUM; k++)
    {
        if (s_slot[k].active && !matched[k])
        {
            if (++s_slot[k].misses >= SLOT_MAX_MISSES)
            {
                palm_slot_reset(&s_slot[k]);
            }
        }
    }

    return true;
}
