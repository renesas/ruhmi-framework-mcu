/*
 * Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
/**********************************************************************************************************************
 * File Name    : R7KA8P1KF_core0_additional.h
 * Version      : .
 * Description  : .
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * IMPORTANT NOTICE : This version of sample project contains preliminary version of iodefine for MIPI-CSI and VIN module.
 *                    The definition and its usage note are subject to change.
 *********************************************************************************************************************/

#ifndef R7KA8P1KF_CORE0_ADDITIONAL_H__
#define R7KA8P1KF_CORE0_ADDITIONAL_H__

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup Configuration_of_CMSIS
 * @{
 */

/* =========================================================================================================================== */
/* ================                                Interrupt Number Definition                                ================ */
/* =========================================================================================================================== */

/* =========================================================================================================================== */
/* ================                           Processor and Core Peripheral Section                           ================ */
/* =========================================================================================================================== */

/* ==========================  Configuration of the ARM Cortex-M85 Processor and Core Peripherals  =========================== */
 #define __CM85_REV                0x0002U /*!< CM85 Core Revision                                                        */
 #define __NVIC_PRIO_BITS          4       /*!< Number of Bits used for Priority Levels                                   */
 #define __Vendor_SysTickConfig    0       /*!< Set to 1 if different SysTick Config is used                              */
 #define __VTOR_PRESENT            1       /*!< Set to 1 if CPU supports Vector Table Offset Register                     */
 #define __MPU_PRESENT             1       /*!< MPU present                                                               */
 #define __FPU_PRESENT             1       /*!< FPU present                                                               */
 #define __FPU_DP                  0       /*!< Double Precision FPU                                                      */
 #define __DSP_PRESENT             1       /*!< DSP extension present                                                     */
 #define __ICACHE_PRESENT          1       /*!< Instruction Cache present                                                 */
 #define __DCACHE_PRESENT          1       /*!< Data Cache present                                                        */
 #define __SAUREGION_PRESENT       1       /*!< SAU region present                                                        */
 #define __PMU_PRESENT             1       /*!< PMU present                                                               */
 #define __PMU_NUM_EVENTCNT        8       /*!< PMU Event Counters                                                        */

/** @} */ /* End of group Configuration_of_CMSIS */

 #include "core_cm85.h"                    /*!< ARM Cortex-M85 processor and core peripherals                             */

 #ifndef __IM                              /*!< Fallback for older CMSIS versions                                         */
  #define __IM     __I
 #endif
 #ifndef __OM                              /*!< Fallback for older CMSIS versions                                         */
  #define __OM     __O
 #endif
 #ifndef __IOM                             /*!< Fallback for older CMSIS versions                                         */
  #define __IOM    __IO
 #endif

/* ========================================  Start of section using anonymous unions  ======================================== */
 #if defined(__CC_ARM)
  #pragma push
  #pragma anon_unions
 #elif defined(__ICCARM__)
  #pragma language=extended
 #elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
  #pragma clang diagnostic push
  #pragma clang diagnostic ignored "-Wc11-extensions"
  #pragma clang diagnostic ignored "-Wreserved-id-macro"
  #pragma clang diagnostic ignored "-Wgnu-anonymous-struct"
  #pragma clang diagnostic ignored "-Wnested-anon-types"
 #elif defined(__GNUC__)

/* anonymous unions are enabled by default */
 #elif defined(__TMS470__)

/* anonymous unions are enabled by default */
 #elif defined(__TASKING__)
  #pragma warning 586
 #elif defined(__CSMC__)

/* anonymous unions are enabled by default */
 #else
  #warning Not supported compiler type
 #endif

/* =========================================================================================================================== */
/* ================                                           R_VIN                                           ================ */
/* =========================================================================================================================== */

/**
 * @brief Video Input Module (R_VIN)
 */
#if 0
typedef struct                         /*!< (@ 0x40347400) R_VIN Structure                                            */
{
    union
    {
        __IOM uint32_t MC;             /*!< (@ 0x00000000) Main Control Register                                      */

        struct
        {
            __IOM uint32_t ME     : 1; /*!< [0..0] Module Enable                                                      */
            __IOM uint32_t BPS    : 1; /*!< [1..1] Color Space Conversion Bypass Mode                                 */
            uint32_t              : 1;
            __IOM uint32_t IM     : 2; /*!< [4..3] Interlace Mode                                                     */
            uint32_t              : 1;
            __IOM uint32_t EN     : 1; /*!< [6..6] Endian Type                                                        */
            uint32_t              : 7;
            __IOM uint32_t DC     : 2; /*!< [15..14] Dithering Mode Control                                           */
            __IOM uint32_t INF    : 3; /*!< [18..16] Input Interface Format                                           */
            uint32_t              : 1;
            __IOM uint32_t LUTE   : 1; /*!< [20..20] Lookup Table Enable                                              */
            uint32_t              : 1;
            __OM uint32_t ST      : 1; /*!< [22..22] Initialization control at STartup                                */
            uint32_t              : 1;
            __IOM uint32_t DC2    : 1; /*!< [24..24] Dithering mode Control 2                                         */
            __IOM uint32_t YUV444 : 1; /*!< [25..25] YUV444 conversion                                                */
            __IOM uint32_t SCLE   : 1; /*!< [26..26] This bit is used to enable or disable scaling by the
                                        *   UDS.                                                                      */
            uint32_t           : 1;
            __IOM uint32_t CLP : 2;    /*!< [29..28] Pixel Data Clipping                                              */
            uint32_t           : 2;
        } MC_b;
    };

    union
    {
        __IM uint32_t MS;              /*!< (@ 0x00000004) Module Status Register                                     */

        struct
        {
            __IM uint32_t CA  : 1;     /*!< [0..0] Video Capture Active Status                                        */
            __IM uint32_t AV  : 1;     /*!< [1..1] Active Video Status                                                */
            __IM uint32_t FS  : 1;     /*!< [2..2] Field Status                                                       */
            __IM uint32_t FBS : 2;     /*!< [4..3] Frame Buffer Status                                                */
            uint32_t          : 11;
            __IM uint32_t MA  : 1;     /*!< [16..16] External frame Memory capture Active status                      */
            uint32_t          : 2;
            __IM uint32_t FMS : 2;     /*!< [20..19] External Frame Memory buffer Status                              */
            uint32_t          : 11;
        } MS_b;
    };

    union
    {
        __IOM uint32_t FC;             /*!< (@ 0x00000008) Frame Capture Register                                     */

        struct
        {
            uint32_t          : 1;
            __IOM uint32_t CC : 1;     /*!< [1..1] Continuous Frame Capture Mode                                      */
            uint32_t          : 30;
        } FC_b;
    };

    union
    {
        __IOM uint32_t SLPRC;          /*!< (@ 0x0000000C) Start Line Pre-Clip Register                               */

        struct
        {
            __IOM uint32_t SLPRC : 12; /*!< [11..0] Start Line PRe-Clip                                               */
            uint32_t             : 20;
        } SLPRC_b;
    };

    union
    {
        __IOM uint32_t ELPRC;          /*!< (@ 0x00000010) End Line Pre-Clip Register                                 */

        struct
        {
            __IOM uint32_t ELPRC : 12; /*!< [11..0] End Line PRe-Clip                                                 */
            uint32_t             : 20;
        } ELPRC_b;
    };

    union
    {
        __IOM uint32_t SPPRC;          /*!< (@ 0x00000014) Start Pixel Pre-Clip Register                              */

        struct
        {
            __IOM uint32_t SPPRC : 12; /*!< [11..0] Start Pixel Pre-Clip                                              */
            uint32_t             : 20;
        } SPPRC_b;
    };

    union
    {
        __IOM uint32_t EPPRC;          /*!< (@ 0x00000018) End Pixel Pre-Clip Register                                */

        struct
        {
            __IOM uint32_t EPPRC : 12; /*!< [11..0] End Pixel PRe-Clip                                                */
            uint32_t             : 20;
        } EPPRC_b;
    };
    __IM uint32_t RESERVED;

    union
    {
        __IOM uint32_t CSI_IFMD;       /*!< (@ 0x00000020) CSI2 Interface Mode Register                               */

        struct
        {
            __IOM uint32_t VC_SEL : 4; /*!< [3..0] Virtual Channel SELect                                             */
            uint32_t              : 4;
            __IOM uint32_t DT     : 6; /*!< [13..8] Data Type select                                                  */
            uint32_t              : 11;
            __IOM uint32_t DES0   : 1; /*!< [25..25] Data Extension Select                                            */
            uint32_t              : 6;
        } CSI_IFMD_b;
    };

    union
    {
        __IOM uint32_t CSIFLD;          /*!< (@ 0x00000024) Field detection control Register                           */

        struct
        {
            __IOM uint32_t FLD_EN  : 1; /*!< [0..0] FieLD detect ENable                                                */
            uint32_t               : 3;
            __IOM uint32_t FLD_SEL : 2; /*!< [5..4] even FieLD DETect SELect                                           */
            uint32_t               : 10;
            __IOM uint32_t FLD_NUM : 1; /*!< [16..16] even FieLD NUMber setting                                        */
            uint32_t               : 15;
        } CSIFLD_b;
    };
    __IM uint32_t RESERVED1;

    union
    {
        __IOM uint32_t IS;             /*!< (@ 0x0000002C) Image Stride Register                                      */

        struct
        {
            __IOM uint32_t IS : 13;    /*!< [12..0] Image Stride (Setting unit: pixel)                                */
            uint32_t          : 19;
        } IS_b;
    };

    union
    {
        __IOM uint32_t MB1;            /*!< (@ 0x00000030) Memory Base 1 Register                                     */

        struct
        {
            uint32_t           : 7;
            __IOM uint32_t MB1 : 25;   /*!< [31..7] Memory Base Address 1                                             */
        } MB1_b;
    };

    union
    {
        __IOM uint32_t MB2;            /*!< (@ 0x00000034) Memory Base 2 Register                                     */

        struct
        {
            uint32_t           : 7;
            __IOM uint32_t MB2 : 25;   /*!< [31..7] Memory Base Address 2                                             */
        } MB2_b;
    };

    union
    {
        __IOM uint32_t MB3;            /*!< (@ 0x00000038) Memory Base 3 Register                                     */

        struct
        {
            uint32_t           : 7;
            __IOM uint32_t MB3 : 25;   /*!< [31..7] Memory Base Address 3                                             */
        } MB3_b;
    };

    union
    {
        __IM uint32_t LC;              /*!< (@ 0x0000003C) Line Count Register                                        */

        struct
        {
            __IM uint32_t LC : 12;     /*!< [11..0] Line Count                                                        */
            uint32_t         : 20;
        } LC_b;
    };

    union
    {
        __IOM uint32_t IE;                /*!< (@ 0x00000040) Interrupt Enable Register                                  */

        struct
        {
            __IOM uint32_t FOE       : 1; /*!< [0..0] FIFO Overflow Interrupt Enable                                     */
            __IOM uint32_t EFE       : 1; /*!< [1..1] End of Frame Interrupt Enable                                      */
            __IOM uint32_t SIE       : 1; /*!< [2..2] Scanline Interrupt Enable                                          */
            uint32_t                 : 1;
            __IOM uint32_t FIE       : 1; /*!< [4..4] Field Interrupt Enable                                             */
            __IOM uint32_t FME       : 1; /*!< [5..5] Frame Memory write completion interrupt Enable                     */
            uint32_t                 : 2;
            __IOM uint32_t PRCLIPHEE : 1; /*!< [8..8] PRCLIPH Error interrupt Enable                                     */
            __IOM uint32_t PRCLIPVEE : 1; /*!< [9..9] PRCLIPV Error interrupt Enable                                     */
            uint32_t                 : 4;
            __IOM uint32_t ROE       : 1; /*!< [14..14] Response Overflow interrupt Enable                               */
            __IOM uint32_t AREE      : 1; /*!< [15..15] Axi Resp Error interrupt Enable                                  */
            __IOM uint32_t VRE       : 1; /*!< [16..16] VSYNC Deasserting Detect Interrupt Enable                        */
            __IOM uint32_t VFE       : 1; /*!< [17..17] Vsync asserting detect interrupt Enable                          */
            uint32_t                 : 13;
            __IOM uint32_t FIE2      : 1; /*!< [31..31] Field Interrupt Enable 2                                         */
        } IE_b;
    };

    union
    {
        __IOM uint32_t INTS;              /*!< (@ 0x00000044) Interrupt Status Register                                  */

        struct
        {
            __IOM uint32_t FOS       : 1; /*!< [0..0] FIFO Overflow Interrupt Status                                     */
            __IOM uint32_t EFS       : 1; /*!< [1..1] End of Frame Interrupt Status                                      */
            __IOM uint32_t SIS       : 1; /*!< [2..2] Scanline Interrupt Status                                          */
            uint32_t                 : 1;
            __IOM uint32_t FIS       : 1; /*!< [4..4] Field Interrupt Status                                             */
            __IOM uint32_t FMS       : 1; /*!< [5..5] Frame Memory write completion interrupt Status                     */
            uint32_t                 : 2;
            __IOM uint32_t PRCLIPHES : 1; /*!< [8..8] PRCLIPH Error interrupt Status                                     */
            __IOM uint32_t PRCLIPVES : 1; /*!< [9..9] PRCLIPV Error interrupt Status                                     */
            uint32_t                 : 4;
            __IOM uint32_t ROS       : 1; /*!< [14..14] Response Overflow interrupt Status                               */
            __IOM uint32_t ARES      : 1; /*!< [15..15] Axi Resp Error interrupt Status                                  */
            __IOM uint32_t VRS       : 1; /*!< [16..16] VSYNC Deasserting Detect Interrupt Status                        */
            __IOM uint32_t VFS       : 1; /*!< [17..17] VSYNC Asserting Detect Interrupt Status                          */
            uint32_t                 : 13;
            __IOM uint32_t FIS2      : 1; /*!< [31..31] Field Interrupt Status 2                                         */
        } INTS_b;
    };

    union
    {
        __IOM uint32_t SI;             /*!< (@ 0x00000048) Scanline Interrupt Register                                */

        struct
        {
            __IOM uint32_t SI : 12;    /*!< [11..0] Scanline Interrupt Setting                                        */
            uint32_t          : 20;
        } SI_b;
    };
    __IM uint32_t RESERVED2[2];

    union
    {
        __IOM uint32_t MTCSTOP;         /*!< (@ 0x00000054) AXI transfer stop control register                         */

        struct
        {
            __IOM uint32_t STOPREQ : 1; /*!< [0..0] axi forced STOP REQuest                                            */
            __IM uint32_t  STOPACK : 1; /*!< [1..1] for axi forced STOP request, ACKnowledgement                       */
            uint32_t               : 14;
            __IM uint32_t OUTSTAND : 6; /*!< [21..16] OUTSTANDing current number                                       */
            uint32_t               : 10;
        } MTCSTOP_b;
    };

    union
    {
        __IOM uint32_t DMR;            /*!< (@ 0x00000058) Data Mode Register                                         */

        struct
        {
            __IOM uint32_t DTMD   : 2; /*!< [1..0] Data Conversion Mode                                               */
            __IOM uint32_t ABIT   : 1; /*!< [2..2] Alpha Bit                                                          */
            uint32_t              : 1;
            __IOM uint32_t BPSM   : 1; /*!< [4..4] Output Data Byte Swap Mode                                         */
            uint32_t              : 3;
            __IOM uint32_t EXRGB  : 1; /*!< [8..8] Extension RGB Conversion Mode                                      */
            uint32_t              : 2;
            __IOM uint32_t YC_THR : 1; /*!< [11..11] YC Data Through Mode                                             */
            __IOM uint32_t YMODE  : 3; /*!< [14..12] YC Data Transfer Mode                                            */
            uint32_t              : 9;
            __IOM uint32_t A8BIT  : 8; /*!< [31..24] Alpha 8                                                          */
        } DMR_b;
    };
    __IM uint32_t RESERVED3;

    union
    {
        __IOM uint32_t UVAOF;          /*!< (@ 0x00000060) UV Address Offset Register                                 */

        struct
        {
            uint32_t             : 7;
            __IOM uint32_t UVAOF : 25; /*!< [31..7] UV Data Address Offset                                            */
        } UVAOF_b;
    };
    __IM uint32_t RESERVED4[7];

    union
    {
        __IOM uint32_t UDS_CTRL;       /*!< (@ 0x00000080) Scaling Control Registers                                  */

        struct
        {
            uint32_t              : 16;
            __IOM uint32_t NE_BCB : 1; /*!< [16..16] B/Cb Interpolation Method When Bilinear/Nearest Neighbor
                                        *   Interpolation is Selected                                                 */
            __IOM uint32_t NE_GY : 1;  /*!< [17..17] G/Y Interpolation Method When Bilinear/Nearest Neighbor
                                        *   Interpolation is Selected                                                 */
            __IOM uint32_t NE_RCR : 1; /*!< [18..18] R/Cr Interpolation Method When Bilinear/Nearest Neighbor
                                        *   Interpolation is Selected                                                 */
            uint32_t             : 1;
            __IOM uint32_t BC    : 1;  /*!< [20..20] Pixel Component Interpolation Method at Scale-Up/Down            */
            uint32_t             : 7;
            __IOM uint32_t BLADV : 1;  /*!< [28..28] BiLinear or nearest neighbor interpolation characteristic
                                        *   ADVanced mode                                                             */
            uint32_t           : 1;
            __IOM uint32_t AMD : 1;    /*!< [30..30] Advanced MoDe: Pixel Count at Scale-Up                           */
            uint32_t           : 1;
        } UDS_CTRL_b;
    };

    union
    {
        __IOM uint32_t UDS_SCALE;      /*!< (@ 0x00000084) Scaling Factor Registers                                   */

        struct
        {
            __IOM uint32_t VFRAC : 12; /*!< [11..0] Multiplier (Fractional Part) of Vertical Scaling Factor           */
            __IOM uint32_t VMANT : 4;  /*!< [15..12] Multiplier (Integral Part) of Vertical Scaling Factor            */
            __IOM uint32_t HFRAC : 12; /*!< [27..16] Multiplier (Fractional Part) of Horizontal Scaling
                                        *   Factor                                                                    */
            __IOM uint32_t HMANT : 4;  /*!< [31..28] Multiplier (Integral Part) of Horizontal Scaling Factor          */
        } UDS_SCALE_b;
    };
    __IM uint32_t RESERVED5[2];

    union
    {
        __IOM uint32_t UDS_PASS_BWIDTH;  /*!< (@ 0x00000090) Passband Registers                                         */

        struct
        {
            __IOM uint32_t BWIDTH_V : 7; /*!< [6..0] Vertical Signal Passband at Image Scale-Up/Down                    */
            uint32_t                : 9;
            __IOM uint32_t BWIDTH_H : 7; /*!< [22..16] Horizontal Signal Passband at Image Scale-Up/Down                */
            uint32_t                : 9;
        } UDS_PASS_BWIDTH_b;
    };
    __IM uint32_t RESERVED6[4];

    union
    {
        __IOM uint32_t UDS_CLIP_SIZE;     /*!< (@ 0x000000A4) UDS Output Size Clipping Registers                         */

        struct
        {
            __IOM uint32_t CL_VSIZE : 12; /*!< [11..0] Clipping Size of Vertical Pixel Count after Scale-Up/-Down        */
            uint32_t                : 4;
            __IOM uint32_t CL_HSIZE : 12; /*!< [27..16] Clipping Size of Horizontal Pixel Count after Scale-Up/-Down     */
            uint32_t                : 4;
        } UDS_CLIP_SIZE_b;
    };
    __IM uint32_t RESERVED7[22];

    union
    {
        __IOM uint32_t LUTP;            /*!< (@ 0x00000100) Lookup Table Pointer Register                              */

        struct
        {
            __IOM uint32_t LTCRPR : 10; /*!< [9..0] Lookup Table Cr Pointer                                            */
            __IOM uint32_t LTCBPR : 10; /*!< [19..10] Lookup Table Cb Pointer                                          */
            __IOM uint32_t LTYPR  : 10; /*!< [29..20] Lookup Table Y Pointer                                           */
            uint32_t              : 2;
        } LUTP_b;
    };

    union
    {
        __IOM uint32_t LUTD;           /*!< (@ 0x00000104) Lookup Table Data Register                                 */

        struct
        {
            __IOM uint32_t LTCRDT : 8; /*!< [7..0] Lookup Table Cr Data                                               */
            __IOM uint32_t LTCBDT : 8; /*!< [15..8] Lookup Table Cb Data                                              */
            __IOM uint32_t LTYDT  : 8; /*!< [23..16] Lookup Table Y Data                                              */
            uint32_t              : 8;
        } LUTD_b;
    };
    __IM uint32_t RESERVED8[72];

    union
    {
        __IOM uint32_t YCCR1;          /*!< (@ 0x00000228) RGB to Y Calculation Setting Register 1                    */

        struct
        {
            __IOM uint32_t YCLRP : 13; /*!< [12..0] R Multiplication Coefficient for Y Calculation                    */
            uint32_t             : 19;
        } YCCR1_b;
    };

    union
    {
        __IOM uint32_t YCCR2;          /*!< (@ 0x0000022C) RGB to Y Calculation Setting Register 2                    */

        struct
        {
            __IOM uint32_t YCLGP : 13; /*!< [12..0] G Multiplication Coefficient for Y Calculation                    */
            uint32_t             : 3;
            __IOM uint32_t YCLBP : 13; /*!< [28..16] B Multiplication Coefficient for Y Calculation                   */
            uint32_t             : 3;
        } YCCR2_b;
    };

    union
    {
        __IOM uint32_t YCCR3;           /*!< (@ 0x00000230) RGB to Y Calculation Setting Register 3                    */

        struct
        {
            __IOM uint32_t YCLAP  : 12; /*!< [11..0] Y Calculation Data Normalized Additional Value                    */
            uint32_t              : 11;
            __IOM uint32_t YCLHEN : 1;  /*!< [23..23] Y Calculation Shift Down Result Round-Off Enable                 */
            __IOM uint32_t YCLSFT : 5;  /*!< [28..24] Y Calculation Shift Down Volume                                  */
            uint32_t              : 3;
        } YCCR3_b;
    };

    union
    {
        __IOM uint32_t CBCCR1;          /*!< (@ 0x00000234) RGB to Cb Calculation Setting Register 1                   */

        struct
        {
            __IOM uint32_t CBCLRP : 13; /*!< [12..0] R Multiplication Coefficient for Cb Calculation                   */
            uint32_t              : 19;
        } CBCCR1_b;
    };

    union
    {
        __IOM uint32_t CBCCR2;          /*!< (@ 0x00000238) RGB to Cb Calculation Setting Register 2                   */

        struct
        {
            __IOM uint32_t CBCLGP : 13; /*!< [12..0] G Multiplication Coefficient for Cb Calculation                   */
            uint32_t              : 3;
            __IOM uint32_t CBCLBP : 13; /*!< [28..16] B Multiplication Coefficient for Cb Calculation                  */
            uint32_t              : 3;
        } CBCCR2_b;
    };

    union
    {
        __IOM uint32_t CBCCR3;           /*!< (@ 0x0000023C) RGB to Cb Calculation Setting Register 3                   */

        struct
        {
            __IOM uint32_t CBCLAP  : 12; /*!< [11..0] Cb Calculation Data Normalized Additional Value                   */
            uint32_t               : 11;
            __IOM uint32_t CBCLHEN : 1;  /*!< [23..23] Cb Calculation Shift Down Result Round-Off Enable                */
            __IOM uint32_t CBCLSFT : 5;  /*!< [28..24] Cb Calculation Shift Down Volume                                 */
            uint32_t               : 3;
        } CBCCR3_b;
    };

    union
    {
        __IOM uint32_t CRCCR1;          /*!< (@ 0x00000240) RGB to Cr Calculation Setting Register 1                   */

        struct
        {
            __IOM uint32_t CRCLRP : 13; /*!< [12..0] R Multiplication Coefficient for Cr Calculation                   */
            uint32_t              : 19;
        } CRCCR1_b;
    };

    union
    {
        __IOM uint32_t CRCCR2;          /*!< (@ 0x00000244) RGB to Cr Calculation Setting Register 2                   */

        struct
        {
            __IOM uint32_t CRCLGP : 13; /*!< [12..0] G Multiplication Coefficient for Cr Calculation                   */
            uint32_t              : 3;
            __IOM uint32_t CRCLBP : 13; /*!< [28..16] B Multiplication Coefficient for Cr Calculation                  */
            uint32_t              : 3;
        } CRCCR2_b;
    };

    union
    {
        __IOM uint32_t CRCCR3;           /*!< (@ 0x00000248) RGB to Cr Calculation Setting Register 3                   */

        struct
        {
            __IOM uint32_t CRCLAP  : 12; /*!< [11..0] Cr Calculation Data Normalized Additional Value                   */
            uint32_t               : 11;
            __IOM uint32_t CRCLHEN : 1;  /*!< [23..23] Cr Calculation Shift Down Result Round-Off Enable                */
            __IOM uint32_t CRCLSFT : 5;  /*!< [28..24] Cr Calculation Shift Down Volume                                 */
            uint32_t               : 3;
        } CRCCR3_b;
    };
    __IM uint32_t RESERVED9[45];

    union
    {
        __IOM uint32_t CSCE1;          /*!< (@ 0x00000300) YC to RGB Calculation Setting Extension Register
                                        *                  1                                                          */

        struct
        {
            __IOM uint32_t YMUL2 : 14; /*!< [13..0] Y Multiplication Coefficient 2 for RGB Calculation                */
            uint32_t             : 2;
            __IOM uint32_t ROUND : 1;  /*!< [16..16] ROUND off enable                                                 */
            uint32_t             : 15;
        } CSCE1_b;
    };

    union
    {
        __IOM uint32_t CSCE2;          /*!< (@ 0x00000304) YC to RGB Calculation Setting Extension Register
                                        *                  2                                                          */

        struct
        {
            __IOM uint32_t CSUB2 : 12; /*!< [11..0] CbCr Subtraction Coefficient 2 for RGB Calculation                */
            uint32_t             : 4;
            __IOM uint32_t YSUB2 : 12; /*!< [27..16] Y Subtraction Coefficient 2 for RGB Calculation                  */
            uint32_t             : 4;
        } CSCE2_b;
    };

    union
    {
        __IOM uint32_t CSCE3;            /*!< (@ 0x00000308) YC to RGB Calculation Setting Extension Register
                                          *                  3                                                          */

        struct
        {
            __IOM uint32_t GCRMUL2 : 14; /*!< [13..0] Cr Multiplication Coefficient 2 for G Calculation                 */
            uint32_t               : 2;
            __IOM uint32_t RCRMUL2 : 14; /*!< [29..16] Cr Multiplication Coefficient 2 for R Calculation                */
            uint32_t               : 2;
        } CSCE3_b;
    };

    union
    {
        __IOM uint32_t CSCE4;            /*!< (@ 0x0000030C) YC to RGB Calculation Setting Extension Register
                                          *                  4                                                          */

        struct
        {
            __IOM uint32_t BCBMUL2 : 14; /*!< [13..0] Cb Multiplication Coefficient 2 for B Calculation                 */
            uint32_t               : 2;
            __IOM uint32_t GCBMUL2 : 14; /*!< [29..16] Cb Multiplication Coefficient 2 for G Calculation                */
            uint32_t               : 2;
        } CSCE4_b;
    };
} R_VIN_Type;                            /*!< Size = 784 (0x310) */
#endif
/* =========================================================================================================================== */
/* ================                                        R_MIPI_CSI                                         ================ */
/* =========================================================================================================================== */
#if 0
/**
 * @brief MIPI_CSI Register area (R_MIPI_CSI)
 */

typedef struct                         /*!< (@ 0x40347000) R_MIPI_CSI Structure                                       */
{
    union
    {
        __IM uint32_t MCG;             /*!< (@ 0x00000000) Module Configuration Register                              */

        struct
        {
            __IM uint32_t VER  : 4;    /*!< [3..0] VERsion of this ip                                                 */
            uint32_t           : 4;
            __IM uint32_t SDLN : 4;    /*!< [11..8] Number of Supported Data Lanes                                    */
            uint32_t           : 4;
            __IM uint32_t GSNM : 8;    /*!< [23..16] NuMber of Generic Short packt FIFO                               */
            uint32_t           : 8;
        } MCG_b;
    };
    __IM uint32_t RESERVED[3];

    union
    {
        __IOM uint32_t MCT0;           /*!< (@ 0x00000010) Module Control Register 0                                  */

        struct
        {
            __IOM uint32_t VDLN   : 4; /*!< [3..0] Numer of Valid Data Lanes                                          */
            uint32_t              : 12;
            __IOM uint32_t ZLMD   : 1; /*!< [16..16] Zero Length long packet output MoDe                              */
            __IOM uint32_t EDMD   : 1; /*!< [17..17] ErrframeData notification MoDe                                   */
            uint32_t              : 1;
            __IOM uint32_t RVMD   : 1; /*!< [19..19] ReserVed packet reception MoDe                                   */
            __IOM uint32_t GRMD   : 1; /*!< [20..20] Generic csi-2 Rule MoDe                                          */
            uint32_t              : 3;
            __IOM uint32_t ECCV13 : 1; /*!< [24..24] ECC check csi-2 Ver 1.3 mode                                     */
            __IOM uint32_t LFSREN : 1; /*!< [25..25] LFSR Enable mode                                                 */
            uint32_t              : 6;
        } MCT0_b;
    };
    __IM uint32_t RESERVED1;

    union
    {
        __IOM uint32_t MCT2;           /*!< (@ 0x00000018) Module Control Register 2                                  */

        struct
        {
            __IOM uint32_t FRRCLK : 9; /*!< [8..0] clock FRequency Rate to judge packet reception end                 */
            uint32_t              : 7;
            __IOM uint32_t FRRSKW : 9; /*!< [24..16] clock FRequency Rate to adjust data lane SKew                    */
            uint32_t              : 7;
        } MCT2_b;
    };

    union
    {
        __IOM uint32_t MCT3;           /*!< (@ 0x0000001C) Module Control Register 3                                  */

        struct
        {
            __IOM uint32_t RXEN : 1;   /*!< [0..0] RX (reception) Enable                                              */
            uint32_t            : 31;
        } MCT3_b;
    };
    __IM uint32_t RESERVED2[2];

    union
    {
        __OM uint32_t RTCT;            /*!< (@ 0x00000028) Reset Control Register                                     */

        struct
        {
            __OM uint32_t VSRST : 1;   /*!< [0..0] Video pixel interface Software ReSeT                               */
            uint32_t            : 31;
        } RTCT_b;
    };

    union
    {
        __IM uint32_t RTST;            /*!< (@ 0x0000002C) Reset Status Register                                      */

        struct
        {
            __IM uint32_t VSRSTS : 1;  /*!< [0..0] Video pixel interface Software ReSeT Status                        */
            uint32_t             : 31;
        } RTST_b;
    };
    __IM uint32_t RESERVED3[4];

    union
    {
        __IOM uint32_t EPCT;           /*!< (@ 0x00000040) EPD Option Control Register                                */

        struct
        {
            __IOM uint32_t SLP   : 15; /*!< [14..0] Long Packet Spacers                                               */
            __IOM uint32_t EPDOP : 1;  /*!< [15..15] EPD OPtion select                                                */
            __IOM uint32_t SSP   : 15; /*!< [30..16] epd Short Packet Spacers                                         */
            __IOM uint32_t EPDEN : 1;  /*!< [31..31] ENable EPD operation                                             */
        } EPCT_b;
    };

    union
    {
        __IOM uint32_t EMCT;           /*!< (@ 0x00000044) EPD Misc Option Control Register                           */

        struct
        {
            uint32_t              : 4;
            __IOM uint32_t VLSIEN : 2; /*!< [5..4] ENable Variable-Length Spacer Insertions                           */
            __IOM uint32_t EOTPEN : 1; /*!< [6..6] ENable EOTP                                                        */
            uint32_t              : 25;
        } EMCT_b;
    };
    __IM uint32_t RESERVED4[2];

    union
    {
        __IM uint32_t MIST;            /*!< (@ 0x00000050) Module Interrupt Status Register                           */

        struct
        {
            __IM uint32_t DL0S  : 1;   /*!< [0..0] interrupt Status related to Data Lane 0                            */
            __IM uint32_t DL1S  : 1;   /*!< [1..1] interrupt Status related to Data Lane 1                            */
            uint32_t            : 6;
            __IM uint32_t PMS   : 1;   /*!< [8..8] interrupt Status related to Power Management                       */
            __IM uint32_t GSTS  : 1;   /*!< [9..9] interrupt Status related to Generic ShorT packet                   */
            __IM uint32_t RXS   : 1;   /*!< [10..10] interrupt Status related to RX (Reception)                       */
            uint32_t            : 5;
            __IM uint32_t VC0S  : 1;   /*!< [16..16] interrupt Status related to Vitrtual Channel 0                   */
            __IM uint32_t VC1S  : 1;   /*!< [17..17] interrupt Status related to Vitrtual Channel 1                   */
            __IM uint32_t VC2S  : 1;   /*!< [18..18] interrupt Status related to Vitrtual Channel 2                   */
            __IM uint32_t VC3S  : 1;   /*!< [19..19] interrupt Status related to Vitrtual Channel 3                   */
            __IM uint32_t VC4S  : 1;   /*!< [20..20] interrupt Status related to Vitrtual Channel 4                   */
            __IM uint32_t VC5S  : 1;   /*!< [21..21] interrupt Status related to Vitrtual Channel 5                   */
            __IM uint32_t VC6S  : 1;   /*!< [22..22] interrupt Status related to Vitrtual Channel 6                   */
            __IM uint32_t VC7S  : 1;   /*!< [23..23] interrupt Status related to Vitrtual Channel 7                   */
            __IM uint32_t VC8S  : 1;   /*!< [24..24] interrupt Status related to Vitrtual Channel 8                   */
            __IM uint32_t VC9S  : 1;   /*!< [25..25] interrupt Status related to Vitrtual Channel 9                   */
            __IM uint32_t VC10S : 1;   /*!< [26..26] interrupt Status related to Vitrtual Channel 10                  */
            __IM uint32_t VC11S : 1;   /*!< [27..27] interrupt Status related to Vitrtual Channel 11                  */
            __IM uint32_t VC12S : 1;   /*!< [28..28] interrupt Status related to Vitrtual Channel 12                  */
            __IM uint32_t VC13S : 1;   /*!< [29..29] interrupt Status related to Vitrtual Channel 13                  */
            __IM uint32_t VC14S : 1;   /*!< [30..30] interrupt Status related to Vitrtual Channel 14                  */
            __IM uint32_t VC15S : 1;   /*!< [31..31] interrupt Status related to Vitrtual Channel 15                  */
        } MIST_b;
    };
    __IM uint32_t RESERVED5[3];

    union
    {
        __IOM uint32_t DTEL;           /*!< (@ 0x00000060) Receive Data Type Enable Low Register                      */

        struct
        {
            __IOM uint32_t DTEN : 32;  /*!< [31..0] Data Type ENable (DT = 0x00 to 0x1F)                              */
        } DTEL_b;
    };

    union
    {
        __IOM uint32_t DTEH;           /*!< (@ 0x00000064) Receive Data Type Enable High Register                     */

        struct
        {
            __IOM uint32_t DTEN : 32;  /*!< [31..0] Data Type ENable (DT = 0x20 to 0x3F)                              */
        } DTEH_b;
    };
    __IM uint32_t RESERVED6[2];

    union
    {
        __IM uint32_t RXST;            /*!< (@ 0x00000070) Receive Status Register                                    */

        struct
        {
            __IM uint32_t FRM0    : 1; /*!< [0..0] FRaMe of virtual channel 0 active                                  */
            __IM uint32_t FRM1    : 1; /*!< [1..1] FRaMe of virtual channel 1 active                                  */
            __IM uint32_t FRM2    : 1; /*!< [2..2] FRaMe of virtual channel 2 active                                  */
            __IM uint32_t FRM3    : 1; /*!< [3..3] FRaMe of virtual channel 3 active                                  */
            __IM uint32_t FRM4    : 1; /*!< [4..4] FRaMe of virtual channel 4 active                                  */
            __IM uint32_t FRM5    : 1; /*!< [5..5] FRaMe of virtual channel 5 active                                  */
            __IM uint32_t FRM6    : 1; /*!< [6..6] FRaMe of virtual channel 6 active                                  */
            __IM uint32_t FRM7    : 1; /*!< [7..7] FRaMe of virtual channel 7 active                                  */
            __IM uint32_t FRM8    : 1; /*!< [8..8] FRaMe of virtual channel 8 active                                  */
            __IM uint32_t FRM9    : 1; /*!< [9..9] FRaMe of virtual channel 9 active                                  */
            __IM uint32_t FRM10   : 1; /*!< [10..10] FRaMe of virtual channel 10 active                               */
            __IM uint32_t FRM11   : 1; /*!< [11..11] FRaMe of virtual channel 11 active                               */
            __IM uint32_t FRM12   : 1; /*!< [12..12] FRaMe of virtual channel 12 active                               */
            __IM uint32_t FRM13   : 1; /*!< [13..13] FRaMe of virtual channel 13 active                               */
            __IM uint32_t FRM14   : 1; /*!< [14..14] FRaMe of virtual channel 14 active                               */
            __IM uint32_t FRM15   : 1; /*!< [15..15] FRaMe of virtual channel 15 active                               */
            __IM uint32_t RACT    : 1; /*!< [16..16] Rx (Reception) ACTive status                                     */
            __IM uint32_t RACTDET : 1; /*!< [17..17] Rx (Reception) ACTive DETect                                     */
            uint32_t              : 14;
        } RXST_b;
    };

    union
    {
        __OM uint32_t RXSC;            /*!< (@ 0x00000074) Receive Status Clear Register                              */

        struct
        {
            uint32_t               : 17;
            __OM uint32_t RACTDETC : 1; /*!< [17..17] Rx (Reception) ACTive DETect status Clear                        */
            uint32_t               : 14;
        } RXSC_b;
    };

    union
    {
        __IOM uint32_t RXIE;           /*!< (@ 0x00000078) Receive Interrupt Enable Register                          */

        struct
        {
            uint32_t                : 17;
            __IOM uint32_t RACTDETE : 1; /*!< [17..17] Rx (Reception) ACTive DETect interrupt Enable                    */
            uint32_t                : 14;
        } RXIE_b;
    };
    __IM uint32_t RESERVED7;

    union
    {
        __IM uint32_t DLST0;           /*!< (@ 0x00000080) Data Lane (N) Status Register                              */

        struct
        {
            __IM uint32_t ESH : 1;     /*!< [0..0] ErrSotHs detect on data lane (N) status                            */
            __IM uint32_t ESS : 1;     /*!< [1..1] ErrSotSynchs detect on data lane (N) status                        */
            __IM uint32_t ECT : 1;     /*!< [2..2] ErrConTrol detect on data lane (N) status                          */
            __IM uint32_t EES : 1;     /*!< [3..3] ErrESc detect on data lane (N) status                              */
            uint32_t          : 12;
            __IM uint32_t EUL : 1;     /*!< [16..16] Exit from ULps detect on data lane (N) status                    */
            __IM uint32_t RUL : 1;     /*!< [17..17] entry to ULps detect on data lane (N) status                     */
            uint32_t          : 6;
            __IM uint32_t ULP : 1;     /*!< [24..24] rxULPsesc of data lane (N) status                                */
            uint32_t          : 7;
        } DLST0_b;
    };

    union
    {
        __OM uint32_t DLSC0;           /*!< (@ 0x00000084) Data Lane (N) Status Clear Register                        */

        struct
        {
            __OM uint32_t ESHC : 1;    /*!< [0..0] ErrSotHs detect on data lane (N) status Clear                      */
            __OM uint32_t ESSC : 1;    /*!< [1..1] ErrSotSynchs detect on data lane (N) status Clear                  */
            __OM uint32_t ECTC : 1;    /*!< [2..2] ErrConTrol detect on data lane (N) status Clear                    */
            __OM uint32_t EESC : 1;    /*!< [3..3] ErrESc detect on data lane (N) status Clear                        */
            uint32_t           : 12;
            __OM uint32_t EULC : 1;    /*!< [16..16] Exit from ULps detect on data lane (N) status Clear              */
            __OM uint32_t RULC : 1;    /*!< [17..17] Entry to ULps detect on data lane (N) status Clear               */
            uint32_t           : 14;
        } DLSC0_b;
    };

    union
    {
        __IOM uint32_t DLIE0;          /*!< (@ 0x00000088) Data Lane (N) Interrupt Enable Register                    */

        struct
        {
            __IOM uint32_t ESHE : 1;   /*!< [0..0] ErrSotHs detect on data lane (N) interrupt Enable                  */
            __IOM uint32_t ESSE : 1;   /*!< [1..1] ErrSotSynchs detect on data lane (N) interrupt Enable              */
            __IOM uint32_t ECTE : 1;   /*!< [2..2] ErrConTrol detect on data lane (N) interrupt Enable                */
            __IOM uint32_t EESE : 1;   /*!< [3..3] ErrESc detect on data lane (N) interrupt Enable                    */
            uint32_t            : 12;
            __IOM uint32_t EULE : 1;   /*!< [16..16] Exit to ULps detect on data lane (N) interrupt Enable            */
            __IOM uint32_t RULE : 1;   /*!< [17..17] Entry to ULps detect on data lane (N) interrupt Enable           */
            uint32_t            : 14;
        } DLIE0_b;
    };
    __IM uint32_t RESERVED8;

    union
    {
        __IM uint32_t DLST1;           /*!< (@ 0x00000090) Data Lane (N) Status Register                              */

        struct
        {
            __IM uint32_t ESH : 1;     /*!< [0..0] ErrSotHs detect on data lane (N) status                            */
            __IM uint32_t ESS : 1;     /*!< [1..1] ErrSotSynchs detect on data lane (N) status                        */
            __IM uint32_t ECT : 1;     /*!< [2..2] ErrConTrol detect on data lane (N) status                          */
            __IM uint32_t EES : 1;     /*!< [3..3] ErrESc detect on data lane (N) status                              */
            uint32_t          : 12;
            __IM uint32_t EUL : 1;     /*!< [16..16] Exit from ULps detect on data lane (N) status                    */
            __IM uint32_t RUL : 1;     /*!< [17..17] entry to ULps detect on data lane (N) status                     */
            uint32_t          : 6;
            __IM uint32_t ULP : 1;     /*!< [24..24] rxULPsesc of data lane (N) status                                */
            uint32_t          : 7;
        } DLST1_b;
    };

    union
    {
        __OM uint32_t DLSC1;           /*!< (@ 0x00000094) Data Lane (N) Status Clear Register                        */

        struct
        {
            __OM uint32_t ESHC : 1;    /*!< [0..0] ErrSotHs detect on data lane (N) status Clear                      */
            __OM uint32_t ESSC : 1;    /*!< [1..1] ErrSotSynchs detect on data lane (N) status Clear                  */
            __OM uint32_t ECTC : 1;    /*!< [2..2] ErrConTrol detect on data lane (N) status Clear                    */
            __OM uint32_t EESC : 1;    /*!< [3..3] ErrESc detect on data lane (N) status Clear                        */
            uint32_t           : 12;
            __OM uint32_t EULC : 1;    /*!< [16..16] Exit from ULps detect on data lane (N) status Clear              */
            __OM uint32_t RULC : 1;    /*!< [17..17] Entry to ULps detect on data lane (N) status Clear               */
            uint32_t           : 14;
        } DLSC1_b;
    };

    union
    {
        __IOM uint32_t DLIE1;          /*!< (@ 0x00000098) Data Lane (N) Interrupt Enable Register                    */

        struct
        {
            __IOM uint32_t ESHE : 1;   /*!< [0..0] ErrSotHs detect on data lane (N) interrupt Enable                  */
            __IOM uint32_t ESSE : 1;   /*!< [1..1] ErrSotSynchs detect on data lane (N) interrupt Enable              */
            __IOM uint32_t ECTE : 1;   /*!< [2..2] ErrConTrol detect on data lane (N) interrupt Enable                */
            __IOM uint32_t EESE : 1;   /*!< [3..3] ErrESc detect on data lane (N) interrupt Enable                    */
            uint32_t            : 12;
            __IOM uint32_t EULE : 1;   /*!< [16..16] Exit to ULps detect on data lane (N) interrupt Enable            */
            __IOM uint32_t RULE : 1;   /*!< [17..17] Entry to ULps detect on data lane (N) interrupt Enable           */
            uint32_t            : 14;
        } DLIE1_b;
    };
    __IM uint32_t RESERVED9[25];

    union
    {
        __IM uint32_t VCST0;           /*!< (@ 0x00000100) Virtual Channel (M) Status Register                        */

        struct
        {
            __IM uint32_t MLF : 1;     /*!< [0..0] MaLFormed packet with virutal channel (M) detect status            */
            __IM uint32_t ECD : 1;     /*!< [1..1] ECc 2-bit (Double) error packet with virutal channel
                                        *   (M) Detect status                                                         */
            __IM uint32_t CRC : 1;     /*!< [2..2] CRC error packet with virtual channel (M) detect status            */
            __IM uint32_t IDE : 1;     /*!< [3..3] ErrID packet with virtual channel (M) detect status                */
            __IM uint32_t WCE : 1;     /*!< [4..4] Word Count Error packet with virtual channel (M) detect
                                        *   status                                                                    */
            __IM uint32_t ECC : 1;     /*!< [5..5] ECc 1-bit error (Corrected) packet with virtual channel
                                        *   (M) detect status                                                         */
            __IM uint32_t ECN : 1;     /*!< [6..6] ECc No-error packet with virtual channel (M) detect status         */
            uint32_t          : 1;
            __IM uint32_t FRS : 1;     /*!< [8..8] errFRameSync of virtual channel (M) detect status                  */
            __IM uint32_t FRD : 1;     /*!< [9..9] errFRameData of virtual channel (M) detect status                  */
            uint32_t          : 6;
            __IM uint32_t OVF : 1;     /*!< [16..16] generic short packet with virtual channel (M) discard
                                        *   by fifo OVerFlow status                                                   */
            uint32_t          : 7;
            __IM uint32_t FSR : 1;     /*!< [24..24] Frame Start packet with virtual channel (M) Reception
                                        *   status                                                                    */
            __IM uint32_t FER : 1;     /*!< [25..25] Frame End packet with virtual channel (M) Reception
                                        *   status                                                                    */
            __IM uint32_t LSR : 1;     /*!< [26..26] Line Start packet with virtual channel (M) Reception
                                        *   status                                                                    */
            __IM uint32_t LER : 1;     /*!< [27..27] Line End packet with virtual channel (M) Reception
                                        *   status                                                                    */
            __IM uint32_t ETR : 1;     /*!< [28..28] EoTp packet with virtual channel (M) Reception status            */
            uint32_t          : 3;
        } VCST0_b;
    };

    union
    {
        __OM uint32_t VCSC0;           /*!< (@ 0x00000104) Virtual Channel (M) Status Clear Register                  */

        struct
        {
            __OM uint32_t MLFC : 1;    /*!< [0..0] MaLFormed packet with virutal channel (M) detect status
                                        *   Clear                                                                     */
            __OM uint32_t ECDC : 1;    /*!< [1..1] ECc 2-bit (Double) error packet with virutal channel
                                        *   (M) Detect status Clear                                                   */
            __OM uint32_t CRCC : 1;    /*!< [2..2] CRC error packet with virtual channel (M) detect status
                                        *   Clear                                                                     */
            __OM uint32_t IDEC : 1;    /*!< [3..3] ErrID packet with virtual channel (M) detect status Clear          */
            __OM uint32_t WCEC : 1;    /*!< [4..4] Word Count Error packet with virtual channel (M) detect
                                        *   status Clear                                                              */
            __OM uint32_t ECCC : 1;    /*!< [5..5] ECc 1-bit error (Corrected) packet with virtual channel
                                        *   (M) detect status Clear                                                   */
            __OM uint32_t ECNC : 1;    /*!< [6..6] ECc No-error packet with virtual channel (M) detect status
                                        *   Clear                                                                     */
            uint32_t            : 1;
            __OM uint32_t FRSC  : 1;   /*!< [8..8] errFRameSync of virtual channel (M) detect status Clear            */
            __OM uint32_t FRDC  : 1;   /*!< [9..9] errFRameData of virtual channel (M) detect status Clear            */
            uint32_t            : 4;
            __OM uint32_t AMLFC : 1;   /*!< [14..14] MaLFormed packet with any virutal channels detect status
                                        *   Clear                                                                     */
            __OM uint32_t AECDC : 1;   /*!< [15..15] ECc 2-bit (Double) error packet with any virutal channels
                                        *   Detect status Clear                                                       */
            __OM uint32_t OVFC : 1;    /*!< [16..16] generic short packet with virtual channel (M) discard
                                        *   by fifo OVerFlow status Clear                                             */
            uint32_t           : 7;
            __OM uint32_t FSRC : 1;    /*!< [24..24] Frame Start packet with virtual channel (M) Reception
                                        *   status Clear                                                              */
            __OM uint32_t FERC : 1;    /*!< [25..25] Frame End packet with virtual channel (M) Reception
                                        *   status Clear                                                              */
            __OM uint32_t LSRC : 1;    /*!< [26..26] Line Start packet with virtual channel (M) Reception
                                        *   status Clear                                                              */
            __OM uint32_t LERC : 1;    /*!< [27..27] Line End packet with virtual channel (M) Reception
                                        *   status Clear                                                              */
            __OM uint32_t ETRC : 1;    /*!< [28..28] EoTp packet with virtual channel (M) Reception status
                                        *   Clear                                                                     */
            uint32_t : 3;
        } VCSC0_b;
    };

    union
    {
        __IOM uint32_t VCIE0;          /*!< (@ 0x00000108) Virtual Channel (M) Interrupt Enable Register              */

        struct
        {
            __IOM uint32_t MLFE : 1;   /*!< [0..0] MaLFormed packet with virutal channel (M) detect interrupt
                                        *   Enable                                                                    */
            __IOM uint32_t ECDE : 1;   /*!< [1..1] ECc 2-bit (Double) error packet with virutal channel
                                        *   (M) Detect interrupt Enable                                               */
            __IOM uint32_t CRCE : 1;   /*!< [2..2] CRC error packet with virtual channel (M) detect interrupt
                                        *   Enable                                                                    */
            __IOM uint32_t IDEE : 1;   /*!< [3..3] ErrID packet with virtual channel (M) detect interrupt
                                        *   Enable                                                                    */
            __IOM uint32_t WCEE : 1;   /*!< [4..4] Word Count Error packet with virtual channel (M) detect
                                        *   interrupt Enable                                                          */
            __IOM uint32_t ECCE : 1;   /*!< [5..5] ECc 1-bit error (Corrected) packet with virtual channel
                                        *   (M) detect interrupt Enable                                               */
            __IOM uint32_t ECNE : 1;   /*!< [6..6] ECc No-error packet with virtual channel (M) detect interrupt
                                        *   Enable                                                                    */
            uint32_t            : 1;
            __IOM uint32_t FRSE : 1;   /*!< [8..8] errFRameSync of virtual channel (M) detect interrupt
                                        *   Enable                                                                    */
            __IOM uint32_t FRDE : 1;   /*!< [9..9] errFRameData of virtual channel (M) detect interrupt
                                        *   Enable                                                                    */
            uint32_t            : 6;
            __IOM uint32_t OVFE : 1;   /*!< [16..16] generic short packet with virtual channel (M) discard
                                        *   by fifo OVerFlow interrupt Enable                                         */
            uint32_t            : 7;
            __IOM uint32_t FSRE : 1;   /*!< [24..24] Frame Start packet with virtual channel (M) Reception
                                        *   interrupt Enable                                                          */
            __IOM uint32_t FERE : 1;   /*!< [25..25] Frame End packet with virtual channel (M) Reception
                                        *   interrupt Enable                                                          */
            __IOM uint32_t LSRE : 1;   /*!< [26..26] Line Start packet with virtual channel (M) Reception
                                        *   interrupt Enable                                                          */
            __IOM uint32_t LERE : 1;   /*!< [27..27] Line End packet with virtual channel (M) Reception
                                        *   interrupt Enable                                                          */
            __IOM uint32_t ETRE : 1;   /*!< [28..28] EoTp packet with virtual channel (M) Reception interrupt
                                        *   Enable                                                                    */
            uint32_t : 3;
        } VCIE0_b;
    };
    __IM uint32_t RESERVED10;

    union
    {
        __IM uint32_t VCST1;           /*!< (@ 0x00000110) Virtual Channel (M) Status Register                        */

        struct
        {
            __IM uint32_t MLF : 1;     /*!< [0..0] MaLFormed packet with virutal channel (M) detect status            */
            __IM uint32_t ECD : 1;     /*!< [1..1] ECc 2-bit (Double) error packet with virutal channel
                                        *   (M) Detect status                                                         */
            __IM uint32_t CRC : 1;     /*!< [2..2] CRC error packet with virtual channel (M) detect status            */
            __IM uint32_t IDE : 1;     /*!< [3..3] ErrID packet with virtual channel (M) detect status                */
            __IM uint32_t WCE : 1;     /*!< [4..4] Word Count Error packet with virtual channel (M) detect
                                        *   status                                                                    */
            __IM uint32_t ECC : 1;     /*!< [5..5] ECc 1-bit error (Corrected) packet with virtual channel
                                        *   (M) detect status                                                         */
            __IM uint32_t ECN : 1;     /*!< [6..6] ECc No-error packet with virtual channel (M) detect status         */
            uint32_t          : 1;
            __IM uint32_t FRS : 1;     /*!< [8..8] errFRameSync of virtual channel (M) detect status                  */
            __IM uint32_t FRD : 1;     /*!< [9..9] errFRameData of virtual channel (M) detect status                  */
            uint32_t          : 6;
            __IM uint32_t OVF : 1;     /*!< [16..16] generic short packet with virtual channel (M) discard
                                        *   by fifo OVerFlow status                                                   */
            uint32_t          : 7;
            __IM uint32_t FSR : 1;     /*!< [24..24] Frame Start packet with virtual channel (M) Reception
                                        *   status                                                                    */
            __IM uint32_t FER : 1;     /*!< [25..25] Frame End packet with virtual channel (M) Reception
                                        *   status                                                                    */
            __IM uint32_t LSR : 1;     /*!< [26..26] Line Start packet with virtual channel (M) Reception
                                        *   status                                                                    */
            __IM uint32_t LER : 1;     /*!< [27..27] Line End packet with virtual channel (M) Reception
                                        *   status                                                                    */
            __IM uint32_t ETR : 1;     /*!< [28..28] EoTp packet with virtual channel (M) Reception status            */
            uint32_t          : 3;
        } VCST1_b;
    };

    union
    {
        __OM uint32_t VCSC1;           /*!< (@ 0x00000114) Virtual Channel (M) Status Clear Register                  */

        struct
        {
            __OM uint32_t MLFC : 1;    /*!< [0..0] MaLFormed packet with virutal channel (M) detect status
                                        *   Clear                                                                     */
            __OM uint32_t ECDC : 1;    /*!< [1..1] ECc 2-bit (Double) error packet with virutal channel
                                        *   (M) Detect status Clear                                                   */
            __OM uint32_t CRCC : 1;    /*!< [2..2] CRC error packet with virtual channel (M) detect status
                                        *   Clear                                                                     */
            __OM uint32_t IDEC : 1;    /*!< [3..3] ErrID packet with virtual channel (M) detect status Clear          */
            __OM uint32_t WCEC : 1;    /*!< [4..4] Word Count Error packet with virtual channel (M) detect
                                        *   status Clear                                                              */
            __OM uint32_t ECCC : 1;    /*!< [5..5] ECc 1-bit error (Corrected) packet with virtual channel
                                        *   (M) detect status Clear                                                   */
            __OM uint32_t ECNC : 1;    /*!< [6..6] ECc No-error packet with virtual channel (M) detect status
                                        *   Clear                                                                     */
            uint32_t            : 1;
            __OM uint32_t FRSC  : 1;   /*!< [8..8] errFRameSync of virtual channel (M) detect status Clear            */
            __OM uint32_t FRDC  : 1;   /*!< [9..9] errFRameData of virtual channel (M) detect status Clear            */
            uint32_t            : 4;
            __OM uint32_t AMLFC : 1;   /*!< [14..14] MaLFormed packet with any virutal channels detect status
                                        *   Clear                                                                     */
            __OM uint32_t AECDC : 1;   /*!< [15..15] ECc 2-bit (Double) error packet with any virutal channels
                                        *   Detect status Clear                                                       */
            __OM uint32_t OVFC : 1;    /*!< [16..16] generic short packet with virtual channel (M) discard
                                        *   by fifo OVerFlow status Clear                                             */
            uint32_t           : 7;
            __OM uint32_t FSRC : 1;    /*!< [24..24] Frame Start packet with virtual channel (M) Reception
                                        *   status Clear                                                              */
            __OM uint32_t FERC : 1;    /*!< [25..25] Frame End packet with virtual channel (M) Reception
                                        *   status Clear                                                              */
            __OM uint32_t LSRC : 1;    /*!< [26..26] Line Start packet with virtual channel (M) Reception
                                        *   status Clear                                                              */
            __OM uint32_t LERC : 1;    /*!< [27..27] Line End packet with virtual channel (M) Reception
                                        *   status Clear                                                              */
            __OM uint32_t ETRC : 1;    /*!< [28..28] EoTp packet with virtual channel (M) Reception status
                                        *   Clear                                                                     */
            uint32_t : 3;
        } VCSC1_b;
    };

    union
    {
        __IOM uint32_t VCIE1;          /*!< (@ 0x00000118) Virtual Channel (M) Interrupt Enable Register              */

        struct
        {
            __IOM uint32_t MLFE : 1;   /*!< [0..0] MaLFormed packet with virutal channel (M) detect interrupt
                                        *   Enable                                                                    */
            __IOM uint32_t ECDE : 1;   /*!< [1..1] ECc 2-bit (Double) error packet with virutal channel
                                        *   (M) Detect interrupt Enable                                               */
            __IOM uint32_t CRCE : 1;   /*!< [2..2] CRC error packet with virtual channel (M) detect interrupt
                                        *   Enable                                                                    */
            __IOM uint32_t IDEE : 1;   /*!< [3..3] ErrID packet with virtual channel (M) detect interrupt
                                        *   Enable                                                                    */
            __IOM uint32_t WCEE : 1;   /*!< [4..4] Word Count Error packet with virtual channel (M) detect
                                        *   interrupt Enable                                                          */
            __IOM uint32_t ECCE : 1;   /*!< [5..5] ECc 1-bit error (Corrected) packet with virtual channel
                                        *   (M) detect interrupt Enable                                               */
            __IOM uint32_t ECNE : 1;   /*!< [6..6] ECc No-error packet with virtual channel (M) detect interrupt
                                        *   Enable                                                                    */
            uint32_t            : 1;
            __IOM uint32_t FRSE : 1;   /*!< [8..8] errFRameSync of virtual channel (M) detect interrupt
                                        *   Enable                                                                    */
            __IOM uint32_t FRDE : 1;   /*!< [9..9] errFRameData of virtual channel (M) detect interrupt
                                        *   Enable                                                                    */
            uint32_t            : 6;
            __IOM uint32_t OVFE : 1;   /*!< [16..16] generic short packet with virtual channel (M) discard
                                        *   by fifo OVerFlow interrupt Enable                                         */
            uint32_t            : 7;
            __IOM uint32_t FSRE : 1;   /*!< [24..24] Frame Start packet with virtual channel (M) Reception
                                        *   interrupt Enable                                                          */
            __IOM uint32_t FERE : 1;   /*!< [25..25] Frame End packet with virtual channel (M) Reception
                                        *   interrupt Enable                                                          */
            __IOM uint32_t LSRE : 1;   /*!< [26..26] Line Start packet with virtual channel (M) Reception
                                        *   interrupt Enable                                                          */
            __IOM uint32_t LERE : 1;   /*!< [27..27] Line End packet with virtual channel (M) Reception
                                        *   interrupt Enable                                                          */
            __IOM uint32_t ETRE : 1;   /*!< [28..28] EoTp packet with virtual channel (M) Reception interrupt
                                        *   Enable                                                                    */
            uint32_t : 3;
        } VCIE1_b;
    };
    __IM uint32_t RESERVED11;

    union
    {
        __IM uint32_t VCST2;           /*!< (@ 0x00000120) Virtual Channel (M) Status Register                        */

        struct
        {
            __IM uint32_t MLF : 1;     /*!< [0..0] MaLFormed packet with virutal channel (M) detect status            */
            __IM uint32_t ECD : 1;     /*!< [1..1] ECc 2-bit (Double) error packet with virutal channel
                                        *   (M) Detect status                                                         */
            __IM uint32_t CRC : 1;     /*!< [2..2] CRC error packet with virtual channel (M) detect status            */
            __IM uint32_t IDE : 1;     /*!< [3..3] ErrID packet with virtual channel (M) detect status                */
            __IM uint32_t WCE : 1;     /*!< [4..4] Word Count Error packet with virtual channel (M) detect
                                        *   status                                                                    */
            __IM uint32_t ECC : 1;     /*!< [5..5] ECc 1-bit error (Corrected) packet with virtual channel
                                        *   (M) detect status                                                         */
            __IM uint32_t ECN : 1;     /*!< [6..6] ECc No-error packet with virtual channel (M) detect status         */
            uint32_t          : 1;
            __IM uint32_t FRS : 1;     /*!< [8..8] errFRameSync of virtual channel (M) detect status                  */
            __IM uint32_t FRD : 1;     /*!< [9..9] errFRameData of virtual channel (M) detect status                  */
            uint32_t          : 6;
            __IM uint32_t OVF : 1;     /*!< [16..16] generic short packet with virtual channel (M) discard
                                        *   by fifo OVerFlow status                                                   */
            uint32_t          : 7;
            __IM uint32_t FSR : 1;     /*!< [24..24] Frame Start packet with virtual channel (M) Reception
                                        *   status                                                                    */
            __IM uint32_t FER : 1;     /*!< [25..25] Frame End packet with virtual channel (M) Reception
                                        *   status                                                                    */
            __IM uint32_t LSR : 1;     /*!< [26..26] Line Start packet with virtual channel (M) Reception
                                        *   status                                                                    */
            __IM uint32_t LER : 1;     /*!< [27..27] Line End packet with virtual channel (M) Reception
                                        *   status                                                                    */
            __IM uint32_t ETR : 1;     /*!< [28..28] EoTp packet with virtual channel (M) Reception status            */
            uint32_t          : 3;
        } VCST2_b;
    };

    union
    {
        __OM uint32_t VCSC2;           /*!< (@ 0x00000124) Virtual Channel (M) Status Clear Register                  */

        struct
        {
            __OM uint32_t MLFC : 1;    /*!< [0..0] MaLFormed packet with virutal channel (M) detect status
                                        *   Clear                                                                     */
            __OM uint32_t ECDC : 1;    /*!< [1..1] ECc 2-bit (Double) error packet with virutal channel
                                        *   (M) Detect status Clear                                                   */
            __OM uint32_t CRCC : 1;    /*!< [2..2] CRC error packet with virtual channel (M) detect status
                                        *   Clear                                                                     */
            __OM uint32_t IDEC : 1;    /*!< [3..3] ErrID packet with virtual channel (M) detect status Clear          */
            __OM uint32_t WCEC : 1;    /*!< [4..4] Word Count Error packet with virtual channel (M) detect
                                        *   status Clear                                                              */
            __OM uint32_t ECCC : 1;    /*!< [5..5] ECc 1-bit error (Corrected) packet with virtual channel
                                        *   (M) detect status Clear                                                   */
            __OM uint32_t ECNC : 1;    /*!< [6..6] ECc No-error packet with virtual channel (M) detect status
                                        *   Clear                                                                     */
            uint32_t            : 1;
            __OM uint32_t FRSC  : 1;   /*!< [8..8] errFRameSync of virtual channel (M) detect status Clear            */
            __OM uint32_t FRDC  : 1;   /*!< [9..9] errFRameData of virtual channel (M) detect status Clear            */
            uint32_t            : 4;
            __OM uint32_t AMLFC : 1;   /*!< [14..14] MaLFormed packet with any virutal channels detect status
                                        *   Clear                                                                     */
            __OM uint32_t AECDC : 1;   /*!< [15..15] ECc 2-bit (Double) error packet with any virutal channels
                                        *   Detect status Clear                                                       */
            __OM uint32_t OVFC : 1;    /*!< [16..16] generic short packet with virtual channel (M) discard
                                        *   by fifo OVerFlow status Clear                                             */
            uint32_t           : 7;
            __OM uint32_t FSRC : 1;    /*!< [24..24] Frame Start packet with virtual channel (M) Reception
                                        *   status Clear                                                              */
            __OM uint32_t FERC : 1;    /*!< [25..25] Frame End packet with virtual channel (M) Reception
                                        *   status Clear                                                              */
            __OM uint32_t LSRC : 1;    /*!< [26..26] Line Start packet with virtual channel (M) Reception
                                        *   status Clear                                                              */
            __OM uint32_t LERC : 1;    /*!< [27..27] Line End packet with virtual channel (M) Reception
                                        *   status Clear                                                              */
            __OM uint32_t ETRC : 1;    /*!< [28..28] EoTp packet with virtual channel (M) Reception status
                                        *   Clear                                                                     */
            uint32_t : 3;
        } VCSC2_b;
    };

    union
    {
        __IOM uint32_t VCIE2;          /*!< (@ 0x00000128) Virtual Channel (M) Interrupt Enable Register              */

        struct
        {
            __IOM uint32_t MLFE : 1;   /*!< [0..0] MaLFormed packet with virutal channel (M) detect interrupt
                                        *   Enable                                                                    */
            __IOM uint32_t ECDE : 1;   /*!< [1..1] ECc 2-bit (Double) error packet with virutal channel
                                        *   (M) Detect interrupt Enable                                               */
            __IOM uint32_t CRCE : 1;   /*!< [2..2] CRC error packet with virtual channel (M) detect interrupt
                                        *   Enable                                                                    */
            __IOM uint32_t IDEE : 1;   /*!< [3..3] ErrID packet with virtual channel (M) detect interrupt
                                        *   Enable                                                                    */
            __IOM uint32_t WCEE : 1;   /*!< [4..4] Word Count Error packet with virtual channel (M) detect
                                        *   interrupt Enable                                                          */
            __IOM uint32_t ECCE : 1;   /*!< [5..5] ECc 1-bit error (Corrected) packet with virtual channel
                                        *   (M) detect interrupt Enable                                               */
            __IOM uint32_t ECNE : 1;   /*!< [6..6] ECc No-error packet with virtual channel (M) detect interrupt
                                        *   Enable                                                                    */
            uint32_t            : 1;
            __IOM uint32_t FRSE : 1;   /*!< [8..8] errFRameSync of virtual channel (M) detect interrupt
                                        *   Enable                                                                    */
            __IOM uint32_t FRDE : 1;   /*!< [9..9] errFRameData of virtual channel (M) detect interrupt
                                        *   Enable                                                                    */
            uint32_t            : 6;
            __IOM uint32_t OVFE : 1;   /*!< [16..16] generic short packet with virtual channel (M) discard
                                        *   by fifo OVerFlow interrupt Enable                                         */
            uint32_t            : 7;
            __IOM uint32_t FSRE : 1;   /*!< [24..24] Frame Start packet with virtual channel (M) Reception
                                        *   interrupt Enable                                                          */
            __IOM uint32_t FERE : 1;   /*!< [25..25] Frame End packet with virtual channel (M) Reception
                                        *   interrupt Enable                                                          */
            __IOM uint32_t LSRE : 1;   /*!< [26..26] Line Start packet with virtual channel (M) Reception
                                        *   interrupt Enable                                                          */
            __IOM uint32_t LERE : 1;   /*!< [27..27] Line End packet with virtual channel (M) Reception
                                        *   interrupt Enable                                                          */
            __IOM uint32_t ETRE : 1;   /*!< [28..28] EoTp packet with virtual channel (M) Reception interrupt
                                        *   Enable                                                                    */
            uint32_t : 3;
        } VCIE2_b;
    };
    __IM uint32_t RESERVED12;

    union
    {
        __IM uint32_t VCST3;           /*!< (@ 0x00000130) Virtual Channel (M) Status Register                        */

        struct
        {
            __IM uint32_t MLF : 1;     /*!< [0..0] MaLFormed packet with virutal channel (M) detect status            */
            __IM uint32_t ECD : 1;     /*!< [1..1] ECc 2-bit (Double) error packet with virutal channel
                                        *   (M) Detect status                                                         */
            __IM uint32_t CRC : 1;     /*!< [2..2] CRC error packet with virtual channel (M) detect status            */
            __IM uint32_t IDE : 1;     /*!< [3..3] ErrID packet with virtual channel (M) detect status                */
            __IM uint32_t WCE : 1;     /*!< [4..4] Word Count Error packet with virtual channel (M) detect
                                        *   status                                                                    */
            __IM uint32_t ECC : 1;     /*!< [5..5] ECc 1-bit error (Corrected) packet with virtual channel
                                        *   (M) detect status                                                         */
            __IM uint32_t ECN : 1;     /*!< [6..6] ECc No-error packet with virtual channel (M) detect status         */
            uint32_t          : 1;
            __IM uint32_t FRS : 1;     /*!< [8..8] errFRameSync of virtual channel (M) detect status                  */
            __IM uint32_t FRD : 1;     /*!< [9..9] errFRameData of virtual channel (M) detect status                  */
            uint32_t          : 6;
            __IM uint32_t OVF : 1;     /*!< [16..16] generic short packet with virtual channel (M) discard
                                        *   by fifo OVerFlow status                                                   */
            uint32_t          : 7;
            __IM uint32_t FSR : 1;     /*!< [24..24] Frame Start packet with virtual channel (M) Reception
                                        *   status                                                                    */
            __IM uint32_t FER : 1;     /*!< [25..25] Frame End packet with virtual channel (M) Reception
                                        *   status                                                                    */
            __IM uint32_t LSR : 1;     /*!< [26..26] Line Start packet with virtual channel (M) Reception
                                        *   status                                                                    */
            __IM uint32_t LER : 1;     /*!< [27..27] Line End packet with virtual channel (M) Reception
                                        *   status                                                                    */
            __IM uint32_t ETR : 1;     /*!< [28..28] EoTp packet with virtual channel (M) Reception status            */
            uint32_t          : 3;
        } VCST3_b;
    };

    union
    {
        __OM uint32_t VCSC3;           /*!< (@ 0x00000134) Virtual Channel (M) Status Clear Register                  */

        struct
        {
            __OM uint32_t MLFC : 1;    /*!< [0..0] MaLFormed packet with virutal channel (M) detect status
                                        *   Clear                                                                     */
            __OM uint32_t ECDC : 1;    /*!< [1..1] ECc 2-bit (Double) error packet with virutal channel
                                        *   (M) Detect status Clear                                                   */
            __OM uint32_t CRCC : 1;    /*!< [2..2] CRC error packet with virtual channel (M) detect status
                                        *   Clear                                                                     */
            __OM uint32_t IDEC : 1;    /*!< [3..3] ErrID packet with virtual channel (M) detect status Clear          */
            __OM uint32_t WCEC : 1;    /*!< [4..4] Word Count Error packet with virtual channel (M) detect
                                        *   status Clear                                                              */
            __OM uint32_t ECCC : 1;    /*!< [5..5] ECc 1-bit error (Corrected) packet with virtual channel
                                        *   (M) detect status Clear                                                   */
            __OM uint32_t ECNC : 1;    /*!< [6..6] ECc No-error packet with virtual channel (M) detect status
                                        *   Clear                                                                     */
            uint32_t            : 1;
            __OM uint32_t FRSC  : 1;   /*!< [8..8] errFRameSync of virtual channel (M) detect status Clear            */
            __OM uint32_t FRDC  : 1;   /*!< [9..9] errFRameData of virtual channel (M) detect status Clear            */
            uint32_t            : 4;
            __OM uint32_t AMLFC : 1;   /*!< [14..14] MaLFormed packet with any virutal channels detect status
                                        *   Clear                                                                     */
            __OM uint32_t AECDC : 1;   /*!< [15..15] ECc 2-bit (Double) error packet with any virutal channels
                                        *   Detect status Clear                                                       */
            __OM uint32_t OVFC : 1;    /*!< [16..16] generic short packet with virtual channel (M) discard
                                        *   by fifo OVerFlow status Clear                                             */
            uint32_t           : 7;
            __OM uint32_t FSRC : 1;    /*!< [24..24] Frame Start packet with virtual channel (M) Reception
                                        *   status Clear                                                              */
            __OM uint32_t FERC : 1;    /*!< [25..25] Frame End packet with virtual channel (M) Reception
                                        *   status Clear                                                              */
            __OM uint32_t LSRC : 1;    /*!< [26..26] Line Start packet with virtual channel (M) Reception
                                        *   status Clear                                                              */
            __OM uint32_t LERC : 1;    /*!< [27..27] Line End packet with virtual channel (M) Reception
                                        *   status Clear                                                              */
            __OM uint32_t ETRC : 1;    /*!< [28..28] EoTp packet with virtual channel (M) Reception status
                                        *   Clear                                                                     */
            uint32_t : 3;
        } VCSC3_b;
    };

    union
    {
        __IOM uint32_t VCIE3;          /*!< (@ 0x00000138) Virtual Channel (M) Interrupt Enable Register              */

        struct
        {
            __IOM uint32_t MLFE : 1;   /*!< [0..0] MaLFormed packet with virutal channel (M) detect interrupt
                                        *   Enable                                                                    */
            __IOM uint32_t ECDE : 1;   /*!< [1..1] ECc 2-bit (Double) error packet with virutal channel
                                        *   (M) Detect interrupt Enable                                               */
            __IOM uint32_t CRCE : 1;   /*!< [2..2] CRC error packet with virtual channel (M) detect interrupt
                                        *   Enable                                                                    */
            __IOM uint32_t IDEE : 1;   /*!< [3..3] ErrID packet with virtual channel (M) detect interrupt
                                        *   Enable                                                                    */
            __IOM uint32_t WCEE : 1;   /*!< [4..4] Word Count Error packet with virtual channel (M) detect
                                        *   interrupt Enable                                                          */
            __IOM uint32_t ECCE : 1;   /*!< [5..5] ECc 1-bit error (Corrected) packet with virtual channel
                                        *   (M) detect interrupt Enable                                               */
            __IOM uint32_t ECNE : 1;   /*!< [6..6] ECc No-error packet with virtual channel (M) detect interrupt
                                        *   Enable                                                                    */
            uint32_t            : 1;
            __IOM uint32_t FRSE : 1;   /*!< [8..8] errFRameSync of virtual channel (M) detect interrupt
                                        *   Enable                                                                    */
            __IOM uint32_t FRDE : 1;   /*!< [9..9] errFRameData of virtual channel (M) detect interrupt
                                        *   Enable                                                                    */
            uint32_t            : 6;
            __IOM uint32_t OVFE : 1;   /*!< [16..16] generic short packet with virtual channel (M) discard
                                        *   by fifo OVerFlow interrupt Enable                                         */
            uint32_t            : 7;
            __IOM uint32_t FSRE : 1;   /*!< [24..24] Frame Start packet with virtual channel (M) Reception
                                        *   interrupt Enable                                                          */
            __IOM uint32_t FERE : 1;   /*!< [25..25] Frame End packet with virtual channel (M) Reception
                                        *   interrupt Enable                                                          */
            __IOM uint32_t LSRE : 1;   /*!< [26..26] Line Start packet with virtual channel (M) Reception
                                        *   interrupt Enable                                                          */
            __IOM uint32_t LERE : 1;   /*!< [27..27] Line End packet with virtual channel (M) Reception
                                        *   interrupt Enable                                                          */
            __IOM uint32_t ETRE : 1;   /*!< [28..28] EoTp packet with virtual channel (M) Reception interrupt
                                        *   Enable                                                                    */
            uint32_t : 3;
        } VCIE3_b;
    };
    __IM uint32_t RESERVED13;

    union
    {
        __IM uint32_t VCST4;           /*!< (@ 0x00000140) Virtual Channel (M) Status Register                        */

        struct
        {
            __IM uint32_t MLF : 1;     /*!< [0..0] MaLFormed packet with virutal channel (M) detect status            */
            __IM uint32_t ECD : 1;     /*!< [1..1] ECc 2-bit (Double) error packet with virutal channel
                                        *   (M) Detect status                                                         */
            __IM uint32_t CRC : 1;     /*!< [2..2] CRC error packet with virtual channel (M) detect status            */
            __IM uint32_t IDE : 1;     /*!< [3..3] ErrID packet with virtual channel (M) detect status                */
            __IM uint32_t WCE : 1;     /*!< [4..4] Word Count Error packet with virtual channel (M) detect
                                        *   status                                                                    */
            __IM uint32_t ECC : 1;     /*!< [5..5] ECc 1-bit error (Corrected) packet with virtual channel
                                        *   (M) detect status                                                         */
            __IM uint32_t ECN : 1;     /*!< [6..6] ECc No-error packet with virtual channel (M) detect status         */
            uint32_t          : 1;
            __IM uint32_t FRS : 1;     /*!< [8..8] errFRameSync of virtual channel (M) detect status                  */
            __IM uint32_t FRD : 1;     /*!< [9..9] errFRameData of virtual channel (M) detect status                  */
            uint32_t          : 6;
            __IM uint32_t OVF : 1;     /*!< [16..16] generic short packet with virtual channel (M) discard
                                        *   by fifo OVerFlow status                                                   */
            uint32_t          : 7;
            __IM uint32_t FSR : 1;     /*!< [24..24] Frame Start packet with virtual channel (M) Reception
                                        *   status                                                                    */
            __IM uint32_t FER : 1;     /*!< [25..25] Frame End packet with virtual channel (M) Reception
                                        *   status                                                                    */
            __IM uint32_t LSR : 1;     /*!< [26..26] Line Start packet with virtual channel (M) Reception
                                        *   status                                                                    */
            __IM uint32_t LER : 1;     /*!< [27..27] Line End packet with virtual channel (M) Reception
                                        *   status                                                                    */
            __IM uint32_t ETR : 1;     /*!< [28..28] EoTp packet with virtual channel (M) Reception status            */
            uint32_t          : 3;
        } VCST4_b;
    };

    union
    {
        __OM uint32_t VCSC4;           /*!< (@ 0x00000144) Virtual Channel (M) Status Clear Register                  */

        struct
        {
            __OM uint32_t MLFC : 1;    /*!< [0..0] MaLFormed packet with virutal channel (M) detect status
                                        *   Clear                                                                     */
            __OM uint32_t ECDC : 1;    /*!< [1..1] ECc 2-bit (Double) error packet with virutal channel
                                        *   (M) Detect status Clear                                                   */
            __OM uint32_t CRCC : 1;    /*!< [2..2] CRC error packet with virtual channel (M) detect status
                                        *   Clear                                                                     */
            __OM uint32_t IDEC : 1;    /*!< [3..3] ErrID packet with virtual channel (M) detect status Clear          */
            __OM uint32_t WCEC : 1;    /*!< [4..4] Word Count Error packet with virtual channel (M) detect
                                        *   status Clear                                                              */
            __OM uint32_t ECCC : 1;    /*!< [5..5] ECc 1-bit error (Corrected) packet with virtual channel
                                        *   (M) detect status Clear                                                   */
            __OM uint32_t ECNC : 1;    /*!< [6..6] ECc No-error packet with virtual channel (M) detect status
                                        *   Clear                                                                     */
            uint32_t            : 1;
            __OM uint32_t FRSC  : 1;   /*!< [8..8] errFRameSync of virtual channel (M) detect status Clear            */
            __OM uint32_t FRDC  : 1;   /*!< [9..9] errFRameData of virtual channel (M) detect status Clear            */
            uint32_t            : 4;
            __OM uint32_t AMLFC : 1;   /*!< [14..14] MaLFormed packet with any virutal channels detect status
                                        *   Clear                                                                     */
            __OM uint32_t AECDC : 1;   /*!< [15..15] ECc 2-bit (Double) error packet with any virutal channels
                                        *   Detect status Clear                                                       */
            __OM uint32_t OVFC : 1;    /*!< [16..16] generic short packet with virtual channel (M) discard
                                        *   by fifo OVerFlow status Clear                                             */
            uint32_t           : 7;
            __OM uint32_t FSRC : 1;    /*!< [24..24] Frame Start packet with virtual channel (M) Reception
                                        *   status Clear                                                              */
            __OM uint32_t FERC : 1;    /*!< [25..25] Frame End packet with virtual channel (M) Reception
                                        *   status Clear                                                              */
            __OM uint32_t LSRC : 1;    /*!< [26..26] Line Start packet with virtual channel (M) Reception
                                        *   status Clear                                                              */
            __OM uint32_t LERC : 1;    /*!< [27..27] Line End packet with virtual channel (M) Reception
                                        *   status Clear                                                              */
            __OM uint32_t ETRC : 1;    /*!< [28..28] EoTp packet with virtual channel (M) Reception status
                                        *   Clear                                                                     */
            uint32_t : 3;
        } VCSC4_b;
    };

    union
    {
        __IOM uint32_t VCIE4;          /*!< (@ 0x00000148) Virtual Channel (M) Interrupt Enable Register              */

        struct
        {
            __IOM uint32_t MLFE : 1;   /*!< [0..0] MaLFormed packet with virutal channel (M) detect interrupt
                                        *   Enable                                                                    */
            __IOM uint32_t ECDE : 1;   /*!< [1..1] ECc 2-bit (Double) error packet with virutal channel
                                        *   (M) Detect interrupt Enable                                               */
            __IOM uint32_t CRCE : 1;   /*!< [2..2] CRC error packet with virtual channel (M) detect interrupt
                                        *   Enable                                                                    */
            __IOM uint32_t IDEE : 1;   /*!< [3..3] ErrID packet with virtual channel (M) detect interrupt
                                        *   Enable                                                                    */
            __IOM uint32_t WCEE : 1;   /*!< [4..4] Word Count Error packet with virtual channel (M) detect
                                        *   interrupt Enable                                                          */
            __IOM uint32_t ECCE : 1;   /*!< [5..5] ECc 1-bit error (Corrected) packet with virtual channel
                                        *   (M) detect interrupt Enable                                               */
            __IOM uint32_t ECNE : 1;   /*!< [6..6] ECc No-error packet with virtual channel (M) detect interrupt
                                        *   Enable                                                                    */
            uint32_t            : 1;
            __IOM uint32_t FRSE : 1;   /*!< [8..8] errFRameSync of virtual channel (M) detect interrupt
                                        *   Enable                                                                    */
            __IOM uint32_t FRDE : 1;   /*!< [9..9] errFRameData of virtual channel (M) detect interrupt
                                        *   Enable                                                                    */
            uint32_t            : 6;
            __IOM uint32_t OVFE : 1;   /*!< [16..16] generic short packet with virtual channel (M) discard
                                        *   by fifo OVerFlow interrupt Enable                                         */
            uint32_t            : 7;
            __IOM uint32_t FSRE : 1;   /*!< [24..24] Frame Start packet with virtual channel (M) Reception
                                        *   interrupt Enable                                                          */
            __IOM uint32_t FERE : 1;   /*!< [25..25] Frame End packet with virtual channel (M) Reception
                                        *   interrupt Enable                                                          */
            __IOM uint32_t LSRE : 1;   /*!< [26..26] Line Start packet with virtual channel (M) Reception
                                        *   interrupt Enable                                                          */
            __IOM uint32_t LERE : 1;   /*!< [27..27] Line End packet with virtual channel (M) Reception
                                        *   interrupt Enable                                                          */
            __IOM uint32_t ETRE : 1;   /*!< [28..28] EoTp packet with virtual channel (M) Reception interrupt
                                        *   Enable                                                                    */
            uint32_t : 3;
        } VCIE4_b;
    };
    __IM uint32_t RESERVED14;

    union
    {
        __IM uint32_t VCST5;           /*!< (@ 0x00000150) Virtual Channel (M) Status Register                        */

        struct
        {
            __IM uint32_t MLF : 1;     /*!< [0..0] MaLFormed packet with virutal channel (M) detect status            */
            __IM uint32_t ECD : 1;     /*!< [1..1] ECc 2-bit (Double) error packet with virutal channel
                                        *   (M) Detect status                                                         */
            __IM uint32_t CRC : 1;     /*!< [2..2] CRC error packet with virtual channel (M) detect status            */
            __IM uint32_t IDE : 1;     /*!< [3..3] ErrID packet with virtual channel (M) detect status                */
            __IM uint32_t WCE : 1;     /*!< [4..4] Word Count Error packet with virtual channel (M) detect
                                        *   status                                                                    */
            __IM uint32_t ECC : 1;     /*!< [5..5] ECc 1-bit error (Corrected) packet with virtual channel
                                        *   (M) detect status                                                         */
            __IM uint32_t ECN : 1;     /*!< [6..6] ECc No-error packet with virtual channel (M) detect status         */
            uint32_t          : 1;
            __IM uint32_t FRS : 1;     /*!< [8..8] errFRameSync of virtual channel (M) detect status                  */
            __IM uint32_t FRD : 1;     /*!< [9..9] errFRameData of virtual channel (M) detect status                  */
            uint32_t          : 6;
            __IM uint32_t OVF : 1;     /*!< [16..16] generic short packet with virtual channel (M) discard
                                        *   by fifo OVerFlow status                                                   */
            uint32_t          : 7;
            __IM uint32_t FSR : 1;     /*!< [24..24] Frame Start packet with virtual channel (M) Reception
                                        *   status                                                                    */
            __IM uint32_t FER : 1;     /*!< [25..25] Frame End packet with virtual channel (M) Reception
                                        *   status                                                                    */
            __IM uint32_t LSR : 1;     /*!< [26..26] Line Start packet with virtual channel (M) Reception
                                        *   status                                                                    */
            __IM uint32_t LER : 1;     /*!< [27..27] Line End packet with virtual channel (M) Reception
                                        *   status                                                                    */
            __IM uint32_t ETR : 1;     /*!< [28..28] EoTp packet with virtual channel (M) Reception status            */
            uint32_t          : 3;
        } VCST5_b;
    };

    union
    {
        __OM uint32_t VCSC5;           /*!< (@ 0x00000154) Virtual Channel (M) Status Clear Register                  */

        struct
        {
            __OM uint32_t MLFC : 1;    /*!< [0..0] MaLFormed packet with virutal channel (M) detect status
                                        *   Clear                                                                     */
            __OM uint32_t ECDC : 1;    /*!< [1..1] ECc 2-bit (Double) error packet with virutal channel
                                        *   (M) Detect status Clear                                                   */
            __OM uint32_t CRCC : 1;    /*!< [2..2] CRC error packet with virtual channel (M) detect status
                                        *   Clear                                                                     */
            __OM uint32_t IDEC : 1;    /*!< [3..3] ErrID packet with virtual channel (M) detect status Clear          */
            __OM uint32_t WCEC : 1;    /*!< [4..4] Word Count Error packet with virtual channel (M) detect
                                        *   status Clear                                                              */
            __OM uint32_t ECCC : 1;    /*!< [5..5] ECc 1-bit error (Corrected) packet with virtual channel
                                        *   (M) detect status Clear                                                   */
            __OM uint32_t ECNC : 1;    /*!< [6..6] ECc No-error packet with virtual channel (M) detect status
                                        *   Clear                                                                     */
            uint32_t            : 1;
            __OM uint32_t FRSC  : 1;   /*!< [8..8] errFRameSync of virtual channel (M) detect status Clear            */
            __OM uint32_t FRDC  : 1;   /*!< [9..9] errFRameData of virtual channel (M) detect status Clear            */
            uint32_t            : 4;
            __OM uint32_t AMLFC : 1;   /*!< [14..14] MaLFormed packet with any virutal channels detect status
                                        *   Clear                                                                     */
            __OM uint32_t AECDC : 1;   /*!< [15..15] ECc 2-bit (Double) error packet with any virutal channels
                                        *   Detect status Clear                                                       */
            __OM uint32_t OVFC : 1;    /*!< [16..16] generic short packet with virtual channel (M) discard
                                        *   by fifo OVerFlow status Clear                                             */
            uint32_t           : 7;
            __OM uint32_t FSRC : 1;    /*!< [24..24] Frame Start packet with virtual channel (M) Reception
                                        *   status Clear                                                              */
            __OM uint32_t FERC : 1;    /*!< [25..25] Frame End packet with virtual channel (M) Reception
                                        *   status Clear                                                              */
            __OM uint32_t LSRC : 1;    /*!< [26..26] Line Start packet with virtual channel (M) Reception
                                        *   status Clear                                                              */
            __OM uint32_t LERC : 1;    /*!< [27..27] Line End packet with virtual channel (M) Reception
                                        *   status Clear                                                              */
            __OM uint32_t ETRC : 1;    /*!< [28..28] EoTp packet with virtual channel (M) Reception status
                                        *   Clear                                                                     */
            uint32_t : 3;
        } VCSC5_b;
    };

    union
    {
        __IOM uint32_t VCIE5;          /*!< (@ 0x00000158) Virtual Channel (M) Interrupt Enable Register              */

        struct
        {
            __IOM uint32_t MLFE : 1;   /*!< [0..0] MaLFormed packet with virutal channel (M) detect interrupt
                                        *   Enable                                                                    */
            __IOM uint32_t ECDE : 1;   /*!< [1..1] ECc 2-bit (Double) error packet with virutal channel
                                        *   (M) Detect interrupt Enable                                               */
            __IOM uint32_t CRCE : 1;   /*!< [2..2] CRC error packet with virtual channel (M) detect interrupt
                                        *   Enable                                                                    */
            __IOM uint32_t IDEE : 1;   /*!< [3..3] ErrID packet with virtual channel (M) detect interrupt
                                        *   Enable                                                                    */
            __IOM uint32_t WCEE : 1;   /*!< [4..4] Word Count Error packet with virtual channel (M) detect
                                        *   interrupt Enable                                                          */
            __IOM uint32_t ECCE : 1;   /*!< [5..5] ECc 1-bit error (Corrected) packet with virtual channel
                                        *   (M) detect interrupt Enable                                               */
            __IOM uint32_t ECNE : 1;   /*!< [6..6] ECc No-error packet with virtual channel (M) detect interrupt
                                        *   Enable                                                                    */
            uint32_t            : 1;
            __IOM uint32_t FRSE : 1;   /*!< [8..8] errFRameSync of virtual channel (M) detect interrupt
                                        *   Enable                                                                    */
            __IOM uint32_t FRDE : 1;   /*!< [9..9] errFRameData of virtual channel (M) detect interrupt
                                        *   Enable                                                                    */
            uint32_t            : 6;
            __IOM uint32_t OVFE : 1;   /*!< [16..16] generic short packet with virtual channel (M) discard
                                        *   by fifo OVerFlow interrupt Enable                                         */
            uint32_t            : 7;
            __IOM uint32_t FSRE : 1;   /*!< [24..24] Frame Start packet with virtual channel (M) Reception
                                        *   interrupt Enable                                                          */
            __IOM uint32_t FERE : 1;   /*!< [25..25] Frame End packet with virtual channel (M) Reception
                                        *   interrupt Enable                                                          */
            __IOM uint32_t LSRE : 1;   /*!< [26..26] Line Start packet with virtual channel (M) Reception
                                        *   interrupt Enable                                                          */
            __IOM uint32_t LERE : 1;   /*!< [27..27] Line End packet with virtual channel (M) Reception
                                        *   interrupt Enable                                                          */
            __IOM uint32_t ETRE : 1;   /*!< [28..28] EoTp packet with virtual channel (M) Reception interrupt
                                        *   Enable                                                                    */
            uint32_t : 3;
        } VCIE5_b;
    };
    __IM uint32_t RESERVED15;

    union
    {
        __IM uint32_t VCST6;           /*!< (@ 0x00000160) Virtual Channel (M) Status Register                        */

        struct
        {
            __IM uint32_t MLF : 1;     /*!< [0..0] MaLFormed packet with virutal channel (M) detect status            */
            __IM uint32_t ECD : 1;     /*!< [1..1] ECc 2-bit (Double) error packet with virutal channel
                                        *   (M) Detect status                                                         */
            __IM uint32_t CRC : 1;     /*!< [2..2] CRC error packet with virtual channel (M) detect status            */
            __IM uint32_t IDE : 1;     /*!< [3..3] ErrID packet with virtual channel (M) detect status                */
            __IM uint32_t WCE : 1;     /*!< [4..4] Word Count Error packet with virtual channel (M) detect
                                        *   status                                                                    */
            __IM uint32_t ECC : 1;     /*!< [5..5] ECc 1-bit error (Corrected) packet with virtual channel
                                        *   (M) detect status                                                         */
            __IM uint32_t ECN : 1;     /*!< [6..6] ECc No-error packet with virtual channel (M) detect status         */
            uint32_t          : 1;
            __IM uint32_t FRS : 1;     /*!< [8..8] errFRameSync of virtual channel (M) detect status                  */
            __IM uint32_t FRD : 1;     /*!< [9..9] errFRameData of virtual channel (M) detect status                  */
            uint32_t          : 6;
            __IM uint32_t OVF : 1;     /*!< [16..16] generic short packet with virtual channel (M) discard
                                        *   by fifo OVerFlow status                                                   */
            uint32_t          : 7;
            __IM uint32_t FSR : 1;     /*!< [24..24] Frame Start packet with virtual channel (M) Reception
                                        *   status                                                                    */
            __IM uint32_t FER : 1;     /*!< [25..25] Frame End packet with virtual channel (M) Reception
                                        *   status                                                                    */
            __IM uint32_t LSR : 1;     /*!< [26..26] Line Start packet with virtual channel (M) Reception
                                        *   status                                                                    */
            __IM uint32_t LER : 1;     /*!< [27..27] Line End packet with virtual channel (M) Reception
                                        *   status                                                                    */
            __IM uint32_t ETR : 1;     /*!< [28..28] EoTp packet with virtual channel (M) Reception status            */
            uint32_t          : 3;
        } VCST6_b;
    };

    union
    {
        __OM uint32_t VCSC6;           /*!< (@ 0x00000164) Virtual Channel (M) Status Clear Register                  */

        struct
        {
            __OM uint32_t MLFC : 1;    /*!< [0..0] MaLFormed packet with virutal channel (M) detect status
                                        *   Clear                                                                     */
            __OM uint32_t ECDC : 1;    /*!< [1..1] ECc 2-bit (Double) error packet with virutal channel
                                        *   (M) Detect status Clear                                                   */
            __OM uint32_t CRCC : 1;    /*!< [2..2] CRC error packet with virtual channel (M) detect status
                                        *   Clear                                                                     */
            __OM uint32_t IDEC : 1;    /*!< [3..3] ErrID packet with virtual channel (M) detect status Clear          */
            __OM uint32_t WCEC : 1;    /*!< [4..4] Word Count Error packet with virtual channel (M) detect
                                        *   status Clear                                                              */
            __OM uint32_t ECCC : 1;    /*!< [5..5] ECc 1-bit error (Corrected) packet with virtual channel
                                        *   (M) detect status Clear                                                   */
            __OM uint32_t ECNC : 1;    /*!< [6..6] ECc No-error packet with virtual channel (M) detect status
                                        *   Clear                                                                     */
            uint32_t            : 1;
            __OM uint32_t FRSC  : 1;   /*!< [8..8] errFRameSync of virtual channel (M) detect status Clear            */
            __OM uint32_t FRDC  : 1;   /*!< [9..9] errFRameData of virtual channel (M) detect status Clear            */
            uint32_t            : 4;
            __OM uint32_t AMLFC : 1;   /*!< [14..14] MaLFormed packet with any virutal channels detect status
                                        *   Clear                                                                     */
            __OM uint32_t AECDC : 1;   /*!< [15..15] ECc 2-bit (Double) error packet with any virutal channels
                                        *   Detect status Clear                                                       */
            __OM uint32_t OVFC : 1;    /*!< [16..16] generic short packet with virtual channel (M) discard
                                        *   by fifo OVerFlow status Clear                                             */
            uint32_t           : 7;
            __OM uint32_t FSRC : 1;    /*!< [24..24] Frame Start packet with virtual channel (M) Reception
                                        *   status Clear                                                              */
            __OM uint32_t FERC : 1;    /*!< [25..25] Frame End packet with virtual channel (M) Reception
                                        *   status Clear                                                              */
            __OM uint32_t LSRC : 1;    /*!< [26..26] Line Start packet with virtual channel (M) Reception
                                        *   status Clear                                                              */
            __OM uint32_t LERC : 1;    /*!< [27..27] Line End packet with virtual channel (M) Reception
                                        *   status Clear                                                              */
            __OM uint32_t ETRC : 1;    /*!< [28..28] EoTp packet with virtual channel (M) Reception status
                                        *   Clear                                                                     */
            uint32_t : 3;
        } VCSC6_b;
    };

    union
    {
        __IOM uint32_t VCIE6;          /*!< (@ 0x00000168) Virtual Channel (M) Interrupt Enable Register              */

        struct
        {
            __IOM uint32_t MLFE : 1;   /*!< [0..0] MaLFormed packet with virutal channel (M) detect interrupt
                                        *   Enable                                                                    */
            __IOM uint32_t ECDE : 1;   /*!< [1..1] ECc 2-bit (Double) error packet with virutal channel
                                        *   (M) Detect interrupt Enable                                               */
            __IOM uint32_t CRCE : 1;   /*!< [2..2] CRC error packet with virtual channel (M) detect interrupt
                                        *   Enable                                                                    */
            __IOM uint32_t IDEE : 1;   /*!< [3..3] ErrID packet with virtual channel (M) detect interrupt
                                        *   Enable                                                                    */
            __IOM uint32_t WCEE : 1;   /*!< [4..4] Word Count Error packet with virtual channel (M) detect
                                        *   interrupt Enable                                                          */
            __IOM uint32_t ECCE : 1;   /*!< [5..5] ECc 1-bit error (Corrected) packet with virtual channel
                                        *   (M) detect interrupt Enable                                               */
            __IOM uint32_t ECNE : 1;   /*!< [6..6] ECc No-error packet with virtual channel (M) detect interrupt
                                        *   Enable                                                                    */
            uint32_t            : 1;
            __IOM uint32_t FRSE : 1;   /*!< [8..8] errFRameSync of virtual channel (M) detect interrupt
                                        *   Enable                                                                    */
            __IOM uint32_t FRDE : 1;   /*!< [9..9] errFRameData of virtual channel (M) detect interrupt
                                        *   Enable                                                                    */
            uint32_t            : 6;
            __IOM uint32_t OVFE : 1;   /*!< [16..16] generic short packet with virtual channel (M) discard
                                        *   by fifo OVerFlow interrupt Enable                                         */
            uint32_t            : 7;
            __IOM uint32_t FSRE : 1;   /*!< [24..24] Frame Start packet with virtual channel (M) Reception
                                        *   interrupt Enable                                                          */
            __IOM uint32_t FERE : 1;   /*!< [25..25] Frame End packet with virtual channel (M) Reception
                                        *   interrupt Enable                                                          */
            __IOM uint32_t LSRE : 1;   /*!< [26..26] Line Start packet with virtual channel (M) Reception
                                        *   interrupt Enable                                                          */
            __IOM uint32_t LERE : 1;   /*!< [27..27] Line End packet with virtual channel (M) Reception
                                        *   interrupt Enable                                                          */
            __IOM uint32_t ETRE : 1;   /*!< [28..28] EoTp packet with virtual channel (M) Reception interrupt
                                        *   Enable                                                                    */
            uint32_t : 3;
        } VCIE6_b;
    };
    __IM uint32_t RESERVED16;

    union
    {
        __IM uint32_t VCST7;           /*!< (@ 0x00000170) Virtual Channel (M) Status Register                        */

        struct
        {
            __IM uint32_t MLF : 1;     /*!< [0..0] MaLFormed packet with virutal channel (M) detect status            */
            __IM uint32_t ECD : 1;     /*!< [1..1] ECc 2-bit (Double) error packet with virutal channel
                                        *   (M) Detect status                                                         */
            __IM uint32_t CRC : 1;     /*!< [2..2] CRC error packet with virtual channel (M) detect status            */
            __IM uint32_t IDE : 1;     /*!< [3..3] ErrID packet with virtual channel (M) detect status                */
            __IM uint32_t WCE : 1;     /*!< [4..4] Word Count Error packet with virtual channel (M) detect
                                        *   status                                                                    */
            __IM uint32_t ECC : 1;     /*!< [5..5] ECc 1-bit error (Corrected) packet with virtual channel
                                        *   (M) detect status                                                         */
            __IM uint32_t ECN : 1;     /*!< [6..6] ECc No-error packet with virtual channel (M) detect status         */
            uint32_t          : 1;
            __IM uint32_t FRS : 1;     /*!< [8..8] errFRameSync of virtual channel (M) detect status                  */
            __IM uint32_t FRD : 1;     /*!< [9..9] errFRameData of virtual channel (M) detect status                  */
            uint32_t          : 6;
            __IM uint32_t OVF : 1;     /*!< [16..16] generic short packet with virtual channel (M) discard
                                        *   by fifo OVerFlow status                                                   */
            uint32_t          : 7;
            __IM uint32_t FSR : 1;     /*!< [24..24] Frame Start packet with virtual channel (M) Reception
                                        *   status                                                                    */
            __IM uint32_t FER : 1;     /*!< [25..25] Frame End packet with virtual channel (M) Reception
                                        *   status                                                                    */
            __IM uint32_t LSR : 1;     /*!< [26..26] Line Start packet with virtual channel (M) Reception
                                        *   status                                                                    */
            __IM uint32_t LER : 1;     /*!< [27..27] Line End packet with virtual channel (M) Reception
                                        *   status                                                                    */
            __IM uint32_t ETR : 1;     /*!< [28..28] EoTp packet with virtual channel (M) Reception status            */
            uint32_t          : 3;
        } VCST7_b;
    };

    union
    {
        __OM uint32_t VCSC7;           /*!< (@ 0x00000174) Virtual Channel (M) Status Clear Register                  */

        struct
        {
            __OM uint32_t MLFC : 1;    /*!< [0..0] MaLFormed packet with virutal channel (M) detect status
                                        *   Clear                                                                     */
            __OM uint32_t ECDC : 1;    /*!< [1..1] ECc 2-bit (Double) error packet with virutal channel
                                        *   (M) Detect status Clear                                                   */
            __OM uint32_t CRCC : 1;    /*!< [2..2] CRC error packet with virtual channel (M) detect status
                                        *   Clear                                                                     */
            __OM uint32_t IDEC : 1;    /*!< [3..3] ErrID packet with virtual channel (M) detect status Clear          */
            __OM uint32_t WCEC : 1;    /*!< [4..4] Word Count Error packet with virtual channel (M) detect
                                        *   status Clear                                                              */
            __OM uint32_t ECCC : 1;    /*!< [5..5] ECc 1-bit error (Corrected) packet with virtual channel
                                        *   (M) detect status Clear                                                   */
            __OM uint32_t ECNC : 1;    /*!< [6..6] ECc No-error packet with virtual channel (M) detect status
                                        *   Clear                                                                     */
            uint32_t            : 1;
            __OM uint32_t FRSC  : 1;   /*!< [8..8] errFRameSync of virtual channel (M) detect status Clear            */
            __OM uint32_t FRDC  : 1;   /*!< [9..9] errFRameData of virtual channel (M) detect status Clear            */
            uint32_t            : 4;
            __OM uint32_t AMLFC : 1;   /*!< [14..14] MaLFormed packet with any virutal channels detect status
                                        *   Clear                                                                     */
            __OM uint32_t AECDC : 1;   /*!< [15..15] ECc 2-bit (Double) error packet with any virutal channels
                                        *   Detect status Clear                                                       */
            __OM uint32_t OVFC : 1;    /*!< [16..16] generic short packet with virtual channel (M) discard
                                        *   by fifo OVerFlow status Clear                                             */
            uint32_t           : 7;
            __OM uint32_t FSRC : 1;    /*!< [24..24] Frame Start packet with virtual channel (M) Reception
                                        *   status Clear                                                              */
            __OM uint32_t FERC : 1;    /*!< [25..25] Frame End packet with virtual channel (M) Reception
                                        *   status Clear                                                              */
            __OM uint32_t LSRC : 1;    /*!< [26..26] Line Start packet with virtual channel (M) Reception
                                        *   status Clear                                                              */
            __OM uint32_t LERC : 1;    /*!< [27..27] Line End packet with virtual channel (M) Reception
                                        *   status Clear                                                              */
            __OM uint32_t ETRC : 1;    /*!< [28..28] EoTp packet with virtual channel (M) Reception status
                                        *   Clear                                                                     */
            uint32_t : 3;
        } VCSC7_b;
    };

    union
    {
        __IOM uint32_t VCIE7;          /*!< (@ 0x00000178) Virtual Channel (M) Interrupt Enable Register              */

        struct
        {
            __IOM uint32_t MLFE : 1;   /*!< [0..0] MaLFormed packet with virutal channel (M) detect interrupt
                                        *   Enable                                                                    */
            __IOM uint32_t ECDE : 1;   /*!< [1..1] ECc 2-bit (Double) error packet with virutal channel
                                        *   (M) Detect interrupt Enable                                               */
            __IOM uint32_t CRCE : 1;   /*!< [2..2] CRC error packet with virtual channel (M) detect interrupt
                                        *   Enable                                                                    */
            __IOM uint32_t IDEE : 1;   /*!< [3..3] ErrID packet with virtual channel (M) detect interrupt
                                        *   Enable                                                                    */
            __IOM uint32_t WCEE : 1;   /*!< [4..4] Word Count Error packet with virtual channel (M) detect
                                        *   interrupt Enable                                                          */
            __IOM uint32_t ECCE : 1;   /*!< [5..5] ECc 1-bit error (Corrected) packet with virtual channel
                                        *   (M) detect interrupt Enable                                               */
            __IOM uint32_t ECNE : 1;   /*!< [6..6] ECc No-error packet with virtual channel (M) detect interrupt
                                        *   Enable                                                                    */
            uint32_t            : 1;
            __IOM uint32_t FRSE : 1;   /*!< [8..8] errFRameSync of virtual channel (M) detect interrupt
                                        *   Enable                                                                    */
            __IOM uint32_t FRDE : 1;   /*!< [9..9] errFRameData of virtual channel (M) detect interrupt
                                        *   Enable                                                                    */
            uint32_t            : 6;
            __IOM uint32_t OVFE : 1;   /*!< [16..16] generic short packet with virtual channel (M) discard
                                        *   by fifo OVerFlow interrupt Enable                                         */
            uint32_t            : 7;
            __IOM uint32_t FSRE : 1;   /*!< [24..24] Frame Start packet with virtual channel (M) Reception
                                        *   interrupt Enable                                                          */
            __IOM uint32_t FERE : 1;   /*!< [25..25] Frame End packet with virtual channel (M) Reception
                                        *   interrupt Enable                                                          */
            __IOM uint32_t LSRE : 1;   /*!< [26..26] Line Start packet with virtual channel (M) Reception
                                        *   interrupt Enable                                                          */
            __IOM uint32_t LERE : 1;   /*!< [27..27] Line End packet with virtual channel (M) Reception
                                        *   interrupt Enable                                                          */
            __IOM uint32_t ETRE : 1;   /*!< [28..28] EoTp packet with virtual channel (M) Reception interrupt
                                        *   Enable                                                                    */
            uint32_t : 3;
        } VCIE7_b;
    };
    __IM uint32_t RESERVED17;

    union
    {
        __IM uint32_t VCST8;           /*!< (@ 0x00000180) Virtual Channel (M) Status Register                        */

        struct
        {
            __IM uint32_t MLF : 1;     /*!< [0..0] MaLFormed packet with virutal channel (M) detect status            */
            __IM uint32_t ECD : 1;     /*!< [1..1] ECc 2-bit (Double) error packet with virutal channel
                                        *   (M) Detect status                                                         */
            __IM uint32_t CRC : 1;     /*!< [2..2] CRC error packet with virtual channel (M) detect status            */
            __IM uint32_t IDE : 1;     /*!< [3..3] ErrID packet with virtual channel (M) detect status                */
            __IM uint32_t WCE : 1;     /*!< [4..4] Word Count Error packet with virtual channel (M) detect
                                        *   status                                                                    */
            __IM uint32_t ECC : 1;     /*!< [5..5] ECc 1-bit error (Corrected) packet with virtual channel
                                        *   (M) detect status                                                         */
            __IM uint32_t ECN : 1;     /*!< [6..6] ECc No-error packet with virtual channel (M) detect status         */
            uint32_t          : 1;
            __IM uint32_t FRS : 1;     /*!< [8..8] errFRameSync of virtual channel (M) detect status                  */
            __IM uint32_t FRD : 1;     /*!< [9..9] errFRameData of virtual channel (M) detect status                  */
            uint32_t          : 6;
            __IM uint32_t OVF : 1;     /*!< [16..16] generic short packet with virtual channel (M) discard
                                        *   by fifo OVerFlow status                                                   */
            uint32_t          : 7;
            __IM uint32_t FSR : 1;     /*!< [24..24] Frame Start packet with virtual channel (M) Reception
                                        *   status                                                                    */
            __IM uint32_t FER : 1;     /*!< [25..25] Frame End packet with virtual channel (M) Reception
                                        *   status                                                                    */
            __IM uint32_t LSR : 1;     /*!< [26..26] Line Start packet with virtual channel (M) Reception
                                        *   status                                                                    */
            __IM uint32_t LER : 1;     /*!< [27..27] Line End packet with virtual channel (M) Reception
                                        *   status                                                                    */
            __IM uint32_t ETR : 1;     /*!< [28..28] EoTp packet with virtual channel (M) Reception status            */
            uint32_t          : 3;
        } VCST8_b;
    };

    union
    {
        __OM uint32_t VCSC8;           /*!< (@ 0x00000184) Virtual Channel (M) Status Clear Register                  */

        struct
        {
            __OM uint32_t MLFC : 1;    /*!< [0..0] MaLFormed packet with virutal channel (M) detect status
                                        *   Clear                                                                     */
            __OM uint32_t ECDC : 1;    /*!< [1..1] ECc 2-bit (Double) error packet with virutal channel
                                        *   (M) Detect status Clear                                                   */
            __OM uint32_t CRCC : 1;    /*!< [2..2] CRC error packet with virtual channel (M) detect status
                                        *   Clear                                                                     */
            __OM uint32_t IDEC : 1;    /*!< [3..3] ErrID packet with virtual channel (M) detect status Clear          */
            __OM uint32_t WCEC : 1;    /*!< [4..4] Word Count Error packet with virtual channel (M) detect
                                        *   status Clear                                                              */
            __OM uint32_t ECCC : 1;    /*!< [5..5] ECc 1-bit error (Corrected) packet with virtual channel
                                        *   (M) detect status Clear                                                   */
            __OM uint32_t ECNC : 1;    /*!< [6..6] ECc No-error packet with virtual channel (M) detect status
                                        *   Clear                                                                     */
            uint32_t            : 1;
            __OM uint32_t FRSC  : 1;   /*!< [8..8] errFRameSync of virtual channel (M) detect status Clear            */
            __OM uint32_t FRDC  : 1;   /*!< [9..9] errFRameData of virtual channel (M) detect status Clear            */
            uint32_t            : 4;
            __OM uint32_t AMLFC : 1;   /*!< [14..14] MaLFormed packet with any virutal channels detect status
                                        *   Clear                                                                     */
            __OM uint32_t AECDC : 1;   /*!< [15..15] ECc 2-bit (Double) error packet with any virutal channels
                                        *   Detect status Clear                                                       */
            __OM uint32_t OVFC : 1;    /*!< [16..16] generic short packet with virtual channel (M) discard
                                        *   by fifo OVerFlow status Clear                                             */
            uint32_t           : 7;
            __OM uint32_t FSRC : 1;    /*!< [24..24] Frame Start packet with virtual channel (M) Reception
                                        *   status Clear                                                              */
            __OM uint32_t FERC : 1;    /*!< [25..25] Frame End packet with virtual channel (M) Reception
                                        *   status Clear                                                              */
            __OM uint32_t LSRC : 1;    /*!< [26..26] Line Start packet with virtual channel (M) Reception
                                        *   status Clear                                                              */
            __OM uint32_t LERC : 1;    /*!< [27..27] Line End packet with virtual channel (M) Reception
                                        *   status Clear                                                              */
            __OM uint32_t ETRC : 1;    /*!< [28..28] EoTp packet with virtual channel (M) Reception status
                                        *   Clear                                                                     */
            uint32_t : 3;
        } VCSC8_b;
    };

    union
    {
        __IOM uint32_t VCIE8;          /*!< (@ 0x00000188) Virtual Channel (M) Interrupt Enable Register              */

        struct
        {
            __IOM uint32_t MLFE : 1;   /*!< [0..0] MaLFormed packet with virutal channel (M) detect interrupt
                                        *   Enable                                                                    */
            __IOM uint32_t ECDE : 1;   /*!< [1..1] ECc 2-bit (Double) error packet with virutal channel
                                        *   (M) Detect interrupt Enable                                               */
            __IOM uint32_t CRCE : 1;   /*!< [2..2] CRC error packet with virtual channel (M) detect interrupt
                                        *   Enable                                                                    */
            __IOM uint32_t IDEE : 1;   /*!< [3..3] ErrID packet with virtual channel (M) detect interrupt
                                        *   Enable                                                                    */
            __IOM uint32_t WCEE : 1;   /*!< [4..4] Word Count Error packet with virtual channel (M) detect
                                        *   interrupt Enable                                                          */
            __IOM uint32_t ECCE : 1;   /*!< [5..5] ECc 1-bit error (Corrected) packet with virtual channel
                                        *   (M) detect interrupt Enable                                               */
            __IOM uint32_t ECNE : 1;   /*!< [6..6] ECc No-error packet with virtual channel (M) detect interrupt
                                        *   Enable                                                                    */
            uint32_t            : 1;
            __IOM uint32_t FRSE : 1;   /*!< [8..8] errFRameSync of virtual channel (M) detect interrupt
                                        *   Enable                                                                    */
            __IOM uint32_t FRDE : 1;   /*!< [9..9] errFRameData of virtual channel (M) detect interrupt
                                        *   Enable                                                                    */
            uint32_t            : 6;
            __IOM uint32_t OVFE : 1;   /*!< [16..16] generic short packet with virtual channel (M) discard
                                        *   by fifo OVerFlow interrupt Enable                                         */
            uint32_t            : 7;
            __IOM uint32_t FSRE : 1;   /*!< [24..24] Frame Start packet with virtual channel (M) Reception
                                        *   interrupt Enable                                                          */
            __IOM uint32_t FERE : 1;   /*!< [25..25] Frame End packet with virtual channel (M) Reception
                                        *   interrupt Enable                                                          */
            __IOM uint32_t LSRE : 1;   /*!< [26..26] Line Start packet with virtual channel (M) Reception
                                        *   interrupt Enable                                                          */
            __IOM uint32_t LERE : 1;   /*!< [27..27] Line End packet with virtual channel (M) Reception
                                        *   interrupt Enable                                                          */
            __IOM uint32_t ETRE : 1;   /*!< [28..28] EoTp packet with virtual channel (M) Reception interrupt
                                        *   Enable                                                                    */
            uint32_t : 3;
        } VCIE8_b;
    };
    __IM uint32_t RESERVED18;

    union
    {
        __IM uint32_t VCST9;           /*!< (@ 0x00000190) Virtual Channel (M) Status Register                        */

        struct
        {
            __IM uint32_t MLF : 1;     /*!< [0..0] MaLFormed packet with virutal channel (M) detect status            */
            __IM uint32_t ECD : 1;     /*!< [1..1] ECc 2-bit (Double) error packet with virutal channel
                                        *   (M) Detect status                                                         */
            __IM uint32_t CRC : 1;     /*!< [2..2] CRC error packet with virtual channel (M) detect status            */
            __IM uint32_t IDE : 1;     /*!< [3..3] ErrID packet with virtual channel (M) detect status                */
            __IM uint32_t WCE : 1;     /*!< [4..4] Word Count Error packet with virtual channel (M) detect
                                        *   status                                                                    */
            __IM uint32_t ECC : 1;     /*!< [5..5] ECc 1-bit error (Corrected) packet with virtual channel
                                        *   (M) detect status                                                         */
            __IM uint32_t ECN : 1;     /*!< [6..6] ECc No-error packet with virtual channel (M) detect status         */
            uint32_t          : 1;
            __IM uint32_t FRS : 1;     /*!< [8..8] errFRameSync of virtual channel (M) detect status                  */
            __IM uint32_t FRD : 1;     /*!< [9..9] errFRameData of virtual channel (M) detect status                  */
            uint32_t          : 6;
            __IM uint32_t OVF : 1;     /*!< [16..16] generic short packet with virtual channel (M) discard
                                        *   by fifo OVerFlow status                                                   */
            uint32_t          : 7;
            __IM uint32_t FSR : 1;     /*!< [24..24] Frame Start packet with virtual channel (M) Reception
                                        *   status                                                                    */
            __IM uint32_t FER : 1;     /*!< [25..25] Frame End packet with virtual channel (M) Reception
                                        *   status                                                                    */
            __IM uint32_t LSR : 1;     /*!< [26..26] Line Start packet with virtual channel (M) Reception
                                        *   status                                                                    */
            __IM uint32_t LER : 1;     /*!< [27..27] Line End packet with virtual channel (M) Reception
                                        *   status                                                                    */
            __IM uint32_t ETR : 1;     /*!< [28..28] EoTp packet with virtual channel (M) Reception status            */
            uint32_t          : 3;
        } VCST9_b;
    };

    union
    {
        __OM uint32_t VCSC9;           /*!< (@ 0x00000194) Virtual Channel (M) Status Clear Register                  */

        struct
        {
            __OM uint32_t MLFC : 1;    /*!< [0..0] MaLFormed packet with virutal channel (M) detect status
                                        *   Clear                                                                     */
            __OM uint32_t ECDC : 1;    /*!< [1..1] ECc 2-bit (Double) error packet with virutal channel
                                        *   (M) Detect status Clear                                                   */
            __OM uint32_t CRCC : 1;    /*!< [2..2] CRC error packet with virtual channel (M) detect status
                                        *   Clear                                                                     */
            __OM uint32_t IDEC : 1;    /*!< [3..3] ErrID packet with virtual channel (M) detect status Clear          */
            __OM uint32_t WCEC : 1;    /*!< [4..4] Word Count Error packet with virtual channel (M) detect
                                        *   status Clear                                                              */
            __OM uint32_t ECCC : 1;    /*!< [5..5] ECc 1-bit error (Corrected) packet with virtual channel
                                        *   (M) detect status Clear                                                   */
            __OM uint32_t ECNC : 1;    /*!< [6..6] ECc No-error packet with virtual channel (M) detect status
                                        *   Clear                                                                     */
            uint32_t            : 1;
            __OM uint32_t FRSC  : 1;   /*!< [8..8] errFRameSync of virtual channel (M) detect status Clear            */
            __OM uint32_t FRDC  : 1;   /*!< [9..9] errFRameData of virtual channel (M) detect status Clear            */
            uint32_t            : 4;
            __OM uint32_t AMLFC : 1;   /*!< [14..14] MaLFormed packet with any virutal channels detect status
                                        *   Clear                                                                     */
            __OM uint32_t AECDC : 1;   /*!< [15..15] ECc 2-bit (Double) error packet with any virutal channels
                                        *   Detect status Clear                                                       */
            __OM uint32_t OVFC : 1;    /*!< [16..16] generic short packet with virtual channel (M) discard
                                        *   by fifo OVerFlow status Clear                                             */
            uint32_t           : 7;
            __OM uint32_t FSRC : 1;    /*!< [24..24] Frame Start packet with virtual channel (M) Reception
                                        *   status Clear                                                              */
            __OM uint32_t FERC : 1;    /*!< [25..25] Frame End packet with virtual channel (M) Reception
                                        *   status Clear                                                              */
            __OM uint32_t LSRC : 1;    /*!< [26..26] Line Start packet with virtual channel (M) Reception
                                        *   status Clear                                                              */
            __OM uint32_t LERC : 1;    /*!< [27..27] Line End packet with virtual channel (M) Reception
                                        *   status Clear                                                              */
            __OM uint32_t ETRC : 1;    /*!< [28..28] EoTp packet with virtual channel (M) Reception status
                                        *   Clear                                                                     */
            uint32_t : 3;
        } VCSC9_b;
    };

    union
    {
        __IOM uint32_t VCIE9;          /*!< (@ 0x00000198) Virtual Channel (M) Interrupt Enable Register              */

        struct
        {
            __IOM uint32_t MLFE : 1;   /*!< [0..0] MaLFormed packet with virutal channel (M) detect interrupt
                                        *   Enable                                                                    */
            __IOM uint32_t ECDE : 1;   /*!< [1..1] ECc 2-bit (Double) error packet with virutal channel
                                        *   (M) Detect interrupt Enable                                               */
            __IOM uint32_t CRCE : 1;   /*!< [2..2] CRC error packet with virtual channel (M) detect interrupt
                                        *   Enable                                                                    */
            __IOM uint32_t IDEE : 1;   /*!< [3..3] ErrID packet with virtual channel (M) detect interrupt
                                        *   Enable                                                                    */
            __IOM uint32_t WCEE : 1;   /*!< [4..4] Word Count Error packet with virtual channel (M) detect
                                        *   interrupt Enable                                                          */
            __IOM uint32_t ECCE : 1;   /*!< [5..5] ECc 1-bit error (Corrected) packet with virtual channel
                                        *   (M) detect interrupt Enable                                               */
            __IOM uint32_t ECNE : 1;   /*!< [6..6] ECc No-error packet with virtual channel (M) detect interrupt
                                        *   Enable                                                                    */
            uint32_t            : 1;
            __IOM uint32_t FRSE : 1;   /*!< [8..8] errFRameSync of virtual channel (M) detect interrupt
                                        *   Enable                                                                    */
            __IOM uint32_t FRDE : 1;   /*!< [9..9] errFRameData of virtual channel (M) detect interrupt
                                        *   Enable                                                                    */
            uint32_t            : 6;
            __IOM uint32_t OVFE : 1;   /*!< [16..16] generic short packet with virtual channel (M) discard
                                        *   by fifo OVerFlow interrupt Enable                                         */
            uint32_t            : 7;
            __IOM uint32_t FSRE : 1;   /*!< [24..24] Frame Start packet with virtual channel (M) Reception
                                        *   interrupt Enable                                                          */
            __IOM uint32_t FERE : 1;   /*!< [25..25] Frame End packet with virtual channel (M) Reception
                                        *   interrupt Enable                                                          */
            __IOM uint32_t LSRE : 1;   /*!< [26..26] Line Start packet with virtual channel (M) Reception
                                        *   interrupt Enable                                                          */
            __IOM uint32_t LERE : 1;   /*!< [27..27] Line End packet with virtual channel (M) Reception
                                        *   interrupt Enable                                                          */
            __IOM uint32_t ETRE : 1;   /*!< [28..28] EoTp packet with virtual channel (M) Reception interrupt
                                        *   Enable                                                                    */
            uint32_t : 3;
        } VCIE9_b;
    };
    __IM uint32_t RESERVED19;

    union
    {
        __IM uint32_t VCST10;          /*!< (@ 0x000001A0) Virtual Channel (M) Status Register                        */

        struct
        {
            __IM uint32_t MLF : 1;     /*!< [0..0] MaLFormed packet with virutal channel (M) detect status            */
            __IM uint32_t ECD : 1;     /*!< [1..1] ECc 2-bit (Double) error packet with virutal channel
                                        *   (M) Detect status                                                         */
            __IM uint32_t CRC : 1;     /*!< [2..2] CRC error packet with virtual channel (M) detect status            */
            __IM uint32_t IDE : 1;     /*!< [3..3] ErrID packet with virtual channel (M) detect status                */
            __IM uint32_t WCE : 1;     /*!< [4..4] Word Count Error packet with virtual channel (M) detect
                                        *   status                                                                    */
            __IM uint32_t ECC : 1;     /*!< [5..5] ECc 1-bit error (Corrected) packet with virtual channel
                                        *   (M) detect status                                                         */
            __IM uint32_t ECN : 1;     /*!< [6..6] ECc No-error packet with virtual channel (M) detect status         */
            uint32_t          : 1;
            __IM uint32_t FRS : 1;     /*!< [8..8] errFRameSync of virtual channel (M) detect status                  */
            __IM uint32_t FRD : 1;     /*!< [9..9] errFRameData of virtual channel (M) detect status                  */
            uint32_t          : 6;
            __IM uint32_t OVF : 1;     /*!< [16..16] generic short packet with virtual channel (M) discard
                                        *   by fifo OVerFlow status                                                   */
            uint32_t          : 7;
            __IM uint32_t FSR : 1;     /*!< [24..24] Frame Start packet with virtual channel (M) Reception
                                        *   status                                                                    */
            __IM uint32_t FER : 1;     /*!< [25..25] Frame End packet with virtual channel (M) Reception
                                        *   status                                                                    */
            __IM uint32_t LSR : 1;     /*!< [26..26] Line Start packet with virtual channel (M) Reception
                                        *   status                                                                    */
            __IM uint32_t LER : 1;     /*!< [27..27] Line End packet with virtual channel (M) Reception
                                        *   status                                                                    */
            __IM uint32_t ETR : 1;     /*!< [28..28] EoTp packet with virtual channel (M) Reception status            */
            uint32_t          : 3;
        } VCST10_b;
    };

    union
    {
        __OM uint32_t VCSC10;          /*!< (@ 0x000001A4) Virtual Channel (M) Status Clear Register                  */

        struct
        {
            __OM uint32_t MLFC : 1;    /*!< [0..0] MaLFormed packet with virutal channel (M) detect status
                                        *   Clear                                                                     */
            __OM uint32_t ECDC : 1;    /*!< [1..1] ECc 2-bit (Double) error packet with virutal channel
                                        *   (M) Detect status Clear                                                   */
            __OM uint32_t CRCC : 1;    /*!< [2..2] CRC error packet with virtual channel (M) detect status
                                        *   Clear                                                                     */
            __OM uint32_t IDEC : 1;    /*!< [3..3] ErrID packet with virtual channel (M) detect status Clear          */
            __OM uint32_t WCEC : 1;    /*!< [4..4] Word Count Error packet with virtual channel (M) detect
                                        *   status Clear                                                              */
            __OM uint32_t ECCC : 1;    /*!< [5..5] ECc 1-bit error (Corrected) packet with virtual channel
                                        *   (M) detect status Clear                                                   */
            __OM uint32_t ECNC : 1;    /*!< [6..6] ECc No-error packet with virtual channel (M) detect status
                                        *   Clear                                                                     */
            uint32_t            : 1;
            __OM uint32_t FRSC  : 1;   /*!< [8..8] errFRameSync of virtual channel (M) detect status Clear            */
            __OM uint32_t FRDC  : 1;   /*!< [9..9] errFRameData of virtual channel (M) detect status Clear            */
            uint32_t            : 4;
            __OM uint32_t AMLFC : 1;   /*!< [14..14] MaLFormed packet with any virutal channels detect status
                                        *   Clear                                                                     */
            __OM uint32_t AECDC : 1;   /*!< [15..15] ECc 2-bit (Double) error packet with any virutal channels
                                        *   Detect status Clear                                                       */
            __OM uint32_t OVFC : 1;    /*!< [16..16] generic short packet with virtual channel (M) discard
                                        *   by fifo OVerFlow status Clear                                             */
            uint32_t           : 7;
            __OM uint32_t FSRC : 1;    /*!< [24..24] Frame Start packet with virtual channel (M) Reception
                                        *   status Clear                                                              */
            __OM uint32_t FERC : 1;    /*!< [25..25] Frame End packet with virtual channel (M) Reception
                                        *   status Clear                                                              */
            __OM uint32_t LSRC : 1;    /*!< [26..26] Line Start packet with virtual channel (M) Reception
                                        *   status Clear                                                              */
            __OM uint32_t LERC : 1;    /*!< [27..27] Line End packet with virtual channel (M) Reception
                                        *   status Clear                                                              */
            __OM uint32_t ETRC : 1;    /*!< [28..28] EoTp packet with virtual channel (M) Reception status
                                        *   Clear                                                                     */
            uint32_t : 3;
        } VCSC10_b;
    };

    union
    {
        __IOM uint32_t VCIE10;         /*!< (@ 0x000001A8) Virtual Channel (M) Interrupt Enable Register              */

        struct
        {
            __IOM uint32_t MLFE : 1;   /*!< [0..0] MaLFormed packet with virutal channel (M) detect interrupt
                                        *   Enable                                                                    */
            __IOM uint32_t ECDE : 1;   /*!< [1..1] ECc 2-bit (Double) error packet with virutal channel
                                        *   (M) Detect interrupt Enable                                               */
            __IOM uint32_t CRCE : 1;   /*!< [2..2] CRC error packet with virtual channel (M) detect interrupt
                                        *   Enable                                                                    */
            __IOM uint32_t IDEE : 1;   /*!< [3..3] ErrID packet with virtual channel (M) detect interrupt
                                        *   Enable                                                                    */
            __IOM uint32_t WCEE : 1;   /*!< [4..4] Word Count Error packet with virtual channel (M) detect
                                        *   interrupt Enable                                                          */
            __IOM uint32_t ECCE : 1;   /*!< [5..5] ECc 1-bit error (Corrected) packet with virtual channel
                                        *   (M) detect interrupt Enable                                               */
            __IOM uint32_t ECNE : 1;   /*!< [6..6] ECc No-error packet with virtual channel (M) detect interrupt
                                        *   Enable                                                                    */
            uint32_t            : 1;
            __IOM uint32_t FRSE : 1;   /*!< [8..8] errFRameSync of virtual channel (M) detect interrupt
                                        *   Enable                                                                    */
            __IOM uint32_t FRDE : 1;   /*!< [9..9] errFRameData of virtual channel (M) detect interrupt
                                        *   Enable                                                                    */
            uint32_t            : 6;
            __IOM uint32_t OVFE : 1;   /*!< [16..16] generic short packet with virtual channel (M) discard
                                        *   by fifo OVerFlow interrupt Enable                                         */
            uint32_t            : 7;
            __IOM uint32_t FSRE : 1;   /*!< [24..24] Frame Start packet with virtual channel (M) Reception
                                        *   interrupt Enable                                                          */
            __IOM uint32_t FERE : 1;   /*!< [25..25] Frame End packet with virtual channel (M) Reception
                                        *   interrupt Enable                                                          */
            __IOM uint32_t LSRE : 1;   /*!< [26..26] Line Start packet with virtual channel (M) Reception
                                        *   interrupt Enable                                                          */
            __IOM uint32_t LERE : 1;   /*!< [27..27] Line End packet with virtual channel (M) Reception
                                        *   interrupt Enable                                                          */
            __IOM uint32_t ETRE : 1;   /*!< [28..28] EoTp packet with virtual channel (M) Reception interrupt
                                        *   Enable                                                                    */
            uint32_t : 3;
        } VCIE10_b;
    };
    __IM uint32_t RESERVED20;

    union
    {
        __IM uint32_t VCST11;          /*!< (@ 0x000001B0) Virtual Channel (M) Status Register                        */

        struct
        {
            __IM uint32_t MLF : 1;     /*!< [0..0] MaLFormed packet with virutal channel (M) detect status            */
            __IM uint32_t ECD : 1;     /*!< [1..1] ECc 2-bit (Double) error packet with virutal channel
                                        *   (M) Detect status                                                         */
            __IM uint32_t CRC : 1;     /*!< [2..2] CRC error packet with virtual channel (M) detect status            */
            __IM uint32_t IDE : 1;     /*!< [3..3] ErrID packet with virtual channel (M) detect status                */
            __IM uint32_t WCE : 1;     /*!< [4..4] Word Count Error packet with virtual channel (M) detect
                                        *   status                                                                    */
            __IM uint32_t ECC : 1;     /*!< [5..5] ECc 1-bit error (Corrected) packet with virtual channel
                                        *   (M) detect status                                                         */
            __IM uint32_t ECN : 1;     /*!< [6..6] ECc No-error packet with virtual channel (M) detect status         */
            uint32_t          : 1;
            __IM uint32_t FRS : 1;     /*!< [8..8] errFRameSync of virtual channel (M) detect status                  */
            __IM uint32_t FRD : 1;     /*!< [9..9] errFRameData of virtual channel (M) detect status                  */
            uint32_t          : 6;
            __IM uint32_t OVF : 1;     /*!< [16..16] generic short packet with virtual channel (M) discard
                                        *   by fifo OVerFlow status                                                   */
            uint32_t          : 7;
            __IM uint32_t FSR : 1;     /*!< [24..24] Frame Start packet with virtual channel (M) Reception
                                        *   status                                                                    */
            __IM uint32_t FER : 1;     /*!< [25..25] Frame End packet with virtual channel (M) Reception
                                        *   status                                                                    */
            __IM uint32_t LSR : 1;     /*!< [26..26] Line Start packet with virtual channel (M) Reception
                                        *   status                                                                    */
            __IM uint32_t LER : 1;     /*!< [27..27] Line End packet with virtual channel (M) Reception
                                        *   status                                                                    */
            __IM uint32_t ETR : 1;     /*!< [28..28] EoTp packet with virtual channel (M) Reception status            */
            uint32_t          : 3;
        } VCST11_b;
    };

    union
    {
        __OM uint32_t VCSC11;          /*!< (@ 0x000001B4) Virtual Channel (M) Status Clear Register                  */

        struct
        {
            __OM uint32_t MLFC : 1;    /*!< [0..0] MaLFormed packet with virutal channel (M) detect status
                                        *   Clear                                                                     */
            __OM uint32_t ECDC : 1;    /*!< [1..1] ECc 2-bit (Double) error packet with virutal channel
                                        *   (M) Detect status Clear                                                   */
            __OM uint32_t CRCC : 1;    /*!< [2..2] CRC error packet with virtual channel (M) detect status
                                        *   Clear                                                                     */
            __OM uint32_t IDEC : 1;    /*!< [3..3] ErrID packet with virtual channel (M) detect status Clear          */
            __OM uint32_t WCEC : 1;    /*!< [4..4] Word Count Error packet with virtual channel (M) detect
                                        *   status Clear                                                              */
            __OM uint32_t ECCC : 1;    /*!< [5..5] ECc 1-bit error (Corrected) packet with virtual channel
                                        *   (M) detect status Clear                                                   */
            __OM uint32_t ECNC : 1;    /*!< [6..6] ECc No-error packet with virtual channel (M) detect status
                                        *   Clear                                                                     */
            uint32_t            : 1;
            __OM uint32_t FRSC  : 1;   /*!< [8..8] errFRameSync of virtual channel (M) detect status Clear            */
            __OM uint32_t FRDC  : 1;   /*!< [9..9] errFRameData of virtual channel (M) detect status Clear            */
            uint32_t            : 4;
            __OM uint32_t AMLFC : 1;   /*!< [14..14] MaLFormed packet with any virutal channels detect status
                                        *   Clear                                                                     */
            __OM uint32_t AECDC : 1;   /*!< [15..15] ECc 2-bit (Double) error packet with any virutal channels
                                        *   Detect status Clear                                                       */
            __OM uint32_t OVFC : 1;    /*!< [16..16] generic short packet with virtual channel (M) discard
                                        *   by fifo OVerFlow status Clear                                             */
            uint32_t           : 7;
            __OM uint32_t FSRC : 1;    /*!< [24..24] Frame Start packet with virtual channel (M) Reception
                                        *   status Clear                                                              */
            __OM uint32_t FERC : 1;    /*!< [25..25] Frame End packet with virtual channel (M) Reception
                                        *   status Clear                                                              */
            __OM uint32_t LSRC : 1;    /*!< [26..26] Line Start packet with virtual channel (M) Reception
                                        *   status Clear                                                              */
            __OM uint32_t LERC : 1;    /*!< [27..27] Line End packet with virtual channel (M) Reception
                                        *   status Clear                                                              */
            __OM uint32_t ETRC : 1;    /*!< [28..28] EoTp packet with virtual channel (M) Reception status
                                        *   Clear                                                                     */
            uint32_t : 3;
        } VCSC11_b;
    };

    union
    {
        __IOM uint32_t VCIE11;         /*!< (@ 0x000001B8) Virtual Channel (M) Interrupt Enable Register              */

        struct
        {
            __IOM uint32_t MLFE : 1;   /*!< [0..0] MaLFormed packet with virutal channel (M) detect interrupt
                                        *   Enable                                                                    */
            __IOM uint32_t ECDE : 1;   /*!< [1..1] ECc 2-bit (Double) error packet with virutal channel
                                        *   (M) Detect interrupt Enable                                               */
            __IOM uint32_t CRCE : 1;   /*!< [2..2] CRC error packet with virtual channel (M) detect interrupt
                                        *   Enable                                                                    */
            __IOM uint32_t IDEE : 1;   /*!< [3..3] ErrID packet with virtual channel (M) detect interrupt
                                        *   Enable                                                                    */
            __IOM uint32_t WCEE : 1;   /*!< [4..4] Word Count Error packet with virtual channel (M) detect
                                        *   interrupt Enable                                                          */
            __IOM uint32_t ECCE : 1;   /*!< [5..5] ECc 1-bit error (Corrected) packet with virtual channel
                                        *   (M) detect interrupt Enable                                               */
            __IOM uint32_t ECNE : 1;   /*!< [6..6] ECc No-error packet with virtual channel (M) detect interrupt
                                        *   Enable                                                                    */
            uint32_t            : 1;
            __IOM uint32_t FRSE : 1;   /*!< [8..8] errFRameSync of virtual channel (M) detect interrupt
                                        *   Enable                                                                    */
            __IOM uint32_t FRDE : 1;   /*!< [9..9] errFRameData of virtual channel (M) detect interrupt
                                        *   Enable                                                                    */
            uint32_t            : 6;
            __IOM uint32_t OVFE : 1;   /*!< [16..16] generic short packet with virtual channel (M) discard
                                        *   by fifo OVerFlow interrupt Enable                                         */
            uint32_t            : 7;
            __IOM uint32_t FSRE : 1;   /*!< [24..24] Frame Start packet with virtual channel (M) Reception
                                        *   interrupt Enable                                                          */
            __IOM uint32_t FERE : 1;   /*!< [25..25] Frame End packet with virtual channel (M) Reception
                                        *   interrupt Enable                                                          */
            __IOM uint32_t LSRE : 1;   /*!< [26..26] Line Start packet with virtual channel (M) Reception
                                        *   interrupt Enable                                                          */
            __IOM uint32_t LERE : 1;   /*!< [27..27] Line End packet with virtual channel (M) Reception
                                        *   interrupt Enable                                                          */
            __IOM uint32_t ETRE : 1;   /*!< [28..28] EoTp packet with virtual channel (M) Reception interrupt
                                        *   Enable                                                                    */
            uint32_t : 3;
        } VCIE11_b;
    };
    __IM uint32_t RESERVED21;

    union
    {
        __IM uint32_t VCST12;          /*!< (@ 0x000001C0) Virtual Channel (M) Status Register                        */

        struct
        {
            __IM uint32_t MLF : 1;     /*!< [0..0] MaLFormed packet with virutal channel (M) detect status            */
            __IM uint32_t ECD : 1;     /*!< [1..1] ECc 2-bit (Double) error packet with virutal channel
                                        *   (M) Detect status                                                         */
            __IM uint32_t CRC : 1;     /*!< [2..2] CRC error packet with virtual channel (M) detect status            */
            __IM uint32_t IDE : 1;     /*!< [3..3] ErrID packet with virtual channel (M) detect status                */
            __IM uint32_t WCE : 1;     /*!< [4..4] Word Count Error packet with virtual channel (M) detect
                                        *   status                                                                    */
            __IM uint32_t ECC : 1;     /*!< [5..5] ECc 1-bit error (Corrected) packet with virtual channel
                                        *   (M) detect status                                                         */
            __IM uint32_t ECN : 1;     /*!< [6..6] ECc No-error packet with virtual channel (M) detect status         */
            uint32_t          : 1;
            __IM uint32_t FRS : 1;     /*!< [8..8] errFRameSync of virtual channel (M) detect status                  */
            __IM uint32_t FRD : 1;     /*!< [9..9] errFRameData of virtual channel (M) detect status                  */
            uint32_t          : 6;
            __IM uint32_t OVF : 1;     /*!< [16..16] generic short packet with virtual channel (M) discard
                                        *   by fifo OVerFlow status                                                   */
            uint32_t          : 7;
            __IM uint32_t FSR : 1;     /*!< [24..24] Frame Start packet with virtual channel (M) Reception
                                        *   status                                                                    */
            __IM uint32_t FER : 1;     /*!< [25..25] Frame End packet with virtual channel (M) Reception
                                        *   status                                                                    */
            __IM uint32_t LSR : 1;     /*!< [26..26] Line Start packet with virtual channel (M) Reception
                                        *   status                                                                    */
            __IM uint32_t LER : 1;     /*!< [27..27] Line End packet with virtual channel (M) Reception
                                        *   status                                                                    */
            __IM uint32_t ETR : 1;     /*!< [28..28] EoTp packet with virtual channel (M) Reception status            */
            uint32_t          : 3;
        } VCST12_b;
    };

    union
    {
        __OM uint32_t VCSC12;          /*!< (@ 0x000001C4) Virtual Channel (M) Status Clear Register                  */

        struct
        {
            __OM uint32_t MLFC : 1;    /*!< [0..0] MaLFormed packet with virutal channel (M) detect status
                                        *   Clear                                                                     */
            __OM uint32_t ECDC : 1;    /*!< [1..1] ECc 2-bit (Double) error packet with virutal channel
                                        *   (M) Detect status Clear                                                   */
            __OM uint32_t CRCC : 1;    /*!< [2..2] CRC error packet with virtual channel (M) detect status
                                        *   Clear                                                                     */
            __OM uint32_t IDEC : 1;    /*!< [3..3] ErrID packet with virtual channel (M) detect status Clear          */
            __OM uint32_t WCEC : 1;    /*!< [4..4] Word Count Error packet with virtual channel (M) detect
                                        *   status Clear                                                              */
            __OM uint32_t ECCC : 1;    /*!< [5..5] ECc 1-bit error (Corrected) packet with virtual channel
                                        *   (M) detect status Clear                                                   */
            __OM uint32_t ECNC : 1;    /*!< [6..6] ECc No-error packet with virtual channel (M) detect status
                                        *   Clear                                                                     */
            uint32_t            : 1;
            __OM uint32_t FRSC  : 1;   /*!< [8..8] errFRameSync of virtual channel (M) detect status Clear            */
            __OM uint32_t FRDC  : 1;   /*!< [9..9] errFRameData of virtual channel (M) detect status Clear            */
            uint32_t            : 4;
            __OM uint32_t AMLFC : 1;   /*!< [14..14] MaLFormed packet with any virutal channels detect status
                                        *   Clear                                                                     */
            __OM uint32_t AECDC : 1;   /*!< [15..15] ECc 2-bit (Double) error packet with any virutal channels
                                        *   Detect status Clear                                                       */
            __OM uint32_t OVFC : 1;    /*!< [16..16] generic short packet with virtual channel (M) discard
                                        *   by fifo OVerFlow status Clear                                             */
            uint32_t           : 7;
            __OM uint32_t FSRC : 1;    /*!< [24..24] Frame Start packet with virtual channel (M) Reception
                                        *   status Clear                                                              */
            __OM uint32_t FERC : 1;    /*!< [25..25] Frame End packet with virtual channel (M) Reception
                                        *   status Clear                                                              */
            __OM uint32_t LSRC : 1;    /*!< [26..26] Line Start packet with virtual channel (M) Reception
                                        *   status Clear                                                              */
            __OM uint32_t LERC : 1;    /*!< [27..27] Line End packet with virtual channel (M) Reception
                                        *   status Clear                                                              */
            __OM uint32_t ETRC : 1;    /*!< [28..28] EoTp packet with virtual channel (M) Reception status
                                        *   Clear                                                                     */
            uint32_t : 3;
        } VCSC12_b;
    };

    union
    {
        __IOM uint32_t VCIE12;         /*!< (@ 0x000001C8) Virtual Channel (M) Interrupt Enable Register              */

        struct
        {
            __IOM uint32_t MLFE : 1;   /*!< [0..0] MaLFormed packet with virutal channel (M) detect interrupt
                                        *   Enable                                                                    */
            __IOM uint32_t ECDE : 1;   /*!< [1..1] ECc 2-bit (Double) error packet with virutal channel
                                        *   (M) Detect interrupt Enable                                               */
            __IOM uint32_t CRCE : 1;   /*!< [2..2] CRC error packet with virtual channel (M) detect interrupt
                                        *   Enable                                                                    */
            __IOM uint32_t IDEE : 1;   /*!< [3..3] ErrID packet with virtual channel (M) detect interrupt
                                        *   Enable                                                                    */
            __IOM uint32_t WCEE : 1;   /*!< [4..4] Word Count Error packet with virtual channel (M) detect
                                        *   interrupt Enable                                                          */
            __IOM uint32_t ECCE : 1;   /*!< [5..5] ECc 1-bit error (Corrected) packet with virtual channel
                                        *   (M) detect interrupt Enable                                               */
            __IOM uint32_t ECNE : 1;   /*!< [6..6] ECc No-error packet with virtual channel (M) detect interrupt
                                        *   Enable                                                                    */
            uint32_t            : 1;
            __IOM uint32_t FRSE : 1;   /*!< [8..8] errFRameSync of virtual channel (M) detect interrupt
                                        *   Enable                                                                    */
            __IOM uint32_t FRDE : 1;   /*!< [9..9] errFRameData of virtual channel (M) detect interrupt
                                        *   Enable                                                                    */
            uint32_t            : 6;
            __IOM uint32_t OVFE : 1;   /*!< [16..16] generic short packet with virtual channel (M) discard
                                        *   by fifo OVerFlow interrupt Enable                                         */
            uint32_t            : 7;
            __IOM uint32_t FSRE : 1;   /*!< [24..24] Frame Start packet with virtual channel (M) Reception
                                        *   interrupt Enable                                                          */
            __IOM uint32_t FERE : 1;   /*!< [25..25] Frame End packet with virtual channel (M) Reception
                                        *   interrupt Enable                                                          */
            __IOM uint32_t LSRE : 1;   /*!< [26..26] Line Start packet with virtual channel (M) Reception
                                        *   interrupt Enable                                                          */
            __IOM uint32_t LERE : 1;   /*!< [27..27] Line End packet with virtual channel (M) Reception
                                        *   interrupt Enable                                                          */
            __IOM uint32_t ETRE : 1;   /*!< [28..28] EoTp packet with virtual channel (M) Reception interrupt
                                        *   Enable                                                                    */
            uint32_t : 3;
        } VCIE12_b;
    };
    __IM uint32_t RESERVED22;

    union
    {
        __IM uint32_t VCST13;          /*!< (@ 0x000001D0) Virtual Channel (M) Status Register                        */

        struct
        {
            __IM uint32_t MLF : 1;     /*!< [0..0] MaLFormed packet with virutal channel (M) detect status            */
            __IM uint32_t ECD : 1;     /*!< [1..1] ECc 2-bit (Double) error packet with virutal channel
                                        *   (M) Detect status                                                         */
            __IM uint32_t CRC : 1;     /*!< [2..2] CRC error packet with virtual channel (M) detect status            */
            __IM uint32_t IDE : 1;     /*!< [3..3] ErrID packet with virtual channel (M) detect status                */
            __IM uint32_t WCE : 1;     /*!< [4..4] Word Count Error packet with virtual channel (M) detect
                                        *   status                                                                    */
            __IM uint32_t ECC : 1;     /*!< [5..5] ECc 1-bit error (Corrected) packet with virtual channel
                                        *   (M) detect status                                                         */
            __IM uint32_t ECN : 1;     /*!< [6..6] ECc No-error packet with virtual channel (M) detect status         */
            uint32_t          : 1;
            __IM uint32_t FRS : 1;     /*!< [8..8] errFRameSync of virtual channel (M) detect status                  */
            __IM uint32_t FRD : 1;     /*!< [9..9] errFRameData of virtual channel (M) detect status                  */
            uint32_t          : 6;
            __IM uint32_t OVF : 1;     /*!< [16..16] generic short packet with virtual channel (M) discard
                                        *   by fifo OVerFlow status                                                   */
            uint32_t          : 7;
            __IM uint32_t FSR : 1;     /*!< [24..24] Frame Start packet with virtual channel (M) Reception
                                        *   status                                                                    */
            __IM uint32_t FER : 1;     /*!< [25..25] Frame End packet with virtual channel (M) Reception
                                        *   status                                                                    */
            __IM uint32_t LSR : 1;     /*!< [26..26] Line Start packet with virtual channel (M) Reception
                                        *   status                                                                    */
            __IM uint32_t LER : 1;     /*!< [27..27] Line End packet with virtual channel (M) Reception
                                        *   status                                                                    */
            __IM uint32_t ETR : 1;     /*!< [28..28] EoTp packet with virtual channel (M) Reception status            */
            uint32_t          : 3;
        } VCST13_b;
    };

    union
    {
        __OM uint32_t VCSC13;          /*!< (@ 0x000001D4) Virtual Channel (M) Status Clear Register                  */

        struct
        {
            __OM uint32_t MLFC : 1;    /*!< [0..0] MaLFormed packet with virutal channel (M) detect status
                                        *   Clear                                                                     */
            __OM uint32_t ECDC : 1;    /*!< [1..1] ECc 2-bit (Double) error packet with virutal channel
                                        *   (M) Detect status Clear                                                   */
            __OM uint32_t CRCC : 1;    /*!< [2..2] CRC error packet with virtual channel (M) detect status
                                        *   Clear                                                                     */
            __OM uint32_t IDEC : 1;    /*!< [3..3] ErrID packet with virtual channel (M) detect status Clear          */
            __OM uint32_t WCEC : 1;    /*!< [4..4] Word Count Error packet with virtual channel (M) detect
                                        *   status Clear                                                              */
            __OM uint32_t ECCC : 1;    /*!< [5..5] ECc 1-bit error (Corrected) packet with virtual channel
                                        *   (M) detect status Clear                                                   */
            __OM uint32_t ECNC : 1;    /*!< [6..6] ECc No-error packet with virtual channel (M) detect status
                                        *   Clear                                                                     */
            uint32_t            : 1;
            __OM uint32_t FRSC  : 1;   /*!< [8..8] errFRameSync of virtual channel (M) detect status Clear            */
            __OM uint32_t FRDC  : 1;   /*!< [9..9] errFRameData of virtual channel (M) detect status Clear            */
            uint32_t            : 4;
            __OM uint32_t AMLFC : 1;   /*!< [14..14] MaLFormed packet with any virutal channels detect status
                                        *   Clear                                                                     */
            __OM uint32_t AECDC : 1;   /*!< [15..15] ECc 2-bit (Double) error packet with any virutal channels
                                        *   Detect status Clear                                                       */
            __OM uint32_t OVFC : 1;    /*!< [16..16] generic short packet with virtual channel (M) discard
                                        *   by fifo OVerFlow status Clear                                             */
            uint32_t           : 7;
            __OM uint32_t FSRC : 1;    /*!< [24..24] Frame Start packet with virtual channel (M) Reception
                                        *   status Clear                                                              */
            __OM uint32_t FERC : 1;    /*!< [25..25] Frame End packet with virtual channel (M) Reception
                                        *   status Clear                                                              */
            __OM uint32_t LSRC : 1;    /*!< [26..26] Line Start packet with virtual channel (M) Reception
                                        *   status Clear                                                              */
            __OM uint32_t LERC : 1;    /*!< [27..27] Line End packet with virtual channel (M) Reception
                                        *   status Clear                                                              */
            __OM uint32_t ETRC : 1;    /*!< [28..28] EoTp packet with virtual channel (M) Reception status
                                        *   Clear                                                                     */
            uint32_t : 3;
        } VCSC13_b;
    };

    union
    {
        __IOM uint32_t VCIE13;         /*!< (@ 0x000001D8) Virtual Channel (M) Interrupt Enable Register              */

        struct
        {
            __IOM uint32_t MLFE : 1;   /*!< [0..0] MaLFormed packet with virutal channel (M) detect interrupt
                                        *   Enable                                                                    */
            __IOM uint32_t ECDE : 1;   /*!< [1..1] ECc 2-bit (Double) error packet with virutal channel
                                        *   (M) Detect interrupt Enable                                               */
            __IOM uint32_t CRCE : 1;   /*!< [2..2] CRC error packet with virtual channel (M) detect interrupt
                                        *   Enable                                                                    */
            __IOM uint32_t IDEE : 1;   /*!< [3..3] ErrID packet with virtual channel (M) detect interrupt
                                        *   Enable                                                                    */
            __IOM uint32_t WCEE : 1;   /*!< [4..4] Word Count Error packet with virtual channel (M) detect
                                        *   interrupt Enable                                                          */
            __IOM uint32_t ECCE : 1;   /*!< [5..5] ECc 1-bit error (Corrected) packet with virtual channel
                                        *   (M) detect interrupt Enable                                               */
            __IOM uint32_t ECNE : 1;   /*!< [6..6] ECc No-error packet with virtual channel (M) detect interrupt
                                        *   Enable                                                                    */
            uint32_t            : 1;
            __IOM uint32_t FRSE : 1;   /*!< [8..8] errFRameSync of virtual channel (M) detect interrupt
                                        *   Enable                                                                    */
            __IOM uint32_t FRDE : 1;   /*!< [9..9] errFRameData of virtual channel (M) detect interrupt
                                        *   Enable                                                                    */
            uint32_t            : 6;
            __IOM uint32_t OVFE : 1;   /*!< [16..16] generic short packet with virtual channel (M) discard
                                        *   by fifo OVerFlow interrupt Enable                                         */
            uint32_t            : 7;
            __IOM uint32_t FSRE : 1;   /*!< [24..24] Frame Start packet with virtual channel (M) Reception
                                        *   interrupt Enable                                                          */
            __IOM uint32_t FERE : 1;   /*!< [25..25] Frame End packet with virtual channel (M) Reception
                                        *   interrupt Enable                                                          */
            __IOM uint32_t LSRE : 1;   /*!< [26..26] Line Start packet with virtual channel (M) Reception
                                        *   interrupt Enable                                                          */
            __IOM uint32_t LERE : 1;   /*!< [27..27] Line End packet with virtual channel (M) Reception
                                        *   interrupt Enable                                                          */
            __IOM uint32_t ETRE : 1;   /*!< [28..28] EoTp packet with virtual channel (M) Reception interrupt
                                        *   Enable                                                                    */
            uint32_t : 3;
        } VCIE13_b;
    };
    __IM uint32_t RESERVED23;

    union
    {
        __IM uint32_t VCST14;          /*!< (@ 0x000001E0) Virtual Channel (M) Status Register                        */

        struct
        {
            __IM uint32_t MLF : 1;     /*!< [0..0] MaLFormed packet with virutal channel (M) detect status            */
            __IM uint32_t ECD : 1;     /*!< [1..1] ECc 2-bit (Double) error packet with virutal channel
                                        *   (M) Detect status                                                         */
            __IM uint32_t CRC : 1;     /*!< [2..2] CRC error packet with virtual channel (M) detect status            */
            __IM uint32_t IDE : 1;     /*!< [3..3] ErrID packet with virtual channel (M) detect status                */
            __IM uint32_t WCE : 1;     /*!< [4..4] Word Count Error packet with virtual channel (M) detect
                                        *   status                                                                    */
            __IM uint32_t ECC : 1;     /*!< [5..5] ECc 1-bit error (Corrected) packet with virtual channel
                                        *   (M) detect status                                                         */
            __IM uint32_t ECN : 1;     /*!< [6..6] ECc No-error packet with virtual channel (M) detect status         */
            uint32_t          : 1;
            __IM uint32_t FRS : 1;     /*!< [8..8] errFRameSync of virtual channel (M) detect status                  */
            __IM uint32_t FRD : 1;     /*!< [9..9] errFRameData of virtual channel (M) detect status                  */
            uint32_t          : 6;
            __IM uint32_t OVF : 1;     /*!< [16..16] generic short packet with virtual channel (M) discard
                                        *   by fifo OVerFlow status                                                   */
            uint32_t          : 7;
            __IM uint32_t FSR : 1;     /*!< [24..24] Frame Start packet with virtual channel (M) Reception
                                        *   status                                                                    */
            __IM uint32_t FER : 1;     /*!< [25..25] Frame End packet with virtual channel (M) Reception
                                        *   status                                                                    */
            __IM uint32_t LSR : 1;     /*!< [26..26] Line Start packet with virtual channel (M) Reception
                                        *   status                                                                    */
            __IM uint32_t LER : 1;     /*!< [27..27] Line End packet with virtual channel (M) Reception
                                        *   status                                                                    */
            __IM uint32_t ETR : 1;     /*!< [28..28] EoTp packet with virtual channel (M) Reception status            */
            uint32_t          : 3;
        } VCST14_b;
    };

    union
    {
        __OM uint32_t VCSC14;          /*!< (@ 0x000001E4) Virtual Channel (M) Status Clear Register                  */

        struct
        {
            __OM uint32_t MLFC : 1;    /*!< [0..0] MaLFormed packet with virutal channel (M) detect status
                                        *   Clear                                                                     */
            __OM uint32_t ECDC : 1;    /*!< [1..1] ECc 2-bit (Double) error packet with virutal channel
                                        *   (M) Detect status Clear                                                   */
            __OM uint32_t CRCC : 1;    /*!< [2..2] CRC error packet with virtual channel (M) detect status
                                        *   Clear                                                                     */
            __OM uint32_t IDEC : 1;    /*!< [3..3] ErrID packet with virtual channel (M) detect status Clear          */
            __OM uint32_t WCEC : 1;    /*!< [4..4] Word Count Error packet with virtual channel (M) detect
                                        *   status Clear                                                              */
            __OM uint32_t ECCC : 1;    /*!< [5..5] ECc 1-bit error (Corrected) packet with virtual channel
                                        *   (M) detect status Clear                                                   */
            __OM uint32_t ECNC : 1;    /*!< [6..6] ECc No-error packet with virtual channel (M) detect status
                                        *   Clear                                                                     */
            uint32_t            : 1;
            __OM uint32_t FRSC  : 1;   /*!< [8..8] errFRameSync of virtual channel (M) detect status Clear            */
            __OM uint32_t FRDC  : 1;   /*!< [9..9] errFRameData of virtual channel (M) detect status Clear            */
            uint32_t            : 4;
            __OM uint32_t AMLFC : 1;   /*!< [14..14] MaLFormed packet with any virutal channels detect status
                                        *   Clear                                                                     */
            __OM uint32_t AECDC : 1;   /*!< [15..15] ECc 2-bit (Double) error packet with any virutal channels
                                        *   Detect status Clear                                                       */
            __OM uint32_t OVFC : 1;    /*!< [16..16] generic short packet with virtual channel (M) discard
                                        *   by fifo OVerFlow status Clear                                             */
            uint32_t           : 7;
            __OM uint32_t FSRC : 1;    /*!< [24..24] Frame Start packet with virtual channel (M) Reception
                                        *   status Clear                                                              */
            __OM uint32_t FERC : 1;    /*!< [25..25] Frame End packet with virtual channel (M) Reception
                                        *   status Clear                                                              */
            __OM uint32_t LSRC : 1;    /*!< [26..26] Line Start packet with virtual channel (M) Reception
                                        *   status Clear                                                              */
            __OM uint32_t LERC : 1;    /*!< [27..27] Line End packet with virtual channel (M) Reception
                                        *   status Clear                                                              */
            __OM uint32_t ETRC : 1;    /*!< [28..28] EoTp packet with virtual channel (M) Reception status
                                        *   Clear                                                                     */
            uint32_t : 3;
        } VCSC14_b;
    };

    union
    {
        __IOM uint32_t VCIE14;         /*!< (@ 0x000001E8) Virtual Channel (M) Interrupt Enable Register              */

        struct
        {
            __IOM uint32_t MLFE : 1;   /*!< [0..0] MaLFormed packet with virutal channel (M) detect interrupt
                                        *   Enable                                                                    */
            __IOM uint32_t ECDE : 1;   /*!< [1..1] ECc 2-bit (Double) error packet with virutal channel
                                        *   (M) Detect interrupt Enable                                               */
            __IOM uint32_t CRCE : 1;   /*!< [2..2] CRC error packet with virtual channel (M) detect interrupt
                                        *   Enable                                                                    */
            __IOM uint32_t IDEE : 1;   /*!< [3..3] ErrID packet with virtual channel (M) detect interrupt
                                        *   Enable                                                                    */
            __IOM uint32_t WCEE : 1;   /*!< [4..4] Word Count Error packet with virtual channel (M) detect
                                        *   interrupt Enable                                                          */
            __IOM uint32_t ECCE : 1;   /*!< [5..5] ECc 1-bit error (Corrected) packet with virtual channel
                                        *   (M) detect interrupt Enable                                               */
            __IOM uint32_t ECNE : 1;   /*!< [6..6] ECc No-error packet with virtual channel (M) detect interrupt
                                        *   Enable                                                                    */
            uint32_t            : 1;
            __IOM uint32_t FRSE : 1;   /*!< [8..8] errFRameSync of virtual channel (M) detect interrupt
                                        *   Enable                                                                    */
            __IOM uint32_t FRDE : 1;   /*!< [9..9] errFRameData of virtual channel (M) detect interrupt
                                        *   Enable                                                                    */
            uint32_t            : 6;
            __IOM uint32_t OVFE : 1;   /*!< [16..16] generic short packet with virtual channel (M) discard
                                        *   by fifo OVerFlow interrupt Enable                                         */
            uint32_t            : 7;
            __IOM uint32_t FSRE : 1;   /*!< [24..24] Frame Start packet with virtual channel (M) Reception
                                        *   interrupt Enable                                                          */
            __IOM uint32_t FERE : 1;   /*!< [25..25] Frame End packet with virtual channel (M) Reception
                                        *   interrupt Enable                                                          */
            __IOM uint32_t LSRE : 1;   /*!< [26..26] Line Start packet with virtual channel (M) Reception
                                        *   interrupt Enable                                                          */
            __IOM uint32_t LERE : 1;   /*!< [27..27] Line End packet with virtual channel (M) Reception
                                        *   interrupt Enable                                                          */
            __IOM uint32_t ETRE : 1;   /*!< [28..28] EoTp packet with virtual channel (M) Reception interrupt
                                        *   Enable                                                                    */
            uint32_t : 3;
        } VCIE14_b;
    };
    __IM uint32_t RESERVED24;

    union
    {
        __IM uint32_t VCST15;          /*!< (@ 0x000001F0) Virtual Channel (M) Status Register                        */

        struct
        {
            __IM uint32_t MLF : 1;     /*!< [0..0] MaLFormed packet with virutal channel (M) detect status            */
            __IM uint32_t ECD : 1;     /*!< [1..1] ECc 2-bit (Double) error packet with virutal channel
                                        *   (M) Detect status                                                         */
            __IM uint32_t CRC : 1;     /*!< [2..2] CRC error packet with virtual channel (M) detect status            */
            __IM uint32_t IDE : 1;     /*!< [3..3] ErrID packet with virtual channel (M) detect status                */
            __IM uint32_t WCE : 1;     /*!< [4..4] Word Count Error packet with virtual channel (M) detect
                                        *   status                                                                    */
            __IM uint32_t ECC : 1;     /*!< [5..5] ECc 1-bit error (Corrected) packet with virtual channel
                                        *   (M) detect status                                                         */
            __IM uint32_t ECN : 1;     /*!< [6..6] ECc No-error packet with virtual channel (M) detect status         */
            uint32_t          : 1;
            __IM uint32_t FRS : 1;     /*!< [8..8] errFRameSync of virtual channel (M) detect status                  */
            __IM uint32_t FRD : 1;     /*!< [9..9] errFRameData of virtual channel (M) detect status                  */
            uint32_t          : 6;
            __IM uint32_t OVF : 1;     /*!< [16..16] generic short packet with virtual channel (M) discard
                                        *   by fifo OVerFlow status                                                   */
            uint32_t          : 7;
            __IM uint32_t FSR : 1;     /*!< [24..24] Frame Start packet with virtual channel (M) Reception
                                        *   status                                                                    */
            __IM uint32_t FER : 1;     /*!< [25..25] Frame End packet with virtual channel (M) Reception
                                        *   status                                                                    */
            __IM uint32_t LSR : 1;     /*!< [26..26] Line Start packet with virtual channel (M) Reception
                                        *   status                                                                    */
            __IM uint32_t LER : 1;     /*!< [27..27] Line End packet with virtual channel (M) Reception
                                        *   status                                                                    */
            __IM uint32_t ETR : 1;     /*!< [28..28] EoTp packet with virtual channel (M) Reception status            */
            uint32_t          : 3;
        } VCST15_b;
    };

    union
    {
        __OM uint32_t VCSC15;          /*!< (@ 0x000001F4) Virtual Channel (M) Status Clear Register                  */

        struct
        {
            __OM uint32_t MLFC : 1;    /*!< [0..0] MaLFormed packet with virutal channel (M) detect status
                                        *   Clear                                                                     */
            __OM uint32_t ECDC : 1;    /*!< [1..1] ECc 2-bit (Double) error packet with virutal channel
                                        *   (M) Detect status Clear                                                   */
            __OM uint32_t CRCC : 1;    /*!< [2..2] CRC error packet with virtual channel (M) detect status
                                        *   Clear                                                                     */
            __OM uint32_t IDEC : 1;    /*!< [3..3] ErrID packet with virtual channel (M) detect status Clear          */
            __OM uint32_t WCEC : 1;    /*!< [4..4] Word Count Error packet with virtual channel (M) detect
                                        *   status Clear                                                              */
            __OM uint32_t ECCC : 1;    /*!< [5..5] ECc 1-bit error (Corrected) packet with virtual channel
                                        *   (M) detect status Clear                                                   */
            __OM uint32_t ECNC : 1;    /*!< [6..6] ECc No-error packet with virtual channel (M) detect status
                                        *   Clear                                                                     */
            uint32_t            : 1;
            __OM uint32_t FRSC  : 1;   /*!< [8..8] errFRameSync of virtual channel (M) detect status Clear            */
            __OM uint32_t FRDC  : 1;   /*!< [9..9] errFRameData of virtual channel (M) detect status Clear            */
            uint32_t            : 4;
            __OM uint32_t AMLFC : 1;   /*!< [14..14] MaLFormed packet with any virutal channels detect status
                                        *   Clear                                                                     */
            __OM uint32_t AECDC : 1;   /*!< [15..15] ECc 2-bit (Double) error packet with any virutal channels
                                        *   Detect status Clear                                                       */
            __OM uint32_t OVFC : 1;    /*!< [16..16] generic short packet with virtual channel (M) discard
                                        *   by fifo OVerFlow status Clear                                             */
            uint32_t           : 7;
            __OM uint32_t FSRC : 1;    /*!< [24..24] Frame Start packet with virtual channel (M) Reception
                                        *   status Clear                                                              */
            __OM uint32_t FERC : 1;    /*!< [25..25] Frame End packet with virtual channel (M) Reception
                                        *   status Clear                                                              */
            __OM uint32_t LSRC : 1;    /*!< [26..26] Line Start packet with virtual channel (M) Reception
                                        *   status Clear                                                              */
            __OM uint32_t LERC : 1;    /*!< [27..27] Line End packet with virtual channel (M) Reception
                                        *   status Clear                                                              */
            __OM uint32_t ETRC : 1;    /*!< [28..28] EoTp packet with virtual channel (M) Reception status
                                        *   Clear                                                                     */
            uint32_t : 3;
        } VCSC15_b;
    };

    union
    {
        __IOM uint32_t VCIE15;         /*!< (@ 0x000001F8) Virtual Channel (M) Interrupt Enable Register              */

        struct
        {
            __IOM uint32_t MLFE : 1;   /*!< [0..0] MaLFormed packet with virutal channel (M) detect interrupt
                                        *   Enable                                                                    */
            __IOM uint32_t ECDE : 1;   /*!< [1..1] ECc 2-bit (Double) error packet with virutal channel
                                        *   (M) Detect interrupt Enable                                               */
            __IOM uint32_t CRCE : 1;   /*!< [2..2] CRC error packet with virtual channel (M) detect interrupt
                                        *   Enable                                                                    */
            __IOM uint32_t IDEE : 1;   /*!< [3..3] ErrID packet with virtual channel (M) detect interrupt
                                        *   Enable                                                                    */
            __IOM uint32_t WCEE : 1;   /*!< [4..4] Word Count Error packet with virtual channel (M) detect
                                        *   interrupt Enable                                                          */
            __IOM uint32_t ECCE : 1;   /*!< [5..5] ECc 1-bit error (Corrected) packet with virtual channel
                                        *   (M) detect interrupt Enable                                               */
            __IOM uint32_t ECNE : 1;   /*!< [6..6] ECc No-error packet with virtual channel (M) detect interrupt
                                        *   Enable                                                                    */
            uint32_t            : 1;
            __IOM uint32_t FRSE : 1;   /*!< [8..8] errFRameSync of virtual channel (M) detect interrupt
                                        *   Enable                                                                    */
            __IOM uint32_t FRDE : 1;   /*!< [9..9] errFRameData of virtual channel (M) detect interrupt
                                        *   Enable                                                                    */
            uint32_t            : 6;
            __IOM uint32_t OVFE : 1;   /*!< [16..16] generic short packet with virtual channel (M) discard
                                        *   by fifo OVerFlow interrupt Enable                                         */
            uint32_t            : 7;
            __IOM uint32_t FSRE : 1;   /*!< [24..24] Frame Start packet with virtual channel (M) Reception
                                        *   interrupt Enable                                                          */
            __IOM uint32_t FERE : 1;   /*!< [25..25] Frame End packet with virtual channel (M) Reception
                                        *   interrupt Enable                                                          */
            __IOM uint32_t LSRE : 1;   /*!< [26..26] Line Start packet with virtual channel (M) Reception
                                        *   interrupt Enable                                                          */
            __IOM uint32_t LERE : 1;   /*!< [27..27] Line End packet with virtual channel (M) Reception
                                        *   interrupt Enable                                                          */
            __IOM uint32_t ETRE : 1;   /*!< [28..28] EoTp packet with virtual channel (M) Reception interrupt
                                        *   Enable                                                                    */
            uint32_t : 3;
        } VCIE15_b;
    };
    __IM uint32_t RESERVED25;

    union
    {
        __IM uint32_t PMST;            /*!< (@ 0x00000200) Power Management Status Register                           */

        struct
        {
            __IM uint32_t DSX  : 1;    /*!< [0..0] eXit from Stop state detect on all valid Data lanes status         */
            __IM uint32_t DSN  : 1;    /*!< [1..1] eNtry to Stop state detect on all valid Data lanes status          */
            __IM uint32_t CSX  : 1;    /*!< [2..2] eXit from Stop state detect on Clock lane status                   */
            __IM uint32_t CSN  : 1;    /*!< [3..3] eNtry to Stop state detect on Clock lane status                    */
            __IM uint32_t DUX  : 1;    /*!< [4..4] eXit from Ulps detect on all valid Data lanes status               */
            __IM uint32_t DUN  : 1;    /*!< [5..5] eNtry to Ulps detect on all valid Data lanes status                */
            __IM uint32_t CUX  : 1;    /*!< [6..6] eXit frum Ulps detect on Clock lane status                         */
            __IM uint32_t CUN  : 1;    /*!< [7..7] eNtry to Ulps detect on Clock lane status                          */
            uint32_t           : 6;
            __IM uint32_t CLSS : 1;    /*!< [14..14] Stop State of Clock Lane status                                  */
            __IM uint32_t CLUL : 1;    /*!< [15..15] rxULpsclknot (inverted) of Clock Lane status                     */
            __IM uint32_t DLSS : 2;    /*!< [17..16] Stop State of Data Lanes status                                  */
            uint32_t           : 6;
            __IM uint32_t DLUL : 2;    /*!< [25..24] rxULpsesc of Data Lanes status                                   */
            uint32_t           : 6;
        } PMST_b;
    };

    union
    {
        __OM uint32_t PMSC;            /*!< (@ 0x00000204) Power Management Status Clear Register                     */

        struct
        {
            __OM uint32_t DSXC : 1;    /*!< [0..0] eXit from Stop state detect on all valid Data lanes status
                                        *   Clear                                                                     */
            __OM uint32_t DSNC : 1;    /*!< [1..1] eNtry to Stop state detect on all valid Data lanes status
                                        *   Clear                                                                     */
            __OM uint32_t CSXC : 1;    /*!< [2..2] eXit from Stop state detect on Clock lane status Clear             */
            __OM uint32_t CSNC : 1;    /*!< [3..3] eNtry to Stop state detect on Clock lane status Clear              */
            __OM uint32_t DUXC : 1;    /*!< [4..4] eXit from Ulps detect on all valid Data lanes status
                                        *   Clear                                                                     */
            __OM uint32_t DUNC : 1;    /*!< [5..5] eNtry to Ulps detect on all valid Data lanes status Clear          */
            __OM uint32_t CUXC : 1;    /*!< [6..6] eXit frum Ulps detect on Clock lane status Clear                   */
            __OM uint32_t CUNC : 1;    /*!< [7..7] eNtry to Ulps detect on Clock lane status Clear                    */
            uint32_t           : 24;
        } PMSC_b;
    };

    union
    {
        __IOM uint32_t PMIE;           /*!< (@ 0x00000208) Power Management Interrupt Enable Register                 */

        struct
        {
            __IOM uint32_t DSXE : 1;   /*!< [0..0] eXit from Stop state detect on all valid Data lanes interrupt
                                        *   Enable                                                                    */
            __IOM uint32_t DSNE : 1;   /*!< [1..1] eNtry to Stop state detect on all valid Data lanes interrupt
                                        *   Enable                                                                    */
            __IOM uint32_t CSXE : 1;   /*!< [2..2] eXit from Stop state detect on Clock lane interrupt Enable         */
            __IOM uint32_t CSNE : 1;   /*!< [3..3] eNtry to Stop state detect on Clock lane interrupt Enable          */
            __IOM uint32_t DUXE : 1;   /*!< [4..4] eXit from Ulps detect on all valid Data lanes interrupt
                                        *   Enable                                                                    */
            __IOM uint32_t DUNE : 1;   /*!< [5..5] eNtry to Ulps detect on all valid Data lanes interrupt
                                        *   Enable                                                                    */
            __IOM uint32_t CUXE : 1;   /*!< [6..6] eXit from Ulps detect on Clock lane interrupt Enable               */
            __IOM uint32_t CUNE : 1;   /*!< [7..7] eNtry to Ulps detect on Clock lane interrupt Enable                */
            uint32_t            : 24;
        } PMIE_b;
    };
    __IM uint32_t RESERVED26[29];

    union
    {
        __IOM uint32_t GSCT;           /*!< (@ 0x00000280) Generic Short Packet Control Register                      */

        struct
        {
            __IOM uint32_t SHTH : 7;   /*!< [6..0] Stored generic short packet THreshold                              */
            uint32_t            : 9;
            __IOM uint32_t GFIF : 1;   /*!< [16..16] Generic short packet store in FIFo                               */
            uint32_t            : 15;
        } GSCT_b;
    };

    union
    {
        __IM uint32_t GSST;            /*!< (@ 0x00000284) Generic Short Packet Status Register                       */

        struct
        {
            __IM uint32_t GNE : 1;     /*!< [0..0] Generic short packet fifo Not Empty                                */
            __IM uint32_t GTH : 1;     /*!< [1..1] more than THreshold Generic short packets existed in
                                        *   fifo                                                                      */
            uint32_t            : 2;
            __IM uint32_t GOV   : 1;   /*!< [4..4] Generic short packet fifo OVerflow status                          */
            uint32_t            : 3;
            __IM uint32_t PNUM  : 8;   /*!< [15..8] NUMber of stored generic short Packets in fifo                    */
            __IM uint32_t GCD   : 1;   /*!< [16..16] Generic short packet fifo Clear status                           */
            __IM uint32_t STRDS : 1;   /*!< [17..17] generic short packet SToRe DiSable                               */
            uint32_t            : 14;
        } GSST_b;
    };

    union
    {
        __OM uint32_t GSSC;            /*!< (@ 0x00000288) Generic Short Packet Status Clear Register                 */

        struct
        {
            uint32_t           : 4;
            __OM uint32_t GOVC : 1;    /*!< [4..4] Generic short packet fifo OVerflow status Clear                    */
            uint32_t           : 27;
        } GSSC_b;
    };

    union
    {
        __IOM uint32_t GSIE;           /*!< (@ 0x0000028C) Generic Short Packet Interrupt Enable Register             */

        struct
        {
            __IOM uint32_t GNEE : 1;   /*!< [0..0] Generic short packet fifo Not Empty interrupt Enable               */
            __IOM uint32_t GTHE : 1;   /*!< [1..1] more than THreshold Generic short packets existed in
                                        *   fifo interrupt Enable                                                     */
            uint32_t            : 2;
            __IOM uint32_t GOVE : 1;   /*!< [4..4] Generic short packet fifo OVerflow interrupt Enable                */
            uint32_t            : 27;
        } GSIE_b;
    };

    union
    {
        __IM uint32_t GSHT;            /*!< (@ 0x00000290) Generic Short Packet Register                              */

        struct
        {
            __IM uint32_t SPDT : 16;   /*!< [15..0] Stored Packet DaTa                                                */
            __IM uint32_t DTYP : 6;    /*!< [21..16] Stored packet Data TYPe                                          */
            uint32_t           : 2;
            __IM uint32_t SPVC : 4;    /*!< [27..24] Stored Packet Virtual Channel                                    */
            uint32_t           : 4;
        } GSHT_b;
    };

    union
    {
        __IOM uint32_t GSIU;           /*!< (@ 0x00000294) Generic Short Packet Information Update Register           */

        struct
        {
            __OM uint32_t FINC : 1;    /*!< [0..0] generic short packet Fifo update (INCrement internal
                                        *   pointer)                                                                  */
            uint32_t             : 7;
            __IOM uint32_t GFCLR : 1;  /*!< [8..8] Generic short packet Fifo CLeaR                                    */
            uint32_t             : 7;
            __OM uint32_t GFEN   : 1;  /*!< [16..16] Generic short packet Fifo ENable                                 */
            uint32_t             : 15;
        } GSIU_b;
    };
} R_MIPI_CSI_Type;                     /*!< Size = 664 (0x298)                                                        */
#endif

/**
  * @brief MIPI CSI 0 (R_MIPI_CSI0)
  */

typedef struct {                                /*!< (@ 0x40347000) R_MIPI_CSI0_DEBUG Structure                                */

  union {
    __OM  uint32_t DGMD;                        /*!< (@ 0x00000300) Debug Mode Enable Register                                 */

    struct {
      __OM  uint32_t KEY        : 32;           /*!< [31..0] debug KEY code                                                    */
    } DGMD_b;
  } ;

  union {
    __IOM uint32_t DGRCT;                       /*!< (@ 0x00000304) Debug Reset Control Register                               */

    struct {
      __IOM uint32_t SRST       : 1;            /*!< [0..0] Software ReSeT                                                     */
      __IM  uint32_t            : 31;
    } DGRCT_b;
  } ;
  __IM  uint32_t  RESERVED28[2];

  union {
    __IM  uint32_t DGST0;                       /*!< (@ 0x00000310) Debug Status Register 0                                    */

    struct {
      __IM  uint32_t LNE0       : 1;            /*!< [0..0] Line Number Error of virtual channel 0 detect status               */
      __IM  uint32_t LNE1       : 1;            /*!< [1..1] Line Number Error of virtual channel 1 detect status               */
      __IM  uint32_t LNE2       : 1;            /*!< [2..2] Line Number Error of virtual channel 2 detect status               */
      __IM  uint32_t LNE3       : 1;            /*!< [3..3] Line Number Error of virtual channel 3 detect status               */
      __IM  uint32_t LNE4       : 1;            /*!< [4..4] Line Number Error of virtual channel 4 detect status               */
      __IM  uint32_t LNE5       : 1;            /*!< [5..5] Line Number Error of virtual channel 5 detect status               */
      __IM  uint32_t LNE6       : 1;            /*!< [6..6] Line Number Error of virtual channel 6 detect status               */
      __IM  uint32_t LNE7       : 1;            /*!< [7..7] Line Number Error of virtual channel 7 detect status               */
      __IM  uint32_t LNE8       : 1;            /*!< [8..8] Line Number Error of virtual channel 8 detect status               */
      __IM  uint32_t LNE9       : 1;            /*!< [9..9] Line Number Error of virtual channel 9 detect status               */
      __IM  uint32_t LNE10      : 1;            /*!< [10..10] Line Number Error of virtual channel 10 detect status            */
      __IM  uint32_t LNE11      : 1;            /*!< [11..11] Line Number Error of virtual channel 11 detect status            */
      __IM  uint32_t LNE12      : 1;            /*!< [12..12] Line Number Error of virtual channel 12 detect status            */
      __IM  uint32_t LNE13      : 1;            /*!< [13..13] Line Number Error of virtual channel 13 detect status            */
      __IM  uint32_t LNE14      : 1;            /*!< [14..14] Line Number Error of virtual channel 14 detect status            */
      __IM  uint32_t LNE15      : 1;            /*!< [15..15] Line Number Error of virtual channel 15 detect status            */
      __IM  uint32_t LSE0       : 1;            /*!< [16..16] Line Start Error of virtual channel 0 detect status              */
      __IM  uint32_t LSE1       : 1;            /*!< [17..17] Line Start Error of virtual channel 1 detect status              */
      __IM  uint32_t LSE2       : 1;            /*!< [18..18] Line Start Error of virtual channel 2 detect status              */
      __IM  uint32_t LSE3       : 1;            /*!< [19..19] Line Start Error of virtual channel 3 detect status              */
      __IM  uint32_t LSE4       : 1;            /*!< [20..20] Line Start Error of virtual channel 4 detect status              */
      __IM  uint32_t LSE5       : 1;            /*!< [21..21] Line Start Error of virtual channel 5 detect status              */
      __IM  uint32_t LSE6       : 1;            /*!< [22..22] Line Start Error of virtual channel 6 detect status              */
      __IM  uint32_t LSE7       : 1;            /*!< [23..23] Line Start Error of virtual channel 7 detect status              */
      __IM  uint32_t LSE8       : 1;            /*!< [24..24] Line Start Error of virtual channel 8 detect status              */
      __IM  uint32_t LSE9       : 1;            /*!< [25..25] Line Start Error of virtual channel 9 detect status              */
      __IM  uint32_t LSE10      : 1;            /*!< [26..26] Line Start Error of virtual channel 10 detect status             */
      __IM  uint32_t LSE11      : 1;            /*!< [27..27] Line Start Error of virtual channel 11 detect status             */
      __IM  uint32_t LSE12      : 1;            /*!< [28..28] Line Start Error of virtual channel 12 detect status             */
      __IM  uint32_t LSE13      : 1;            /*!< [29..29] Line Start Error of virtual channel 13 detect status             */
      __IM  uint32_t LSE14      : 1;            /*!< [30..30] Line Start Error of virtual channel 14 detect status             */
      __IM  uint32_t LSE15      : 1;            /*!< [31..31] Line Start Error of virtual channel 15 detect status             */
    } DGST0_b;
  } ;

  union {
    __IM  uint32_t DGST1;                       /*!< (@ 0x00000314) Debug Status Register 1                                    */

    struct {
      __IM  uint32_t FNE0       : 1;            /*!< [0..0] Frame Number Error of virtual channel 0 detect status              */
      __IM  uint32_t FNE1       : 1;            /*!< [1..1] Frame Number Error of virtual channel 1 detect status              */
      __IM  uint32_t FNE2       : 1;            /*!< [2..2] Frame Number Error of virtual channel 2 detect status              */
      __IM  uint32_t FNE3       : 1;            /*!< [3..3] Frame Number Error of virtual channel 3 detect status              */
      __IM  uint32_t FNE4       : 1;            /*!< [4..4] Frame Number Error of virtual channel 4 detect status              */
      __IM  uint32_t FNE5       : 1;            /*!< [5..5] Frame Number Error of virtual channel 5 detect status              */
      __IM  uint32_t FNE6       : 1;            /*!< [6..6] Frame Number Error of virtual channel 6 detect status              */
      __IM  uint32_t FNE7       : 1;            /*!< [7..7] Frame Number Error of virtual channel 7 detect status              */
      __IM  uint32_t FNE8       : 1;            /*!< [8..8] Frame Number Error of virtual channel 8 detect status              */
      __IM  uint32_t FNE9       : 1;            /*!< [9..9] Frame Number Error of virtual channel 9 detect status              */
      __IM  uint32_t FNE10      : 1;            /*!< [10..10] Frame Number Error of virtual channel 10 detect status           */
      __IM  uint32_t FNE11      : 1;            /*!< [11..11] Frame Number Error of virtual channel 11 detect status           */
      __IM  uint32_t FNE12      : 1;            /*!< [12..12] Frame Number Error of virtual channel 12 detect status           */
      __IM  uint32_t FNE13      : 1;            /*!< [13..13] Frame Number Error of virtual channel 13 detect status           */
      __IM  uint32_t FNE14      : 1;            /*!< [14..14] Frame Number Error of virtual channel 14 detect status           */
      __IM  uint32_t FNE15      : 1;            /*!< [15..15] Frame Number Error of virtual channel 15 detect status           */
      __IM  uint32_t NPE0       : 1;            /*!< [16..16] No Packet Error of virtual channel 0 detect status               */
      __IM  uint32_t NPE1       : 1;            /*!< [17..17] No Packet Error of virtual channel 1 detect status               */
      __IM  uint32_t NPE2       : 1;            /*!< [18..18] No Packet Error of virtual channel 2 detect status               */
      __IM  uint32_t NPE3       : 1;            /*!< [19..19] No Packet Error of virtual channel 3 detect status               */
      __IM  uint32_t NPE4       : 1;            /*!< [20..20] No Packet Error of virtual channel 4 detect status               */
      __IM  uint32_t NPE5       : 1;            /*!< [21..21] No Packet Error of virtual channel 5 detect status               */
      __IM  uint32_t NPE6       : 1;            /*!< [22..22] No Packet Error of virtual channel 6 detect status               */
      __IM  uint32_t NPE7       : 1;            /*!< [23..23] No Packet Error of virtual channel 7 detect status               */
      __IM  uint32_t NPE8       : 1;            /*!< [24..24] No Packet Error of virtual channel 8 detect status               */
      __IM  uint32_t NPE9       : 1;            /*!< [25..25] No Packet Error of virtual channel 9 detect status               */
      __IM  uint32_t NPE10      : 1;            /*!< [26..26] No Packet Error of virtual channel 10 detect status              */
      __IM  uint32_t NPE11      : 1;            /*!< [27..27] No Packet Error of virtual channel 11 detect status              */
      __IM  uint32_t NPE12      : 1;            /*!< [28..28] No Packet Error of virtual channel 12 detect status              */
      __IM  uint32_t NPE13      : 1;            /*!< [29..29] No Packet Error of virtual channel 13 detect status              */
      __IM  uint32_t NPE14      : 1;            /*!< [30..30] No Packet Error of virtual channel 14 detect status              */
      __IM  uint32_t NPE15      : 1;            /*!< [31..31] No Packet Error of virtual channel 15 detect status              */
    } DGST1_b;
  } ;

  union {
    __IM  uint32_t DGST2;                       /*!< (@ 0x00000318) Debug Status Register 2                                    */

    struct {
      __IM  uint32_t EFOV0      : 1;            /*!< [0..0] Elastic buFfer OVerflow on physical data lane 0 detect
                                                     status                                                                    */
      __IM  uint32_t EFOV1      : 1;            /*!< [1..1] Elastic buFfer OVerflow on physical data lane 1 detect
                                                     status                                                                    */
      __IM  uint32_t EFOV2      : 1;            /*!< [2..2] Elastic buFfer OVerflow on physical data lane 2 detect
                                                     status                                                                    */
      __IM  uint32_t EFOV3      : 1;            /*!< [3..3] Elastic buFfer OVerflow on physical data lane 3 detect
                                                     status                                                                    */
      __IM  uint32_t EFOV4      : 1;            /*!< [4..4] Elastic buFfer OVerflow on physical data lane 4 detect
                                                     status                                                                    */
      __IM  uint32_t EFOV5      : 1;            /*!< [5..5] Elastic buFfer OVerflow on physical data lane 5 detect
                                                     status                                                                    */
      __IM  uint32_t EFOV6      : 1;            /*!< [6..6] Elastic buFfer OVerflow on physical data lane 6 detect
                                                     status                                                                    */
      __IM  uint32_t EFOV7      : 1;            /*!< [7..7] Elastic buFfer OVerflow on physical data lane 7 detect
                                                     status                                                                    */
      __IM  uint32_t            : 16;
      __IM  uint32_t NOEND      : 1;            /*!< [24..24] packet NO END detect status                                      */
      __IM  uint32_t            : 7;
    } DGST2_b;
  } ;

  union {
    __IM  uint32_t DGST3;                       /*!< (@ 0x0000031C) Debug Status Register 3                                    */

    struct {
      __IM  uint32_t DSKWE0     : 1;            /*!< [0..0] DeSKeW Error on physical data lane 0 detect status                 */
      __IM  uint32_t DSKWE1     : 1;            /*!< [1..1] DeSKeW Error on physical data lane 1 detect status                 */
      __IM  uint32_t DSKWE2     : 1;            /*!< [2..2] DeSKeW Error on physical data lane 2 detect status                 */
      __IM  uint32_t DSKWE3     : 1;            /*!< [3..3] DeSKeW Error on physical data lane 3 detect status                 */
      __IM  uint32_t DSKWE4     : 1;            /*!< [4..4] DeSKeW Error on physical data lane 4 detect status                 */
      __IM  uint32_t DSKWE5     : 1;            /*!< [5..5] DeSKeW Error on physical data lane 5 detect status                 */
      __IM  uint32_t DSKWE6     : 1;            /*!< [6..6] DeSKeW Error on physical data lane 6 detect status                 */
      __IM  uint32_t DSKWE7     : 1;            /*!< [7..7] DeSKeW Error on physical data lane 7 detect status                 */
      __IM  uint32_t            : 1;
      __IM  uint32_t STRTE1     : 1;            /*!< [9..9] packet STaRt Timing Error on logical lane 1 detect status          */
      __IM  uint32_t STRTE2     : 1;            /*!< [10..10] packet STaRt Timing Error on logical lane 2 detect
                                                     status                                                                    */
      __IM  uint32_t STRTE3     : 1;            /*!< [11..11] packet STaRt Timing Error on logical lane 3 detect
                                                     status                                                                    */
      __IM  uint32_t STRTE4     : 1;            /*!< [12..12] packet STaRt Timing Error on logical lane 4 detect
                                                     status                                                                    */
      __IM  uint32_t STRTE5     : 1;            /*!< [13..13] packet STaRt Timing Error on logical lane 5 detect
                                                     status                                                                    */
      __IM  uint32_t STRTE6     : 1;            /*!< [14..14] packet STaRt Timing Error on logical lane 6 detect
                                                     status                                                                    */
      __IM  uint32_t STRTE7     : 1;            /*!< [15..15] packet STaRt Timing Error on logical lane 7 detect
                                                     status                                                                    */
      __IM  uint32_t            : 16;
    } DGST3_b;
  } ;

  union {
    __OM  uint32_t DGSC0;                       /*!< (@ 0x00000320) Debug Status Clear Register 0                              */

    struct {
      __OM  uint32_t LNE0C      : 1;            /*!< [0..0] Line Number Error of virtual channel 0 detect status
                                                     Clear                                                                     */
      __OM  uint32_t LNE1C      : 1;            /*!< [1..1] Line Number Error of virtual channel 1 detect status
                                                     Clear                                                                     */
      __OM  uint32_t LNE2C      : 1;            /*!< [2..2] Line Number Error of virtual channel 2 detect status
                                                     Clear                                                                     */
      __OM  uint32_t LNE3C      : 1;            /*!< [3..3] Line Number Error of virtual channel 3 detect status
                                                     Clear                                                                     */
      __OM  uint32_t LNE4C      : 1;            /*!< [4..4] Line Number Error of virtual channel 4 detect status
                                                     Clear                                                                     */
      __OM  uint32_t LNE5C      : 1;            /*!< [5..5] Line Number Error of virtual channel 5 detect status
                                                     Clear                                                                     */
      __OM  uint32_t LNE6C      : 1;            /*!< [6..6] Line Number Error of virtual channel 6 detect status
                                                     Clear                                                                     */
      __OM  uint32_t LNE7C      : 1;            /*!< [7..7] Line Number Error of virtual channel 7 detect status
                                                     Clear                                                                     */
      __OM  uint32_t LNE8C      : 1;            /*!< [8..8] Line Number Error of virtual channel 8 detect status
                                                     Clear                                                                     */
      __OM  uint32_t LNE9C      : 1;            /*!< [9..9] Line Number Error of virtual channel 9 detect status
                                                     Clear                                                                     */
      __OM  uint32_t LNE10C     : 1;            /*!< [10..10] Line Number Error of virtual channel 10 detect status
                                                     Clear                                                                     */
      __OM  uint32_t LNE11C     : 1;            /*!< [11..11] Line Number Error of virtual channel 11 detect status
                                                     Clear                                                                     */
      __OM  uint32_t LNE12C     : 1;            /*!< [12..12] Line Number Error of virtual channel 12 detect status
                                                     Clear                                                                     */
      __OM  uint32_t LNE13C     : 1;            /*!< [13..13] Line Number Error of virtual channel 13 detect status
                                                     Clear                                                                     */
      __OM  uint32_t LNE14C     : 1;            /*!< [14..14] Line Number Error of virtual channel 14 detect status
                                                     Clear                                                                     */
      __OM  uint32_t LNE15C     : 1;            /*!< [15..15] Line Number Error of virtual channel 15 detect status
                                                     Clear                                                                     */
      __OM  uint32_t LSE0C      : 1;            /*!< [16..16] Line Start Error of virtual channel 0 detect status
                                                     Clear                                                                     */
      __OM  uint32_t LSE1C      : 1;            /*!< [17..17] Line Start Error of virtual channel 1 detect status
                                                     Clear                                                                     */
      __OM  uint32_t LSE2C      : 1;            /*!< [18..18] Line Start Error of virtual channel 2 detect status
                                                     Clear                                                                     */
      __OM  uint32_t LSE3C      : 1;            /*!< [19..19] Line Start Error of virtual channel 3 detect status
                                                     Clear                                                                     */
      __OM  uint32_t LSE4C      : 1;            /*!< [20..20] Line Start Error of virtual channel 4 detect status
                                                     Clear                                                                     */
      __OM  uint32_t LSE5C      : 1;            /*!< [21..21] Line Start Error of virtual channel 5 detect status
                                                     Clear                                                                     */
      __OM  uint32_t LSE6C      : 1;            /*!< [22..22] Line Start Error of virtual channel 6 detect status
                                                     Clear                                                                     */
      __OM  uint32_t LSE7C      : 1;            /*!< [23..23] Line Start Error of virtual channel 7 detect status
                                                     Clear                                                                     */
      __OM  uint32_t LSE8C      : 1;            /*!< [24..24] Line Start Error of virtual channel 8 detect status
                                                     Clear                                                                     */
      __OM  uint32_t LSE9C      : 1;            /*!< [25..25] Line Start Error of virtual channel 9 detect status
                                                     Clear                                                                     */
      __OM  uint32_t LSE10C     : 1;            /*!< [26..26] Line Start Error of virtual channel 10 detect status
                                                     Clear                                                                     */
      __OM  uint32_t LSE11C     : 1;            /*!< [27..27] Line Start Error of virtual channel 11 detect status
                                                     Clear                                                                     */
      __OM  uint32_t LSE12C     : 1;            /*!< [28..28] Line Start Error of virtual channel 12 detect status
                                                     Clear                                                                     */
      __OM  uint32_t LSE13C     : 1;            /*!< [29..29] Line Start Error of virtual channel 13 detect status
                                                     Clear                                                                     */
      __OM  uint32_t LSE14C     : 1;            /*!< [30..30] Line Start Error of virtual channel 14 detect status
                                                     Clear                                                                     */
      __OM  uint32_t LSE15C     : 1;            /*!< [31..31] Line Start Error of virtual channel 15 detect status
                                                     Clear                                                                     */
    } DGSC0_b;
  } ;

  union {
    __OM  uint32_t DGSC1;                       /*!< (@ 0x00000324) Debug Status Clear Register 1                              */

    struct {
      __OM  uint32_t FNE0C      : 1;            /*!< [0..0] Frame Number Error of virtual channel 0 detect status
                                                     Clear                                                                     */
      __OM  uint32_t FNE1C      : 1;            /*!< [1..1] Frame Number Error of virtual channel 1 detect status
                                                     Clear                                                                     */
      __OM  uint32_t FNE2C      : 1;            /*!< [2..2] Frame Number Error of virtual channel 2 detect status
                                                     Clear                                                                     */
      __OM  uint32_t FNE3C      : 1;            /*!< [3..3] Frame Number Error of virtual channel 3 detect status
                                                     Clear                                                                     */
      __OM  uint32_t FNE4C      : 1;            /*!< [4..4] Frame Number Error of virtual channel 4 detect status
                                                     Clear                                                                     */
      __OM  uint32_t FNE5C      : 1;            /*!< [5..5] Frame Number Error of virtual channel 5 detect status
                                                     Clear                                                                     */
      __OM  uint32_t FNE6C      : 1;            /*!< [6..6] Frame Number Error of virtual channel 6 detect status
                                                     Clear                                                                     */
      __OM  uint32_t FNE7C      : 1;            /*!< [7..7] Frame Number Error of virtual channel 7 detect status
                                                     Clear                                                                     */
      __OM  uint32_t FNE8C      : 1;            /*!< [8..8] Frame Number Error of virtual channel 8 detect status
                                                     Clear                                                                     */
      __OM  uint32_t FNE9C      : 1;            /*!< [9..9] Frame Number Error of virtual channel 9 detect status
                                                     Clear                                                                     */
      __OM  uint32_t FNE10C     : 1;            /*!< [10..10] Frame Number Error of virtual channel 10 detect status
                                                     Clear                                                                     */
      __OM  uint32_t FNE11C     : 1;            /*!< [11..11] Frame Number Error of virtual channel 11 detect status
                                                     Clear                                                                     */
      __OM  uint32_t FNE12C     : 1;            /*!< [12..12] Frame Number Error of virtual channel 12 detect status
                                                     Clear                                                                     */
      __OM  uint32_t FNE13C     : 1;            /*!< [13..13] Frame Number Error of virtual channel 13 detect status
                                                     Clear                                                                     */
      __OM  uint32_t FNE14C     : 1;            /*!< [14..14] Frame Number Error of virtual channel 14 detect status
                                                     Clear                                                                     */
      __OM  uint32_t FNE15C     : 1;            /*!< [15..15] Frame Number Error of virtual channel 15 detect status
                                                     Clear                                                                     */
      __OM  uint32_t NPE0C      : 1;            /*!< [16..16] No Packet Error of virtual channel 0 detect status
                                                     Clear                                                                     */
      __OM  uint32_t NPE1C      : 1;            /*!< [17..17] No Packet Error of virtual channel 1 detect status
                                                     Clear                                                                     */
      __OM  uint32_t NPE2C      : 1;            /*!< [18..18] No Packet Error of virtual channel 2 detect status
                                                     Clear                                                                     */
      __OM  uint32_t NPE3C      : 1;            /*!< [19..19] No Packet Error of virtual channel 3 detect status
                                                     Clear                                                                     */
      __OM  uint32_t NPE4C      : 1;            /*!< [20..20] No Packet Error of virtual channel 4 detect status
                                                     Clear                                                                     */
      __OM  uint32_t NPE5C      : 1;            /*!< [21..21] No Packet Error of virtual channel 5 detect status
                                                     Clear                                                                     */
      __OM  uint32_t NPE6C      : 1;            /*!< [22..22] No Packet Error of virtual channel 6 detect status
                                                     Clear                                                                     */
      __OM  uint32_t NPE7C      : 1;            /*!< [23..23] No Packet Error of virtual channel 7 detect status
                                                     Clear                                                                     */
      __OM  uint32_t NPE8C      : 1;            /*!< [24..24] No Packet Error of virtual channel 8 detect status
                                                     Clear                                                                     */
      __OM  uint32_t NPE9C      : 1;            /*!< [25..25] No Packet Error of virtual channel 9 detect status
                                                     Clear                                                                     */
      __OM  uint32_t NPE10C     : 1;            /*!< [26..26] No Packet Error of virtual channel 10 detect status
                                                     Clear                                                                     */
      __OM  uint32_t NPE11C     : 1;            /*!< [27..27] No Packet Error of virtual channel 11 detect status
                                                     Clear                                                                     */
      __OM  uint32_t NPE12C     : 1;            /*!< [28..28] No Packet Error of virtual channel 12 detect status
                                                     Clear                                                                     */
      __OM  uint32_t NPE13C     : 1;            /*!< [29..29] No Packet Error of virtual channel 13 detect status
                                                     Clear                                                                     */
      __OM  uint32_t NPE14C     : 1;            /*!< [30..30] No Packet Error of virtual channel 14 detect status
                                                     Clear                                                                     */
      __OM  uint32_t NPE15C     : 1;            /*!< [31..31] No Packet Error of virtual channel 15 detect status
                                                     Clear                                                                     */
    } DGSC1_b;
  } ;

  union {
    __OM  uint32_t DGSC2;                       /*!< (@ 0x00000328) Debug Status Clear Register 2                              */

    struct {
      __OM  uint32_t EFOV0C     : 1;            /*!< [0..0] Elastic buFfer OVerflow on physical data lane 0 detect
                                                     status Clear                                                              */
      __OM  uint32_t EFOV1C     : 1;            /*!< [1..1] Elastic buFfer OVerflow on physical data lane 1 detect
                                                     status Clear                                                              */
      __OM  uint32_t EFOV2C     : 1;            /*!< [2..2] Elastic buFfer OVerflow on physical data lane 2 detect
                                                     status Clear                                                              */
      __OM  uint32_t EFOV3C     : 1;            /*!< [3..3] Elastic buFfer OVerflow on physical data lane 3 detect
                                                     status Clear                                                              */
      __OM  uint32_t EFOV4C     : 1;            /*!< [4..4] Elastic buFfer OVerflow on physical data lane 4 detect
                                                     status Clear                                                              */
      __OM  uint32_t EFOV5C     : 1;            /*!< [5..5] Elastic buFfer OVerflow on physical data lane 5 detect
                                                     status Clear                                                              */
      __OM  uint32_t EFOV6C     : 1;            /*!< [6..6] Elastic buFfer OVerflow on physical data lane 6 detect
                                                     status Clear                                                              */
      __OM  uint32_t EFOV7C     : 1;            /*!< [7..7] Elastic buFfer OVerflow on physical data lane 7 detect
                                                     status Clear                                                              */
      __IM  uint32_t            : 16;
      __OM  uint32_t NOENDC     : 1;            /*!< [24..24] packet NO END detect status Clear                                */
      __IM  uint32_t            : 7;
    } DGSC2_b;
  } ;

  union {
    __OM  uint32_t DGSC3;                       /*!< (@ 0x0000032C) Debug Status Clear Register 3                              */

    struct {
      __OM  uint32_t DSKWE0C    : 1;            /*!< [0..0] DeSKeW Error on physical data lane 0 detect status Clear           */
      __OM  uint32_t DSKWE1C    : 1;            /*!< [1..1] DeSKeW Error on physical data lane 1 detect status Clear           */
      __OM  uint32_t DSKWE2C    : 1;            /*!< [2..2] DeSKeW Error on physical data lane 2 detect status Clear           */
      __OM  uint32_t DSKWE3C    : 1;            /*!< [3..3] DeSKeW Error on physical data lane 3 detect status Clear           */
      __OM  uint32_t DSKWE4C    : 1;            /*!< [4..4] DeSKeW Error on physical data lane 4 detect status Clear           */
      __OM  uint32_t DSKWE5C    : 1;            /*!< [5..5] DeSKeW Error on physical data lane 5 detect status Clear           */
      __OM  uint32_t DSKWE6C    : 1;            /*!< [6..6] DeSKeW Error on physical data lane 6 detect status Clear           */
      __OM  uint32_t DSKWE7C    : 1;            /*!< [7..7] DeSKeW Error on physical data lane 7 detect status Clear           */
      __IM  uint32_t            : 1;
      __OM  uint32_t STRTE1C    : 1;            /*!< [9..9] packet STaRt Timing Error on logical data lane 1 detect
                                                     status                                                                    */
      __OM  uint32_t STRTE2C    : 1;            /*!< [10..10] packet STaRt Timing Error on logical data lane 2 detect
                                                     status                                                                    */
      __OM  uint32_t STRTE3C    : 1;            /*!< [11..11] packet STaRt Timing Error on logical data lane 3 detect
                                                     status                                                                    */
      __OM  uint32_t STRTE4C    : 1;            /*!< [12..12] packet STaRt Timing Error on logical data lane 4 detect
                                                     status                                                                    */
      __OM  uint32_t STRTE5C    : 1;            /*!< [13..13] packet STaRt Timing Error on logical data lane 5 detect
                                                     status                                                                    */
      __OM  uint32_t STRTE6C    : 1;            /*!< [14..14] packet STaRt Timing Error on logical data lane 6 detect
                                                     status                                                                    */
      __OM  uint32_t STRTE7C    : 1;            /*!< [15..15] packet STaRt Timing Error on logical data lane 7 detect
                                                     status                                                                    */
      __IM  uint32_t            : 16;
    } DGSC3_b;
  } ;

  union {
    __IOM uint32_t DGIE0;                       /*!< (@ 0x00000330) Debug Interrupt Enable Register 0                          */

    struct {
      __IOM uint32_t LNE0E      : 1;            /*!< [0..0] Line Number Error of virtual channel 0 detect interrupt
                                                     Enable                                                                    */
      __IOM uint32_t LNE1E      : 1;            /*!< [1..1] Line Number Error of virtual channel 1 detect interrupt
                                                     Enable                                                                    */
      __IOM uint32_t LNE2E      : 1;            /*!< [2..2] Line Number Error of virtual channel 2 detect interrupt
                                                     Enable                                                                    */
      __IOM uint32_t LNE3E      : 1;            /*!< [3..3] Line Number Error of virtual channel 3 detect interrupt
                                                     Enable                                                                    */
      __IOM uint32_t LNE4E      : 1;            /*!< [4..4] Line Number Error of virtual channel 4 detect interrupt
                                                     Enable                                                                    */
      __IOM uint32_t LNE5E      : 1;            /*!< [5..5] Line Number Error of virtual channel 5 detect interrupt
                                                     Enable                                                                    */
      __IOM uint32_t LNE6E      : 1;            /*!< [6..6] Line Number Error of virtual channel 6 detect interrupt
                                                     Enable                                                                    */
      __IOM uint32_t LNE7E      : 1;            /*!< [7..7] Line Number Error of virtual channel 7 detect interrupt
                                                     Enable                                                                    */
      __IOM uint32_t LNE8E      : 1;            /*!< [8..8] Line Number Error of virtual channel 8 detect interrupt
                                                     Enable                                                                    */
      __IOM uint32_t LNE9E      : 1;            /*!< [9..9] Line Number Error of virtual channel 9 detect interrupt
                                                     Enable                                                                    */
      __IOM uint32_t LNE10E     : 1;            /*!< [10..10] Line Number Error of virtual channel 10 detect interrupt
                                                     Enable                                                                    */
      __IOM uint32_t LNE11E     : 1;            /*!< [11..11] Line Number Error of virtual channel 11 detect interrupt
                                                     Enable                                                                    */
      __IOM uint32_t LNE12E     : 1;            /*!< [12..12] Line Number Error of virtual channel 12 detect interrupt
                                                     Enable                                                                    */
      __IOM uint32_t LNE13E     : 1;            /*!< [13..13] Line Number Error of virtual channel 13 detect interrupt
                                                     Enable                                                                    */
      __IOM uint32_t LNE14E     : 1;            /*!< [14..14] Line Number Error of virtual channel 14 detect interrupt
                                                     Enable                                                                    */
      __IOM uint32_t LNE15E     : 1;            /*!< [15..15] Line Number Error of virtual channel 15 detect interrupt
                                                     Enable                                                                    */
      __IOM uint32_t LSE0E      : 1;            /*!< [16..16] Line Start Error of virtual channel 0 detect interrupt
                                                     Enable                                                                    */
      __IOM uint32_t LSE1E      : 1;            /*!< [17..17] Line Start Error of virtual channel 1 detect interrupt
                                                     Enable                                                                    */
      __IOM uint32_t LSE2E      : 1;            /*!< [18..18] Line Start Error of virtual channel 2 detect interrupt
                                                     Enable                                                                    */
      __IOM uint32_t LSE3E      : 1;            /*!< [19..19] Line Start Error of virtual channel 3 detect interrupt
                                                     Enable                                                                    */
      __IOM uint32_t LSE4E      : 1;            /*!< [20..20] Line Start Error of virtual channel 4 detect interrupt
                                                     Enable                                                                    */
      __IOM uint32_t LSE5E      : 1;            /*!< [21..21] Line Start Error of virtual channel 5 detect interrupt
                                                     Enable                                                                    */
      __IOM uint32_t LSE6E      : 1;            /*!< [22..22] Line Start Error of virtual channel 6 detect interrupt
                                                     Enable                                                                    */
      __IOM uint32_t LSE7E      : 1;            /*!< [23..23] Line Start Error of virtual channel 7 detect interrupt
                                                     Enable                                                                    */
      __IOM uint32_t LSE8E      : 1;            /*!< [24..24] Line Start Error of virtual channel 8 detect interrupt
                                                     Enable                                                                    */
      __IOM uint32_t LSE9E      : 1;            /*!< [25..25] Line Start Error of virtual channel 9 detect interrupt
                                                     Enable                                                                    */
      __IOM uint32_t LSE10E     : 1;            /*!< [26..26] Line Start Error of virtual channel 10 detect interrupt
                                                     Enable                                                                    */
      __IOM uint32_t LSE11E     : 1;            /*!< [27..27] Line Start Error of virtual channel 11 detect interrupt
                                                     Enable                                                                    */
      __IOM uint32_t LSE12E     : 1;            /*!< [28..28] Line Start Error of virtual channel 12 detect interrupt
                                                     Enable                                                                    */
      __IOM uint32_t LSE13E     : 1;            /*!< [29..29] Line Start Error of virtual channel 13 detect interrupt
                                                     Enable                                                                    */
      __IOM uint32_t LSE14E     : 1;            /*!< [30..30] Line Start Error of virtual channel 14 detect interrupt
                                                     Enable                                                                    */
      __IOM uint32_t LSE15E     : 1;            /*!< [31..31] Line Start Error of virtual channel 15 detect interrupt
                                                     Enable                                                                    */
    } DGIE0_b;
  } ;

  union {
    __IOM uint32_t DGIE1;                       /*!< (@ 0x00000334) Debug Interrupt Enable Register 1                          */

    struct {
      __IOM uint32_t FNE0E      : 1;            /*!< [0..0] Frame Number Error of virtual channel 0 detect interrupt
                                                     Enable                                                                    */
      __IOM uint32_t FNE1E      : 1;            /*!< [1..1] Frame Number Error of virtual channel 1 detect interrupt
                                                     Enable                                                                    */
      __IOM uint32_t FNE2E      : 1;            /*!< [2..2] Frame Number Error of virtual channel 2 detect interrupt
                                                     Enable                                                                    */
      __IOM uint32_t FNE3E      : 1;            /*!< [3..3] Frame Number Error of virtual channel 3 detect interrupt
                                                     Enable                                                                    */
      __IOM uint32_t FNE4E      : 1;            /*!< [4..4] Frame Number Error of virtual channel 4 detect interrupt
                                                     Enable                                                                    */
      __IOM uint32_t FNE5E      : 1;            /*!< [5..5] Frame Number Error of virtual channel 5 detect interrupt
                                                     Enable                                                                    */
      __IOM uint32_t FNE6E      : 1;            /*!< [6..6] Frame Number Error of virtual channel 6 detect interrupt
                                                     Enable                                                                    */
      __IOM uint32_t FNE7E      : 1;            /*!< [7..7] Frame Number Error of virtual channel 7 detect interrupt
                                                     Enable                                                                    */
      __IOM uint32_t FNE8E      : 1;            /*!< [8..8] Frame Number Error of virtual channel 8 detect interrupt
                                                     Enable                                                                    */
      __IOM uint32_t FNE9E      : 1;            /*!< [9..9] Frame Number Error of virtual channel 9 detect interrupt
                                                     Enable                                                                    */
      __IOM uint32_t FNE10E     : 1;            /*!< [10..10] Frame Number Error of virtual channel 10 detect interrupt
                                                     Enable                                                                    */
      __IOM uint32_t FNE11E     : 1;            /*!< [11..11] Frame Number Error of virtual channel 11 detect interrupt
                                                     Enable                                                                    */
      __IOM uint32_t FNE12E     : 1;            /*!< [12..12] Frame Number Error of virtual channel 12 detect interrupt
                                                     Enable                                                                    */
      __IOM uint32_t FNE13E     : 1;            /*!< [13..13] Frame Number Error of virtual channel 13 detect interrupt
                                                     Enable                                                                    */
      __IOM uint32_t FNE14E     : 1;            /*!< [14..14] Frame Number Error of virtual channel 14 detect interrupt
                                                     Enable                                                                    */
      __IOM uint32_t FNE15E     : 1;            /*!< [15..15] Frame Number Error of virtual channel 15 detect interrupt
                                                     Enable                                                                    */
      __IOM uint32_t NPE0E      : 1;            /*!< [16..16] No Packet Error of virtual channel 0 detect interrupt
                                                     Enable                                                                    */
      __IOM uint32_t NPE1E      : 1;            /*!< [17..17] No Packet Error of virtual channel 1 detect interrupt
                                                     Enable                                                                    */
      __IOM uint32_t NPE2E      : 1;            /*!< [18..18] No Packet Error of virtual channel 2 detect interrupt
                                                     Enable                                                                    */
      __IOM uint32_t NPE3E      : 1;            /*!< [19..19] No Packet Error of virtual channel 3 detect interrupt
                                                     Enable                                                                    */
      __IOM uint32_t NPE4E      : 1;            /*!< [20..20] No Packet Error of virtual channel 4 detect interrupt
                                                     Enable                                                                    */
      __IOM uint32_t NPE5E      : 1;            /*!< [21..21] No Packet Error of virtual channel 5 detect interrupt
                                                     Enable                                                                    */
      __IOM uint32_t NPE6E      : 1;            /*!< [22..22] No Packet Error of virtual channel 6 detect interrupt
                                                     Enable                                                                    */
      __IOM uint32_t NPE7E      : 1;            /*!< [23..23] No Packet Error of virtual channel 7 detect interrupt
                                                     Enable                                                                    */
      __IOM uint32_t NPE8E      : 1;            /*!< [24..24] No Packet Error of virtual channel 8 detect interrupt
                                                     Enable                                                                    */
      __IOM uint32_t NPE9E      : 1;            /*!< [25..25] No Packet Error of virtual channel 9 detect interrupt
                                                     Enable                                                                    */
      __IOM uint32_t NPE10E     : 1;            /*!< [26..26] No Packet Error of virtual channel 10 detect interrupt
                                                     Enable                                                                    */
      __IOM uint32_t NPE11E     : 1;            /*!< [27..27] No Packet Error of virtual channel 11 detect interrupt
                                                     Enable                                                                    */
      __IOM uint32_t NPE12E     : 1;            /*!< [28..28] No Packet Error of virtual channel 12 detect interrupt
                                                     Enable                                                                    */
      __IOM uint32_t NPE13E     : 1;            /*!< [29..29] No Packet Error of virtual channel 13 detect interrupt
                                                     Enable                                                                    */
      __IOM uint32_t NPE14E     : 1;            /*!< [30..30] No Packet Error of virtual channel 14 detect interrupt
                                                     Enable                                                                    */
      __IOM uint32_t NPE15E     : 1;            /*!< [31..31] No Packet Error of virtual channel 15 detect interrupt
                                                     Enable                                                                    */
    } DGIE1_b;
  } ;

  union {
    __IOM uint32_t DGIE2;                       /*!< (@ 0x00000338) Debug Interrupt Enable Register 2                          */

    struct {
      __IOM uint32_t EFOV0E     : 1;            /*!< [0..0] Elastic buFfer OVerflow on physical data lane 0 detect
                                                     interrupt Enable                                                          */
      __IOM uint32_t EFOV1E     : 1;            /*!< [1..1] Elastic buFfer OVerflow on physical data lane 1 detect
                                                     interrupt Enable                                                          */
      __IOM uint32_t EFOV2E     : 1;            /*!< [2..2] Elastic buFfer OVerflow on physical data lane 2 detect
                                                     interrupt Enable                                                          */
      __IOM uint32_t EFOV3E     : 1;            /*!< [3..3] Elastic buFfer OVerflow on physical data lane 3 detect
                                                     interrupt Enable                                                          */
      __IOM uint32_t EFOV4E     : 1;            /*!< [4..4] Elastic buFfer OVerflow on physical data lane 4 detect
                                                     interrupt Enable                                                          */
      __IOM uint32_t EFOV5E     : 1;            /*!< [5..5] Elastic buFfer OVerflow on physical data lane 5 detect
                                                     interrupt Enable                                                          */
      __IOM uint32_t EFOV6E     : 1;            /*!< [6..6] Elastic buFfer OVerflow on physical data lane 6 detect
                                                     interrupt Enable                                                          */
      __IOM uint32_t EFOV7E     : 1;            /*!< [7..7] Elastic buFfer OVerflow on physical data lane 7 detect
                                                     interrupt Enable                                                          */
      __IM  uint32_t            : 16;
      __IOM uint32_t NOENDE     : 1;            /*!< [24..24] packet NO END detect interrupt Enable                            */
      __IM  uint32_t            : 7;
    } DGIE2_b;
  } ;

  union {
    __IOM uint32_t DGIE3;                       /*!< (@ 0x0000033C) Debug Interrupt Enable Register 3                          */

    struct {
      __IOM uint32_t DSKWE0E    : 1;            /*!< [0..0] DeSKeW Error on physical data lane 0 detect interrupt
                                                     Enable                                                                    */
      __IOM uint32_t DSKWE1E    : 1;            /*!< [1..1] DeSKeW Error on physical data lane 1 detect interrupt
                                                     Enable                                                                    */
      __IOM uint32_t DSKWE2E    : 1;            /*!< [2..2] DeSKeW Error on physical data lane 2 detect interrupt
                                                     Enable                                                                    */
      __IOM uint32_t DSKWE3E    : 1;            /*!< [3..3] DeSKeW Error on physical data lane 3 detect interrupt
                                                     Enable                                                                    */
      __IOM uint32_t DSKWE4E    : 1;            /*!< [4..4] DeSKeW Error on physical data lane 4 detect interrupt
                                                     Enable                                                                    */
      __IOM uint32_t DSKWE5E    : 1;            /*!< [5..5] DeSKeW Error on physical data lane 5 detect interrupt
                                                     Enable                                                                    */
      __IOM uint32_t DSKWE6E    : 1;            /*!< [6..6] DeSKeW Error on physical data lane 6 detect interrupt
                                                     Enable                                                                    */
      __IOM uint32_t DSKWE7E    : 1;            /*!< [7..7] DeSKeW Error on physical data lane 7 detect interrupt
                                                     Enable                                                                    */
      __IM  uint32_t            : 1;
      __IOM uint32_t STRTE1E    : 1;            /*!< [9..9] packet STaRt Timing Error on logical lane 1 detect interrupt
                                                     Enable                                                                    */
      __IOM uint32_t STRTE2E    : 1;            /*!< [10..10] packet STaRt Timing Error on logical lane 2 detect
                                                     interrupt Enable                                                          */
      __IOM uint32_t STRTE3E    : 1;            /*!< [11..11] packet STaRt Timing Error on logical lane 3 detect
                                                     interrupt Enable                                                          */
      __IOM uint32_t STRTE4E    : 1;            /*!< [12..12] packet STaRt Timing Error on logical lane 4 detect
                                                     interrupt Enable                                                          */
      __IOM uint32_t STRTE5E    : 1;            /*!< [13..13] packet STaRt Timing Error on logical lane 5 detect
                                                     interrupt Enable                                                          */
      __IOM uint32_t STRTE6E    : 1;            /*!< [14..14] packet STaRt Timing Error on logical lane 6 detect
                                                     interrupt Enable                                                          */
      __IOM uint32_t STRTE7E    : 1;            /*!< [15..15] packet STaRt Timing Error on logical lane 7 detect
                                                     interrupt Enable                                                          */
      __IM  uint32_t            : 16;
    } DGIE3_b;
  } ;

  union {
    __IOM uint32_t DGEC;                        /*!< (@ 0x00000340) Debug Error Count Register                                 */

    struct {
      __IOM uint32_t ECDCNT     : 16;           /*!< [15..0] ECc 2-bit (Double) error CouNT                                    */
      __IOM uint32_t CRCCNT     : 16;           /*!< [31..16] CRC error CouNT                                                  */
    } DGEC_b;
  } ;
  __IM  uint32_t  RESERVED29[23];

  union {
    __IM  uint32_t DGVP0;                       /*!< (@ 0x000003A0) Debug VPI Monitor Register 0                               */

    struct {
      __IM  uint32_t LVLD0      : 1;            /*!< [0..0] csi2_vc_LVaLiD[0] status                                           */
      __IM  uint32_t LVLD1      : 1;            /*!< [1..1] csi2_vc_LVaLiD[1] status                                           */
      __IM  uint32_t LVLD2      : 1;            /*!< [2..2] csi2_vc_LVaLiD[2] status                                           */
      __IM  uint32_t LVLD3      : 1;            /*!< [3..3] csi2_vc_LVaLiD[3] status                                           */
      __IM  uint32_t LVLD4      : 1;            /*!< [4..4] csi2_vc_LVaLiD[4] status                                           */
      __IM  uint32_t LVLD5      : 1;            /*!< [5..5] csi2_vc_LVaLiD[5] status                                           */
      __IM  uint32_t LVLD6      : 1;            /*!< [6..6] csi2_vc_LVaLiD[6] status                                           */
      __IM  uint32_t LVLD7      : 1;            /*!< [7..7] csi2_vc_LVaLiD[7] status                                           */
      __IM  uint32_t LVLD8      : 1;            /*!< [8..8] csi2_vc_LVaLiD[8] status                                           */
      __IM  uint32_t LVLD9      : 1;            /*!< [9..9] csi2_vc_LVaLiD[9] status                                           */
      __IM  uint32_t LVLD10     : 1;            /*!< [10..10] csi2_vc_LVaLiD[10] status                                        */
      __IM  uint32_t LVLD11     : 1;            /*!< [11..11] csi2_vc_LVaLiD[11] status                                        */
      __IM  uint32_t LVLD12     : 1;            /*!< [12..12] csi2_vc_LVaLiD[12] status                                        */
      __IM  uint32_t LVLD13     : 1;            /*!< [13..13] csi2_vc_LVaLiD[13] status                                        */
      __IM  uint32_t LVLD14     : 1;            /*!< [14..14] csi2_vc_LVaLiD[14] status                                        */
      __IM  uint32_t LVLD15     : 1;            /*!< [15..15] csi2_vc_LVaLiD[15] status                                        */
      __IM  uint32_t DVLD       : 1;            /*!< [16..16] csi2_Data_VaLiD status                                           */
      __IM  uint32_t            : 15;
    } DGVP0_b;
  } ;

  union {
    __IM  uint32_t DGVP1;                       /*!< (@ 0x000003A4) Debug VPI Monitor Register 1                               */

    struct {
      __IM  uint32_t EFD0       : 1;            /*!< [0..0] csi2_vc_ErrFrameData[0] status                                     */
      __IM  uint32_t EFD1       : 1;            /*!< [1..1] csi2_vc_ErrFrameData[1] status                                     */
      __IM  uint32_t EFD2       : 1;            /*!< [2..2] csi2_vc_ErrFrameData[2] status                                     */
      __IM  uint32_t EFD3       : 1;            /*!< [3..3] csi2_vc_ErrFrameData[3] status                                     */
      __IM  uint32_t EFD4       : 1;            /*!< [4..4] csi2_vc_ErrFrameData[4] status                                     */
      __IM  uint32_t EFD5       : 1;            /*!< [5..5] csi2_vc_ErrFrameData[5] status                                     */
      __IM  uint32_t EFD6       : 1;            /*!< [6..6] csi2_vc_ErrFrameData[6] status                                     */
      __IM  uint32_t EFD7       : 1;            /*!< [7..7] csi2_vc_ErrFrameData[7] status                                     */
      __IM  uint32_t EFD8       : 1;            /*!< [8..8] csi2_vc_ErrFrameData[8] status                                     */
      __IM  uint32_t EFD9       : 1;            /*!< [9..9] csi2_vc_ErrFrameData[9] status                                     */
      __IM  uint32_t EFD10      : 1;            /*!< [10..10] csi2_vc_ErrFrameData[10] status                                  */
      __IM  uint32_t EFD11      : 1;            /*!< [11..11] csi2_vc_ErrFrameData[11] status                                  */
      __IM  uint32_t EFD12      : 1;            /*!< [12..12] csi2_vc_ErrFrameData[12] status                                  */
      __IM  uint32_t EFD13      : 1;            /*!< [13..13] csi2_vc_ErrFrameData[13] status                                  */
      __IM  uint32_t EFD14      : 1;            /*!< [14..14] csi2_vc_ErrFrameData[14] status                                  */
      __IM  uint32_t EFD15      : 1;            /*!< [15..15] csi2_vc_ErrFrameData[15] status                                  */
      __IM  uint32_t EID0       : 1;            /*!< [16..16] csi2_vc_ErrID[0] status                                          */
      __IM  uint32_t EID1       : 1;            /*!< [17..17] csi2_vc_ErrID[1] status                                          */
      __IM  uint32_t EID2       : 1;            /*!< [18..18] csi2_vc_ErrID[2] status                                          */
      __IM  uint32_t EID3       : 1;            /*!< [19..19] csi2_vc_ErrID[3] status                                          */
      __IM  uint32_t EID4       : 1;            /*!< [20..20] csi2_vc_ErrID[4] status                                          */
      __IM  uint32_t EID5       : 1;            /*!< [21..21] csi2_vc_ErrID[5] status                                          */
      __IM  uint32_t EID6       : 1;            /*!< [22..22] csi2_vc_ErrID[6] status                                          */
      __IM  uint32_t EID7       : 1;            /*!< [23..23] csi2_vc_ErrID[7] status                                          */
      __IM  uint32_t EID8       : 1;            /*!< [24..24] csi2_vc_ErrID[8] status                                          */
      __IM  uint32_t EID9       : 1;            /*!< [25..25] csi2_vc_ErrID[9] status                                          */
      __IM  uint32_t EID10      : 1;            /*!< [26..26] csi2_vc_ErrID[10] status                                         */
      __IM  uint32_t EID11      : 1;            /*!< [27..27] csi2_vc_ErrID[11] status                                         */
      __IM  uint32_t EID12      : 1;            /*!< [28..28] csi2_vc_ErrID[12] status                                         */
      __IM  uint32_t EID13      : 1;            /*!< [29..29] csi2_vc_ErrID[13] status                                         */
      __IM  uint32_t EID14      : 1;            /*!< [30..30] csi2_vc_ErrID[14] status                                         */
      __IM  uint32_t EID15      : 1;            /*!< [31..31] csi2_vc_ErrID[15] status                                         */
    } DGVP1_b;
  } ;
  __IM  uint32_t  RESERVED30[2];

  union {
    __IM  uint32_t DGCL;                        /*!< (@ 0x000003B0) Debug PPI CL Monitor                                       */

    struct {
      __IM  uint32_t RXCLKACT   : 1;            /*!< [0..0] ppi_cl_RXCLKACTivehs status                                        */
      __IM  uint32_t            : 15;
      __IM  uint32_t STPSTCL    : 1;            /*!< [16..16] ppi_CL_SToPSTate                                                 */
      __IM  uint32_t RXULPSCN   : 1;            /*!< [17..17] ppi_cl_RXULPSClkNot status                                       */
      __IM  uint32_t            : 14;
    } DGCL_b;
  } ;
  __IM  uint32_t  RESERVED31[3];

  union {
    __IM  uint32_t DGDL0;                       /*!< (@ 0x000003C0) Debug PPI DL0 Monitor                                      */

    struct {
      __IM  uint32_t RXVLD      : 4;            /*!< [3..0] ppi_dl(L)_RXVaLiDhs[3:0] status                                    */
      __IM  uint32_t RXACT      : 1;            /*!< [4..4] ppi_dl(L)_RXACTivehs status                                        */
      __IM  uint32_t RXSYNC     : 1;            /*!< [5..5] ppi_dl(L)_RXSYNChs status                                          */
      __IM  uint32_t            : 1;
      __IM  uint32_t RXSKEW     : 1;            /*!< [7..7] ppi_dl(L)_RXSKEWcalhs status                                       */
      __IM  uint32_t ERSOT      : 1;            /*!< [8..8] ppi_dl(L)_ERrSOThs status                                          */
      __IM  uint32_t ERSOTSY    : 1;            /*!< [9..9] ppi_dl(L)_ERrSOTSYnchs status                                      */
      __IM  uint32_t ERESC      : 1;            /*!< [10..10] ppi_dl(L)_ERrESC status                                          */
      __IM  uint32_t ERCTL      : 1;            /*!< [11..11] ppi_dl(L)_ERrConTroL status                                      */
      __IM  uint32_t            : 4;
      __IM  uint32_t STPSTDL    : 1;            /*!< [16..16] ppi_DL(L)_SToPSTate status                                       */
      __IM  uint32_t RXULPS     : 1;            /*!< [17..17] ppi_dl(L)_RXULPSesc status                                       */
      __IM  uint32_t            : 2;
      __IM  uint32_t RXTRG      : 4;            /*!< [23..20] ppi_dl(L)_RXTRiGgeresc[3:0] status                               */
      __IM  uint32_t            : 8;
    } DGDL0_b;
  } ;

  union {
    __IM  uint32_t DGDL1;                       /*!< (@ 0x000003C4) Debug PPI DL1 Monitor                                      */

    struct {
      __IM  uint32_t RXVLD      : 4;            /*!< [3..0] ppi_dl(L)_RXVaLiDhs[3:0] status                                    */
      __IM  uint32_t RXACT      : 1;            /*!< [4..4] ppi_dl(L)_RXACTivehs status                                        */
      __IM  uint32_t RXSYNC     : 1;            /*!< [5..5] ppi_dl(L)_RXSYNChs status                                          */
      __IM  uint32_t            : 1;
      __IM  uint32_t RXSKEW     : 1;            /*!< [7..7] ppi_dl(L)_RXSKEWcalhs status                                       */
      __IM  uint32_t ERSOT      : 1;            /*!< [8..8] ppi_dl(L)_ERrSOThs status                                          */
      __IM  uint32_t ERSOTSY    : 1;            /*!< [9..9] ppi_dl(L)_ERrSOTSYnchs status                                      */
      __IM  uint32_t ERESC      : 1;            /*!< [10..10] ppi_dl(L)_ERrESC status                                          */
      __IM  uint32_t ERCTL      : 1;            /*!< [11..11] ppi_dl(L)_ERrConTroL status                                      */
      __IM  uint32_t            : 4;
      __IM  uint32_t STPSTDL    : 1;            /*!< [16..16] ppi_DL(L)_SToPSTate status                                       */
      __IM  uint32_t RXULPS     : 1;            /*!< [17..17] ppi_dl(L)_RXULPSesc status                                       */
      __IM  uint32_t            : 2;
      __IM  uint32_t RXTRG      : 4;            /*!< [23..20] ppi_dl(L)_RXTRiGgeresc[3:0] status                               */
      __IM  uint32_t            : 8;
    } DGDL1_b;
  } ;
} R_MIPI_CSI0_DEBUG_Type;                             /*!< Size = 968 (0x3c8)                                                        */

/* =========================================================================================================================== */
/* ================                                  Peripheral declaration                                   ================ */
/* =========================================================================================================================== */

#define R_VIN_BASE            (0x40347400UL)
#define R_MIPI_CSI_BASE       (0x40347000UL)
#define R_MIPI_CSI_DEBUG_BASE (0x40347300UL)

#define R_VIN                 ((R_VIN_Type *) R_VIN_BASE)
#define R_MIPI_CSI            ((R_MIPI_CSI_Type *) R_MIPI_CSI_BASE)
#define R_MIPI_CSI0_DEBUG     ((R_MIPI_CSI0_DEBUG_Type *) R_MIPI_CSI_DEBUG_BASE)

/* =========================================================================================================================== */
/* ================                                           R_VIN                                           ================ */
/* =========================================================================================================================== */

/* ==========================================================  MC  =========================================================== */
 #define R_VIN_MC_ME_Pos                       (0UL)          /*!< ME (Bit 0)                                            */
 #define R_VIN_MC_ME_Msk                       (0x1UL)        /*!< ME (Bitfield-Mask: 0x01)                              */
 #define R_VIN_MC_BPS_Pos                      (1UL)          /*!< BPS (Bit 1)                                           */
 #define R_VIN_MC_BPS_Msk                      (0x2UL)        /*!< BPS (Bitfield-Mask: 0x01)                             */
 #define R_VIN_MC_IM_Pos                       (3UL)          /*!< IM (Bit 3)                                            */
 #define R_VIN_MC_IM_Msk                       (0x18UL)       /*!< IM (Bitfield-Mask: 0x03)                              */
 #define R_VIN_MC_EN_Pos                       (6UL)          /*!< EN (Bit 6)                                            */
 #define R_VIN_MC_EN_Msk                       (0x40UL)       /*!< EN (Bitfield-Mask: 0x01)                              */
 #define R_VIN_MC_DC_Pos                       (14UL)         /*!< DC (Bit 14)                                           */
 #define R_VIN_MC_DC_Msk                       (0xc000UL)     /*!< DC (Bitfield-Mask: 0x03)                              */
 #define R_VIN_MC_INF_Pos                      (16UL)         /*!< INF (Bit 16)                                          */
 #define R_VIN_MC_INF_Msk                      (0x70000UL)    /*!< INF (Bitfield-Mask: 0x07)                             */
 #define R_VIN_MC_LUTE_Pos                     (20UL)         /*!< LUTE (Bit 20)                                         */
 #define R_VIN_MC_LUTE_Msk                     (0x100000UL)   /*!< LUTE (Bitfield-Mask: 0x01)                            */
 #define R_VIN_MC_ST_Pos                       (22UL)         /*!< ST (Bit 22)                                           */
 #define R_VIN_MC_ST_Msk                       (0x400000UL)   /*!< ST (Bitfield-Mask: 0x01)                              */
 #define R_VIN_MC_DC2_Pos                      (24UL)         /*!< DC2 (Bit 24)                                          */
 #define R_VIN_MC_DC2_Msk                      (0x1000000UL)  /*!< DC2 (Bitfield-Mask: 0x01)                             */
 #define R_VIN_MC_YUV444_Pos                   (25UL)         /*!< YUV444 (Bit 25)                                       */
 #define R_VIN_MC_YUV444_Msk                   (0x2000000UL)  /*!< YUV444 (Bitfield-Mask: 0x01)                          */
 #define R_VIN_MC_SCLE_Pos                     (26UL)         /*!< SCLE (Bit 26)                                         */
 #define R_VIN_MC_SCLE_Msk                     (0x4000000UL)  /*!< SCLE (Bitfield-Mask: 0x01)                            */
 #define R_VIN_MC_CLP_Pos                      (28UL)         /*!< CLP (Bit 28)                                          */
 #define R_VIN_MC_CLP_Msk                      (0x30000000UL) /*!< CLP (Bitfield-Mask: 0x03)                             */
/* ==========================================================  MS  =========================================================== */
 #define R_VIN_MS_CA_Pos                       (0UL)          /*!< CA (Bit 0)                                            */
 #define R_VIN_MS_CA_Msk                       (0x1UL)        /*!< CA (Bitfield-Mask: 0x01)                              */
 #define R_VIN_MS_AV_Pos                       (1UL)          /*!< AV (Bit 1)                                            */
 #define R_VIN_MS_AV_Msk                       (0x2UL)        /*!< AV (Bitfield-Mask: 0x01)                              */
 #define R_VIN_MS_FS_Pos                       (2UL)          /*!< FS (Bit 2)                                            */
 #define R_VIN_MS_FS_Msk                       (0x4UL)        /*!< FS (Bitfield-Mask: 0x01)                              */
 #define R_VIN_MS_FBS_Pos                      (3UL)          /*!< FBS (Bit 3)                                           */
 #define R_VIN_MS_FBS_Msk                      (0x18UL)       /*!< FBS (Bitfield-Mask: 0x03)                             */
 #define R_VIN_MS_MA_Pos                       (16UL)         /*!< MA (Bit 16)                                           */
 #define R_VIN_MS_MA_Msk                       (0x10000UL)    /*!< MA (Bitfield-Mask: 0x01)                              */
 #define R_VIN_MS_FMS_Pos                      (19UL)         /*!< FMS (Bit 19)                                          */
 #define R_VIN_MS_FMS_Msk                      (0x180000UL)   /*!< FMS (Bitfield-Mask: 0x03)                             */
/* ==========================================================  FC  =========================================================== */
 #define R_VIN_FC_CC_Pos                       (1UL)          /*!< CC (Bit 1)                                            */
 #define R_VIN_FC_CC_Msk                       (0x2UL)        /*!< CC (Bitfield-Mask: 0x01)                              */
/* =========================================================  SLPRC  ========================================================= */
 #define R_VIN_SLPRC_SLPRC_Pos                 (0UL)          /*!< SLPRC (Bit 0)                                         */
 #define R_VIN_SLPRC_SLPRC_Msk                 (0xfffUL)      /*!< SLPRC (Bitfield-Mask: 0xfff)                          */
/* =========================================================  ELPRC  ========================================================= */
 #define R_VIN_ELPRC_ELPRC_Pos                 (0UL)          /*!< ELPRC (Bit 0)                                         */
 #define R_VIN_ELPRC_ELPRC_Msk                 (0xfffUL)      /*!< ELPRC (Bitfield-Mask: 0xfff)                          */
/* =========================================================  SPPRC  ========================================================= */
 #define R_VIN_SPPRC_SPPRC_Pos                 (0UL)          /*!< SPPRC (Bit 0)                                         */
 #define R_VIN_SPPRC_SPPRC_Msk                 (0xfffUL)      /*!< SPPRC (Bitfield-Mask: 0xfff)                          */
/* =========================================================  EPPRC  ========================================================= */
 #define R_VIN_EPPRC_EPPRC_Pos                 (0UL)          /*!< EPPRC (Bit 0)                                         */
 #define R_VIN_EPPRC_EPPRC_Msk                 (0xfffUL)      /*!< EPPRC (Bitfield-Mask: 0xfff)                          */
/* =======================================================  CSI_IFMD  ======================================================== */
 #define R_VIN_CSI_IFMD_VC_SEL_Pos             (0UL)          /*!< VC_SEL (Bit 0)                                        */
 #define R_VIN_CSI_IFMD_VC_SEL_Msk             (0xfUL)        /*!< VC_SEL (Bitfield-Mask: 0x0f)                          */
 #define R_VIN_CSI_IFMD_DT_Pos                 (8UL)          /*!< DT (Bit 8)                                            */
 #define R_VIN_CSI_IFMD_DT_Msk                 (0x3f00UL)     /*!< DT (Bitfield-Mask: 0x3f)                              */
 #define R_VIN_CSI_IFMD_DES0_Pos               (25UL)         /*!< DES0 (Bit 25)                                         */
 #define R_VIN_CSI_IFMD_DES0_Msk               (0x2000000UL)  /*!< DES0 (Bitfield-Mask: 0x01)                            */
/* ========================================================  CSIFLD  ========================================================= */
 #define R_VIN_CSIFLD_FLD_EN_Pos               (0UL)          /*!< FLD_EN (Bit 0)                                        */
 #define R_VIN_CSIFLD_FLD_EN_Msk               (0x1UL)        /*!< FLD_EN (Bitfield-Mask: 0x01)                          */
 #define R_VIN_CSIFLD_FLD_SEL_Pos              (4UL)          /*!< FLD_SEL (Bit 4)                                       */
 #define R_VIN_CSIFLD_FLD_SEL_Msk              (0x30UL)       /*!< FLD_SEL (Bitfield-Mask: 0x03)                         */
 #define R_VIN_CSIFLD_FLD_NUM_Pos              (16UL)         /*!< FLD_NUM (Bit 16)                                      */
 #define R_VIN_CSIFLD_FLD_NUM_Msk              (0x10000UL)    /*!< FLD_NUM (Bitfield-Mask: 0x01)                         */
/* ==========================================================  IS  =========================================================== */
 #define R_VIN_IS_IS_Pos                       (0UL)          /*!< IS (Bit 0)                                            */
 #define R_VIN_IS_IS_Msk                       (0x1fffUL)     /*!< IS (Bitfield-Mask: 0x1fff)                            */
/* ==========================================================  MB1  ========================================================== */
 #define R_VIN_MB1_MB1_Pos                     (7UL)          /*!< MB1 (Bit 7)                                           */
 #define R_VIN_MB1_MB1_Msk                     (0xffffff80UL) /*!< MB1 (Bitfield-Mask: 0x1ffffff)                        */
/* ==========================================================  MB2  ========================================================== */
 #define R_VIN_MB2_MB2_Pos                     (7UL)          /*!< MB2 (Bit 7)                                           */
 #define R_VIN_MB2_MB2_Msk                     (0xffffff80UL) /*!< MB2 (Bitfield-Mask: 0x1ffffff)                        */
/* ==========================================================  MB3  ========================================================== */
 #define R_VIN_MB3_MB3_Pos                     (7UL)          /*!< MB3 (Bit 7)                                           */
 #define R_VIN_MB3_MB3_Msk                     (0xffffff80UL) /*!< MB3 (Bitfield-Mask: 0x1ffffff)                        */
/* ==========================================================  LC  =========================================================== */
 #define R_VIN_LC_LC_Pos                       (0UL)          /*!< LC (Bit 0)                                            */
 #define R_VIN_LC_LC_Msk                       (0xfffUL)      /*!< LC (Bitfield-Mask: 0xfff)                             */
/* ==========================================================  IE  =========================================================== */
 #define R_VIN_IE_FOE_Pos                      (0UL)          /*!< FOE (Bit 0)                                           */
 #define R_VIN_IE_FOE_Msk                      (0x1UL)        /*!< FOE (Bitfield-Mask: 0x01)                             */
 #define R_VIN_IE_EFE_Pos                      (1UL)          /*!< EFE (Bit 1)                                           */
 #define R_VIN_IE_EFE_Msk                      (0x2UL)        /*!< EFE (Bitfield-Mask: 0x01)                             */
 #define R_VIN_IE_SIE_Pos                      (2UL)          /*!< SIE (Bit 2)                                           */
 #define R_VIN_IE_SIE_Msk                      (0x4UL)        /*!< SIE (Bitfield-Mask: 0x01)                             */
 #define R_VIN_IE_FIE_Pos                      (4UL)          /*!< FIE (Bit 4)                                           */
 #define R_VIN_IE_FIE_Msk                      (0x10UL)       /*!< FIE (Bitfield-Mask: 0x01)                             */
 #define R_VIN_IE_FME_Pos                      (5UL)          /*!< FME (Bit 5)                                           */
 #define R_VIN_IE_FME_Msk                      (0x20UL)       /*!< FME (Bitfield-Mask: 0x01)                             */
 #define R_VIN_IE_PRCLIPHEE_Pos                (8UL)          /*!< PRCLIPHEE (Bit 8)                                     */
 #define R_VIN_IE_PRCLIPHEE_Msk                (0x100UL)      /*!< PRCLIPHEE (Bitfield-Mask: 0x01)                       */
 #define R_VIN_IE_PRCLIPVEE_Pos                (9UL)          /*!< PRCLIPVEE (Bit 9)                                     */
 #define R_VIN_IE_PRCLIPVEE_Msk                (0x200UL)      /*!< PRCLIPVEE (Bitfield-Mask: 0x01)                       */
 #define R_VIN_IE_ROE_Pos                      (14UL)         /*!< ROE (Bit 14)                                          */
 #define R_VIN_IE_ROE_Msk                      (0x4000UL)     /*!< ROE (Bitfield-Mask: 0x01)                             */
 #define R_VIN_IE_AREE_Pos                     (15UL)         /*!< AREE (Bit 15)                                         */
 #define R_VIN_IE_AREE_Msk                     (0x8000UL)     /*!< AREE (Bitfield-Mask: 0x01)                            */
 #define R_VIN_IE_VRE_Pos                      (16UL)         /*!< VRE (Bit 16)                                          */
 #define R_VIN_IE_VRE_Msk                      (0x10000UL)    /*!< VRE (Bitfield-Mask: 0x01)                             */
 #define R_VIN_IE_VFE_Pos                      (17UL)         /*!< VFE (Bit 17)                                          */
 #define R_VIN_IE_VFE_Msk                      (0x20000UL)    /*!< VFE (Bitfield-Mask: 0x01)                             */
 #define R_VIN_IE_FIE2_Pos                     (31UL)         /*!< FIE2 (Bit 31)                                         */
 #define R_VIN_IE_FIE2_Msk                     (0x80000000UL) /*!< FIE2 (Bitfield-Mask: 0x01)                            */
/* =========================================================  INTS  ========================================================== */
 #define R_VIN_INTS_FOS_Pos                    (0UL)          /*!< FOS (Bit 0)                                           */
 #define R_VIN_INTS_FOS_Msk                    (0x1UL)        /*!< FOS (Bitfield-Mask: 0x01)                             */
 #define R_VIN_INTS_EFS_Pos                    (1UL)          /*!< EFS (Bit 1)                                           */
 #define R_VIN_INTS_EFS_Msk                    (0x2UL)        /*!< EFS (Bitfield-Mask: 0x01)                             */
 #define R_VIN_INTS_SIS_Pos                    (2UL)          /*!< SIS (Bit 2)                                           */
 #define R_VIN_INTS_SIS_Msk                    (0x4UL)        /*!< SIS (Bitfield-Mask: 0x01)                             */
 #define R_VIN_INTS_FIS_Pos                    (4UL)          /*!< FIS (Bit 4)                                           */
 #define R_VIN_INTS_FIS_Msk                    (0x10UL)       /*!< FIS (Bitfield-Mask: 0x01)                             */
 #define R_VIN_INTS_FMS_Pos                    (5UL)          /*!< FMS (Bit 5)                                           */
 #define R_VIN_INTS_FMS_Msk                    (0x20UL)       /*!< FMS (Bitfield-Mask: 0x01)                             */
 #define R_VIN_INTS_PRCLIPHES_Pos              (8UL)          /*!< PRCLIPHES (Bit 8)                                     */
 #define R_VIN_INTS_PRCLIPHES_Msk              (0x100UL)      /*!< PRCLIPHES (Bitfield-Mask: 0x01)                       */
 #define R_VIN_INTS_PRCLIPVES_Pos              (9UL)          /*!< PRCLIPVES (Bit 9)                                     */
 #define R_VIN_INTS_PRCLIPVES_Msk              (0x200UL)      /*!< PRCLIPVES (Bitfield-Mask: 0x01)                       */
 #define R_VIN_INTS_ROS_Pos                    (14UL)         /*!< ROS (Bit 14)                                          */
 #define R_VIN_INTS_ROS_Msk                    (0x4000UL)     /*!< ROS (Bitfield-Mask: 0x01)                             */
 #define R_VIN_INTS_ARES_Pos                   (15UL)         /*!< ARES (Bit 15)                                         */
 #define R_VIN_INTS_ARES_Msk                   (0x8000UL)     /*!< ARES (Bitfield-Mask: 0x01)                            */
 #define R_VIN_INTS_VRS_Pos                    (16UL)         /*!< VRS (Bit 16)                                          */
 #define R_VIN_INTS_VRS_Msk                    (0x10000UL)    /*!< VRS (Bitfield-Mask: 0x01)                             */
 #define R_VIN_INTS_VFS_Pos                    (17UL)         /*!< VFS (Bit 17)                                          */
 #define R_VIN_INTS_VFS_Msk                    (0x20000UL)    /*!< VFS (Bitfield-Mask: 0x01)                             */
 #define R_VIN_INTS_FIS2_Pos                   (31UL)         /*!< FIS2 (Bit 31)                                         */
 #define R_VIN_INTS_FIS2_Msk                   (0x80000000UL) /*!< FIS2 (Bitfield-Mask: 0x01)                            */
/* ==========================================================  SI  =========================================================== */
 #define R_VIN_SI_SI_Pos                       (0UL)          /*!< SI (Bit 0)                                            */
 #define R_VIN_SI_SI_Msk                       (0xfffUL)      /*!< SI (Bitfield-Mask: 0xfff)                             */
/* ========================================================  MTCSTOP  ======================================================== */
 #define R_VIN_MTCSTOP_STOPREQ_Pos             (0UL)          /*!< STOPREQ (Bit 0)                                       */
 #define R_VIN_MTCSTOP_STOPREQ_Msk             (0x1UL)        /*!< STOPREQ (Bitfield-Mask: 0x01)                         */
 #define R_VIN_MTCSTOP_STOPACK_Pos             (1UL)          /*!< STOPACK (Bit 1)                                       */
 #define R_VIN_MTCSTOP_STOPACK_Msk             (0x2UL)        /*!< STOPACK (Bitfield-Mask: 0x01)                         */
 #define R_VIN_MTCSTOP_OUTSTAND_Pos            (16UL)         /*!< OUTSTAND (Bit 16)                                     */
 #define R_VIN_MTCSTOP_OUTSTAND_Msk            (0x3f0000UL)   /*!< OUTSTAND (Bitfield-Mask: 0x3f)                        */
/* ==========================================================  DMR  ========================================================== */
 #define R_VIN_DMR_DTMD_Pos                    (0UL)          /*!< DTMD (Bit 0)                                          */
 #define R_VIN_DMR_DTMD_Msk                    (0x3UL)        /*!< DTMD (Bitfield-Mask: 0x03)                            */
 #define R_VIN_DMR_ABIT_Pos                    (2UL)          /*!< ABIT (Bit 2)                                          */
 #define R_VIN_DMR_ABIT_Msk                    (0x4UL)        /*!< ABIT (Bitfield-Mask: 0x01)                            */
 #define R_VIN_DMR_BPSM_Pos                    (4UL)          /*!< BPSM (Bit 4)                                          */
 #define R_VIN_DMR_BPSM_Msk                    (0x10UL)       /*!< BPSM (Bitfield-Mask: 0x01)                            */
 #define R_VIN_DMR_EXRGB_Pos                   (8UL)          /*!< EXRGB (Bit 8)                                         */
 #define R_VIN_DMR_EXRGB_Msk                   (0x100UL)      /*!< EXRGB (Bitfield-Mask: 0x01)                           */
 #define R_VIN_DMR_YC_THR_Pos                  (11UL)         /*!< YC_THR (Bit 11)                                       */
 #define R_VIN_DMR_YC_THR_Msk                  (0x800UL)      /*!< YC_THR (Bitfield-Mask: 0x01)                          */
 #define R_VIN_DMR_YMODE_Pos                   (12UL)         /*!< YMODE (Bit 12)                                        */
 #define R_VIN_DMR_YMODE_Msk                   (0x7000UL)     /*!< YMODE (Bitfield-Mask: 0x07)                           */
 #define R_VIN_DMR_A8BIT_Pos                   (24UL)         /*!< A8BIT (Bit 24)                                        */
 #define R_VIN_DMR_A8BIT_Msk                   (0xff000000UL) /*!< A8BIT (Bitfield-Mask: 0xff)                           */
/* =========================================================  UVAOF  ========================================================= */
 #define R_VIN_UVAOF_UVAOF_Pos                 (7UL)          /*!< UVAOF (Bit 7)                                         */
 #define R_VIN_UVAOF_UVAOF_Msk                 (0xffffff80UL) /*!< UVAOF (Bitfield-Mask: 0x1ffffff)                      */
/* =========================================================  CSCE1  ========================================================= */
 #define R_VIN_CSCE1_YMUL2_Pos                 (0UL)          /*!< YMUL2 (Bit 0)                                         */
 #define R_VIN_CSCE1_YMUL2_Msk                 (0x3fffUL)     /*!< YMUL2 (Bitfield-Mask: 0x3fff)                         */
 #define R_VIN_CSCE1_ROUND_Pos                 (16UL)         /*!< ROUND (Bit 16)                                        */
 #define R_VIN_CSCE1_ROUND_Msk                 (0x10000UL)    /*!< ROUND (Bitfield-Mask: 0x01)                           */
/* =========================================================  CSCE2  ========================================================= */
 #define R_VIN_CSCE2_CSUB2_Pos                 (0UL)          /*!< CSUB2 (Bit 0)                                         */
 #define R_VIN_CSCE2_CSUB2_Msk                 (0xfffUL)      /*!< CSUB2 (Bitfield-Mask: 0xfff)                          */
 #define R_VIN_CSCE2_YSUB2_Pos                 (16UL)         /*!< YSUB2 (Bit 16)                                        */
 #define R_VIN_CSCE2_YSUB2_Msk                 (0xfff0000UL)  /*!< YSUB2 (Bitfield-Mask: 0xfff)                          */
/* =========================================================  CSCE3  ========================================================= */
 #define R_VIN_CSCE3_GCRMUL2_Pos               (0UL)          /*!< GCRMUL2 (Bit 0)                                       */
 #define R_VIN_CSCE3_GCRMUL2_Msk               (0x3fffUL)     /*!< GCRMUL2 (Bitfield-Mask: 0x3fff)                       */
 #define R_VIN_CSCE3_RCRMUL2_Pos               (16UL)         /*!< RCRMUL2 (Bit 16)                                      */
 #define R_VIN_CSCE3_RCRMUL2_Msk               (0x3fff0000UL) /*!< RCRMUL2 (Bitfield-Mask: 0x3fff)                       */
/* =========================================================  CSCE4  ========================================================= */
 #define R_VIN_CSCE4_BCBMUL2_Pos               (0UL)          /*!< BCBMUL2 (Bit 0)                                       */
 #define R_VIN_CSCE4_BCBMUL2_Msk               (0x3fffUL)     /*!< BCBMUL2 (Bitfield-Mask: 0x3fff)                       */
 #define R_VIN_CSCE4_GCBMUL2_Pos               (16UL)         /*!< GCBMUL2 (Bit 16)                                      */
 #define R_VIN_CSCE4_GCBMUL2_Msk               (0x3fff0000UL) /*!< GCBMUL2 (Bitfield-Mask: 0x3fff)                       */
/* =======================================================  UDS_CTRL  ======================================================== */
 #define R_VIN_UDS_CTRL_NE_BCB_Pos             (16UL)         /*!< NE_BCB (Bit 16)                                       */
 #define R_VIN_UDS_CTRL_NE_BCB_Msk             (0x10000UL)    /*!< NE_BCB (Bitfield-Mask: 0x01)                          */
 #define R_VIN_UDS_CTRL_NE_GY_Pos              (17UL)         /*!< NE_GY (Bit 17)                                        */
 #define R_VIN_UDS_CTRL_NE_GY_Msk              (0x20000UL)    /*!< NE_GY (Bitfield-Mask: 0x01)                           */
 #define R_VIN_UDS_CTRL_NE_RCR_Pos             (18UL)         /*!< NE_RCR (Bit 18)                                       */
 #define R_VIN_UDS_CTRL_NE_RCR_Msk             (0x40000UL)    /*!< NE_RCR (Bitfield-Mask: 0x01)                          */
 #define R_VIN_UDS_CTRL_BC_Pos                 (20UL)         /*!< BC (Bit 20)                                           */
 #define R_VIN_UDS_CTRL_BC_Msk                 (0x100000UL)   /*!< BC (Bitfield-Mask: 0x01)                              */
 #define R_VIN_UDS_CTRL_BLADV_Pos              (28UL)         /*!< BLADV (Bit 28)                                        */
 #define R_VIN_UDS_CTRL_BLADV_Msk              (0x10000000UL) /*!< BLADV (Bitfield-Mask: 0x01)                           */
 #define R_VIN_UDS_CTRL_AMD_Pos                (30UL)         /*!< AMD (Bit 30)                                          */
 #define R_VIN_UDS_CTRL_AMD_Msk                (0x40000000UL) /*!< AMD (Bitfield-Mask: 0x01)                             */
/* =======================================================  UDS_SCALE  ======================================================= */
 #define R_VIN_UDS_SCALE_VFRAC_Pos             (0UL)          /*!< VFRAC (Bit 0)                                         */
 #define R_VIN_UDS_SCALE_VFRAC_Msk             (0xfffUL)      /*!< VFRAC (Bitfield-Mask: 0xfff)                          */
 #define R_VIN_UDS_SCALE_VMANT_Pos             (12UL)         /*!< VMANT (Bit 12)                                        */
 #define R_VIN_UDS_SCALE_VMANT_Msk             (0xf000UL)     /*!< VMANT (Bitfield-Mask: 0x0f)                           */
 #define R_VIN_UDS_SCALE_HFRAC_Pos             (16UL)         /*!< HFRAC (Bit 16)                                        */
 #define R_VIN_UDS_SCALE_HFRAC_Msk             (0xfff0000UL)  /*!< HFRAC (Bitfield-Mask: 0xfff)                          */
 #define R_VIN_UDS_SCALE_HMANT_Pos             (28UL)         /*!< HMANT (Bit 28)                                        */
 #define R_VIN_UDS_SCALE_HMANT_Msk             (0xf0000000UL) /*!< HMANT (Bitfield-Mask: 0x0f)                           */
/* ====================================================  UDS_PASS_BWIDTH  ==================================================== */
 #define R_VIN_UDS_PASS_BWIDTH_BWIDTH_V_Pos    (0UL)          /*!< BWIDTH_V (Bit 0)                                      */
 #define R_VIN_UDS_PASS_BWIDTH_BWIDTH_V_Msk    (0x7fUL)       /*!< BWIDTH_V (Bitfield-Mask: 0x7f)                        */
 #define R_VIN_UDS_PASS_BWIDTH_BWIDTH_H_Pos    (16UL)         /*!< BWIDTH_H (Bit 16)                                     */
 #define R_VIN_UDS_PASS_BWIDTH_BWIDTH_H_Msk    (0x7f0000UL)   /*!< BWIDTH_H (Bitfield-Mask: 0x7f)                        */
/* =====================================================  UDS_CLIP_SIZE  ===================================================== */
 #define R_VIN_UDS_CLIP_SIZE_CL_VSIZE_Pos      (0UL)          /*!< CL_VSIZE (Bit 0)                                      */
 #define R_VIN_UDS_CLIP_SIZE_CL_VSIZE_Msk      (0xfffUL)      /*!< CL_VSIZE (Bitfield-Mask: 0xfff)                       */
 #define R_VIN_UDS_CLIP_SIZE_CL_HSIZE_Pos      (16UL)         /*!< CL_HSIZE (Bit 16)                                     */
 #define R_VIN_UDS_CLIP_SIZE_CL_HSIZE_Msk      (0xfff0000UL)  /*!< CL_HSIZE (Bitfield-Mask: 0xfff)                       */
/* =========================================================  LUTP  ========================================================== */
 #define R_VIN_LUTP_LTCRPR_Pos                 (0UL)          /*!< LTCRPR (Bit 0)                                        */
 #define R_VIN_LUTP_LTCRPR_Msk                 (0x3ffUL)      /*!< LTCRPR (Bitfield-Mask: 0x3ff)                         */
 #define R_VIN_LUTP_LTCBPR_Pos                 (10UL)         /*!< LTCBPR (Bit 10)                                       */
 #define R_VIN_LUTP_LTCBPR_Msk                 (0xffc00UL)    /*!< LTCBPR (Bitfield-Mask: 0x3ff)                         */
 #define R_VIN_LUTP_LTYPR_Pos                  (20UL)         /*!< LTYPR (Bit 20)                                        */
 #define R_VIN_LUTP_LTYPR_Msk                  (0x3ff00000UL) /*!< LTYPR (Bitfield-Mask: 0x3ff)                          */
/* =========================================================  LUTD  ========================================================== */
 #define R_VIN_LUTD_LTCRDT_Pos                 (0UL)          /*!< LTCRDT (Bit 0)                                        */
 #define R_VIN_LUTD_LTCRDT_Msk                 (0xffUL)       /*!< LTCRDT (Bitfield-Mask: 0xff)                          */
 #define R_VIN_LUTD_LTCBDT_Pos                 (8UL)          /*!< LTCBDT (Bit 8)                                        */
 #define R_VIN_LUTD_LTCBDT_Msk                 (0xff00UL)     /*!< LTCBDT (Bitfield-Mask: 0xff)                          */
 #define R_VIN_LUTD_LTYDT_Pos                  (16UL)         /*!< LTYDT (Bit 16)                                        */
 #define R_VIN_LUTD_LTYDT_Msk                  (0xff0000UL)   /*!< LTYDT (Bitfield-Mask: 0xff)                           */
/* =========================================================  YCCR1  ========================================================= */
 #define R_VIN_YCCR1_YCLRP_Pos                 (0UL)          /*!< YCLRP (Bit 0)                                         */
 #define R_VIN_YCCR1_YCLRP_Msk                 (0x1fffUL)     /*!< YCLRP (Bitfield-Mask: 0x1fff)                         */
/* =========================================================  YCCR2  ========================================================= */
 #define R_VIN_YCCR2_YCLGP_Pos                 (0UL)          /*!< YCLGP (Bit 0)                                         */
 #define R_VIN_YCCR2_YCLGP_Msk                 (0x1fffUL)     /*!< YCLGP (Bitfield-Mask: 0x1fff)                         */
 #define R_VIN_YCCR2_YCLBP_Pos                 (16UL)         /*!< YCLBP (Bit 16)                                        */
 #define R_VIN_YCCR2_YCLBP_Msk                 (0x1fff0000UL) /*!< YCLBP (Bitfield-Mask: 0x1fff)                         */
/* =========================================================  YCCR3  ========================================================= */
 #define R_VIN_YCCR3_YCLAP_Pos                 (0UL)          /*!< YCLAP (Bit 0)                                         */
 #define R_VIN_YCCR3_YCLAP_Msk                 (0xfffUL)      /*!< YCLAP (Bitfield-Mask: 0xfff)                          */
 #define R_VIN_YCCR3_YCLHEN_Pos                (23UL)         /*!< YCLHEN (Bit 23)                                       */
 #define R_VIN_YCCR3_YCLHEN_Msk                (0x800000UL)   /*!< YCLHEN (Bitfield-Mask: 0x01)                          */
 #define R_VIN_YCCR3_YCLSFT_Pos                (24UL)         /*!< YCLSFT (Bit 24)                                       */
 #define R_VIN_YCCR3_YCLSFT_Msk                (0x1f000000UL) /*!< YCLSFT (Bitfield-Mask: 0x1f)                          */
/* ========================================================  CBCCR1  ========================================================= */
 #define R_VIN_CBCCR1_CBCLRP_Pos               (0UL)          /*!< CBCLRP (Bit 0)                                        */
 #define R_VIN_CBCCR1_CBCLRP_Msk               (0x1fffUL)     /*!< CBCLRP (Bitfield-Mask: 0x1fff)                        */
/* ========================================================  CBCCR2  ========================================================= */
 #define R_VIN_CBCCR2_CBCLGP_Pos               (0UL)          /*!< CBCLGP (Bit 0)                                        */
 #define R_VIN_CBCCR2_CBCLGP_Msk               (0x1fffUL)     /*!< CBCLGP (Bitfield-Mask: 0x1fff)                        */
 #define R_VIN_CBCCR2_CBCLBP_Pos               (16UL)         /*!< CBCLBP (Bit 16)                                       */
 #define R_VIN_CBCCR2_CBCLBP_Msk               (0x1fff0000UL) /*!< CBCLBP (Bitfield-Mask: 0x1fff)                        */
/* ========================================================  CBCCR3  ========================================================= */
 #define R_VIN_CBCCR3_CBCLAP_Pos               (0UL)          /*!< CBCLAP (Bit 0)                                        */
 #define R_VIN_CBCCR3_CBCLAP_Msk               (0xfffUL)      /*!< CBCLAP (Bitfield-Mask: 0xfff)                         */
 #define R_VIN_CBCCR3_CBCLHEN_Pos              (23UL)         /*!< CBCLHEN (Bit 23)                                      */
 #define R_VIN_CBCCR3_CBCLHEN_Msk              (0x800000UL)   /*!< CBCLHEN (Bitfield-Mask: 0x01)                         */
 #define R_VIN_CBCCR3_CBCLSFT_Pos              (24UL)         /*!< CBCLSFT (Bit 24)                                      */
 #define R_VIN_CBCCR3_CBCLSFT_Msk              (0x1f000000UL) /*!< CBCLSFT (Bitfield-Mask: 0x1f)                         */
/* ========================================================  CRCCR1  ========================================================= */
 #define R_VIN_CRCCR1_CRCLRP_Pos               (0UL)          /*!< CRCLRP (Bit 0)                                        */
 #define R_VIN_CRCCR1_CRCLRP_Msk               (0x1fffUL)     /*!< CRCLRP (Bitfield-Mask: 0x1fff)                        */
/* ========================================================  CRCCR2  ========================================================= */
 #define R_VIN_CRCCR2_CRCLGP_Pos               (0UL)          /*!< CRCLGP (Bit 0)                                        */
 #define R_VIN_CRCCR2_CRCLGP_Msk               (0x1fffUL)     /*!< CRCLGP (Bitfield-Mask: 0x1fff)                        */
 #define R_VIN_CRCCR2_CRCLBP_Pos               (16UL)         /*!< CRCLBP (Bit 16)                                       */
 #define R_VIN_CRCCR2_CRCLBP_Msk               (0x1fff0000UL) /*!< CRCLBP (Bitfield-Mask: 0x1fff)                        */
/* ========================================================  CRCCR3  ========================================================= */
 #define R_VIN_CRCCR3_CRCLAP_Pos               (0UL)          /*!< CRCLAP (Bit 0)                                        */
 #define R_VIN_CRCCR3_CRCLAP_Msk               (0xfffUL)      /*!< CRCLAP (Bitfield-Mask: 0xfff)                         */
 #define R_VIN_CRCCR3_CRCLHEN_Pos              (23UL)         /*!< CRCLHEN (Bit 23)                                      */
 #define R_VIN_CRCCR3_CRCLHEN_Msk              (0x800000UL)   /*!< CRCLHEN (Bitfield-Mask: 0x01)                         */
 #define R_VIN_CRCCR3_CRCLSFT_Pos              (24UL)         /*!< CRCLSFT (Bit 24)                                      */
 #define R_VIN_CRCCR3_CRCLSFT_Msk              (0x1f000000UL) /*!< CRCLSFT (Bitfield-Mask: 0x1f)                         */

/* =========================================================================================================================== */
/* ================                                        R_MIPI_CSI                                         ================ */
/* =========================================================================================================================== */

/* ==========================================================  MCG  ========================================================== */
 #define R_MIPI_CSI_MCG_VER_Pos          (0UL)          /*!< VER (Bit 0)                                           */
 #define R_MIPI_CSI_MCG_VER_Msk          (0xfUL)        /*!< VER (Bitfield-Mask: 0x0f)                             */
 #define R_MIPI_CSI_MCG_SDLN_Pos         (8UL)          /*!< SDLN (Bit 8)                                          */
 #define R_MIPI_CSI_MCG_SDLN_Msk         (0xf00UL)      /*!< SDLN (Bitfield-Mask: 0x0f)                            */
 #define R_MIPI_CSI_MCG_GSNM_Pos         (16UL)         /*!< GSNM (Bit 16)                                         */
 #define R_MIPI_CSI_MCG_GSNM_Msk         (0xff0000UL)   /*!< GSNM (Bitfield-Mask: 0xff)                            */
/* =========================================================  MCT0  ========================================================== */
 #define R_MIPI_CSI_MCT0_VDLN_Pos        (0UL)          /*!< VDLN (Bit 0)                                          */
 #define R_MIPI_CSI_MCT0_VDLN_Msk        (0xfUL)        /*!< VDLN (Bitfield-Mask: 0x0f)                            */
 #define R_MIPI_CSI_MCT0_ZLMD_Pos        (16UL)         /*!< ZLMD (Bit 16)                                         */
 #define R_MIPI_CSI_MCT0_ZLMD_Msk        (0x10000UL)    /*!< ZLMD (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_MCT0_EDMD_Pos        (17UL)         /*!< EDMD (Bit 17)                                         */
 #define R_MIPI_CSI_MCT0_EDMD_Msk        (0x20000UL)    /*!< EDMD (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_MCT0_RVMD_Pos        (19UL)         /*!< RVMD (Bit 19)                                         */
 #define R_MIPI_CSI_MCT0_RVMD_Msk        (0x80000UL)    /*!< RVMD (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_MCT0_GRMD_Pos        (20UL)         /*!< GRMD (Bit 20)                                         */
 #define R_MIPI_CSI_MCT0_GRMD_Msk        (0x100000UL)   /*!< GRMD (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_MCT0_ECCV13_Pos      (24UL)         /*!< ECCV13 (Bit 24)                                       */
 #define R_MIPI_CSI_MCT0_ECCV13_Msk      (0x1000000UL)  /*!< ECCV13 (Bitfield-Mask: 0x01)                          */
 #define R_MIPI_CSI_MCT0_LFSREN_Pos      (25UL)         /*!< LFSREN (Bit 25)                                       */
 #define R_MIPI_CSI_MCT0_LFSREN_Msk      (0x2000000UL)  /*!< LFSREN (Bitfield-Mask: 0x01)                          */
/* =========================================================  MCT2  ========================================================== */
 #define R_MIPI_CSI_MCT2_FRRCLK_Pos      (0UL)          /*!< FRRCLK (Bit 0)                                        */
 #define R_MIPI_CSI_MCT2_FRRCLK_Msk      (0x1ffUL)      /*!< FRRCLK (Bitfield-Mask: 0x1ff)                         */
 #define R_MIPI_CSI_MCT2_FRRSKW_Pos      (16UL)         /*!< FRRSKW (Bit 16)                                       */
 #define R_MIPI_CSI_MCT2_FRRSKW_Msk      (0x1ff0000UL)  /*!< FRRSKW (Bitfield-Mask: 0x1ff)                         */
/* =========================================================  MCT3  ========================================================== */
 #define R_MIPI_CSI_MCT3_RXEN_Pos        (0UL)          /*!< RXEN (Bit 0)                                          */
 #define R_MIPI_CSI_MCT3_RXEN_Msk        (0x1UL)        /*!< RXEN (Bitfield-Mask: 0x01)                            */
/* =========================================================  RTCT  ========================================================== */
 #define R_MIPI_CSI_RTCT_VSRST_Pos       (0UL)          /*!< VSRST (Bit 0)                                         */
 #define R_MIPI_CSI_RTCT_VSRST_Msk       (0x1UL)        /*!< VSRST (Bitfield-Mask: 0x01)                           */
/* =========================================================  RTST  ========================================================== */
 #define R_MIPI_CSI_RTST_VSRSTS_Pos      (0UL)          /*!< VSRSTS (Bit 0)                                        */
 #define R_MIPI_CSI_RTST_VSRSTS_Msk      (0x1UL)        /*!< VSRSTS (Bitfield-Mask: 0x01)                          */
/* =========================================================  EPCT  ========================================================== */
 #define R_MIPI_CSI_EPCT_SLP_Pos         (0UL)          /*!< SLP (Bit 0)                                           */
 #define R_MIPI_CSI_EPCT_SLP_Msk         (0x7fffUL)     /*!< SLP (Bitfield-Mask: 0x7fff)                           */
 #define R_MIPI_CSI_EPCT_EPDOP_Pos       (15UL)         /*!< EPDOP (Bit 15)                                        */
 #define R_MIPI_CSI_EPCT_EPDOP_Msk       (0x8000UL)     /*!< EPDOP (Bitfield-Mask: 0x01)                           */
 #define R_MIPI_CSI_EPCT_SSP_Pos         (16UL)         /*!< SSP (Bit 16)                                          */
 #define R_MIPI_CSI_EPCT_SSP_Msk         (0x7fff0000UL) /*!< SSP (Bitfield-Mask: 0x7fff)                           */
 #define R_MIPI_CSI_EPCT_EPDEN_Pos       (31UL)         /*!< EPDEN (Bit 31)                                        */
 #define R_MIPI_CSI_EPCT_EPDEN_Msk       (0x80000000UL) /*!< EPDEN (Bitfield-Mask: 0x01)                           */
/* =========================================================  EMCT  ========================================================== */
 #define R_MIPI_CSI_EMCT_VLSIEN_Pos      (4UL)          /*!< VLSIEN (Bit 4)                                        */
 #define R_MIPI_CSI_EMCT_VLSIEN_Msk      (0x30UL)       /*!< VLSIEN (Bitfield-Mask: 0x03)                          */
 #define R_MIPI_CSI_EMCT_EOTPEN_Pos      (6UL)          /*!< EOTPEN (Bit 6)                                        */
 #define R_MIPI_CSI_EMCT_EOTPEN_Msk      (0x40UL)       /*!< EOTPEN (Bitfield-Mask: 0x01)                          */
/* =========================================================  MIST  ========================================================== */
 #define R_MIPI_CSI_MIST_DL0S_Pos        (0UL)          /*!< DL0S (Bit 0)                                          */
 #define R_MIPI_CSI_MIST_DL0S_Msk        (0x1UL)        /*!< DL0S (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_MIST_DL1S_Pos        (1UL)          /*!< DL1S (Bit 1)                                          */
 #define R_MIPI_CSI_MIST_DL1S_Msk        (0x2UL)        /*!< DL1S (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_MIST_PMS_Pos         (8UL)          /*!< PMS (Bit 8)                                           */
 #define R_MIPI_CSI_MIST_PMS_Msk         (0x100UL)      /*!< PMS (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_MIST_GSTS_Pos        (9UL)          /*!< GSTS (Bit 9)                                          */
 #define R_MIPI_CSI_MIST_GSTS_Msk        (0x200UL)      /*!< GSTS (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_MIST_RXS_Pos         (10UL)         /*!< RXS (Bit 10)                                          */
 #define R_MIPI_CSI_MIST_RXS_Msk         (0x400UL)      /*!< RXS (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_MIST_VC0S_Pos        (16UL)         /*!< VC0S (Bit 16)                                         */
 #define R_MIPI_CSI_MIST_VC0S_Msk        (0x10000UL)    /*!< VC0S (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_MIST_VC1S_Pos        (17UL)         /*!< VC1S (Bit 17)                                         */
 #define R_MIPI_CSI_MIST_VC1S_Msk        (0x20000UL)    /*!< VC1S (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_MIST_VC2S_Pos        (18UL)         /*!< VC2S (Bit 18)                                         */
 #define R_MIPI_CSI_MIST_VC2S_Msk        (0x40000UL)    /*!< VC2S (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_MIST_VC3S_Pos        (19UL)         /*!< VC3S (Bit 19)                                         */
 #define R_MIPI_CSI_MIST_VC3S_Msk        (0x80000UL)    /*!< VC3S (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_MIST_VC4S_Pos        (20UL)         /*!< VC4S (Bit 20)                                         */
 #define R_MIPI_CSI_MIST_VC4S_Msk        (0x100000UL)   /*!< VC4S (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_MIST_VC5S_Pos        (21UL)         /*!< VC5S (Bit 21)                                         */
 #define R_MIPI_CSI_MIST_VC5S_Msk        (0x200000UL)   /*!< VC5S (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_MIST_VC6S_Pos        (22UL)         /*!< VC6S (Bit 22)                                         */
 #define R_MIPI_CSI_MIST_VC6S_Msk        (0x400000UL)   /*!< VC6S (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_MIST_VC7S_Pos        (23UL)         /*!< VC7S (Bit 23)                                         */
 #define R_MIPI_CSI_MIST_VC7S_Msk        (0x800000UL)   /*!< VC7S (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_MIST_VC8S_Pos        (24UL)         /*!< VC8S (Bit 24)                                         */
 #define R_MIPI_CSI_MIST_VC8S_Msk        (0x1000000UL)  /*!< VC8S (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_MIST_VC9S_Pos        (25UL)         /*!< VC9S (Bit 25)                                         */
 #define R_MIPI_CSI_MIST_VC9S_Msk        (0x2000000UL)  /*!< VC9S (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_MIST_VC10S_Pos       (26UL)         /*!< VC10S (Bit 26)                                        */
 #define R_MIPI_CSI_MIST_VC10S_Msk       (0x4000000UL)  /*!< VC10S (Bitfield-Mask: 0x01)                           */
 #define R_MIPI_CSI_MIST_VC11S_Pos       (27UL)         /*!< VC11S (Bit 27)                                        */
 #define R_MIPI_CSI_MIST_VC11S_Msk       (0x8000000UL)  /*!< VC11S (Bitfield-Mask: 0x01)                           */
 #define R_MIPI_CSI_MIST_VC12S_Pos       (28UL)         /*!< VC12S (Bit 28)                                        */
 #define R_MIPI_CSI_MIST_VC12S_Msk       (0x10000000UL) /*!< VC12S (Bitfield-Mask: 0x01)                           */
 #define R_MIPI_CSI_MIST_VC13S_Pos       (29UL)         /*!< VC13S (Bit 29)                                        */
 #define R_MIPI_CSI_MIST_VC13S_Msk       (0x20000000UL) /*!< VC13S (Bitfield-Mask: 0x01)                           */
 #define R_MIPI_CSI_MIST_VC14S_Pos       (30UL)         /*!< VC14S (Bit 30)                                        */
 #define R_MIPI_CSI_MIST_VC14S_Msk       (0x40000000UL) /*!< VC14S (Bitfield-Mask: 0x01)                           */
 #define R_MIPI_CSI_MIST_VC15S_Pos       (31UL)         /*!< VC15S (Bit 31)                                        */
 #define R_MIPI_CSI_MIST_VC15S_Msk       (0x80000000UL) /*!< VC15S (Bitfield-Mask: 0x01)                           */
/* =========================================================  DTEL  ========================================================== */
 #define R_MIPI_CSI_DTEL_DTEN_Pos        (0UL)          /*!< DTEN (Bit 0)                                          */
 #define R_MIPI_CSI_DTEL_DTEN_Msk        (0xffffffffUL) /*!< DTEN (Bitfield-Mask: 0xffffffff)                      */
/* =========================================================  DTEH  ========================================================== */
 #define R_MIPI_CSI_DTEH_DTEN_Pos        (0UL)          /*!< DTEN (Bit 0)                                          */
 #define R_MIPI_CSI_DTEH_DTEN_Msk        (0xffffffffUL) /*!< DTEN (Bitfield-Mask: 0xffffffff)                      */
/* =========================================================  RXST  ========================================================== */
 #define R_MIPI_CSI_RXST_FRM0_Pos        (0UL)          /*!< FRM0 (Bit 0)                                          */
 #define R_MIPI_CSI_RXST_FRM0_Msk        (0x1UL)        /*!< FRM0 (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_RXST_FRM1_Pos        (1UL)          /*!< FRM1 (Bit 1)                                          */
 #define R_MIPI_CSI_RXST_FRM1_Msk        (0x2UL)        /*!< FRM1 (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_RXST_FRM2_Pos        (2UL)          /*!< FRM2 (Bit 2)                                          */
 #define R_MIPI_CSI_RXST_FRM2_Msk        (0x4UL)        /*!< FRM2 (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_RXST_FRM3_Pos        (3UL)          /*!< FRM3 (Bit 3)                                          */
 #define R_MIPI_CSI_RXST_FRM3_Msk        (0x8UL)        /*!< FRM3 (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_RXST_FRM4_Pos        (4UL)          /*!< FRM4 (Bit 4)                                          */
 #define R_MIPI_CSI_RXST_FRM4_Msk        (0x10UL)       /*!< FRM4 (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_RXST_FRM5_Pos        (5UL)          /*!< FRM5 (Bit 5)                                          */
 #define R_MIPI_CSI_RXST_FRM5_Msk        (0x20UL)       /*!< FRM5 (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_RXST_FRM6_Pos        (6UL)          /*!< FRM6 (Bit 6)                                          */
 #define R_MIPI_CSI_RXST_FRM6_Msk        (0x40UL)       /*!< FRM6 (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_RXST_FRM7_Pos        (7UL)          /*!< FRM7 (Bit 7)                                          */
 #define R_MIPI_CSI_RXST_FRM7_Msk        (0x80UL)       /*!< FRM7 (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_RXST_FRM8_Pos        (8UL)          /*!< FRM8 (Bit 8)                                          */
 #define R_MIPI_CSI_RXST_FRM8_Msk        (0x100UL)      /*!< FRM8 (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_RXST_FRM9_Pos        (9UL)          /*!< FRM9 (Bit 9)                                          */
 #define R_MIPI_CSI_RXST_FRM9_Msk        (0x200UL)      /*!< FRM9 (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_RXST_FRM10_Pos       (10UL)         /*!< FRM10 (Bit 10)                                        */
 #define R_MIPI_CSI_RXST_FRM10_Msk       (0x400UL)      /*!< FRM10 (Bitfield-Mask: 0x01)                           */
 #define R_MIPI_CSI_RXST_FRM11_Pos       (11UL)         /*!< FRM11 (Bit 11)                                        */
 #define R_MIPI_CSI_RXST_FRM11_Msk       (0x800UL)      /*!< FRM11 (Bitfield-Mask: 0x01)                           */
 #define R_MIPI_CSI_RXST_FRM12_Pos       (12UL)         /*!< FRM12 (Bit 12)                                        */
 #define R_MIPI_CSI_RXST_FRM12_Msk       (0x1000UL)     /*!< FRM12 (Bitfield-Mask: 0x01)                           */
 #define R_MIPI_CSI_RXST_FRM13_Pos       (13UL)         /*!< FRM13 (Bit 13)                                        */
 #define R_MIPI_CSI_RXST_FRM13_Msk       (0x2000UL)     /*!< FRM13 (Bitfield-Mask: 0x01)                           */
 #define R_MIPI_CSI_RXST_FRM14_Pos       (14UL)         /*!< FRM14 (Bit 14)                                        */
 #define R_MIPI_CSI_RXST_FRM14_Msk       (0x4000UL)     /*!< FRM14 (Bitfield-Mask: 0x01)                           */
 #define R_MIPI_CSI_RXST_FRM15_Pos       (15UL)         /*!< FRM15 (Bit 15)                                        */
 #define R_MIPI_CSI_RXST_FRM15_Msk       (0x8000UL)     /*!< FRM15 (Bitfield-Mask: 0x01)                           */
 #define R_MIPI_CSI_RXST_RACT_Pos        (16UL)         /*!< RACT (Bit 16)                                         */
 #define R_MIPI_CSI_RXST_RACT_Msk        (0x10000UL)    /*!< RACT (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_RXST_RACTDET_Pos     (17UL)         /*!< RACTDET (Bit 17)                                      */
 #define R_MIPI_CSI_RXST_RACTDET_Msk     (0x20000UL)    /*!< RACTDET (Bitfield-Mask: 0x01)                         */
/* =========================================================  RXSC  ========================================================== */
 #define R_MIPI_CSI_RXSC_RACTDETC_Pos    (17UL)         /*!< RACTDETC (Bit 17)                                     */
 #define R_MIPI_CSI_RXSC_RACTDETC_Msk    (0x20000UL)    /*!< RACTDETC (Bitfield-Mask: 0x01)                        */
/* =========================================================  RXIE  ========================================================== */
 #define R_MIPI_CSI_RXIE_RACTDETE_Pos    (17UL)         /*!< RACTDETE (Bit 17)                                     */
 #define R_MIPI_CSI_RXIE_RACTDETE_Msk    (0x20000UL)    /*!< RACTDETE (Bitfield-Mask: 0x01)                        */
/* =========================================================  DLST0  ========================================================= */
 #define R_MIPI_CSI_DLST0_ESH_Pos        (0UL)          /*!< ESH (Bit 0)                                           */
 #define R_MIPI_CSI_DLST0_ESH_Msk        (0x1UL)        /*!< ESH (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_DLST0_ESS_Pos        (1UL)          /*!< ESS (Bit 1)                                           */
 #define R_MIPI_CSI_DLST0_ESS_Msk        (0x2UL)        /*!< ESS (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_DLST0_ECT_Pos        (2UL)          /*!< ECT (Bit 2)                                           */
 #define R_MIPI_CSI_DLST0_ECT_Msk        (0x4UL)        /*!< ECT (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_DLST0_EES_Pos        (3UL)          /*!< EES (Bit 3)                                           */
 #define R_MIPI_CSI_DLST0_EES_Msk        (0x8UL)        /*!< EES (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_DLST0_EUL_Pos        (16UL)         /*!< EUL (Bit 16)                                          */
 #define R_MIPI_CSI_DLST0_EUL_Msk        (0x10000UL)    /*!< EUL (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_DLST0_RUL_Pos        (17UL)         /*!< RUL (Bit 17)                                          */
 #define R_MIPI_CSI_DLST0_RUL_Msk        (0x20000UL)    /*!< RUL (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_DLST0_ULP_Pos        (24UL)         /*!< ULP (Bit 24)                                          */
 #define R_MIPI_CSI_DLST0_ULP_Msk        (0x1000000UL)  /*!< ULP (Bitfield-Mask: 0x01)                             */
/* =========================================================  DLST1  ========================================================= */
 #define R_MIPI_CSI_DLST1_ESH_Pos        (0UL)          /*!< ESH (Bit 0)                                           */
 #define R_MIPI_CSI_DLST1_ESH_Msk        (0x1UL)        /*!< ESH (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_DLST1_ESS_Pos        (1UL)          /*!< ESS (Bit 1)                                           */
 #define R_MIPI_CSI_DLST1_ESS_Msk        (0x2UL)        /*!< ESS (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_DLST1_ECT_Pos        (2UL)          /*!< ECT (Bit 2)                                           */
 #define R_MIPI_CSI_DLST1_ECT_Msk        (0x4UL)        /*!< ECT (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_DLST1_EES_Pos        (3UL)          /*!< EES (Bit 3)                                           */
 #define R_MIPI_CSI_DLST1_EES_Msk        (0x8UL)        /*!< EES (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_DLST1_EUL_Pos        (16UL)         /*!< EUL (Bit 16)                                          */
 #define R_MIPI_CSI_DLST1_EUL_Msk        (0x10000UL)    /*!< EUL (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_DLST1_RUL_Pos        (17UL)         /*!< RUL (Bit 17)                                          */
 #define R_MIPI_CSI_DLST1_RUL_Msk        (0x20000UL)    /*!< RUL (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_DLST1_ULP_Pos        (24UL)         /*!< ULP (Bit 24)                                          */
 #define R_MIPI_CSI_DLST1_ULP_Msk        (0x1000000UL)  /*!< ULP (Bitfield-Mask: 0x01)                             */
/* =========================================================  DLSC0  ========================================================= */
 #define R_MIPI_CSI_DLSC0_ESHC_Pos       (0UL)          /*!< ESHC (Bit 0)                                          */
 #define R_MIPI_CSI_DLSC0_ESHC_Msk       (0x1UL)        /*!< ESHC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_DLSC0_ESSC_Pos       (1UL)          /*!< ESSC (Bit 1)                                          */
 #define R_MIPI_CSI_DLSC0_ESSC_Msk       (0x2UL)        /*!< ESSC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_DLSC0_ECTC_Pos       (2UL)          /*!< ECTC (Bit 2)                                          */
 #define R_MIPI_CSI_DLSC0_ECTC_Msk       (0x4UL)        /*!< ECTC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_DLSC0_EESC_Pos       (3UL)          /*!< EESC (Bit 3)                                          */
 #define R_MIPI_CSI_DLSC0_EESC_Msk       (0x8UL)        /*!< EESC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_DLSC0_EULC_Pos       (16UL)         /*!< EULC (Bit 16)                                         */
 #define R_MIPI_CSI_DLSC0_EULC_Msk       (0x10000UL)    /*!< EULC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_DLSC0_RULC_Pos       (17UL)         /*!< RULC (Bit 17)                                         */
 #define R_MIPI_CSI_DLSC0_RULC_Msk       (0x20000UL)    /*!< RULC (Bitfield-Mask: 0x01)                            */
/* =========================================================  DLSC1  ========================================================= */
 #define R_MIPI_CSI_DLSC1_ESHC_Pos       (0UL)          /*!< ESHC (Bit 0)                                          */
 #define R_MIPI_CSI_DLSC1_ESHC_Msk       (0x1UL)        /*!< ESHC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_DLSC1_ESSC_Pos       (1UL)          /*!< ESSC (Bit 1)                                          */
 #define R_MIPI_CSI_DLSC1_ESSC_Msk       (0x2UL)        /*!< ESSC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_DLSC1_ECTC_Pos       (2UL)          /*!< ECTC (Bit 2)                                          */
 #define R_MIPI_CSI_DLSC1_ECTC_Msk       (0x4UL)        /*!< ECTC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_DLSC1_EESC_Pos       (3UL)          /*!< EESC (Bit 3)                                          */
 #define R_MIPI_CSI_DLSC1_EESC_Msk       (0x8UL)        /*!< EESC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_DLSC1_EULC_Pos       (16UL)         /*!< EULC (Bit 16)                                         */
 #define R_MIPI_CSI_DLSC1_EULC_Msk       (0x10000UL)    /*!< EULC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_DLSC1_RULC_Pos       (17UL)         /*!< RULC (Bit 17)                                         */
 #define R_MIPI_CSI_DLSC1_RULC_Msk       (0x20000UL)    /*!< RULC (Bitfield-Mask: 0x01)                            */
/* =========================================================  DLIE0  ========================================================= */
 #define R_MIPI_CSI_DLIE0_ESHE_Pos       (0UL)          /*!< ESHE (Bit 0)                                          */
 #define R_MIPI_CSI_DLIE0_ESHE_Msk       (0x1UL)        /*!< ESHE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_DLIE0_ESSE_Pos       (1UL)          /*!< ESSE (Bit 1)                                          */
 #define R_MIPI_CSI_DLIE0_ESSE_Msk       (0x2UL)        /*!< ESSE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_DLIE0_ECTE_Pos       (2UL)          /*!< ECTE (Bit 2)                                          */
 #define R_MIPI_CSI_DLIE0_ECTE_Msk       (0x4UL)        /*!< ECTE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_DLIE0_EESE_Pos       (3UL)          /*!< EESE (Bit 3)                                          */
 #define R_MIPI_CSI_DLIE0_EESE_Msk       (0x8UL)        /*!< EESE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_DLIE0_EULE_Pos       (16UL)         /*!< EULE (Bit 16)                                         */
 #define R_MIPI_CSI_DLIE0_EULE_Msk       (0x10000UL)    /*!< EULE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_DLIE0_RULE_Pos       (17UL)         /*!< RULE (Bit 17)                                         */
 #define R_MIPI_CSI_DLIE0_RULE_Msk       (0x20000UL)    /*!< RULE (Bitfield-Mask: 0x01)                            */
/* =========================================================  DLIE1  ========================================================= */
 #define R_MIPI_CSI_DLIE1_ESHE_Pos       (0UL)          /*!< ESHE (Bit 0)                                          */
 #define R_MIPI_CSI_DLIE1_ESHE_Msk       (0x1UL)        /*!< ESHE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_DLIE1_ESSE_Pos       (1UL)          /*!< ESSE (Bit 1)                                          */
 #define R_MIPI_CSI_DLIE1_ESSE_Msk       (0x2UL)        /*!< ESSE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_DLIE1_ECTE_Pos       (2UL)          /*!< ECTE (Bit 2)                                          */
 #define R_MIPI_CSI_DLIE1_ECTE_Msk       (0x4UL)        /*!< ECTE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_DLIE1_EESE_Pos       (3UL)          /*!< EESE (Bit 3)                                          */
 #define R_MIPI_CSI_DLIE1_EESE_Msk       (0x8UL)        /*!< EESE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_DLIE1_EULE_Pos       (16UL)         /*!< EULE (Bit 16)                                         */
 #define R_MIPI_CSI_DLIE1_EULE_Msk       (0x10000UL)    /*!< EULE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_DLIE1_RULE_Pos       (17UL)         /*!< RULE (Bit 17)                                         */
 #define R_MIPI_CSI_DLIE1_RULE_Msk       (0x20000UL)    /*!< RULE (Bitfield-Mask: 0x01)                            */
/* =========================================================  VCST0  ========================================================= */
 #define R_MIPI_CSI_VCST0_MLF_Pos        (0UL)          /*!< MLF (Bit 0)                                           */
 #define R_MIPI_CSI_VCST0_MLF_Msk        (0x1UL)        /*!< MLF (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST0_ECD_Pos        (1UL)          /*!< ECD (Bit 1)                                           */
 #define R_MIPI_CSI_VCST0_ECD_Msk        (0x2UL)        /*!< ECD (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST0_CRC_Pos        (2UL)          /*!< CRC (Bit 2)                                           */
 #define R_MIPI_CSI_VCST0_CRC_Msk        (0x4UL)        /*!< CRC (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST0_IDE_Pos        (3UL)          /*!< IDE (Bit 3)                                           */
 #define R_MIPI_CSI_VCST0_IDE_Msk        (0x8UL)        /*!< IDE (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST0_WCE_Pos        (4UL)          /*!< WCE (Bit 4)                                           */
 #define R_MIPI_CSI_VCST0_WCE_Msk        (0x10UL)       /*!< WCE (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST0_ECC_Pos        (5UL)          /*!< ECC (Bit 5)                                           */
 #define R_MIPI_CSI_VCST0_ECC_Msk        (0x20UL)       /*!< ECC (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST0_ECN_Pos        (6UL)          /*!< ECN (Bit 6)                                           */
 #define R_MIPI_CSI_VCST0_ECN_Msk        (0x40UL)       /*!< ECN (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST0_FRS_Pos        (8UL)          /*!< FRS (Bit 8)                                           */
 #define R_MIPI_CSI_VCST0_FRS_Msk        (0x100UL)      /*!< FRS (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST0_FRD_Pos        (9UL)          /*!< FRD (Bit 9)                                           */
 #define R_MIPI_CSI_VCST0_FRD_Msk        (0x200UL)      /*!< FRD (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST0_OVF_Pos        (16UL)         /*!< OVF (Bit 16)                                          */
 #define R_MIPI_CSI_VCST0_OVF_Msk        (0x10000UL)    /*!< OVF (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST0_FSR_Pos        (24UL)         /*!< FSR (Bit 24)                                          */
 #define R_MIPI_CSI_VCST0_FSR_Msk        (0x1000000UL)  /*!< FSR (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST0_FER_Pos        (25UL)         /*!< FER (Bit 25)                                          */
 #define R_MIPI_CSI_VCST0_FER_Msk        (0x2000000UL)  /*!< FER (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST0_LSR_Pos        (26UL)         /*!< LSR (Bit 26)                                          */
 #define R_MIPI_CSI_VCST0_LSR_Msk        (0x4000000UL)  /*!< LSR (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST0_LER_Pos        (27UL)         /*!< LER (Bit 27)                                          */
 #define R_MIPI_CSI_VCST0_LER_Msk        (0x8000000UL)  /*!< LER (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST0_ETR_Pos        (28UL)         /*!< ETR (Bit 28)                                          */
 #define R_MIPI_CSI_VCST0_ETR_Msk        (0x10000000UL) /*!< ETR (Bitfield-Mask: 0x01)                             */
/* =========================================================  VCST1  ========================================================= */
 #define R_MIPI_CSI_VCST1_MLF_Pos        (0UL)          /*!< MLF (Bit 0)                                           */
 #define R_MIPI_CSI_VCST1_MLF_Msk        (0x1UL)        /*!< MLF (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST1_ECD_Pos        (1UL)          /*!< ECD (Bit 1)                                           */
 #define R_MIPI_CSI_VCST1_ECD_Msk        (0x2UL)        /*!< ECD (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST1_CRC_Pos        (2UL)          /*!< CRC (Bit 2)                                           */
 #define R_MIPI_CSI_VCST1_CRC_Msk        (0x4UL)        /*!< CRC (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST1_IDE_Pos        (3UL)          /*!< IDE (Bit 3)                                           */
 #define R_MIPI_CSI_VCST1_IDE_Msk        (0x8UL)        /*!< IDE (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST1_WCE_Pos        (4UL)          /*!< WCE (Bit 4)                                           */
 #define R_MIPI_CSI_VCST1_WCE_Msk        (0x10UL)       /*!< WCE (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST1_ECC_Pos        (5UL)          /*!< ECC (Bit 5)                                           */
 #define R_MIPI_CSI_VCST1_ECC_Msk        (0x20UL)       /*!< ECC (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST1_ECN_Pos        (6UL)          /*!< ECN (Bit 6)                                           */
 #define R_MIPI_CSI_VCST1_ECN_Msk        (0x40UL)       /*!< ECN (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST1_FRS_Pos        (8UL)          /*!< FRS (Bit 8)                                           */
 #define R_MIPI_CSI_VCST1_FRS_Msk        (0x100UL)      /*!< FRS (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST1_FRD_Pos        (9UL)          /*!< FRD (Bit 9)                                           */
 #define R_MIPI_CSI_VCST1_FRD_Msk        (0x200UL)      /*!< FRD (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST1_OVF_Pos        (16UL)         /*!< OVF (Bit 16)                                          */
 #define R_MIPI_CSI_VCST1_OVF_Msk        (0x10000UL)    /*!< OVF (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST1_FSR_Pos        (24UL)         /*!< FSR (Bit 24)                                          */
 #define R_MIPI_CSI_VCST1_FSR_Msk        (0x1000000UL)  /*!< FSR (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST1_FER_Pos        (25UL)         /*!< FER (Bit 25)                                          */
 #define R_MIPI_CSI_VCST1_FER_Msk        (0x2000000UL)  /*!< FER (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST1_LSR_Pos        (26UL)         /*!< LSR (Bit 26)                                          */
 #define R_MIPI_CSI_VCST1_LSR_Msk        (0x4000000UL)  /*!< LSR (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST1_LER_Pos        (27UL)         /*!< LER (Bit 27)                                          */
 #define R_MIPI_CSI_VCST1_LER_Msk        (0x8000000UL)  /*!< LER (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST1_ETR_Pos        (28UL)         /*!< ETR (Bit 28)                                          */
 #define R_MIPI_CSI_VCST1_ETR_Msk        (0x10000000UL) /*!< ETR (Bitfield-Mask: 0x01)                             */
/* =========================================================  VCST2  ========================================================= */
 #define R_MIPI_CSI_VCST2_MLF_Pos        (0UL)          /*!< MLF (Bit 0)                                           */
 #define R_MIPI_CSI_VCST2_MLF_Msk        (0x1UL)        /*!< MLF (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST2_ECD_Pos        (1UL)          /*!< ECD (Bit 1)                                           */
 #define R_MIPI_CSI_VCST2_ECD_Msk        (0x2UL)        /*!< ECD (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST2_CRC_Pos        (2UL)          /*!< CRC (Bit 2)                                           */
 #define R_MIPI_CSI_VCST2_CRC_Msk        (0x4UL)        /*!< CRC (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST2_IDE_Pos        (3UL)          /*!< IDE (Bit 3)                                           */
 #define R_MIPI_CSI_VCST2_IDE_Msk        (0x8UL)        /*!< IDE (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST2_WCE_Pos        (4UL)          /*!< WCE (Bit 4)                                           */
 #define R_MIPI_CSI_VCST2_WCE_Msk        (0x10UL)       /*!< WCE (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST2_ECC_Pos        (5UL)          /*!< ECC (Bit 5)                                           */
 #define R_MIPI_CSI_VCST2_ECC_Msk        (0x20UL)       /*!< ECC (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST2_ECN_Pos        (6UL)          /*!< ECN (Bit 6)                                           */
 #define R_MIPI_CSI_VCST2_ECN_Msk        (0x40UL)       /*!< ECN (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST2_FRS_Pos        (8UL)          /*!< FRS (Bit 8)                                           */
 #define R_MIPI_CSI_VCST2_FRS_Msk        (0x100UL)      /*!< FRS (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST2_FRD_Pos        (9UL)          /*!< FRD (Bit 9)                                           */
 #define R_MIPI_CSI_VCST2_FRD_Msk        (0x200UL)      /*!< FRD (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST2_OVF_Pos        (16UL)         /*!< OVF (Bit 16)                                          */
 #define R_MIPI_CSI_VCST2_OVF_Msk        (0x10000UL)    /*!< OVF (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST2_FSR_Pos        (24UL)         /*!< FSR (Bit 24)                                          */
 #define R_MIPI_CSI_VCST2_FSR_Msk        (0x1000000UL)  /*!< FSR (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST2_FER_Pos        (25UL)         /*!< FER (Bit 25)                                          */
 #define R_MIPI_CSI_VCST2_FER_Msk        (0x2000000UL)  /*!< FER (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST2_LSR_Pos        (26UL)         /*!< LSR (Bit 26)                                          */
 #define R_MIPI_CSI_VCST2_LSR_Msk        (0x4000000UL)  /*!< LSR (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST2_LER_Pos        (27UL)         /*!< LER (Bit 27)                                          */
 #define R_MIPI_CSI_VCST2_LER_Msk        (0x8000000UL)  /*!< LER (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST2_ETR_Pos        (28UL)         /*!< ETR (Bit 28)                                          */
 #define R_MIPI_CSI_VCST2_ETR_Msk        (0x10000000UL) /*!< ETR (Bitfield-Mask: 0x01)                             */
/* =========================================================  VCST3  ========================================================= */
 #define R_MIPI_CSI_VCST3_MLF_Pos        (0UL)          /*!< MLF (Bit 0)                                           */
 #define R_MIPI_CSI_VCST3_MLF_Msk        (0x1UL)        /*!< MLF (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST3_ECD_Pos        (1UL)          /*!< ECD (Bit 1)                                           */
 #define R_MIPI_CSI_VCST3_ECD_Msk        (0x2UL)        /*!< ECD (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST3_CRC_Pos        (2UL)          /*!< CRC (Bit 2)                                           */
 #define R_MIPI_CSI_VCST3_CRC_Msk        (0x4UL)        /*!< CRC (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST3_IDE_Pos        (3UL)          /*!< IDE (Bit 3)                                           */
 #define R_MIPI_CSI_VCST3_IDE_Msk        (0x8UL)        /*!< IDE (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST3_WCE_Pos        (4UL)          /*!< WCE (Bit 4)                                           */
 #define R_MIPI_CSI_VCST3_WCE_Msk        (0x10UL)       /*!< WCE (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST3_ECC_Pos        (5UL)          /*!< ECC (Bit 5)                                           */
 #define R_MIPI_CSI_VCST3_ECC_Msk        (0x20UL)       /*!< ECC (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST3_ECN_Pos        (6UL)          /*!< ECN (Bit 6)                                           */
 #define R_MIPI_CSI_VCST3_ECN_Msk        (0x40UL)       /*!< ECN (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST3_FRS_Pos        (8UL)          /*!< FRS (Bit 8)                                           */
 #define R_MIPI_CSI_VCST3_FRS_Msk        (0x100UL)      /*!< FRS (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST3_FRD_Pos        (9UL)          /*!< FRD (Bit 9)                                           */
 #define R_MIPI_CSI_VCST3_FRD_Msk        (0x200UL)      /*!< FRD (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST3_OVF_Pos        (16UL)         /*!< OVF (Bit 16)                                          */
 #define R_MIPI_CSI_VCST3_OVF_Msk        (0x10000UL)    /*!< OVF (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST3_FSR_Pos        (24UL)         /*!< FSR (Bit 24)                                          */
 #define R_MIPI_CSI_VCST3_FSR_Msk        (0x1000000UL)  /*!< FSR (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST3_FER_Pos        (25UL)         /*!< FER (Bit 25)                                          */
 #define R_MIPI_CSI_VCST3_FER_Msk        (0x2000000UL)  /*!< FER (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST3_LSR_Pos        (26UL)         /*!< LSR (Bit 26)                                          */
 #define R_MIPI_CSI_VCST3_LSR_Msk        (0x4000000UL)  /*!< LSR (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST3_LER_Pos        (27UL)         /*!< LER (Bit 27)                                          */
 #define R_MIPI_CSI_VCST3_LER_Msk        (0x8000000UL)  /*!< LER (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST3_ETR_Pos        (28UL)         /*!< ETR (Bit 28)                                          */
 #define R_MIPI_CSI_VCST3_ETR_Msk        (0x10000000UL) /*!< ETR (Bitfield-Mask: 0x01)                             */
/* =========================================================  VCST4  ========================================================= */
 #define R_MIPI_CSI_VCST4_MLF_Pos        (0UL)          /*!< MLF (Bit 0)                                           */
 #define R_MIPI_CSI_VCST4_MLF_Msk        (0x1UL)        /*!< MLF (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST4_ECD_Pos        (1UL)          /*!< ECD (Bit 1)                                           */
 #define R_MIPI_CSI_VCST4_ECD_Msk        (0x2UL)        /*!< ECD (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST4_CRC_Pos        (2UL)          /*!< CRC (Bit 2)                                           */
 #define R_MIPI_CSI_VCST4_CRC_Msk        (0x4UL)        /*!< CRC (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST4_IDE_Pos        (3UL)          /*!< IDE (Bit 3)                                           */
 #define R_MIPI_CSI_VCST4_IDE_Msk        (0x8UL)        /*!< IDE (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST4_WCE_Pos        (4UL)          /*!< WCE (Bit 4)                                           */
 #define R_MIPI_CSI_VCST4_WCE_Msk        (0x10UL)       /*!< WCE (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST4_ECC_Pos        (5UL)          /*!< ECC (Bit 5)                                           */
 #define R_MIPI_CSI_VCST4_ECC_Msk        (0x20UL)       /*!< ECC (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST4_ECN_Pos        (6UL)          /*!< ECN (Bit 6)                                           */
 #define R_MIPI_CSI_VCST4_ECN_Msk        (0x40UL)       /*!< ECN (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST4_FRS_Pos        (8UL)          /*!< FRS (Bit 8)                                           */
 #define R_MIPI_CSI_VCST4_FRS_Msk        (0x100UL)      /*!< FRS (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST4_FRD_Pos        (9UL)          /*!< FRD (Bit 9)                                           */
 #define R_MIPI_CSI_VCST4_FRD_Msk        (0x200UL)      /*!< FRD (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST4_OVF_Pos        (16UL)         /*!< OVF (Bit 16)                                          */
 #define R_MIPI_CSI_VCST4_OVF_Msk        (0x10000UL)    /*!< OVF (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST4_FSR_Pos        (24UL)         /*!< FSR (Bit 24)                                          */
 #define R_MIPI_CSI_VCST4_FSR_Msk        (0x1000000UL)  /*!< FSR (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST4_FER_Pos        (25UL)         /*!< FER (Bit 25)                                          */
 #define R_MIPI_CSI_VCST4_FER_Msk        (0x2000000UL)  /*!< FER (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST4_LSR_Pos        (26UL)         /*!< LSR (Bit 26)                                          */
 #define R_MIPI_CSI_VCST4_LSR_Msk        (0x4000000UL)  /*!< LSR (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST4_LER_Pos        (27UL)         /*!< LER (Bit 27)                                          */
 #define R_MIPI_CSI_VCST4_LER_Msk        (0x8000000UL)  /*!< LER (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST4_ETR_Pos        (28UL)         /*!< ETR (Bit 28)                                          */
 #define R_MIPI_CSI_VCST4_ETR_Msk        (0x10000000UL) /*!< ETR (Bitfield-Mask: 0x01)                             */
/* =========================================================  VCST5  ========================================================= */
 #define R_MIPI_CSI_VCST5_MLF_Pos        (0UL)          /*!< MLF (Bit 0)                                           */
 #define R_MIPI_CSI_VCST5_MLF_Msk        (0x1UL)        /*!< MLF (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST5_ECD_Pos        (1UL)          /*!< ECD (Bit 1)                                           */
 #define R_MIPI_CSI_VCST5_ECD_Msk        (0x2UL)        /*!< ECD (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST5_CRC_Pos        (2UL)          /*!< CRC (Bit 2)                                           */
 #define R_MIPI_CSI_VCST5_CRC_Msk        (0x4UL)        /*!< CRC (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST5_IDE_Pos        (3UL)          /*!< IDE (Bit 3)                                           */
 #define R_MIPI_CSI_VCST5_IDE_Msk        (0x8UL)        /*!< IDE (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST5_WCE_Pos        (4UL)          /*!< WCE (Bit 4)                                           */
 #define R_MIPI_CSI_VCST5_WCE_Msk        (0x10UL)       /*!< WCE (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST5_ECC_Pos        (5UL)          /*!< ECC (Bit 5)                                           */
 #define R_MIPI_CSI_VCST5_ECC_Msk        (0x20UL)       /*!< ECC (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST5_ECN_Pos        (6UL)          /*!< ECN (Bit 6)                                           */
 #define R_MIPI_CSI_VCST5_ECN_Msk        (0x40UL)       /*!< ECN (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST5_FRS_Pos        (8UL)          /*!< FRS (Bit 8)                                           */
 #define R_MIPI_CSI_VCST5_FRS_Msk        (0x100UL)      /*!< FRS (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST5_FRD_Pos        (9UL)          /*!< FRD (Bit 9)                                           */
 #define R_MIPI_CSI_VCST5_FRD_Msk        (0x200UL)      /*!< FRD (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST5_OVF_Pos        (16UL)         /*!< OVF (Bit 16)                                          */
 #define R_MIPI_CSI_VCST5_OVF_Msk        (0x10000UL)    /*!< OVF (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST5_FSR_Pos        (24UL)         /*!< FSR (Bit 24)                                          */
 #define R_MIPI_CSI_VCST5_FSR_Msk        (0x1000000UL)  /*!< FSR (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST5_FER_Pos        (25UL)         /*!< FER (Bit 25)                                          */
 #define R_MIPI_CSI_VCST5_FER_Msk        (0x2000000UL)  /*!< FER (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST5_LSR_Pos        (26UL)         /*!< LSR (Bit 26)                                          */
 #define R_MIPI_CSI_VCST5_LSR_Msk        (0x4000000UL)  /*!< LSR (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST5_LER_Pos        (27UL)         /*!< LER (Bit 27)                                          */
 #define R_MIPI_CSI_VCST5_LER_Msk        (0x8000000UL)  /*!< LER (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST5_ETR_Pos        (28UL)         /*!< ETR (Bit 28)                                          */
 #define R_MIPI_CSI_VCST5_ETR_Msk        (0x10000000UL) /*!< ETR (Bitfield-Mask: 0x01)                             */
/* =========================================================  VCST6  ========================================================= */
 #define R_MIPI_CSI_VCST6_MLF_Pos        (0UL)          /*!< MLF (Bit 0)                                           */
 #define R_MIPI_CSI_VCST6_MLF_Msk        (0x1UL)        /*!< MLF (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST6_ECD_Pos        (1UL)          /*!< ECD (Bit 1)                                           */
 #define R_MIPI_CSI_VCST6_ECD_Msk        (0x2UL)        /*!< ECD (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST6_CRC_Pos        (2UL)          /*!< CRC (Bit 2)                                           */
 #define R_MIPI_CSI_VCST6_CRC_Msk        (0x4UL)        /*!< CRC (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST6_IDE_Pos        (3UL)          /*!< IDE (Bit 3)                                           */
 #define R_MIPI_CSI_VCST6_IDE_Msk        (0x8UL)        /*!< IDE (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST6_WCE_Pos        (4UL)          /*!< WCE (Bit 4)                                           */
 #define R_MIPI_CSI_VCST6_WCE_Msk        (0x10UL)       /*!< WCE (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST6_ECC_Pos        (5UL)          /*!< ECC (Bit 5)                                           */
 #define R_MIPI_CSI_VCST6_ECC_Msk        (0x20UL)       /*!< ECC (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST6_ECN_Pos        (6UL)          /*!< ECN (Bit 6)                                           */
 #define R_MIPI_CSI_VCST6_ECN_Msk        (0x40UL)       /*!< ECN (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST6_FRS_Pos        (8UL)          /*!< FRS (Bit 8)                                           */
 #define R_MIPI_CSI_VCST6_FRS_Msk        (0x100UL)      /*!< FRS (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST6_FRD_Pos        (9UL)          /*!< FRD (Bit 9)                                           */
 #define R_MIPI_CSI_VCST6_FRD_Msk        (0x200UL)      /*!< FRD (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST6_OVF_Pos        (16UL)         /*!< OVF (Bit 16)                                          */
 #define R_MIPI_CSI_VCST6_OVF_Msk        (0x10000UL)    /*!< OVF (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST6_FSR_Pos        (24UL)         /*!< FSR (Bit 24)                                          */
 #define R_MIPI_CSI_VCST6_FSR_Msk        (0x1000000UL)  /*!< FSR (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST6_FER_Pos        (25UL)         /*!< FER (Bit 25)                                          */
 #define R_MIPI_CSI_VCST6_FER_Msk        (0x2000000UL)  /*!< FER (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST6_LSR_Pos        (26UL)         /*!< LSR (Bit 26)                                          */
 #define R_MIPI_CSI_VCST6_LSR_Msk        (0x4000000UL)  /*!< LSR (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST6_LER_Pos        (27UL)         /*!< LER (Bit 27)                                          */
 #define R_MIPI_CSI_VCST6_LER_Msk        (0x8000000UL)  /*!< LER (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST6_ETR_Pos        (28UL)         /*!< ETR (Bit 28)                                          */
 #define R_MIPI_CSI_VCST6_ETR_Msk        (0x10000000UL) /*!< ETR (Bitfield-Mask: 0x01)                             */
/* =========================================================  VCST7  ========================================================= */
 #define R_MIPI_CSI_VCST7_MLF_Pos        (0UL)          /*!< MLF (Bit 0)                                           */
 #define R_MIPI_CSI_VCST7_MLF_Msk        (0x1UL)        /*!< MLF (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST7_ECD_Pos        (1UL)          /*!< ECD (Bit 1)                                           */
 #define R_MIPI_CSI_VCST7_ECD_Msk        (0x2UL)        /*!< ECD (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST7_CRC_Pos        (2UL)          /*!< CRC (Bit 2)                                           */
 #define R_MIPI_CSI_VCST7_CRC_Msk        (0x4UL)        /*!< CRC (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST7_IDE_Pos        (3UL)          /*!< IDE (Bit 3)                                           */
 #define R_MIPI_CSI_VCST7_IDE_Msk        (0x8UL)        /*!< IDE (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST7_WCE_Pos        (4UL)          /*!< WCE (Bit 4)                                           */
 #define R_MIPI_CSI_VCST7_WCE_Msk        (0x10UL)       /*!< WCE (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST7_ECC_Pos        (5UL)          /*!< ECC (Bit 5)                                           */
 #define R_MIPI_CSI_VCST7_ECC_Msk        (0x20UL)       /*!< ECC (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST7_ECN_Pos        (6UL)          /*!< ECN (Bit 6)                                           */
 #define R_MIPI_CSI_VCST7_ECN_Msk        (0x40UL)       /*!< ECN (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST7_FRS_Pos        (8UL)          /*!< FRS (Bit 8)                                           */
 #define R_MIPI_CSI_VCST7_FRS_Msk        (0x100UL)      /*!< FRS (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST7_FRD_Pos        (9UL)          /*!< FRD (Bit 9)                                           */
 #define R_MIPI_CSI_VCST7_FRD_Msk        (0x200UL)      /*!< FRD (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST7_OVF_Pos        (16UL)         /*!< OVF (Bit 16)                                          */
 #define R_MIPI_CSI_VCST7_OVF_Msk        (0x10000UL)    /*!< OVF (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST7_FSR_Pos        (24UL)         /*!< FSR (Bit 24)                                          */
 #define R_MIPI_CSI_VCST7_FSR_Msk        (0x1000000UL)  /*!< FSR (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST7_FER_Pos        (25UL)         /*!< FER (Bit 25)                                          */
 #define R_MIPI_CSI_VCST7_FER_Msk        (0x2000000UL)  /*!< FER (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST7_LSR_Pos        (26UL)         /*!< LSR (Bit 26)                                          */
 #define R_MIPI_CSI_VCST7_LSR_Msk        (0x4000000UL)  /*!< LSR (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST7_LER_Pos        (27UL)         /*!< LER (Bit 27)                                          */
 #define R_MIPI_CSI_VCST7_LER_Msk        (0x8000000UL)  /*!< LER (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST7_ETR_Pos        (28UL)         /*!< ETR (Bit 28)                                          */
 #define R_MIPI_CSI_VCST7_ETR_Msk        (0x10000000UL) /*!< ETR (Bitfield-Mask: 0x01)                             */
/* =========================================================  VCST8  ========================================================= */
 #define R_MIPI_CSI_VCST8_MLF_Pos        (0UL)          /*!< MLF (Bit 0)                                           */
 #define R_MIPI_CSI_VCST8_MLF_Msk        (0x1UL)        /*!< MLF (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST8_ECD_Pos        (1UL)          /*!< ECD (Bit 1)                                           */
 #define R_MIPI_CSI_VCST8_ECD_Msk        (0x2UL)        /*!< ECD (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST8_CRC_Pos        (2UL)          /*!< CRC (Bit 2)                                           */
 #define R_MIPI_CSI_VCST8_CRC_Msk        (0x4UL)        /*!< CRC (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST8_IDE_Pos        (3UL)          /*!< IDE (Bit 3)                                           */
 #define R_MIPI_CSI_VCST8_IDE_Msk        (0x8UL)        /*!< IDE (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST8_WCE_Pos        (4UL)          /*!< WCE (Bit 4)                                           */
 #define R_MIPI_CSI_VCST8_WCE_Msk        (0x10UL)       /*!< WCE (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST8_ECC_Pos        (5UL)          /*!< ECC (Bit 5)                                           */
 #define R_MIPI_CSI_VCST8_ECC_Msk        (0x20UL)       /*!< ECC (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST8_ECN_Pos        (6UL)          /*!< ECN (Bit 6)                                           */
 #define R_MIPI_CSI_VCST8_ECN_Msk        (0x40UL)       /*!< ECN (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST8_FRS_Pos        (8UL)          /*!< FRS (Bit 8)                                           */
 #define R_MIPI_CSI_VCST8_FRS_Msk        (0x100UL)      /*!< FRS (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST8_FRD_Pos        (9UL)          /*!< FRD (Bit 9)                                           */
 #define R_MIPI_CSI_VCST8_FRD_Msk        (0x200UL)      /*!< FRD (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST8_OVF_Pos        (16UL)         /*!< OVF (Bit 16)                                          */
 #define R_MIPI_CSI_VCST8_OVF_Msk        (0x10000UL)    /*!< OVF (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST8_FSR_Pos        (24UL)         /*!< FSR (Bit 24)                                          */
 #define R_MIPI_CSI_VCST8_FSR_Msk        (0x1000000UL)  /*!< FSR (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST8_FER_Pos        (25UL)         /*!< FER (Bit 25)                                          */
 #define R_MIPI_CSI_VCST8_FER_Msk        (0x2000000UL)  /*!< FER (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST8_LSR_Pos        (26UL)         /*!< LSR (Bit 26)                                          */
 #define R_MIPI_CSI_VCST8_LSR_Msk        (0x4000000UL)  /*!< LSR (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST8_LER_Pos        (27UL)         /*!< LER (Bit 27)                                          */
 #define R_MIPI_CSI_VCST8_LER_Msk        (0x8000000UL)  /*!< LER (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST8_ETR_Pos        (28UL)         /*!< ETR (Bit 28)                                          */
 #define R_MIPI_CSI_VCST8_ETR_Msk        (0x10000000UL) /*!< ETR (Bitfield-Mask: 0x01)                             */
/* =========================================================  VCST9  ========================================================= */
 #define R_MIPI_CSI_VCST9_MLF_Pos        (0UL)          /*!< MLF (Bit 0)                                           */
 #define R_MIPI_CSI_VCST9_MLF_Msk        (0x1UL)        /*!< MLF (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST9_ECD_Pos        (1UL)          /*!< ECD (Bit 1)                                           */
 #define R_MIPI_CSI_VCST9_ECD_Msk        (0x2UL)        /*!< ECD (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST9_CRC_Pos        (2UL)          /*!< CRC (Bit 2)                                           */
 #define R_MIPI_CSI_VCST9_CRC_Msk        (0x4UL)        /*!< CRC (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST9_IDE_Pos        (3UL)          /*!< IDE (Bit 3)                                           */
 #define R_MIPI_CSI_VCST9_IDE_Msk        (0x8UL)        /*!< IDE (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST9_WCE_Pos        (4UL)          /*!< WCE (Bit 4)                                           */
 #define R_MIPI_CSI_VCST9_WCE_Msk        (0x10UL)       /*!< WCE (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST9_ECC_Pos        (5UL)          /*!< ECC (Bit 5)                                           */
 #define R_MIPI_CSI_VCST9_ECC_Msk        (0x20UL)       /*!< ECC (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST9_ECN_Pos        (6UL)          /*!< ECN (Bit 6)                                           */
 #define R_MIPI_CSI_VCST9_ECN_Msk        (0x40UL)       /*!< ECN (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST9_FRS_Pos        (8UL)          /*!< FRS (Bit 8)                                           */
 #define R_MIPI_CSI_VCST9_FRS_Msk        (0x100UL)      /*!< FRS (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST9_FRD_Pos        (9UL)          /*!< FRD (Bit 9)                                           */
 #define R_MIPI_CSI_VCST9_FRD_Msk        (0x200UL)      /*!< FRD (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST9_OVF_Pos        (16UL)         /*!< OVF (Bit 16)                                          */
 #define R_MIPI_CSI_VCST9_OVF_Msk        (0x10000UL)    /*!< OVF (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST9_FSR_Pos        (24UL)         /*!< FSR (Bit 24)                                          */
 #define R_MIPI_CSI_VCST9_FSR_Msk        (0x1000000UL)  /*!< FSR (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST9_FER_Pos        (25UL)         /*!< FER (Bit 25)                                          */
 #define R_MIPI_CSI_VCST9_FER_Msk        (0x2000000UL)  /*!< FER (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST9_LSR_Pos        (26UL)         /*!< LSR (Bit 26)                                          */
 #define R_MIPI_CSI_VCST9_LSR_Msk        (0x4000000UL)  /*!< LSR (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST9_LER_Pos        (27UL)         /*!< LER (Bit 27)                                          */
 #define R_MIPI_CSI_VCST9_LER_Msk        (0x8000000UL)  /*!< LER (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST9_ETR_Pos        (28UL)         /*!< ETR (Bit 28)                                          */
 #define R_MIPI_CSI_VCST9_ETR_Msk        (0x10000000UL) /*!< ETR (Bitfield-Mask: 0x01)                             */
/* ========================================================  VCST10  ========================================================= */
 #define R_MIPI_CSI_VCST10_MLF_Pos       (0UL)          /*!< MLF (Bit 0)                                           */
 #define R_MIPI_CSI_VCST10_MLF_Msk       (0x1UL)        /*!< MLF (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST10_ECD_Pos       (1UL)          /*!< ECD (Bit 1)                                           */
 #define R_MIPI_CSI_VCST10_ECD_Msk       (0x2UL)        /*!< ECD (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST10_CRC_Pos       (2UL)          /*!< CRC (Bit 2)                                           */
 #define R_MIPI_CSI_VCST10_CRC_Msk       (0x4UL)        /*!< CRC (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST10_IDE_Pos       (3UL)          /*!< IDE (Bit 3)                                           */
 #define R_MIPI_CSI_VCST10_IDE_Msk       (0x8UL)        /*!< IDE (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST10_WCE_Pos       (4UL)          /*!< WCE (Bit 4)                                           */
 #define R_MIPI_CSI_VCST10_WCE_Msk       (0x10UL)       /*!< WCE (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST10_ECC_Pos       (5UL)          /*!< ECC (Bit 5)                                           */
 #define R_MIPI_CSI_VCST10_ECC_Msk       (0x20UL)       /*!< ECC (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST10_ECN_Pos       (6UL)          /*!< ECN (Bit 6)                                           */
 #define R_MIPI_CSI_VCST10_ECN_Msk       (0x40UL)       /*!< ECN (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST10_FRS_Pos       (8UL)          /*!< FRS (Bit 8)                                           */
 #define R_MIPI_CSI_VCST10_FRS_Msk       (0x100UL)      /*!< FRS (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST10_FRD_Pos       (9UL)          /*!< FRD (Bit 9)                                           */
 #define R_MIPI_CSI_VCST10_FRD_Msk       (0x200UL)      /*!< FRD (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST10_OVF_Pos       (16UL)         /*!< OVF (Bit 16)                                          */
 #define R_MIPI_CSI_VCST10_OVF_Msk       (0x10000UL)    /*!< OVF (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST10_FSR_Pos       (24UL)         /*!< FSR (Bit 24)                                          */
 #define R_MIPI_CSI_VCST10_FSR_Msk       (0x1000000UL)  /*!< FSR (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST10_FER_Pos       (25UL)         /*!< FER (Bit 25)                                          */
 #define R_MIPI_CSI_VCST10_FER_Msk       (0x2000000UL)  /*!< FER (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST10_LSR_Pos       (26UL)         /*!< LSR (Bit 26)                                          */
 #define R_MIPI_CSI_VCST10_LSR_Msk       (0x4000000UL)  /*!< LSR (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST10_LER_Pos       (27UL)         /*!< LER (Bit 27)                                          */
 #define R_MIPI_CSI_VCST10_LER_Msk       (0x8000000UL)  /*!< LER (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST10_ETR_Pos       (28UL)         /*!< ETR (Bit 28)                                          */
 #define R_MIPI_CSI_VCST10_ETR_Msk       (0x10000000UL) /*!< ETR (Bitfield-Mask: 0x01)                             */
/* ========================================================  VCST11  ========================================================= */
 #define R_MIPI_CSI_VCST11_MLF_Pos       (0UL)          /*!< MLF (Bit 0)                                           */
 #define R_MIPI_CSI_VCST11_MLF_Msk       (0x1UL)        /*!< MLF (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST11_ECD_Pos       (1UL)          /*!< ECD (Bit 1)                                           */
 #define R_MIPI_CSI_VCST11_ECD_Msk       (0x2UL)        /*!< ECD (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST11_CRC_Pos       (2UL)          /*!< CRC (Bit 2)                                           */
 #define R_MIPI_CSI_VCST11_CRC_Msk       (0x4UL)        /*!< CRC (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST11_IDE_Pos       (3UL)          /*!< IDE (Bit 3)                                           */
 #define R_MIPI_CSI_VCST11_IDE_Msk       (0x8UL)        /*!< IDE (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST11_WCE_Pos       (4UL)          /*!< WCE (Bit 4)                                           */
 #define R_MIPI_CSI_VCST11_WCE_Msk       (0x10UL)       /*!< WCE (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST11_ECC_Pos       (5UL)          /*!< ECC (Bit 5)                                           */
 #define R_MIPI_CSI_VCST11_ECC_Msk       (0x20UL)       /*!< ECC (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST11_ECN_Pos       (6UL)          /*!< ECN (Bit 6)                                           */
 #define R_MIPI_CSI_VCST11_ECN_Msk       (0x40UL)       /*!< ECN (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST11_FRS_Pos       (8UL)          /*!< FRS (Bit 8)                                           */
 #define R_MIPI_CSI_VCST11_FRS_Msk       (0x100UL)      /*!< FRS (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST11_FRD_Pos       (9UL)          /*!< FRD (Bit 9)                                           */
 #define R_MIPI_CSI_VCST11_FRD_Msk       (0x200UL)      /*!< FRD (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST11_OVF_Pos       (16UL)         /*!< OVF (Bit 16)                                          */
 #define R_MIPI_CSI_VCST11_OVF_Msk       (0x10000UL)    /*!< OVF (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST11_FSR_Pos       (24UL)         /*!< FSR (Bit 24)                                          */
 #define R_MIPI_CSI_VCST11_FSR_Msk       (0x1000000UL)  /*!< FSR (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST11_FER_Pos       (25UL)         /*!< FER (Bit 25)                                          */
 #define R_MIPI_CSI_VCST11_FER_Msk       (0x2000000UL)  /*!< FER (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST11_LSR_Pos       (26UL)         /*!< LSR (Bit 26)                                          */
 #define R_MIPI_CSI_VCST11_LSR_Msk       (0x4000000UL)  /*!< LSR (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST11_LER_Pos       (27UL)         /*!< LER (Bit 27)                                          */
 #define R_MIPI_CSI_VCST11_LER_Msk       (0x8000000UL)  /*!< LER (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST11_ETR_Pos       (28UL)         /*!< ETR (Bit 28)                                          */
 #define R_MIPI_CSI_VCST11_ETR_Msk       (0x10000000UL) /*!< ETR (Bitfield-Mask: 0x01)                             */
/* ========================================================  VCST12  ========================================================= */
 #define R_MIPI_CSI_VCST12_MLF_Pos       (0UL)          /*!< MLF (Bit 0)                                           */
 #define R_MIPI_CSI_VCST12_MLF_Msk       (0x1UL)        /*!< MLF (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST12_ECD_Pos       (1UL)          /*!< ECD (Bit 1)                                           */
 #define R_MIPI_CSI_VCST12_ECD_Msk       (0x2UL)        /*!< ECD (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST12_CRC_Pos       (2UL)          /*!< CRC (Bit 2)                                           */
 #define R_MIPI_CSI_VCST12_CRC_Msk       (0x4UL)        /*!< CRC (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST12_IDE_Pos       (3UL)          /*!< IDE (Bit 3)                                           */
 #define R_MIPI_CSI_VCST12_IDE_Msk       (0x8UL)        /*!< IDE (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST12_WCE_Pos       (4UL)          /*!< WCE (Bit 4)                                           */
 #define R_MIPI_CSI_VCST12_WCE_Msk       (0x10UL)       /*!< WCE (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST12_ECC_Pos       (5UL)          /*!< ECC (Bit 5)                                           */
 #define R_MIPI_CSI_VCST12_ECC_Msk       (0x20UL)       /*!< ECC (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST12_ECN_Pos       (6UL)          /*!< ECN (Bit 6)                                           */
 #define R_MIPI_CSI_VCST12_ECN_Msk       (0x40UL)       /*!< ECN (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST12_FRS_Pos       (8UL)          /*!< FRS (Bit 8)                                           */
 #define R_MIPI_CSI_VCST12_FRS_Msk       (0x100UL)      /*!< FRS (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST12_FRD_Pos       (9UL)          /*!< FRD (Bit 9)                                           */
 #define R_MIPI_CSI_VCST12_FRD_Msk       (0x200UL)      /*!< FRD (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST12_OVF_Pos       (16UL)         /*!< OVF (Bit 16)                                          */
 #define R_MIPI_CSI_VCST12_OVF_Msk       (0x10000UL)    /*!< OVF (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST12_FSR_Pos       (24UL)         /*!< FSR (Bit 24)                                          */
 #define R_MIPI_CSI_VCST12_FSR_Msk       (0x1000000UL)  /*!< FSR (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST12_FER_Pos       (25UL)         /*!< FER (Bit 25)                                          */
 #define R_MIPI_CSI_VCST12_FER_Msk       (0x2000000UL)  /*!< FER (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST12_LSR_Pos       (26UL)         /*!< LSR (Bit 26)                                          */
 #define R_MIPI_CSI_VCST12_LSR_Msk       (0x4000000UL)  /*!< LSR (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST12_LER_Pos       (27UL)         /*!< LER (Bit 27)                                          */
 #define R_MIPI_CSI_VCST12_LER_Msk       (0x8000000UL)  /*!< LER (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST12_ETR_Pos       (28UL)         /*!< ETR (Bit 28)                                          */
 #define R_MIPI_CSI_VCST12_ETR_Msk       (0x10000000UL) /*!< ETR (Bitfield-Mask: 0x01)                             */
/* ========================================================  VCST13  ========================================================= */
 #define R_MIPI_CSI_VCST13_MLF_Pos       (0UL)          /*!< MLF (Bit 0)                                           */
 #define R_MIPI_CSI_VCST13_MLF_Msk       (0x1UL)        /*!< MLF (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST13_ECD_Pos       (1UL)          /*!< ECD (Bit 1)                                           */
 #define R_MIPI_CSI_VCST13_ECD_Msk       (0x2UL)        /*!< ECD (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST13_CRC_Pos       (2UL)          /*!< CRC (Bit 2)                                           */
 #define R_MIPI_CSI_VCST13_CRC_Msk       (0x4UL)        /*!< CRC (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST13_IDE_Pos       (3UL)          /*!< IDE (Bit 3)                                           */
 #define R_MIPI_CSI_VCST13_IDE_Msk       (0x8UL)        /*!< IDE (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST13_WCE_Pos       (4UL)          /*!< WCE (Bit 4)                                           */
 #define R_MIPI_CSI_VCST13_WCE_Msk       (0x10UL)       /*!< WCE (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST13_ECC_Pos       (5UL)          /*!< ECC (Bit 5)                                           */
 #define R_MIPI_CSI_VCST13_ECC_Msk       (0x20UL)       /*!< ECC (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST13_ECN_Pos       (6UL)          /*!< ECN (Bit 6)                                           */
 #define R_MIPI_CSI_VCST13_ECN_Msk       (0x40UL)       /*!< ECN (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST13_FRS_Pos       (8UL)          /*!< FRS (Bit 8)                                           */
 #define R_MIPI_CSI_VCST13_FRS_Msk       (0x100UL)      /*!< FRS (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST13_FRD_Pos       (9UL)          /*!< FRD (Bit 9)                                           */
 #define R_MIPI_CSI_VCST13_FRD_Msk       (0x200UL)      /*!< FRD (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST13_OVF_Pos       (16UL)         /*!< OVF (Bit 16)                                          */
 #define R_MIPI_CSI_VCST13_OVF_Msk       (0x10000UL)    /*!< OVF (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST13_FSR_Pos       (24UL)         /*!< FSR (Bit 24)                                          */
 #define R_MIPI_CSI_VCST13_FSR_Msk       (0x1000000UL)  /*!< FSR (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST13_FER_Pos       (25UL)         /*!< FER (Bit 25)                                          */
 #define R_MIPI_CSI_VCST13_FER_Msk       (0x2000000UL)  /*!< FER (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST13_LSR_Pos       (26UL)         /*!< LSR (Bit 26)                                          */
 #define R_MIPI_CSI_VCST13_LSR_Msk       (0x4000000UL)  /*!< LSR (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST13_LER_Pos       (27UL)         /*!< LER (Bit 27)                                          */
 #define R_MIPI_CSI_VCST13_LER_Msk       (0x8000000UL)  /*!< LER (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST13_ETR_Pos       (28UL)         /*!< ETR (Bit 28)                                          */
 #define R_MIPI_CSI_VCST13_ETR_Msk       (0x10000000UL) /*!< ETR (Bitfield-Mask: 0x01)                             */
/* ========================================================  VCST14  ========================================================= */
 #define R_MIPI_CSI_VCST14_MLF_Pos       (0UL)          /*!< MLF (Bit 0)                                           */
 #define R_MIPI_CSI_VCST14_MLF_Msk       (0x1UL)        /*!< MLF (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST14_ECD_Pos       (1UL)          /*!< ECD (Bit 1)                                           */
 #define R_MIPI_CSI_VCST14_ECD_Msk       (0x2UL)        /*!< ECD (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST14_CRC_Pos       (2UL)          /*!< CRC (Bit 2)                                           */
 #define R_MIPI_CSI_VCST14_CRC_Msk       (0x4UL)        /*!< CRC (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST14_IDE_Pos       (3UL)          /*!< IDE (Bit 3)                                           */
 #define R_MIPI_CSI_VCST14_IDE_Msk       (0x8UL)        /*!< IDE (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST14_WCE_Pos       (4UL)          /*!< WCE (Bit 4)                                           */
 #define R_MIPI_CSI_VCST14_WCE_Msk       (0x10UL)       /*!< WCE (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST14_ECC_Pos       (5UL)          /*!< ECC (Bit 5)                                           */
 #define R_MIPI_CSI_VCST14_ECC_Msk       (0x20UL)       /*!< ECC (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST14_ECN_Pos       (6UL)          /*!< ECN (Bit 6)                                           */
 #define R_MIPI_CSI_VCST14_ECN_Msk       (0x40UL)       /*!< ECN (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST14_FRS_Pos       (8UL)          /*!< FRS (Bit 8)                                           */
 #define R_MIPI_CSI_VCST14_FRS_Msk       (0x100UL)      /*!< FRS (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST14_FRD_Pos       (9UL)          /*!< FRD (Bit 9)                                           */
 #define R_MIPI_CSI_VCST14_FRD_Msk       (0x200UL)      /*!< FRD (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST14_OVF_Pos       (16UL)         /*!< OVF (Bit 16)                                          */
 #define R_MIPI_CSI_VCST14_OVF_Msk       (0x10000UL)    /*!< OVF (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST14_FSR_Pos       (24UL)         /*!< FSR (Bit 24)                                          */
 #define R_MIPI_CSI_VCST14_FSR_Msk       (0x1000000UL)  /*!< FSR (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST14_FER_Pos       (25UL)         /*!< FER (Bit 25)                                          */
 #define R_MIPI_CSI_VCST14_FER_Msk       (0x2000000UL)  /*!< FER (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST14_LSR_Pos       (26UL)         /*!< LSR (Bit 26)                                          */
 #define R_MIPI_CSI_VCST14_LSR_Msk       (0x4000000UL)  /*!< LSR (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST14_LER_Pos       (27UL)         /*!< LER (Bit 27)                                          */
 #define R_MIPI_CSI_VCST14_LER_Msk       (0x8000000UL)  /*!< LER (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST14_ETR_Pos       (28UL)         /*!< ETR (Bit 28)                                          */
 #define R_MIPI_CSI_VCST14_ETR_Msk       (0x10000000UL) /*!< ETR (Bitfield-Mask: 0x01)                             */
/* ========================================================  VCST15  ========================================================= */
 #define R_MIPI_CSI_VCST15_MLF_Pos       (0UL)          /*!< MLF (Bit 0)                                           */
 #define R_MIPI_CSI_VCST15_MLF_Msk       (0x1UL)        /*!< MLF (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST15_ECD_Pos       (1UL)          /*!< ECD (Bit 1)                                           */
 #define R_MIPI_CSI_VCST15_ECD_Msk       (0x2UL)        /*!< ECD (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST15_CRC_Pos       (2UL)          /*!< CRC (Bit 2)                                           */
 #define R_MIPI_CSI_VCST15_CRC_Msk       (0x4UL)        /*!< CRC (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST15_IDE_Pos       (3UL)          /*!< IDE (Bit 3)                                           */
 #define R_MIPI_CSI_VCST15_IDE_Msk       (0x8UL)        /*!< IDE (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST15_WCE_Pos       (4UL)          /*!< WCE (Bit 4)                                           */
 #define R_MIPI_CSI_VCST15_WCE_Msk       (0x10UL)       /*!< WCE (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST15_ECC_Pos       (5UL)          /*!< ECC (Bit 5)                                           */
 #define R_MIPI_CSI_VCST15_ECC_Msk       (0x20UL)       /*!< ECC (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST15_ECN_Pos       (6UL)          /*!< ECN (Bit 6)                                           */
 #define R_MIPI_CSI_VCST15_ECN_Msk       (0x40UL)       /*!< ECN (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST15_FRS_Pos       (8UL)          /*!< FRS (Bit 8)                                           */
 #define R_MIPI_CSI_VCST15_FRS_Msk       (0x100UL)      /*!< FRS (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST15_FRD_Pos       (9UL)          /*!< FRD (Bit 9)                                           */
 #define R_MIPI_CSI_VCST15_FRD_Msk       (0x200UL)      /*!< FRD (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST15_OVF_Pos       (16UL)         /*!< OVF (Bit 16)                                          */
 #define R_MIPI_CSI_VCST15_OVF_Msk       (0x10000UL)    /*!< OVF (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST15_FSR_Pos       (24UL)         /*!< FSR (Bit 24)                                          */
 #define R_MIPI_CSI_VCST15_FSR_Msk       (0x1000000UL)  /*!< FSR (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST15_FER_Pos       (25UL)         /*!< FER (Bit 25)                                          */
 #define R_MIPI_CSI_VCST15_FER_Msk       (0x2000000UL)  /*!< FER (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST15_LSR_Pos       (26UL)         /*!< LSR (Bit 26)                                          */
 #define R_MIPI_CSI_VCST15_LSR_Msk       (0x4000000UL)  /*!< LSR (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST15_LER_Pos       (27UL)         /*!< LER (Bit 27)                                          */
 #define R_MIPI_CSI_VCST15_LER_Msk       (0x8000000UL)  /*!< LER (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_VCST15_ETR_Pos       (28UL)         /*!< ETR (Bit 28)                                          */
 #define R_MIPI_CSI_VCST15_ETR_Msk       (0x10000000UL) /*!< ETR (Bitfield-Mask: 0x01)                             */
/* =========================================================  VCSC0  ========================================================= */
 #define R_MIPI_CSI_VCSC0_MLFC_Pos       (0UL)          /*!< MLFC (Bit 0)                                          */
 #define R_MIPI_CSI_VCSC0_MLFC_Msk       (0x1UL)        /*!< MLFC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC0_ECDC_Pos       (1UL)          /*!< ECDC (Bit 1)                                          */
 #define R_MIPI_CSI_VCSC0_ECDC_Msk       (0x2UL)        /*!< ECDC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC0_CRCC_Pos       (2UL)          /*!< CRCC (Bit 2)                                          */
 #define R_MIPI_CSI_VCSC0_CRCC_Msk       (0x4UL)        /*!< CRCC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC0_IDEC_Pos       (3UL)          /*!< IDEC (Bit 3)                                          */
 #define R_MIPI_CSI_VCSC0_IDEC_Msk       (0x8UL)        /*!< IDEC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC0_WCEC_Pos       (4UL)          /*!< WCEC (Bit 4)                                          */
 #define R_MIPI_CSI_VCSC0_WCEC_Msk       (0x10UL)       /*!< WCEC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC0_ECCC_Pos       (5UL)          /*!< ECCC (Bit 5)                                          */
 #define R_MIPI_CSI_VCSC0_ECCC_Msk       (0x20UL)       /*!< ECCC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC0_ECNC_Pos       (6UL)          /*!< ECNC (Bit 6)                                          */
 #define R_MIPI_CSI_VCSC0_ECNC_Msk       (0x40UL)       /*!< ECNC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC0_FRSC_Pos       (8UL)          /*!< FRSC (Bit 8)                                          */
 #define R_MIPI_CSI_VCSC0_FRSC_Msk       (0x100UL)      /*!< FRSC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC0_FRDC_Pos       (9UL)          /*!< FRDC (Bit 9)                                          */
 #define R_MIPI_CSI_VCSC0_FRDC_Msk       (0x200UL)      /*!< FRDC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC0_AMLFC_Pos      (14UL)         /*!< AMLFC (Bit 14)                                        */
 #define R_MIPI_CSI_VCSC0_AMLFC_Msk      (0x4000UL)     /*!< AMLFC (Bitfield-Mask: 0x01)                           */
 #define R_MIPI_CSI_VCSC0_AECDC_Pos      (15UL)         /*!< AECDC (Bit 15)                                        */
 #define R_MIPI_CSI_VCSC0_AECDC_Msk      (0x8000UL)     /*!< AECDC (Bitfield-Mask: 0x01)                           */
 #define R_MIPI_CSI_VCSC0_OVFC_Pos       (16UL)         /*!< OVFC (Bit 16)                                         */
 #define R_MIPI_CSI_VCSC0_OVFC_Msk       (0x10000UL)    /*!< OVFC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC0_FSRC_Pos       (24UL)         /*!< FSRC (Bit 24)                                         */
 #define R_MIPI_CSI_VCSC0_FSRC_Msk       (0x1000000UL)  /*!< FSRC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC0_FERC_Pos       (25UL)         /*!< FERC (Bit 25)                                         */
 #define R_MIPI_CSI_VCSC0_FERC_Msk       (0x2000000UL)  /*!< FERC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC0_LSRC_Pos       (26UL)         /*!< LSRC (Bit 26)                                         */
 #define R_MIPI_CSI_VCSC0_LSRC_Msk       (0x4000000UL)  /*!< LSRC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC0_LERC_Pos       (27UL)         /*!< LERC (Bit 27)                                         */
 #define R_MIPI_CSI_VCSC0_LERC_Msk       (0x8000000UL)  /*!< LERC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC0_ETRC_Pos       (28UL)         /*!< ETRC (Bit 28)                                         */
 #define R_MIPI_CSI_VCSC0_ETRC_Msk       (0x10000000UL) /*!< ETRC (Bitfield-Mask: 0x01)                            */
/* =========================================================  VCSC1  ========================================================= */
 #define R_MIPI_CSI_VCSC1_MLFC_Pos       (0UL)          /*!< MLFC (Bit 0)                                          */
 #define R_MIPI_CSI_VCSC1_MLFC_Msk       (0x1UL)        /*!< MLFC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC1_ECDC_Pos       (1UL)          /*!< ECDC (Bit 1)                                          */
 #define R_MIPI_CSI_VCSC1_ECDC_Msk       (0x2UL)        /*!< ECDC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC1_CRCC_Pos       (2UL)          /*!< CRCC (Bit 2)                                          */
 #define R_MIPI_CSI_VCSC1_CRCC_Msk       (0x4UL)        /*!< CRCC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC1_IDEC_Pos       (3UL)          /*!< IDEC (Bit 3)                                          */
 #define R_MIPI_CSI_VCSC1_IDEC_Msk       (0x8UL)        /*!< IDEC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC1_WCEC_Pos       (4UL)          /*!< WCEC (Bit 4)                                          */
 #define R_MIPI_CSI_VCSC1_WCEC_Msk       (0x10UL)       /*!< WCEC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC1_ECCC_Pos       (5UL)          /*!< ECCC (Bit 5)                                          */
 #define R_MIPI_CSI_VCSC1_ECCC_Msk       (0x20UL)       /*!< ECCC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC1_ECNC_Pos       (6UL)          /*!< ECNC (Bit 6)                                          */
 #define R_MIPI_CSI_VCSC1_ECNC_Msk       (0x40UL)       /*!< ECNC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC1_FRSC_Pos       (8UL)          /*!< FRSC (Bit 8)                                          */
 #define R_MIPI_CSI_VCSC1_FRSC_Msk       (0x100UL)      /*!< FRSC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC1_FRDC_Pos       (9UL)          /*!< FRDC (Bit 9)                                          */
 #define R_MIPI_CSI_VCSC1_FRDC_Msk       (0x200UL)      /*!< FRDC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC1_AMLFC_Pos      (14UL)         /*!< AMLFC (Bit 14)                                        */
 #define R_MIPI_CSI_VCSC1_AMLFC_Msk      (0x4000UL)     /*!< AMLFC (Bitfield-Mask: 0x01)                           */
 #define R_MIPI_CSI_VCSC1_AECDC_Pos      (15UL)         /*!< AECDC (Bit 15)                                        */
 #define R_MIPI_CSI_VCSC1_AECDC_Msk      (0x8000UL)     /*!< AECDC (Bitfield-Mask: 0x01)                           */
 #define R_MIPI_CSI_VCSC1_OVFC_Pos       (16UL)         /*!< OVFC (Bit 16)                                         */
 #define R_MIPI_CSI_VCSC1_OVFC_Msk       (0x10000UL)    /*!< OVFC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC1_FSRC_Pos       (24UL)         /*!< FSRC (Bit 24)                                         */
 #define R_MIPI_CSI_VCSC1_FSRC_Msk       (0x1000000UL)  /*!< FSRC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC1_FERC_Pos       (25UL)         /*!< FERC (Bit 25)                                         */
 #define R_MIPI_CSI_VCSC1_FERC_Msk       (0x2000000UL)  /*!< FERC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC1_LSRC_Pos       (26UL)         /*!< LSRC (Bit 26)                                         */
 #define R_MIPI_CSI_VCSC1_LSRC_Msk       (0x4000000UL)  /*!< LSRC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC1_LERC_Pos       (27UL)         /*!< LERC (Bit 27)                                         */
 #define R_MIPI_CSI_VCSC1_LERC_Msk       (0x8000000UL)  /*!< LERC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC1_ETRC_Pos       (28UL)         /*!< ETRC (Bit 28)                                         */
 #define R_MIPI_CSI_VCSC1_ETRC_Msk       (0x10000000UL) /*!< ETRC (Bitfield-Mask: 0x01)                            */
/* =========================================================  VCSC2  ========================================================= */
 #define R_MIPI_CSI_VCSC2_MLFC_Pos       (0UL)          /*!< MLFC (Bit 0)                                          */
 #define R_MIPI_CSI_VCSC2_MLFC_Msk       (0x1UL)        /*!< MLFC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC2_ECDC_Pos       (1UL)          /*!< ECDC (Bit 1)                                          */
 #define R_MIPI_CSI_VCSC2_ECDC_Msk       (0x2UL)        /*!< ECDC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC2_CRCC_Pos       (2UL)          /*!< CRCC (Bit 2)                                          */
 #define R_MIPI_CSI_VCSC2_CRCC_Msk       (0x4UL)        /*!< CRCC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC2_IDEC_Pos       (3UL)          /*!< IDEC (Bit 3)                                          */
 #define R_MIPI_CSI_VCSC2_IDEC_Msk       (0x8UL)        /*!< IDEC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC2_WCEC_Pos       (4UL)          /*!< WCEC (Bit 4)                                          */
 #define R_MIPI_CSI_VCSC2_WCEC_Msk       (0x10UL)       /*!< WCEC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC2_ECCC_Pos       (5UL)          /*!< ECCC (Bit 5)                                          */
 #define R_MIPI_CSI_VCSC2_ECCC_Msk       (0x20UL)       /*!< ECCC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC2_ECNC_Pos       (6UL)          /*!< ECNC (Bit 6)                                          */
 #define R_MIPI_CSI_VCSC2_ECNC_Msk       (0x40UL)       /*!< ECNC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC2_FRSC_Pos       (8UL)          /*!< FRSC (Bit 8)                                          */
 #define R_MIPI_CSI_VCSC2_FRSC_Msk       (0x100UL)      /*!< FRSC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC2_FRDC_Pos       (9UL)          /*!< FRDC (Bit 9)                                          */
 #define R_MIPI_CSI_VCSC2_FRDC_Msk       (0x200UL)      /*!< FRDC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC2_AMLFC_Pos      (14UL)         /*!< AMLFC (Bit 14)                                        */
 #define R_MIPI_CSI_VCSC2_AMLFC_Msk      (0x4000UL)     /*!< AMLFC (Bitfield-Mask: 0x01)                           */
 #define R_MIPI_CSI_VCSC2_AECDC_Pos      (15UL)         /*!< AECDC (Bit 15)                                        */
 #define R_MIPI_CSI_VCSC2_AECDC_Msk      (0x8000UL)     /*!< AECDC (Bitfield-Mask: 0x01)                           */
 #define R_MIPI_CSI_VCSC2_OVFC_Pos       (16UL)         /*!< OVFC (Bit 16)                                         */
 #define R_MIPI_CSI_VCSC2_OVFC_Msk       (0x10000UL)    /*!< OVFC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC2_FSRC_Pos       (24UL)         /*!< FSRC (Bit 24)                                         */
 #define R_MIPI_CSI_VCSC2_FSRC_Msk       (0x1000000UL)  /*!< FSRC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC2_FERC_Pos       (25UL)         /*!< FERC (Bit 25)                                         */
 #define R_MIPI_CSI_VCSC2_FERC_Msk       (0x2000000UL)  /*!< FERC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC2_LSRC_Pos       (26UL)         /*!< LSRC (Bit 26)                                         */
 #define R_MIPI_CSI_VCSC2_LSRC_Msk       (0x4000000UL)  /*!< LSRC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC2_LERC_Pos       (27UL)         /*!< LERC (Bit 27)                                         */
 #define R_MIPI_CSI_VCSC2_LERC_Msk       (0x8000000UL)  /*!< LERC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC2_ETRC_Pos       (28UL)         /*!< ETRC (Bit 28)                                         */
 #define R_MIPI_CSI_VCSC2_ETRC_Msk       (0x10000000UL) /*!< ETRC (Bitfield-Mask: 0x01)                            */
/* =========================================================  VCSC3  ========================================================= */
 #define R_MIPI_CSI_VCSC3_MLFC_Pos       (0UL)          /*!< MLFC (Bit 0)                                          */
 #define R_MIPI_CSI_VCSC3_MLFC_Msk       (0x1UL)        /*!< MLFC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC3_ECDC_Pos       (1UL)          /*!< ECDC (Bit 1)                                          */
 #define R_MIPI_CSI_VCSC3_ECDC_Msk       (0x2UL)        /*!< ECDC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC3_CRCC_Pos       (2UL)          /*!< CRCC (Bit 2)                                          */
 #define R_MIPI_CSI_VCSC3_CRCC_Msk       (0x4UL)        /*!< CRCC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC3_IDEC_Pos       (3UL)          /*!< IDEC (Bit 3)                                          */
 #define R_MIPI_CSI_VCSC3_IDEC_Msk       (0x8UL)        /*!< IDEC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC3_WCEC_Pos       (4UL)          /*!< WCEC (Bit 4)                                          */
 #define R_MIPI_CSI_VCSC3_WCEC_Msk       (0x10UL)       /*!< WCEC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC3_ECCC_Pos       (5UL)          /*!< ECCC (Bit 5)                                          */
 #define R_MIPI_CSI_VCSC3_ECCC_Msk       (0x20UL)       /*!< ECCC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC3_ECNC_Pos       (6UL)          /*!< ECNC (Bit 6)                                          */
 #define R_MIPI_CSI_VCSC3_ECNC_Msk       (0x40UL)       /*!< ECNC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC3_FRSC_Pos       (8UL)          /*!< FRSC (Bit 8)                                          */
 #define R_MIPI_CSI_VCSC3_FRSC_Msk       (0x100UL)      /*!< FRSC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC3_FRDC_Pos       (9UL)          /*!< FRDC (Bit 9)                                          */
 #define R_MIPI_CSI_VCSC3_FRDC_Msk       (0x200UL)      /*!< FRDC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC3_AMLFC_Pos      (14UL)         /*!< AMLFC (Bit 14)                                        */
 #define R_MIPI_CSI_VCSC3_AMLFC_Msk      (0x4000UL)     /*!< AMLFC (Bitfield-Mask: 0x01)                           */
 #define R_MIPI_CSI_VCSC3_AECDC_Pos      (15UL)         /*!< AECDC (Bit 15)                                        */
 #define R_MIPI_CSI_VCSC3_AECDC_Msk      (0x8000UL)     /*!< AECDC (Bitfield-Mask: 0x01)                           */
 #define R_MIPI_CSI_VCSC3_OVFC_Pos       (16UL)         /*!< OVFC (Bit 16)                                         */
 #define R_MIPI_CSI_VCSC3_OVFC_Msk       (0x10000UL)    /*!< OVFC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC3_FSRC_Pos       (24UL)         /*!< FSRC (Bit 24)                                         */
 #define R_MIPI_CSI_VCSC3_FSRC_Msk       (0x1000000UL)  /*!< FSRC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC3_FERC_Pos       (25UL)         /*!< FERC (Bit 25)                                         */
 #define R_MIPI_CSI_VCSC3_FERC_Msk       (0x2000000UL)  /*!< FERC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC3_LSRC_Pos       (26UL)         /*!< LSRC (Bit 26)                                         */
 #define R_MIPI_CSI_VCSC3_LSRC_Msk       (0x4000000UL)  /*!< LSRC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC3_LERC_Pos       (27UL)         /*!< LERC (Bit 27)                                         */
 #define R_MIPI_CSI_VCSC3_LERC_Msk       (0x8000000UL)  /*!< LERC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC3_ETRC_Pos       (28UL)         /*!< ETRC (Bit 28)                                         */
 #define R_MIPI_CSI_VCSC3_ETRC_Msk       (0x10000000UL) /*!< ETRC (Bitfield-Mask: 0x01)                            */
/* =========================================================  VCSC4  ========================================================= */
 #define R_MIPI_CSI_VCSC4_MLFC_Pos       (0UL)          /*!< MLFC (Bit 0)                                          */
 #define R_MIPI_CSI_VCSC4_MLFC_Msk       (0x1UL)        /*!< MLFC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC4_ECDC_Pos       (1UL)          /*!< ECDC (Bit 1)                                          */
 #define R_MIPI_CSI_VCSC4_ECDC_Msk       (0x2UL)        /*!< ECDC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC4_CRCC_Pos       (2UL)          /*!< CRCC (Bit 2)                                          */
 #define R_MIPI_CSI_VCSC4_CRCC_Msk       (0x4UL)        /*!< CRCC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC4_IDEC_Pos       (3UL)          /*!< IDEC (Bit 3)                                          */
 #define R_MIPI_CSI_VCSC4_IDEC_Msk       (0x8UL)        /*!< IDEC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC4_WCEC_Pos       (4UL)          /*!< WCEC (Bit 4)                                          */
 #define R_MIPI_CSI_VCSC4_WCEC_Msk       (0x10UL)       /*!< WCEC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC4_ECCC_Pos       (5UL)          /*!< ECCC (Bit 5)                                          */
 #define R_MIPI_CSI_VCSC4_ECCC_Msk       (0x20UL)       /*!< ECCC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC4_ECNC_Pos       (6UL)          /*!< ECNC (Bit 6)                                          */
 #define R_MIPI_CSI_VCSC4_ECNC_Msk       (0x40UL)       /*!< ECNC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC4_FRSC_Pos       (8UL)          /*!< FRSC (Bit 8)                                          */
 #define R_MIPI_CSI_VCSC4_FRSC_Msk       (0x100UL)      /*!< FRSC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC4_FRDC_Pos       (9UL)          /*!< FRDC (Bit 9)                                          */
 #define R_MIPI_CSI_VCSC4_FRDC_Msk       (0x200UL)      /*!< FRDC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC4_AMLFC_Pos      (14UL)         /*!< AMLFC (Bit 14)                                        */
 #define R_MIPI_CSI_VCSC4_AMLFC_Msk      (0x4000UL)     /*!< AMLFC (Bitfield-Mask: 0x01)                           */
 #define R_MIPI_CSI_VCSC4_AECDC_Pos      (15UL)         /*!< AECDC (Bit 15)                                        */
 #define R_MIPI_CSI_VCSC4_AECDC_Msk      (0x8000UL)     /*!< AECDC (Bitfield-Mask: 0x01)                           */
 #define R_MIPI_CSI_VCSC4_OVFC_Pos       (16UL)         /*!< OVFC (Bit 16)                                         */
 #define R_MIPI_CSI_VCSC4_OVFC_Msk       (0x10000UL)    /*!< OVFC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC4_FSRC_Pos       (24UL)         /*!< FSRC (Bit 24)                                         */
 #define R_MIPI_CSI_VCSC4_FSRC_Msk       (0x1000000UL)  /*!< FSRC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC4_FERC_Pos       (25UL)         /*!< FERC (Bit 25)                                         */
 #define R_MIPI_CSI_VCSC4_FERC_Msk       (0x2000000UL)  /*!< FERC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC4_LSRC_Pos       (26UL)         /*!< LSRC (Bit 26)                                         */
 #define R_MIPI_CSI_VCSC4_LSRC_Msk       (0x4000000UL)  /*!< LSRC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC4_LERC_Pos       (27UL)         /*!< LERC (Bit 27)                                         */
 #define R_MIPI_CSI_VCSC4_LERC_Msk       (0x8000000UL)  /*!< LERC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC4_ETRC_Pos       (28UL)         /*!< ETRC (Bit 28)                                         */
 #define R_MIPI_CSI_VCSC4_ETRC_Msk       (0x10000000UL) /*!< ETRC (Bitfield-Mask: 0x01)                            */
/* =========================================================  VCSC5  ========================================================= */
 #define R_MIPI_CSI_VCSC5_MLFC_Pos       (0UL)          /*!< MLFC (Bit 0)                                          */
 #define R_MIPI_CSI_VCSC5_MLFC_Msk       (0x1UL)        /*!< MLFC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC5_ECDC_Pos       (1UL)          /*!< ECDC (Bit 1)                                          */
 #define R_MIPI_CSI_VCSC5_ECDC_Msk       (0x2UL)        /*!< ECDC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC5_CRCC_Pos       (2UL)          /*!< CRCC (Bit 2)                                          */
 #define R_MIPI_CSI_VCSC5_CRCC_Msk       (0x4UL)        /*!< CRCC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC5_IDEC_Pos       (3UL)          /*!< IDEC (Bit 3)                                          */
 #define R_MIPI_CSI_VCSC5_IDEC_Msk       (0x8UL)        /*!< IDEC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC5_WCEC_Pos       (4UL)          /*!< WCEC (Bit 4)                                          */
 #define R_MIPI_CSI_VCSC5_WCEC_Msk       (0x10UL)       /*!< WCEC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC5_ECCC_Pos       (5UL)          /*!< ECCC (Bit 5)                                          */
 #define R_MIPI_CSI_VCSC5_ECCC_Msk       (0x20UL)       /*!< ECCC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC5_ECNC_Pos       (6UL)          /*!< ECNC (Bit 6)                                          */
 #define R_MIPI_CSI_VCSC5_ECNC_Msk       (0x40UL)       /*!< ECNC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC5_FRSC_Pos       (8UL)          /*!< FRSC (Bit 8)                                          */
 #define R_MIPI_CSI_VCSC5_FRSC_Msk       (0x100UL)      /*!< FRSC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC5_FRDC_Pos       (9UL)          /*!< FRDC (Bit 9)                                          */
 #define R_MIPI_CSI_VCSC5_FRDC_Msk       (0x200UL)      /*!< FRDC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC5_AMLFC_Pos      (14UL)         /*!< AMLFC (Bit 14)                                        */
 #define R_MIPI_CSI_VCSC5_AMLFC_Msk      (0x4000UL)     /*!< AMLFC (Bitfield-Mask: 0x01)                           */
 #define R_MIPI_CSI_VCSC5_AECDC_Pos      (15UL)         /*!< AECDC (Bit 15)                                        */
 #define R_MIPI_CSI_VCSC5_AECDC_Msk      (0x8000UL)     /*!< AECDC (Bitfield-Mask: 0x01)                           */
 #define R_MIPI_CSI_VCSC5_OVFC_Pos       (16UL)         /*!< OVFC (Bit 16)                                         */
 #define R_MIPI_CSI_VCSC5_OVFC_Msk       (0x10000UL)    /*!< OVFC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC5_FSRC_Pos       (24UL)         /*!< FSRC (Bit 24)                                         */
 #define R_MIPI_CSI_VCSC5_FSRC_Msk       (0x1000000UL)  /*!< FSRC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC5_FERC_Pos       (25UL)         /*!< FERC (Bit 25)                                         */
 #define R_MIPI_CSI_VCSC5_FERC_Msk       (0x2000000UL)  /*!< FERC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC5_LSRC_Pos       (26UL)         /*!< LSRC (Bit 26)                                         */
 #define R_MIPI_CSI_VCSC5_LSRC_Msk       (0x4000000UL)  /*!< LSRC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC5_LERC_Pos       (27UL)         /*!< LERC (Bit 27)                                         */
 #define R_MIPI_CSI_VCSC5_LERC_Msk       (0x8000000UL)  /*!< LERC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC5_ETRC_Pos       (28UL)         /*!< ETRC (Bit 28)                                         */
 #define R_MIPI_CSI_VCSC5_ETRC_Msk       (0x10000000UL) /*!< ETRC (Bitfield-Mask: 0x01)                            */
/* =========================================================  VCSC6  ========================================================= */
 #define R_MIPI_CSI_VCSC6_MLFC_Pos       (0UL)          /*!< MLFC (Bit 0)                                          */
 #define R_MIPI_CSI_VCSC6_MLFC_Msk       (0x1UL)        /*!< MLFC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC6_ECDC_Pos       (1UL)          /*!< ECDC (Bit 1)                                          */
 #define R_MIPI_CSI_VCSC6_ECDC_Msk       (0x2UL)        /*!< ECDC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC6_CRCC_Pos       (2UL)          /*!< CRCC (Bit 2)                                          */
 #define R_MIPI_CSI_VCSC6_CRCC_Msk       (0x4UL)        /*!< CRCC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC6_IDEC_Pos       (3UL)          /*!< IDEC (Bit 3)                                          */
 #define R_MIPI_CSI_VCSC6_IDEC_Msk       (0x8UL)        /*!< IDEC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC6_WCEC_Pos       (4UL)          /*!< WCEC (Bit 4)                                          */
 #define R_MIPI_CSI_VCSC6_WCEC_Msk       (0x10UL)       /*!< WCEC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC6_ECCC_Pos       (5UL)          /*!< ECCC (Bit 5)                                          */
 #define R_MIPI_CSI_VCSC6_ECCC_Msk       (0x20UL)       /*!< ECCC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC6_ECNC_Pos       (6UL)          /*!< ECNC (Bit 6)                                          */
 #define R_MIPI_CSI_VCSC6_ECNC_Msk       (0x40UL)       /*!< ECNC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC6_FRSC_Pos       (8UL)          /*!< FRSC (Bit 8)                                          */
 #define R_MIPI_CSI_VCSC6_FRSC_Msk       (0x100UL)      /*!< FRSC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC6_FRDC_Pos       (9UL)          /*!< FRDC (Bit 9)                                          */
 #define R_MIPI_CSI_VCSC6_FRDC_Msk       (0x200UL)      /*!< FRDC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC6_AMLFC_Pos      (14UL)         /*!< AMLFC (Bit 14)                                        */
 #define R_MIPI_CSI_VCSC6_AMLFC_Msk      (0x4000UL)     /*!< AMLFC (Bitfield-Mask: 0x01)                           */
 #define R_MIPI_CSI_VCSC6_AECDC_Pos      (15UL)         /*!< AECDC (Bit 15)                                        */
 #define R_MIPI_CSI_VCSC6_AECDC_Msk      (0x8000UL)     /*!< AECDC (Bitfield-Mask: 0x01)                           */
 #define R_MIPI_CSI_VCSC6_OVFC_Pos       (16UL)         /*!< OVFC (Bit 16)                                         */
 #define R_MIPI_CSI_VCSC6_OVFC_Msk       (0x10000UL)    /*!< OVFC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC6_FSRC_Pos       (24UL)         /*!< FSRC (Bit 24)                                         */
 #define R_MIPI_CSI_VCSC6_FSRC_Msk       (0x1000000UL)  /*!< FSRC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC6_FERC_Pos       (25UL)         /*!< FERC (Bit 25)                                         */
 #define R_MIPI_CSI_VCSC6_FERC_Msk       (0x2000000UL)  /*!< FERC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC6_LSRC_Pos       (26UL)         /*!< LSRC (Bit 26)                                         */
 #define R_MIPI_CSI_VCSC6_LSRC_Msk       (0x4000000UL)  /*!< LSRC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC6_LERC_Pos       (27UL)         /*!< LERC (Bit 27)                                         */
 #define R_MIPI_CSI_VCSC6_LERC_Msk       (0x8000000UL)  /*!< LERC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC6_ETRC_Pos       (28UL)         /*!< ETRC (Bit 28)                                         */
 #define R_MIPI_CSI_VCSC6_ETRC_Msk       (0x10000000UL) /*!< ETRC (Bitfield-Mask: 0x01)                            */
/* =========================================================  VCSC7  ========================================================= */
 #define R_MIPI_CSI_VCSC7_MLFC_Pos       (0UL)          /*!< MLFC (Bit 0)                                          */
 #define R_MIPI_CSI_VCSC7_MLFC_Msk       (0x1UL)        /*!< MLFC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC7_ECDC_Pos       (1UL)          /*!< ECDC (Bit 1)                                          */
 #define R_MIPI_CSI_VCSC7_ECDC_Msk       (0x2UL)        /*!< ECDC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC7_CRCC_Pos       (2UL)          /*!< CRCC (Bit 2)                                          */
 #define R_MIPI_CSI_VCSC7_CRCC_Msk       (0x4UL)        /*!< CRCC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC7_IDEC_Pos       (3UL)          /*!< IDEC (Bit 3)                                          */
 #define R_MIPI_CSI_VCSC7_IDEC_Msk       (0x8UL)        /*!< IDEC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC7_WCEC_Pos       (4UL)          /*!< WCEC (Bit 4)                                          */
 #define R_MIPI_CSI_VCSC7_WCEC_Msk       (0x10UL)       /*!< WCEC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC7_ECCC_Pos       (5UL)          /*!< ECCC (Bit 5)                                          */
 #define R_MIPI_CSI_VCSC7_ECCC_Msk       (0x20UL)       /*!< ECCC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC7_ECNC_Pos       (6UL)          /*!< ECNC (Bit 6)                                          */
 #define R_MIPI_CSI_VCSC7_ECNC_Msk       (0x40UL)       /*!< ECNC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC7_FRSC_Pos       (8UL)          /*!< FRSC (Bit 8)                                          */
 #define R_MIPI_CSI_VCSC7_FRSC_Msk       (0x100UL)      /*!< FRSC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC7_FRDC_Pos       (9UL)          /*!< FRDC (Bit 9)                                          */
 #define R_MIPI_CSI_VCSC7_FRDC_Msk       (0x200UL)      /*!< FRDC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC7_AMLFC_Pos      (14UL)         /*!< AMLFC (Bit 14)                                        */
 #define R_MIPI_CSI_VCSC7_AMLFC_Msk      (0x4000UL)     /*!< AMLFC (Bitfield-Mask: 0x01)                           */
 #define R_MIPI_CSI_VCSC7_AECDC_Pos      (15UL)         /*!< AECDC (Bit 15)                                        */
 #define R_MIPI_CSI_VCSC7_AECDC_Msk      (0x8000UL)     /*!< AECDC (Bitfield-Mask: 0x01)                           */
 #define R_MIPI_CSI_VCSC7_OVFC_Pos       (16UL)         /*!< OVFC (Bit 16)                                         */
 #define R_MIPI_CSI_VCSC7_OVFC_Msk       (0x10000UL)    /*!< OVFC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC7_FSRC_Pos       (24UL)         /*!< FSRC (Bit 24)                                         */
 #define R_MIPI_CSI_VCSC7_FSRC_Msk       (0x1000000UL)  /*!< FSRC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC7_FERC_Pos       (25UL)         /*!< FERC (Bit 25)                                         */
 #define R_MIPI_CSI_VCSC7_FERC_Msk       (0x2000000UL)  /*!< FERC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC7_LSRC_Pos       (26UL)         /*!< LSRC (Bit 26)                                         */
 #define R_MIPI_CSI_VCSC7_LSRC_Msk       (0x4000000UL)  /*!< LSRC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC7_LERC_Pos       (27UL)         /*!< LERC (Bit 27)                                         */
 #define R_MIPI_CSI_VCSC7_LERC_Msk       (0x8000000UL)  /*!< LERC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC7_ETRC_Pos       (28UL)         /*!< ETRC (Bit 28)                                         */
 #define R_MIPI_CSI_VCSC7_ETRC_Msk       (0x10000000UL) /*!< ETRC (Bitfield-Mask: 0x01)                            */
/* =========================================================  VCSC8  ========================================================= */
 #define R_MIPI_CSI_VCSC8_MLFC_Pos       (0UL)          /*!< MLFC (Bit 0)                                          */
 #define R_MIPI_CSI_VCSC8_MLFC_Msk       (0x1UL)        /*!< MLFC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC8_ECDC_Pos       (1UL)          /*!< ECDC (Bit 1)                                          */
 #define R_MIPI_CSI_VCSC8_ECDC_Msk       (0x2UL)        /*!< ECDC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC8_CRCC_Pos       (2UL)          /*!< CRCC (Bit 2)                                          */
 #define R_MIPI_CSI_VCSC8_CRCC_Msk       (0x4UL)        /*!< CRCC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC8_IDEC_Pos       (3UL)          /*!< IDEC (Bit 3)                                          */
 #define R_MIPI_CSI_VCSC8_IDEC_Msk       (0x8UL)        /*!< IDEC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC8_WCEC_Pos       (4UL)          /*!< WCEC (Bit 4)                                          */
 #define R_MIPI_CSI_VCSC8_WCEC_Msk       (0x10UL)       /*!< WCEC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC8_ECCC_Pos       (5UL)          /*!< ECCC (Bit 5)                                          */
 #define R_MIPI_CSI_VCSC8_ECCC_Msk       (0x20UL)       /*!< ECCC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC8_ECNC_Pos       (6UL)          /*!< ECNC (Bit 6)                                          */
 #define R_MIPI_CSI_VCSC8_ECNC_Msk       (0x40UL)       /*!< ECNC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC8_FRSC_Pos       (8UL)          /*!< FRSC (Bit 8)                                          */
 #define R_MIPI_CSI_VCSC8_FRSC_Msk       (0x100UL)      /*!< FRSC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC8_FRDC_Pos       (9UL)          /*!< FRDC (Bit 9)                                          */
 #define R_MIPI_CSI_VCSC8_FRDC_Msk       (0x200UL)      /*!< FRDC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC8_AMLFC_Pos      (14UL)         /*!< AMLFC (Bit 14)                                        */
 #define R_MIPI_CSI_VCSC8_AMLFC_Msk      (0x4000UL)     /*!< AMLFC (Bitfield-Mask: 0x01)                           */
 #define R_MIPI_CSI_VCSC8_AECDC_Pos      (15UL)         /*!< AECDC (Bit 15)                                        */
 #define R_MIPI_CSI_VCSC8_AECDC_Msk      (0x8000UL)     /*!< AECDC (Bitfield-Mask: 0x01)                           */
 #define R_MIPI_CSI_VCSC8_OVFC_Pos       (16UL)         /*!< OVFC (Bit 16)                                         */
 #define R_MIPI_CSI_VCSC8_OVFC_Msk       (0x10000UL)    /*!< OVFC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC8_FSRC_Pos       (24UL)         /*!< FSRC (Bit 24)                                         */
 #define R_MIPI_CSI_VCSC8_FSRC_Msk       (0x1000000UL)  /*!< FSRC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC8_FERC_Pos       (25UL)         /*!< FERC (Bit 25)                                         */
 #define R_MIPI_CSI_VCSC8_FERC_Msk       (0x2000000UL)  /*!< FERC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC8_LSRC_Pos       (26UL)         /*!< LSRC (Bit 26)                                         */
 #define R_MIPI_CSI_VCSC8_LSRC_Msk       (0x4000000UL)  /*!< LSRC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC8_LERC_Pos       (27UL)         /*!< LERC (Bit 27)                                         */
 #define R_MIPI_CSI_VCSC8_LERC_Msk       (0x8000000UL)  /*!< LERC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC8_ETRC_Pos       (28UL)         /*!< ETRC (Bit 28)                                         */
 #define R_MIPI_CSI_VCSC8_ETRC_Msk       (0x10000000UL) /*!< ETRC (Bitfield-Mask: 0x01)                            */
/* =========================================================  VCSC9  ========================================================= */
 #define R_MIPI_CSI_VCSC9_MLFC_Pos       (0UL)          /*!< MLFC (Bit 0)                                          */
 #define R_MIPI_CSI_VCSC9_MLFC_Msk       (0x1UL)        /*!< MLFC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC9_ECDC_Pos       (1UL)          /*!< ECDC (Bit 1)                                          */
 #define R_MIPI_CSI_VCSC9_ECDC_Msk       (0x2UL)        /*!< ECDC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC9_CRCC_Pos       (2UL)          /*!< CRCC (Bit 2)                                          */
 #define R_MIPI_CSI_VCSC9_CRCC_Msk       (0x4UL)        /*!< CRCC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC9_IDEC_Pos       (3UL)          /*!< IDEC (Bit 3)                                          */
 #define R_MIPI_CSI_VCSC9_IDEC_Msk       (0x8UL)        /*!< IDEC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC9_WCEC_Pos       (4UL)          /*!< WCEC (Bit 4)                                          */
 #define R_MIPI_CSI_VCSC9_WCEC_Msk       (0x10UL)       /*!< WCEC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC9_ECCC_Pos       (5UL)          /*!< ECCC (Bit 5)                                          */
 #define R_MIPI_CSI_VCSC9_ECCC_Msk       (0x20UL)       /*!< ECCC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC9_ECNC_Pos       (6UL)          /*!< ECNC (Bit 6)                                          */
 #define R_MIPI_CSI_VCSC9_ECNC_Msk       (0x40UL)       /*!< ECNC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC9_FRSC_Pos       (8UL)          /*!< FRSC (Bit 8)                                          */
 #define R_MIPI_CSI_VCSC9_FRSC_Msk       (0x100UL)      /*!< FRSC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC9_FRDC_Pos       (9UL)          /*!< FRDC (Bit 9)                                          */
 #define R_MIPI_CSI_VCSC9_FRDC_Msk       (0x200UL)      /*!< FRDC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC9_AMLFC_Pos      (14UL)         /*!< AMLFC (Bit 14)                                        */
 #define R_MIPI_CSI_VCSC9_AMLFC_Msk      (0x4000UL)     /*!< AMLFC (Bitfield-Mask: 0x01)                           */
 #define R_MIPI_CSI_VCSC9_AECDC_Pos      (15UL)         /*!< AECDC (Bit 15)                                        */
 #define R_MIPI_CSI_VCSC9_AECDC_Msk      (0x8000UL)     /*!< AECDC (Bitfield-Mask: 0x01)                           */
 #define R_MIPI_CSI_VCSC9_OVFC_Pos       (16UL)         /*!< OVFC (Bit 16)                                         */
 #define R_MIPI_CSI_VCSC9_OVFC_Msk       (0x10000UL)    /*!< OVFC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC9_FSRC_Pos       (24UL)         /*!< FSRC (Bit 24)                                         */
 #define R_MIPI_CSI_VCSC9_FSRC_Msk       (0x1000000UL)  /*!< FSRC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC9_FERC_Pos       (25UL)         /*!< FERC (Bit 25)                                         */
 #define R_MIPI_CSI_VCSC9_FERC_Msk       (0x2000000UL)  /*!< FERC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC9_LSRC_Pos       (26UL)         /*!< LSRC (Bit 26)                                         */
 #define R_MIPI_CSI_VCSC9_LSRC_Msk       (0x4000000UL)  /*!< LSRC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC9_LERC_Pos       (27UL)         /*!< LERC (Bit 27)                                         */
 #define R_MIPI_CSI_VCSC9_LERC_Msk       (0x8000000UL)  /*!< LERC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC9_ETRC_Pos       (28UL)         /*!< ETRC (Bit 28)                                         */
 #define R_MIPI_CSI_VCSC9_ETRC_Msk       (0x10000000UL) /*!< ETRC (Bitfield-Mask: 0x01)                            */
/* ========================================================  VCSC10  ========================================================= */
 #define R_MIPI_CSI_VCSC10_MLFC_Pos      (0UL)          /*!< MLFC (Bit 0)                                          */
 #define R_MIPI_CSI_VCSC10_MLFC_Msk      (0x1UL)        /*!< MLFC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC10_ECDC_Pos      (1UL)          /*!< ECDC (Bit 1)                                          */
 #define R_MIPI_CSI_VCSC10_ECDC_Msk      (0x2UL)        /*!< ECDC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC10_CRCC_Pos      (2UL)          /*!< CRCC (Bit 2)                                          */
 #define R_MIPI_CSI_VCSC10_CRCC_Msk      (0x4UL)        /*!< CRCC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC10_IDEC_Pos      (3UL)          /*!< IDEC (Bit 3)                                          */
 #define R_MIPI_CSI_VCSC10_IDEC_Msk      (0x8UL)        /*!< IDEC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC10_WCEC_Pos      (4UL)          /*!< WCEC (Bit 4)                                          */
 #define R_MIPI_CSI_VCSC10_WCEC_Msk      (0x10UL)       /*!< WCEC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC10_ECCC_Pos      (5UL)          /*!< ECCC (Bit 5)                                          */
 #define R_MIPI_CSI_VCSC10_ECCC_Msk      (0x20UL)       /*!< ECCC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC10_ECNC_Pos      (6UL)          /*!< ECNC (Bit 6)                                          */
 #define R_MIPI_CSI_VCSC10_ECNC_Msk      (0x40UL)       /*!< ECNC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC10_FRSC_Pos      (8UL)          /*!< FRSC (Bit 8)                                          */
 #define R_MIPI_CSI_VCSC10_FRSC_Msk      (0x100UL)      /*!< FRSC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC10_FRDC_Pos      (9UL)          /*!< FRDC (Bit 9)                                          */
 #define R_MIPI_CSI_VCSC10_FRDC_Msk      (0x200UL)      /*!< FRDC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC10_AMLFC_Pos     (14UL)         /*!< AMLFC (Bit 14)                                        */
 #define R_MIPI_CSI_VCSC10_AMLFC_Msk     (0x4000UL)     /*!< AMLFC (Bitfield-Mask: 0x01)                           */
 #define R_MIPI_CSI_VCSC10_AECDC_Pos     (15UL)         /*!< AECDC (Bit 15)                                        */
 #define R_MIPI_CSI_VCSC10_AECDC_Msk     (0x8000UL)     /*!< AECDC (Bitfield-Mask: 0x01)                           */
 #define R_MIPI_CSI_VCSC10_OVFC_Pos      (16UL)         /*!< OVFC (Bit 16)                                         */
 #define R_MIPI_CSI_VCSC10_OVFC_Msk      (0x10000UL)    /*!< OVFC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC10_FSRC_Pos      (24UL)         /*!< FSRC (Bit 24)                                         */
 #define R_MIPI_CSI_VCSC10_FSRC_Msk      (0x1000000UL)  /*!< FSRC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC10_FERC_Pos      (25UL)         /*!< FERC (Bit 25)                                         */
 #define R_MIPI_CSI_VCSC10_FERC_Msk      (0x2000000UL)  /*!< FERC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC10_LSRC_Pos      (26UL)         /*!< LSRC (Bit 26)                                         */
 #define R_MIPI_CSI_VCSC10_LSRC_Msk      (0x4000000UL)  /*!< LSRC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC10_LERC_Pos      (27UL)         /*!< LERC (Bit 27)                                         */
 #define R_MIPI_CSI_VCSC10_LERC_Msk      (0x8000000UL)  /*!< LERC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC10_ETRC_Pos      (28UL)         /*!< ETRC (Bit 28)                                         */
 #define R_MIPI_CSI_VCSC10_ETRC_Msk      (0x10000000UL) /*!< ETRC (Bitfield-Mask: 0x01)                            */
/* ========================================================  VCSC11  ========================================================= */
 #define R_MIPI_CSI_VCSC11_MLFC_Pos      (0UL)          /*!< MLFC (Bit 0)                                          */
 #define R_MIPI_CSI_VCSC11_MLFC_Msk      (0x1UL)        /*!< MLFC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC11_ECDC_Pos      (1UL)          /*!< ECDC (Bit 1)                                          */
 #define R_MIPI_CSI_VCSC11_ECDC_Msk      (0x2UL)        /*!< ECDC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC11_CRCC_Pos      (2UL)          /*!< CRCC (Bit 2)                                          */
 #define R_MIPI_CSI_VCSC11_CRCC_Msk      (0x4UL)        /*!< CRCC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC11_IDEC_Pos      (3UL)          /*!< IDEC (Bit 3)                                          */
 #define R_MIPI_CSI_VCSC11_IDEC_Msk      (0x8UL)        /*!< IDEC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC11_WCEC_Pos      (4UL)          /*!< WCEC (Bit 4)                                          */
 #define R_MIPI_CSI_VCSC11_WCEC_Msk      (0x10UL)       /*!< WCEC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC11_ECCC_Pos      (5UL)          /*!< ECCC (Bit 5)                                          */
 #define R_MIPI_CSI_VCSC11_ECCC_Msk      (0x20UL)       /*!< ECCC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC11_ECNC_Pos      (6UL)          /*!< ECNC (Bit 6)                                          */
 #define R_MIPI_CSI_VCSC11_ECNC_Msk      (0x40UL)       /*!< ECNC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC11_FRSC_Pos      (8UL)          /*!< FRSC (Bit 8)                                          */
 #define R_MIPI_CSI_VCSC11_FRSC_Msk      (0x100UL)      /*!< FRSC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC11_FRDC_Pos      (9UL)          /*!< FRDC (Bit 9)                                          */
 #define R_MIPI_CSI_VCSC11_FRDC_Msk      (0x200UL)      /*!< FRDC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC11_AMLFC_Pos     (14UL)         /*!< AMLFC (Bit 14)                                        */
 #define R_MIPI_CSI_VCSC11_AMLFC_Msk     (0x4000UL)     /*!< AMLFC (Bitfield-Mask: 0x01)                           */
 #define R_MIPI_CSI_VCSC11_AECDC_Pos     (15UL)         /*!< AECDC (Bit 15)                                        */
 #define R_MIPI_CSI_VCSC11_AECDC_Msk     (0x8000UL)     /*!< AECDC (Bitfield-Mask: 0x01)                           */
 #define R_MIPI_CSI_VCSC11_OVFC_Pos      (16UL)         /*!< OVFC (Bit 16)                                         */
 #define R_MIPI_CSI_VCSC11_OVFC_Msk      (0x10000UL)    /*!< OVFC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC11_FSRC_Pos      (24UL)         /*!< FSRC (Bit 24)                                         */
 #define R_MIPI_CSI_VCSC11_FSRC_Msk      (0x1000000UL)  /*!< FSRC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC11_FERC_Pos      (25UL)         /*!< FERC (Bit 25)                                         */
 #define R_MIPI_CSI_VCSC11_FERC_Msk      (0x2000000UL)  /*!< FERC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC11_LSRC_Pos      (26UL)         /*!< LSRC (Bit 26)                                         */
 #define R_MIPI_CSI_VCSC11_LSRC_Msk      (0x4000000UL)  /*!< LSRC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC11_LERC_Pos      (27UL)         /*!< LERC (Bit 27)                                         */
 #define R_MIPI_CSI_VCSC11_LERC_Msk      (0x8000000UL)  /*!< LERC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC11_ETRC_Pos      (28UL)         /*!< ETRC (Bit 28)                                         */
 #define R_MIPI_CSI_VCSC11_ETRC_Msk      (0x10000000UL) /*!< ETRC (Bitfield-Mask: 0x01)                            */
/* ========================================================  VCSC12  ========================================================= */
 #define R_MIPI_CSI_VCSC12_MLFC_Pos      (0UL)          /*!< MLFC (Bit 0)                                          */
 #define R_MIPI_CSI_VCSC12_MLFC_Msk      (0x1UL)        /*!< MLFC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC12_ECDC_Pos      (1UL)          /*!< ECDC (Bit 1)                                          */
 #define R_MIPI_CSI_VCSC12_ECDC_Msk      (0x2UL)        /*!< ECDC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC12_CRCC_Pos      (2UL)          /*!< CRCC (Bit 2)                                          */
 #define R_MIPI_CSI_VCSC12_CRCC_Msk      (0x4UL)        /*!< CRCC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC12_IDEC_Pos      (3UL)          /*!< IDEC (Bit 3)                                          */
 #define R_MIPI_CSI_VCSC12_IDEC_Msk      (0x8UL)        /*!< IDEC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC12_WCEC_Pos      (4UL)          /*!< WCEC (Bit 4)                                          */
 #define R_MIPI_CSI_VCSC12_WCEC_Msk      (0x10UL)       /*!< WCEC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC12_ECCC_Pos      (5UL)          /*!< ECCC (Bit 5)                                          */
 #define R_MIPI_CSI_VCSC12_ECCC_Msk      (0x20UL)       /*!< ECCC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC12_ECNC_Pos      (6UL)          /*!< ECNC (Bit 6)                                          */
 #define R_MIPI_CSI_VCSC12_ECNC_Msk      (0x40UL)       /*!< ECNC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC12_FRSC_Pos      (8UL)          /*!< FRSC (Bit 8)                                          */
 #define R_MIPI_CSI_VCSC12_FRSC_Msk      (0x100UL)      /*!< FRSC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC12_FRDC_Pos      (9UL)          /*!< FRDC (Bit 9)                                          */
 #define R_MIPI_CSI_VCSC12_FRDC_Msk      (0x200UL)      /*!< FRDC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC12_AMLFC_Pos     (14UL)         /*!< AMLFC (Bit 14)                                        */
 #define R_MIPI_CSI_VCSC12_AMLFC_Msk     (0x4000UL)     /*!< AMLFC (Bitfield-Mask: 0x01)                           */
 #define R_MIPI_CSI_VCSC12_AECDC_Pos     (15UL)         /*!< AECDC (Bit 15)                                        */
 #define R_MIPI_CSI_VCSC12_AECDC_Msk     (0x8000UL)     /*!< AECDC (Bitfield-Mask: 0x01)                           */
 #define R_MIPI_CSI_VCSC12_OVFC_Pos      (16UL)         /*!< OVFC (Bit 16)                                         */
 #define R_MIPI_CSI_VCSC12_OVFC_Msk      (0x10000UL)    /*!< OVFC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC12_FSRC_Pos      (24UL)         /*!< FSRC (Bit 24)                                         */
 #define R_MIPI_CSI_VCSC12_FSRC_Msk      (0x1000000UL)  /*!< FSRC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC12_FERC_Pos      (25UL)         /*!< FERC (Bit 25)                                         */
 #define R_MIPI_CSI_VCSC12_FERC_Msk      (0x2000000UL)  /*!< FERC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC12_LSRC_Pos      (26UL)         /*!< LSRC (Bit 26)                                         */
 #define R_MIPI_CSI_VCSC12_LSRC_Msk      (0x4000000UL)  /*!< LSRC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC12_LERC_Pos      (27UL)         /*!< LERC (Bit 27)                                         */
 #define R_MIPI_CSI_VCSC12_LERC_Msk      (0x8000000UL)  /*!< LERC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC12_ETRC_Pos      (28UL)         /*!< ETRC (Bit 28)                                         */
 #define R_MIPI_CSI_VCSC12_ETRC_Msk      (0x10000000UL) /*!< ETRC (Bitfield-Mask: 0x01)                            */
/* ========================================================  VCSC13  ========================================================= */
 #define R_MIPI_CSI_VCSC13_MLFC_Pos      (0UL)          /*!< MLFC (Bit 0)                                          */
 #define R_MIPI_CSI_VCSC13_MLFC_Msk      (0x1UL)        /*!< MLFC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC13_ECDC_Pos      (1UL)          /*!< ECDC (Bit 1)                                          */
 #define R_MIPI_CSI_VCSC13_ECDC_Msk      (0x2UL)        /*!< ECDC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC13_CRCC_Pos      (2UL)          /*!< CRCC (Bit 2)                                          */
 #define R_MIPI_CSI_VCSC13_CRCC_Msk      (0x4UL)        /*!< CRCC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC13_IDEC_Pos      (3UL)          /*!< IDEC (Bit 3)                                          */
 #define R_MIPI_CSI_VCSC13_IDEC_Msk      (0x8UL)        /*!< IDEC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC13_WCEC_Pos      (4UL)          /*!< WCEC (Bit 4)                                          */
 #define R_MIPI_CSI_VCSC13_WCEC_Msk      (0x10UL)       /*!< WCEC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC13_ECCC_Pos      (5UL)          /*!< ECCC (Bit 5)                                          */
 #define R_MIPI_CSI_VCSC13_ECCC_Msk      (0x20UL)       /*!< ECCC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC13_ECNC_Pos      (6UL)          /*!< ECNC (Bit 6)                                          */
 #define R_MIPI_CSI_VCSC13_ECNC_Msk      (0x40UL)       /*!< ECNC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC13_FRSC_Pos      (8UL)          /*!< FRSC (Bit 8)                                          */
 #define R_MIPI_CSI_VCSC13_FRSC_Msk      (0x100UL)      /*!< FRSC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC13_FRDC_Pos      (9UL)          /*!< FRDC (Bit 9)                                          */
 #define R_MIPI_CSI_VCSC13_FRDC_Msk      (0x200UL)      /*!< FRDC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC13_AMLFC_Pos     (14UL)         /*!< AMLFC (Bit 14)                                        */
 #define R_MIPI_CSI_VCSC13_AMLFC_Msk     (0x4000UL)     /*!< AMLFC (Bitfield-Mask: 0x01)                           */
 #define R_MIPI_CSI_VCSC13_AECDC_Pos     (15UL)         /*!< AECDC (Bit 15)                                        */
 #define R_MIPI_CSI_VCSC13_AECDC_Msk     (0x8000UL)     /*!< AECDC (Bitfield-Mask: 0x01)                           */
 #define R_MIPI_CSI_VCSC13_OVFC_Pos      (16UL)         /*!< OVFC (Bit 16)                                         */
 #define R_MIPI_CSI_VCSC13_OVFC_Msk      (0x10000UL)    /*!< OVFC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC13_FSRC_Pos      (24UL)         /*!< FSRC (Bit 24)                                         */
 #define R_MIPI_CSI_VCSC13_FSRC_Msk      (0x1000000UL)  /*!< FSRC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC13_FERC_Pos      (25UL)         /*!< FERC (Bit 25)                                         */
 #define R_MIPI_CSI_VCSC13_FERC_Msk      (0x2000000UL)  /*!< FERC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC13_LSRC_Pos      (26UL)         /*!< LSRC (Bit 26)                                         */
 #define R_MIPI_CSI_VCSC13_LSRC_Msk      (0x4000000UL)  /*!< LSRC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC13_LERC_Pos      (27UL)         /*!< LERC (Bit 27)                                         */
 #define R_MIPI_CSI_VCSC13_LERC_Msk      (0x8000000UL)  /*!< LERC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC13_ETRC_Pos      (28UL)         /*!< ETRC (Bit 28)                                         */
 #define R_MIPI_CSI_VCSC13_ETRC_Msk      (0x10000000UL) /*!< ETRC (Bitfield-Mask: 0x01)                            */
/* ========================================================  VCSC14  ========================================================= */
 #define R_MIPI_CSI_VCSC14_MLFC_Pos      (0UL)          /*!< MLFC (Bit 0)                                          */
 #define R_MIPI_CSI_VCSC14_MLFC_Msk      (0x1UL)        /*!< MLFC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC14_ECDC_Pos      (1UL)          /*!< ECDC (Bit 1)                                          */
 #define R_MIPI_CSI_VCSC14_ECDC_Msk      (0x2UL)        /*!< ECDC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC14_CRCC_Pos      (2UL)          /*!< CRCC (Bit 2)                                          */
 #define R_MIPI_CSI_VCSC14_CRCC_Msk      (0x4UL)        /*!< CRCC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC14_IDEC_Pos      (3UL)          /*!< IDEC (Bit 3)                                          */
 #define R_MIPI_CSI_VCSC14_IDEC_Msk      (0x8UL)        /*!< IDEC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC14_WCEC_Pos      (4UL)          /*!< WCEC (Bit 4)                                          */
 #define R_MIPI_CSI_VCSC14_WCEC_Msk      (0x10UL)       /*!< WCEC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC14_ECCC_Pos      (5UL)          /*!< ECCC (Bit 5)                                          */
 #define R_MIPI_CSI_VCSC14_ECCC_Msk      (0x20UL)       /*!< ECCC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC14_ECNC_Pos      (6UL)          /*!< ECNC (Bit 6)                                          */
 #define R_MIPI_CSI_VCSC14_ECNC_Msk      (0x40UL)       /*!< ECNC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC14_FRSC_Pos      (8UL)          /*!< FRSC (Bit 8)                                          */
 #define R_MIPI_CSI_VCSC14_FRSC_Msk      (0x100UL)      /*!< FRSC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC14_FRDC_Pos      (9UL)          /*!< FRDC (Bit 9)                                          */
 #define R_MIPI_CSI_VCSC14_FRDC_Msk      (0x200UL)      /*!< FRDC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC14_AMLFC_Pos     (14UL)         /*!< AMLFC (Bit 14)                                        */
 #define R_MIPI_CSI_VCSC14_AMLFC_Msk     (0x4000UL)     /*!< AMLFC (Bitfield-Mask: 0x01)                           */
 #define R_MIPI_CSI_VCSC14_AECDC_Pos     (15UL)         /*!< AECDC (Bit 15)                                        */
 #define R_MIPI_CSI_VCSC14_AECDC_Msk     (0x8000UL)     /*!< AECDC (Bitfield-Mask: 0x01)                           */
 #define R_MIPI_CSI_VCSC14_OVFC_Pos      (16UL)         /*!< OVFC (Bit 16)                                         */
 #define R_MIPI_CSI_VCSC14_OVFC_Msk      (0x10000UL)    /*!< OVFC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC14_FSRC_Pos      (24UL)         /*!< FSRC (Bit 24)                                         */
 #define R_MIPI_CSI_VCSC14_FSRC_Msk      (0x1000000UL)  /*!< FSRC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC14_FERC_Pos      (25UL)         /*!< FERC (Bit 25)                                         */
 #define R_MIPI_CSI_VCSC14_FERC_Msk      (0x2000000UL)  /*!< FERC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC14_LSRC_Pos      (26UL)         /*!< LSRC (Bit 26)                                         */
 #define R_MIPI_CSI_VCSC14_LSRC_Msk      (0x4000000UL)  /*!< LSRC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC14_LERC_Pos      (27UL)         /*!< LERC (Bit 27)                                         */
 #define R_MIPI_CSI_VCSC14_LERC_Msk      (0x8000000UL)  /*!< LERC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC14_ETRC_Pos      (28UL)         /*!< ETRC (Bit 28)                                         */
 #define R_MIPI_CSI_VCSC14_ETRC_Msk      (0x10000000UL) /*!< ETRC (Bitfield-Mask: 0x01)                            */
/* ========================================================  VCSC15  ========================================================= */
 #define R_MIPI_CSI_VCSC15_MLFC_Pos      (0UL)          /*!< MLFC (Bit 0)                                          */
 #define R_MIPI_CSI_VCSC15_MLFC_Msk      (0x1UL)        /*!< MLFC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC15_ECDC_Pos      (1UL)          /*!< ECDC (Bit 1)                                          */
 #define R_MIPI_CSI_VCSC15_ECDC_Msk      (0x2UL)        /*!< ECDC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC15_CRCC_Pos      (2UL)          /*!< CRCC (Bit 2)                                          */
 #define R_MIPI_CSI_VCSC15_CRCC_Msk      (0x4UL)        /*!< CRCC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC15_IDEC_Pos      (3UL)          /*!< IDEC (Bit 3)                                          */
 #define R_MIPI_CSI_VCSC15_IDEC_Msk      (0x8UL)        /*!< IDEC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC15_WCEC_Pos      (4UL)          /*!< WCEC (Bit 4)                                          */
 #define R_MIPI_CSI_VCSC15_WCEC_Msk      (0x10UL)       /*!< WCEC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC15_ECCC_Pos      (5UL)          /*!< ECCC (Bit 5)                                          */
 #define R_MIPI_CSI_VCSC15_ECCC_Msk      (0x20UL)       /*!< ECCC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC15_ECNC_Pos      (6UL)          /*!< ECNC (Bit 6)                                          */
 #define R_MIPI_CSI_VCSC15_ECNC_Msk      (0x40UL)       /*!< ECNC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC15_FRSC_Pos      (8UL)          /*!< FRSC (Bit 8)                                          */
 #define R_MIPI_CSI_VCSC15_FRSC_Msk      (0x100UL)      /*!< FRSC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC15_FRDC_Pos      (9UL)          /*!< FRDC (Bit 9)                                          */
 #define R_MIPI_CSI_VCSC15_FRDC_Msk      (0x200UL)      /*!< FRDC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC15_AMLFC_Pos     (14UL)         /*!< AMLFC (Bit 14)                                        */
 #define R_MIPI_CSI_VCSC15_AMLFC_Msk     (0x4000UL)     /*!< AMLFC (Bitfield-Mask: 0x01)                           */
 #define R_MIPI_CSI_VCSC15_AECDC_Pos     (15UL)         /*!< AECDC (Bit 15)                                        */
 #define R_MIPI_CSI_VCSC15_AECDC_Msk     (0x8000UL)     /*!< AECDC (Bitfield-Mask: 0x01)                           */
 #define R_MIPI_CSI_VCSC15_OVFC_Pos      (16UL)         /*!< OVFC (Bit 16)                                         */
 #define R_MIPI_CSI_VCSC15_OVFC_Msk      (0x10000UL)    /*!< OVFC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC15_FSRC_Pos      (24UL)         /*!< FSRC (Bit 24)                                         */
 #define R_MIPI_CSI_VCSC15_FSRC_Msk      (0x1000000UL)  /*!< FSRC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC15_FERC_Pos      (25UL)         /*!< FERC (Bit 25)                                         */
 #define R_MIPI_CSI_VCSC15_FERC_Msk      (0x2000000UL)  /*!< FERC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC15_LSRC_Pos      (26UL)         /*!< LSRC (Bit 26)                                         */
 #define R_MIPI_CSI_VCSC15_LSRC_Msk      (0x4000000UL)  /*!< LSRC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC15_LERC_Pos      (27UL)         /*!< LERC (Bit 27)                                         */
 #define R_MIPI_CSI_VCSC15_LERC_Msk      (0x8000000UL)  /*!< LERC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCSC15_ETRC_Pos      (28UL)         /*!< ETRC (Bit 28)                                         */
 #define R_MIPI_CSI_VCSC15_ETRC_Msk      (0x10000000UL) /*!< ETRC (Bitfield-Mask: 0x01)                            */
/* =========================================================  VCIE0  ========================================================= */
 #define R_MIPI_CSI_VCIE0_MLFE_Pos       (0UL)          /*!< MLFE (Bit 0)                                          */
 #define R_MIPI_CSI_VCIE0_MLFE_Msk       (0x1UL)        /*!< MLFE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE0_ECDE_Pos       (1UL)          /*!< ECDE (Bit 1)                                          */
 #define R_MIPI_CSI_VCIE0_ECDE_Msk       (0x2UL)        /*!< ECDE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE0_CRCE_Pos       (2UL)          /*!< CRCE (Bit 2)                                          */
 #define R_MIPI_CSI_VCIE0_CRCE_Msk       (0x4UL)        /*!< CRCE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE0_IDEE_Pos       (3UL)          /*!< IDEE (Bit 3)                                          */
 #define R_MIPI_CSI_VCIE0_IDEE_Msk       (0x8UL)        /*!< IDEE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE0_WCEE_Pos       (4UL)          /*!< WCEE (Bit 4)                                          */
 #define R_MIPI_CSI_VCIE0_WCEE_Msk       (0x10UL)       /*!< WCEE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE0_ECCE_Pos       (5UL)          /*!< ECCE (Bit 5)                                          */
 #define R_MIPI_CSI_VCIE0_ECCE_Msk       (0x20UL)       /*!< ECCE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE0_ECNE_Pos       (6UL)          /*!< ECNE (Bit 6)                                          */
 #define R_MIPI_CSI_VCIE0_ECNE_Msk       (0x40UL)       /*!< ECNE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE0_FRSE_Pos       (8UL)          /*!< FRSE (Bit 8)                                          */
 #define R_MIPI_CSI_VCIE0_FRSE_Msk       (0x100UL)      /*!< FRSE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE0_FRDE_Pos       (9UL)          /*!< FRDE (Bit 9)                                          */
 #define R_MIPI_CSI_VCIE0_FRDE_Msk       (0x200UL)      /*!< FRDE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE0_OVFE_Pos       (16UL)         /*!< OVFE (Bit 16)                                         */
 #define R_MIPI_CSI_VCIE0_OVFE_Msk       (0x10000UL)    /*!< OVFE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE0_FSRE_Pos       (24UL)         /*!< FSRE (Bit 24)                                         */
 #define R_MIPI_CSI_VCIE0_FSRE_Msk       (0x1000000UL)  /*!< FSRE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE0_FERE_Pos       (25UL)         /*!< FERE (Bit 25)                                         */
 #define R_MIPI_CSI_VCIE0_FERE_Msk       (0x2000000UL)  /*!< FERE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE0_LSRE_Pos       (26UL)         /*!< LSRE (Bit 26)                                         */
 #define R_MIPI_CSI_VCIE0_LSRE_Msk       (0x4000000UL)  /*!< LSRE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE0_LERE_Pos       (27UL)         /*!< LERE (Bit 27)                                         */
 #define R_MIPI_CSI_VCIE0_LERE_Msk       (0x8000000UL)  /*!< LERE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE0_ETRE_Pos       (28UL)         /*!< ETRE (Bit 28)                                         */
 #define R_MIPI_CSI_VCIE0_ETRE_Msk       (0x10000000UL) /*!< ETRE (Bitfield-Mask: 0x01)                            */
/* =========================================================  VCIE1  ========================================================= */
 #define R_MIPI_CSI_VCIE1_MLFE_Pos       (0UL)          /*!< MLFE (Bit 0)                                          */
 #define R_MIPI_CSI_VCIE1_MLFE_Msk       (0x1UL)        /*!< MLFE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE1_ECDE_Pos       (1UL)          /*!< ECDE (Bit 1)                                          */
 #define R_MIPI_CSI_VCIE1_ECDE_Msk       (0x2UL)        /*!< ECDE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE1_CRCE_Pos       (2UL)          /*!< CRCE (Bit 2)                                          */
 #define R_MIPI_CSI_VCIE1_CRCE_Msk       (0x4UL)        /*!< CRCE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE1_IDEE_Pos       (3UL)          /*!< IDEE (Bit 3)                                          */
 #define R_MIPI_CSI_VCIE1_IDEE_Msk       (0x8UL)        /*!< IDEE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE1_WCEE_Pos       (4UL)          /*!< WCEE (Bit 4)                                          */
 #define R_MIPI_CSI_VCIE1_WCEE_Msk       (0x10UL)       /*!< WCEE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE1_ECCE_Pos       (5UL)          /*!< ECCE (Bit 5)                                          */
 #define R_MIPI_CSI_VCIE1_ECCE_Msk       (0x20UL)       /*!< ECCE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE1_ECNE_Pos       (6UL)          /*!< ECNE (Bit 6)                                          */
 #define R_MIPI_CSI_VCIE1_ECNE_Msk       (0x40UL)       /*!< ECNE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE1_FRSE_Pos       (8UL)          /*!< FRSE (Bit 8)                                          */
 #define R_MIPI_CSI_VCIE1_FRSE_Msk       (0x100UL)      /*!< FRSE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE1_FRDE_Pos       (9UL)          /*!< FRDE (Bit 9)                                          */
 #define R_MIPI_CSI_VCIE1_FRDE_Msk       (0x200UL)      /*!< FRDE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE1_OVFE_Pos       (16UL)         /*!< OVFE (Bit 16)                                         */
 #define R_MIPI_CSI_VCIE1_OVFE_Msk       (0x10000UL)    /*!< OVFE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE1_FSRE_Pos       (24UL)         /*!< FSRE (Bit 24)                                         */
 #define R_MIPI_CSI_VCIE1_FSRE_Msk       (0x1000000UL)  /*!< FSRE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE1_FERE_Pos       (25UL)         /*!< FERE (Bit 25)                                         */
 #define R_MIPI_CSI_VCIE1_FERE_Msk       (0x2000000UL)  /*!< FERE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE1_LSRE_Pos       (26UL)         /*!< LSRE (Bit 26)                                         */
 #define R_MIPI_CSI_VCIE1_LSRE_Msk       (0x4000000UL)  /*!< LSRE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE1_LERE_Pos       (27UL)         /*!< LERE (Bit 27)                                         */
 #define R_MIPI_CSI_VCIE1_LERE_Msk       (0x8000000UL)  /*!< LERE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE1_ETRE_Pos       (28UL)         /*!< ETRE (Bit 28)                                         */
 #define R_MIPI_CSI_VCIE1_ETRE_Msk       (0x10000000UL) /*!< ETRE (Bitfield-Mask: 0x01)                            */
/* =========================================================  VCIE2  ========================================================= */
 #define R_MIPI_CSI_VCIE2_MLFE_Pos       (0UL)          /*!< MLFE (Bit 0)                                          */
 #define R_MIPI_CSI_VCIE2_MLFE_Msk       (0x1UL)        /*!< MLFE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE2_ECDE_Pos       (1UL)          /*!< ECDE (Bit 1)                                          */
 #define R_MIPI_CSI_VCIE2_ECDE_Msk       (0x2UL)        /*!< ECDE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE2_CRCE_Pos       (2UL)          /*!< CRCE (Bit 2)                                          */
 #define R_MIPI_CSI_VCIE2_CRCE_Msk       (0x4UL)        /*!< CRCE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE2_IDEE_Pos       (3UL)          /*!< IDEE (Bit 3)                                          */
 #define R_MIPI_CSI_VCIE2_IDEE_Msk       (0x8UL)        /*!< IDEE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE2_WCEE_Pos       (4UL)          /*!< WCEE (Bit 4)                                          */
 #define R_MIPI_CSI_VCIE2_WCEE_Msk       (0x10UL)       /*!< WCEE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE2_ECCE_Pos       (5UL)          /*!< ECCE (Bit 5)                                          */
 #define R_MIPI_CSI_VCIE2_ECCE_Msk       (0x20UL)       /*!< ECCE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE2_ECNE_Pos       (6UL)          /*!< ECNE (Bit 6)                                          */
 #define R_MIPI_CSI_VCIE2_ECNE_Msk       (0x40UL)       /*!< ECNE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE2_FRSE_Pos       (8UL)          /*!< FRSE (Bit 8)                                          */
 #define R_MIPI_CSI_VCIE2_FRSE_Msk       (0x100UL)      /*!< FRSE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE2_FRDE_Pos       (9UL)          /*!< FRDE (Bit 9)                                          */
 #define R_MIPI_CSI_VCIE2_FRDE_Msk       (0x200UL)      /*!< FRDE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE2_OVFE_Pos       (16UL)         /*!< OVFE (Bit 16)                                         */
 #define R_MIPI_CSI_VCIE2_OVFE_Msk       (0x10000UL)    /*!< OVFE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE2_FSRE_Pos       (24UL)         /*!< FSRE (Bit 24)                                         */
 #define R_MIPI_CSI_VCIE2_FSRE_Msk       (0x1000000UL)  /*!< FSRE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE2_FERE_Pos       (25UL)         /*!< FERE (Bit 25)                                         */
 #define R_MIPI_CSI_VCIE2_FERE_Msk       (0x2000000UL)  /*!< FERE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE2_LSRE_Pos       (26UL)         /*!< LSRE (Bit 26)                                         */
 #define R_MIPI_CSI_VCIE2_LSRE_Msk       (0x4000000UL)  /*!< LSRE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE2_LERE_Pos       (27UL)         /*!< LERE (Bit 27)                                         */
 #define R_MIPI_CSI_VCIE2_LERE_Msk       (0x8000000UL)  /*!< LERE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE2_ETRE_Pos       (28UL)         /*!< ETRE (Bit 28)                                         */
 #define R_MIPI_CSI_VCIE2_ETRE_Msk       (0x10000000UL) /*!< ETRE (Bitfield-Mask: 0x01)                            */
/* =========================================================  VCIE3  ========================================================= */
 #define R_MIPI_CSI_VCIE3_MLFE_Pos       (0UL)          /*!< MLFE (Bit 0)                                          */
 #define R_MIPI_CSI_VCIE3_MLFE_Msk       (0x1UL)        /*!< MLFE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE3_ECDE_Pos       (1UL)          /*!< ECDE (Bit 1)                                          */
 #define R_MIPI_CSI_VCIE3_ECDE_Msk       (0x2UL)        /*!< ECDE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE3_CRCE_Pos       (2UL)          /*!< CRCE (Bit 2)                                          */
 #define R_MIPI_CSI_VCIE3_CRCE_Msk       (0x4UL)        /*!< CRCE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE3_IDEE_Pos       (3UL)          /*!< IDEE (Bit 3)                                          */
 #define R_MIPI_CSI_VCIE3_IDEE_Msk       (0x8UL)        /*!< IDEE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE3_WCEE_Pos       (4UL)          /*!< WCEE (Bit 4)                                          */
 #define R_MIPI_CSI_VCIE3_WCEE_Msk       (0x10UL)       /*!< WCEE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE3_ECCE_Pos       (5UL)          /*!< ECCE (Bit 5)                                          */
 #define R_MIPI_CSI_VCIE3_ECCE_Msk       (0x20UL)       /*!< ECCE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE3_ECNE_Pos       (6UL)          /*!< ECNE (Bit 6)                                          */
 #define R_MIPI_CSI_VCIE3_ECNE_Msk       (0x40UL)       /*!< ECNE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE3_FRSE_Pos       (8UL)          /*!< FRSE (Bit 8)                                          */
 #define R_MIPI_CSI_VCIE3_FRSE_Msk       (0x100UL)      /*!< FRSE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE3_FRDE_Pos       (9UL)          /*!< FRDE (Bit 9)                                          */
 #define R_MIPI_CSI_VCIE3_FRDE_Msk       (0x200UL)      /*!< FRDE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE3_OVFE_Pos       (16UL)         /*!< OVFE (Bit 16)                                         */
 #define R_MIPI_CSI_VCIE3_OVFE_Msk       (0x10000UL)    /*!< OVFE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE3_FSRE_Pos       (24UL)         /*!< FSRE (Bit 24)                                         */
 #define R_MIPI_CSI_VCIE3_FSRE_Msk       (0x1000000UL)  /*!< FSRE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE3_FERE_Pos       (25UL)         /*!< FERE (Bit 25)                                         */
 #define R_MIPI_CSI_VCIE3_FERE_Msk       (0x2000000UL)  /*!< FERE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE3_LSRE_Pos       (26UL)         /*!< LSRE (Bit 26)                                         */
 #define R_MIPI_CSI_VCIE3_LSRE_Msk       (0x4000000UL)  /*!< LSRE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE3_LERE_Pos       (27UL)         /*!< LERE (Bit 27)                                         */
 #define R_MIPI_CSI_VCIE3_LERE_Msk       (0x8000000UL)  /*!< LERE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE3_ETRE_Pos       (28UL)         /*!< ETRE (Bit 28)                                         */
 #define R_MIPI_CSI_VCIE3_ETRE_Msk       (0x10000000UL) /*!< ETRE (Bitfield-Mask: 0x01)                            */
/* =========================================================  VCIE4  ========================================================= */
 #define R_MIPI_CSI_VCIE4_MLFE_Pos       (0UL)          /*!< MLFE (Bit 0)                                          */
 #define R_MIPI_CSI_VCIE4_MLFE_Msk       (0x1UL)        /*!< MLFE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE4_ECDE_Pos       (1UL)          /*!< ECDE (Bit 1)                                          */
 #define R_MIPI_CSI_VCIE4_ECDE_Msk       (0x2UL)        /*!< ECDE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE4_CRCE_Pos       (2UL)          /*!< CRCE (Bit 2)                                          */
 #define R_MIPI_CSI_VCIE4_CRCE_Msk       (0x4UL)        /*!< CRCE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE4_IDEE_Pos       (3UL)          /*!< IDEE (Bit 3)                                          */
 #define R_MIPI_CSI_VCIE4_IDEE_Msk       (0x8UL)        /*!< IDEE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE4_WCEE_Pos       (4UL)          /*!< WCEE (Bit 4)                                          */
 #define R_MIPI_CSI_VCIE4_WCEE_Msk       (0x10UL)       /*!< WCEE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE4_ECCE_Pos       (5UL)          /*!< ECCE (Bit 5)                                          */
 #define R_MIPI_CSI_VCIE4_ECCE_Msk       (0x20UL)       /*!< ECCE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE4_ECNE_Pos       (6UL)          /*!< ECNE (Bit 6)                                          */
 #define R_MIPI_CSI_VCIE4_ECNE_Msk       (0x40UL)       /*!< ECNE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE4_FRSE_Pos       (8UL)          /*!< FRSE (Bit 8)                                          */
 #define R_MIPI_CSI_VCIE4_FRSE_Msk       (0x100UL)      /*!< FRSE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE4_FRDE_Pos       (9UL)          /*!< FRDE (Bit 9)                                          */
 #define R_MIPI_CSI_VCIE4_FRDE_Msk       (0x200UL)      /*!< FRDE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE4_OVFE_Pos       (16UL)         /*!< OVFE (Bit 16)                                         */
 #define R_MIPI_CSI_VCIE4_OVFE_Msk       (0x10000UL)    /*!< OVFE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE4_FSRE_Pos       (24UL)         /*!< FSRE (Bit 24)                                         */
 #define R_MIPI_CSI_VCIE4_FSRE_Msk       (0x1000000UL)  /*!< FSRE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE4_FERE_Pos       (25UL)         /*!< FERE (Bit 25)                                         */
 #define R_MIPI_CSI_VCIE4_FERE_Msk       (0x2000000UL)  /*!< FERE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE4_LSRE_Pos       (26UL)         /*!< LSRE (Bit 26)                                         */
 #define R_MIPI_CSI_VCIE4_LSRE_Msk       (0x4000000UL)  /*!< LSRE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE4_LERE_Pos       (27UL)         /*!< LERE (Bit 27)                                         */
 #define R_MIPI_CSI_VCIE4_LERE_Msk       (0x8000000UL)  /*!< LERE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE4_ETRE_Pos       (28UL)         /*!< ETRE (Bit 28)                                         */
 #define R_MIPI_CSI_VCIE4_ETRE_Msk       (0x10000000UL) /*!< ETRE (Bitfield-Mask: 0x01)                            */
/* =========================================================  VCIE5  ========================================================= */
 #define R_MIPI_CSI_VCIE5_MLFE_Pos       (0UL)          /*!< MLFE (Bit 0)                                          */
 #define R_MIPI_CSI_VCIE5_MLFE_Msk       (0x1UL)        /*!< MLFE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE5_ECDE_Pos       (1UL)          /*!< ECDE (Bit 1)                                          */
 #define R_MIPI_CSI_VCIE5_ECDE_Msk       (0x2UL)        /*!< ECDE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE5_CRCE_Pos       (2UL)          /*!< CRCE (Bit 2)                                          */
 #define R_MIPI_CSI_VCIE5_CRCE_Msk       (0x4UL)        /*!< CRCE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE5_IDEE_Pos       (3UL)          /*!< IDEE (Bit 3)                                          */
 #define R_MIPI_CSI_VCIE5_IDEE_Msk       (0x8UL)        /*!< IDEE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE5_WCEE_Pos       (4UL)          /*!< WCEE (Bit 4)                                          */
 #define R_MIPI_CSI_VCIE5_WCEE_Msk       (0x10UL)       /*!< WCEE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE5_ECCE_Pos       (5UL)          /*!< ECCE (Bit 5)                                          */
 #define R_MIPI_CSI_VCIE5_ECCE_Msk       (0x20UL)       /*!< ECCE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE5_ECNE_Pos       (6UL)          /*!< ECNE (Bit 6)                                          */
 #define R_MIPI_CSI_VCIE5_ECNE_Msk       (0x40UL)       /*!< ECNE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE5_FRSE_Pos       (8UL)          /*!< FRSE (Bit 8)                                          */
 #define R_MIPI_CSI_VCIE5_FRSE_Msk       (0x100UL)      /*!< FRSE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE5_FRDE_Pos       (9UL)          /*!< FRDE (Bit 9)                                          */
 #define R_MIPI_CSI_VCIE5_FRDE_Msk       (0x200UL)      /*!< FRDE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE5_OVFE_Pos       (16UL)         /*!< OVFE (Bit 16)                                         */
 #define R_MIPI_CSI_VCIE5_OVFE_Msk       (0x10000UL)    /*!< OVFE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE5_FSRE_Pos       (24UL)         /*!< FSRE (Bit 24)                                         */
 #define R_MIPI_CSI_VCIE5_FSRE_Msk       (0x1000000UL)  /*!< FSRE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE5_FERE_Pos       (25UL)         /*!< FERE (Bit 25)                                         */
 #define R_MIPI_CSI_VCIE5_FERE_Msk       (0x2000000UL)  /*!< FERE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE5_LSRE_Pos       (26UL)         /*!< LSRE (Bit 26)                                         */
 #define R_MIPI_CSI_VCIE5_LSRE_Msk       (0x4000000UL)  /*!< LSRE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE5_LERE_Pos       (27UL)         /*!< LERE (Bit 27)                                         */
 #define R_MIPI_CSI_VCIE5_LERE_Msk       (0x8000000UL)  /*!< LERE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE5_ETRE_Pos       (28UL)         /*!< ETRE (Bit 28)                                         */
 #define R_MIPI_CSI_VCIE5_ETRE_Msk       (0x10000000UL) /*!< ETRE (Bitfield-Mask: 0x01)                            */
/* =========================================================  VCIE6  ========================================================= */
 #define R_MIPI_CSI_VCIE6_MLFE_Pos       (0UL)          /*!< MLFE (Bit 0)                                          */
 #define R_MIPI_CSI_VCIE6_MLFE_Msk       (0x1UL)        /*!< MLFE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE6_ECDE_Pos       (1UL)          /*!< ECDE (Bit 1)                                          */
 #define R_MIPI_CSI_VCIE6_ECDE_Msk       (0x2UL)        /*!< ECDE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE6_CRCE_Pos       (2UL)          /*!< CRCE (Bit 2)                                          */
 #define R_MIPI_CSI_VCIE6_CRCE_Msk       (0x4UL)        /*!< CRCE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE6_IDEE_Pos       (3UL)          /*!< IDEE (Bit 3)                                          */
 #define R_MIPI_CSI_VCIE6_IDEE_Msk       (0x8UL)        /*!< IDEE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE6_WCEE_Pos       (4UL)          /*!< WCEE (Bit 4)                                          */
 #define R_MIPI_CSI_VCIE6_WCEE_Msk       (0x10UL)       /*!< WCEE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE6_ECCE_Pos       (5UL)          /*!< ECCE (Bit 5)                                          */
 #define R_MIPI_CSI_VCIE6_ECCE_Msk       (0x20UL)       /*!< ECCE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE6_ECNE_Pos       (6UL)          /*!< ECNE (Bit 6)                                          */
 #define R_MIPI_CSI_VCIE6_ECNE_Msk       (0x40UL)       /*!< ECNE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE6_FRSE_Pos       (8UL)          /*!< FRSE (Bit 8)                                          */
 #define R_MIPI_CSI_VCIE6_FRSE_Msk       (0x100UL)      /*!< FRSE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE6_FRDE_Pos       (9UL)          /*!< FRDE (Bit 9)                                          */
 #define R_MIPI_CSI_VCIE6_FRDE_Msk       (0x200UL)      /*!< FRDE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE6_OVFE_Pos       (16UL)         /*!< OVFE (Bit 16)                                         */
 #define R_MIPI_CSI_VCIE6_OVFE_Msk       (0x10000UL)    /*!< OVFE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE6_FSRE_Pos       (24UL)         /*!< FSRE (Bit 24)                                         */
 #define R_MIPI_CSI_VCIE6_FSRE_Msk       (0x1000000UL)  /*!< FSRE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE6_FERE_Pos       (25UL)         /*!< FERE (Bit 25)                                         */
 #define R_MIPI_CSI_VCIE6_FERE_Msk       (0x2000000UL)  /*!< FERE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE6_LSRE_Pos       (26UL)         /*!< LSRE (Bit 26)                                         */
 #define R_MIPI_CSI_VCIE6_LSRE_Msk       (0x4000000UL)  /*!< LSRE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE6_LERE_Pos       (27UL)         /*!< LERE (Bit 27)                                         */
 #define R_MIPI_CSI_VCIE6_LERE_Msk       (0x8000000UL)  /*!< LERE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE6_ETRE_Pos       (28UL)         /*!< ETRE (Bit 28)                                         */
 #define R_MIPI_CSI_VCIE6_ETRE_Msk       (0x10000000UL) /*!< ETRE (Bitfield-Mask: 0x01)                            */
/* =========================================================  VCIE7  ========================================================= */
 #define R_MIPI_CSI_VCIE7_MLFE_Pos       (0UL)          /*!< MLFE (Bit 0)                                          */
 #define R_MIPI_CSI_VCIE7_MLFE_Msk       (0x1UL)        /*!< MLFE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE7_ECDE_Pos       (1UL)          /*!< ECDE (Bit 1)                                          */
 #define R_MIPI_CSI_VCIE7_ECDE_Msk       (0x2UL)        /*!< ECDE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE7_CRCE_Pos       (2UL)          /*!< CRCE (Bit 2)                                          */
 #define R_MIPI_CSI_VCIE7_CRCE_Msk       (0x4UL)        /*!< CRCE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE7_IDEE_Pos       (3UL)          /*!< IDEE (Bit 3)                                          */
 #define R_MIPI_CSI_VCIE7_IDEE_Msk       (0x8UL)        /*!< IDEE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE7_WCEE_Pos       (4UL)          /*!< WCEE (Bit 4)                                          */
 #define R_MIPI_CSI_VCIE7_WCEE_Msk       (0x10UL)       /*!< WCEE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE7_ECCE_Pos       (5UL)          /*!< ECCE (Bit 5)                                          */
 #define R_MIPI_CSI_VCIE7_ECCE_Msk       (0x20UL)       /*!< ECCE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE7_ECNE_Pos       (6UL)          /*!< ECNE (Bit 6)                                          */
 #define R_MIPI_CSI_VCIE7_ECNE_Msk       (0x40UL)       /*!< ECNE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE7_FRSE_Pos       (8UL)          /*!< FRSE (Bit 8)                                          */
 #define R_MIPI_CSI_VCIE7_FRSE_Msk       (0x100UL)      /*!< FRSE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE7_FRDE_Pos       (9UL)          /*!< FRDE (Bit 9)                                          */
 #define R_MIPI_CSI_VCIE7_FRDE_Msk       (0x200UL)      /*!< FRDE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE7_OVFE_Pos       (16UL)         /*!< OVFE (Bit 16)                                         */
 #define R_MIPI_CSI_VCIE7_OVFE_Msk       (0x10000UL)    /*!< OVFE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE7_FSRE_Pos       (24UL)         /*!< FSRE (Bit 24)                                         */
 #define R_MIPI_CSI_VCIE7_FSRE_Msk       (0x1000000UL)  /*!< FSRE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE7_FERE_Pos       (25UL)         /*!< FERE (Bit 25)                                         */
 #define R_MIPI_CSI_VCIE7_FERE_Msk       (0x2000000UL)  /*!< FERE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE7_LSRE_Pos       (26UL)         /*!< LSRE (Bit 26)                                         */
 #define R_MIPI_CSI_VCIE7_LSRE_Msk       (0x4000000UL)  /*!< LSRE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE7_LERE_Pos       (27UL)         /*!< LERE (Bit 27)                                         */
 #define R_MIPI_CSI_VCIE7_LERE_Msk       (0x8000000UL)  /*!< LERE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE7_ETRE_Pos       (28UL)         /*!< ETRE (Bit 28)                                         */
 #define R_MIPI_CSI_VCIE7_ETRE_Msk       (0x10000000UL) /*!< ETRE (Bitfield-Mask: 0x01)                            */
/* =========================================================  VCIE8  ========================================================= */
 #define R_MIPI_CSI_VCIE8_MLFE_Pos       (0UL)          /*!< MLFE (Bit 0)                                          */
 #define R_MIPI_CSI_VCIE8_MLFE_Msk       (0x1UL)        /*!< MLFE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE8_ECDE_Pos       (1UL)          /*!< ECDE (Bit 1)                                          */
 #define R_MIPI_CSI_VCIE8_ECDE_Msk       (0x2UL)        /*!< ECDE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE8_CRCE_Pos       (2UL)          /*!< CRCE (Bit 2)                                          */
 #define R_MIPI_CSI_VCIE8_CRCE_Msk       (0x4UL)        /*!< CRCE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE8_IDEE_Pos       (3UL)          /*!< IDEE (Bit 3)                                          */
 #define R_MIPI_CSI_VCIE8_IDEE_Msk       (0x8UL)        /*!< IDEE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE8_WCEE_Pos       (4UL)          /*!< WCEE (Bit 4)                                          */
 #define R_MIPI_CSI_VCIE8_WCEE_Msk       (0x10UL)       /*!< WCEE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE8_ECCE_Pos       (5UL)          /*!< ECCE (Bit 5)                                          */
 #define R_MIPI_CSI_VCIE8_ECCE_Msk       (0x20UL)       /*!< ECCE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE8_ECNE_Pos       (6UL)          /*!< ECNE (Bit 6)                                          */
 #define R_MIPI_CSI_VCIE8_ECNE_Msk       (0x40UL)       /*!< ECNE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE8_FRSE_Pos       (8UL)          /*!< FRSE (Bit 8)                                          */
 #define R_MIPI_CSI_VCIE8_FRSE_Msk       (0x100UL)      /*!< FRSE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE8_FRDE_Pos       (9UL)          /*!< FRDE (Bit 9)                                          */
 #define R_MIPI_CSI_VCIE8_FRDE_Msk       (0x200UL)      /*!< FRDE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE8_OVFE_Pos       (16UL)         /*!< OVFE (Bit 16)                                         */
 #define R_MIPI_CSI_VCIE8_OVFE_Msk       (0x10000UL)    /*!< OVFE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE8_FSRE_Pos       (24UL)         /*!< FSRE (Bit 24)                                         */
 #define R_MIPI_CSI_VCIE8_FSRE_Msk       (0x1000000UL)  /*!< FSRE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE8_FERE_Pos       (25UL)         /*!< FERE (Bit 25)                                         */
 #define R_MIPI_CSI_VCIE8_FERE_Msk       (0x2000000UL)  /*!< FERE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE8_LSRE_Pos       (26UL)         /*!< LSRE (Bit 26)                                         */
 #define R_MIPI_CSI_VCIE8_LSRE_Msk       (0x4000000UL)  /*!< LSRE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE8_LERE_Pos       (27UL)         /*!< LERE (Bit 27)                                         */
 #define R_MIPI_CSI_VCIE8_LERE_Msk       (0x8000000UL)  /*!< LERE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE8_ETRE_Pos       (28UL)         /*!< ETRE (Bit 28)                                         */
 #define R_MIPI_CSI_VCIE8_ETRE_Msk       (0x10000000UL) /*!< ETRE (Bitfield-Mask: 0x01)                            */
/* =========================================================  VCIE9  ========================================================= */
 #define R_MIPI_CSI_VCIE9_MLFE_Pos       (0UL)          /*!< MLFE (Bit 0)                                          */
 #define R_MIPI_CSI_VCIE9_MLFE_Msk       (0x1UL)        /*!< MLFE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE9_ECDE_Pos       (1UL)          /*!< ECDE (Bit 1)                                          */
 #define R_MIPI_CSI_VCIE9_ECDE_Msk       (0x2UL)        /*!< ECDE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE9_CRCE_Pos       (2UL)          /*!< CRCE (Bit 2)                                          */
 #define R_MIPI_CSI_VCIE9_CRCE_Msk       (0x4UL)        /*!< CRCE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE9_IDEE_Pos       (3UL)          /*!< IDEE (Bit 3)                                          */
 #define R_MIPI_CSI_VCIE9_IDEE_Msk       (0x8UL)        /*!< IDEE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE9_WCEE_Pos       (4UL)          /*!< WCEE (Bit 4)                                          */
 #define R_MIPI_CSI_VCIE9_WCEE_Msk       (0x10UL)       /*!< WCEE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE9_ECCE_Pos       (5UL)          /*!< ECCE (Bit 5)                                          */
 #define R_MIPI_CSI_VCIE9_ECCE_Msk       (0x20UL)       /*!< ECCE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE9_ECNE_Pos       (6UL)          /*!< ECNE (Bit 6)                                          */
 #define R_MIPI_CSI_VCIE9_ECNE_Msk       (0x40UL)       /*!< ECNE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE9_FRSE_Pos       (8UL)          /*!< FRSE (Bit 8)                                          */
 #define R_MIPI_CSI_VCIE9_FRSE_Msk       (0x100UL)      /*!< FRSE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE9_FRDE_Pos       (9UL)          /*!< FRDE (Bit 9)                                          */
 #define R_MIPI_CSI_VCIE9_FRDE_Msk       (0x200UL)      /*!< FRDE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE9_OVFE_Pos       (16UL)         /*!< OVFE (Bit 16)                                         */
 #define R_MIPI_CSI_VCIE9_OVFE_Msk       (0x10000UL)    /*!< OVFE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE9_FSRE_Pos       (24UL)         /*!< FSRE (Bit 24)                                         */
 #define R_MIPI_CSI_VCIE9_FSRE_Msk       (0x1000000UL)  /*!< FSRE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE9_FERE_Pos       (25UL)         /*!< FERE (Bit 25)                                         */
 #define R_MIPI_CSI_VCIE9_FERE_Msk       (0x2000000UL)  /*!< FERE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE9_LSRE_Pos       (26UL)         /*!< LSRE (Bit 26)                                         */
 #define R_MIPI_CSI_VCIE9_LSRE_Msk       (0x4000000UL)  /*!< LSRE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE9_LERE_Pos       (27UL)         /*!< LERE (Bit 27)                                         */
 #define R_MIPI_CSI_VCIE9_LERE_Msk       (0x8000000UL)  /*!< LERE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE9_ETRE_Pos       (28UL)         /*!< ETRE (Bit 28)                                         */
 #define R_MIPI_CSI_VCIE9_ETRE_Msk       (0x10000000UL) /*!< ETRE (Bitfield-Mask: 0x01)                            */
/* ========================================================  VCIE10  ========================================================= */
 #define R_MIPI_CSI_VCIE10_MLFE_Pos      (0UL)          /*!< MLFE (Bit 0)                                          */
 #define R_MIPI_CSI_VCIE10_MLFE_Msk      (0x1UL)        /*!< MLFE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE10_ECDE_Pos      (1UL)          /*!< ECDE (Bit 1)                                          */
 #define R_MIPI_CSI_VCIE10_ECDE_Msk      (0x2UL)        /*!< ECDE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE10_CRCE_Pos      (2UL)          /*!< CRCE (Bit 2)                                          */
 #define R_MIPI_CSI_VCIE10_CRCE_Msk      (0x4UL)        /*!< CRCE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE10_IDEE_Pos      (3UL)          /*!< IDEE (Bit 3)                                          */
 #define R_MIPI_CSI_VCIE10_IDEE_Msk      (0x8UL)        /*!< IDEE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE10_WCEE_Pos      (4UL)          /*!< WCEE (Bit 4)                                          */
 #define R_MIPI_CSI_VCIE10_WCEE_Msk      (0x10UL)       /*!< WCEE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE10_ECCE_Pos      (5UL)          /*!< ECCE (Bit 5)                                          */
 #define R_MIPI_CSI_VCIE10_ECCE_Msk      (0x20UL)       /*!< ECCE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE10_ECNE_Pos      (6UL)          /*!< ECNE (Bit 6)                                          */
 #define R_MIPI_CSI_VCIE10_ECNE_Msk      (0x40UL)       /*!< ECNE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE10_FRSE_Pos      (8UL)          /*!< FRSE (Bit 8)                                          */
 #define R_MIPI_CSI_VCIE10_FRSE_Msk      (0x100UL)      /*!< FRSE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE10_FRDE_Pos      (9UL)          /*!< FRDE (Bit 9)                                          */
 #define R_MIPI_CSI_VCIE10_FRDE_Msk      (0x200UL)      /*!< FRDE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE10_OVFE_Pos      (16UL)         /*!< OVFE (Bit 16)                                         */
 #define R_MIPI_CSI_VCIE10_OVFE_Msk      (0x10000UL)    /*!< OVFE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE10_FSRE_Pos      (24UL)         /*!< FSRE (Bit 24)                                         */
 #define R_MIPI_CSI_VCIE10_FSRE_Msk      (0x1000000UL)  /*!< FSRE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE10_FERE_Pos      (25UL)         /*!< FERE (Bit 25)                                         */
 #define R_MIPI_CSI_VCIE10_FERE_Msk      (0x2000000UL)  /*!< FERE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE10_LSRE_Pos      (26UL)         /*!< LSRE (Bit 26)                                         */
 #define R_MIPI_CSI_VCIE10_LSRE_Msk      (0x4000000UL)  /*!< LSRE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE10_LERE_Pos      (27UL)         /*!< LERE (Bit 27)                                         */
 #define R_MIPI_CSI_VCIE10_LERE_Msk      (0x8000000UL)  /*!< LERE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE10_ETRE_Pos      (28UL)         /*!< ETRE (Bit 28)                                         */
 #define R_MIPI_CSI_VCIE10_ETRE_Msk      (0x10000000UL) /*!< ETRE (Bitfield-Mask: 0x01)                            */
/* ========================================================  VCIE11  ========================================================= */
 #define R_MIPI_CSI_VCIE11_MLFE_Pos      (0UL)          /*!< MLFE (Bit 0)                                          */
 #define R_MIPI_CSI_VCIE11_MLFE_Msk      (0x1UL)        /*!< MLFE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE11_ECDE_Pos      (1UL)          /*!< ECDE (Bit 1)                                          */
 #define R_MIPI_CSI_VCIE11_ECDE_Msk      (0x2UL)        /*!< ECDE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE11_CRCE_Pos      (2UL)          /*!< CRCE (Bit 2)                                          */
 #define R_MIPI_CSI_VCIE11_CRCE_Msk      (0x4UL)        /*!< CRCE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE11_IDEE_Pos      (3UL)          /*!< IDEE (Bit 3)                                          */
 #define R_MIPI_CSI_VCIE11_IDEE_Msk      (0x8UL)        /*!< IDEE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE11_WCEE_Pos      (4UL)          /*!< WCEE (Bit 4)                                          */
 #define R_MIPI_CSI_VCIE11_WCEE_Msk      (0x10UL)       /*!< WCEE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE11_ECCE_Pos      (5UL)          /*!< ECCE (Bit 5)                                          */
 #define R_MIPI_CSI_VCIE11_ECCE_Msk      (0x20UL)       /*!< ECCE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE11_ECNE_Pos      (6UL)          /*!< ECNE (Bit 6)                                          */
 #define R_MIPI_CSI_VCIE11_ECNE_Msk      (0x40UL)       /*!< ECNE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE11_FRSE_Pos      (8UL)          /*!< FRSE (Bit 8)                                          */
 #define R_MIPI_CSI_VCIE11_FRSE_Msk      (0x100UL)      /*!< FRSE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE11_FRDE_Pos      (9UL)          /*!< FRDE (Bit 9)                                          */
 #define R_MIPI_CSI_VCIE11_FRDE_Msk      (0x200UL)      /*!< FRDE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE11_OVFE_Pos      (16UL)         /*!< OVFE (Bit 16)                                         */
 #define R_MIPI_CSI_VCIE11_OVFE_Msk      (0x10000UL)    /*!< OVFE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE11_FSRE_Pos      (24UL)         /*!< FSRE (Bit 24)                                         */
 #define R_MIPI_CSI_VCIE11_FSRE_Msk      (0x1000000UL)  /*!< FSRE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE11_FERE_Pos      (25UL)         /*!< FERE (Bit 25)                                         */
 #define R_MIPI_CSI_VCIE11_FERE_Msk      (0x2000000UL)  /*!< FERE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE11_LSRE_Pos      (26UL)         /*!< LSRE (Bit 26)                                         */
 #define R_MIPI_CSI_VCIE11_LSRE_Msk      (0x4000000UL)  /*!< LSRE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE11_LERE_Pos      (27UL)         /*!< LERE (Bit 27)                                         */
 #define R_MIPI_CSI_VCIE11_LERE_Msk      (0x8000000UL)  /*!< LERE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE11_ETRE_Pos      (28UL)         /*!< ETRE (Bit 28)                                         */
 #define R_MIPI_CSI_VCIE11_ETRE_Msk      (0x10000000UL) /*!< ETRE (Bitfield-Mask: 0x01)                            */
/* ========================================================  VCIE12  ========================================================= */
 #define R_MIPI_CSI_VCIE12_MLFE_Pos      (0UL)          /*!< MLFE (Bit 0)                                          */
 #define R_MIPI_CSI_VCIE12_MLFE_Msk      (0x1UL)        /*!< MLFE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE12_ECDE_Pos      (1UL)          /*!< ECDE (Bit 1)                                          */
 #define R_MIPI_CSI_VCIE12_ECDE_Msk      (0x2UL)        /*!< ECDE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE12_CRCE_Pos      (2UL)          /*!< CRCE (Bit 2)                                          */
 #define R_MIPI_CSI_VCIE12_CRCE_Msk      (0x4UL)        /*!< CRCE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE12_IDEE_Pos      (3UL)          /*!< IDEE (Bit 3)                                          */
 #define R_MIPI_CSI_VCIE12_IDEE_Msk      (0x8UL)        /*!< IDEE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE12_WCEE_Pos      (4UL)          /*!< WCEE (Bit 4)                                          */
 #define R_MIPI_CSI_VCIE12_WCEE_Msk      (0x10UL)       /*!< WCEE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE12_ECCE_Pos      (5UL)          /*!< ECCE (Bit 5)                                          */
 #define R_MIPI_CSI_VCIE12_ECCE_Msk      (0x20UL)       /*!< ECCE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE12_ECNE_Pos      (6UL)          /*!< ECNE (Bit 6)                                          */
 #define R_MIPI_CSI_VCIE12_ECNE_Msk      (0x40UL)       /*!< ECNE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE12_FRSE_Pos      (8UL)          /*!< FRSE (Bit 8)                                          */
 #define R_MIPI_CSI_VCIE12_FRSE_Msk      (0x100UL)      /*!< FRSE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE12_FRDE_Pos      (9UL)          /*!< FRDE (Bit 9)                                          */
 #define R_MIPI_CSI_VCIE12_FRDE_Msk      (0x200UL)      /*!< FRDE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE12_OVFE_Pos      (16UL)         /*!< OVFE (Bit 16)                                         */
 #define R_MIPI_CSI_VCIE12_OVFE_Msk      (0x10000UL)    /*!< OVFE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE12_FSRE_Pos      (24UL)         /*!< FSRE (Bit 24)                                         */
 #define R_MIPI_CSI_VCIE12_FSRE_Msk      (0x1000000UL)  /*!< FSRE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE12_FERE_Pos      (25UL)         /*!< FERE (Bit 25)                                         */
 #define R_MIPI_CSI_VCIE12_FERE_Msk      (0x2000000UL)  /*!< FERE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE12_LSRE_Pos      (26UL)         /*!< LSRE (Bit 26)                                         */
 #define R_MIPI_CSI_VCIE12_LSRE_Msk      (0x4000000UL)  /*!< LSRE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE12_LERE_Pos      (27UL)         /*!< LERE (Bit 27)                                         */
 #define R_MIPI_CSI_VCIE12_LERE_Msk      (0x8000000UL)  /*!< LERE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE12_ETRE_Pos      (28UL)         /*!< ETRE (Bit 28)                                         */
 #define R_MIPI_CSI_VCIE12_ETRE_Msk      (0x10000000UL) /*!< ETRE (Bitfield-Mask: 0x01)                            */
/* ========================================================  VCIE13  ========================================================= */
 #define R_MIPI_CSI_VCIE13_MLFE_Pos      (0UL)          /*!< MLFE (Bit 0)                                          */
 #define R_MIPI_CSI_VCIE13_MLFE_Msk      (0x1UL)        /*!< MLFE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE13_ECDE_Pos      (1UL)          /*!< ECDE (Bit 1)                                          */
 #define R_MIPI_CSI_VCIE13_ECDE_Msk      (0x2UL)        /*!< ECDE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE13_CRCE_Pos      (2UL)          /*!< CRCE (Bit 2)                                          */
 #define R_MIPI_CSI_VCIE13_CRCE_Msk      (0x4UL)        /*!< CRCE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE13_IDEE_Pos      (3UL)          /*!< IDEE (Bit 3)                                          */
 #define R_MIPI_CSI_VCIE13_IDEE_Msk      (0x8UL)        /*!< IDEE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE13_WCEE_Pos      (4UL)          /*!< WCEE (Bit 4)                                          */
 #define R_MIPI_CSI_VCIE13_WCEE_Msk      (0x10UL)       /*!< WCEE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE13_ECCE_Pos      (5UL)          /*!< ECCE (Bit 5)                                          */
 #define R_MIPI_CSI_VCIE13_ECCE_Msk      (0x20UL)       /*!< ECCE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE13_ECNE_Pos      (6UL)          /*!< ECNE (Bit 6)                                          */
 #define R_MIPI_CSI_VCIE13_ECNE_Msk      (0x40UL)       /*!< ECNE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE13_FRSE_Pos      (8UL)          /*!< FRSE (Bit 8)                                          */
 #define R_MIPI_CSI_VCIE13_FRSE_Msk      (0x100UL)      /*!< FRSE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE13_FRDE_Pos      (9UL)          /*!< FRDE (Bit 9)                                          */
 #define R_MIPI_CSI_VCIE13_FRDE_Msk      (0x200UL)      /*!< FRDE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE13_OVFE_Pos      (16UL)         /*!< OVFE (Bit 16)                                         */
 #define R_MIPI_CSI_VCIE13_OVFE_Msk      (0x10000UL)    /*!< OVFE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE13_FSRE_Pos      (24UL)         /*!< FSRE (Bit 24)                                         */
 #define R_MIPI_CSI_VCIE13_FSRE_Msk      (0x1000000UL)  /*!< FSRE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE13_FERE_Pos      (25UL)         /*!< FERE (Bit 25)                                         */
 #define R_MIPI_CSI_VCIE13_FERE_Msk      (0x2000000UL)  /*!< FERE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE13_LSRE_Pos      (26UL)         /*!< LSRE (Bit 26)                                         */
 #define R_MIPI_CSI_VCIE13_LSRE_Msk      (0x4000000UL)  /*!< LSRE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE13_LERE_Pos      (27UL)         /*!< LERE (Bit 27)                                         */
 #define R_MIPI_CSI_VCIE13_LERE_Msk      (0x8000000UL)  /*!< LERE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE13_ETRE_Pos      (28UL)         /*!< ETRE (Bit 28)                                         */
 #define R_MIPI_CSI_VCIE13_ETRE_Msk      (0x10000000UL) /*!< ETRE (Bitfield-Mask: 0x01)                            */
/* ========================================================  VCIE14  ========================================================= */
 #define R_MIPI_CSI_VCIE14_MLFE_Pos      (0UL)          /*!< MLFE (Bit 0)                                          */
 #define R_MIPI_CSI_VCIE14_MLFE_Msk      (0x1UL)        /*!< MLFE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE14_ECDE_Pos      (1UL)          /*!< ECDE (Bit 1)                                          */
 #define R_MIPI_CSI_VCIE14_ECDE_Msk      (0x2UL)        /*!< ECDE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE14_CRCE_Pos      (2UL)          /*!< CRCE (Bit 2)                                          */
 #define R_MIPI_CSI_VCIE14_CRCE_Msk      (0x4UL)        /*!< CRCE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE14_IDEE_Pos      (3UL)          /*!< IDEE (Bit 3)                                          */
 #define R_MIPI_CSI_VCIE14_IDEE_Msk      (0x8UL)        /*!< IDEE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE14_WCEE_Pos      (4UL)          /*!< WCEE (Bit 4)                                          */
 #define R_MIPI_CSI_VCIE14_WCEE_Msk      (0x10UL)       /*!< WCEE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE14_ECCE_Pos      (5UL)          /*!< ECCE (Bit 5)                                          */
 #define R_MIPI_CSI_VCIE14_ECCE_Msk      (0x20UL)       /*!< ECCE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE14_ECNE_Pos      (6UL)          /*!< ECNE (Bit 6)                                          */
 #define R_MIPI_CSI_VCIE14_ECNE_Msk      (0x40UL)       /*!< ECNE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE14_FRSE_Pos      (8UL)          /*!< FRSE (Bit 8)                                          */
 #define R_MIPI_CSI_VCIE14_FRSE_Msk      (0x100UL)      /*!< FRSE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE14_FRDE_Pos      (9UL)          /*!< FRDE (Bit 9)                                          */
 #define R_MIPI_CSI_VCIE14_FRDE_Msk      (0x200UL)      /*!< FRDE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE14_OVFE_Pos      (16UL)         /*!< OVFE (Bit 16)                                         */
 #define R_MIPI_CSI_VCIE14_OVFE_Msk      (0x10000UL)    /*!< OVFE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE14_FSRE_Pos      (24UL)         /*!< FSRE (Bit 24)                                         */
 #define R_MIPI_CSI_VCIE14_FSRE_Msk      (0x1000000UL)  /*!< FSRE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE14_FERE_Pos      (25UL)         /*!< FERE (Bit 25)                                         */
 #define R_MIPI_CSI_VCIE14_FERE_Msk      (0x2000000UL)  /*!< FERE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE14_LSRE_Pos      (26UL)         /*!< LSRE (Bit 26)                                         */
 #define R_MIPI_CSI_VCIE14_LSRE_Msk      (0x4000000UL)  /*!< LSRE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE14_LERE_Pos      (27UL)         /*!< LERE (Bit 27)                                         */
 #define R_MIPI_CSI_VCIE14_LERE_Msk      (0x8000000UL)  /*!< LERE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE14_ETRE_Pos      (28UL)         /*!< ETRE (Bit 28)                                         */
 #define R_MIPI_CSI_VCIE14_ETRE_Msk      (0x10000000UL) /*!< ETRE (Bitfield-Mask: 0x01)                            */
/* ========================================================  VCIE15  ========================================================= */
 #define R_MIPI_CSI_VCIE15_MLFE_Pos      (0UL)          /*!< MLFE (Bit 0)                                          */
 #define R_MIPI_CSI_VCIE15_MLFE_Msk      (0x1UL)        /*!< MLFE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE15_ECDE_Pos      (1UL)          /*!< ECDE (Bit 1)                                          */
 #define R_MIPI_CSI_VCIE15_ECDE_Msk      (0x2UL)        /*!< ECDE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE15_CRCE_Pos      (2UL)          /*!< CRCE (Bit 2)                                          */
 #define R_MIPI_CSI_VCIE15_CRCE_Msk      (0x4UL)        /*!< CRCE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE15_IDEE_Pos      (3UL)          /*!< IDEE (Bit 3)                                          */
 #define R_MIPI_CSI_VCIE15_IDEE_Msk      (0x8UL)        /*!< IDEE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE15_WCEE_Pos      (4UL)          /*!< WCEE (Bit 4)                                          */
 #define R_MIPI_CSI_VCIE15_WCEE_Msk      (0x10UL)       /*!< WCEE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE15_ECCE_Pos      (5UL)          /*!< ECCE (Bit 5)                                          */
 #define R_MIPI_CSI_VCIE15_ECCE_Msk      (0x20UL)       /*!< ECCE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE15_ECNE_Pos      (6UL)          /*!< ECNE (Bit 6)                                          */
 #define R_MIPI_CSI_VCIE15_ECNE_Msk      (0x40UL)       /*!< ECNE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE15_FRSE_Pos      (8UL)          /*!< FRSE (Bit 8)                                          */
 #define R_MIPI_CSI_VCIE15_FRSE_Msk      (0x100UL)      /*!< FRSE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE15_FRDE_Pos      (9UL)          /*!< FRDE (Bit 9)                                          */
 #define R_MIPI_CSI_VCIE15_FRDE_Msk      (0x200UL)      /*!< FRDE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE15_OVFE_Pos      (16UL)         /*!< OVFE (Bit 16)                                         */
 #define R_MIPI_CSI_VCIE15_OVFE_Msk      (0x10000UL)    /*!< OVFE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE15_FSRE_Pos      (24UL)         /*!< FSRE (Bit 24)                                         */
 #define R_MIPI_CSI_VCIE15_FSRE_Msk      (0x1000000UL)  /*!< FSRE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE15_FERE_Pos      (25UL)         /*!< FERE (Bit 25)                                         */
 #define R_MIPI_CSI_VCIE15_FERE_Msk      (0x2000000UL)  /*!< FERE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE15_LSRE_Pos      (26UL)         /*!< LSRE (Bit 26)                                         */
 #define R_MIPI_CSI_VCIE15_LSRE_Msk      (0x4000000UL)  /*!< LSRE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE15_LERE_Pos      (27UL)         /*!< LERE (Bit 27)                                         */
 #define R_MIPI_CSI_VCIE15_LERE_Msk      (0x8000000UL)  /*!< LERE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_VCIE15_ETRE_Pos      (28UL)         /*!< ETRE (Bit 28)                                         */
 #define R_MIPI_CSI_VCIE15_ETRE_Msk      (0x10000000UL) /*!< ETRE (Bitfield-Mask: 0x01)                            */
/* =========================================================  PMST  ========================================================== */
 #define R_MIPI_CSI_PMST_DSX_Pos         (0UL)          /*!< DSX (Bit 0)                                           */
 #define R_MIPI_CSI_PMST_DSX_Msk         (0x1UL)        /*!< DSX (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_PMST_DSN_Pos         (1UL)          /*!< DSN (Bit 1)                                           */
 #define R_MIPI_CSI_PMST_DSN_Msk         (0x2UL)        /*!< DSN (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_PMST_CSX_Pos         (2UL)          /*!< CSX (Bit 2)                                           */
 #define R_MIPI_CSI_PMST_CSX_Msk         (0x4UL)        /*!< CSX (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_PMST_CSN_Pos         (3UL)          /*!< CSN (Bit 3)                                           */
 #define R_MIPI_CSI_PMST_CSN_Msk         (0x8UL)        /*!< CSN (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_PMST_DUX_Pos         (4UL)          /*!< DUX (Bit 4)                                           */
 #define R_MIPI_CSI_PMST_DUX_Msk         (0x10UL)       /*!< DUX (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_PMST_DUN_Pos         (5UL)          /*!< DUN (Bit 5)                                           */
 #define R_MIPI_CSI_PMST_DUN_Msk         (0x20UL)       /*!< DUN (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_PMST_CUX_Pos         (6UL)          /*!< CUX (Bit 6)                                           */
 #define R_MIPI_CSI_PMST_CUX_Msk         (0x40UL)       /*!< CUX (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_PMST_CUN_Pos         (7UL)          /*!< CUN (Bit 7)                                           */
 #define R_MIPI_CSI_PMST_CUN_Msk         (0x80UL)       /*!< CUN (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_PMST_CLSS_Pos        (14UL)         /*!< CLSS (Bit 14)                                         */
 #define R_MIPI_CSI_PMST_CLSS_Msk        (0x4000UL)     /*!< CLSS (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_PMST_CLUL_Pos        (15UL)         /*!< CLUL (Bit 15)                                         */
 #define R_MIPI_CSI_PMST_CLUL_Msk        (0x8000UL)     /*!< CLUL (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_PMST_DLSS_Pos        (16UL)         /*!< DLSS (Bit 16)                                         */
 #define R_MIPI_CSI_PMST_DLSS_Msk        (0x30000UL)    /*!< DLSS (Bitfield-Mask: 0x03)                            */
 #define R_MIPI_CSI_PMST_DLUL_Pos        (24UL)         /*!< DLUL (Bit 24)                                         */
 #define R_MIPI_CSI_PMST_DLUL_Msk        (0x3000000UL)  /*!< DLUL (Bitfield-Mask: 0x03)                            */
/* =========================================================  PMSC  ========================================================== */
 #define R_MIPI_CSI_PMSC_DSXC_Pos        (0UL)          /*!< DSXC (Bit 0)                                          */
 #define R_MIPI_CSI_PMSC_DSXC_Msk        (0x1UL)        /*!< DSXC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_PMSC_DSNC_Pos        (1UL)          /*!< DSNC (Bit 1)                                          */
 #define R_MIPI_CSI_PMSC_DSNC_Msk        (0x2UL)        /*!< DSNC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_PMSC_CSXC_Pos        (2UL)          /*!< CSXC (Bit 2)                                          */
 #define R_MIPI_CSI_PMSC_CSXC_Msk        (0x4UL)        /*!< CSXC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_PMSC_CSNC_Pos        (3UL)          /*!< CSNC (Bit 3)                                          */
 #define R_MIPI_CSI_PMSC_CSNC_Msk        (0x8UL)        /*!< CSNC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_PMSC_DUXC_Pos        (4UL)          /*!< DUXC (Bit 4)                                          */
 #define R_MIPI_CSI_PMSC_DUXC_Msk        (0x10UL)       /*!< DUXC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_PMSC_DUNC_Pos        (5UL)          /*!< DUNC (Bit 5)                                          */
 #define R_MIPI_CSI_PMSC_DUNC_Msk        (0x20UL)       /*!< DUNC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_PMSC_CUXC_Pos        (6UL)          /*!< CUXC (Bit 6)                                          */
 #define R_MIPI_CSI_PMSC_CUXC_Msk        (0x40UL)       /*!< CUXC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_PMSC_CUNC_Pos        (7UL)          /*!< CUNC (Bit 7)                                          */
 #define R_MIPI_CSI_PMSC_CUNC_Msk        (0x80UL)       /*!< CUNC (Bitfield-Mask: 0x01)                            */
/* =========================================================  PMIE  ========================================================== */
 #define R_MIPI_CSI_PMIE_DSXE_Pos        (0UL)          /*!< DSXE (Bit 0)                                          */
 #define R_MIPI_CSI_PMIE_DSXE_Msk        (0x1UL)        /*!< DSXE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_PMIE_DSNE_Pos        (1UL)          /*!< DSNE (Bit 1)                                          */
 #define R_MIPI_CSI_PMIE_DSNE_Msk        (0x2UL)        /*!< DSNE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_PMIE_CSXE_Pos        (2UL)          /*!< CSXE (Bit 2)                                          */
 #define R_MIPI_CSI_PMIE_CSXE_Msk        (0x4UL)        /*!< CSXE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_PMIE_CSNE_Pos        (3UL)          /*!< CSNE (Bit 3)                                          */
 #define R_MIPI_CSI_PMIE_CSNE_Msk        (0x8UL)        /*!< CSNE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_PMIE_DUXE_Pos        (4UL)          /*!< DUXE (Bit 4)                                          */
 #define R_MIPI_CSI_PMIE_DUXE_Msk        (0x10UL)       /*!< DUXE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_PMIE_DUNE_Pos        (5UL)          /*!< DUNE (Bit 5)                                          */
 #define R_MIPI_CSI_PMIE_DUNE_Msk        (0x20UL)       /*!< DUNE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_PMIE_CUXE_Pos        (6UL)          /*!< CUXE (Bit 6)                                          */
 #define R_MIPI_CSI_PMIE_CUXE_Msk        (0x40UL)       /*!< CUXE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_PMIE_CUNE_Pos        (7UL)          /*!< CUNE (Bit 7)                                          */
 #define R_MIPI_CSI_PMIE_CUNE_Msk        (0x80UL)       /*!< CUNE (Bitfield-Mask: 0x01)                            */
/* =========================================================  GSCT  ========================================================== */
 #define R_MIPI_CSI_GSCT_SHTH_Pos        (0UL)          /*!< SHTH (Bit 0)                                          */
 #define R_MIPI_CSI_GSCT_SHTH_Msk        (0x7fUL)       /*!< SHTH (Bitfield-Mask: 0x7f)                            */
 #define R_MIPI_CSI_GSCT_GFIF_Pos        (16UL)         /*!< GFIF (Bit 16)                                         */
 #define R_MIPI_CSI_GSCT_GFIF_Msk        (0x10000UL)    /*!< GFIF (Bitfield-Mask: 0x01)                            */
/* =========================================================  GSST  ========================================================== */
 #define R_MIPI_CSI_GSST_GNE_Pos         (0UL)          /*!< GNE (Bit 0)                                           */
 #define R_MIPI_CSI_GSST_GNE_Msk         (0x1UL)        /*!< GNE (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_GSST_GTH_Pos         (1UL)          /*!< GTH (Bit 1)                                           */
 #define R_MIPI_CSI_GSST_GTH_Msk         (0x2UL)        /*!< GTH (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_GSST_GOV_Pos         (4UL)          /*!< GOV (Bit 4)                                           */
 #define R_MIPI_CSI_GSST_GOV_Msk         (0x10UL)       /*!< GOV (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_GSST_PNUM_Pos        (8UL)          /*!< PNUM (Bit 8)                                          */
 #define R_MIPI_CSI_GSST_PNUM_Msk        (0xff00UL)     /*!< PNUM (Bitfield-Mask: 0xff)                            */
 #define R_MIPI_CSI_GSST_GCD_Pos         (16UL)         /*!< GCD (Bit 16)                                          */
 #define R_MIPI_CSI_GSST_GCD_Msk         (0x10000UL)    /*!< GCD (Bitfield-Mask: 0x01)                             */
 #define R_MIPI_CSI_GSST_STRDS_Pos       (17UL)         /*!< STRDS (Bit 17)                                        */
 #define R_MIPI_CSI_GSST_STRDS_Msk       (0x20000UL)    /*!< STRDS (Bitfield-Mask: 0x01)                           */
/* =========================================================  GSSC  ========================================================== */
 #define R_MIPI_CSI_GSSC_GOVC_Pos        (4UL)          /*!< GOVC (Bit 4)                                          */
 #define R_MIPI_CSI_GSSC_GOVC_Msk        (0x10UL)       /*!< GOVC (Bitfield-Mask: 0x01)                            */
/* =========================================================  GSIE  ========================================================== */
 #define R_MIPI_CSI_GSIE_GNEE_Pos        (0UL)          /*!< GNEE (Bit 0)                                          */
 #define R_MIPI_CSI_GSIE_GNEE_Msk        (0x1UL)        /*!< GNEE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_GSIE_GTHE_Pos        (1UL)          /*!< GTHE (Bit 1)                                          */
 #define R_MIPI_CSI_GSIE_GTHE_Msk        (0x2UL)        /*!< GTHE (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_GSIE_GOVE_Pos        (4UL)          /*!< GOVE (Bit 4)                                          */
 #define R_MIPI_CSI_GSIE_GOVE_Msk        (0x10UL)       /*!< GOVE (Bitfield-Mask: 0x01)                            */
/* =========================================================  GSHT  ========================================================== */
 #define R_MIPI_CSI_GSHT_SPDT_Pos        (0UL)          /*!< SPDT (Bit 0)                                          */
 #define R_MIPI_CSI_GSHT_SPDT_Msk        (0xffffUL)     /*!< SPDT (Bitfield-Mask: 0xffff)                          */
 #define R_MIPI_CSI_GSHT_DTYP_Pos        (16UL)         /*!< DTYP (Bit 16)                                         */
 #define R_MIPI_CSI_GSHT_DTYP_Msk        (0x3f0000UL)   /*!< DTYP (Bitfield-Mask: 0x3f)                            */
 #define R_MIPI_CSI_GSHT_SPVC_Pos        (24UL)         /*!< SPVC (Bit 24)                                         */
 #define R_MIPI_CSI_GSHT_SPVC_Msk        (0xf000000UL)  /*!< SPVC (Bitfield-Mask: 0x0f)                            */
/* =========================================================  GSIU  ========================================================== */
 #define R_MIPI_CSI_GSIU_FINC_Pos        (0UL)          /*!< FINC (Bit 0)                                          */
 #define R_MIPI_CSI_GSIU_FINC_Msk        (0x1UL)        /*!< FINC (Bitfield-Mask: 0x01)                            */
 #define R_MIPI_CSI_GSIU_GFCLR_Pos       (8UL)          /*!< GFCLR (Bit 8)                                         */
 #define R_MIPI_CSI_GSIU_GFCLR_Msk       (0x100UL)      /*!< GFCLR (Bitfield-Mask: 0x01)                           */
 #define R_MIPI_CSI_GSIU_GFEN_Pos        (16UL)         /*!< GFEN (Bit 16)                                         */
 #define R_MIPI_CSI_GSIU_GFEN_Msk        (0x10000UL)    /*!< GFEN (Bitfield-Mask: 0x01)                            */

#ifdef __cplusplus
}
#endif

#endif /* R7KA8P1KF_CORE0_ADDITIONAL_H__ */
