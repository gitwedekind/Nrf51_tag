/**
* @file nrf51_tag_authentication_status.h
* @brief Header file for BLE Authentication Status Interface.
*
*/

#pragma once

#include "nrf51_tag_headers.h"

// ------------------------------------------------------------------------------------------------
// Interface Functions
// ------------------------------------------------------------------------------------------------

/**@brief Function to initialize the BLE GAP Authentication Status.
 */
void nrf51_tag_initialize_authentication_status(void);

/**@brief Function to set the GAP Authentication Status.
 */
void nrf51_tag_set_gap_auth_status(ble_gap_evt_auth_status_t ble_gap_evt_auth_status);

/**@brief
 */
ble_gap_sec_keyset_t* nrf51_tag_get_security_parameters_keysets(void);

