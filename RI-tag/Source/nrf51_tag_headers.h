/**
* @file nrf51_tag_headers.h
* @brief nrf51 tag Header files.
*
*/

#pragma once

//-------------------------------------------------------------------------------------------------
// RI-tag Headers
//-------------------------------------------------------------------------------------------------

#include "nrf51_tag_version.h"
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
