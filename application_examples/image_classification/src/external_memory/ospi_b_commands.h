/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/**********************************************************************************************************************
 * File Name    : ospi_b_commands.h
 * Version      : .
 * Description  : .
 *********************************************************************************************************************/
#ifndef OSPI_B_COMMANDS_H_
#define OSPI_B_COMMANDS_H_

#include "hal_data.h"

/* Macro for OSPI command code */
#define OSPI_B_COMMAND_WRITE_ENABLE_SPI             (0x06)
#define OSPI_B_COMMAND_READ_STATUS_SPI              (0x05)
#define OSPI_B_COMMAND_READ_REGISTER_SPI            (0x15)
#define OSPI_B_COMMAND_WRITE_REGISTER_SPI           (0x01)
#define OSPI_B_COMMAND_READ_REGISTER2_SPI           (0x71)
#define OSPI_B_COMMAND_WRITE_REGISTER2_SPI          (0x72)

#define OSPI_B_COMMAND_WRITE_ENABLE_OPI             (0x06F9)
#define OSPI_B_COMMAND_WRITE_REGISTER_OPI           (0x01FE)
#define OSPI_B_COMMAND_WRITE_REGISTER2_OPI          (0x728D)
#define OSPI_B_COMMAND_READ_STATUS_OPI              (0x05FA)
#define OSPI_B_COMMAND_READ_REGISTER_OPI            (0x15EA)

/* Macro for OSPI command length */
#define OSPI_B_COMMAND_LENGTH_SPI                   (1U)
#define OSPI_B_COMMAND_LENGTH_OPI                   (2U)

/* Macro for OSPI transfer address */
#define OSPI_B_ADDRESS_DUMMY                        (0U)
#define OSPI_B_ADDRESS_LENGTH_ZERO                  (0U)
#define OSPI_B_ADDRESS_LENGTH_THREE                 (3U)
#define OSPI_B_ADDRESS_LENGTH_FOUR                  (4U)

/* Macro for OSPI transfer data */
#define OSPI_B_DATA_DUMMY                           (0U)
#define OSPI_B_DATA_LENGTH_ZERO                     (0U)
#define OSPI_B_DATA_LENGTH_ONE                      (1U)
#define OSPI_B_DATA_LENGTH_TWO                      (2U)
#define OSPI_B_DATA_LENGTH_FOUR                     (4U)

/* Macro for OSPI transfer dummy cycles */
#define OSPI_B_DUMMY_CYCLE_WRITE_SPI                (0U)
#define OSPI_B_DUMMY_CYCLE_WRITE_OPI                (0U)
#define OSPI_B_DUMMY_CYCLE_READ_STATUS_SPI          (0U)
#define OSPI_B_DUMMY_CYCLE_READ_STATUS_OPI          (4U)
#define OSPI_B_DUMMY_CYCLE_READ_REGISTER_SPI        (1U)
#define OSPI_B_DUMMY_CYCLE_READ_REGISTER_OPI        (4U)
#define OSPI_B_DUMMY_CYCLE_READ_MEMORY_SPI          (3U)


typedef enum e_ospi_b_transfer
{
    OSPI_B_TRANSFER_WRITE_ENABLE_SPI = 0,
    OSPI_B_TRANSFER_WRITE_CFR2V_SPI,
    OSPI_B_TRANSFER_READ_STATUS_SPI,
    OSPI_B_TRANSFER_READ_CFR2V_SPI,

    /* OPI */
    OSPI_B_TRANSFER_WRITE_ENABLE_OPI,
    OSPI_B_TRANSFER_WRITE_CFR2V_OPI,
    OSPI_B_TRANSFER_READ_STATUS_OPI,
    OSPI_B_TRANSFER_READ_CFR2V_OPI,

    OSPI_B_TRANSFER_MAX
} ospi_b_transfer_t;

#endif /* OSPI_B_COMMANDS_H_ */
