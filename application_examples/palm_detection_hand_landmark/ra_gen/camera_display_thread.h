/* generated thread header file - do not edit */
#ifndef CAMERA_DISPLAY_THREAD_H_
#define CAMERA_DISPLAY_THREAD_H_
#include "bsp_api.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "hal_data.h"
#ifdef __cplusplus
                extern "C" void camera_display_thread_entry(void * pvParameters);
                #else
extern void camera_display_thread_entry(void *pvParameters);
#endif
#include "r_gpt.h"
#include "r_timer_api.h"
#include "r_iic_master.h"
#include "r_i2c_master_api.h"
FSP_HEADER
/** Timer on GPT Instance. */
extern const timer_instance_t g_cam_clk;

/** Access the GPT instance using these structures when calling API functions directly (::p_api is not used). */
extern gpt_instance_ctrl_t g_cam_clk_ctrl;
extern const timer_cfg_t g_cam_clk_cfg;

#ifndef NULL
void NULL(timer_callback_args_t *p_args);
#endif
/* I2C Master on IIC Instance. */
extern const i2c_master_instance_t g_cam_i2c_master;

/** Access the I2C Master instance using these structures when calling API functions directly (::p_api is not used). */
extern iic_master_instance_ctrl_t g_cam_i2c_master_ctrl;
extern const i2c_master_cfg_t g_cam_i2c_master_cfg;

#ifndef g_cam_i2c_master_user_callback
void g_cam_i2c_master_user_callback(i2c_master_callback_args_t *p_args);
#endif
FSP_FOOTER
#endif /* CAMERA_DISPLAY_THREAD_H_ */
