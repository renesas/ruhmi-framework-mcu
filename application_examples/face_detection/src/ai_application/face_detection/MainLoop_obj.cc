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
#include "DetectorPostProcessing.hpp"
#include "DetectionResult.hpp"

extern "C" {
#include "time_counter.h"
#include "wrapper.h"
void update_detection_result(uint16_t index, signed short  x, signed short  y, signed short  w, signed short  h);
}

#define IMAGE_DATA_SIZE  (AI_INPUT_IMAGE_WIDTH * AI_INPUT_IMAGE_HEIGHT * AI_INPUT_IMAGE_BYTE_PER_PIXEL)
extern int8_t model_buffer_int8[IMAGE_DATA_SIZE];

int CompareOutput(const uint8_t* reference, const uint8_t* actual_output, const uint64_t size_in_elements, const float epsilon) {
    int mismatches = 0;
    for (uint32_t i = 0; i < size_in_elements; i += 1) {
        float diff = (actual_output[i] - reference[i]);
        if (diff > epsilon) {
            mismatches += 1;
        }
    }
    return mismatches;
}
const float anchor1[] = {38, 77, 47, 97, 61, 126};
const float anchor2[] = {14, 26, 19, 37, 28, 55 };

void create_int8_tensor(TfLiteTensor* tensor, int8_t* input_ptr, float scale, int zero_point) {
    // Set type to int8
    tensor->type = kTfLiteInt8;

    // Assign the existing input pointer
    tensor->data.int8 = input_ptr;

    // Set bytes
    tensor->bytes = 0;

    // Set dims to NULL as requested
    tensor->dims = NULL;

    /* TfLiteFloatArray/TfLiteIntArray end in a flexible array member, so a bare
     * instance reserves no storage for data[0]; and a single shared static would
     * make all tensors share one scale/zero-point. Use a small static pool with
     * real backing for one element, one slot per tensor. */
    #define Q_POOL_SIZE 4
    static struct q_slot {
        TfLiteAffineQuantization quant;
        struct { int size; float data[1]; } scale_arr;  // real storage for data[0]
        struct { int size; int   data[1]; } zp_arr;
    } q_pool[Q_POOL_SIZE];
    static unsigned q_next = 0;

    /* main_loop_face_detection() calls this twice per frame, forever, so the index
     * must wrap around (not clamp) or every call past the 4th would alias onto the
     * same slot and reintroduce cross-tensor sharing between the two live tensors. */
    struct q_slot* slot = &q_pool[q_next % Q_POOL_SIZE];
    q_next++;

    // Set scale
    slot->scale_arr.size = 1;
    slot->scale_arr.data[0] = scale;
    slot->quant.scale = (TfLiteFloatArray*)&slot->scale_arr;

    // Set zero point
    slot->zp_arr.size = 1;
    slot->zp_arr.data[0] = zero_point;
    slot->quant.zero_point = (TfLiteIntArray*)&slot->zp_arr;

    slot->quant.quantized_dimension = 0;  // Per-tensor quantization

    tensor->quantization.type = kTfLiteAffineQuantization;
    tensor->quantization.params = &slot->quant;

    // Set allocation type
    tensor->allocation_type = kTfLiteArenaRw;

    // Set other fields
    tensor->is_variable = false;
}

static bool PresentInferenceResult(const std::vector<arm::app::object_detection::DetectionResult>& results)
{
    /* Only clear slots that have no detection this frame. Calling update_detection_result()
     * with (0,0,0,0) and then immediately again with the real box (as this used to do for
     * every slot, every frame) resets that slot's smoothing filter right before writing to
     * it, so the "no previous value yet, show raw immediately" fast path fired on every
     * single frame and the dead-zone/EMA smoothing never actually got to run. */
    for (uint16_t i = 0; i < results.size() && i < AI_MAX_DETECTION_NUM; ++i) {
        update_detection_result(i, (signed short)results[i].m_x0, (signed short)results[i].m_y0, (signed short)results[i].m_w, (signed short)results[i].m_h );
    }

    for (uint16_t i = (uint16_t)results.size(); i < AI_MAX_DETECTION_NUM; i++)
    {
        update_detection_result(i, (signed short)0, (signed short)0, (signed short)0, (signed short)0);
    }

    return true;
}


/*********************************************************************************************************************
 *  main_loop_face_detection function: sets up the application context with a model object and then calls the
 *  ObjectDetectionHandler" function to perform the face detection.
 *  @param[IN]   None
 *  @retval      true	successful execution.
 *  			 false	handler call failed.
***********************************************************************************************************************/
bool main_loop_face_detection()
{
    /* Copy the AI input image to tensor arena */
    memcpy(mera_input_ptr(), model_buffer_int8, IMAGE_DATA_SIZE);

    volatile uint32_t old_counter =  TimeCounter_CurrentCountGet();

    /* Execute AI inference */
    mera_invoke();

    application_processing_time.ai_inference_time_ms = TimeCounter_CountValueConvertToMs(old_counter, TimeCounter_CurrentCountGet());

    int8_t* output0 = (int8_t*)mera_output1_ptr();
    int8_t* output1 = (int8_t*)mera_output2_ptr();

    std::vector<arm::app::object_detection::DetectionResult> results;
    arm::app::object_detection::PostProcessParams postProcessParams {
        AI_INPUT_IMAGE_HEIGHT, AI_INPUT_IMAGE_WIDTH, AI_INPUT_IMAGE_WIDTH, anchor1, anchor2
    };
    // Cap the pre-NMS candidate list to the number of boxes the app can actually display,
    // instead of letting GetNetworkBoxes() grow it unbounded (topN <= 0 means "no limit").
    postProcessParams.topN = AI_MAX_DETECTION_NUM;
    results.clear();

    TfLiteTensor outputTensor0;
    TfLiteTensor outputTensor1;

    // Need to read quatization params from tflite model (netron)
    create_int8_tensor(&outputTensor0, output0, 0.13408391177654266, 47);
    create_int8_tensor(&outputTensor1, output1, 0.18535925447940826, 10);


    arm::app::DetectorPostProcess postProcess = arm::app::DetectorPostProcess(&outputTensor0, &outputTensor1,
            results, postProcessParams);

    if (!postProcess.DoPostProcess()) {
        error("Post-processing failed.");
        return false;
    }

    if (!PresentInferenceResult(results)) {
        return false;
    }

    return true;
}
