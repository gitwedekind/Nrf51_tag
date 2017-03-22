/**
* @file nrf51_tag_stack.h
* @brief Header for Radio Interface Initialize Functions.
*
*/

#pragma once

#include "nrf51_tag_headers.h"

//----------------------------------------------------------------------------
// RDI Interface Functions
//----------------------------------------------------------------------------

/**@brief Function to initialize the BLE Stack Interface.
 */
void nrf51_tag_stack_init(void);

/**@brief Function for enabling the BLE stack.
 */
void nrf51_tag_ble_stack_enable(void);

/**@brief Function for disabling the BLE stack.
 */
void nrf51_tag_ble_stack_disable(void);

/**@brief Function
 */
void nrf51_tag_ble_set_gap_address(ble_gap_addr_t* p_gap_addr);

/**@brief Function
 */
void nrf51_tag_ble_get_gap_address(ble_gap_addr_t* p_gap_addr);

/**@brief
 */
bool nrf51_tag_is_cccd_configured(uint16_t cccd_handle);

// ------------------------------------------------------------------------------------------------
// Debug Message(s)
// ------------------------------------------------------------------------------------------------
#define ENABLE_STACK_INITIALIZE_MESSAGES

#if defined(ENABLE_STACK_INITIALIZE_MESSAGES)

#define DBG_STACK_INITIALIZE() FUNCTION()

#else

#define DBG_STACK_INITIALIZE()

#endif
