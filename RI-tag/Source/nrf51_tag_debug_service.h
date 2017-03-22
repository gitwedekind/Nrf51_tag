/**
* @file nrf51_tag_debug_service.h
* @brief Header file for the Tag Debug Service.
*
*/

#pragma once

#include "nrf51_tag_headers.h"

//-------------------------------------------------------------------------------------------------
// Tag Debug Service Structures
//-------------------------------------------------------------------------------------------------

/**@brief Tag Debug Service structure.
*/
typedef struct ble_tag_debug_service_t ble_tag_debug_service_t;
struct ble_tag_debug_service_t
{
    uint16_t                    service_handle;                  /**< Handle of Tag Tag Debug Service (as provided by the BLE stack). */
    uint8_t                     uuid_type;                       /**< UUID type for the Tag Debug Service. */
    ble_gatts_char_handles_t    tag_debug_cmd_char_handles;      /**< Tag Debug Command Characteristic handles. */
};

/** @brief Tag Debug Command Characteristic structure.
*/
#pragma pack(1)
typedef struct ble_tag_debug_cmd_t ble_tag_debug_cmd_t;
struct ble_tag_debug_cmd_t
{
    uint8_t cmd_id;
    uint8_t cmd_status;
    uint8_t cmd_action;
    uint8_t cmd_options;
    uint32_t data;
};
#pragma pack()

//-------------------------------------------------------------------------------------------------
// Tag Debug Service API
//-------------------------------------------------------------------------------------------------

/**@brief Add Tag Debug Service to the Softdevice.
*/
void nrf51_tag_debug_service_initialize(void);

//-------------------------------------------------------------------------------------------------
// Tag Debug GATT API
//-------------------------------------------------------------------------------------------------

/** @brief
 */
void nrf51_tag_debug_write(ble_evt_t* p_ble_evt);

/** @brief
 */
void nrf51_tag_debug_authorize_request(ble_evt_t* p_ble_evt);

/** @brief
 */
void nrf51_tag_debug_system_attribute_missing(ble_evt_t* p_ble_evt);

/** @brief
 */
void nrf51_tag_debug_handle_value_confirmation(ble_evt_t* p_ble_evt);

/** @brief
 */
void nrf51_tag_debug_service_change_confirm(ble_evt_t* p_ble_evt);

/** @brief
 */
void nrf51_tag_debug_timeout(ble_evt_t* p_ble_evt);

//-------------------------------------------------------------------------------------------------
// Tag Debug Get / Set API
//-------------------------------------------------------------------------------------------------

/** @brief
 */
void nrf51_tag_debug_cmd_set(ble_tag_debug_cmd_t* p_tag_debug_cmd);

/** @brief
 */
void nrf51_tag_debug_cmd_get(ble_tag_debug_cmd_t* p_tag_debug_cmd);

//-------------------------------------------------------------------------------------------------
// Tag Debug handle(s) API 
//-------------------------------------------------------------------------------------------------

/** @brief
 */
uint16_t nrf51_tag_debug_value_handle(void);

/** @brief
 */
uint16_t nrf51_tag_debug_cccd_handle(void);
