/**
* @file nrf51_tag_security_parameters.c
* @brief Source file for the BLE Security Parameters.
*
*/

#include "nrf51_tag_error.h"
#include "nrf51_tag_headers.h"

//-----------------------------------------------------------------------------
// Security Parameter Settings
//-----------------------------------------------------------------------------

#define SEC_PARAM_BOND            1                    /**< Perform bonding. */
#define SEC_PARAM_MITM            0                    /**< Man In The Middle protection not required. */
#define SEC_PARAM_IO_CAPABILITIES BLE_GAP_IO_CAPS_NONE /**< No I/O capabilities. */
#define SEC_PARAM_OOB             0                    /**< Out Of Band data not available. */
#define SEC_PARAM_MIN_KEY_SIZE    7                    /**< Minimum encryption key size. */
#define SEC_PARAM_MAX_KEY_SIZE    16                   /**< Maximum encryption key size. */

static ble_gap_sec_params_t s_sec_params = {0}; 

static ble_gap_evt_sec_params_request_t s_sec_params_request = {0};

//-----------------------------------------------------------------------------
// Interface Functions
//-----------------------------------------------------------------------------

/**@brief Function for settings security parameters.
 */
void nrf51_tag_set_security_parameters(void)
{
    DBG_INITIALIZE_SEC_PARAMS();
    
    memset(&s_sec_params, 0, sizeof(s_sec_params));
    
    s_sec_params.bond         = SEC_PARAM_BOND;
    s_sec_params.mitm         = SEC_PARAM_MITM;
    s_sec_params.io_caps      = SEC_PARAM_IO_CAPABILITIES;
    s_sec_params.oob          = SEC_PARAM_OOB;
    s_sec_params.min_key_size = SEC_PARAM_MIN_KEY_SIZE;
    s_sec_params.max_key_size = SEC_PARAM_MAX_KEY_SIZE;

    s_sec_params.kdist_own.enc  = 0;
    s_sec_params.kdist_own.id   = 0;
    s_sec_params.kdist_own.sign = 0;
    s_sec_params.kdist_own.link = 0;
    
    s_sec_params.kdist_peer.enc  = 0;
    s_sec_params.kdist_peer.id   = 0;
    s_sec_params.kdist_peer.sign = 0;
    s_sec_params.kdist_peer.link = 0;
}

/**@brief Function for getting security parameters.
 */
ble_gap_sec_params_t* nrf51_tag_get_security_parameters(void)
{
    return &s_sec_params;
}

/**@brief Function to set security parameters request.
 */
void nrf51_tag_set_security_parameters_request(ble_gap_evt_sec_params_request_t sec_params_request)
{
    s_sec_params_request = sec_params_request;
    
    s_sec_params.kdist_own.enc  = s_sec_params_request.peer_params.kdist_own.enc;
    s_sec_params.kdist_own.id   = s_sec_params_request.peer_params.kdist_own.id;
    s_sec_params.kdist_own.sign = s_sec_params_request.peer_params.kdist_own.sign;
    s_sec_params.kdist_own.link = s_sec_params_request.peer_params.kdist_own.link;
    
    s_sec_params.kdist_peer.enc  = s_sec_params_request.peer_params.kdist_peer.enc;
    s_sec_params.kdist_peer.id   = s_sec_params_request.peer_params.kdist_peer.id;
    s_sec_params.kdist_peer.sign = s_sec_params_request.peer_params.kdist_peer.sign;
    s_sec_params.kdist_peer.link = s_sec_params_request.peer_params.kdist_peer.link;

    DBG_SEC_PARAMS_REQUEST();
}

/**@brief Function to get latest security parameters request.
 */
ble_gap_evt_sec_params_request_t nrf51_tag_get_security_parameters_request(void)
{
    return s_sec_params_request;
}
