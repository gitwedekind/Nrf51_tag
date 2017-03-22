/**
* @file nrf51_tag_on_ble_evt.h
* @brief Header file for Soft Device BLE Event Handlers.
*
*/

#pragma once

#include "nrf51_tag_headers.h"

//-------------------------------------------------------------------------------------------------
// Soft Device Interface GAP Functions
//-------------------------------------------------------------------------------------------------

void nrf51_tag_gap_evt_connect(ble_evt_t* p_ble_evt);
void nrf51_tag_gap_evt_disconnect(ble_evt_t* p_ble_evt);
void nrf51_tag_gap_evt_connection_parameters_update(ble_evt_t* p_ble_evt);
void nrf51_tag_gap_evt_security_parameters_request(ble_evt_t* p_ble_evt);
void nrf51_tag_gap_evt_security_info_request(ble_evt_t* p_ble_evt);
void nrf51_tag_gap_evt_passkey_display(ble_evt_t* p_ble_evt);
void nrf51_tag_gap_evt_key_pressed(ble_evt_t* p_ble_evt);
void nrf51_tag_gap_evt_authentication_key_request(ble_evt_t* p_ble_evt);
void nrf51_tag_gap_evt_authentication_status(ble_evt_t* p_ble_evt);
void nrf51_tag_gap_evt_connection_security_update(ble_evt_t* p_ble_evt);
void nrf51_tag_gap_evt_timeout(ble_evt_t* p_ble_evt);
void nrf51_tag_gap_evt_rssi_changed(ble_evt_t* p_ble_evt);
void nrf51_tag_gap_evt_adv_report(ble_evt_t* p_ble_evt);
void nrf51_tag_gap_evt_security_request(ble_evt_t* p_ble_evt);
void nrf51_tag_gap_conn_param_update_request(ble_evt_t* p_ble_evt);
void nrf51_tag_gap_evt_scan_request_report(ble_evt_t* p_ble_evt);
