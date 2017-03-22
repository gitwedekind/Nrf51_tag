/**
* @file nrf51_tag_on_ble_evt.h
* @brief Header file for Soft Device BLE Event Handlers.
*
*/

#pragma once

#include "nrf51_tag_headers.h"

//-------------------------------------------------------------------------------------------------
// Soft Device Interface GATT Functions
//-------------------------------------------------------------------------------------------------

/** @brief
 */
void nrf51_tag_gatts_evt_write(ble_evt_t* p_ble_evt);

/** @brief
 */
void nrf51_tag_gatts_evt_authorize_request(ble_evt_t* p_ble_evt);

/** @brief
 */
void nrf51_tag_gatts_evt_system_attribute_missing(ble_evt_t* p_ble_evt);

/** @brief
 */
void nrf51_tag_gatts_evt_handle_value_confirmation(ble_evt_t* p_ble_evt);

/** @brief
 */
void nrf51_tag_gatts_evt_service_change_confirm(ble_evt_t* p_ble_evt);

/** @brief
 */
void nrf51_tag_gatts_evt_timeout(ble_evt_t* p_ble_evt);
