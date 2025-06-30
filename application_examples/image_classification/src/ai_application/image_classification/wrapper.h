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
#ifndef MODEL_WRAPPER_H
#define MODEL_WRAPPER_H

#include "mera/model.h"
#include <stdint.h>
#include <stdbool.h>

static inline uint8_t* mera_input_ptr() {
    return (uint8_t*) GetModelInputPtr_serving_default_input_1_0();
}

static inline uint8_t* mera_output_ptr() {
    return (uint8_t*) GetModelOutputPtr_StatefulPartitionedCall_0_70098();
}

static inline void mera_invoke() {
//    memcpy(mera_input_ptr(), model_image_input, model_image_input_SIZE);
    RunModel(false);
}

#endif // MODEL_WRAPPER_H
