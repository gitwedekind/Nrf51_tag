/**
* @file nrf51_tag_whitelist.h
* @brief Header file for the Radio Whitelist Interface.
*
*/

#pragma once

#include "nrf51_tag_headers.h"

// ---------------------------------------------------------------------------
// Interface Functions
// ---------------------------------------------------------------------------

/**@brief Whitelist initialization.
 */
void nrf51_tag_whitelist_init(void);

/**@brief Clear the Whitelist.
 */
void nrf51_tag_clear_whitelist(void);

/**@brief Set the active Whitelist to use a gap address.
 */
void nrf51_tag_set_whitelist_gap_addr(ble_gap_addr_t gap_addr);

/**@brief Set the active Whitelist to use a gap irk.
 */
void nrf51_tag_set_whitelist_gap_irk(ble_gap_irk_t gap_irk);

/**@brief Return the pointer to the active Whitelist.
 */
ble_gap_whitelist_t* nrf51_tag_get_whitelist(void);

/**@brief Return the active Whitelist filter policy.
 */
uint8_t nrf51_tag_get_whitelist_filter_policy(void);
