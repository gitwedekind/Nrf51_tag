/**
* @file nrf51_tag_on_ble_evt.h
* @brief Header file for Soft Device BLE Event Handlers.
*
*/

#pragma once

#include "nrf51_tag_headers.h"

//-------------------------------------------------------------------------------------------------
// Soft Device Interface Functions
//-------------------------------------------------------------------------------------------------

/** @brief Function for handling the callback events.
*/
void softdevice_on_ble_evt(ble_evt_t * p_ble_evt);

