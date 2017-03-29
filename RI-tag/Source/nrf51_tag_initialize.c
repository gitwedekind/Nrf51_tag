/**
* @file nrf51_tag_initialize.c
* @brief Source file for Initializing the nrf51 tag application code.
*
*/

#include "nrf51_tag_error.h"
#include "nrf51_tag_initialize.h"

// ----------------------------------------------------------------------------
// 
// ----------------------------------------------------------------------------

uint32_t nrf51_tag_temperature_get(void)
{
    int32_t temp = 0;
    uint32_t err_code = NRF_SUCCESS;
    
    err_code = sd_temp_get(&temp);
    APP_ERROR_CHECK(err_code);
    
    temp = (temp / 4) * 100;
    
    int8_t exponent = -2;
    
    return ((exponent & 0xFF) << 24) | (temp & 0x00FFFFFF);
}

/**@brief Function for initializing the Dexcom application code.
 */
void nrf51_tag_initialize(void)
{
    DBG_INITIALIZE();
    
    DBG_TOTAL_RAM_SIZE();
    
    DBG_RAMON();
    DBG_RESET_REASON();
    DBG_GPRR();
    DBG_TX_POWER();
    
    initialize_power_manage();

    nrf51_tag_stack_init();
    
    nrf51_tag_timers_init();

    nrf51_tag_spi0_master_init();
#if 1
    
    uint8_t tx_data[2] = {0x8F,0x00};
    uint8_t rx_data[2] = {0x00, 0x00};
    
    while (1) 
    {
        nrf51_tag_spi_master_tx_rx(tx_data, rx_data);
        
        DBG_HEX_DUMP("Rx Data", rx_data, sizeof(rx_data));
        
        nrf_delay_ms(1000);
    }
#endif
    DBG_GAP_ADDR();
    DBG_TEMPERATURE();

    DBG_INITIALIZE_COMPLETE();
}
