/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/**********************************************************************************************************************
 * File Name    : console_output.c
 * Description  : This file defines the jlink console implementations.
 **********************************************************************************************************************/
#include "hal_data.h"
#include "common_data.h"

#include <stdio.h>
#include <string.h>

#include "common_util.h"
#include "console_output.h"
#include "console_output_config.h"

/***************************************************************************************************************************
 * Macro definitions
 ***************************************************************************************************************************/
#if (CONSOLE_OUTPUT_TYPE == 0)
#include "SEGGER_RTT/SEGGER_RTT.h"
#endif

/***************************************************************************************************************************
 * Typedef definitions
 ***************************************************************************************************************************/
/***************************************************************************************************************************
 * Imported global variables and functions (from other files)
 ***************************************************************************************************************************/
/***************************************************************************************************************************
 * Exported global variables and functions (to be accessed by other files)
 ***************************************************************************************************************************/
char sprintf_buffer[BUFFER_LINE_LENGTH] = {};
/***************************************************************************************************************************
 * Private global variables and functions
 ***************************************************************************************************************************/
static uint8_t s_rx_buf;

#if (CONSOLE_OUTPUT_TYPE == 1)
static uint8_t  g_out_of_band_received[BUFFER_LINE_LENGTH];
static uint32_t g_out_of_band_index = 0;
static volatile uint32_t g_transfer_complete = 0;
static volatile uint32_t g_receive_complete  = 0;
#endif

static fsp_err_t console_output_write(const char *buffer);
static bool key_pressed(void);
static uint8_t get_detected_key(void);

/*********************************************************************************************************************
 *  Initialize the SCI UART
 *  @param[IN]   None
 *  @retval      None
***********************************************************************************************************************/

fsp_err_t console_output_init (void)
{
    fsp_err_t fsp_err = FSP_SUCCESS;

#if (CONSOLE_OUTPUT_TYPE == 0)
    SEGGER_RTT_Init();
#elif (CONSOLE_OUTPUT_TYPE == 1)
    fsp_err = g_console_output_uart.p_api->open(g_console_output_uart.p_ctrl, g_console_output_uart.p_cfg);
#endif

    return fsp_err;
}

/*********************************************************************************************************************
 *  Global API: Print a string buffer to Jlink console
 *  @param[IN]   None
 *  @retval      return success
***********************************************************************************************************************/
vision_ai_app_err_t print_to_console(char * p_data)
{
    fsp_err_t err = FSP_SUCCESS;
    vision_ai_app_err_t vision_ai_status = VISION_AI_APP_SUCCESS;

    err = console_output_write(p_data);
    if(FSP_SUCCESS != err)
    {
    	handle_error(VISION_AI_APP_ERR_CONSOLE_WRITE);
    	return VISION_AI_APP_ERR_CONSOLE_WRITE;
    }

    return vision_ai_status;
}

/*********************************************************************************************************************
 *  Read user input from the Jlink console
 *  @param[IN]   None
 *  @retval      return input buffer
***********************************************************************************************************************/
int8_t input_from_console (void)
{
	fsp_err_t err = FSP_SUCCESS;

	s_rx_buf = 0;
#if (CONSOLE_OUTPUT_TYPE == 1)
	g_receive_complete = false;

	err = g_console_output_uart.p_api->read(g_console_output_uart.p_ctrl, &s_rx_buf, 1);
	if (FSP_SUCCESS != err)
    {
    	handle_error(VISION_AI_APP_ERR_CONSOLE_READ);
    }
#endif

    while(key_pressed() == false)
    {
        vTaskDelay(1);
    }

    return ((int8_t)get_detected_key());
}

/*********************************************************************************************************************
 *  Local function: write a string over the JLink console
 *  @param[IN]   buffer: string buffer
 *  @retval      None
***********************************************************************************************************************/
static fsp_err_t console_output_write(const char *buffer)
{
    fsp_err_t err = FSP_SUCCESS;

#if (CONSOLE_OUTPUT_TYPE == 0)
    SEGGER_RTT_Write(0, (uint8_t *)buffer, strlen(buffer));
#elif (CONSOLE_OUTPUT_TYPE == 1)
    g_transfer_complete = false;

    err = g_console_output_uart.p_api->write(g_console_output_uart.p_ctrl, (uint8_t *)buffer, strlen(buffer));
    if (FSP_SUCCESS != err)
    {
    	handle_error(VISION_AI_APP_ERR_CONSOLE_WRITE);
    	APP_ERROR_TRAP(VISION_AI_APP_ERR_CONSOLE_WRITE);
    }

    while (!g_transfer_complete)
    {
#if (BSP_CFG_RTOS == 2) // FreeRTOS
        vTaskDelay(1);
#endif
    }
#endif

    return err;
}

/*********************************************************************************************************************
 *  Get key pressed
 *  @param[IN]   None
 *  @retval      uint8_t: key ascii
***********************************************************************************************************************/
uint8_t get_detected_key(void)
{
#if (CONSOLE_OUTPUT_TYPE == 0)
    SEGGER_RTT_Read(0, &s_rx_buf, sizeof(s_rx_buf));
    return (s_rx_buf);
#elif (CONSOLE_OUTPUT_TYPE == 1)
    return (s_rx_buf);
#endif
}


static bool key_pressed(void)
{
#if (CONSOLE_OUTPUT_TYPE == 0)
    return (SEGGER_RTT_HasKey());
#elif (CONSOLE_OUTPUT_TYPE == 1)
    return (g_receive_complete);
#endif
}

#if (CONSOLE_OUTPUT_TYPE == 1)
/*********************************************************************************************************************
 *  Console console callback
 *  @param[IN]   uart_callback_args_t *p_args: callback information
 *  @retval      None
***********************************************************************************************************************/
void console_output_uart_callback(uart_callback_args_t *p_args)
{
    /* Handle the UART event */
    switch (p_args->event)
    {
        /* Received a character */
        case UART_EVENT_RX_CHAR:
        {
            /* Only put the next character in the receive buffer if there is space for it */
            if (sizeof(g_out_of_band_received) > g_out_of_band_index)
            {
                /* Write either the next one or two bytes depending on the receive data size */
                if (UART_DATA_BITS_8 >= g_console_output_uart_cfg.data_bits)
                {
                    g_out_of_band_received[g_out_of_band_index++] = (uint8_t) p_args->data;
                }
                else
                {
                    uint16_t * p_dest = (uint16_t *) &g_out_of_band_received[g_out_of_band_index];
                    *p_dest              = (uint16_t) p_args->data;
                    g_out_of_band_index += 2;
                }
            }
            break;
        }
        /* Receive complete */
        case UART_EVENT_RX_COMPLETE:
        {
            g_receive_complete = 1;
            break;
        }
        /* Transmit complete */
        case UART_EVENT_TX_COMPLETE:
        {
            g_transfer_complete = 1;
            break;
        }
        default:
        {
            /* Do nothing */
        }
    }
}
#endif
