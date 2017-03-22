/**
* @file nrf51_tag_connection_settings.c
* @brief Source File for BLE Connection Handle.
*
*/

#include "nrf51_tag_error.h"
#include "nrf51_tag_headers.h"

// ---------------------------------------------------------------------------
// Connection Handle Variables
// ---------------------------------------------------------------------------

/**< Handle of the current connection. 
*/
static uint16_t s_conn_handle = BLE_CONN_HANDLE_INVALID; 

/**< Connected Info. 
*/
static ble_gap_evt_connected_t s_ble_gap_evt_connected = {0};

static ble_gap_evt_disconnected_t s_ble_gap_evt_disconnected = {0};

// ---------------------------------------------------------------------------
// Initialize Connection Settings
// ---------------------------------------------------------------------------

/**@brief Function to initialize the BLE Connection Settings.
 */
void nrf51_tag_initialize_connection_settings(void)
{
    DBG_INITIALIZE_CONNECTION_SETTINGS();
    
    memset(&s_ble_gap_evt_connected, '\0', sizeof(s_ble_gap_evt_connected));
    s_conn_handle = BLE_CONN_HANDLE_INVALID;
}

// ---------------------------------------------------------------------------
// Connection Handle
// ---------------------------------------------------------------------------

/**@brief Function to set the BLE Connection Handle.
 *
 * @param Connection Handle
 */
void nrf51_tag_disconnect(ble_gap_evt_disconnected_t ble_gap_evt_disconnected)
{
    s_conn_handle = BLE_CONN_HANDLE_INVALID;
    s_ble_gap_evt_disconnected = ble_gap_evt_disconnected;
    DBG_DISCONNECT_EVT();
}

/**@brief Function to set the BLE Connection Handle Settings.
 */
void nrf51_tag_set_connection_settings
(
    uint16_t conn_handle, 
    ble_gap_evt_connected_t ble_gap_evt_connected
)
{
    s_conn_handle = conn_handle;
    s_ble_gap_evt_connected = ble_gap_evt_connected;
    
    DBG_CONNECTION_EVT();
}

/**@brief Function to get the BLE Connection Handle.
 *
 * @return Connection Handle
 */
uint16_t nrf51_tag_get_connection_handle(void)
{
    return s_conn_handle;
}

/**@brief Function to get the last disconnect reason.
 *
 * @return disconnect code
 */
uint8_t nrf51_tag_get_disconnect_reason(void)
{
    return s_ble_gap_evt_disconnected.reason;
}

// ------------------------------------------------------------------------------------------------
// Peer Address
// ------------------------------------------------------------------------------------------------

/**@brief Function to get the BLE Peer Address Type.
 *
 * @return GAP Address Type
 */
uint8_t nrf51_tag_get_peer_address_type(void)
{
    return s_ble_gap_evt_connected.peer_addr.addr_type;
}

/**@brief Function to get the pointer to the BLE Peer Address.
 *
 * @return GAP Address Type
 */
uint8_t* nrf51_tag_get_peer_p_address(void)
{
    return s_ble_gap_evt_connected.peer_addr.addr;
}

/**@brief Function to get the BLE Peer Address length.
 *
 * @return GAP Address Type
 */
uint8_t nrf51_tag_get_peer_address_length(void)
{
    return sizeof(s_ble_gap_evt_connected.peer_addr.addr);
}

/**@brief Function returns the BLE Peer Address Object.
 *
 * @return GAP Address Object (by value)
 */
ble_gap_addr_t nrf51_tag_get_peer_address(void)
{
    return s_ble_gap_evt_connected.peer_addr;
}

// ------------------------------------------------------------------------------------------------
// Own Address
// ------------------------------------------------------------------------------------------------

/**@brief Function to get the BLE Own Address.
 *
 * @return Own Address Type
 */
uint8_t nrf51_tag_get_own_address_type(void)
{
    return s_ble_gap_evt_connected.own_addr.addr_type;
}

/**@brief Function to get the pointer to the BLE Own Address.
 *
 * @return Own Address Pointer
 */
uint8_t* nrf51_tag_get_own_p_address(void)
{
    return s_ble_gap_evt_connected.own_addr.addr;
}

/**@brief Function to get the BLE Own Address length.
 *
 * @return Own Address Length
 */
uint8_t nrf51_tag_get_own_address_length(void)
{
    return sizeof(s_ble_gap_evt_connected.own_addr.addr);
}

/**@brief Function returns the BLE Own Address Object.
 *
 * @return Own Address Object (by value)
 */
ble_gap_addr_t nrf51_tag_get_own_address(void)
{
    return s_ble_gap_evt_connected.own_addr;
}

// ------------------------------------------------------------------------------------------------
// IRK
// ------------------------------------------------------------------------------------------------

/**@brief Function to get the BLE GAP Connection Parameters.
 *
 * @return GAP IRK Match Type
 */
uint8_t nrf51_tag_get_gap_irk_match(void)
{
    return s_ble_gap_evt_connected.irk_match;
}

/**@brief Function to get the BLE GAP Connection Parameters.
 *
 * @return GAP IRK Match Index Type
 */
uint8_t nrf51_tag_get_gap_irk_match_idx(void)
{
    return s_ble_gap_evt_connected.irk_match_idx;
}

// ------------------------------------------------------------------------------------------------
// Connection Parameters
// ------------------------------------------------------------------------------------------------

/**@brief Function to get the BLE GAP Connection Parameters.
 *
 * @return GAP Connection Parameter Type
 */
ble_gap_conn_params_t nrf51_tag_get_gap_conn_params(void)
{
    return s_ble_gap_evt_connected.conn_params;
}

// ------------------------------------------------------------------------------------------------
// Device Role
// ------------------------------------------------------------------------------------------------

/**@brief Function to get the BLE Device Role.
 */
uint8_t nrf51_tag_get_device_role(void)
{
    return s_ble_gap_evt_connected.role;
}

// ------------------------------------------------------------------------------------------------
// ENABLE_CONNECTION_EVT
// ------------------------------------------------------------------------------------------------
#ifdef ENABLE_CONNECTION_EVT

void nrf51_tag_dbg_connection_event(void)
{
    DBG("--> Connection Event, handle: 0x%x\r\n", s_conn_handle);
    
    DBG("Peer Address - addr_type : %s\r\n", BLE_GAP_ADDR_TYPE[s_ble_gap_evt_connected.peer_addr.addr_type]);
    DBG_ADDRESS(" - addr: ", s_ble_gap_evt_connected.peer_addr.addr, BLE_GAP_ADDR_LEN );

    DBG("Own Address - addr_type : %s\r\n", BLE_GAP_ADDR_TYPE[s_ble_gap_evt_connected.own_addr.addr_type]);
    DBG_ADDRESS(" - addr: ", s_ble_gap_evt_connected.own_addr.addr, BLE_GAP_ADDR_LEN );
    
    DBG("Role            : %s\r\n", BLE_GAP_ROLE[s_ble_gap_evt_connected.role]);
    DBG("IRK Match       : %d\r\n", s_ble_gap_evt_connected.irk_match);
    DBG("IRK Match Index : %d\r\n", s_ble_gap_evt_connected.irk_match_idx);

    DBG("min_conn_interval: %d\r\n", s_ble_gap_evt_connected.conn_params.min_conn_interval);
    DBG("max_conn_interval: %d\r\n", s_ble_gap_evt_connected.conn_params.max_conn_interval);
    DBG("slave_latency    : %d\r\n", s_ble_gap_evt_connected.conn_params.slave_latency);
    DBG("conn_sup_timeout : %d\r\n", s_ble_gap_evt_connected.conn_params.conn_sup_timeout);
}

void nrf51_tag_dbg_disconnect_event(void)
{
    DBG("--> Disconnect Event, reason code: 0x%x\r\n", s_ble_gap_evt_disconnected.reason );
}

#endif // ENABLE_CONNECTION_EVT
