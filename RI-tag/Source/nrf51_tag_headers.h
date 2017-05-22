/**
* @file nrf51_tag_headers.h
* @brief nrf51 tag Header files.
*
*/

#pragma once

//-------------------------------------------------------------------------------------------------
// RI-tag Headers
//-------------------------------------------------------------------------------------------------

#ifndef WIN32

#include "nrf51_tag_version.h"
#include "nrf51_tag_diagnostics.h"
#include "nrf51_tag_timers.h"
#include "nrf51_tag_tx_power.h"
#include "nrf51_tag_power_manage.h"
#include "nrf51_tag_rtc.h"
#include "nrf51_tag_lis3dh.h"
#include "nrf51_tag_spi0_lis3dh.h"
#include "nrf51_tag_flash.h"
#include "nrf51_tag_config_params.h"
#include "nrf51_tag_db.h"

#include "nrf51_tag_initialize.h"
#include "nrf51_tag_ble_stack.h"
#include "nrf51_tag_gap_params.h"
#include "nrf51_tag_connection_parameters.h"
#include "nrf51_tag_security_parameters.h"
#include "nrf51_tag_radio_notification.h"
#include "nrf51_tag_terminate_connection.h"
#include "nrf51_tag_connection_settings.h"
#include "nrf51_tag_connection_security.h"
#include "nrf51_tag_whitelist.h"
#include "nrf51_tag_advertising.h"
#include "nrf51_tag_authentication_status.h"

#include "nrf51_tag_services_init.h"
#include "nrf51_tag_status_service.h"

#include "nrf51_tag_on_ble_evt.h"
#include "nrf51_tag_on_ble_evt_gap.h"
#include "nrf51_tag_on_ble_evt_gatt.h"
#include "nrf51_tag_on_ble_evt_sd.h"
#include "nrf51_tag_dbg_ble_on_evt.h"

#else

#include "nrf51_std_headers.h"

#define __STATIC_INLINE static inline
#define __INLINE inline

//---------------------------------------------------------------------------
// Macro to remove "Tag vs Type Name" issues when defining structures,
// i.e. removes typo's since the name is typed 3 times.
//
// Note: Based on Embedded.com Article by Dan Saks
//       "Tag vs Type Names" Oct 01 2002
//---------------------------------------------------------------------------
#define STRUCT_DEF(x_struct_name) \
    typedef struct x_struct_name x_struct_name; \
    struct x_struct_name

#define UNION_DEF(x_union_name) \
    typedef union x_union_name x_union_name; \
    union x_union_name

/**@brief SoC Events. */
enum NRF_SOC_EVTS
{
  NRF_EVT_HFCLKSTARTED,                         /**< Event indicating that the HFCLK has started. */
  NRF_EVT_POWER_FAILURE_WARNING,                /**< Event indicating that a power failure warning has occurred. */
  NRF_EVT_FLASH_OPERATION_SUCCESS,              /**< Event indicating that the ongoing flash operation has completed successfully. */
  NRF_EVT_FLASH_OPERATION_ERROR,                /**< Event indicating that the ongoing flash operation has timed out with an error. */
  NRF_EVT_RADIO_BLOCKED,                        /**< Event indicating that a radio timeslot was blocked. */
  NRF_EVT_RADIO_CANCELED,                       /**< Event indicating that a radio timeslot was canceled by SoftDevice. */
  NRF_EVT_RADIO_SIGNAL_CALLBACK_INVALID_RETURN, /**< Event indicating that a radio timeslot signal callback handler return was invalid. */
  NRF_EVT_RADIO_SESSION_IDLE,                   /**< Event indicating that a radio timeslot session is idle. */
  NRF_EVT_RADIO_SESSION_CLOSED,                 /**< Event indicating that a radio timeslot session is closed. */
  NRF_EVT_NUMBER_OF_EVTS
};

#ifdef __cplusplus
extern "C" {
#endif

uint32_t sd_flash_write(uint32_t * const p_dst, uint32_t const * const p_src, uint32_t size);
uint32_t sd_flash_page_erase(uint32_t page_number);

#ifdef __cplusplus
}
#endif

#include "nrf51_tag_flash.h"

#endif
