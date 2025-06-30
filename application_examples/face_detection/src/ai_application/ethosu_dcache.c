/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/**********************************************************************************************************************
 * File Name    : ethosu_dcache.c
 * Description  : .
 **********************************************************************************************************************/

#include "common_data.h"

// Overwrite cache clean API of ethos-u-driver
void ethosu_flush_dcache(uint32_t *p, size_t bytes)
{
#if (BSP_CFG_DCACHE_ENABLED == 1)
    if(p != NULL)
    {
        SCB_CleanDCache_by_Addr(p, (int32_t) bytes);
    }
    else
    {
        SCB_CleanDCache();
    }
#else
    FSP_PARAMETER_NOT_USED(p);
    FSP_PARAMETER_NOT_USED(bytes);
#endif
}

// Overwrite cache invalidate API of ethos-u-driver
void ethosu_invalidate_dcache(uint32_t *p, size_t bytes)
{
#if (BSP_CFG_DCACHE_ENABLED == 1)
    if(p != NULL)
    {
        SCB_InvalidateDCache_by_Addr(p, (int32_t) bytes);
    }
    else
    {
        SCB_InvalidateDCache();
    }
#else
    FSP_PARAMETER_NOT_USED(p);
    FSP_PARAMETER_NOT_USED(bytes);
#endif
}
