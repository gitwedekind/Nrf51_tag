/** 
 * @file nrf51)tag_spi0_lis3dh.c
 *
 */

#include "nrf51_tag_error.h"
#include "nrf51_tag_spi0_lis3dh.h"

// ------------------------------------------------------------------------------------------------
// static module variable(s)
// ------------------------------------------------------------------------------------------------

/**
*/
static NRF_SPI_Type* spi0_base_address = (NRF_SPI_Type*)NRF_SPI0;

// ------------------------------------------------------------------------------------------------
// static Module Interface Functions
// ------------------------------------------------------------------------------------------------

/**
 * GPIOTE_IRQHandler()
 *
 *  GPIOTE interrupt handler - Triggered on pin DTX_NRF_REQ change
 *
 */
void GPIOTE_IRQHandler(void)
{
    if ( NRF_GPIOTE->EVENTS_PORT )
    {
        //DBG("--> NRF_GPIOTE: 0x%x\r\n", NRF_GPIOTE->EVENTS_PORT);
        
        NRF_GPIOTE->EVENTS_PORT = 0;
        
        void GPIOTE_IRQHandler_LIS3DH(void);
        GPIOTE_IRQHandler_LIS3DH();
        
        DEV_BOARD_BUTTONS();
    }
}

// ------------------------------------------------------------------------------------------------
// Public Module Interface Functions
// ------------------------------------------------------------------------------------------------

/**
 */
void nrf51_tag_gpio_port_event_init(nrf_gpio_pin_sense_t pin_polarity)
{
    NVIC_DisableIRQ(GPIOTE_IRQn);

    nrf_gpio_cfg_sense_input(LIS3DH_WAKE_IRQ_PIN, NRF_GPIO_PIN_NOPULL, pin_polarity);
    
    DEV_BOARD_INIT_BUTTONS();
    
    NRF_GPIOTE->INTENCLR = 0xFFFFFFFF;
    NRF_GPIOTE->INTENSET = GPIOTE_INTENSET_PORT_Msk;

    NVIC_ClearPendingIRQ(GPIOTE_IRQn);
    NVIC_SetPriority(GPIOTE_IRQn, APP_IRQ_PRIORITY_HIGH);

    NVIC_EnableIRQ(GPIOTE_IRQn);
}

/**
 */
void nrf51_tag_spi0_lis3dh_init()
{
    // Get the SPI0 base address 
    //
    spi0_base_address = (NRF_SPI_Type*)NRF_SPI0;

    // Configure the GPIOTE PORT_EVENTS input signal
    //
    nrf51_tag_gpio_port_event_init(NRF_GPIO_PIN_SENSE_HIGH);    

    // Configure GPIO pins used for pselsck, pselmosi, pselmiso and pselss for SPI0 
    //
    nrf_gpio_cfg_output(SPI_PSELSCK0);
    nrf_gpio_cfg_output(SPI_PSELMOSI0);
    nrf_gpio_cfg_input(SPI_PSELMISO0, NRF_GPIO_PIN_NOPULL);
    nrf_gpio_cfg_output(SPI_PSELSS0);

    // Configure the SPI0 pins
    //
    spi0_base_address->PSELSCK  = SPI_PSELSCK0;
    spi0_base_address->PSELMOSI = SPI_PSELMOSI0;
    spi0_base_address->PSELMISO = SPI_PSELMISO0;

    // Set SCK, MOSI, CS HIGH 
    //
    nrf_gpio_pin_set(SPI_PSELSCK0);
    nrf_gpio_pin_set(SPI_PSELMOSI0);
    nrf_gpio_pin_set(SPI_PSELSS0);
    
    // Set the SPI Clock Frequency 
    //
    spi0_base_address->FREQUENCY = (uint32_t)SPI0_OPERATING_FREQUENCY;

    // --------------------------
    // Set the SPI Operating Mode
    // --------------------------
    // Data Valid on Trailing Edge
    // MSB First
    // 4-Wire Mode 
    // 8-bits per transfer
    // Clock is Active Low
    // Enable Line is "Active LOW"
    //
    uint32_t config_mode = (SPI_CONFIG_CPHA_Trailing << SPI_CONFIG_CPHA_Pos) | (SPI_CONFIG_CPOL_ActiveLow << SPI_CONFIG_CPOL_Pos);
    spi0_base_address->CONFIG = (config_mode | (SPI_CONFIG_ORDER_MsbFirst << SPI_CONFIG_ORDER_Pos));

    // Clear the Event Ready Flag 
    //
    spi0_base_address->EVENTS_READY = 0;
    
    // Enable SPI0 Hardware
    //
    spi0_base_address->ENABLE = (SPI_ENABLE_ENABLE_Enabled << SPI_ENABLE_ENABLE_Pos);
}

/**
 */
static uint32_t nrf51_tag_spi_tx_byte_transferred()
{
    uint32_t counter = 0;

    // Wait for the transaction complete or timeout
    //
    while ((spi0_base_address->EVENTS_READY == 0) && (counter < TIMEOUT_COUNTER_10MS))
    {
        ++counter;
    }
    
    spi0_base_address->EVENTS_READY = 0;

    if ( counter >= TIMEOUT_COUNTER_10MS )
    {
        return NRF_TAG_ERROR_SPI_RX_ERROR;
    }
    else
    {
        return NRF_SUCCESS;
    }
}

/**
 */
void nrf51_tag_spi_lis3dh_cmd(const uint8_t* p_write_cmd, uint8_t* p_read_cmd)
{
    // Enable Slave CS (Active LOW) 
    //
    nrf_gpio_pin_clear(SPI_PSELSS0);
    
    // Start the SPI Master Transfer  
    
    memset(p_read_cmd, 0, LIS3DH_CMD_LENGTH);
    
    // Send the 2 byte command
    // Note: This starts the SPI Master Hardware to start clocking 
    //
    spi0_base_address->TXD = (uint32_t)p_write_cmd[LIS3DH_CMD_REG_INDEX_0];

    spi0_base_address->TXD = (uint32_t)p_write_cmd[LIS3DH_CMD_DATA_INDEX_1];

    // Read the 2 byte Response
    //
    APP_ERROR_CHECK( nrf51_tag_spi_tx_byte_transferred() );
    p_read_cmd[LIS3DH_CMD_REG_INDEX_0] = spi0_base_address->RXD;
    
    APP_ERROR_CHECK( nrf51_tag_spi_tx_byte_transferred() );
    p_read_cmd[LIS3DH_CMD_DATA_INDEX_1] = spi0_base_address->RXD;

    // Disable Slave CS (HIGH) 
    //
    nrf_gpio_pin_set(SPI_PSELSS0);
}
