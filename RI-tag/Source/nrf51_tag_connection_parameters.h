/**
* @file nrf51_tag_connection_parameters.h
* @brief Header file for the BLE Connection Parameters.
*
*/

#pragma once

#include "nrf51_tag_headers.h"

// ---------------------------------------------------------------------------
// Interface Functions
// ---------------------------------------------------------------------------

/**@brief Function for setting the Connection Parameters.
 */
void nrf51_tag_set_connection_parameters(void);

// ------------------------------------------------------------------------------------------------
// Debug Message(s)
// ------------------------------------------------------------------------------------------------
//#define ENABLE_CONN_PARAM_MESSAGES

#if defined(ENABLE_CONN_PARAM_MESSAGES)

#define DBG_INITIALIZE_CONN_PARAM() FUNCTION()

#else

#define DBG_INITIALIZE_CONN_PARAM()

#endif
