/** 
 * @file nrf51)tag_spi_master.c
 *
 */

#include "nrf51_tag_error.h"
#include "nrf51_tag_spi_master.h"

//------------------------------------------------------------------------------
// static module variable(s)
//------------------------------------------------------------------------------

static uint8_t rx_data[CTRL_LENGTH] = {0x00,0x00};

/**
*/
static NRF_SPI_Type* spi0_base_address = (NRF_SPI_Type*)NRF_SPI0;

//------------------------------------------------------------------------------
// static Module Interface Functions
//------------------------------------------------------------------------------

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
        NRF_GPIOTE->EVENTS_PORT = 0;
    }
}

/**
 */
static bool nrf51_tag_spi_tx_byte_transferred()
{
    uint32_t counter = 0;

    // Wait for the transaction complete or timeout
    //
    while ((spi0_base_address->EVENTS_READY == 0U)) // && (counter < TIMEOUT_COUNTER_10MS))
    {
        ++counter;
    }

    if ( counter >= TIMEOUT_COUNTER_10MS )
    {
        return false;
    }
    else
    {
        return true;
    }
}

//------------------------------------------------------------------------------
// Public Module Interface Functions
//------------------------------------------------------------------------------

/**
 */
void nrf51_tag_gpio_port_event_init(nrf_gpio_pin_sense_t pin_polarity)
{
    NVIC_DisableIRQ(GPIOTE_IRQn);

    nrf_gpio_cfg_sense_input(TAG_NRF_IRQ_PIN, NRF_GPIO_PIN_NOPULL, pin_polarity);
    
    NRF_GPIOTE->INTENCLR = 0xFFFFFFFF;
    NRF_GPIOTE->INTENSET = GPIOTE_INTENSET_PORT_Msk;

    NVIC_ClearPendingIRQ(GPIOTE_IRQn);
    NVIC_SetPriority(GPIOTE_IRQn, APP_IRQ_PRIORITY_HIGH);

    NVIC_EnableIRQ(GPIOTE_IRQn);
}

/**
 */
void nrf51_tag_spi0_master_init()
{
    uint32_t config_mode = 0;
    
    // Get the SPI0 base address 
    //
    spi0_base_address = (NRF_SPI_Type*)NRF_SPI0;

    // Configure the GPIOTE PORT_EVENTS input signal
    //
    //nrf51_tag_gpio_port_event_init(NRF_GPIO_PIN_SENSE_LOW);    

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

    // disable (Set) slave select (inactive high) 
    //
    nrf_gpio_pin_set(SPI_PSELSS0);

    // Set the SPI Clock Frequency 
    //
    spi0_base_address->FREQUENCY = (uint32_t) SPI0_OPERATING_FREQUENCY;

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
    config_mode = (SPI_CONFIG_CPHA_Trailing << SPI_CONFIG_CPHA_Pos) | (SPI_CONFIG_CPOL_ActiveLow << SPI_CONFIG_CPOL_Pos);
    spi0_base_address->CONFIG = (config_mode | (SPI_CONFIG_ORDER_MsbFirst << SPI_CONFIG_ORDER_Pos));

    // Clear the Event Ready Flag 
    //
    spi0_base_address->EVENTS_READY = 0U;

    // Enable SPI0 Hardware
    //
    spi0_base_address->ENABLE = (SPI_ENABLE_ENABLE_Enabled << SPI_ENABLE_ENABLE_Pos);
}

/**
 */

#define SPI_MASTER_CLOCK_DELAY 100
#define SPI_SLAVE_CS_DELAY     50
#define SPI_FIRST_BYTE_DELAY   10

bool nrf51_tag_spi_master_tx_rx(const uint8_t* p_write_cmd, uint8_t* p_read_cmd)
{
    uint32_t index = 0;
    bool bTransferSuccess = true;
    bool bFirstByteDelay = true;
    
    // Enable Slave CS (Active LOW) 
    //
    nrf_gpio_pin_clear(SPI_PSELSS0);
    
    // Allow SPI Slave a few us to Initialize
    //
    nrf_delay_us(SPI_SLAVE_CS_DELAY);

    // Start the SPI Master Transfer  
    
    index = 0;
    
    // Send the Tx Byte
    // Note: This starts the SPI Master Hardware to start clocking 
    //
    DBG("--> tx_data[%d]: 0x%x\r\n", index, p_write_cmd[index]);
    spi0_base_address->TXD = (uint32_t)p_write_cmd[index];
    DBG("--> EVENTS_READY 0x%x\r\n", spi0_base_address->EVENTS_READY);

    // Wait / Verify the Tx byte transfered successfully
    // Note: Break out of the loop if there is an error
    //
    if ( !nrf51_tag_spi_tx_byte_transferred() )
    {
        bTransferSuccess = false;
    }
        
    DBG("--> EVENTS_READY 0x%x, %d\r\n", spi0_base_address->EVENTS_READY, bTransferSuccess);

    // Read the Rx Byte
    //
    uint32_t rx0 = spi0_base_address->RXD;
    DBG("--> rx_data[%d]: 0x%x\r\n", index, rx0);
    
    p_read_cmd[index] = (uint8_t)rx0;
    
    ++index;
    
    DBG("--> tx_data[%d]: 0x%x\r\n", index, p_write_cmd[index]);
    spi0_base_address->TXD = (uint32_t)p_write_cmd[index];
    DBG("--> EVENTS_READY 0x%x\r\n", spi0_base_address->EVENTS_READY);
    
    // Wait / Verify the Tx byte transfered successfully
    // Note: Break out of the loop if there is an error
    //
    if ( !nrf51_tag_spi_tx_byte_transferred() )
    {
        bTransferSuccess = false;
    }

    DBG("--> EVENTS_READY 0x%x, %d\r\n", spi0_base_address->EVENTS_READY, bTransferSuccess);

    // Read the Rx Byte
    //
    uint32_t rx1 = spi0_base_address->RXD;
    DBG("--> rx_data[%d]: 0x%x\r\n", index, rx1);
    
    p_read_cmd[index] = (uint8_t)rx1;

    // Clear the EVENTS_READY flag 
    //
    spi0_base_address->EVENTS_READY = 0;
    
    if (bFirstByteDelay)
    {
        bFirstByteDelay = false;
        nrf_delay_us(SPI_FIRST_BYTE_DELAY);
    }

    // Allow final clock phase to complete before clearing CS
    //
    nrf_delay_us(SPI_MASTER_CLOCK_DELAY);
    
    // Disable Slave CS (HIGH) 
    //
    nrf_gpio_pin_set(SPI_PSELSS0);

    return bTransferSuccess;
}
