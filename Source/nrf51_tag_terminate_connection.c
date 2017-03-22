/**
* @file nrf51_tag_terminate_connection.c
* @brief Source File for Connection Management.
*
*/

#include "nrf51_tag_error.h"
#include "nrf51_tag_headers.h"

// ---------------------------------------------------------------------------
// RDI Terminate Interface Function
// ---------------------------------------------------------------------------

/**@brief Function to terminate the BLE Connection.
 */
void nrf51_tag_terminate_connection(void)
{
    if ( nrf51_tag_get_connection_handle() != BLE_CONN_HANDLE_INVALID )
    {
        uint32_t err_code = sd_ble_gap_disconnect
            (nrf51_tag_get_connection_handle(), BLE_HCI_REMOTE_USER_TERMINATED_CONNECTION);
        
        ble_gap_evt_disconnected_t ble_gap_evt_disconnected = {0};
            
        ble_gap_evt_disconnected.reason = BLE_HCI_REMOTE_USER_TERMINATED_CONNECTION;
        
        nrf51_tag_disconnect(ble_gap_evt_disconnected); 
        APP_ERROR_CHECK(err_code);
    }
}
