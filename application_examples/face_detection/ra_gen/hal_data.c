/* generated HAL source file - do not edit */
#include "hal_data.h"

gpt_instance_ctrl_t g_time_counter_ctrl;
#if 0
const gpt_extended_pwm_cfg_t g_time_counter_pwm_extend =
{
    .trough_ipl          = (BSP_IRQ_DISABLED),
#if defined(VECTOR_NUMBER_GPT0_COUNTER_UNDERFLOW)
    .trough_irq          = VECTOR_NUMBER_GPT0_COUNTER_UNDERFLOW,
#else
    .trough_irq          = FSP_INVALID_VECTOR,
#endif
    .poeg_link           = GPT_POEG_LINK_POEG0,
    .output_disable      = (gpt_output_disable_t) ( GPT_OUTPUT_DISABLE_NONE),
    .adc_trigger         = (gpt_adc_trigger_t) ( GPT_ADC_TRIGGER_NONE),
    .dead_time_count_up  = 0,
    .dead_time_count_down = 0,
    .adc_a_compare_match = 0,
    .adc_b_compare_match = 0,
    .interrupt_skip_source = GPT_INTERRUPT_SKIP_SOURCE_NONE,
    .interrupt_skip_count  = GPT_INTERRUPT_SKIP_COUNT_0,
    .interrupt_skip_adc    = GPT_INTERRUPT_SKIP_ADC_NONE,
    .gtioca_disable_setting = GPT_GTIOC_DISABLE_PROHIBITED,
    .gtiocb_disable_setting = GPT_GTIOC_DISABLE_PROHIBITED,
};
#endif
const gpt_extended_cfg_t g_time_counter_extend =
        { .gtioca =
        { .output_enabled = false, .stop_level = GPT_PIN_LEVEL_LOW },
          .gtiocb =
          { .output_enabled = false, .stop_level = GPT_PIN_LEVEL_LOW },
          .start_source = (gpt_source_t) (GPT_SOURCE_NONE), .stop_source = (gpt_source_t) (GPT_SOURCE_NONE), .clear_source =
                  (gpt_source_t) (GPT_SOURCE_NONE),
          .count_up_source = (gpt_source_t) (GPT_SOURCE_NONE), .count_down_source = (gpt_source_t) (GPT_SOURCE_NONE), .capture_a_source =
                  (gpt_source_t) (GPT_SOURCE_NONE),
          .capture_b_source = (gpt_source_t) (GPT_SOURCE_NONE), .capture_a_ipl = (BSP_IRQ_DISABLED), .capture_b_ipl =
                  (BSP_IRQ_DISABLED),
#if defined(VECTOR_NUMBER_GPT0_CAPTURE_COMPARE_A)
    .capture_a_irq       = VECTOR_NUMBER_GPT0_CAPTURE_COMPARE_A,
#else
          .capture_a_irq = FSP_INVALID_VECTOR,
#endif
#if defined(VECTOR_NUMBER_GPT0_CAPTURE_COMPARE_B)
    .capture_b_irq       = VECTOR_NUMBER_GPT0_CAPTURE_COMPARE_B,
#else
          .capture_b_irq = FSP_INVALID_VECTOR,
#endif
          .compare_match_value =
          { /* CMP_A */(uint32_t) 0x0, /* CMP_B */(uint32_t) 0x0 },
          .compare_match_status = (0U << 1U) | 0U, .capture_filter_gtioca = GPT_CAPTURE_FILTER_NONE, .capture_filter_gtiocb =
                  GPT_CAPTURE_FILTER_NONE,
#if 0
    .p_pwm_cfg                   = &g_time_counter_pwm_extend,
#else
          .p_pwm_cfg = NULL,
#endif
#if 0
    .gtior_setting.gtior_b.gtioa  = (0U << 4U) | (0U << 2U) | (0U << 0U),
    .gtior_setting.gtior_b.oadflt = (uint32_t) GPT_PIN_LEVEL_LOW,
    .gtior_setting.gtior_b.oahld  = 0U,
    .gtior_setting.gtior_b.oae    = (uint32_t) false,
    .gtior_setting.gtior_b.oadf   = (uint32_t) GPT_GTIOC_DISABLE_PROHIBITED,
    .gtior_setting.gtior_b.nfaen  = ((uint32_t) GPT_CAPTURE_FILTER_NONE & 1U),
    .gtior_setting.gtior_b.nfcsa  = ((uint32_t) GPT_CAPTURE_FILTER_NONE >> 1U),
    .gtior_setting.gtior_b.gtiob  = (0U << 4U) | (0U << 2U) | (0U << 0U),
    .gtior_setting.gtior_b.obdflt = (uint32_t) GPT_PIN_LEVEL_LOW,
    .gtior_setting.gtior_b.obhld  = 0U,
    .gtior_setting.gtior_b.obe    = (uint32_t) false,
    .gtior_setting.gtior_b.obdf   = (uint32_t) GPT_GTIOC_DISABLE_PROHIBITED,
    .gtior_setting.gtior_b.nfben  = ((uint32_t) GPT_CAPTURE_FILTER_NONE & 1U),
    .gtior_setting.gtior_b.nfcsb  = ((uint32_t) GPT_CAPTURE_FILTER_NONE >> 1U),
#else
          .gtior_setting.gtior = 0U,
#endif
        };

const timer_cfg_t g_time_counter_cfg =
{ .mode = TIMER_MODE_PERIODIC,
/* Actual period: 0.0001 seconds. Actual duty: 50%. */.period_counts = (uint32_t) 0x61a8,
  .duty_cycle_counts = 0x30d4, .source_div = (timer_source_div_t) 0, .channel = 0, .p_callback = time_counter_callback,
  /** If NULL then do not add & */
#if defined(NULL)
    .p_context           = NULL,
#else
  .p_context = (void*) &NULL,
#endif
  .p_extend = &g_time_counter_extend,
  .cycle_end_ipl = (1),
#if defined(VECTOR_NUMBER_GPT0_COUNTER_OVERFLOW)
    .cycle_end_irq       = VECTOR_NUMBER_GPT0_COUNTER_OVERFLOW,
#else
  .cycle_end_irq = FSP_INVALID_VECTOR,
#endif
        };
/* Instance structure to use this module. */
const timer_instance_t g_time_counter =
{ .p_ctrl = &g_time_counter_ctrl, .p_cfg = &g_time_counter_cfg, .p_api = &g_timer_on_gpt };
dmac_instance_ctrl_t g_transfer0_ctrl;
transfer_info_t g_transfer0_info =
{ .transfer_settings_word_b.dest_addr_mode = TRANSFER_ADDR_MODE_INCREMENTED,
  .transfer_settings_word_b.repeat_area = TRANSFER_REPEAT_AREA_SOURCE,
  .transfer_settings_word_b.irq = TRANSFER_IRQ_END,
  .transfer_settings_word_b.chain_mode = TRANSFER_CHAIN_MODE_DISABLED,
  .transfer_settings_word_b.src_addr_mode = TRANSFER_ADDR_MODE_INCREMENTED,
  .transfer_settings_word_b.size = TRANSFER_SIZE_1_BYTE,
  .transfer_settings_word_b.mode = TRANSFER_MODE_BLOCK,
  .p_dest = (void*) NULL,
  .p_src = (void const*) NULL,
  .num_blocks = 1,
  .length = 64, };
const dmac_extended_cfg_t g_transfer0_extend =
{ .offset = 0, .src_buffer_size = 0,
#if defined(VECTOR_NUMBER_DMAC1_INT)
    .irq                 = VECTOR_NUMBER_DMAC1_INT,
#else
  .irq = FSP_INVALID_VECTOR,
#endif
  .ipl = (BSP_IRQ_DISABLED),
  .channel = 1, .p_callback = NULL, .p_context = NULL, .activation_source = ELC_EVENT_NONE, };
const transfer_cfg_t g_transfer0_cfg =
{ .p_info = &g_transfer0_info, .p_extend = &g_transfer0_extend, };
/* Instance structure to use this module. */
const transfer_instance_t g_transfer0 =
{ .p_ctrl = &g_transfer0_ctrl, .p_cfg = &g_transfer0_cfg, .p_api = &g_transfer_on_dmac };
ospi_b_instance_ctrl_t g_ospi_b_ctrl;

static ospi_b_timing_setting_t g_ospi_b_timing_settings =
{ .command_to_command_interval = OSPI_B_COMMAND_INTERVAL_CLOCKS_2,
  .cs_pullup_lag = OSPI_B_COMMAND_CS_PULLUP_CLOCKS_NO_EXTENSION,
  .cs_pulldown_lead = OSPI_B_COMMAND_CS_PULLDOWN_CLOCKS_NO_EXTENSION,
  .sdr_drive_timing = OSPI_B_SDR_DRIVE_TIMING_BEFORE_CK,
  .sdr_sampling_edge = OSPI_B_CK_EDGE_FALLING,
  .sdr_sampling_delay = OSPI_B_SDR_SAMPLING_DELAY_NONE,
  .ddr_sampling_extension = OSPI_B_DDR_SAMPLING_EXTENSION_NONE, };

static const spi_flash_erase_command_t g_ospi_b_command_set_initial_erase_commands[] =
{
{ .command = 0x21, .size = 4096 },
  { .command = 0xDC, .size = 65536 },
  { .command = 0x60, .size = SPI_FLASH_ERASE_SIZE_CHIP_ERASE }, };
static const ospi_b_table_t g_ospi_b_command_set_initial_erase_table =
        { .p_table = (void*) g_ospi_b_command_set_initial_erase_commands, .length =
                  sizeof(g_ospi_b_command_set_initial_erase_commands)
                          / sizeof(g_ospi_b_command_set_initial_erase_commands[0]), };
static const spi_flash_erase_command_t g_ospi_b_command_set_high_speed_erase_commands[] =
{
{ .command = 0x21DE, .size = 4096 },
  { .command = 0xDC23, .size = 65536 },
  { .command = 0xC738, .size = SPI_FLASH_ERASE_SIZE_CHIP_ERASE }, };
static const ospi_b_table_t g_ospi_b_command_set_high_speed_erase_table =
{ .p_table = (void*) g_ospi_b_command_set_high_speed_erase_commands, .length =
          sizeof(g_ospi_b_command_set_high_speed_erase_commands)
                  / sizeof(g_ospi_b_command_set_high_speed_erase_commands[0]), };

static const ospi_b_xspi_command_set_t g_ospi_b_command_set_table[] =
{
{ .protocol = SPI_FLASH_PROTOCOL_1S_1S_1S,
  .frame_format = OSPI_B_FRAME_FORMAT_STANDARD,
  .latency_mode = OSPI_B_LATENCY_MODE_FIXED,
  .command_bytes = OSPI_B_COMMAND_BYTES_1,
  .address_bytes = SPI_FLASH_ADDRESS_BYTES_4,
  .address_msb_mask = 0xF0,
  .status_needs_address = false,
  .status_address = 0U,
  .status_address_bytes = (spi_flash_address_bytes_t) 0U,
  .p_erase_commands = &g_ospi_b_command_set_initial_erase_table,
  .read_command = 0x13,
  .read_dummy_cycles = 0,
  .program_command = 0x12,
  .program_dummy_cycles = 0,
  .row_load_command = 0x00,
  .row_load_dummy_cycles = 0,
  .row_store_command = 0x00,
  .row_store_dummy_cycles = 0,
  .write_enable_command = 0x06,
  .status_command = 0x05,
  .status_dummy_cycles = 0, },
  { .protocol = SPI_FLASH_PROTOCOL_8D_8D_8D,
    .frame_format = OSPI_B_FRAME_FORMAT_XSPI_PROFILE_1,
    .latency_mode = OSPI_B_LATENCY_MODE_FIXED,
    .command_bytes = OSPI_B_COMMAND_BYTES_2,
    .address_bytes = SPI_FLASH_ADDRESS_BYTES_4,
    .address_msb_mask = 0xF0,
    .status_needs_address = false,
    .status_address = 0U,
    .status_address_bytes = (spi_flash_address_bytes_t) 0U,
    .p_erase_commands = &g_ospi_b_command_set_high_speed_erase_table,
    .read_command = 0xEE11,
    .read_dummy_cycles = 10,
    .program_command = 0x12ED,
    .program_dummy_cycles = 0,
    .row_load_command = 0x00,
    .row_load_dummy_cycles = 0,
    .row_store_command = 0x00,
    .row_store_dummy_cycles = 0,
    .write_enable_command = 0x06F9,
    .status_command = 0x05FA,
    .status_dummy_cycles = 0, } };

static const ospi_b_table_t g_ospi_b_command_set =
{ .p_table = (void*) g_ospi_b_command_set_table, .length = 2 };

#if OSPI_B_CFG_DOTF_SUPPORT_ENABLE
extern uint8_t g_ospi_dotf_iv[];
extern uint8_t g_ospi_dotf_key[];

static ospi_b_dotf_cfg_t g_ospi_dotf_cfg=
{
    .key_type       = OSPI_B_DOTF_AES_KEY_TYPE_128,
    .format         = OSPI_B_DOTF_KEY_FORMAT_PLAINTEXT,
    .p_start_addr   = (uint32_t *)0x90000000,
    .p_end_addr     = (uint32_t *)0x90001FFF,
    .p_key          = (uint32_t *)g_ospi_dotf_key,
    .p_iv           = (uint32_t *)g_ospi_dotf_iv,
};
#endif

static const ospi_b_extended_cfg_t g_ospi_b_extended_cfg =
{ .ospi_b_unit = 0,
  .channel = (ospi_b_device_number_t) 1,
  .p_timing_settings = &g_ospi_b_timing_settings,
  .p_xspi_command_set = &g_ospi_b_command_set,
  .data_latch_delay_clocks = OSPI_B_DS_TIMING_DELAY_NONE,
  .p_autocalibration_preamble_pattern_addr = (uint8_t*) 0x00,
#if OSPI_B_CFG_DMAC_SUPPORT_ENABLE
    .p_lower_lvl_transfer                    = &g_transfer0,
#endif
#if OSPI_B_CFG_DOTF_SUPPORT_ENABLE
    .p_dotf_cfg                              = &g_ospi_dotf_cfg,
#endif
#if OSPI_B_CFG_ROW_ADDRESSING_SUPPORT_ENABLE
    .row_index_bytes                         = 0xFF
#endif
        };
const spi_flash_cfg_t g_ospi_b_cfg =
{ .spi_protocol = SPI_FLASH_PROTOCOL_1S_1S_1S, .read_mode = SPI_FLASH_READ_MODE_STANDARD, /* Unused by OSPI_B */
  .address_bytes = SPI_FLASH_ADDRESS_BYTES_4, .dummy_clocks = SPI_FLASH_DUMMY_CLOCKS_DEFAULT, /* Unused by OSPI_B */
  .page_program_address_lines = (spi_flash_data_lines_t) 0U, /* Unused by OSPI_B */
  .page_size_bytes = 64, .write_status_bit = 0, .write_enable_bit = 1, .page_program_command = 0, /* OSPI_B uses command sets. See g_ospi_b_command_set. */
  .write_enable_command = 0, /* OSPI_B uses command sets. See g_ospi_b_command_set. */
  .status_command = 0, /* OSPI_B uses command sets. See g_ospi_b_command_set. */
  .read_command = 0, /* OSPI_B uses command sets. See g_ospi_b_command_set. */
#if OSPI_B_CFG_XIP_SUPPORT_ENABLE
    .xip_enter_command           = 0,
    .xip_exit_command            = 0,
#else
  .xip_enter_command = 0U,
  .xip_exit_command = 0U,
#endif
  .erase_command_list_length = 0U, /* OSPI_B uses command sets. See g_ospi_b_command_set. */
  .p_erase_command_list = NULL, /* OSPI_B uses command sets. See g_ospi_b_command_set. */
  .p_extend = &g_ospi_b_extended_cfg, };

/** This structure encompasses everything that is needed to use an instance of this interface. */
const spi_flash_instance_t g_ospi_b =
{ .p_ctrl = &g_ospi_b_ctrl, .p_cfg = &g_ospi_b_cfg, .p_api = &g_ospi_b_on_spi_flash, };

#if defined OSPI_B_CFG_DOTF_PROTECTED_MODE_SUPPORT_ENABLE
rsip_instance_t const * const gp_rsip_instance = &RA_NOT_DEFINED;
#endif
sci_b_uart_instance_ctrl_t g_console_output_uart_ctrl;

sci_b_baud_setting_t g_console_output_uart_baud_setting =
        {
        /* Baud rate calculated with 1.725% error. */.baudrate_bits_b.abcse = 0,
          .baudrate_bits_b.abcs = 0, .baudrate_bits_b.bgdm = 1, .baudrate_bits_b.cks = 0, .baudrate_bits_b.brr = 31, .baudrate_bits_b.mddr =
                  (uint8_t) 256,
          .baudrate_bits_b.brme = false };

/** UART extended configuration for UARTonSCI HAL driver */
const sci_b_uart_extended_cfg_t g_console_output_uart_cfg_extend =
{ .clock = SCI_B_UART_CLOCK_INT,
  .rx_edge_start = SCI_B_UART_START_BIT_FALLING_EDGE,
  .noise_cancel = SCI_B_UART_NOISE_CANCELLATION_DISABLE,
  .rx_fifo_trigger = SCI_B_UART_RX_FIFO_TRIGGER_MAX,
  .p_baud_setting = &g_console_output_uart_baud_setting,
  .flow_control = SCI_B_UART_FLOW_CONTROL_RTS,
#if 0xFF != 0xFF
                .flow_control_pin       = BSP_IO_PORT_FF_PIN_0xFF,
                #else
  .flow_control_pin = (bsp_io_port_pin_t) UINT16_MAX,
#endif
  .rs485_setting =
  { .enable = SCI_B_UART_RS485_DISABLE,
    .polarity = SCI_B_UART_RS485_DE_POLARITY_HIGH,
    .assertion_time = 1,
    .negation_time = 1, } };

/** UART interface configuration */
const uart_cfg_t g_console_output_uart_cfg =
{ .channel = 8, .data_bits = UART_DATA_BITS_8, .parity = UART_PARITY_OFF, .stop_bits = UART_STOP_BITS_1, .p_callback =
          console_output_uart_callback,
  .p_context = NULL, .p_extend = &g_console_output_uart_cfg_extend,
#define RA_NOT_DEFINED (1)
#if (RA_NOT_DEFINED == RA_NOT_DEFINED)
  .p_transfer_tx = NULL,
#else
                .p_transfer_tx       = &RA_NOT_DEFINED,
#endif
#if (RA_NOT_DEFINED == RA_NOT_DEFINED)
  .p_transfer_rx = NULL,
#else
                .p_transfer_rx       = &RA_NOT_DEFINED,
#endif
#undef RA_NOT_DEFINED
  .rxi_ipl = (13),
  .txi_ipl = (13), .tei_ipl = (13), .eri_ipl = (13),
#if defined(VECTOR_NUMBER_SCI8_RXI)
                .rxi_irq             = VECTOR_NUMBER_SCI8_RXI,
#else
  .rxi_irq = FSP_INVALID_VECTOR,
#endif
#if defined(VECTOR_NUMBER_SCI8_TXI)
                .txi_irq             = VECTOR_NUMBER_SCI8_TXI,
#else
  .txi_irq = FSP_INVALID_VECTOR,
#endif
#if defined(VECTOR_NUMBER_SCI8_TEI)
                .tei_irq             = VECTOR_NUMBER_SCI8_TEI,
#else
  .tei_irq = FSP_INVALID_VECTOR,
#endif
#if defined(VECTOR_NUMBER_SCI8_ERI)
                .eri_irq             = VECTOR_NUMBER_SCI8_ERI,
#else
  .eri_irq = FSP_INVALID_VECTOR,
#endif
        };

/* Instance structure to use this module. */
const uart_instance_t g_console_output_uart =
{ .p_ctrl = &g_console_output_uart_ctrl, .p_cfg = &g_console_output_uart_cfg, .p_api = &g_uart_on_sci_b };
void g_hal_init(void)
{
    g_common_init ();
}
