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

void nrf51_tag_sd_evt_tx_complete(ble_evt_t* p_ble_evt);
void nrf51_tag_sd_evt_user_memory(ble_evt_t* p_ble_evt);
void nrf51_tag_sd_evt_user_memory_release(ble_evt_t* p_ble_evt);
