/** 
 * @file nrf51_tag_spi0_lis3dh.h
 *
 */
 
#pragma once 

#include "nrf51_tag_headers.h"

// ------------------------------------------------------------------------------------------------
// LIS3DH
// ------------------------------------------------------------------------------------------------

#define LIS3DH_READ  0x80
#define LIS3DH_WRITE 0x00
#define LIS3DH_MS    0x40

#define LIS3DH_CMD_LENGTH  2
#define LIS3DH_CMD_INDEX_0 0
#define LIS3DH_CMD_INDEX_1 1

#define LIS3DH_CMD(x_tx_buffer, x_cmd_reg, x_flags, x_config) \
    x_tx_buffer[LIS3DH_CMD_INDEX_0] = x_cmd_reg | x_flags; \
    x_tx_buffer[LIS3DH_CMD_INDEX_1] = x_config;

#define LIS3DH_WHO_AM_1_DEFAULT 0x33

#define LIS3DH_READY(x_status) x_status == 1 ? "LIS3DH Ready" : "LIS3DH Offline" 

#define LIS3DH_ADC_ENABLE         0x80
#define LIS3DH_TEMPERATURE_ENABLE 0x40

// ------------------------------------------------------------------------------------------------
// LIS3DH Control Registers
// ------------------------------------------------------------------------------------------------

static const uint8_t LIS3DH_STATUS_REG_AUX = 0x07;

static const uint8_t LIS3DH_OUT_ADC1_L     = 0x08;
static const uint8_t LIS3DH_OUT_ADC1_H     = 0x09;
static const uint8_t LIS3DH_OUT_ADC2_L     = 0x0A;
static const uint8_t LIS3DH_OUT_ADC2_H     = 0x0B;
static const uint8_t LIS3DH_OUT_ADC3_L     = 0x0C;
static const uint8_t LIS3DH_OUT_ADC4_H     = 0x0D;

static const uint8_t LIS3DH_WHO_AM_I       = 0x0F;

static const uint8_t LIS3DH_CTRL_REG0      = 0x1E;

static const uint8_t LIS3DH_TEMP_CFG_REG   = 0x1F;

static const uint8_t LIS3DH_CTRL_REG1      = 0x20;
static const uint8_t LIS3DH_CTRL_REG2      = 0x21;
static const uint8_t LIS3DH_CTRL_REG3      = 0x22;
static const uint8_t LIS3DH_CTRL_REG4      = 0x23;
static const uint8_t LIS3DH_CTRL_REG5      = 0x24;
static const uint8_t LIS3DH_CTRL_REG6      = 0x25;

static const uint8_t LIS3DH_REFERENCE      = 0x26;
static const uint8_t LIS3DH_STATUS_REG     = 0x27;

static const uint8_t LIS3DH_OUT_X_L        = 0x28;
static const uint8_t LIS3DH_OUT_X_H        = 0x29;
static const uint8_t LIS3DH_OUT_Y_L        = 0x2A;
static const uint8_t LIS3DH_OUT_Y_H        = 0x2B;
static const uint8_t LIS3DH_OUT_Z_L        = 0x2C;
static const uint8_t LIS3DH_OUT_Z_H        = 0x2D;

static const uint8_t LIS3DH_FIFO_CTRL_REG  = 0x2E;
static const uint8_t LIS3DH_FIFO_SRC_REG   = 0x2F;

static const uint8_t LIS3DH_INT1_CFG       = 0x30;
static const uint8_t LIS3DH_INT1_SRC       = 0x31;
static const uint8_t LIS3DH_INT1_THS       = 0x32;
static const uint8_t LIS3DH_INT1_DURATION  = 0x33;

static const uint8_t LIS3DH_INT2_CFG       = 0x34;
static const uint8_t LIS3DH_INT2_SRC       = 0x35;
static const uint8_t LIS3DH_INT2_THS       = 0x36;
static const uint8_t LIS3DH_INT2_DURATION  = 0x37;

static const uint8_t LIS3DH_CLICK_CFG      = 0x38;
static const uint8_t LIS3DH_CLICK_SRC      = 0x39;
static const uint8_t LIS3DH_CLICK_THS      = 0x3A;

static const uint8_t LIS3DH_TIME_LIMIT     = 0x3B;
static const uint8_t LIS3DH_TIME_LATENCY   = 0x3C;
static const uint8_t LIS3DH_TIME_WINDOW    = 0x3D;

static const uint8_t LIS3DH_ACT_THS        = 0x3E;
static const uint8_t LIS3DH_ACT_DUR        = 0x3F;

/**< GPIOTE channel number
*/
#define TAG_GPIOTE_CHANNEL_NUMBER 0  

/*!< Slave clock frequency
*/
#define SPI0_OPERATING_FREQUENCY ( 0x02000000UL << (uint32_t)Freq_125Kbps )  

/* LIS3DH Wake Pin
*/
#define LIS3DH_WAKE_IRQ_PIN 1   

/* NRF SPI0 Pins
*/
#ifdef ENABLE_BLE400_DEV_BOARD

#define SPI_PSELSCK0  25   /*!< GPIO pin number for SPI clock SCLK           */
#define SPI_PSELMOSI0 24   /*!< GPIO pin number for Master Out Slave In MOSI */
#define SPI_PSELMISO0 23   /*!< GPIO pin number for Master In Slave Out MISO */
#define SPI_PSELSS0   30   /*!< GPIO pin number for Slave Select CS          */

#else

#define SPI_PSELSCK0  7   /*!< GPIO pin number for SPI clock SCLK           */
#define SPI_PSELMOSI0 6   /*!< GPIO pin number for Master Out Slave In MOSI */
#define SPI_PSELMISO0 4   /*!< GPIO pin number for Master In Slave Out MISO */
#define SPI_PSELSS0   3   /*!< GPIO pin number for Slave Select CS          */

#endif

/*!< timeout for getting rx bytes from slave - measured 10 ms 
*/
#define TIMEOUT_COUNTER_10MS 0x8000UL

/** SPI master operating frequency
 */
typedef enum
{
    Freq_125Kbps = 0,        /*!< drive SClk with frequency 125Kbps */
    Freq_250Kbps,            /*!< drive SClk with frequency 250Kbps */
    Freq_500Kbps,            /*!< drive SClk with frequency 500Kbps */
    Freq_1Mbps,              /*!< drive SClk with frequency 1Mbps */
    Freq_2Mbps,              /*!< drive SClk with frequency 2Mbps */
    Freq_4Mbps,              /*!< drive SClk with frequency 4Mbps */
    Freq_8Mbps               /*!< drive SClk with frequency 8Mbps */
} SPI_Frequency_t;

// ------------------------------------------------------------------------------------------------
// Function Declarations
// ------------------------------------------------------------------------------------------------

/**
 *
 */
void nrf51_tag_gpio_port_event_init(nrf_gpio_pin_sense_t pin_polarity);

/**
 *
 */
void nrf51_tag_spi0_lis3dh_init(void);

/**
 *
 */
void nrf51_tag_spi_lis3dh_cmd(const uint8_t* p_write_cmd, uint8_t* p_read_cmd);
