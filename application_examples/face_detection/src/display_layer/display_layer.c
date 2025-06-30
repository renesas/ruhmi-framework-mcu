/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/**********************************************************************************************************************
 * File Name    : dsi_layer.c
 * Version      : .
 * Description  : .
 *********************************************************************************************************************/
#include "hal_data.h"
#include "display_layer.h"
#include "common_util.h"

#include "time_counter.h"

#include "display_layer_config.h"

static uint8_t drw_buf = 1;

FSP_CPP_HEADER
static fsp_err_t fill_w_color_rgb565(uint8_t * buff,
                                     uint32_t screen_w, uint32_t screen_h,
                                     uint32_t write_area_w_start, uint32_t write_area_h_start,
                                     uint32_t write_area_w, uint32_t write_area_h,
                                     uint16_t color);
FSP_CPP_FOOTER

fsp_err_t drw_init(void)
{
    /* Initialize D/AVE 2D driver */
     d2_handle = d2_opendevice(0);
     d2_inithw(d2_handle, 0);

     /* Clear both buffers */
     d2_framebuffer(d2_handle, fb_background, DISPLAY_SCREEN_WIDTH, DISPLAY_SCREEN_WIDTH, DISPLAY_SCREEN_HEIGHT * DISPLAY_SCREEN_BUFF_NUMBER, DISPLAY_SCREEN_BUFF_D2_COLOR_CODE);
     d2_clear(d2_handle, 0x00000000);

     /* Set various D2 parameters */
     d2_setblendmode(d2_handle, d2_bm_alpha, d2_bm_one_minus_alpha);
     d2_setalphamode(d2_handle, d2_am_constant);
     d2_setalpha(d2_handle, 0xff);
     d2_setantialiasing(d2_handle, 1);
     d2_setlinecap(d2_handle, d2_lc_butt);
     d2_setlinejoin(d2_handle, d2_lj_none);

     return FSP_SUCCESS;
}

fsp_err_t display_init(void)
{
    fsp_err_t fsp_status = FSP_SUCCESS;

    /* Reset Display - active low */
    /* Note: Please update wait periods according to LCD controller specification */
    R_IOPORT_PinWrite(&g_ioport_ctrl, LCD_RST, BSP_IO_LEVEL_LOW);
    R_BSP_SoftwareDelay(10, BSP_DELAY_UNITS_MICROSECONDS);
    R_IOPORT_PinWrite(&g_ioport_ctrl, LCD_RST, BSP_IO_LEVEL_HIGH);
    R_BSP_SoftwareDelay(120, BSP_DELAY_UNITS_MILLISECONDS);

    /* open MIPI DSI Interface */
    fsp_status = R_GLCDC_Open(&g_lcd_glcdc_ctrl, &g_lcd_glcdc_cfg);
    if (FSP_SUCCESS != fsp_status)
    {
        ERROR_INDICATE;
    }

    /* NOTE: cannot send commands for 5 ms after HW reset */
    R_BSP_SoftwareDelay(5, BSP_DELAY_UNITS_MILLISECONDS);

    /* Note: When video is started, timing of any further messages must carefully controlled to not interfere with transmission. */
    fsp_status = R_GLCDC_Start(&g_lcd_glcdc_ctrl);
    if (FSP_SUCCESS != fsp_status)
    {
        ERROR_INDICATE;
    }

    /* Wait for the LCD to display valid data */
    /* Note: Please update wait periods according to LCD controller specification */
    R_BSP_SoftwareDelay(200, BSP_DELAY_UNITS_MILLISECONDS);

    /* Switch GLCDC display buffer */
    R_GLCDC_BufferChange(&g_lcd_glcdc_ctrl, &fb_background[0][0], DISPLAY_FRAME_LAYER_1);

    /* Enable the back light */
    R_IOPORT_PinWrite(&g_ioport_ctrl, LCD_BLEN, BSP_IO_LEVEL_HIGH);

    return FSP_SUCCESS;
}

void display_image_buffer_initialize(void)
{
#if 1
    /* Clear the buffer with 0x0 (black) */
    memset(&fb_background[0][0], 0x0, sizeof(fb_background)/2);
    memset(&fb_background[1][0], 0x0, sizeof(fb_background)/2);
#endif
#if 0
    /* Fill with Renesas blue */
    fill_w_color_rgb565(&fb_background[0][0], DISPLAY_HSIZE_INPUT0, DISPLAY_VSIZE_INPUT0,   0,   0, DISPLAY_HSIZE_INPUT0, DISPLAY_VSIZE_INPUT0, 0x2953); // Renesas blue
    fill_w_color_rgb565(&fb_background[1][0], DISPLAY_HSIZE_INPUT0, DISPLAY_VSIZE_INPUT0,   0,   0, DISPLAY_HSIZE_INPUT0, DISPLAY_VSIZE_INPUT0, 0x2953); // Renesas blue
#endif
#if 0
    /* Fill with color bar */
    fill_w_color_rgb565(&fb_background[0][0], DISPLAY_HSIZE_INPUT0, DISPLAY_VSIZE_INPUT0, (DISPLAY_HSIZE_INPUT0/8)*0, 0, (DISPLAY_HSIZE_INPUT0/8), DISPLAY_VSIZE_INPUT0, 0xF800); // Red
    fill_w_color_rgb565(&fb_background[0][0], DISPLAY_HSIZE_INPUT0, DISPLAY_VSIZE_INPUT0, (DISPLAY_HSIZE_INPUT0/8)*1, 0, (DISPLAY_HSIZE_INPUT0/8), DISPLAY_VSIZE_INPUT0, 0x07E0); // Green
    fill_w_color_rgb565(&fb_background[0][0], DISPLAY_HSIZE_INPUT0, DISPLAY_VSIZE_INPUT0, (DISPLAY_HSIZE_INPUT0/8)*2, 0, (DISPLAY_HSIZE_INPUT0/8), DISPLAY_VSIZE_INPUT0, 0x001F); // Blue
    fill_w_color_rgb565(&fb_background[0][0], DISPLAY_HSIZE_INPUT0, DISPLAY_VSIZE_INPUT0, (DISPLAY_HSIZE_INPUT0/8)*3, 0, (DISPLAY_HSIZE_INPUT0/8), DISPLAY_VSIZE_INPUT0, 0xFFE0); // Yellow
    fill_w_color_rgb565(&fb_background[0][0], DISPLAY_HSIZE_INPUT0, DISPLAY_VSIZE_INPUT0, (DISPLAY_HSIZE_INPUT0/8)*4, 0, (DISPLAY_HSIZE_INPUT0/8), DISPLAY_VSIZE_INPUT0, 0x780F); // Purple
    fill_w_color_rgb565(&fb_background[0][0], DISPLAY_HSIZE_INPUT0, DISPLAY_VSIZE_INPUT0, (DISPLAY_HSIZE_INPUT0/8)*5, 0, (DISPLAY_HSIZE_INPUT0/8), DISPLAY_VSIZE_INPUT0, 0x07FF); // Cyan
    fill_w_color_rgb565(&fb_background[0][0], DISPLAY_HSIZE_INPUT0, DISPLAY_VSIZE_INPUT0, (DISPLAY_HSIZE_INPUT0/8)*6, 0, (DISPLAY_HSIZE_INPUT0/8), DISPLAY_VSIZE_INPUT0, 0x0000); // Write
    fill_w_color_rgb565(&fb_background[0][0], DISPLAY_HSIZE_INPUT0, DISPLAY_VSIZE_INPUT0, (DISPLAY_HSIZE_INPUT0/8)*7, 0, (DISPLAY_HSIZE_INPUT0/8), DISPLAY_VSIZE_INPUT0, 0xFFFF); // Black

    fill_w_color_rgb565(&fb_background[1][0], DISPLAY_HSIZE_INPUT0, DISPLAY_VSIZE_INPUT0, 0, (DISPLAY_VSIZE_INPUT0/8)*0, DISPLAY_HSIZE_INPUT0, (DISPLAY_VSIZE_INPUT0/8), 0xF800); // Red
    fill_w_color_rgb565(&fb_background[1][0], DISPLAY_HSIZE_INPUT0, DISPLAY_VSIZE_INPUT0, 0, (DISPLAY_VSIZE_INPUT0/8)*1, DISPLAY_HSIZE_INPUT0, (DISPLAY_VSIZE_INPUT0/8), 0x07E0); // Green
    fill_w_color_rgb565(&fb_background[1][0], DISPLAY_HSIZE_INPUT0, DISPLAY_VSIZE_INPUT0, 0, (DISPLAY_VSIZE_INPUT0/8)*2, DISPLAY_HSIZE_INPUT0, (DISPLAY_VSIZE_INPUT0/8), 0x001F); // Blue
    fill_w_color_rgb565(&fb_background[1][0], DISPLAY_HSIZE_INPUT0, DISPLAY_VSIZE_INPUT0, 0, (DISPLAY_VSIZE_INPUT0/8)*3, DISPLAY_HSIZE_INPUT0, (DISPLAY_VSIZE_INPUT0/8), 0xFFE0); // Yellow
    fill_w_color_rgb565(&fb_background[1][0], DISPLAY_HSIZE_INPUT0, DISPLAY_VSIZE_INPUT0, 0, (DISPLAY_VSIZE_INPUT0/8)*4, DISPLAY_HSIZE_INPUT0, (DISPLAY_VSIZE_INPUT0/8), 0x780F); // Purple
    fill_w_color_rgb565(&fb_background[1][0], DISPLAY_HSIZE_INPUT0, DISPLAY_VSIZE_INPUT0, 0, (DISPLAY_VSIZE_INPUT0/8)*5, DISPLAY_HSIZE_INPUT0, (DISPLAY_VSIZE_INPUT0/8), 0x07FF); // Cyan
    fill_w_color_rgb565(&fb_background[1][0], DISPLAY_HSIZE_INPUT0, DISPLAY_VSIZE_INPUT0, 0, (DISPLAY_VSIZE_INPUT0/8)*6, DISPLAY_HSIZE_INPUT0, (DISPLAY_VSIZE_INPUT0/8), 0x0000); // Write
    fill_w_color_rgb565(&fb_background[1][0], DISPLAY_HSIZE_INPUT0, DISPLAY_VSIZE_INPUT0, 0, (DISPLAY_VSIZE_INPUT0/8)*7, DISPLAY_HSIZE_INPUT0, (DISPLAY_VSIZE_INPUT0/8), 0xFFFF); // Black
#endif
}

fsp_err_t fill_w_color_rgb565(uint8_t * buff,
                              uint32_t screen_w, uint32_t screen_h,
                              uint32_t write_area_w_start, uint32_t write_area_h_start,
                              uint32_t write_area_w, uint32_t write_area_h,
                              uint16_t color)
{
    if(screen_w < write_area_w_start)
    {
        return FSP_ERR_INVALID_ARGUMENT;
    }

    if(screen_w < write_area_w_start + write_area_w)
    {
        return FSP_ERR_INVALID_ARGUMENT;
    }

    if(screen_h < write_area_h_start)
    {
        return FSP_ERR_INVALID_ARGUMENT;
    }

    if(screen_h < write_area_h_start + write_area_h)
    {
        return FSP_ERR_INVALID_ARGUMENT;
    }

    uint16_t * buff_start_address = (uint16_t *) buff;

    for(uint32_t i=write_area_h_start; i<write_area_h_start+write_area_h; i++)
    {
        for(uint32_t j=write_area_w_start; j< write_area_w_start+write_area_w; j++)
        {
            *(buff_start_address + (i * screen_w) + j) = color;
        }
    }

    return FSP_SUCCESS;
}

#define DIM_FRAME_COUNT_LIMIT (120)
static uint8_t g_draw_count = 0;

static uint32_t last_lcd_glcdc_frame_end = 0;

void lcd_glcdc_callback(display_callback_args_t *p_args)
{
    FSP_PARAMETER_NOT_USED(p_args);

    BaseType_t xHigherPriorityTaskWoken, xResult;
    /* xHigherPriorityTaskWoken must be initialised to pdFALSE. */
    xHigherPriorityTaskWoken = pdFALSE;
    if (DISPLAY_EVENT_LINE_DETECTION & p_args->event )
    {
        application_processing_time.lcd_display_update_refresh_ms = TimeCounter_CountValueConvertToMs(last_lcd_glcdc_frame_end, TimeCounter_CurrentCountGet());
        last_lcd_glcdc_frame_end = TimeCounter_CurrentCountGet();

        /* Set GLCDC VSYNC flag */
        xResult = xEventGroupSetBitsFromISR(g_ai_app_event, GLCDC_VSYNC, &xHigherPriorityTaskWoken);
        if( xResult != pdFAIL )
        {
            /* If xHigherPriorityTaskWoken is now set to pdTRUE then a context
              switch should be requested.  The macro used is port specific and will
              be either portYIELD_FROM_ISR() or portEND_SWITCHING_ISR() - refer to
              the documentation page for the port being used. */
            portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
        }
    }

    /* wait for 120 v sync cycles before enable mipi backlight */
    if(g_draw_count < DIM_FRAME_COUNT_LIMIT)
    {
        g_draw_count++;
        if(g_draw_count == DIM_FRAME_COUNT_LIMIT)
        {
//            mipi_dsi_enable_backlight();
        }
    }
}

/*********************************************************************************************************************
 *  System uses double buffer. Swap the current buffer.
 *  @param[IN]   None
 *  @retval      None
***********************************************************************************************************************/
void graphics_swap_buffer()
{
    drw_buf = (drw_buf == 0) ? 1 : 0;

    /* Update the layer to display in the GLCDC (will be set on next Vsync) */
    R_GLCDC_BufferChange(g_lcd_glcdc.p_ctrl, fb_background[drw_buf], DISPLAY_FRAME_LAYER_1);
}

/*********************************************************************************************************************
 *  Get pointer address of backup buffer
 *  @param[IN]   None
 *  @retval      None
***********************************************************************************************************************/
uint32_t graphics_backup_buffer_pointer_get(void)
{
    uint8_t backup_buffer = (drw_buf == 0) ? 1 : 0;

    return (uint32_t)&fb_background[backup_buffer][0];
}

/*********************************************************************************************************************
 *  Start a new frame with the current draw buffer.
 *  @param[IN]   None
 *  @retval      None
***********************************************************************************************************************/
void graphics_start_frame()
{
    /* Start a new display list */
    d2_startframe(d2_handle);

    /* Set the new buffer to the current draw buffer */
    d2_framebuffer(d2_handle, &(fb_background[drw_buf][0]), DISPLAY_SCREEN_WIDTH, DISPLAY_SCREEN_WIDTH, DISPLAY_SCREEN_HEIGHT, DISPLAY_SCREEN_BUFF_D2_COLOR_CODE);
}

/*********************************************************************************************************************
 *  Wait the current frame to end and swap the framebuffer
 *  @param[IN]   None
 *  @retval      None
***********************************************************************************************************************/
void graphics_end_frame()
{
    /* End the current display list */
    d2_endframe(d2_handle);

    /* Flip the framebuffer */
    graphics_swap_buffer();

}
