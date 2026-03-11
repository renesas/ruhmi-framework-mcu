/* generated vector source file - do not edit */
#include "bsp_api.h"
/* Do not build these data structures if no interrupts are currently allocated because IAR will have build errors. */
#if VECTOR_DATA_IRQ_COUNT > 0
        BSP_DONT_REMOVE const fsp_vector_t g_vector_table[BSP_ICU_VECTOR_NUM_ENTRIES] BSP_PLACE_IN_SECTION(BSP_SECTION_APPLICATION_VECTORS) =
        {
                        [0] = sci_b_uart_rxi_isr, /* SCI8 RXI (Receive data full) */
            [1] = sci_b_uart_txi_isr, /* SCI8 TXI (Transmit data empty) */
            [2] = sci_b_uart_tei_isr, /* SCI8 TEI (Transmit end) */
            [3] = sci_b_uart_eri_isr, /* SCI8 ERI (Receive error) */
            [4] = gpt_counter_overflow_isr, /* GPT0 COUNTER OVERFLOW (Overflow) */
            [5] = r_icu_isr, /* ICU IRQ13 (External pin interrupt 13) */
            [6] = r_icu_isr, /* ICU IRQ12 (External pin interrupt 12) */
            [7] = iic_master_rxi_isr, /* IIC1 RXI (Receive data full) */
            [8] = iic_master_txi_isr, /* IIC1 TXI (Transmit data empty) */
            [9] = iic_master_tei_isr, /* IIC1 TEI (Transmit end) */
            [10] = iic_master_eri_isr, /* IIC1 ERI (Transfer error) */
            [11] = drw_int_isr, /* DRW INT (DRW interrupt) */
            [12] = glcdc_line_detect_isr, /* GLCDC LINE DETECT (Specified line) */
            [13] = vin_status_isr, /* VIN IRQ (Interrupt Request) */
            [14] = vin_error_isr, /* VIN ERR (Interrupt Request for SYNC Error) */
            [15] = mipi_csi_rx_isr, /* MIPICSI RX (Receive interrupt) */
            [16] = mipi_csi_dl_isr, /* MIPICSI DL (Data Lane interrupt) */
            [17] = mipi_csi_vc_isr, /* MIPICSI VC (Virtual Channel interrupt) */
            [18] = mipi_csi_pm_isr, /* MIPICSI PM (Power Management interrupt) */
            [19] = mipi_csi_gst_isr, /* MIPICSI GST (Generic Short Packet interrupt) */
            [20] = rm_ethosu_isr, /* NPU IRQ (NPU IRQ) */
        };
        #if BSP_FEATURE_ICU_HAS_IELSR
        const bsp_interrupt_event_t g_interrupt_event_link_select[BSP_ICU_VECTOR_NUM_ENTRIES] =
        {
            [0] = BSP_PRV_VECT_ENUM(EVENT_SCI8_RXI,GROUP0), /* SCI8 RXI (Receive data full) */
            [1] = BSP_PRV_VECT_ENUM(EVENT_SCI8_TXI,GROUP1), /* SCI8 TXI (Transmit data empty) */
            [2] = BSP_PRV_VECT_ENUM(EVENT_SCI8_TEI,GROUP2), /* SCI8 TEI (Transmit end) */
            [3] = BSP_PRV_VECT_ENUM(EVENT_SCI8_ERI,GROUP3), /* SCI8 ERI (Receive error) */
            [4] = BSP_PRV_VECT_ENUM(EVENT_GPT0_COUNTER_OVERFLOW,GROUP4), /* GPT0 COUNTER OVERFLOW (Overflow) */
            [5] = BSP_PRV_VECT_ENUM(EVENT_ICU_IRQ13,GROUP5), /* ICU IRQ13 (External pin interrupt 13) */
            [6] = BSP_PRV_VECT_ENUM(EVENT_ICU_IRQ12,GROUP6), /* ICU IRQ12 (External pin interrupt 12) */
            [7] = BSP_PRV_VECT_ENUM(EVENT_IIC1_RXI,GROUP7), /* IIC1 RXI (Receive data full) */
            [8] = BSP_PRV_VECT_ENUM(EVENT_IIC1_TXI,GROUP0), /* IIC1 TXI (Transmit data empty) */
            [9] = BSP_PRV_VECT_ENUM(EVENT_IIC1_TEI,GROUP1), /* IIC1 TEI (Transmit end) */
            [10] = BSP_PRV_VECT_ENUM(EVENT_IIC1_ERI,GROUP2), /* IIC1 ERI (Transfer error) */
            [11] = BSP_PRV_VECT_ENUM(EVENT_DRW_INT,GROUP3), /* DRW INT (DRW interrupt) */
            [12] = BSP_PRV_VECT_ENUM(EVENT_GLCDC_LINE_DETECT,GROUP4), /* GLCDC LINE DETECT (Specified line) */
            [13] = BSP_PRV_VECT_ENUM(EVENT_VIN_IRQ,GROUP5), /* VIN IRQ (Interrupt Request) */
            [14] = BSP_PRV_VECT_ENUM(EVENT_VIN_ERR,GROUP6), /* VIN ERR (Interrupt Request for SYNC Error) */
            [15] = BSP_PRV_VECT_ENUM(EVENT_MIPICSI_RX,GROUP7), /* MIPICSI RX (Receive interrupt) */
            [16] = BSP_PRV_VECT_ENUM(EVENT_MIPICSI_DL,GROUP0), /* MIPICSI DL (Data Lane interrupt) */
            [17] = BSP_PRV_VECT_ENUM(EVENT_MIPICSI_VC,GROUP1), /* MIPICSI VC (Virtual Channel interrupt) */
            [18] = BSP_PRV_VECT_ENUM(EVENT_MIPICSI_PM,GROUP2), /* MIPICSI PM (Power Management interrupt) */
            [19] = BSP_PRV_VECT_ENUM(EVENT_MIPICSI_GST,GROUP3), /* MIPICSI GST (Generic Short Packet interrupt) */
            [20] = BSP_PRV_VECT_ENUM(EVENT_NPU_IRQ,GROUP4), /* NPU IRQ (NPU IRQ) */
        };
        #endif
        #endif
