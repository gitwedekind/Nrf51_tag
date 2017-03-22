/**
* @file nrf51_tag_nrd_connection_security.c
* @brief Source File for BLE Connection Security Interface.
*
*/

#include "nrf51_tag_error.h"
#include "nrf51_tag_headers.h"

// ---------------------------------------------------------------------------
// Connection Security Variables
// ---------------------------------------------------------------------------

/**< GAP Connection Security 
*/
static ble_gap_conn_sec_t s_ble_gap_conn_sec = {0};

/**< GAP Security Info Request
*/
ble_gap_evt_sec_info_request_t s_sec_info_request = {0};

// ---------------------------------------------------------------------------
// GAP Connection Security  Functions
// ---------------------------------------------------------------------------

/**@brief Function to initialize the BLE GAP Connection Security.
 */
void nrf51_tag_initialize_gap_conn_sec(void)
{
    DBG_INITIALIZE_GAP_CONN_SEC();
    
    memset(&s_ble_gap_conn_sec, '\0', sizeof(s_ble_gap_conn_sec));
}

/**@brief Function to set the BLE BLE GAP Connection Security.
 *
 * @param GAP Connection Security structure
 */
void nrf51_tag_set_gap_conn_sec(ble_gap_conn_sec_t ble_gap_conn_sec)
{
    s_ble_gap_conn_sec = ble_gap_conn_sec;
}

/**@brief Function to get the BLE GAP Connection Security Encryption Key Size.
 *
 * @return Encryption Key Size
 */
uint8_t nrf51_tag_get_conn_sec_key_size(void)
{
    return s_ble_gap_conn_sec.encr_key_size;
}

/**@brief Function to get the BLE GAP Connection Security Mode.
 *
 * @return Connection Security Mode
 */
uint8_t nrf51_tag_get_conn_sec_mode(void)
{
    return s_ble_gap_conn_sec.sec_mode.sm;
}

/**@brief Function to get the BLE GAP Connection Security Level.
 *
 * @return Connection Security Level
 */
uint8_t nrf51_tag_get_conn_sec_level(void)
{
    return s_ble_gap_conn_sec.sec_mode.lv;
}

// ---------------------------------------------------------------------------
// GAP Security Info Request Functions
// ---------------------------------------------------------------------------

/**@brief Function to initialize the BLE GAP Security Info Request.
 */
void nrf51_tag_initialize_gap_sec_info_request(void)
{
    DBG_INITIALIZE_GAP_SEC_INFO();
    
    memset(&s_sec_info_request, '\0', sizeof(s_sec_info_request));
}

/**@brief Function to set the BLE GAP Security Info Request.
 */
void nrf51_tag_set_gap_sec_info_request(ble_gap_evt_sec_info_request_t sec_info_request)
{
    s_sec_info_request = sec_info_request;
}

/**@brief Function to get the BLE GAP Security Info Request.
 */
ble_gap_evt_sec_info_request_t nrf51_tag_get_gap_sec_info_request(void)
{
    return s_sec_info_request;
}
