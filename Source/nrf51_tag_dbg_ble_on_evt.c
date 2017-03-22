/**
* @file dbg_ble_on_evt.c
* @brief Source file for the BLE Event Debugging.
*
*/

#include "nrf51_tag_error.h"
#include "nrf51_tag_headers.h"

//-------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------
#ifdef ENABLE_GAP_DEBUG

/**@brief Function to print BLE GAP String (Id's)
 */
void nrf51_tag_ble_gap_evt_debug(uint32_t evt_id)
{
    switch (evt_id)
    {
    case BLE_GAP_EVT_CONNECTED: // Connection established
        DBG("--> BLE_GAP_EVT_CONNECTED (0x%x)\r\n", evt_id);
        break;
        
    case BLE_GAP_EVT_DISCONNECTED: // Disconnected from peer
        DBG("--> BLE_GAP_EVT_DISCONNECTED (0x%x)\r\n", evt_id);
        break;
        
    case BLE_GAP_EVT_CONN_PARAM_UPDATE: // Connection Parameters updated
        DBG("--> BLE_GAP_EVT_CONN_PARAM_UPDATE (0x%x)\r\n", evt_id);
        break;
        
    case BLE_GAP_EVT_SEC_PARAMS_REQUEST: // Request to provide security parameters
        DBG("--> BLE_GAP_EVT_SEC_PARAMS_REQUEST (0x%x)\r\n", evt_id);
        break;
        
    case BLE_GAP_EVT_SEC_INFO_REQUEST: // Request to provide security information
        DBG("--> BLE_GAP_EVT_SEC_INFO_REQUEST (0x%x)\r\n", evt_id);
        break;
        
    case BLE_GAP_EVT_PASSKEY_DISPLAY: // Request to display a passkey to the user
        DBG("--> BLE_GAP_EVT_PASSKEY_DISPLAY (0x%x)\r\n", evt_id);
        break;
        
    case BLE_GAP_EVT_KEY_PRESSED: // Notification of a keypress on the remote device
        DBG("--> BLE_GAP_EVT_KEY_PRESSED (0x%x)\r\n", evt_id);
        break;

    case BLE_GAP_EVT_AUTH_KEY_REQUEST: // Request to provide an authentication key
        DBG("--> BLE_GAP_EVT_AUTH_KEY_REQUEST (0x%x)\r\n", evt_id);
        break;
        
    case BLE_GAP_EVT_LESC_DHKEY_REQUEST: // Request to calculate an LE Secure Connections DHKey
        DBG("--> BLE_GAP_EVT_LESC_DHKEY_REQUEST (0x%x)\r\n", evt_id);
        break;

    case BLE_GAP_EVT_AUTH_STATUS: // Authentication procedure completed with status
        DBG("--> BLE_GAP_EVT_AUTH_STATUS (0x%x)\r\n", evt_id);
        break;
        
    case BLE_GAP_EVT_CONN_SEC_UPDATE: // Connection security updated
        DBG("--> BLE_GAP_EVT_CONN_SEC_UPDATE (0x%x)\r\n", evt_id);
        break;
        
    case BLE_GAP_EVT_TIMEOUT: // Timeout expired
        DBG("--> BLE_GAP_EVT_TIMEOUT (0x%x)\r\n", evt_id);
        break;
        
    case BLE_GAP_EVT_RSSI_CHANGED: // Signal strength measurement report
        DBG("--> BLE_GAP_EVT_RSSI_CHANGED (0x%x)\r\n", evt_id);
        break;

    case BLE_GAP_EVT_ADV_REPORT: // Advertising report
        DBG("--> BLE_GAP_EVT_ADV_REPORT (0x%x)\r\n", evt_id);
        break;

    case BLE_GAP_EVT_SEC_REQUEST: // Security Request
        DBG("--> BLE_GAP_EVT_SEC_REQUEST (0x%x)\r\n", evt_id);
        break;

    case BLE_GAP_EVT_CONN_PARAM_UPDATE_REQUEST: // Connection Parameter Update Request
        DBG("--> BLE_GAP_EVT_CONN_PARAM_UPDATE_REQUEST (0x%x)\r\n", evt_id);
        break;

    case BLE_GAP_EVT_SCAN_REQ_REPORT: // Scan request report
        DBG("--> BLE_GAP_EVT_SCAN_REQ_REPORT (0x%x)\r\n", evt_id);
        break;
    }
}

#endif // ENABLE_GAP_DEBUG

//-------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------
#ifdef ENABLE_GATTS_DEBUG

/**@brief Function to print BLE GATT Id's
 */
void nrf51_tag_dbg_ble_gatts_evt(uint32_t evt_id)
{
    switch (evt_id)
    {
    case BLE_GATTS_EVT_WRITE: // Write operation performed
        DBG("--> BLE_GATTS_EVT_WRITE (0x%x)\r\n", evt_id);
        break;
    case BLE_GATTS_EVT_RW_AUTHORIZE_REQUEST: // Read/Write Authorization request
        DBG("--> BLE_GATTS_EVT_RW_AUTHORIZE_REQUEST (0x%x)\r\n", evt_id);
        break;
    case BLE_GATTS_EVT_SYS_ATTR_MISSING: // A persistent system attribute access is pending
        DBG("--> BLE_GATTS_EVT_SYS_ATTR_MISSING (0x%x)\r\n", evt_id); // waiting for sd_ble_gatts_sys_attr_set()
        break;
    case BLE_GATTS_EVT_HVC: // Handle Value Confirmation
        DBG("--> BLE_GATTS_EVT_HVC (0x%x)\r\n", evt_id);
        break;
    case BLE_GATTS_EVT_SC_CONFIRM: // Service Changed Confirmation
        DBG("--> BLE_GATTS_EVT_SC_CONFIRM (0x%x)\r\n", evt_id);
        break;
    case BLE_GATTS_EVT_TIMEOUT: // GATTS Timeout
        DBG("--> BLE_GATTS_EVT_TIMEOUT (0x%x)\r\n", evt_id);
        break;
    }
}

#endif // ENABLE_GATTS_DEBUG

//-------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------
#ifdef ENABLE_SD_DEBUG

/**@brief Function to print Soft Device Id's
 */
void nrf51_tag_dbg_sd_evt(uint32_t evt_id)
{
    switch (evt_id)
    {
    case BLE_EVT_TX_COMPLETE: // Transmission Complete
        DBG("--> BLE_EVT_TX_COMPLETE (0x%x)\r\n", evt_id);
        break;
    case BLE_EVT_USER_MEM_REQUEST: // User Memory request
        DBG("--> BLE_EVT_USER_MEM_REQUEST (0x%x\r\n)", evt_id);
        break;
    case BLE_EVT_USER_MEM_RELEASE: // User Memory release
        DBG("--> BLE_EVT_USER_MEM_RELEASE (0x%x)\r\n", evt_id);
        break;
    }
}

#endif // ENABLE_SD_DEBUG

//-------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------
#ifdef ENABLE_AUTH_STATUS_DEBUG

/**@brief Function to print auth_status
 */
void nrf51_tag_dbg_authentication_status(ble_gap_evt_auth_status_t as)
{
    DBG("--> GAP Authentication Status\r\n");
    
    DBG(" - auth_status      : %d\r\n", as.auth_status);
    DBG(" - error src        : %d\r\n", as.error_src);
    DBG(" - bonded           : %d\r\n", as.bonded);

    DBG(" - sm1_levels       : lv1: %d lv2: %d lv3: %d\r\n",
        as.sm1_levels.lv1, as.sm1_levels.lv2, as.sm1_levels.lv3);

    DBG(" - sm2_levels       : lv1: %d lv2: %d lv3: %d\r\n",
        as.sm2_levels.lv1, as.sm2_levels.lv2, as.sm2_levels.lv3);
    
    DBG(" - kdist_own        : enc: %d id: %d irk: %d link: %d sign: %d\r\n",
        as.kdist_own.enc, as.kdist_own.id, as.kdist_own.link, as.kdist_own.sign);

    DBG(" - kdist_peer       : enc: %d id: %d irk: %d link: %d sign: %d\r\n",
        as.kdist_peer.enc, as.kdist_peer.id, as.kdist_peer.link, as.kdist_peer.sign);
}

/**@brief Function to print auth_status
 */
void nrf51_tag_dbg_gap_enc_key(char* p_key_name, ble_gap_enc_key_t key)
{
    DBG("--> GAP Enc Key: %s\r\n", p_key_name);
    
    DBG(" - auth   : %d\r\n", key.enc_info.auth);
    DBG(" - lesc   : %d\r\n", key.enc_info.lesc);
    DBG(" - ltk_len: %d\r\n", key.enc_info.ltk_len);

    DBG_ADDRESS(" - ltk", key.enc_info.ltk, key.enc_info.ltk_len);

    DBG(" - ediv: %d\r\n", key.master_id.ediv);
    DBG_ADDRESS(" - rand", key.master_id.rand, BLE_GAP_SEC_RAND_LEN);
}

void nrf51_tag_dbg_gap_id_key(char* p_key_name, ble_gap_id_key_t key)
{
    DBG("--> GAP Id Key: %s\r\n", p_key_name);
    
    DBG_ADDRESS(" - ltk: ", key.id_info.irk, BLE_GAP_SEC_KEY_LEN);
    
    DBG(" - addr type: %d\r\n", key.id_addr_info.addr_type);
    DBG_ADDRESS(" - addr: ", key.id_addr_info.addr, BLE_GAP_ADDR_LEN);
}

#endif // ENABLE_AUTH_STATUS_DEBUG

//-------------------------------------------------------------------------------------------------
// ENABLE_WHITELIST_DEBUG
//-------------------------------------------------------------------------------------------------
#ifdef ENABLE_WHITELIST_DEBUG

/**
 */
void nrf51_tag_whitelist(ble_gap_whitelist_t* p_whitelist)
{
    DBG("--> Whitelist\r\n");
    
    DBG(" - addr_cnt: %d\r\n", p_whitelist->addr_count);
    DBG(" - irk_cnt : %d\r\n", p_whitelist->irk_count);
    
    ble_gap_addr_t* p_gap_addr = *p_whitelist->pp_addrs;
    
    if ( p_whitelist->addr_count )
    {
       DBG(" - addr_type : %d\r\n", p_gap_addr->addr_type);
       DBG_ADDRESS(" - addr: ", p_gap_addr->addr, sizeof(p_gap_addr->addr) );
    }

    ble_gap_irk_t* p_gap_irk = *p_whitelist->pp_irks;
    
    if ( p_whitelist->irk_count )
    {
       DBG(" - addr_type : %d\r\n", p_gap_addr->addr_type);
       DBG_ADDRESS(" - irk: ", p_gap_irk->irk, sizeof(p_gap_irk->irk) );
    }
}

#endif // ENABLE_WHITELIST_DEBUG

//-------------------------------------------------------------------------------------------------
// ENABLE_ADV_FILTER_POLICY_DEBUG
//-------------------------------------------------------------------------------------------------
#ifdef ENABLE_ADV_FILTER_POLICY_DEBUG

/**
 */
void nrf51_tag_adv_filter_policy(uint8_t fp)
{
    switch (fp)
    {
    case BLE_GAP_ADV_FP_ANY: // Allow scan requests and connect requests from any device
        DBG(" - BLE_GAP_ADV_FP_ANY (0x%x)\r\n", fp);
        break;
    case BLE_GAP_ADV_FP_FILTER_SCANREQ: // Filter scan requests with whitelist
        DBG(" - BLE_GAP_ADV_FP_FILTER_SCANREQ (0x%x)\r\n", fp);
        break;
    case BLE_GAP_ADV_FP_FILTER_CONNREQ: // Filter connect requests with whitelist
        DBG(" - BLE_GAP_ADV_FP_FILTER_CONNREQ (0x%x)\r\n", fp);
        break;
    case BLE_GAP_ADV_FP_FILTER_BOTH: // Filter both scan and connect requests with whitelist
        DBG(" - BLE_GAP_ADV_FP_FILTER_BOTH (0x%x)\r\n", fp);
        break;
    }
}

#endif // ENABLE_ADV_FILTER_POLICY_DEBUG

//-------------------------------------------------------------------------------------------------
// ENABLE_SEC_INFO_REQUEST_DEBUG
//-------------------------------------------------------------------------------------------------
#ifdef ENABLE_SEC_INFO_REQUEST_DEBUG

/**@brief Function to print sec_info_request
 */
void nrf51_tag_dbg_sec_info_request(ble_gap_evt_sec_info_request_t sir)
{
    DBG("\r\n--> GAP Security Info Request\r\n");

    DBG(" - addr type       : %d\r\n", sir.peer_addr.addr_type);
    DBG_ADDRESS(" - peer address    : ", sir.peer_addr.addr, sizeof(sir.peer_addr.addr));

    DBG(" - Encryption Div  : 0x%x\r\n", sir.div);
    DBG(" - enc_info        : 0x%x\r\n", sir.enc_info);
    DBG(" - id_info         : 0x%x\r\n", sir.id_info);
    DBG(" - sign_info       : 0x%x\r\n", sir.sign_info);
}

#endif // ENABLE_SEC_INFO_REQUEST_DEBUG

//-------------------------------------------------------------------------------------------------
// ENABLE_GAP_ENC_INFO_DEBUG
//-------------------------------------------------------------------------------------------------
#ifdef ENABLE_GAP_ENC_INFO_DEBUG

/**@brief Function to print gap_enc_info_request
 */
void nrf51_tag_dbg_gap_enc_info(ble_gap_enc_info_t ir)
{
    DBG("\r\n--> GAP Encryption Information");

    DBG(" - Encryption Div  : 0x%x\r\n", ir.div);
    DBG(" - auth            : 0x%x\r\n", ir.auth);
    DBG_ADDRESS(" - LTK             : ", ir.ltk, ir.ltk_len);
    DBG(" - LTK Length      : %d\r\n", ir.ltk_len);
}

#endif // ENABLE_GAP_ENC_INFO_DEBUG
