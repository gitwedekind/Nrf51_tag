/**
* @file nrf51_sys_headers.h
* @brief nrf51 System Header files.
*
*/

#pragma once

//-------------------------------------------------------------------------------------------------
// Nordic NRF51 Headers
//-------------------------------------------------------------------------------------------------

#include "nordic_common.h"

// Note: this header includes the nrf51.h header, #include <nrf51.h> will include the version
// from the ARM compiler which we don't want
//
#include "nrf.h"

//-------------------------------------------------------------------------------------------------
// Nordic NRF51 Peripheral / Utility Headers
//-------------------------------------------------------------------------------------------------
#include "nrf51822_peripherals.h"

#include "nrf_delay.h"
#include "nrf_gpio.h"
#include "nrf_gpiote.h"

#include "nrf_drv_rtc.h"
#include "nrf_drv_clock.h"

//-------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------
#include "sdk_config.h"
#include "nrf51_sys_defines.h"

//-------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------
#include "app_util.h"
#include "app_timer.h"

