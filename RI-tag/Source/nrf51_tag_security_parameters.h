/**
* @file nrf51_tag_security_parameters.h
* @brief Header file for the BLE Security Parameters.
*
*/

#pragma once

#include "nrf51_tag_headers.h"

//-----------------------------------------------------------------------------
// Interface Functions
//-----------------------------------------------------------------------------

/**@brief
 */
void nrf51_tag_set_security_parameters(void);

/**@brief
 */
ble_gap_sec_params_t* nrf51_tag_get_security_parameters(void);

/**@brief Function to set security parameters request.
 */
void nrf51_tag_set_security_parameters_request(ble_gap_evt_sec_params_request_t sec_params_request);

/**@brief Function to get latest security parameters request.
 */
ble_gap_evt_sec_params_request_t nrf51_tag_get_security_parameters_request(void);

// ------------------------------------------------------------------------------------------------
// Debug Message(s)
// ------------------------------------------------------------------------------------------------
#define ENABLE_SEC_PARAMS_MESSAGES
#define ENABLE_SEC_PARAMS_REQUEST_MESSAGES

#if defined(ENABLE_SEC_PARAMS_MESSAGES)

#define DBG_INITIALIZE_SEC_PARAMS() FUNCTION()

#else

#define DBG_INITIALIZE_SEC_PARAMS()

#endif

#if defined(ENABLE_SEC_PARAMS_REQUEST_MESSAGES)

#define DBG_SEC_PARAMS_REQUEST() \
    DBG("--> sec_params_request\r\n"); \
    DBG("--> bond           : 0x%02x\r\n", s_sec_params_request.peer_params.bond); \
    DBG("--> mitm           : 0x%02x\r\n", s_sec_params_request.peer_params.mitm); \
    DBG("--> lesc           : 0x%02x\r\n", s_sec_params_request.peer_params.lesc); \
    DBG("--> keypress       : 0x%02x\r\n", s_sec_params_request.peer_params.keypress); \
    DBG("--> io_caps        : 0x%02x\r\n", s_sec_params_request.peer_params.io_caps); \
    DBG("--> oob            : 0x%02x\r\n", s_sec_params_request.peer_params.oob); \
    DBG("--> min_key_size   : 0x%02x\r\n", s_sec_params_request.peer_params.min_key_size); \
    DBG("--> max_key_size   : 0x%02x\r\n", s_sec_params_request.peer_params.max_key_size); \
    DBG("--> kdist_peer.enc : 0x%02x\r\n", s_sec_params_request.peer_params.kdist_peer.enc); \
    DBG("--> kdist_peer.id  : 0x%02x\r\n", s_sec_params_request.peer_params.kdist_peer.id); \
    DBG("--> kdist_peer.sign: 0x%02x\r\n", s_sec_params_request.peer_params.kdist_peer.sign); \
    DBG("--> kdist_peer.link: 0x%02x\r\n", s_sec_params_request.peer_params.kdist_peer.link); \
    DBG("--> kdist_own.enc  : 0x%02x\r\n", s_sec_params_request.peer_params.kdist_own.enc); \
    DBG("--> kdist_own.id   : 0x%02x\r\n", s_sec_params_request.peer_params.kdist_own.id); \
    DBG("--> kdist_own.sign : 0x%02x\r\n", s_sec_params_request.peer_params.kdist_own.sign); \
    DBG("--> kdist_own.link : 0x%02x\r\n", s_sec_params_request.peer_params.kdist_own.link)
#else

#define DBG_SEC_PARAMS_REQUEST()

#endif
