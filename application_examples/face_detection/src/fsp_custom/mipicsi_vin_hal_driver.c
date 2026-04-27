/*
 * Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
/**********************************************************************************************************************
 * File Name    : mipicsi_vin_hal_drvier.c
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
#include "hal_data.h"
#include "common_util.h"

#include "mipicsi_vin_hal_driver.h"
#include "R7KA8P1KF_core0_additional.h" // Include additional iodefine file.
#include "r_mipi_phy.h" // Include r_mipi_phy file

#include "mipicsi_vin_hal_driver_config.h"

#include "camera_layer.h"
#include "camera_utils.h"

#include "application_config.h"

/***************************************************************************************************************************
 * Macro definitions
 ***************************************************************************************************************************/
/*====================================================================================================
 * Debug and similar configuration / documentation
 ====================================================================================================*/
#define OV5640_HSCLK_HZ               (OV5640_HSCLK_MHZ * 1000000)
#define OV5640_HS_CLK_UI_NS           ((1000000000/OV5640_HSCLK_HZ)/2)
#define MIPI_DPHYTIM_CALC(sf, ns, ui) ((uint16_t)(((float)ui * (float)OV5640_HS_CLK_UI_NS) + ((float)ns * sf))) /* Input ns and UI, output ns */
#define MIPI_DPHYTIM_NS_TO_PCLKA(ns)  (uint8_t)(((float)ns / (float)g_pclka_period_ns) - 1.0f)

/*====================================================================================================
 * Camera Timing Macros
 ====================================================================================================*/
#define PHY_T_INIT       (75001)
#define PHY_T_CLK_MISS   (20)   /* ns */
#define PHY_T_CLK_SETTLE (150)  /* ns */
#define PHY_T_HS_SETT    (125)  /* ns */

#define PHY_T_LP_EXIT    (104)  /* ns (104 clock lane /115 data lane) */

#define PHY_T_CLK_PREP   (85)   /* ns (before CLK start) */
#define PHY_T_CLK_ZERO   (548)  /* ns */
#define PHY_T_CLK_PRE    (122)  /* ns (before DataN LPX) */
#define PHY_T_CLK_POST   (366)  /* ns */
#define PHY_T_CLK_TRAIL  (99)   /* ns */

#define PHY_T_HS_PREP    (74)   /* ns */
#define PHY_T_HS_ZERO    (143)  /* ns */
#define PHY_T_HS_TRAIL   (96)   /* ns */
#define PHY_T_HS_EXIT    (13)   /* ns */

/***************************************************************************************************************************
 * Private global variables and functions
 ***************************************************************************************************************************/
static uint32_t g_pclka_hz        = 0;
static uint32_t g_pclka_mhz       = 100000000U;
static float    g_pclka_period_ns = 0;

static void (* p_mipicsi_vin_user_callback)(vin_event_t vin_event, mipicsi_event_status_t mipicsi_event);

FSP_CPP_HEADER
static fsp_err_t mipi_phy_configure(mipi_phy_timing_t * phy_timing);
static fsp_err_t vin_configure(uint8_t vc_id);
static fsp_err_t mipi_csi_configure(void);
static fsp_err_t vin_buffer_set(uint8_t * p_buffer1, uint8_t * p_buffer2, uint8_t * p_buffer3, bool triple_buffer);

static void mipi_csi_debug_interrupt_enable(void);
static void mipi_csi_interrupt_enable(void);
static void vin_interrupt_enable(void);
FSP_CPP_FOOTER

#if (BSP_CFG_RTOS == 0) // Non RTOS
#define SOFTWARE_DELAY_MS(x)  R_BSP_SoftwareDelay(x, BSP_DELAY_UNITS_MILLISECONDS)
#elif (BSP_CFG_RTOS == 2) // FreeRTOS
#define SOFTWARE_DELAY_MS(x)  vTaskDelay(pdTICKS_TO_MS(x))
#endif

fsp_err_t mipicsi_vin_module_configure(void)
{
    FSP_CRITICAL_SECTION_DEFINE;

    // Check if the Graphics power domain is power on
    if(R_SYSTEM->PDCTRGD_b.PDPGSF != 0)
    {
        return FSP_ERR_NOT_ENABLED;
    }

    // MIPI-DSI and MIPI-CSI cannot be enabled at same time. Check if MIPI-DSI is disabled
    if(R_MSTP->MSTPCRC_b.MSTPC10 == 0)
    {
        return FSP_ERR_UNSUPPORTED;
    }

    FSP_CRITICAL_SECTION_ENTER;
    // Configure security and privilege attribute as secure
    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_SAR);
    R_PSCU->PSARC_b.PSARC15   = 0x0; // Graphic (GLCDC, MIPI-DSI, MIPI-CSI, DRW) Security Attribution
    R_PSCU->PPARC_b.PPARC15   = 0x0; // Graphic (GLCDC, MIPI-DSI, MIPI-CSI, DRW) Privilege Attribution
    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_SAR);

    // Release module stop for MIPI-CSI module
    R_MSTP->MSTPCRC_b.MSTPC17 = 0x0; // MIPI CSI Module Stop Cancel
    SOFTWARE_DELAY_MS(1);

    // Update pclka information with current PCLKA frequency
    g_pclka_hz        = R_FSP_SystemClockHzGet(FSP_PRIV_CLOCK_PCLKA);
    g_pclka_mhz       = (uint8_t) (g_pclka_hz / 1000000);
    g_pclka_period_ns = 1000000000.0f / ((float)g_pclka_hz);

    /* These values are empirically measured. I could not find a reliable way to calculate them from sensor data read from the camera */
    mipi_phy_timing_t measured_phy_timing =
    {
     .t_init = PHY_T_INIT,
     .t_lp_exit               = MIPI_DPHYTIM_NS_TO_PCLKA( PHY_T_LP_EXIT    ), // 160-128 ns (measured) Register Value: (calculated) / Calculated: 132

     .dphytim4_b.t_clk_zero   = MIPI_DPHYTIM_NS_TO_PCLKA( PHY_T_CLK_ZERO   ), // 583 ns (measured) Register Value: (calculated) / Calculated: 134
     .dphytim4_b.t_clk_pre    = MIPI_DPHYTIM_NS_TO_PCLKA( PHY_T_CLK_PRE    ), // 85 ns (measured) Register Value: (calculated) / Calculated: 112
     .dphytim4_b.t_clk_post   = MIPI_DPHYTIM_NS_TO_PCLKA( PHY_T_CLK_POST   ), // -- ns (measured)  Register Value: (calculated) / Calculated: 184
     .dphytim4_b.t_clk_trail  = MIPI_DPHYTIM_NS_TO_PCLKA( PHY_T_CLK_TRAIL  ), // -- ns (measured)  Register Value: (calculated) / Calculated: 60

     .dphytim5_b.t_hs_zero    = MIPI_DPHYTIM_NS_TO_PCLKA( PHY_T_HS_ZERO    ), // 88-160 ns (measured) Register Value: (calculated) / Calculated: 159
     .dphytim5_b.t_hs_trail   = MIPI_DPHYTIM_NS_TO_PCLKA( PHY_T_HS_TRAIL   ), // 84-110 ns (measured)  Register Value: (calculated) / Calculated: 67
     .dphytim5_b.t_hs_exit    = MIPI_DPHYTIM_NS_TO_PCLKA( PHY_T_HS_EXIT    ), // 12-15 ns (measured)  Register Value: (calculated) / Calculated: 100

     .dphytim3_b.t_hs_prep    = MIPI_DPHYTIM_NS_TO_PCLKA( PHY_T_HS_PREP    ), // 70-85 ns (measured)  Register Value: (calculated) / Calculated: 57
     .dphytim3_b.t_hs_sett    = MIPI_DPHYTIM_NS_TO_PCLKA( PHY_T_HS_SETT    ), // -- ns (measured)  Register Value: (calculated) / Calculated: 136

     .dphytim2_b.t_clk_prep   = MIPI_DPHYTIM_NS_TO_PCLKA( PHY_T_CLK_PREP   ), // 85 ns (measured)  Register Value: (calculated) / Calculated: 60
     .dphytim2_b.t_clk_settle = MIPI_DPHYTIM_NS_TO_PCLKA( PHY_T_CLK_SETTLE ), // -- ns (measured)  Register Value: (calculated) / Calculated: 127
     .dphytim2_b.t_clk_miss   = MIPI_DPHYTIM_NS_TO_PCLKA( PHY_T_CLK_MISS   ), // -- ns (measured)  Register Value: (calculated) / Calculated: 127
    };

    // Configure MIPI PHY
    mipi_phy_configure(&measured_phy_timing);

    // Configure VIN
    vin_configure(MIPI_VIRTUAL_CHANNEL);

    // Configure MIPI CSI
    mipi_csi_configure();

    FSP_CRITICAL_SECTION_EXIT;

    // Enable interrupts
    mipi_csi_interrupt_enable();
    mipi_csi_debug_interrupt_enable();
    vin_interrupt_enable();

    return FSP_SUCCESS;
}

fsp_err_t mipicsi_vin_capture_start(uint8_t * p_buffer)
{
    uint32_t vin_intf = R_VIN->IE;
    R_VIN->IE = 0x0;

    vin_buffer_set(p_buffer, NULL, NULL, false);

    // Start Capture
    R_VIN->MC_b.ME = 0x1;
    R_VIN->FC_b.CC = 0x1;

    R_VIN->IE = vin_intf;

    return FSP_SUCCESS;
}

fsp_err_t mipicsi_vin_capture_stop(void)
{
    uint32_t vin_intf = R_VIN->IE;
    R_VIN->IE = 0x0;

    // Stop Capture
    R_VIN->FC_b.CC = 0x0;
    R_VIN->MC_b.ME = 0x0;

    R_VIN->IE = vin_intf;

    return FSP_SUCCESS;
}

fsp_err_t mipicsi_vin_callback_set(void (* p_callback)(vin_event_t vin_event, mipicsi_event_status_t mipicsi_event))
{
    p_mipicsi_vin_user_callback = p_callback;

    return FSP_SUCCESS;
}

static fsp_err_t mipi_csi_configure()
{
    /* Module Control Register 3 */
    R_MIPI_CSI->MCT3_b.RXEN = 0; // Disable reception - Enable Configuration

    R_MIPI_CSI->MCT0_b.VDLN = MIPI_NUM_LANES; // Number of Valid Data Lanes
    R_MIPI_CSI->MCT0_b.ZLMD = 0; // Zero Length long packet output MoDe
    R_MIPI_CSI->MCT0_b.EDMD = 1; // ErrfameData notification MoDe
    R_MIPI_CSI->MCT0_b.RVMD = 1; // ReserVed packet reception MoDe
    R_MIPI_CSI->MCT0_b.GRMD = 1; // <TBD> JDG - ???? What Is LSI?
    // <TBD> JDG: This is a difference (later - not working - project ECCV13 was set to zero)
    R_MIPI_CSI->MCT0_b.ECCV13 = 1; // ECC check csi-2 Ver 1.3 mode (0: 26-bit, 1: 24-bit)
    R_MIPI_CSI->MCT0_b.LFSREN = 0; // LFSR Enable mode (Enable de-scrambling)

    /*  Module Control Register 2 */
    // R_MIPI_CSI->MCT2 = 0x02000002;
    uint32_t vclk = g_pclka_hz;
    R_MIPI_CSI->MCT2_b.FRRCLK = 0x1FF & ((uint16_t)((1.5f * (float)vclk)/(float)OV5640_HSCLK_HZ) + 1u); // clock FRequency Rate to adjust data lane SKew
    R_MIPI_CSI->MCT2_b.FRRSKW = 0x1FF & ((uint16_t)((3.0f * (float)vclk)/(float)OV5640_HSCLK_HZ) + 1u); // clock FRequency Rate to judge packet reception end

    /* EPD option control */
    R_MIPI_CSI->EPCT_b.SSP   = 0; // Long packet spacers - EPDEN = 0: disabled
    R_MIPI_CSI->EPCT_b.EPDEN = 0; // EPD Option select - EPDEN = 0: disabled
    R_MIPI_CSI->EPCT_b.SLP   = 0; // epd Short Packet Spacers - EPDEN = 0: disabled
    R_MIPI_CSI->EPCT_b.EPDOP = 0; // ENable EPD operation - EPDEN = 0: disabled

    /* EPD Misc Option Control Register */
    R_MIPI_CSI->EMCT_b.EOTPEN = 0; // ENable EOTP
    R_MIPI_CSI->EMCT_b.VLSIEN = 00; // ENable Variable-Length Spacer Insertions (when EPD option 2 enabled) -- EPD is disabled above

    /* Receive Data Type Enable Low Register
     *  - I'm not entirely sure why the UM doesn't roll these bitfields into the register definition. I may do that myself later, but this for now. */
    uint32_t dtel_dten_value = 0;
#if (VIN_INPUT_FORMAT == 0) //YUV422_8_BIT
    dtel_dten_value |= (1 << 30);
#elif (VIN_INPUT_FORMAT == 1) //YUV422_10_BIT
    dtel_dten_value |= (1 << 31);
#endif
    const uint32_t generic_short_packet_code8 = 1U << 15;
    const uint32_t generic_short_packet_code7 = 1U << 14;
    const uint32_t generic_short_packet_code6 = 1U << 13;
    const uint32_t generic_short_packet_code5 = 1U << 12;
    const uint32_t generic_short_packet_code4 = 1U << 11;
    const uint32_t generic_short_packet_code3 = 1U << 10;
    const uint32_t generic_short_packet_code2 = 1U << 9;
    const uint32_t generic_short_packet_code1 = 1U << 8;
    const uint32_t eotc = 1 << 4;
    R_MIPI_CSI->DTEL_b.DTEN =  dtel_dten_value | \
            (1 ? generic_short_packet_code8 : 0) | \
            (1 ? generic_short_packet_code7 : 0) | \
            (1 ? generic_short_packet_code6 : 0) | \
            (1 ? generic_short_packet_code5 : 0) | \
            (1 ? generic_short_packet_code4 : 0) | \
            (1 ? generic_short_packet_code3 : 0) | \
            (1 ? generic_short_packet_code2 : 0) | \
            (1 ? generic_short_packet_code1 : 0) | \
            (1 ? eotc                       : 0); // Data Type ENable (DT = 0x00 to 0x1F)

    /* Receive Data Type Enable High Register
     *  - I'm not entirely sure why the UM doesn't roll these bitfields into the register definition. I may do that myself later, but this for now. */
    uint32_t dteh_dten_value = 0;
#if (VIN_INPUT_FORMAT == 2) // RAW8
    dteh_dten_value |= (1 << 10);
#elif (VIN_INPUT_FORMAT == 3) // RGB888
    dteh_dten_value |= (1 << 4);
#endif
    R_MIPI_CSI->DTEH_b.DTEN = dteh_dten_value;

    /* Generic Short Packet Control */
    R_MIPI_CSI->GSCT_b.SHTH = 15; // Stored generic short packet THreshold
    R_MIPI_CSI->GSCT_b.GFIF = 1; // Generic short packet store in FIFo (enable)

    R_MIPI_CSI->GSCT_b.GFIF = 1;

#define DATA_LANE_INTERRUPT_ENABLE_BITS       (0x0103000F)// None, else interrupt storm //(0x0003000F); Disable SotHs, SotSyncs, ErrConTrol, and ErrESc (0xF)- Which can interrupt storm
    R_MIPI_CSI->RXIE   = 0;//0x00020000;
    R_MIPI_CSI->DLIE0  = DATA_LANE_INTERRUPT_ENABLE_BITS;
    R_MIPI_CSI->DLIE1  = DATA_LANE_INTERRUPT_ENABLE_BITS;

#define VIRTUAL_CHANNEL_INTERRUPT_ENABLE_BITS (0x1F01037F & ~(1<<24))
    R_MIPI_CSI->VCIE0  = VIRTUAL_CHANNEL_INTERRUPT_ENABLE_BITS;/*
    R_MIPI_CSI->VCIE1  = VIRTUAL_CHANNEL_INTERRUPT_ENABLE_BITS;
    R_MIPI_CSI->VCIE2  = VIRTUAL_CHANNEL_INTERRUPT_ENABLE_BITS;
    R_MIPI_CSI->VCIE3  = VIRTUAL_CHANNEL_INTERRUPT_ENABLE_BITS;
    R_MIPI_CSI->VCIE4  = VIRTUAL_CHANNEL_INTERRUPT_ENABLE_BITS;
    R_MIPI_CSI->VCIE5  = VIRTUAL_CHANNEL_INTERRUPT_ENABLE_BITS;
    R_MIPI_CSI->VCIE6  = VIRTUAL_CHANNEL_INTERRUPT_ENABLE_BITS;
    R_MIPI_CSI->VCIE7  = VIRTUAL_CHANNEL_INTERRUPT_ENABLE_BITS;
    R_MIPI_CSI->VCIE8  = VIRTUAL_CHANNEL_INTERRUPT_ENABLE_BITS;
    R_MIPI_CSI->VCIE9  = VIRTUAL_CHANNEL_INTERRUPT_ENABLE_BITS;
    R_MIPI_CSI->VCIE10 = VIRTUAL_CHANNEL_INTERRUPT_ENABLE_BITS;
    R_MIPI_CSI->VCIE11 = VIRTUAL_CHANNEL_INTERRUPT_ENABLE_BITS;
    R_MIPI_CSI->VCIE12 = VIRTUAL_CHANNEL_INTERRUPT_ENABLE_BITS;
    R_MIPI_CSI->VCIE13 = VIRTUAL_CHANNEL_INTERRUPT_ENABLE_BITS;
    R_MIPI_CSI->VCIE14 = VIRTUAL_CHANNEL_INTERRUPT_ENABLE_BITS;
    R_MIPI_CSI->VCIE15 = VIRTUAL_CHANNEL_INTERRUPT_ENABLE_BITS;*/

#define GENERIC_SHORT_PKT_INTERRUPT_ENABLE_BITS (0x00000013)
    R_MIPI_CSI->GSIE   = GENERIC_SHORT_PKT_INTERRUPT_ENABLE_BITS;

#define POWER_MANAAGEMENT_INTERRUPT_ENABLE_BITS (0x000000FC) // (0x000000FF)
    R_MIPI_CSI->PMIE   = POWER_MANAAGEMENT_INTERRUPT_ENABLE_BITS;

    /* Enable CSI Reception */
    R_MIPI_CSI->MCT3   = 0x00000001; // Enable reception - Disable Configuration

    /* Reset Control Register */
    //R_MIPI_CSI->RTCT_b.VSRST = 1; // Software reset video pixel interface (because we can and it feels like a thing reasonable people might do.)
    while((R_MIPI_CSI->RTST & 0x00000001) == 0x00000001);/* Wait for reset to complete  */

    return FSP_SUCCESS;
}

static void mipi_csi_interrupt_enable()
{
    R_BSP_IrqCfgEnable(MIPICSI_RX_IRQn, MIPICSI_RX_IRQ_PRIORITY, NULL);
    R_BSP_IrqCfgEnable(MIPICSI_DL_IRQn, MIPICSI_DL_IRQ_PRIORITY, NULL);
    R_BSP_IrqCfgEnable(MIPICSI_VC_IRQn, MIPICSI_VC_IRQ_PRIORITY, NULL);
    R_BSP_IrqCfgEnable(MIPICSI_PM_IRQn, MIPICSI_PM_IRQ_PRIORITY, NULL);
    R_BSP_IrqCfgEnable(MIPICSI_GST_IRQn, MIPICSI_GST_IRQ_PRIORITY, NULL);
}

static void mipi_csi_debug_interrupt_enable()
{
    /* Enable writes to debug registers for reset */
    R_MIPI_CSI0_DEBUG->DGMD_b.KEY = 0x43534932; // Debug Mode Enable Register - debug KEY code (write-only)
    R_MIPI_CSI0_DEBUG->DGIE0      = 0xFFFFFFFF; // Enable all Line Number Error and Line Start Error Virtual Channel interrupts
    R_MIPI_CSI0_DEBUG->DGIE1      = 0xFFFFFFFF; // Enable all Frame Number Error and No Packet Error Virtual Channel interrupts
    R_MIPI_CSI0_DEBUG->DGIE2      = 0xFFFFFFFF; // Enable all Elastic buFfer OVerflow on physical data lane and packet NO END detect interrupts
    R_MIPI_CSI0_DEBUG->DGIE3      = 0xFFFFFFFF; // Enable all DeSKeW Error on physical data lane and packet STaRt Timing Error on logical lane interrupts

    R_BSP_IrqCfgEnable(MIPICSI_GST_IRQn, MIPICSI_DBG_IRQ_PRIORITY, NULL);
}

static fsp_err_t mipi_phy_configure(mipi_phy_timing_t * phy_timing)
{
    R_MIPI_PHY->DPHYMDC_b.MASTEREN = 0x0;
    R_MIPI_PHY->DPHYREFCR_b.RFREQ = (uint8_t)(g_pclka_mhz - 1);

    /* Following registers not required for MIPI CSI
     * R_DPHYCNT->DPHYPLFCR
     * R_DPHYCNT->DPHYESCCR.ESCDIV[4:0]
     * R_DPHYCNT->DPHYPLOCR.PLLSTP
     * R_DPHYCNT->DPHYSFR.PLLSF (wait)
     */

    R_MIPI_PHY->DPHYPWRCR_b.PWRSEN = 1; // [0]:PWRSEN

    while((R_MIPI_PHY->DPHYSFR & 0x00000001) != 0x00000001);/* watch_reg */

    /* Intermediate variables for debug */

    /* DPHYTIM1 */
    R_MIPI_PHY->DPHYTIM1_b.TINIT    = 0x1FFFF & phy_timing->t_init;        // Per Table 65.2 for 100MHz PCLKA

    /* DPHYTIM2 */
    R_MIPI_PHY->DPHYTIM2_b.TCLKPREP = phy_timing->dphytim2_b.t_clk_prep;   // Camera MIPI_CLK is continuous
    R_MIPI_PHY->DPHYTIM2_b.TCLKSETT = phy_timing->dphytim2_b.t_clk_settle; // Camera MIPI_CLK is continuous
    R_MIPI_PHY->DPHYTIM2_b.TCLKMISS = phy_timing->dphytim2_b.t_clk_miss;   // Camera MIPI_CLK is continuous
    /* DPHYTIM3 */
    R_MIPI_PHY->DPHYTIM3_b.THSPREP  = phy_timing->dphytim3_b.t_hs_prep;    // 70 ns (measured)
    R_MIPI_PHY->DPHYTIM3_b.THSSETT  = phy_timing->dphytim3_b.t_hs_sett;    // 98 ns (measured: low-time + 6 UI - Per mipi spec v1.2) -- 1 UI measeured: 4ns
    /* DPHYTIM4 */
    R_MIPI_PHY->DPHYTIM4_b.TCLKZERO = phy_timing->dphytim4_b.t_clk_zero;   // 160 ns (159 measured)
    R_MIPI_PHY->DPHYTIM4_b.TCLKPRE  = phy_timing->dphytim4_b.t_clk_pre ;   // Camera MIPI_CLK is continuous - I don't think this setting matters
    R_MIPI_PHY->DPHYTIM4_b.TCLKPOST = phy_timing->dphytim4_b.t_clk_post;   // Camera MIPI_CLK is continuous - I don't think this setting matters
    R_MIPI_PHY->DPHYTIM4_b.TCLKTRL  = phy_timing->dphytim4_b.t_clk_trail;  // Camera MIPI_CLK is continuous - I don't think this setting matters
    /* DPHYTIM5 */
    R_MIPI_PHY->DPHYTIM5_b.THSEXIT  = phy_timing->dphytim5_b.t_hs_exit;    // 13 ns (measured)
    R_MIPI_PHY->DPHYTIM5_b.THSTRL   = phy_timing->dphytim5_b.t_hs_trail;   // 93 ns (measured)
    R_MIPI_PHY->DPHYTIM5_b.THSZERO  = phy_timing->dphytim5_b.t_hs_zero;    // 188 ns (measured)
    /* DPHYTIM6 */
    R_MIPI_PHY->DPHYTIM6_b.TLPX     = phy_timing->t_lp_exit;               // 119 ns (measured)

    R_MIPI_PHY->DPHYOCR_b.DPHYEN = 1; // [0]:DPHYEN

    return FSP_SUCCESS;
}

/* Strictly follow order of operations from UM for now */
static fsp_err_t vin_configure(uint8_t vc_id)
{
    // R_VIN->MC              = 0x04010002;
    R_VIN->MC_b.ME            = 0; // Disable Module for configuration
    R_VIN->FC_b.CC            = 0; // Put VIN in continuous frame capture mode waiting for video input

    //R_VIN->CSI_IFMD        = 0x02001E00;  // CSI Interface mode control
    R_VIN->CSI_IFMD_b.VC_SEL  = (uint8_t)(0xF & vc_id);  // Virtual channel

#if (VIN_INPUT_FORMAT == 0)            // YUV442 8-bit
    R_VIN->CSI_IFMD_b.DES0    = 1;     //   Data extension: pad with 1:zero 0:sign-extend
    R_VIN->DMR_b.YC_THR       = 0;     //   YCB, do not extend to 10-bit
    R_VIN->CSI_IFMD_b.DT      = 0x1E;  //   Data type YUV
    R_VIN->MC_b.INF           = 0x1;   //   Input format (001: 8-bit YCbCr-422)
#elif (VIN_INPUT_FORMAT == 1)          // YUV442 10-bit
    R_VIN->CSI_IFMD_b.DES0    = 1;     //   Data extension: pad with 1:zero 0:sign-extend
    R_VIN->DMR_b.YC_THR       = 1;     //   YCB, do not extend to 10-bit
    R_VIN->CSI_IFMD_b.DT      = 0x1F;  //   Data type YUV
    R_VIN->MC_b.INF           = 0x3;   //   Input format (011: 10-bit YCbCr-422)
#elif (VIN_INPUT_FORMAT == 2)          // RAW8
    R_VIN->DMR_b.YC_THR       = 0;     //   YCB, do not extend to 10-bit
    R_VIN->CSI_IFMD_b.DT      = 0x2A;  //   Data type RAW8
    R_VIN->MC_b.INF           = 0x4;   //   Input format (100: 8-bit user defined data (RAW8))
#elif (VIN_INPUT_FORMAT == 3)          // RGB888
    R_VIN->CSI_IFMD_b.DES0    = 0;     //   Data extension: pad with 1:zero 0:sign-extend
    R_VIN->DMR_b.YC_THR       = 0;     //   YCB, do not extend to 10-bit
    R_VIN->CSI_IFMD_b.DT      = 0x24;  //   Data type RAW8
    R_VIN->MC_b.INF           = 0x6;   //   Input format (110: 24-bit RGB-888)
#endif

    //R_VIN->DMR             = 0xAA010101;  // A8BIT = 0xAA
    R_VIN->DMR_b.YMODE        = 0;     // Both Y and CbCr transferred to memory
    R_VIN->DMR_b.EXRGB        = 0;     // Extension RGB Conversion mode off/on
    R_VIN->DMR_b.DTMD         = 0;     // Data conversion mode: not converted

#if (VIN_OUTPUT_FORMAT == 1)           // RGB565 Table 68.7
    R_VIN->DMR_b.YMODE        = 0;     //   Both Y and CbCr transferred to memory
    R_VIN->DMR_b.EXRGB        = 0;     //   Extension RGB Conversion mode off/on
    R_VIN->DMR_b.YC_THR       = 0;     //   YCB, do not extend to 10-bit
    R_VIN->DMR_b.DTMD         = 0;     //   Data conversion mode: not converted
#elif (VIN_OUTPUT_FORMAT == 2)         // RGB888 Table 68.7
    R_VIN->DMR_b.YMODE        = 0;     //   Both Y and CbCr transferred to memory
    R_VIN->DMR_b.EXRGB        = 1;     //   Extension RGB Conversion mode off/on
    R_VIN->DMR_b.YC_THR       = 0;     //   YCB, do not extend to 10-bit
    R_VIN->DMR_b.DTMD         = 0;     //   Data conversion mode: not converted
#elif (VIN_OUTPUT_FORMAT == 3)         // RGB1555 Table 68.7
    R_VIN->DMR_b.YMODE        = 0;     //   Both Y and CbCr transferred to memory
    R_VIN->DMR_b.EXRGB        = 0;     //   Extension RGB Conversion mode off/on
    R_VIN->DMR_b.YC_THR       = 0;     //   YCB, do not extend to 10-bit
    R_VIN->DMR_b.DTMD         = 1;     //   Data conversion mode: not converted
#elif (VIN_OUTPUT_FORMAT == 4)         // RGB8888 Table 68.7
    R_VIN->DMR_b.YMODE        = 0;     //   Both Y and CbCr transferred to memory
    R_VIN->DMR_b.EXRGB        = 1;     //   Extension RGB Conversion mode off/on
    R_VIN->DMR_b.YC_THR       = 0;     //   YCB, do not extend to 10-bit
    R_VIN->DMR_b.DTMD         = 1;     //   Data conversion mode: not converted
#endif

    R_VIN->DMR_b.ABIT         = 0;     // Alpha bit zero
    R_VIN->DMR_b.BPSM         = 1;     // Output byte swap (0: off)
    R_VIN->DMR_b.A8BIT        = 0xAA;  // These bits are the alpha value for the ARGB8888 format

    //R_VIN->SLPRC           = 0x00000000;  // Start Line Pre-Clip = 0
    // <TBD> JDG: Some of these clipping values were modified from original project. See comments
    R_VIN->SPPRC_b.SPPRC      = 0;  // Start Pixel Pre-Clip = 0
    R_VIN->EPPRC_b.EPPRC      = (CAMERA_ACTIVE_IMAGE_WIDTH * 2) - 1;  // End Pixel Pre-Clip
    R_VIN->SLPRC_b.SLPRC      = 0;  // Start Line Pre-Clip = 0
    R_VIN->ELPRC_b.ELPRC      = CAMERA_ACTIVE_IMAGE_HEIGHT - 1;  // End line Pre-Clip = 2

    R_VIN->IS_b.IS            = 0x1FFF & CAMERA_ACTIVE_IMAGE_WIDTH;  // VIN multiplies by divisor internally

    if((R_VIN->IS & 0xF) != 0) // See 68.2.10 of R01UH1064EJ0090
    {
        return FSP_ERR_INTERNAL;
    }

    // Not set in original project
    R_VIN->UVAOF_b.UVAOF      = 0 >> 7; // Specify the transfer offset address for the YC separation YCbCr-422 UV data

    R_VIN->MC_b.LUTE          = 0; // No look up table

    R_VIN->LUTP_b.LTCRPR      = 0;
    R_VIN->LUTP_b.LTCBPR      = 0;
    R_VIN->LUTP_b.LTYPR       = 0;

#if ((VIN_INPUT_FORMAT == 0) || (VIN_INPUT_FORMAT == 1)) && (VIN_OUTPUT_FORMAT == 0)
    R_VIN->MC_b.BPS           = 1; // Color space conversion bypass -- Table 68.3
#endif
    R_VIN->CSCE1 = 0x0001129F;
    R_VIN->CSCE2 = 0x01000800;
    R_VIN->CSCE3 = 0x19890D02;
    R_VIN->CSCE4 = 0x06452045;
    /*
    R_VIN->LUTD_b.LTYDT  = ;
    R_VIN->LUTD_b.LTCBDT = ;
    R_VIN->LUTD_b.LTCRDT = ;
     */
    R_VIN->YCCR1              = 0x00000107; // Default from UM
    R_VIN->YCCR2              = 0x00640204; // Default from UM
    R_VIN->YCCR3              = 0x8A010000; // Default from UM

    R_VIN->CBCCR1             = 0x00001F68; // Default from UM
    R_VIN->CBCCR2             = 0x01C21ED6; // Default from UM
    R_VIN->CBCCR3             = 0x8A010800; // Default from UM

    R_VIN->CRCCR1             = 0x000001C2; // Default from UM
    R_VIN->CRCCR2             = 0x1FB71E87; // Default from UM
    R_VIN->CRCCR3             = 0x8A010800; // Default from UM

    R_VIN->MC_b.YUV444        = 0; // Disable YUV conversion

    R_VIN->MC_b.DC            = 0; // Dithering with cumulative addition
    R_VIN->MC_b.DC2           = 1; // 0: Enable dithering

    /*====================================================================================================
     * This group of registers not mentioned in start-up procedure
     *====================================================================================================*/
    R_VIN->MC_b.IM          = 1; // Odd/Even field capture
    R_VIN->MC_b.EN          = 0; // Endian Type (1: big)
    R_VIN->MC_b.CLP         = 0; // No clipping

    //R_VIN->CSIFLD          = 0x00000010;
    R_VIN->CSIFLD_b.FLD_EN  = 0; // Even field detection control enabled
    R_VIN->CSIFLD_b.FLD_NUM = 1; // Default - Not configurable
    R_VIN->CSIFLD_b.FLD_SEL = 0; // even FieLD NUMber setting - Specify value for detecting even fields in interlaced image

    // Enabling interrupts
    R_VIN->IE_b.FOE       = 1; // FIFO overflow interrupt enable
    R_VIN->IE_b.EFE       = 0; // End of frame interrupt enable
    R_VIN->IE_b.SIE       = 0; // Scanline interrupt enable
    R_VIN->IE_b.FIE       = 0; // field interrupt enable
    R_VIN->IE_b.FME       = 0; // frame memory write complete interrupt enable
    R_VIN->IE_b.PRCLIPHEE = 0; // PRCLIPH error interuupt enable
    R_VIN->IE_b.PRCLIPVEE = 0; // prclipv error interrupt enable
    R_VIN->IE_b.ROE       = 1; // response overflow interrupt enable
    R_VIN->IE_b.AREE      = 1; // Axi resp error interrupt enable
    R_VIN->IE_b.VRE       = 0; // Vsync deasserting detect interrupt enable
    R_VIN->IE_b.VFE       = 1; // Vsync asserting detect interrupt enable
    R_VIN->IE_b.FIE2      = 0; // field interrupt interrupt enable

    /*====================================================================================================
     * The following registers not mentioned in start-up procedure
     *====================================================================================================*/
    R_VIN->MC_b.ST = 0x1;           // Initialize the internal state of VIN
    FSP_REGISTER_READ(R_VIN->MC_b.ST);                  // Wait at least 10 cycles of aclk (ICLK)
    FSP_REGISTER_READ(R_VIN->MC_b.ST);                  // Wait at least 10 cycles of aclk (ICLK)
    FSP_REGISTER_READ(R_VIN->MC_b.ST);                  // Wait at least 10 cycles of aclk (ICLK)
    FSP_REGISTER_READ(R_VIN->MC_b.ST);                  // Wait at least 10 cycles of aclk (ICLK)
    FSP_REGISTER_READ(R_VIN->MC_b.ST);                  // Wait at least 10 cycles of aclk (ICLK)
    FSP_REGISTER_READ(R_VIN->MC_b.ST);                  // Wait at least 10 cycles of aclk (ICLK)
    FSP_REGISTER_READ(R_VIN->MC_b.ST);                  // Wait at least 10 cycles of aclk (ICLK)
    FSP_REGISTER_READ(R_VIN->MC_b.ST);                  // Wait at least 10 cycles of aclk (ICLK)
    FSP_REGISTER_READ(R_VIN->MC_b.ST);                  // Wait at least 10 cycles of aclk (ICLK)
    FSP_REGISTER_READ(R_VIN->MC_b.ST);                  // Wait at least 10 cycles of aclk (ICLK)
    R_VIN->MC_b.SCLE = 0;           // No scaling

    // Not set in original project
    R_VIN->UDS_CTRL_b.NE_BCB = 0;   // default (shouldn't* be used)
    R_VIN->UDS_CTRL_b.NE_GY = 0;    // default (shouldn't* be used)
    R_VIN->UDS_CTRL_b.NE_RCR = 0;   // default (shouldn't* be used)
    R_VIN->UDS_CTRL_b.BC = 0;       // default (shouldn't* be used)
    R_VIN->UDS_CTRL_b.BLADV = 0;    // default (shouldn't* be used)
    R_VIN->UDS_CTRL_b.AMD = 1;      // default (shouldn't* be used)

    /*====================================================================================================
     * This group of registers not mentioned in start-up procedure
     *====================================================================================================*/
    // R_VIN->UDS_SCALE       = 0x10001000;
    // <TBD> JDG: Some values changed from original project. See above for original.
    R_VIN->UDS_SCALE_b.VFRAC = 0; // Multiplier (fractional part) of vertical scaling factor
    R_VIN->UDS_SCALE_b.VMANT = 0; // Multiplier (integral part) of vertical scaling factor
    R_VIN->UDS_SCALE_b.HFRAC = 0; // Multiplier (fractional part) of horizontal scaling factor
    R_VIN->UDS_SCALE_b.HMANT = 0; // Multiplier (integral part) of horizontal scaling factor

    // R_VIN->UDS_PASS_BWIDTH = 0x00400040;
    /*
    uint8_t bwidth_h = 64;
    if(R_VIN->UDS_SCALE_b.HMANT)
    {
        uint32_t mh = R_VIN->UDS_SCALE_b.HMANT;
        uint32_t mh_prime = R_VIN->UDS_SCALE_b.HFRAC;
        uint32_t fh = bwidth_h;
        uint32_t numerator = ;
        uint32_t denominator = ;
        bwidth_h = bwidth_h * ((numerator)/(denominator));
    }*/
    R_VIN->UDS_PASS_BWIDTH_b.BWIDTH_H = 64; // 0x40;
    R_VIN->UDS_PASS_BWIDTH_b.BWIDTH_V = 64; // 0x40;

    // R_VIN->UDS_CLIP_SIZE   = 0x07800004;
    // <TBD> JDG: Some values changed from original project. See above for original.
    R_VIN->UDS_CLIP_SIZE_b.CL_VSIZE   = CAMERA_ACTIVE_IMAGE_HEIGHT;
    R_VIN->UDS_CLIP_SIZE_b.CL_HSIZE   = CAMERA_ACTIVE_IMAGE_WIDTH * 2;

    R_VIN->SI = 0; //IMAGE_WIDTH / 2; // Enable for debug

    return FSP_SUCCESS;
}

static void vin_interrupt_enable(void)
{
    R_BSP_IrqCfgEnable(VIN_IRQ_IRQn, VIN_IRQ_PRIORITY, NULL);
    R_BSP_IrqCfgEnable(VIN_ERR_IRQn, VIN_ERR_PRIORITY, NULL);
}

static fsp_err_t vin_buffer_set(uint8_t * p_buffer1, uint8_t * p_buffer2, uint8_t * p_buffer3, bool triple_buffer)
{
    if(((uint32_t)p_buffer1 & ~(R_VIN_MB1_MB1_Msk)) != 0)
    {
        return FSP_ERR_INVALID_POINTER;
    }

    if(true == triple_buffer)
    {
        if(((uint32_t)p_buffer2 & ~(R_VIN_MB1_MB1_Msk)) != 0)
        {
            return FSP_ERR_INVALID_POINTER;
        }

        if(((uint32_t)p_buffer3 & ~(R_VIN_MB1_MB1_Msk)) != 0)
        {
            return FSP_ERR_INVALID_POINTER;
        }
    }

    uint32_t vin_intf = R_VIN->IE;
    R_VIN->IE = 0x0;

    if(false == triple_buffer)
    {
        R_VIN->MB1 = (uint32_t)p_buffer1;
        R_VIN->MB2 = (uint32_t)p_buffer1;
        R_VIN->MB3 = (uint32_t)p_buffer1;
    }
    else
    {
        R_VIN->MB1 = (uint32_t)p_buffer1;
        R_VIN->MB2 = (uint32_t)p_buffer2;
        R_VIN->MB3 = (uint32_t)p_buffer3;
    }

    R_VIN->IE = vin_intf;

    return FSP_SUCCESS;
}

void mipi_csi_rx_isr(void) // ELC_EVENT_MIPICSI_RX
{
    mipicsi_event_status_t mipi_event_status;
    mipi_event_status.event = MIPICSI_EVENT_RX;
    mipi_event_status.receive_event = R_MIPI_CSI->RXST;
    R_MIPI_CSI->RXSC = 0xFFFFFFFF;

    IRQn_Type irq = R_FSP_CurrentIrqGet();
    R_BSP_IrqStatusClear(irq);

    if(NULL != p_mipicsi_vin_user_callback)
    {
        p_mipicsi_vin_user_callback(0, mipi_event_status);
    }
}

void mipi_csi_dl_isr(void) // ELC_EVENT_MIPICSI_DL (data lane)
{
    mipicsi_event_status_t mipi_event_status;
    mipi_event_status.event = MIPICSI_EVENT_DL;
    mipi_event_status.data_line_0_event = R_MIPI_CSI->DLST0;
    mipi_event_status.data_line_1_event = R_MIPI_CSI->DLST1;
    R_MIPI_CSI->DLSC0 = mipi_event_status.data_line_0_event;
    R_MIPI_CSI->DLSC1 = mipi_event_status.data_line_1_event;

    IRQn_Type irq = R_FSP_CurrentIrqGet();
    R_BSP_IrqStatusClear(irq);

    if(NULL != p_mipicsi_vin_user_callback)
    {
        p_mipicsi_vin_user_callback(0, mipi_event_status);
    }
}

void mipi_csi_vc_isr(void)  // Virtual Channel interrupt
{
    mipicsi_event_status_t mipi_event_status;
    mipi_event_status.event = MIPICSI_EVENT_VC;
    mipi_event_status.virtual_channel_event = R_MIPI_CSI->VCSC0;
    R_MIPI_CSI->VCSC0 = 0x1F01C37F & ~(1<<24); // Clear all but FSR (it's read in main loop) -  MLFC, ECDC, and AMLFC apply universally to all channels (0x00004003)

    IRQn_Type irq = R_FSP_CurrentIrqGet();
    R_BSP_IrqStatusClear(irq);

    if(NULL != p_mipicsi_vin_user_callback)
    {
        p_mipicsi_vin_user_callback(0, mipi_event_status);
    }
}

void mipi_csi_pm_isr(void) // Power Management interrupt
{
    mipicsi_event_status_t mipi_event_status;
    mipi_event_status.event = MIPICSI_EVENT_PM;
    mipi_event_status.power_manage_event = R_MIPI_CSI->PMST;
    R_MIPI_CSI->PMSC = mipi_event_status.power_manage_event & 0xFF;

    IRQn_Type irq = R_FSP_CurrentIrqGet();
    R_BSP_IrqStatusClear(irq);

    if(NULL != p_mipicsi_vin_user_callback)
    {
        p_mipicsi_vin_user_callback(0, mipi_event_status);
    }
}

void mipi_csi_gst_isr(void) // Generic Short Packet interrupt
{
    IRQn_Type irq = R_FSP_CurrentIrqGet();
    R_BSP_IrqStatusClear(irq);

    mipicsi_event_status_t mipi_event_status;
    mipi_event_status.event = MIPICSI_EVENT_GST;

    mipi_event_status.generic_short_packet_event = R_MIPI_CSI->GSST & 0xFFFF00FF;
    mipi_event_status.num_of_stored_gst = R_MIPI_CSI->GSST_b.PNUM;

    if(0 != mipi_event_status.num_of_stored_gst)
    {
        R_MIPI_CSI->GSSC = (uint32_t)(mipi_event_status.num_of_stored_gst << 4);
    }

    if(NULL != p_mipicsi_vin_user_callback)
    {
        p_mipicsi_vin_user_callback(0, mipi_event_status);
    }
}

void mipi_csi_dbg_isr(void) // Debug interrupt
{
    IRQn_Type irq = R_FSP_CurrentIrqGet();
    R_BSP_IrqStatusClear(irq);

    // CSI Setting
    unsigned int read_data0 = *((volatile unsigned int*)(&R_MIPI_CSI0_DEBUG->DGST0)); (void) read_data0;
    unsigned int read_data1 = *((volatile unsigned int*)(&R_MIPI_CSI0_DEBUG->DGST1)); (void) read_data1;
    unsigned int read_data2 = *((volatile unsigned int*)(&R_MIPI_CSI0_DEBUG->DGST2)); (void) read_data2;
    unsigned int read_data3 = *((volatile unsigned int*)(&R_MIPI_CSI0_DEBUG->DGST3)); (void) read_data3;


    R_MIPI_CSI0_DEBUG->DGSC0 = read_data0;
    R_MIPI_CSI0_DEBUG->DGSC1 = read_data1;
    R_MIPI_CSI0_DEBUG->DGSC2 = read_data2;
    R_MIPI_CSI0_DEBUG->DGSC3 = read_data3;

    FSP_PARAMETER_NOT_USED(read_data0);
    FSP_PARAMETER_NOT_USED(read_data1);
    FSP_PARAMETER_NOT_USED(read_data2);
    FSP_PARAMETER_NOT_USED(read_data3);
}

void vin_irq_isr(void) // Interrupt Request
{
    vin_event_t vin_event = R_VIN->INTS;
    R_VIN->INTS = vin_event;
    IRQn_Type irq = R_FSP_CurrentIrqGet();
    R_BSP_IrqStatusClear(irq);

    unsigned int read_data0;
    unsigned int read_data2;
    unsigned int read_data3;

    FSP_PARAMETER_NOT_USED(read_data0);
    FSP_PARAMETER_NOT_USED(read_data2);
    FSP_PARAMETER_NOT_USED(read_data3);

    // CSI Setting
    read_data0 = *((volatile unsigned int*)(&R_VIN->MS));
    read_data2 = *((volatile unsigned int*)(&R_VIN->MTCSTOP));
    read_data3 = *((volatile unsigned int*)0x4034776C);//&R_VIN->SYNCS));

    if(NULL != p_mipicsi_vin_user_callback)
    {
        mipicsi_event_status_t mipicsi_event_status = {0x0};
        p_mipicsi_vin_user_callback(vin_event, mipicsi_event_status);
    }
}

void vin_err_isr(void)
{
    vin_event_t vin_event = R_VIN->INTS;
    R_VIN->INTS = vin_event;
    IRQn_Type irq = R_FSP_CurrentIrqGet();
    R_BSP_IrqStatusClear(irq);

    if(NULL != p_mipicsi_vin_user_callback)
    {
        mipicsi_event_status_t mipicsi_event_status = {0x0};
        p_mipicsi_vin_user_callback(vin_event, mipicsi_event_status);
    }
}
