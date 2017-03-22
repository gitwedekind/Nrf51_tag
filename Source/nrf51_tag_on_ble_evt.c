/**
* @file nrf51_tag_on_ble_evt.c
* @brief Source file Radio Interface BLE Event Handler.
*
*/

#include "nrf51_tag_error.h"
#include "nrf51_tag_headers.h"

//-------------------------------------------------------------------------------------------------
//  Radio Interface Event Handler Router
//-------------------------------------------------------------------------------------------------

/**@brief Function for handling the callback events for the Radio Interface.
 * 
 * @param[in]   p_ble_evt   Pointer to the BLE Event structure.
 */
void softdevice_on_ble_evt(ble_evt_t* p_ble_evt)
{
    DBG_GAP(p_ble_evt->header.evt_id);
    DBG_GATTS(p_ble_evt->header.evt_id);
    DBG_SD(p_ble_evt->header.evt_id);
    
    // --------------------------------
    // BLE GAP Event(s)
    // --------------------------------
    switch (p_ble_evt->header.evt_id)
    {
    case BLE_GAP_EVT_CONNECTED:
        nrf51_tag_gap_evt_connect(p_ble_evt);
        break;
        
    case BLE_GAP_EVT_DISCONNECTED:
        nrf51_tag_gap_evt_disconnect(p_ble_evt);
        break;
        
    case BLE_GAP_EVT_CONN_PARAM_UPDATE:
        nrf51_tag_gap_evt_connection_parameters_update(p_ble_evt);
        break;

    case BLE_GAP_EVT_SEC_PARAMS_REQUEST:
        nrf51_tag_gap_evt_security_parameters_request(p_ble_evt);
        break;
    
    case BLE_GAP_EVT_SEC_INFO_REQUEST:
        nrf51_tag_gap_evt_security_info_request(p_ble_evt);
        break;
    
    case BLE_GAP_EVT_PASSKEY_DISPLAY:
        nrf51_tag_gap_evt_passkey_display(p_ble_evt);
        break;
    
    case BLE_GAP_EVT_KEY_PRESSED:
        nrf51_tag_gap_evt_key_pressed(p_ble_evt);
        break;

    case BLE_GAP_EVT_AUTH_KEY_REQUEST:
        nrf51_tag_gap_evt_authentication_key_request(p_ble_evt);
        break;
    
    case BLE_GAP_EVT_LESC_DHKEY_REQUEST:
        nrf51_tag_gap_evt_authentication_key_request(p_ble_evt);
        break;

    case BLE_GAP_EVT_AUTH_STATUS:
        nrf51_tag_gap_evt_authentication_status(p_ble_evt);
        break;
    
    case BLE_GAP_EVT_CONN_SEC_UPDATE:
        nrf51_tag_gap_evt_connection_security_update(p_ble_evt);
        break;
    
    case BLE_GAP_EVT_TIMEOUT:
        nrf51_tag_gap_evt_timeout(p_ble_evt);
        break;

    case BLE_GAP_EVT_RSSI_CHANGED:
        nrf51_tag_gap_evt_rssi_changed(p_ble_evt);
        break;

    case BLE_GAP_EVT_ADV_REPORT:
        nrf51_tag_gap_evt_adv_report(p_ble_evt);
        break;
    
    case BLE_GAP_EVT_SEC_REQUEST:
        nrf51_tag_gap_evt_security_request(p_ble_evt);
        break;

    case BLE_GAP_EVT_CONN_PARAM_UPDATE_REQUEST:
        nrf51_tag_gap_conn_param_update_request(p_ble_evt);
        break;
    
    case BLE_GAP_EVT_SCAN_REQ_REPORT:
        nrf51_tag_gap_evt_scan_request_report(p_ble_evt);
        break;
    }

    // --------------------------------
    // BLE GATTS Event(s)
    // --------------------------------
    switch (p_ble_evt->header.evt_id)
    {
    case BLE_GATTS_EVT_WRITE:
        nrf51_tag_gatts_evt_write(p_ble_evt);
        break;
    
    case BLE_GATTS_EVT_RW_AUTHORIZE_REQUEST:
        nrf51_tag_gatts_evt_authorize_request(p_ble_evt);
        break;
    
    case BLE_GATTS_EVT_SYS_ATTR_MISSING:
        nrf51_tag_gatts_evt_system_attribute_missing(p_ble_evt);
        break;
    
    case BLE_GATTS_EVT_HVC:
        nrf51_tag_gatts_evt_handle_value_confirmation(p_ble_evt);
        break;
    
    case BLE_GATTS_EVT_SC_CONFIRM:
        nrf51_tag_gatts_evt_service_change_confirm(p_ble_evt);
        break;
    
    case BLE_GATTS_EVT_TIMEOUT:
        nrf51_tag_gatts_evt_timeout(p_ble_evt);
        break;
    }

    // --------------------------------
    // BLE Soft Device Event(s)
    // --------------------------------
    switch (p_ble_evt->header.evt_id)
    {
    case BLE_EVT_TX_COMPLETE:
        nrf51_tag_sd_evt_tx_complete(p_ble_evt);
        break;
    
    case BLE_EVT_USER_MEM_REQUEST:
        nrf51_tag_sd_evt_user_memory(p_ble_evt);
        break;

    case BLE_EVT_USER_MEM_RELEASE:
        nrf51_tag_sd_evt_user_memory_release(p_ble_evt);
        break;
    }
}
