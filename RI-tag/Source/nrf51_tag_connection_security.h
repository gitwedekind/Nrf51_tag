/**
* @file nrf51_tag_connection_security.h
* @brief Header file for BLE Connection Security Interface.
*
*/

#pragma once

#include "nrf51_tag_headers.h"

// ---------------------------------------------------------------------------
// Interface Functions
// ---------------------------------------------------------------------------

/**@brief Function to initialize the BLE GAP Connection Security.
 */
void nrf51_tag_initialize_gap_conn_sec(void);

/**@brief Function to set the BLE BLE GAP Connection Security.
 */
void nrf51_tag_set_gap_conn_sec(ble_gap_conn_sec_t ble_gap_conn_sec);

/**@brief Function to get the BLE GAP Connection Security Encryption Key Size.
 */
uint8_t nrf51_tag_get_conn_sec_key_size(void);

/**@brief Function to get the BLE GAP Connection Security Mode.
 */
uint8_t nrf51_tag_get_conn_sec_mode(void);

/**@brief Function to get the BLE GAP Connection Security Level.
 */
uint8_t nrf51_tag_get_conn_sec_level(void);

// ---------------------------------------------------------------------------
// Interface Functions
// ---------------------------------------------------------------------------

/**@brief Function to initialize the BLE GAP Security Info Request.
 */
void nrf51_tag_initialize_gap_sec_info_request(void);

/**@brief Function to set the BLE GAP Security Info Request.
 */
void nrf51_tag_set_gap_sec_info_request(ble_gap_evt_sec_info_request_t sec_info_request);

/**@brief Function to get the BLE GAP Security Info Request.
 */
ble_gap_evt_sec_info_request_t nrf51_tag_get_gap_sec_info_request(void);

// ------------------------------------------------------------------------------------------------
// Debug Message(s)
// ------------------------------------------------------------------------------------------------
#define ENABLE_CONNECTION_SECURITY_MESSAGES

#if defined(ENABLE_CONNECTION_SECURITY_MESSAGES)

#define DBG_INITIALIZE_GAP_CONN_SEC() FUNCTION()
#define DBG_INITIALIZE_GAP_SEC_INFO() FUNCTION()

#else

#define DBG_INITIALIZE_GAP_CONN_SEC()
#define DBG_INITIALIZE_GAP_SEC_INFO()

#endif
