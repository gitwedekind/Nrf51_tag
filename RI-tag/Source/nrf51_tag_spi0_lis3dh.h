/** 
 * @file nrf51_tag_spi0_lis3dh.h
 *
 */
 
#pragma once 

#include "nrf51_tag_headers.h"

/**< GPIOTE channel number
*/
#define TAG_GPIOTE_CHANNEL_NUMBER 0  

/*!< Slave clock frequency
*/
#define SPI0_OPERATING_FREQUENCY ( 0x02000000UL << (uint32_t)Freq_8Mbps )  

/* NRF SPI0 Pins
*/
#ifdef ENABLE_BLE400_DEV_BOARD

/* LIS3DH Wake Pin
*/
#define LIS3DH_WAKE_IRQ_PIN 20   

#define SPI_PSELSCK0  25   /*!< GPIO pin number for SPI clock SCLK           */
#define SPI_PSELMOSI0 24   /*!< GPIO pin number for Master Out Slave In MOSI */
#define SPI_PSELMISO0 23   /*!< GPIO pin number for Master In Slave Out MISO */
#define SPI_PSELSS0   30   /*!< GPIO pin number for Slave Select CS          */

#else

/* LIS3DH Wake Pin
*/
#define LIS3DH_WAKE_IRQ_PIN 1   

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
