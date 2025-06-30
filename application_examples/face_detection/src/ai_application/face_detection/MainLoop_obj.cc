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
    // Allocate and set quantization parameters on the stack
    static TfLiteAffineQuantization quantization;  // Static to avoid malloc
    static TfLiteFloatArray scale_array;           // Static to avoid malloc
    static TfLiteIntArray zero_point_array;       // Static to avoid malloc

    // Set scale
    scale_array.size = 1;
    scale_array.data[0] = scale;
    quantization.scale = &scale_array;

    // Set zero point
    zero_point_array.size = 1;
    zero_point_array.data[0] = zero_point;
    quantization.zero_point = &zero_point_array;

    quantization.quantized_dimension = 0;  // Per-tensor quantization

    tensor->quantization.type = kTfLiteAffineQuantization;
    tensor->quantization.params = &quantization;

    // Set allocation type
    tensor->allocation_type = kTfLiteArenaRw;

    // Set other fields
    tensor->is_variable = false;
}

static bool PresentInferenceResult(const std::vector<arm::app::object_detection::DetectionResult>& results)
{
    for (uint16_t i = 0; i < AI_MAX_DETECTION_NUM; i++)
    {
        update_detection_result(i, (signed short)0, (signed short)0, (signed short)0, (signed short)0);
    }

    for (uint16_t i = 0; i < results.size(); ++i) {
        update_detection_result(i, (signed short)results[i].m_x0, (signed short)results[i].m_y0, (signed short)results[i].m_w, (signed short)results[i].m_h );
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
    memcpy(mera_input_ptr(), model_buffer_int8, IMAGE_DATA_SIZE);
    /* Run inference over this image. */
    volatile uint32_t old_counter =  TimeCounter_CurrentCountGet();
    mera_invoke();
    volatile uint32_t new_counter = TimeCounter_CurrentCountGet();
    volatile uint32_t diff = new_counter - old_counter;
    application_processing_time.ai_inference_time_ms = TimeCounter_CountValueConvertToMs(old_counter, new_counter);

    int8_t* output0 = (int8_t*)mera_output1_ptr();
    int8_t* output1 = (int8_t*)mera_output2_ptr();

    std::vector<arm::app::object_detection::DetectionResult> results;
    arm::app::object_detection::PostProcessParams postProcessParams {
        AI_INPUT_IMAGE_HEIGHT, AI_INPUT_IMAGE_WIDTH, AI_INPUT_IMAGE_WIDTH, anchor1, anchor2
    };
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
