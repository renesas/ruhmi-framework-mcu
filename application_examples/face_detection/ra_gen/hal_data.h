/* generated HAL header file - do not edit */
#ifndef HAL_DATA_H_
#define HAL_DATA_H_
#include <stdint.h>
#include "bsp_api.h"
#include "common_data.h"
#include "r_gpt.h"
#include "r_timer_api.h"
#include "r_dmac.h"
#include "r_transfer_api.h"
#include "r_ospi_b.h"
#include "r_spi_flash_api.h"
#include "r_sci_b_uart.h"
#include "r_uart_api.h"
FSP_HEADER
/** Timer on GPT Instance. */
extern const timer_instance_t g_time_counter;

/** Access the GPT instance using these structures when calling API functions directly (::p_api is not used). */
extern gpt_instance_ctrl_t g_time_counter_ctrl;
extern const timer_cfg_t g_time_counter_cfg;

#ifndef time_counter_callback
void time_counter_callback(timer_callback_args_t *p_args);
#endif
/* Transfer on DMAC Instance. */
extern const transfer_instance_t g_transfer0;

/** Access the DMAC instance using these structures when calling API functions directly (::p_api is not used). */
extern dmac_instance_ctrl_t g_transfer0_ctrl;
extern const transfer_cfg_t g_transfer0_cfg;

#ifndef NULL
void NULL(transfer_callback_args_t *p_args);
#endif
#if OSPI_B_CFG_DMAC_SUPPORT_ENABLE
    #include "r_dmac.h"
#endif
#if OSPI_CFG_DOTF_SUPPORT_ENABLE
    #include "r_sce_if.h"
#endif
extern const spi_flash_instance_t g_ospi_b;
extern ospi_b_instance_ctrl_t g_ospi_b_ctrl;
extern const spi_flash_cfg_t g_ospi_b_cfg;
/** UART on SCI Instance. */
extern const uart_instance_t g_console_output_uart;

/** Access the UART instance using these structures when calling API functions directly (::p_api is not used). */
extern sci_b_uart_instance_ctrl_t g_console_output_uart_ctrl;
extern const uart_cfg_t g_console_output_uart_cfg;
extern const sci_b_uart_extended_cfg_t g_console_output_uart_cfg_extend;

#ifndef console_output_uart_callback
void console_output_uart_callback(uart_callback_args_t *p_args);
#endif
void hal_entry(void);
void g_hal_init(void);
FSP_FOOTER
#endif /* HAL_DATA_H_ */
