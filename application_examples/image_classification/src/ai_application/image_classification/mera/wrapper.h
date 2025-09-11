#ifndef MODEL_WRAPPER_H
#define MODEL_WRAPPER_H

#include "model.h"
#include "model_io_data.h"
#include <stdint.h>
#include <stdbool.h>

static inline uint8_t* mera_input_ptr() {
    return (uint8_t*) GetModelInputPtr_serving_default_input_1_0();
}

static inline uint8_t* mera_output_ptr() {
    return (uint8_t*) GetModelOutputPtr_StatefulPartitionedCall_0_70098();
}

static inline uint64_t mera_input_size() {
    return 150528;
}

static inline uint64_t mera_output_size() {
    return 1000;
}

static inline uint8_t* mera_sample_input_ptr() {
    return (uint8_t*) model_serving_default_input_1_0;
}

static inline uint8_t* mera_sample_output_ptr() {
    return (uint8_t*) model_StatefulPartitionedCall_0;
}


static inline void mera_invoke() {
//    memcpy(mera_input_ptr(), model_image_input, model_image_input_SIZE);
    RunModel(false);
}

#endif // MODEL_WRAPPER_H
