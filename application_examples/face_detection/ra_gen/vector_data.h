/* generated vector header file - do not edit */
#ifndef VECTOR_DATA_H
#define VECTOR_DATA_H
#ifdef __cplusplus
        extern "C" {
        #endif
/* Number of interrupts allocated */
#ifndef VECTOR_DATA_IRQ_COUNT
#define VECTOR_DATA_IRQ_COUNT    (21)
#endif
/* ISR prototypes */
void sci_b_uart_rxi_isr(void);
void sci_b_uart_txi_isr(void);
void sci_b_uart_tei_isr(void);
void sci_b_uart_eri_isr(void);
void gpt_counter_overflow_isr(void);
void r_icu_isr(void);
void iic_master_rxi_isr(void);
void iic_master_txi_isr(void);
void iic_master_tei_isr(void);
void iic_master_eri_isr(void);
void drw_int_isr(void);
void glcdc_line_detect_isr(void);
void vin_status_isr(void);
void vin_error_isr(void);
void mipi_csi_rx_isr(void);
void mipi_csi_dl_isr(void);
void mipi_csi_vc_isr(void);
void mipi_csi_pm_isr(void);
void mipi_csi_gst_isr(void);
void rm_ethosu_isr(void);

/* Vector table allocations */
#define VECTOR_NUMBER_SCI8_RXI ((IRQn_Type) 0) /* SCI8 RXI (Receive data full) */
#define SCI8_RXI_IRQn          ((IRQn_Type) 0) /* SCI8 RXI (Receive data full) */
#define VECTOR_NUMBER_SCI8_TXI ((IRQn_Type) 1) /* SCI8 TXI (Transmit data empty) */
#define SCI8_TXI_IRQn          ((IRQn_Type) 1) /* SCI8 TXI (Transmit data empty) */
#define VECTOR_NUMBER_SCI8_TEI ((IRQn_Type) 2) /* SCI8 TEI (Transmit end) */
#define SCI8_TEI_IRQn          ((IRQn_Type) 2) /* SCI8 TEI (Transmit end) */
#define VECTOR_NUMBER_SCI8_ERI ((IRQn_Type) 3) /* SCI8 ERI (Receive error) */
#define SCI8_ERI_IRQn          ((IRQn_Type) 3) /* SCI8 ERI (Receive error) */
#define VECTOR_NUMBER_GPT0_COUNTER_OVERFLOW ((IRQn_Type) 4) /* GPT0 COUNTER OVERFLOW (Overflow) */
#define GPT0_COUNTER_OVERFLOW_IRQn          ((IRQn_Type) 4) /* GPT0 COUNTER OVERFLOW (Overflow) */
#define VECTOR_NUMBER_ICU_IRQ13 ((IRQn_Type) 5) /* ICU IRQ13 (External pin interrupt 13) */
#define ICU_IRQ13_IRQn          ((IRQn_Type) 5) /* ICU IRQ13 (External pin interrupt 13) */
#define VECTOR_NUMBER_ICU_IRQ12 ((IRQn_Type) 6) /* ICU IRQ12 (External pin interrupt 12) */
#define ICU_IRQ12_IRQn          ((IRQn_Type) 6) /* ICU IRQ12 (External pin interrupt 12) */
#define VECTOR_NUMBER_IIC1_RXI ((IRQn_Type) 7) /* IIC1 RXI (Receive data full) */
#define IIC1_RXI_IRQn          ((IRQn_Type) 7) /* IIC1 RXI (Receive data full) */
#define VECTOR_NUMBER_IIC1_TXI ((IRQn_Type) 8) /* IIC1 TXI (Transmit data empty) */
#define IIC1_TXI_IRQn          ((IRQn_Type) 8) /* IIC1 TXI (Transmit data empty) */
#define VECTOR_NUMBER_IIC1_TEI ((IRQn_Type) 9) /* IIC1 TEI (Transmit end) */
#define IIC1_TEI_IRQn          ((IRQn_Type) 9) /* IIC1 TEI (Transmit end) */
#define VECTOR_NUMBER_IIC1_ERI ((IRQn_Type) 10) /* IIC1 ERI (Transfer error) */
#define IIC1_ERI_IRQn          ((IRQn_Type) 10) /* IIC1 ERI (Transfer error) */
#define VECTOR_NUMBER_DRW_INT ((IRQn_Type) 11) /* DRW INT (DRW interrupt) */
#define DRW_INT_IRQn          ((IRQn_Type) 11) /* DRW INT (DRW interrupt) */
#define VECTOR_NUMBER_GLCDC_LINE_DETECT ((IRQn_Type) 12) /* GLCDC LINE DETECT (Specified line) */
#define GLCDC_LINE_DETECT_IRQn          ((IRQn_Type) 12) /* GLCDC LINE DETECT (Specified line) */
#define VECTOR_NUMBER_VIN_IRQ ((IRQn_Type) 13) /* VIN IRQ (Interrupt Request) */
#define VIN_IRQ_IRQn          ((IRQn_Type) 13) /* VIN IRQ (Interrupt Request) */
#define VECTOR_NUMBER_VIN_ERR ((IRQn_Type) 14) /* VIN ERR (Interrupt Request for SYNC Error) */
#define VIN_ERR_IRQn          ((IRQn_Type) 14) /* VIN ERR (Interrupt Request for SYNC Error) */
#define VECTOR_NUMBER_MIPICSI_RX ((IRQn_Type) 15) /* MIPICSI RX (Receive interrupt) */
#define MIPICSI_RX_IRQn          ((IRQn_Type) 15) /* MIPICSI RX (Receive interrupt) */
#define VECTOR_NUMBER_MIPICSI_DL ((IRQn_Type) 16) /* MIPICSI DL (Data Lane interrupt) */
#define MIPICSI_DL_IRQn          ((IRQn_Type) 16) /* MIPICSI DL (Data Lane interrupt) */
#define VECTOR_NUMBER_MIPICSI_VC ((IRQn_Type) 17) /* MIPICSI VC (Virtual Channel interrupt) */
#define MIPICSI_VC_IRQn          ((IRQn_Type) 17) /* MIPICSI VC (Virtual Channel interrupt) */
#define VECTOR_NUMBER_MIPICSI_PM ((IRQn_Type) 18) /* MIPICSI PM (Power Management interrupt) */
#define MIPICSI_PM_IRQn          ((IRQn_Type) 18) /* MIPICSI PM (Power Management interrupt) */
#define VECTOR_NUMBER_MIPICSI_GST ((IRQn_Type) 19) /* MIPICSI GST (Generic Short Packet interrupt) */
#define MIPICSI_GST_IRQn          ((IRQn_Type) 19) /* MIPICSI GST (Generic Short Packet interrupt) */
#define VECTOR_NUMBER_NPU_IRQ ((IRQn_Type) 20) /* NPU IRQ (NPU IRQ) */
#define NPU_IRQ_IRQn          ((IRQn_Type) 20) /* NPU IRQ (NPU IRQ) */
/* The number of entries required for the ICU vector table. */
#define BSP_ICU_VECTOR_NUM_ENTRIES (21)

#ifdef __cplusplus
        }
        #endif
#endif /* VECTOR_DATA_H */
