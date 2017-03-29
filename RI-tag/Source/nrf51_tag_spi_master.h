/** 
 * @file nrf51_tag_spi_master.h
 *
 */
 
#pragma once 

#include "nrf51_tag_headers.h"

#define CTRL_LENGTH 2

static const uint8_t WHO_AM_I[CTRL_LENGTH] = {0x8F,0x00};

static const uint8_t CTRL_REG1_DATA[CTRL_LENGTH]     = {0x20,0xA7};
static const uint8_t CTRL_REG1_DATA_r[CTRL_LENGTH]     = {0xFF,0xFF};
static const uint8_t CTRL_REG2_DATA[CTRL_LENGTH]     = {0x21,0x00};
static const uint8_t CTRL_REG3_DATA[CTRL_LENGTH]     = {0x22,0x40};
static const uint8_t CTRL_REG4_DATA[CTRL_LENGTH]     = {0x23,0x00};
static const uint8_t CTRL_REG5_DATA[CTRL_LENGTH]     = {0x24,0x00};
static const uint8_t INT1_THS_DATA[CTRL_LENGTH]      = {0x32,0x10};
static const uint8_t INT1_DURATION_DATA[CTRL_LENGTH] = {0x33,0x10};
static const uint8_t INT1_CFG_DATA[CTRL_LENGTH]      = {0x30,0x0A};

#define TAG_ON  1
#define TAG_OFF 0

#define TAG_GPIOTE_CHANNEL_NUMBER 0  /**< GPIOTE channel number. */

#define TAG_PIN_TOGGLE_DELAY 20  /**< pin toggle delay 20 us. */

#define TAG_SPI_SLAVE_ENABLE_DELAY 35  /**< SPI Slave Enable Delay: 35 us. */

#define SPI0_OPERATING_FREQUENCY ( 0x02000000UL << (uint32_t)Freq_125Kbps )  /*!< Slave clock frequency. */

/* NRF Hardware Control Lines 
*/
#define TAG_NRF_IRQ_PIN 1   /*!< GPIO (Output) pin number for IRQ  */

/* NRF SPI0 
*/
//#define SPI_PSELSCK0  25   /*!< GPIO pin number for SPI clock SCLK           */
//#define SPI_PSELMOSI0 24   /*!< GPIO pin number for Master Out Slave In MOSI */
//#define SPI_PSELMISO0 23   /*!< GPIO pin number for Master In Slave Out MISO */
//#define SPI_PSELSS0   30   /*!< GPIO pin number for Slave Select CS          */

#define SPI_PSELSCK0  7   /*!< GPIO pin number for SPI clock SCLK           */
#define SPI_PSELMOSI0 6   /*!< GPIO pin number for Master Out Slave In MOSI */
#define SPI_PSELMISO0 4   /*!< GPIO pin number for Master In Slave Out MISO */
#define SPI_PSELSS0   3   /*!< GPIO pin number for Slave Select CS          */

#define TIMEOUT_COUNTER_10MS 0xF000UL  /*!< timeout for getting rx bytes from slave - measured 10 ms */

/**
 * SPI master operating frequency
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

//=============================================================================
// Function Declarations
//=============================================================================

/**
 *
 */
void nrf51_tag_gpio_port_event_init(nrf_gpio_pin_sense_t pin_polarity);

/**
 *
 */
void nrf51_tag_spi0_master_init(void);

/**
 *
 */
bool nrf51_tag_spi_master_tx_rx(const uint8_t* p_write_cmd, uint8_t* p_read_cmd);
