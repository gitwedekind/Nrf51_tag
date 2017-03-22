/**
* @file nrf51_tag_configuration_service.h
* @brief Header file for the Tag Configuration Service.
*
*/

#pragma once

#include "nrf51_tag_headers.h"

//-------------------------------------------------------------------------------------------------
// Tag Configuration Service Structure
//-------------------------------------------------------------------------------------------------

/**@brief Tag Configuration Service structure.
*/
typedef struct ble_tag_configuration_service_t ble_tag_configuration_service_t;
struct ble_tag_configuration_service_t
{
    uint16_t                    service_handle;                                    /**< Handle of Tag Configuration Service (as provided by the BLE stack). */
    uint8_t                     uuid_type;                                         /**< UUID type for the Tag Service. */
    ble_gatts_char_handles_t    tag_configuration_beacon_ids_char_handles;         /**< Handles related to the Tag Configuration Beacon Ids Characteristic. */
    ble_gatts_char_handles_t    tag_configuration_adv_burst_interval_char_handles; /**< Handles related to the Tag Configuration Adv Burst Interval Characteristic. */
    ble_gatts_char_handles_t    tag_configuration_adv_burst_duration_char_handles; /**< Handles related to the Tag Configuration Adv Burst Duration Characteristic. */
};

//-------------------------------------------------------------------------------------------------
// Tag Configuration Characteristic Data Types
//-------------------------------------------------------------------------------------------------
#pragma pack(1)

/** @brief Tag Configuration Beacon Ids
*/

#define TAG_BEACON_ID_COUNT 5
#define TAG_BEACON_ID_LENGTH 16

typedef struct ble_tag_configuration_beacon_ids_t ble_tag_configuration_beacon_ids_t;
struct ble_tag_configuration_beacon_ids_t
{
    uint8_t beacon_ids[TAG_BEACON_ID_COUNT][TAG_BEACON_ID_LENGTH];
};

/** @brief Tag Configuration Adv Burst Interval
*/

typedef struct ble_tag_configuration_adv_burst_interval_t ble_tag_configuration_adv_burst_interval_t;
struct ble_tag_configuration_adv_burst_interval_t
{
    uint16_t adv_burst_interval;
};

typedef struct ble_tag_configuration_adv_burst_duration_t ble_tag_configuration_adv_burst_duration_t;
struct ble_tag_configuration_adv_burst_duration_t
{
    uint16_t adv_burst_duration;
};

#pragma pack()

//-------------------------------------------------------------------------------------------------
// Tag Configuration Service API
//-------------------------------------------------------------------------------------------------

/**@brief Add Tag Configuration Service to the Softdevice.
*/
void nrf51_tag_configuration_service_initialize(void);

//-------------------------------------------------------------------------------------------------
// Tag Configuration GATT API
//-------------------------------------------------------------------------------------------------

/** @brief
 */
void nrf51_tag_configuration_write(ble_evt_t* p_ble_evt);

/** @brief
 */
void nrf51_tag_configuration_authorize_request(ble_evt_t* p_ble_evt);

/** @brief
 */
void nrf51_tag_configuration_system_attribute_missing(ble_evt_t* p_ble_evt);

/** @brief
 */
void nrf51_tag_configuration_handle_value_confirmation(ble_evt_t* p_ble_evt);

/** @brief
 */
void nrf51_tag_configuration_service_change_confirm(ble_evt_t* p_ble_evt);

/** @brief
 */
void nrf51_tag_configuration_timeout(ble_evt_t* p_ble_evt);

//-------------------------------------------------------------------------------------------------
// Tag Configuration Get / Set API
//-------------------------------------------------------------------------------------------------

/** @brief
 */
void nrf51_tag_configuration_uptime_set(ble_tag_configuration_beacon_ids_t* p_tag_configuration_beacon_ids);

/** @brief
 */
void nrf51_tag_configuration_uptime_get(ble_tag_configuration_beacon_ids_t* p_tag_configuration_beacon_ids);

/** @brief
 */
void nrf51_tag_configuration_adv_burst_interval_set(ble_tag_configuration_adv_burst_interval_t* p_tag_configuration_adv_burst_interval);

/** @brief
 */
void nrf51_tag_configuration_adv_burst_interval_get(ble_tag_configuration_adv_burst_interval_t* p_tag_configuration_adv_burst_interval);

/** @brief
 */
void nrf51_tag_configuration_adv_burst_duration_set(ble_tag_configuration_adv_burst_duration_t* p_tag_configuration_adv_burst_duration);

/** @brief
 */
void nrf51_tag_configuration_adv_burst_duration_get(ble_tag_configuration_adv_burst_duration_t* p_tag_configuration_adv_burst_duration);

//-------------------------------------------------------------------------------------------------
// Tag Configuration handle(s) API 
//-------------------------------------------------------------------------------------------------

/** @brief
 */
uint16_t nrf51_tag_configuration_beacon_ids_value_handle(void);

/** @brief
 */
uint16_t nrf51_tag_configuration_beacon_ids_cccd_handle(void);

/** @brief
 */
uint16_t nrf51_tag_configuration_adv_burst_interval_value_handle(void);

/** @brief
 */
uint16_t nrf51_tag_configuration_adv_burst_interval_cccd_handle(void);

/** @brief
 */
uint16_t nrf51_tag_configuration_adv_burst_duration_value_handle(void);

/** @brief
 */
uint16_t nrf51_tag_configuration_adv_burst_duration_cccd_handle(void);
