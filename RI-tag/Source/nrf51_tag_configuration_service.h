/**
* @file nrf51_tag_configuration_service.h
* @brief Header file for the Tag Configuration Service.
*
*/

#pragma once

#include "nrf51_tag_headers.h"

#define SERIAL_NUMBER_LENGTH 8

//-------------------------------------------------------------------------------------------------
// Tag Configuration Service Structure
//-------------------------------------------------------------------------------------------------

/**@brief Tag Configuration Service structure.
*/
typedef struct ble_tag_configuration_service_t ble_tag_configuration_service_t;
struct ble_tag_configuration_service_t
{
    uint16_t                    service_handle;                               /**< Handle of Tag Configuration Service (as provided by the BLE stack). */
    uint8_t                     uuid_type;                                    /**< UUID type for the Tag Service. */
    ble_gatts_char_handles_t    tag_configuration_sample_rate_char_handles;   /**< Handles related to the Tag Configuration Beacon Ids Characteristic. */
    ble_gatts_char_handles_t    tag_configuration_serial_number_char_handles; /**< Handles related to the Tag Configuration Adv Burst Interval Characteristic. */
};

//-------------------------------------------------------------------------------------------------
// Tag Configuration Characteristic Data Types
//-------------------------------------------------------------------------------------------------
#pragma pack(1)

/** @brief Tag Configuration Sample Rate
*/

typedef struct ble_tag_configuration_sample_rate_t ble_tag_configuration_sample_rate_t;
struct ble_tag_configuration_sample_rate_t
{
    uint16_t sample_rate;
};

typedef struct ble_tag_configuration_serial_number_t ble_tag_configuration_serial_number_t;
struct ble_tag_configuration_serial_number_t
{
    uint8_t serial_number[SERIAL_NUMBER_LENGTH];
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
void nrf51_tag_configuration_sample_rate_set(ble_tag_configuration_sample_rate_t* p_tag_configuration_sample_rate);

/** @brief
 */
void nrf51_tag_configuration_sample_rate_get(ble_tag_configuration_sample_rate_t* p_tag_configuration_sample_rate);

/** @brief
 */
void nrf51_tag_configuration_serial_number_set(ble_tag_configuration_serial_number_t* p_tag_configuration_serial_number);

/** @brief
 */
void nrf51_tag_configuration_serial_number_get(ble_tag_configuration_serial_number_t* p_tag_configuration_serial_number);

//-------------------------------------------------------------------------------------------------
// Tag Configuration handle(s) API 
//-------------------------------------------------------------------------------------------------

/** @brief
 */
uint16_t nrf51_tag_configuration_sample_rate_value_handle(void);

/** @brief
 */
uint16_t nrf51_tag_configuration_sample_rate_cccd_handle(void);

/** @brief
 */
uint16_t nrf51_tag_configuration_serial_number_value_handle(void);

/** @brief
 */
uint16_t nrf51_tag_configuration_serial_number_cccd_handle(void);
