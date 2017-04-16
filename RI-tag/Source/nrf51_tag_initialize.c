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

int8_t nrf51_tag_temperature_get(void)
{
    int32_t temp = 0;
    uint32_t err_code = NRF_SUCCESS;
    
    err_code = sd_temp_get(&temp);
    APP_ERROR_CHECK(err_code);
    
    temp /= 4;
    
    return temp;
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

    nrf51_tag_timers_init();

    nrf51_tag_stack_init();
    

    //nrf51_tag_lis3dh_init();
    
    DBG_GAP_ADDR();
    DBG_TEMPERATURE();

    DBG_INITIALIZE_COMPLETE();
}
