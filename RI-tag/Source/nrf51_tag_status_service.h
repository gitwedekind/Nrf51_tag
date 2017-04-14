/**
* @file nrf51_tag_status_service.h
* @brief Header file for the Tag Status Service.
*
*/

#pragma once

#include "nrf51_tag_headers.h"

#define FIRMWARE_REVISION_LENGTH 8

//-------------------------------------------------------------------------------------------------
// Tag Status Service Structures
//-------------------------------------------------------------------------------------------------

/**@brief Tag Status Service structure.
*/
typedef struct ble_tag_status_service_t ble_tag_status_service_t;
struct ble_tag_status_service_t
{
    uint16_t                    service_handle;                                /**< Handle of Tag Status Service (as provided by the BLE stack). */
    uint8_t                     uuid_type;                                     /**< UUID type for the Tag Service. */
    ble_gatts_char_handles_t    tag_status_uptime_char_handles;                /**< Handles related to the Tag Status Uptime Characteristic. */
    ble_gatts_char_handles_t    tag_status_temperature_char_handles;           /**< Handles related to the Tag Status Temperature Characteristic. */
    ble_gatts_char_handles_t    tag_status_battery_level_char_handles;         /**< Handles related to the Tag Status Battery_level Characteristic. */
    ble_gatts_char_handles_t    tag_status_firmware_revision_char_handles;     /**< Handles related to the Tag Status Firmware_revision Characteristic. */
    ble_gatts_char_handles_t    tag_status_beacon_record_count_char_handles;   /**< Handles related to the Tag Status Beacon Record Count Characteristic. */
    ble_gatts_char_handles_t    tag_status_beacon_read_records_char_handles;   /**< Handles related to the Tag Status Beacon Read Records Characteristic. */
    ble_gatts_char_handles_t    tag_status_activity_record_count_char_handles; /**< Handles related to the Tag Status Activity Record Count Characteristic. */
    ble_gatts_char_handles_t    tag_status_activity_read_records_char_handles; /**< Handles related to the Tag Status Activity Read Records Characteristic. */
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
    int8_t temperature;
};
#pragma pack()

/** @brief Tag Status Battery Level
*/

#pragma pack(1)
typedef struct ble_tag_status_battery_level_t ble_tag_status_battery_level_t;
struct ble_tag_status_battery_level_t
{
    int8_t battery_level;
};
#pragma pack()

/** @brief Tag Status Firmware Revision
*/

#pragma pack(1)
typedef struct ble_tag_status_firmware_revision_t ble_tag_status_firmware_revision_t;
struct ble_tag_status_firmware_revision_t
{
    uint8_t firmware_revision[FIRMWARE_REVISION_LENGTH];
};
#pragma pack()

/** @brief Tag Status Beacon Record Count
*/

#pragma pack(1)
typedef struct ble_tag_status_beacon_record_count_t ble_tag_status_beacon_record_count_t;
struct ble_tag_status_beacon_record_count_t
{
    uint16_t br_count;
};
#pragma pack()

/** @brief Tag Status Beacon Read Records
*/

#pragma pack(1)
typedef struct ble_tag_status_beacon_read_records_t ble_tag_status_beacon_read_records_t;
struct ble_tag_status_beacon_read_records_t
{
    uint32_t timestamp;
    uint8_t x;
    uint8_t y;
    uint8_t z;
};
#pragma pack()

/** @brief Tag Status Activity Record Count
*/

#pragma pack(1)
typedef struct ble_tag_status_activity_record_count_t ble_tag_status_activity_record_count_t;
struct ble_tag_status_activity_record_count_t
{
    uint16_t br_count;
};
#pragma pack()

/** @brief Tag Status Activity Read Records
*/

#pragma pack(1)
typedef struct ble_tag_status_activity_read_records_t ble_tag_status_activity_read_records_t;
struct ble_tag_status_activity_read_records_t
{
    uint32_t timestamp;
    uint8_t x;
    uint8_t y;
    uint8_t z;
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

/** @brief
 */
void nrf51_tag_status_battery_level_set(ble_tag_status_battery_level_t* p_tag_status_battery_level);

/** @brief
 */
void nrf51_tag_status_battery_level_get(ble_tag_status_battery_level_t* p_tag_status_battery_level);

/** @brief
 */
void nrf51_tag_status_firmware_revision_set(ble_tag_status_firmware_revision_t* p_tag_status_firmware_revision);

/** @brief
 */
void nrf51_tag_status_firmware_revision_get(ble_tag_status_firmware_revision_t* p_tag_status_firmware_revision);

/** @brief
 */
void nrf51_tag_status_beacon_record_count_set(ble_tag_status_beacon_record_count_t* p_tag_status_beacon_record_count);

/** @brief
 */
void nrf51_tag_status_beacon_record_count_get(ble_tag_status_beacon_record_count_t* p_tag_status_beacon_record_count);

/** @brief
 */
void nrf51_tag_status_beacon_read_records_set(ble_tag_status_beacon_read_records_t* p_tag_status_beacon_read_records);

/** @brief
 */
void nrf51_tag_status_beacon_read_records_get(ble_tag_status_beacon_read_records_t* p_tag_status_beacon_read_records);

/** @brief
 */
void nrf51_tag_status_activity_record_count_set(ble_tag_status_activity_record_count_t* p_tag_status_activity_record_count);

/** @brief
 */
void nrf51_tag_status_activity_record_count_get(ble_tag_status_activity_record_count_t* p_tag_status_activity_record_count);

/** @brief
 */
void nrf51_tag_status_activity_read_records_set(ble_tag_status_activity_read_records_t* p_tag_status_activity_read_records);

/** @brief
 */
void nrf51_tag_status_activity_read_records_get(ble_tag_status_activity_read_records_t* p_tag_status_activity_read_records);

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

/** @brief
 */
uint16_t nrf51_tag_status_battery_level_value_handle(void);

/** @brief
 */
uint16_t nrf51_tag_status_battery_level_cccd_handle(void);

/** @brief
 */
uint16_t nrf51_tag_status_firmware_revision_value_handle(void);

/** @brief
 */
uint16_t nrf51_tag_status_firmware_revision_cccd_handle(void);

/** @brief
 */
uint16_t nrf51_tag_status_beacon_record_count_value_handle(void);

/** @brief
 */
uint16_t nrf51_tag_status_beacon_record_count_cccd_handle(void);

/** @brief
 */
uint16_t nrf51_tag_status_beacon_read_records_value_handle(void);

/** @brief
 */
uint16_t nrf51_tag_status_beacon_read_records_cccd_handle(void);

/** @brief
 */
uint16_t nrf51_tag_status_activity_record_count_value_handle(void);

/** @brief
 */
uint16_t nrf51_tag_status_activity_record_count_cccd_handle(void);

/** @brief
 */
uint16_t nrf51_tag_status_activity_read_records_value_handle(void);

/** @brief
 */
uint16_t nrf51_tag_status_activity_read_records_cccd_handle(void);
