/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/**********************************************************************************************************************
 * File Name    : r_mipi_phy.c
 * Version      : .
 * Description  : .
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * IMPORTANT NOTICE : This version of sample project contains preliminary version of r_mipi_phy.h.
 *                    This file updated some portion to support MIPI-CSI hardware.
 *                    The API and its usage note are subject to change.
 *********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_mipi_phy.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define MIPI_PHY_OPEN        (0x4D504950)

#define MIPI_DSI_PRV_1MHZ    (1000000)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/

const mipi_phy_api_t g_mipi_phy =
{
    .open  = r_mipi_phy_open,
    .close = r_mipi_phy_close,
};

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @addtogroup MIPI_PHY
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Initialize the MIPI DSI peripheral according to section 57.3.1 D-PHY Start-up Procedure, R01UH0995EJ0060
 *
 * @retval FSP_SUCCESS                  The channel was successfully opened.
 * @retval FSP_ERR_ASSERTION            One or both of the parameters was NULL.
 * @retval FSP_ERR_ALREADY_OPEN         The instance is already opened.
 * @retval FSP_ERR_INVALID_MODE         Power control mode must be high-speed-mode.
 **********************************************************************************************************************/
fsp_err_t r_mipi_phy_open (mipi_phy_ctrl_t * const p_api_ctrl, mipi_phy_cfg_t const * const p_cfg)
{
    mipi_phy_ctrl_t * p_ctrl = p_api_ctrl;

    /* Set DSI/CSI Mode setting */
#if defined(R_DPHYCNT_DPHYMDC_MASTEREN_Msk)
    R_DPHYCNT->DPHYMDC_b.MASTEREN = p_cfg->dsi_mode;
#endif

    /* Set DPHYREFCR to match PCLKA */
    uint32_t pclka_hz = R_FSP_SystemClockHzGet(FSP_PRIV_CLOCK_PCLKA);
    R_MIPI_PHY->DPHYREFCR_b.RFREQ = (uint8_t) ((pclka_hz / MIPI_DSI_PRV_1MHZ) - 1);

    /* Start D-PHY LDO and wait for startup */
    R_MIPI_PHY->DPHYPWRCR_b.PWRSEN = 1;
    FSP_HARDWARE_REGISTER_WAIT((R_MIPI_PHY->DPHYSFR & R_MIPI_PHY_DPHYSFR_PWRSF_Msk), R_MIPI_PHY_DPHYSFR_PWRSF_Msk);

    /* Configure D-PHY PLL and LP frequency divider */
    R_MIPI_PHY->DPHYPLFCR          = p_cfg->pll_settings.raw;
    R_MIPI_PHY->DPHYESCCR_b.ESCDIV = p_cfg->lp_divisor;

    /* Start D-PHY PLL and wait for startup */
    R_MIPI_PHY->DPHYPLOCR_b.PLLSTP = 0;
    FSP_HARDWARE_REGISTER_WAIT((R_MIPI_PHY->DPHYSFR & R_MIPI_PHY_DPHYSFR_PLLSF_Msk), R_MIPI_PHY_DPHYSFR_PLLSF_Msk);

    /* Set D-PHY timing parameters */
    mipi_phy_timing_t const * p_timing = p_cfg->p_timing;
    R_MIPI_PHY->DPHYTIM1 = p_timing->t_init;
    R_MIPI_PHY->DPHYTIM2 = p_timing->dphytim2;
    R_MIPI_PHY->DPHYTIM3 = p_timing->dphytim3;
    R_MIPI_PHY->DPHYTIM4 = p_timing->dphytim4;
    R_MIPI_PHY->DPHYTIM5 = p_timing->dphytim5;
    R_MIPI_PHY->DPHYTIM6 = p_timing->t_lp_exit;

    /* Enable D-PHY */
    R_MIPI_PHY->DPHYOCR_b.DPHYEN = 1U;

    /* Keep track of p_cfg struct */
    p_ctrl->p_cfg = p_cfg;

    /* Mark control block as opened */
    p_ctrl->open = MIPI_PHY_OPEN;

    return FSP_SUCCESS;
}

/**********************************************************************************************************************
 * Stop filter operations and close the channel instance.
 *
 * NOTE: D_PHY must be stopped and LDO disabled before entering standby mode. See 56.3.2 D-PHY Stop Procedure, R01UH0995EJ0060
 *
 * @retval   FSP_SUCCESS           The channel is successfully closed.
 * @retval   FSP_ERR_ASSERTION     p_api_ctrl is NULL.
 * @retval   FSP_ERR_NOT_OPEN      Instance is not open.
 **********************************************************************************************************************/
fsp_err_t r_mipi_phy_close (mipi_phy_ctrl_t * const p_api_ctrl)
{
    mipi_phy_ctrl_t * p_ctrl = p_api_ctrl;

    /* Disable D-PHY */
    R_MIPI_PHY->DPHYOCR_b.DPHYEN = 0;

    /* Disable D-PHY PLL */
    R_MIPI_PHY->DPHYPLOCR_b.PLLSTP = 1;

    /* Disable MIPI LDO */
    R_MIPI_PHY->DPHYPWRCR_b.PWRSEN = 0;

    /* Set control block to closed */
    p_ctrl->open = 0U;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup MIPI_PHY)
 **********************************************************************************************************************/
