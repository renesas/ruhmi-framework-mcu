#ifndef MODEL_WRAPPER_H
#define MODEL_WRAPPER_H

#include "model.h"
#include "model_io_data.h"
#include <stdint.h>

static inline uint8_t* mera_input_ptr() {
    return (uint8_t*) GetModelInputPtr_image_input();
}

static inline uint8_t* mera_output1_ptr() {
    return (uint8_t*) GetModelOutputPtr_Identity_70275();
}

static inline uint8_t* mera_output2_ptr() {
    return (uint8_t*) GetModelOutputPtr_Identity_1_70284();
}

static inline void mera_invoke() {
//    memcpy(mera_input_ptr(), model_image_input, model_image_input_SIZE);
    RunModel(false);
}

#endif // MODEL_WRAPPER_H
