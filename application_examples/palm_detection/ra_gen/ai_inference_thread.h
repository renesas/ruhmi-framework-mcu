/* generated thread header file - do not edit */
#ifndef AI_INFERENCE_THREAD_H_
#define AI_INFERENCE_THREAD_H_
#include "bsp_api.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "hal_data.h"
#ifdef __cplusplus
                extern "C" void ai_inference_thread_entry(void * pvParameters);
                #else
extern void ai_inference_thread_entry(void *pvParameters);
#endif
FSP_HEADER
FSP_FOOTER
#endif /* AI_INFERENCE_THREAD_H_ */
