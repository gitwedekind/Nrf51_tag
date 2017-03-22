/**
* @file nrf51_tag_tx_power.c
* @brief Source file for setting the Transmit Power.
*
*/

#include "nrf51_tag_error.h"
#include "nrf51_tag_tx_power.h"

static tx_power_level_e s_tx_power_level = DBM_0;

// ---------------------------------------------------------------------------
// Interface Functions
// ---------------------------------------------------------------------------

/**@brief Function to set the RF transmit power.
 *
 * Function sets the current RF transmit power value.
 *
 * @param Transmit Power Level 
 */
void nrf51_tag_set_tx_power(tx_power_level_e tx_power_level)
{
    uint32_t err_code = NRF_SUCCESS;
    
    DBG_INITIALIZE_TX_POWER();
    
    s_tx_power_level = tx_power_level;

    err_code = sd_ble_gap_tx_power_set( s_tx_power_level );
    APP_ERROR_CHECK(err_code);   
}

/**@brief Function to get the RF transmit power.
 * 
 * @return transmit power in Dbm
 */
tx_power_level_e nrf51_tag_get_tx_power(void)
{
    return s_tx_power_level;
}
