/*
 * Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
/**********************************************************************************************************************
 * File Name    : ospi_b_ep.c
 * Version      : .
 * Description  : .
 *********************************************************************************************************************/
#include "hal_data.h"
#include "common_util.h"
#include "ospi_b_ep.h"

/*******************************************************************************************************************//**
 * @addtogroup ospi_b_ep.c
 * @{
 **********************************************************************************************************************/

#define OSPI_B_EP_ERR_RETURN(...)

/* External variables */

/* function declarations*/
fsp_err_t ospi_b_setup_calibrate_data(void);
fsp_err_t ospi_test_wait_until_wip(void);

/*******************************************************************************************************************//**
 * @brief       This functions initializes OSPI module and Flash device.
 * @param       None
 * @retval      FSP_SUCCESS     Upon successful initialization of OSPI module and Flash device
 * @retval      Any Other Error code apart from FSP_SUCCESS  Unsuccessful open
 **********************************************************************************************************************/
fsp_err_t ospi_b_init ()
{
    fsp_err_t err = FSP_SUCCESS;

    err = R_OSPI_B_Open(&g_ospi_b_ctrl, &g_ospi_b_cfg);
    OSPI_B_EP_ERR_RETURN(err, "R_OSPI_B_Open API FAILED \r\n");

    R_XSPI0_Type * p_reg = g_ospi_b_ctrl.p_reg;

    /* Reset flash device */
    p_reg->LIOCTL_b.RSTCS0 = 0;
    R_BSP_SoftwareDelay(10, BSP_DELAY_UNITS_MILLISECONDS);
    p_reg->LIOCTL_b.RSTCS0 = 1;
    R_BSP_SoftwareDelay(1, BSP_DELAY_UNITS_MILLISECONDS);

    err = R_OSPI_B_SpiProtocolSet(&g_ospi_b_ctrl, SPI_FLASH_PROTOCOL_EXTENDED_SPI);
    OSPI_B_EP_ERR_RETURN(err, "R_OSPI_B_SpiProtocolSet API FAILED \r\n");

    return err;
}

/*******************************************************************************************************************//**
 * @brief       This function configures ospi to extended spi mode.
 * @param[IN]   None
 * @retval      FSP_SUCCESS                  Upon successful transition to spi operating mode.
 * @retval      FSP_ERR_ABORTED              Upon incorrect read data.
 * @retval      Any Other Error code apart from FSP_SUCCESS  Unsuccessful operation
 **********************************************************************************************************************/
fsp_err_t ospi_b_set_protocol_to_spi ()
{
    fsp_err_t                   err = FSP_SUCCESS;
    spi_flash_direct_transfer_t direct_command;
    bsp_octaclk_settings_t      new_octaclk_config;

    /* Execute Write Enable */
    memset(&direct_command, 0, sizeof(direct_command));
    direct_command.command        = 0x06F9;
    direct_command.command_length = 0x2;
    err = R_OSPI_B_DirectTransfer (g_ospi_b.p_ctrl, &direct_command, SPI_FLASH_DIRECT_TRANSFER_DIR_WRITE);
    OSPI_B_EP_ERR_RETURN(err, "ospi_b_write_enable FAILED \r\n");

    /* Set DQS disable */
    if(FSP_SUCCESS == err)
    {
        memset(&direct_command, 0, sizeof(direct_command));
        direct_command.command        = 0x728D;
        direct_command.command_length = 0x2;
        direct_command.address        = 0x00000200;
        direct_command.address_length = 0x4;
        direct_command.data           = 0x00;
        direct_command.data_length    = 0x1;
        err = R_OSPI_B_DirectTransfer (g_ospi_b.p_ctrl, &direct_command, SPI_FLASH_DIRECT_TRANSFER_DIR_WRITE);
        OSPI_B_EP_ERR_RETURN(err, "ospi_b_dqs_disable FAILED \r\n");
    }

    /* Execute Write Enable */
    if(FSP_SUCCESS == err)
    {
        memset(&direct_command, 0, sizeof(direct_command));
        direct_command.command        = 0x06F9;
        direct_command.command_length = 0x2;
        err = R_OSPI_B_DirectTransfer (g_ospi_b.p_ctrl, &direct_command, SPI_FLASH_DIRECT_TRANSFER_DIR_WRITE);
        OSPI_B_EP_ERR_RETURN(err, "ospi_b_write_enable FAILED \r\n");
    }

    /* Exit DOPI Mode */
    if(FSP_SUCCESS == err)
    {
        memset(&direct_command, 0, sizeof(direct_command));
        direct_command.command        = 0x728D;
        direct_command.command_length = 0x2;
        direct_command.address        = 0x00000000;
        direct_command.address_length = 0x4;
        direct_command.data           = 0x00;
        direct_command.data_length    = 0x1;
        err = R_OSPI_B_DirectTransfer (g_ospi_b.p_ctrl, &direct_command, SPI_FLASH_DIRECT_TRANSFER_DIR_WRITE);
        OSPI_B_EP_ERR_RETURN(err, "ospi_b_dopi_exit FAILED \r\n");
    }

    /* Change OSPI clock */
    if(FSP_SUCCESS == err)
    {
        err = R_OSPI_B_Close(g_ospi_b.p_ctrl);
        OSPI_B_EP_ERR_RETURN(err, "ospi_b_close FAILED \r\n");

        new_octaclk_config.source_clock = BSP_CLOCKS_SOURCE_CLOCK_PLL2Q;
        new_octaclk_config.divider      = BSP_CLOCKS_OCTA_CLOCK_DIV_2;
        R_BSP_OctaclkUpdate(&new_octaclk_config);
    }

    if(FSP_SUCCESS == err)
    {
        err = R_OSPI_B_Open(g_ospi_b.p_ctrl, g_ospi_b.p_cfg);
        OSPI_B_EP_ERR_RETURN(err, "ospi_b_close FAILED \r\n");
    }

    /* Switch OSPI module mode to SPI mode */
    if(FSP_SUCCESS == err)
    {
        err = R_OSPI_B_SpiProtocolSet(&g_ospi_b_ctrl, SPI_FLASH_PROTOCOL_EXTENDED_SPI);
        OSPI_B_EP_ERR_RETURN(err, "R_OSPI_SpiProtocolSet API FAILED \r\n");
    }

    return err;
}

/*******************************************************************************************************************//**
 * @brief       This function configures ospi to opi mode.
 * @param[IN]   None
 * @retval      FSP_SUCCESS                  Upon successful transition to opi operating mode.
 * @retval      FSP_ERR_ABORTED              Upon incorrect read data.
 * @retval      Any Other Error code apart from FSP_SUCCESS  Unsuccessful operation
 **********************************************************************************************************************/
fsp_err_t ospi_b_set_protocol_to_opi ()
{
    fsp_err_t                   err = FSP_SUCCESS;
    spi_flash_direct_transfer_t direct_command;
    bsp_octaclk_settings_t      new_octaclk_config;

    /* Set calibration data for 8D-8D-8D mode operation */
    err = ospi_b_setup_calibrate_data();
    OSPI_B_EP_ERR_RETURN(err, "ospi_b_calib_data_write FAILED \r\n");

    /* Execute Write Enable */
    if(FSP_SUCCESS == err)
    {
        memset(&direct_command, 0, sizeof(direct_command));
        direct_command.command        = 0x06;
        direct_command.command_length = 0x1;
        err = R_OSPI_B_DirectTransfer (g_ospi_b.p_ctrl, &direct_command, SPI_FLASH_DIRECT_TRANSFER_DIR_WRITE);
        OSPI_B_EP_ERR_RETURN(err, "ospi_b_write_enable FAILED \r\n");
    }

    /* Update dummy cycle according to used clock speed */
    if(FSP_SUCCESS == err)
    {
        memset(&direct_command, 0, sizeof(direct_command));
        direct_command.command        = 0x72;
        direct_command.command_length = 0x1;
        direct_command.address        = 0x00000300;
        direct_command.address_length = 0x4;
        direct_command.data           = 0x03; // DC[2:0]=011b=14 dummy cycle (max ospi clock is 133 MHz)
        direct_command.data_length    = 0x1;
        err = R_OSPI_B_DirectTransfer (g_ospi_b.p_ctrl, &direct_command, SPI_FLASH_DIRECT_TRANSFER_DIR_WRITE);
        OSPI_B_EP_ERR_RETURN(err, "ospi_b_update_dummy_cycle FAILED \r\n");
    }

    /* Execute Write Enable */
    if(FSP_SUCCESS == err)
    {
        memset(&direct_command, 0, sizeof(direct_command));
        direct_command.command        = 0x06;
        direct_command.command_length = 0x1;
        err = R_OSPI_B_DirectTransfer (g_ospi_b.p_ctrl, &direct_command, SPI_FLASH_DIRECT_TRANSFER_DIR_WRITE);
        OSPI_B_EP_ERR_RETURN(err, "ospi_b_write_enable FAILED \r\n");
    }

    /* Set DQS enable */
    if(FSP_SUCCESS == err)
    {
        memset(&direct_command, 0, sizeof(direct_command));
        direct_command.command        = 0x72;
        direct_command.command_length = 0x1;
        direct_command.address        = 0x00000200;
        direct_command.address_length = 0x4;
        direct_command.data           = 0x02;
        direct_command.data_length    = 0x1;
        err = R_OSPI_B_DirectTransfer (g_ospi_b.p_ctrl, &direct_command, SPI_FLASH_DIRECT_TRANSFER_DIR_WRITE);
        OSPI_B_EP_ERR_RETURN(err, "ospi_b_dqs_enable FAILED \r\n");
    }

    /* Execute Write Enable */
    if(FSP_SUCCESS == err)
    {
        memset(&direct_command, 0, sizeof(direct_command));
        direct_command.command        = 0x06;
        direct_command.command_length = 0x1;
        err = R_OSPI_B_DirectTransfer (g_ospi_b.p_ctrl, &direct_command, SPI_FLASH_DIRECT_TRANSFER_DIR_WRITE);
        OSPI_B_EP_ERR_RETURN(err, "ospi_b_write_enable FAILED \r\n");
    }

    /* Enter DOPI Mode */
    if(FSP_SUCCESS == err)
    {
        memset(&direct_command, 0, sizeof(direct_command));
        direct_command.command        = 0x72;
        direct_command.command_length = 0x1;
        direct_command.address        = 0x00000000;
        direct_command.address_length = 0x4;
        direct_command.data           = 0x02;
        direct_command.data_length    = 0x1;
        err = R_OSPI_B_DirectTransfer (g_ospi_b.p_ctrl, &direct_command, SPI_FLASH_DIRECT_TRANSFER_DIR_WRITE);
        OSPI_B_EP_ERR_RETURN(err, "ospi_b_dopi_mode_enter FAILED \r\n");
    }

    /* Change OSPI clock */
    if(FSP_SUCCESS == err)
    {
        err = R_OSPI_B_Close(g_ospi_b.p_ctrl);
        OSPI_B_EP_ERR_RETURN(err, "ospi_b_close FAILED \r\n");
    }

    if(FSP_SUCCESS == err)
    {
        new_octaclk_config.source_clock = BSP_CLOCKS_SOURCE_CLOCK_PLL2Q;
        new_octaclk_config.divider      = BSP_CLOCKS_OCTA_CLOCK_DIV_1;
        R_BSP_OctaclkUpdate(&new_octaclk_config);

        err = R_OSPI_B_Open(g_ospi_b.p_ctrl, g_ospi_b.p_cfg);
        OSPI_B_EP_ERR_RETURN(err, "ospi_b_close FAILED \r\n");
    }

    /* Switch OSPI module mode to SPI mode */
    if(FSP_SUCCESS == err)
    {
        err = R_OSPI_B_SpiProtocolSet(&g_ospi_b_ctrl, SPI_FLASH_PROTOCOL_8D_8D_8D);
        OSPI_B_EP_ERR_RETURN(err, "R_OSPI_SpiProtocolSet API FAILED \r\n");
    }

    return err;
}

fsp_err_t ospi_b_setup_calibrate_data(void)
{
    fsp_err_t fsp_status = FSP_SUCCESS;

    ospi_b_extended_cfg_t * p_ospi_extended_cfg;
    p_ospi_extended_cfg = (ospi_b_extended_cfg_t *) g_ospi_b.p_cfg->p_extend;
    ospi_b_instance_ctrl_t * p_ospi_ctrl;
    p_ospi_ctrl = (ospi_b_instance_ctrl_t *) g_ospi_b.p_ctrl;

    if(p_ospi_ctrl->spi_protocol != SPI_FLASH_PROTOCOL_1S_1S_1S)
    {
        return FSP_ERR_UNSUPPORTED;
    }

    // The expected data values are 0xFFFF0000U, 0x000800FFU, 0x00FFF700U, 0xF700F708U.
    // However, the OSPI memory (MX25LW51245G) on the EK-RA8D2 WS/P1 is a byte order swapped data type memory,
    // and this application writes calibration data in 1S-1S-1S mode (non-8D-8D-8D mode).
    // Therefore, the data must be pre-swapped before being written to the memory device.
    // Reference : section "Byte Data Order in 8-pin DDR Mode" in OSPI chapter in RA8x2 Hardware User's Manual.
    uint32_t g_autocalibration_data[] =
    {
     0xFFFF0000U, 0x000800FFU, 0x00FFF700U, 0xF700F708U
    };

    uint32_t g_autocalibration_data_swapped[] =
    {
     0xFFFF0000U, 0x0800FF00U, 0xFF0000F7U, 0x00F708F7U
    };

#if BSP_CFG_DCACHE_ENABLED
    SCB_InvalidateDCache_by_Addr((volatile void *)p_ospi_extended_cfg->p_autocalibration_preamble_pattern_addr, sizeof(g_autocalibration_data));
#endif

    /* Verify auto-calibration data */
    if (0x0 != memcmp(p_ospi_extended_cfg->p_autocalibration_preamble_pattern_addr, &g_autocalibration_data, sizeof(g_autocalibration_data)))
    {
        /* Erase the flash sector that will store auto-calibration data */
        fsp_status = R_OSPI_B_Erase (g_ospi_b.p_ctrl, p_ospi_extended_cfg->p_autocalibration_preamble_pattern_addr, 0x1000);
        if(FSP_SUCCESS != fsp_status)
        {
            return fsp_status;
        }

        /* Wait until erase operation completes */
        ospi_test_wait_until_wip();

#if BSP_CFG_DCACHE_ENABLED
#if OSPI_B_CFG_DMAC_SUPPORT_ENABLE
        SCB_CleanDCache_by_Addr((volatile void *)&g_autocalibration_data_swapped[0], sizeof(g_autocalibration_data));
#else
        SCB_DisableDCache();
#endif
#endif

        /* Write auto-calibration data to the flash */
        fsp_status = R_OSPI_B_Write(g_ospi_b.p_ctrl, (uint8_t *)&g_autocalibration_data_swapped, p_ospi_extended_cfg->p_autocalibration_preamble_pattern_addr, sizeof(g_autocalibration_data));
        if(FSP_SUCCESS != fsp_status)
        {
            return fsp_status;
        }

        /* Wait until write operation completes */
        ospi_test_wait_until_wip();

#if BSP_CFG_DCACHE_ENABLED
#if OSPI_B_CFG_DMAC_SUPPORT_ENABLE
        SCB_InvalidateDCache_by_Addr((volatile void *)p_ospi_extended_cfg->p_autocalibration_preamble_pattern_addr, sizeof(g_autocalibration_data));
#else
        SCB_EnableDCache();
#endif
#endif
    }

    return fsp_status;
}

fsp_err_t ospi_test_wait_until_wip(void)
{
    fsp_err_t fsp_status = FSP_SUCCESS;

    spi_flash_status_t status;
    status.write_in_progress = true;
    uint32_t timeout = UINT32_MAX;
    while ((status.write_in_progress) && (--timeout > 0))
    {
        fsp_status = R_OSPI_B_StatusGet (g_ospi_b.p_ctrl, &status);
        if(FSP_SUCCESS != fsp_status){ return FSP_ERR_INTERNAL; }
    }

    if (0 == timeout)
    {
        return FSP_ERR_TIMEOUT;
    }

    return fsp_status;
}


/*******************************************************************************************************************//**
 * @} (end addtogroup ospi_b_ep.c)
 **********************************************************************************************************************/
