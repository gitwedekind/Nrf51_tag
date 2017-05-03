/**
* @file nrf51_tag_advertising.h
* @brief Header file for Radio Advertising.
*
*/

#pragma once

#include "nrf51_tag_headers.h"

#define NRF51_TAG_ADV_INTERVAL           300 /**< The advertising interval (in units of 0.625 ms. This value corresponds to 187.5 ms). */
#define NRF51_TAG_ADV_TIMEOUT_IN_SECONDS 30 /**< The advertising timeout in units of seconds. */

//----------------------------------------------------------------------------
// Radio Advertising Functions
//----------------------------------------------------------------------------

/**@brief
 */
void nrf51_tag_update_device_name(uint32_t tag_serial_number);

/**@brief
 */
uint8_t* nrf51_tag_get_device_name(void);

/**@brief
 */
uint8_t nrf51_tag_get_device_name_length(void);

/**@brief
 */
void nrf51_tag_update_manufacturing_data(uint8_t ping, uint16_t tag_id, uint16_t beacon_record_count, uint16_t activity_log_record_count);

/**@brief
 */
uint8_t* nrf51_tag_get_manufacturing_data(void);

/**@brief
 */
uint8_t nrf51_tag_get_manufacturing_data_length(void);

/**@brief
 */
bool nrf51_tag_set_advertising_parameters(uint16_t interval, uint16_t timeout);

/**@brief
 */
void nrf51_tag_advertising_packet_initialize(void);

/**@brief
 */
uint32_t nrf51_tag_start_advertising(void);

/**@brief
 */
void nrf51_tag_stop_advertising(void);

// ------------------------------------------------------------------------------------------------
// Debug Message(s)
// ------------------------------------------------------------------------------------------------
#define ENABLE_ADVERTISING_MESSAGES

#if defined(ENABLE_ADVERTISING_MESSAGES)

static char const * const ADV[] =
{
    "BLE_ADV_EVT_IDLE",
    "BLE_ADV_EVT_DIRECTED",
    "BLE_ADV_EVT_DIRECTED_SLOW",
    "BLE_ADV_EVT_FAST",
    "BLE_ADV_EVT_SLOW",
    "BLE_ADV_EVT_FAST_WHITELIST",
    "BLE_ADV_EVT_SLOW_WHITELIST",
    "BLE_ADV_EVT_WHITELIST_REQUEST",
    "BLE_ADV_EVT_PEER_ADDR_REQUEST",
};

#define DBG_INITIALIZE_ADVERTISING() FUNCTION()

#define DBG_START_ADVERTISING() DBG("--> Advertising Started\r\n")
#define DBG_STOP_ADVERTISING() DBG("--> Advertising Stopped\r\n")

#define DBG_EVENT_ADVERTISING(x_event) DBG("--> ADV Event: %s\r\n", ADV[x_event])

#else

#define DBG_INITIALIZE_ADVERTISING()

#define DBG_START_ADVERTISING()
#define DBG_STOP_ADVERTISING()

#define DBG_EVENT_ADVERTISING(x_event)

#endif
