/**
* @file nrf51_tag_activity_log_service.h
* @brief Header file for the Tag Activity Log Service.
*
*/

#pragma once

#include "nrf51_tag_headers.h"

//-------------------------------------------------------------------------------------------------
// Tag Activity Log Service Structure
//-------------------------------------------------------------------------------------------------

/**@brief Tag Activity Log Service structure.
*/
typedef struct ble_tag_activity_log_service_t ble_tag_activity_log_service_t;
struct ble_tag_activity_log_service_t
{
    uint16_t                    service_handle;                                   /**< Handle of Tag Activity Log Service (as provided by the BLE stack). */
    uint8_t                     uuid_type;                                        /**< UUID type for the Tag Service. */
    ble_gatts_char_handles_t    tag_activity_log_record_size_char_handles;        /**< Handles Tag Activity Log Record Size Characteristic. */
    ble_gatts_char_handles_t    tag_activity_log_record_count_char_handles;       /**< Handles Tag Activity Log Record Count Characteristic. */
    ble_gatts_char_handles_t    tag_activity_log_read_records_count_char_handles; /**< Handles Tag Activity Log Read Records Count Characteristic. */
    ble_gatts_char_handles_t    tag_activity_log_read_records_char_handles;       /**< Handles Tag Activity Log Read Records Characteristic. */
    ble_gatts_char_handles_t    tag_activity_log_create_records_char_handles;     /**< Handles Tag Activity Log Create Records Characteristic. */
};

//-------------------------------------------------------------------------------------------------
// Tag Activity Log Characteristic Data Types
//-------------------------------------------------------------------------------------------------
#pragma pack(1)

/** @brief Tag Activity Log Record Size
*/
typedef struct ble_tag_activity_log_record_size_t ble_tag_activity_log_record_size_t;
struct ble_tag_activity_log_record_size_t
{
    uint8_t record_size;
};

/** @brief Tag Activity Log Record Count
*/
typedef struct ble_tag_activity_log_record_count_t ble_tag_activity_log_record_count_t;
struct ble_tag_activity_log_record_count_t
{
    uint16_t record_count;
};

/** @brief Tag Activity Log Read Records Count
*/
typedef struct ble_tag_activity_log_read_records_count_t ble_tag_activity_log_read_records_count_t;
struct ble_tag_activity_log_read_records_count_t
{
    uint8_t read_records_count;
};

/** @brief Tag Activity Log Read Records
*/
typedef struct ble_tag_activity_log_read_records_t ble_tag_activity_log_read_records_t;
struct ble_tag_activity_log_read_records_t
{
    uint8_t read_records;
};

/** @brief Tag Activity Log Create Records
*/
typedef struct ble_tag_activity_log_create_records_t ble_tag_activity_log_create_records_t;
struct ble_tag_activity_log_create_records_t
{
    uint8_t create_records;
};

#pragma pack()

//-------------------------------------------------------------------------------------------------
// Tag Activity Log Service API
//-------------------------------------------------------------------------------------------------

/**@brief Add Tag Activity Log Service to the Softdevice.
*/
void nrf51_tag_activity_log_service_initialize(void);

//-------------------------------------------------------------------------------------------------
// Tag Activity Log GATT API
//-------------------------------------------------------------------------------------------------

/** @brief
 */
void nrf51_tag_activity_log_write(ble_evt_t* p_ble_evt);

/** @brief
 */
void nrf51_tag_activity_log_authorize_request(ble_evt_t* p_ble_evt);

/** @brief
 */
void nrf51_tag_activity_log_system_attribute_missing(ble_evt_t* p_ble_evt);

/** @brief
 */
void nrf51_tag_activity_log_handle_value_confirmation(ble_evt_t* p_ble_evt);

/** @brief
 */
void nrf51_tag_activity_log_service_change_confirm(ble_evt_t* p_ble_evt);

/** @brief
 */
void nrf51_tag_activity_log_timeout(ble_evt_t* p_ble_evt);

//-------------------------------------------------------------------------------------------------
// Tag Activity Log Get / Set API
//-------------------------------------------------------------------------------------------------

/** @brief
 */
void nrf51_tag_activity_log_record_size_set(ble_tag_activity_log_record_size_t* p_tag_activity_log_record_size);

/** @brief
 */
void nrf51_tag_activity_log_record_size_get(ble_tag_activity_log_record_size_t* p_tag_activity_log_record_size);

/** @brief
 */
void nrf51_tag_activity_log_record_count_set(ble_tag_activity_log_record_count_t* p_tag_activity_log_record_count);

/** @brief
 */
void nrf51_tag_activity_log_record_count_get(ble_tag_activity_log_record_count_t* p_tag_activity_log_record_count);

/** @brief
 */
void nrf51_tag_activity_log_read_records_count_set(ble_tag_activity_log_read_records_count_t* p_tag_activity_log_read_records_count);

/** @brief
 */
void nrf51_tag_activity_log_read_records_count_get(ble_tag_activity_log_read_records_count_t* p_tag_activity_log_read_records_count);

/** @brief
 */
void nrf51_tag_activity_log_read_records_set(ble_tag_activity_log_read_records_t* p_tag_activity_log_read_records);

/** @brief
 */
void nrf51_tag_activity_log_read_records_get(ble_tag_activity_log_read_records_t* p_tag_activity_log_read_records);

/** @brief
 */
void nrf51_tag_activity_log_create_records_set(ble_tag_activity_log_create_records_t* p_tag_activity_log_create_records);

/** @brief
 */
void nrf51_tag_activity_log_create_records_get(ble_tag_activity_log_create_records_t* p_tag_activity_log_create_records);

//-------------------------------------------------------------------------------------------------
// Tag Activity Log handle(s) API 
//-------------------------------------------------------------------------------------------------

/** @brief
 */
uint16_t nrf51_tag_activity_log_record_size_value_handle(void);

/** @brief
 */
uint16_t nrf51_tag_activity_log_record_size_cccd_handle(void);

/** @brief
 */
uint16_t nrf51_tag_activity_log_record_count_value_handle(void);

/** @brief
 */
uint16_t nrf51_tag_activity_log_record_count_cccd_handle(void);

/** @brief
 */
uint16_t nrf51_tag_activity_log_read_records_count_value_handle(void);

/** @brief
 */
uint16_t nrf51_tag_activity_log_read_records_count_cccd_handle(void);

/** @brief
 */
uint16_t nrf51_tag_activity_log_read_records_value_handle(void);

/** @brief
 */
uint16_t nrf51_tag_activity_log_read_records_cccd_handle(void);

/** @brief
 */
uint16_t nrf51_tag_activity_log_create_records_value_handle(void);

/** @brief
 */
uint16_t nrf51_tag_activity_log_create_records_cccd_handle(void);
