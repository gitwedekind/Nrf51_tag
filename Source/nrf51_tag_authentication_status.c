/**
* @file nrf51_tag_authentication_status.c
* @brief Source File for BLE Authentication Status.
*
*/

#include "nrf51_tag_error.h"
#include "nrf51_tag_headers.h"

// ------------------------------------------------------------------------------------------------
// Authentication Status Variables
// ------------------------------------------------------------------------------------------------

/**< Authentication Status
*/
static ble_gap_evt_auth_status_t s_ble_gap_evt_auth_status = {0};

static ble_gap_enc_key_t s_sec_params_enc_own  = {0};
static ble_gap_enc_key_t s_sec_params_enc_peer = {0};
static ble_gap_id_key_t  s_sec_params_id_own   = {0};
static ble_gap_id_key_t  s_sec_params_id_peer  = {0};

static ble_gap_sec_keyset_t s_sec_keyset_params = 
{
    .keys_own.p_enc_key   = &s_sec_params_enc_own,
    .keys_own.p_id_key    = &s_sec_params_id_own,
    .keys_peer.p_enc_key  = &s_sec_params_enc_peer,
    .keys_peer.p_id_key   = &s_sec_params_id_peer
};

// ------------------------------------------------------------------------------------------------
// Connection Handle Functions
// ------------------------------------------------------------------------------------------------

/**@brief Function to initialize the BLE GAP Authentication Status.
 */
void nrf51_tag_initialize_authentication_status(void)
{
    memset(&s_ble_gap_evt_auth_status, '\0', sizeof(s_ble_gap_evt_auth_status));
}

/**@brief Function to set the BLE GAP Authentication Status.
 */
void nrf51_tag_set_gap_auth_status(ble_gap_evt_auth_status_t ble_gap_evt_auth_status)
{
    s_ble_gap_evt_auth_status = ble_gap_evt_auth_status;
    
    DBG_AUTH_STATUS(s_ble_gap_evt_auth_status);
    
    DBG_GAP_ENC_KEY("enc_own", s_sec_params_enc_own);
    DBG_GAP_ID_KEY("enc_own", s_sec_params_id_own);
    
    DBG_GAP_ENC_KEY("enc_peer", s_sec_params_enc_peer);
    DBG_GAP_ID_KEY("enc_peer", s_sec_params_id_peer);
}

/**@brief
 */
ble_gap_sec_keyset_t* nrf51_tag_get_security_parameters_keysets()
{
    return &s_sec_keyset_params;
}
