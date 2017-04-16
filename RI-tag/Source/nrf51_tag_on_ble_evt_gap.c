/**
* @file nrf51_tag_on_ble_evt_gap.c
* @brief Source file Radio Interface BLE Event GAP Handler(s).
*
*/

#include "nrf51_tag_error.h"
#include "nrf51_tag_headers.h"

//-------------------------------------------------------------------------------------------------
// BLE GAP Handler(s) 
//-------------------------------------------------------------------------------------------------

/**@brief Function for handling the Connect event - BLE_GAP_EVT_CONNECTED.
 *
 * @param[in]   p_ble_evt   Pointer to the BLE Event structure.
 */
void nrf51_tag_gap_evt_connect(ble_evt_t* p_ble_evt)
{
    nrf51_tag_set_connection_settings
    (
        p_ble_evt->evt.gap_evt.conn_handle,
        p_ble_evt->evt.gap_evt.params.connected
    );
}

/**@brief Function for handling the Disconnect event - BLE_GAP_EVT_DISCONNECTED.
 *
 * @param[in]   p_ble_evt   Pointer to the BLE Event structure.
 */
void nrf51_tag_gap_evt_disconnect(ble_evt_t* p_ble_evt)
{
    nrf51_tag_disconnect(p_ble_evt->evt.gap_evt.params.disconnected);
    
    nrf51_tag_start_advertising();
}

/**@brief Function for handling the Connection Parameters Update event - BLE_GAP_EVT_CONN_PARAM_UPDATE.
 *
 * @param[in]   p_ble_evt   Pointer to the BLE Event structure.
 */
void nrf51_tag_gap_evt_connection_parameters_update(ble_evt_t* p_ble_evt)
{
//    nrf51_tag_update_gap_connection_parameters(
//        &p_ble_evt->evt.gap_evt.params.conn_param_update.conn_params);
}

/**@brief Function for handling the Security Parameters Request event - BLE_GAP_EVT_SEC_PARAMS_REQUEST.
 *
 * @param[in]   p_ble_evt   Pointer to the BLE Event structure.
 */
void nrf51_tag_gap_evt_security_parameters_request(ble_evt_t* p_ble_evt)
{
    uint32_t err_code = NRF_SUCCESS;
    
    ble_gap_evt_sec_params_request_t sec_params_request = p_ble_evt->evt.gap_evt.params.sec_params_request;
    
    nrf51_tag_set_security_parameters_request(sec_params_request);

    ble_gap_sec_params_t peer_params = sec_params_request.peer_params;
    
    if ( peer_params.bond )
    {
        err_code = sd_ble_gap_sec_params_reply
        (
            nrf51_tag_get_connection_handle(),
            BLE_GAP_SEC_STATUS_SUCCESS,
            nrf51_tag_get_security_parameters(),
            nrf51_tag_get_security_parameters_keysets()
        );
        APP_ERROR_CHECK(err_code);
    }
}

/**@brief Function for handling the Security Info Request event - BLE_GAP_EVT_SEC_INFO_REQUEST.
 *
 * @param[in]   p_ble_evt   Pointer to the BLE Event structure.
 */
void nrf51_tag_gap_evt_security_info_request(ble_evt_t* p_ble_evt)
{
    nrf51_tag_set_gap_sec_info_request(
        p_ble_evt->evt.gap_evt.params.sec_info_request);
}

/**@brief Function for handling the Passkey Display event - BLE_GAP_EVT_PASSKEY_DISPLAY.
 *
 * @param[in]   p_ble_evt   Pointer to the BLE Event structure.
 */
void nrf51_tag_gap_evt_passkey_display(ble_evt_t* p_ble_evt)
{
}

/**@brief Function for handling the Key Pressed event - BLE_GAP_EVT_KEY_PRESSED.
 *
 * @param[in]   p_ble_evt   Pointer to the BLE Event structure.
 */
void nrf51_tag_gap_evt_key_pressed(ble_evt_t* p_ble_evt)
{
}

/**@brief Function for handling the Authentication Key Request event - BLE_GAP_EVT_AUTH_KEY_REQUEST.
 *
 * @param[in]   p_ble_evt   Pointer to the BLE Event structure.
 */
void nrf51_tag_gap_evt_authentication_key_request(ble_evt_t* p_ble_evt)
{
}

/**@brief Function for handling the Authentication Status event - BLE_GAP_EVT_AUTH_STATUS.
 *
 * @param[in]   p_ble_evt   Pointer to the BLE Event structure.
 */
void nrf51_tag_gap_evt_authentication_status(ble_evt_t* p_ble_evt)
{
    nrf51_tag_set_gap_auth_status(
        p_ble_evt->evt.gap_evt.params.auth_status);
}

/**@brief Function for handling the Connection Security Update event - BLE_GAP_EVT_CONN_SEC_UPDATE.
 *
 * @param[in]   p_ble_evt   Pointer to the BLE Event structure.
 */
void nrf51_tag_gap_evt_connection_security_update(ble_evt_t* p_ble_evt)
{
    nrf51_tag_set_gap_conn_sec(
        p_ble_evt->evt.gap_evt.params.conn_sec_update.conn_sec);
}

/**@brief Function for handling the GAP Timeout event - BLE_GAP_EVT_TIMEOUT.
 *
 * @param[in]   p_ble_evt   Pointer to the BLE Event structure.
 */
void nrf51_tag_gap_evt_timeout(ble_evt_t* p_ble_evt)
{
    DBG("--> %s", BLE_GAP_TIMEOUT[p_ble_evt->evt.gap_evt.params.timeout.src]);
}

/**@brief Function for handling the RSSI Changed event - BLE_GAP_EVT_RSSI_CHANGED.
 *
 * @param[in]   p_ble_evt   Pointer to the BLE Event structure.
 */
void nrf51_tag_gap_evt_rssi_changed(ble_evt_t* p_ble_evt)
{
}

/**@brief Function for handling the RSSI Changed event - BLE_GAP_EVT_ADV_REPORT.
 *
 * @param[in]   p_ble_evt   Pointer to the BLE Event structure.
 */
void nrf51_tag_gap_evt_adv_report(ble_evt_t* p_ble_evt)
{
}

/**@brief Function for handling the RSSI Changed event - BLE_GAP_EVT_SEC_REQUEST.
 *
 * @param[in]   p_ble_evt   Pointer to the BLE Event structure.
 */
void nrf51_tag_gap_evt_security_request(ble_evt_t* p_ble_evt)
{
}

/**@brief Function for handling the RSSI Changed event - BLE_GAP_EVT_CONN_PARAM_UPDATE_REQUEST.
 *
 * @param[in]   p_ble_evt   Pointer to the BLE Event structure.
 */
void nrf51_tag_gap_conn_param_update_request(ble_evt_t* p_ble_evt)
{
}

/**@brief Function for handling the RSSI Changed event - BLE_GAP_EVT_SCAN_REQ_REPORT.
 *
 * @param[in]   p_ble_evt   Pointer to the BLE Event structure.
 */
void nrf51_tag_gap_evt_scan_request_report(ble_evt_t* p_ble_evt)
{
}
