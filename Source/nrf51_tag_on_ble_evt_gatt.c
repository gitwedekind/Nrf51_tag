/**
* @file nrf51_tag_on_ble_evt_gatt.c
* @brief Source file Radio Interface BLE Event GATT Handler(s).
*
*/

#include "nrf51_tag_error.h"
#include "nrf51_tag_headers.h"

//-------------------------------------------------------------------------------------------------
// BLE GATTS Handler(s) 
//-------------------------------------------------------------------------------------------------

/**@brief Function for handling the Write event.
 *
 * @param[in]   p_ble_evt   Pointer to the BLE Event structure.
 */
void nrf51_tag_gatts_evt_write(ble_evt_t* p_ble_evt)
{
    nrf51_tag_debug_write(p_ble_evt);
    nrf51_tag_status_write(p_ble_evt);
    nrf51_tag_configuration_write(p_ble_evt);
    nrf51_tag_activity_log_write(p_ble_evt);
}

/**@brief Function for handling the Authorize event.
 *
 * @param[in]   p_ble_evt   Pointer to the BLE Event structure.
 */
void nrf51_tag_gatts_evt_authorize_request(ble_evt_t* p_ble_evt)
{
    nrf51_tag_debug_authorize_request(p_ble_evt);
    nrf51_tag_status_authorize_request(p_ble_evt);
    nrf51_tag_configuration_authorize_request(p_ble_evt);
    nrf51_tag_activity_log_authorize_request(p_ble_evt);
}

/**@brief Function for handling the Attribute Missing event.
 *
 * @param[in]   p_ble_evt   Pointer to the BLE Event structure.
 */
void nrf51_tag_gatts_evt_system_attribute_missing(ble_evt_t* p_ble_evt)
{
    nrf51_tag_debug_system_attribute_missing(p_ble_evt);
    nrf51_tag_status_system_attribute_missing(p_ble_evt);
    nrf51_tag_configuration_system_attribute_missing(p_ble_evt);
    nrf51_tag_activity_log_system_attribute_missing(p_ble_evt);
}

/**@brief Function for handling the Handle Value event.
 *
 * @param[in]   p_ble_evt   Pointer to the BLE Event structure.
 */
void nrf51_tag_gatts_evt_handle_value_confirmation(ble_evt_t* p_ble_evt)
{
    nrf51_tag_debug_handle_value_confirmation(p_ble_evt);
    nrf51_tag_status_handle_value_confirmation(p_ble_evt);
    nrf51_tag_configuration_handle_value_confirmation(p_ble_evt);
    nrf51_tag_activity_log_handle_value_confirmation(p_ble_evt);
}

/**@brief Function for handling the Service Change Confirm event.
 *
 * @param[in]   p_ble_evt   Pointer to the BLE Event structure.
 */
void nrf51_tag_gatts_evt_service_change_confirm(ble_evt_t* p_ble_evt)
{
    nrf51_tag_debug_service_change_confirm(p_ble_evt);
    nrf51_tag_status_service_change_confirm(p_ble_evt);
    nrf51_tag_configuration_service_change_confirm(p_ble_evt);
    nrf51_tag_activity_log_service_change_confirm(p_ble_evt);
}

/**@brief Function for handling the GATTS Timeout event.
 *
 * @param[in]   p_ble_evt   Pointer to the BLE Event structure.
 */
void nrf51_tag_gatts_evt_timeout(ble_evt_t* p_ble_evt)
{
    nrf51_tag_debug_timeout(p_ble_evt);
    nrf51_tag_status_timeout(p_ble_evt);
    nrf51_tag_configuration_timeout(p_ble_evt);
    nrf51_tag_activity_log_timeout(p_ble_evt);
}
