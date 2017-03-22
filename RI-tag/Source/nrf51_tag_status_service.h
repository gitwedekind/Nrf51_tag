/**
* @file nrf51_tag_status_service.h
* @brief Header file for the Tag Status Service.
*
*/

#pragma once

#include "nrf51_tag_headers.h"

//-------------------------------------------------------------------------------------------------
// Tag Status Service Structures
//-------------------------------------------------------------------------------------------------

/**@brief Tag Status Service structure.
*/
typedef struct ble_tag_status_service_t ble_tag_status_service_t;
struct ble_tag_status_service_t
{
    uint16_t                    service_handle;                      /**< Handle of Tag Status Service (as provided by the BLE stack). */
    uint8_t                     uuid_type;                           /**< UUID type for the Tag Service. */
    ble_gatts_char_handles_t    tag_status_uptime_char_handles;      /**< Handles related to the Tag Status Uptime Characteristic. */
    ble_gatts_char_handles_t    tag_status_temperature_char_handles; /**< Handles related to the Tag Status Temperature Characteristic. */
};

/** @brief Tag Status Uptime
*/

#pragma pack(1)
typedef struct ble_tag_status_uptime_t ble_tag_status_uptime_t;
struct ble_tag_status_uptime_t
{
    uint32_t uptime;
};
#pragma pack()

/** @brief Tag Status Temperature
*/

#pragma pack(1)
typedef struct ble_tag_status_temperature_t ble_tag_status_temperature_t;
struct ble_tag_status_temperature_t
{
    uint8_t temperature;
};
#pragma pack()

//-------------------------------------------------------------------------------------------------
// Tag Status Service API
//-------------------------------------------------------------------------------------------------

/**@brief Add Tag Status Service to the Softdevice.
*/
void nrf51_tag_status_service_initialize(void);

//-------------------------------------------------------------------------------------------------
// Tag Status GATT API
//-------------------------------------------------------------------------------------------------

/** @brief
 */
void nrf51_tag_status_write(ble_evt_t* p_ble_evt);

/** @brief
 */
void nrf51_tag_status_authorize_request(ble_evt_t* p_ble_evt);

/** @brief
 */
void nrf51_tag_status_system_attribute_missing(ble_evt_t* p_ble_evt);

/** @brief
 */
void nrf51_tag_status_handle_value_confirmation(ble_evt_t* p_ble_evt);

/** @brief
 */
void nrf51_tag_status_service_change_confirm(ble_evt_t* p_ble_evt);

/** @brief
 */
void nrf51_tag_status_timeout(ble_evt_t* p_ble_evt);

//-------------------------------------------------------------------------------------------------
// Tag Status Get / Set API
//-------------------------------------------------------------------------------------------------

/** @brief
 */
void nrf51_tag_status_uptime_set(ble_tag_status_uptime_t* p_tag_status_uptime);

/** @brief
 */
void nrf51_tag_status_uptime_get(ble_tag_status_uptime_t* p_tag_status_uptime);

/** @brief
 */
void nrf51_tag_status_temperature_set(ble_tag_status_temperature_t* p_tag_status_temperature);

/** @brief
 */
void nrf51_tag_status_temperature_get(ble_tag_status_temperature_t* p_tag_status_temperature);

//-------------------------------------------------------------------------------------------------
// Tag Status handle(s) API 
//-------------------------------------------------------------------------------------------------

/** @brief
 */
uint16_t nrf51_tag_status_uptime_value_handle(void);

/** @brief
 */
uint16_t nrf51_tag_status_uptime_cccd_handle(void);

/** @brief
 */
uint16_t nrf51_tag_status_temperature_value_handle(void);

/** @brief
 */
uint16_t nrf51_tag_status_temperature_cccd_handle(void);
