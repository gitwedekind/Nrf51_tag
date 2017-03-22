/**
* @file nrf51_tag_connection_settings.h
* @brief Header file for BLE Connection Settings.
*
*/

#pragma once

#include "nrf51_tag_headers.h"

// ---------------------------------------------------------------------------
// Interface Functions
// ---------------------------------------------------------------------------

/**@brief Function to initialize the BLE Connection Handle.
 */
void nrf51_tag_initialize_connection_settings(void);

/**@brief Function to process BLE GAP disconnect.
 */
void nrf51_tag_disconnect(ble_gap_evt_disconnected_t ble_gap_evt_disconnected);

/**@brief Function to get the BLE Connection Handle.
 */
uint16_t nrf51_tag_get_connection_handle(void);

/**@brief Function to get the last disconnect reason.
 */
uint8_t nrf51_tag_get_disconnect_reason(void);

/**@brief Function to set the BLE Connection Handle Extended.
 */
void nrf51_tag_set_connection_settings
(
    uint16_t conn_handle, 
    ble_gap_evt_connected_t ble_gap_evt_connected
);

/**@brief Function to get the BLE Peer Address Type.
 */
uint8_t nrf51_tag_get_peer_address_type(void);

/**@brief Function to get the pointer to the BLE Peer Address.
 */
uint8_t* nrf51_tag_get_peer_p_address(void);

/**@brief Function to get the BLE Peer Address Length.
 */
uint8_t nrf51_tag_get_peer_address_length(void);

/**@brief Function to get the BLE Peer Address Object.
 */
ble_gap_addr_t nrf51_tag_get_peer_address(void);


/**@brief Function to get the BLE Own Address Type.
 */
uint8_t nrf51_tag_get_own_address_type(void);

/**@brief Function to get the pointer to the BLE Own Address.
 */
uint8_t* nrf51_tag_get_own_p_address(void);

/**@brief Function to get the BLE Own Address Length.
 */
uint8_t nrf51_tag_get_own_address_length(void);

/**@brief Function to get the BLE Own Address Object.
 */
ble_gap_addr_t nrf51_tag_get_own_address(void);


/**@brief Function to get the BLE GAP Connection Parameters.
 */
uint8_t nrf51_tag_get_gap_irk_match(void);

/**@brief Function to get the BLE GAP Connection Parameters.
 */
uint8_t nrf51_tag_get_gap_irk_match_idx(void);


/**@brief Function to get the BLE GAP Connection Parameters.
 */
ble_gap_conn_params_t nrf51_tag_get_gap_conn_params(void);


/**@brief Function to get the BLE Device Role.
 */
uint8_t nrf51_tag_get_device_role(void);

// ------------------------------------------------------------------------------------------------
// Debug Message(s)
// ------------------------------------------------------------------------------------------------
#define ENABLE_CONNECTION_SETTINGS_MESSAGES

#if defined(ENABLE_CONNECTION_SETTINGS_MESSAGES)

#define DBG_INITIALIZE_CONNECTION_SETTINGS() FUNCTION()

#else

#define DBG_INITIALIZE_CONNECTION_SETTINGS()

#endif

#define ENABLE_CONNECTION_EVT

#if defined(ENABLE_CONNECTION_EVT)

void nrf51_tag_dbg_connection_event(void);
#define DBG_CONNECTION_EVT() nrf51_tag_dbg_connection_event()

void nrf51_tag_dbg_disconnect_event(void);
#define DBG_DISCONNECT_EVT() nrf51_tag_dbg_disconnect_event()

#else

#define DBG_CONNECTION_EVT()
#define DBG_DISCONNECT_EVT()

#endif
