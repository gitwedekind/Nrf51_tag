/**
* @file nrf51_tag_rtc.h
* @brief Header file for tag RTC.
*
*/

#pragma once

#include "nrf51_std_headers.h"
#include "nrf51_sys_headers.h"

// ------------------------------------------------------------------------------------------------
// RTC API's
// ------------------------------------------------------------------------------------------------

uint32_t nrf51_tag_get_system_uptime(void);
