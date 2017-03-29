/**
* @file nrf51_tag_gap_params.h
* @brief Header file for the nrf51 tag gap parameters.
*
*/

#pragma once

#include "nrf51_tag_headers.h"

// ------------------------------------------------------------------------------------------------
//
// ------------------------------------------------------------------------------------------------

/**
*
*/
void nrf51_tag_set_gap_parameters(void);

/**
*
*/
void nrf51_tag_set_gap_device_name(uint8_t const * const p_dev_name, uint16_t length);

// ------------------------------------------------------------------------------------------------
// Debug Message(s)
// ------------------------------------------------------------------------------------------------
//#define ENABLE_GAP_PARAM_MESSAGES

#if defined(ENABLE_GAP_PARAM_MESSAGES)

#define DBG_INITIALIZE_GAP_PARAM() FUNCTION()
#define DBG_INITIALIZE_SET_DEVICE_NAME() FUNCTION()

#else

#define DBG_INITIALIZE_GAP_PARAM()
#define DBG_INITIALIZE_SET_DEVICE_NAME()

#endif
