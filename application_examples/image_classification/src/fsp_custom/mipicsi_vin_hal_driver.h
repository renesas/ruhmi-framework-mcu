/*
 * Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
/**********************************************************************************************************************
 * File Name    : mipicsi_vin_hal_drvier.h
 * Version      : .
 * Description  : .
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * IMPORTANT NOTICE : This version of sample project contains preliminary version of MIPI-CSI and VIN module control code.
 *                    The code is under development and can be used only for AS-IS use.
 *                    Any configuration change (for example, clock / timing setting) may cause operation failure.
 *                    Recommend to check MCU Hardware User's Manual if you need a modification.
 *                    Also the HAL driver API and its usage note are subject to change.
 *********************************************************************************************************************/
#ifndef MIPICSI_VIN_HAL_DRIVER_H__
#define MIPICSI_VIN_HAL_DRIVER_H__

#include "hal_data.h"
#include "common_data.h"

FSP_CPP_HEADER

typedef enum e_vin_event
{
    VIN_EVENT_NONE      = 0x00000000, // No event, default state
    VIN_EVENT_FOS       = 0x00000001, ///< FIFO Overflow Interrupt
    VIN_EVENT_EFS       = 0x00000002, ///< End of Frame Interrupt
    VIN_EVENT_SIS       = 0x00000004, ///< Scanline Interrupt
    VIN_EVENT_FIS       = 0x00000010, ///< Field Interrupt
    VIN_EVENT_FMS       = 0x00000020, ///< Frame Memory write completion Interrupt
    VIN_EVENT_PRCLIPHES = 0x00000100, ///< PRCLIPH Error interrupt
    VIN_EVENT_PRCLIPVES = 0x00000200, ///< PRCLIPV Error interrupt
    VIN_EVENT_ROS       = 0x00004000, ///< Response Overflow interrupt
    VIN_EVENT_ARES      = 0x00008000, ///< Axi Resp Error interrupt
    VIN_EVENT_VRS       = 0x00010000, ///< VSYNC Deasserting Detect Interrupt
    VIN_EVENT_VFS       = 0x00020000, ///< VSYNC Asserting Detect Interrupt
    VIN_EVENT_FIS2      = 0x80000000, ///< Field Interrupt Status 2
}vin_event_t;

typedef enum e_mipicsi_rx_event
{
    MIPICSI_RX_EVENT_NONE    = 0x00000000, // No event, default state
    MIPICSI_RX_EVENT_FRM0    = 0x00000001,
    MIPICSI_RX_EVENT_FRM1    = 0x00000002,
    MIPICSI_RX_EVENT_FRM2    = 0000000004,
    MIPICSI_RX_EVENT_FRM3    = 0x00000008,
    MIPICSI_RX_EVENT_FRM4    = 0x00000010,
    MIPICSI_RX_EVENT_FRM5    = 0x00000020,
    MIPICSI_RX_EVENT_FRM6    = 0x00000040,
    MIPICSI_RX_EVENT_FRM7    = 0x00000080,
    MIPICSI_RX_EVENT_FRM8    = 0x00000100,
    MIPICSI_RX_EVENT_FRM9    = 0x00000200,
    MIPICSI_RX_EVENT_FRM10   = 0x00000400,
    MIPICSI_RX_EVENT_FRM11   = 0x00000800,
    MIPICSI_RX_EVENT_FRM12   = 0x00001000,
    MIPICSI_RX_EVENT_FRM13   = 0x00002000,
    MIPICSI_RX_EVENT_FRM14   = 0x00004000,
    MIPICSI_RX_EVENT_FRM15   = 0x00008000,
    MIPICSI_RX_EVENT_RACT    = 0x00010000,
    MIPICSI_RX_EVENT_RACTDET = 0x00020000,
}mipicsi_rx_event_t;

typedef enum e_mipicsi_dl_event
{
    MIPICSI_DL_EVENT_NONE = 0x00000000, // No event, default state
    MIPICSI_DL_EVENT_ESH  = 0x00000001,
    MIPICSI_DL_EVENT_ESS  = 0x00000002,
    MIPICSI_DL_EVENT_ECT  = 0x00000004,
    MIPICSI_DL_EVENT_EES  = 0x00000008,
    MIPICSI_DL_EVENT_EUL  = 0x00010000,
    MIPICSI_DL_EVENT_RUL  = 0x00020000,
    MIPICSI_DL_EVENT_ULP  = 0x01000000,
}mipicsi_dl_event_t;

typedef enum e_mipicsi_vc_event
{
    MIPICSI_VC_EVENT_NONE = 0x00000000, // No event, default state
    MIPICSI_VC_EVENT_MLF  = 0x00000001,
    MIPICSI_VC_EVENT_ECD  = 0x00000002,
    MIPICSI_VC_EVENT_CRC  = 0x00000004,
    MIPICSI_VC_EVENT_IDE  = 0x00000008,
    MIPICSI_VC_EVENT_WCE  = 0x00000010,
    MIPICSI_VC_EVENT_ECC  = 0x00000020,
    MIPICSI_VC_EVENT_ECN  = 0x00000040,
    MIPICSI_VC_EVENT_FRS  = 0x00000100,
    MIPICSI_VC_EVENT_FRD  = 0x00000200,
    MIPICSI_VC_EVENT_OVF  = 0x00010000,
    MIPICSI_VC_EVENT_FSR  = 0x01000000,
    MIPICSI_VC_EVENT_FER  = 0x02000000,
    MIPICSI_VC_EVENT_LSR  = 0x04000000,
    MIPICSI_VC_EVENT_LER  = 0x08000000,
    MIPICSI_VC_EVENT_ETR  = 0x10000000,
}mipicsi_vc_event_t;

typedef enum e_mipicsi_pm_event
{
    MIPICSI_PM_EVENT_NONE     = 0x00000000, // No event, default state
    MIPICSI_PM_EVENT_DSX      = 0x00000001,
    MIPICSI_PM_EVENT_DSN      = 0x00000002,
    MIPICSI_PM_EVENT_CSX      = 0x00000004,
    MIPICSI_PM_EVENT_CSN      = 0x00000008,
    MIPICSI_PM_EVENT_DUX      = 0x00000010,
    MIPICSI_PM_EVENT_DUN      = 0x00000020,
    MIPICSI_PM_EVENT_CUX      = 0x00000040,
    MIPICSI_PM_EVENT_CUN      = 0x00000080,
    MIPICSI_PM_EVENT_CLSS     = 0x00004000,
    MIPICSI_PM_EVENT_CLUL     = 0x00008000,
    MIPICSI_PM_EVENT_DL0_DLSS = 0x00010000,
    MIPICSI_PM_EVENT_DL1_DLSS = 0x00020000,
    MIPICSI_PM_EVENT_DL0_DLUL = 0x01000000,
    MIPICSI_PM_EVENT_DL1_DLUL = 0x02000000,
}mipicsi_pm_event_t;

typedef enum e_mipicsi_gst_event
{
    MIPICSI_GST_EVENT_NONE    = 0x00000000, // No event, default state
    MIPICSI_GST_EVENT_GNE     = 0x00000001,
    MIPICSI_GST_EVENT_GTH     = 0x00000002,
    MIPICSI_GST_EVENT_GOV     = 0x00000010,
    MIPICSI_GST_EVENT_GCD     = 0x00010000,
    MIPICSI_GST_EVENT_STRDS   = 0x00020000,
}mipicsi_gst_event_t;

typedef enum e_mipicsi_event
{
    MIPICSI_EVENT_NONE = 0x0,
    MIPICSI_EVENT_RX,
    MIPICSI_EVENT_DL,
    MIPICSI_EVENT_VC,
    MIPICSI_EVENT_PM,
    MIPICSI_EVENT_GST,
}mipicsi_event_t;

typedef struct st_mipicsi_event
{
    mipicsi_event_t     event;
    uint8_t             virtual_channel;
    mipicsi_vc_event_t  virtual_channel_event;
    mipicsi_dl_event_t  data_line_0_event;
    mipicsi_dl_event_t  data_line_1_event;
    mipicsi_rx_event_t  receive_event;
    mipicsi_pm_event_t  power_manage_event;
    mipicsi_gst_event_t generic_short_packet_event;
    uint8_t             num_of_stored_gst;
}mipicsi_event_status_t;

fsp_err_t mipicsi_vin_module_configure(void);
fsp_err_t mipicsi_vin_capture_start(uint8_t * p_buffer);
fsp_err_t mipicsi_vin_capture_stop(void);
fsp_err_t mipicsi_vin_callback_set(void (* p_callback)(vin_event_t vin_event, mipicsi_event_status_t mipicsi_event));
FSP_CPP_FOOTER

#endif /* MIPICSI_VIN_HAL_DRIVER_H__ */
