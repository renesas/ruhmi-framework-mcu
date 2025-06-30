/* generated common header file - do not edit */
#ifndef COMMON_DATA_H_
#define COMMON_DATA_H_
#include <stdint.h>
#include "bsp_api.h"
#include "FreeRTOS.h"
#include "event_groups.h"
#include "arm_math.h"
#include "arm_nnfunctions.h"
#include "rm_ethosu_api.h"
#include "rm_ethosu.h"
#include "r_glcdc.h"
#include "r_display_api.h"
#include "dave_driver.h"
#include "r_icu.h"
#include "r_external_irq_api.h"
#include "r_ioport.h"
#include "bsp_pin_cfg.h"
FSP_HEADER
#include "ethosu_driver.h"
extern struct ethosu_driver g_ethosu0;
extern rm_ethosu_instance_ctrl_t g_rm_ethosu0_ctrl;
extern const rm_ethosu_cfg_t g_rm_ethosu0_cfg;
extern const rm_ethosu_instance_t g_rm_ethosu0;
#ifndef NULL
void NULL(rm_ethosu_callback_args_t *p_arg);
#endif
#define GLCDC_CFG_LAYER_1_ENABLE (true)
#define GLCDC_CFG_LAYER_2_ENABLE (false)

#define GLCDC_CFG_CLUT_ENABLE (false)

#define GLCDC_CFG_CORRECTION_GAMMA_ENABLE_R       (false)
#define GLCDC_CFG_CORRECTION_GAMMA_ENABLE_G       (false)
#define GLCDC_CFG_CORRECTION_GAMMA_ENABLE_B       (false)

/* Display on GLCDC Instance. */
extern const display_instance_t g_lcd_glcdc;
extern display_runtime_cfg_t g_lcd_glcdc_runtime_cfg_fg;
extern display_runtime_cfg_t g_lcd_glcdc_runtime_cfg_bg;

/** Access the GLCDC instance using these structures when calling API functions directly (::p_api is not used). */
extern glcdc_instance_ctrl_t g_lcd_glcdc_ctrl;
extern const display_cfg_t g_lcd_glcdc_cfg;

#if ((GLCDC_CFG_CORRECTION_GAMMA_ENABLE_R | GLCDC_CFG_CORRECTION_GAMMA_ENABLE_G | GLCDC_CFG_CORRECTION_GAMMA_ENABLE_B) && GLCDC_CFG_COLOR_CORRECTION_ENABLE && !(false))
            extern display_gamma_correction_t g_lcd_glcdc_gamma_cfg;
            #endif

#if GLCDC_CFG_CLUT_ENABLE
            extern display_clut_cfg_t g_lcd_glcdc_clut_cfg_glcdc;
            #endif

#ifndef lcd_glcdc_callback
void lcd_glcdc_callback(display_callback_args_t *p_args);
#endif

#define DISPLAY_IN_FORMAT_16BITS_RGB565_0
#if defined (DISPLAY_IN_FORMAT_32BITS_RGB888_0) || defined (DISPLAY_IN_FORMAT_32BITS_ARGB8888_0)
            #define DISPLAY_BITS_PER_PIXEL_INPUT0 (32)
            #elif defined (DISPLAY_IN_FORMAT_16BITS_RGB565_0) || defined (DISPLAY_IN_FORMAT_16BITS_ARGB1555_0) || defined (DISPLAY_IN_FORMAT_16BITS_ARGB4444_0)
#define DISPLAY_BITS_PER_PIXEL_INPUT0 (16)
#elif defined (DISPLAY_IN_FORMAT_CLUT8_0)
            #define DISPLAY_BITS_PER_PIXEL_INPUT0 (8)
            #elif defined (DISPLAY_IN_FORMAT_CLUT4_0)
            #define DISPLAY_BITS_PER_PIXEL_INPUT0 (4)
            #else
            #define DISPLAY_BITS_PER_PIXEL_INPUT0 (1)
            #endif
#define DISPLAY_HSIZE_INPUT0                 (1024)
#define DISPLAY_VSIZE_INPUT0                 (600)
#define DISPLAY_BUFFER_STRIDE_BYTES_INPUT0   (((DISPLAY_HSIZE_INPUT0 * DISPLAY_BITS_PER_PIXEL_INPUT0 + 0x1FF) >> 9) << 6)
#define DISPLAY_BUFFER_STRIDE_PIXELS_INPUT0  ((DISPLAY_BUFFER_STRIDE_BYTES_INPUT0 * 8) / DISPLAY_BITS_PER_PIXEL_INPUT0)
#if GLCDC_CFG_LAYER_1_ENABLE
            extern uint8_t fb_background[2][DISPLAY_BUFFER_STRIDE_BYTES_INPUT0 * DISPLAY_VSIZE_INPUT0];
            #endif

#define DISPLAY_IN_FORMAT_16BITS_RGB565_1
#if defined (DISPLAY_IN_FORMAT_32BITS_RGB888_1) || defined (DISPLAY_IN_FORMAT_32BITS_ARGB8888_1)
            #define DISPLAY_BITS_PER_PIXEL_INPUT1 (32)
            #elif defined (DISPLAY_IN_FORMAT_16BITS_RGB565_1) || defined (DISPLAY_IN_FORMAT_16BITS_ARGB1555_1) || defined (DISPLAY_IN_FORMAT_16BITS_ARGB4444_1)
#define DISPLAY_BITS_PER_PIXEL_INPUT1 (16)
#elif defined (DISPLAY_IN_FORMAT_CLUT8_1)
            #define DISPLAY_BITS_PER_PIXEL_INPUT1 (8)
            #elif defined (DISPLAY_IN_FORMAT_CLUT4_1)
            #define DISPLAY_BITS_PER_PIXEL_INPUT1 (4)
            #else
            #define DISPLAY_BITS_PER_PIXEL_INPUT1 (1)
            #endif
#define DISPLAY_HSIZE_INPUT1                 (320)
#define DISPLAY_VSIZE_INPUT1                 (600)
#define DISPLAY_BUFFER_STRIDE_BYTES_INPUT1   (((DISPLAY_HSIZE_INPUT1 * DISPLAY_BITS_PER_PIXEL_INPUT1 + 0x1FF) >> 9) << 6)
#define DISPLAY_BUFFER_STRIDE_PIXELS_INPUT1  ((DISPLAY_BUFFER_STRIDE_BYTES_INPUT1 * 8) / DISPLAY_BITS_PER_PIXEL_INPUT1)
#if GLCDC_CFG_LAYER_2_ENABLE
            extern uint8_t fb_foreground[1][DISPLAY_BUFFER_STRIDE_BYTES_INPUT1 * DISPLAY_VSIZE_INPUT1];
            #endif
#if DRW_CFG_CUSTOM_MALLOC
            void * d1_malloc(size_t size);
            void   d1_free(void * ptr);
            #endif
/** External IRQ on ICU Instance. */
extern const external_irq_instance_t g_external_irq_sw2;

/** Access the ICU instance using these structures when calling API functions directly (::p_api is not used). */
extern icu_instance_ctrl_t g_external_irq_sw2_ctrl;
extern const external_irq_cfg_t g_external_irq_sw2_cfg;

#ifndef external_irq_sw2_cb
void external_irq_sw2_cb(external_irq_callback_args_t *p_args);
#endif
/** External IRQ on ICU Instance. */
extern const external_irq_instance_t g_external_irq_sw1;

/** Access the ICU instance using these structures when calling API functions directly (::p_api is not used). */
extern icu_instance_ctrl_t g_external_irq_sw1_ctrl;
extern const external_irq_cfg_t g_external_irq_sw1_cfg;

#ifndef external_irq_sw1_cb
void external_irq_sw1_cb(external_irq_callback_args_t *p_args);
#endif
#define IOPORT_CFG_NAME g_bsp_pin_cfg
#define IOPORT_CFG_OPEN R_IOPORT_Open
#define IOPORT_CFG_CTRL g_ioport_ctrl

/* IOPORT Instance */
extern const ioport_instance_t g_ioport;

/* IOPORT control structure. */
extern ioport_instance_ctrl_t g_ioport_ctrl;
extern EventGroupHandle_t g_ai_app_event;
void g_common_init(void);
FSP_FOOTER
#endif /* COMMON_DATA_H_ */
