/**
* @file nrf51_tag_radio_notification.c
* @brief Source file for the Nordic Radio Notfication Interface.
*
*/

#include "nrf51_tag_error.h"
#include "nrf51_tag_headers.h"

// ---------------------------------------------------------------------------
// API Functions
// ---------------------------------------------------------------------------

/**@brief Function for the Radio Notification Initialization.
 */
void nrf51_tag_radio_notification_init(void)
{
    uint32_t err_code = NRF_SUCCESS;
    
    DBG_INITIALIZE_NOTIFICATION();
    
    err_code = sd_radio_notification_cfg_set
    (
        NRF_RADIO_NOTIFICATION_TYPE_INT_ON_BOTH,
        NRF_RADIO_NOTIFICATION_DISTANCE_5500US
    );

    
    APP_ERROR_CHECK(err_code);
}
