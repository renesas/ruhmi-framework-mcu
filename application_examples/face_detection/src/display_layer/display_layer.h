/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/**********************************************************************************************************************
 * File Name    : dsi_layer.h
 * Version      : .
 * Description  : .
 *********************************************************************************************************************/
#ifndef __DSI_LAYER_H__
#define __DSI_LAYER_H__

#include "hal_data.h"

extern d2_device * d2_handle;

#define REGFLAG_DELAY        0xFE
#define REGFLAG_END_OF_TABLE 0xFD

typedef struct {
    unsigned char size;
    unsigned char buffer[10];
    uint8_t cmd_id;
    uint8_t flags;
} LCD_setting_table;

extern LCD_setting_table lcd_init_focuslcd[];

FSP_CPP_HEADER
fsp_err_t drw_init(void);
fsp_err_t display_init(void);
void display_image_buffer_initialize(void);
void graphics_start_frame(void);
void graphics_end_frame(void);
uint32_t graphics_backup_buffer_pointer_get(void);
void graphics_swap_buffer(void);
FSP_CPP_FOOTER

#endif /*__DSI_LAYER_H__*/
