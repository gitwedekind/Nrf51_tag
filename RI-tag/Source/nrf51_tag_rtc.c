/**
* @file nrf51_tag_rtc.c
* @brief Header file for tag RTC.
 */

#include "nrf51_tag_error.h"
#include "nrf51_tag_rtc.h"

//-------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------

static uint32_t s_system_uptime = 0;

void nrf51_tag_system_uptime_callback(void)
{
    ++s_system_uptime;
}

uint32_t nrf51_tag_get_system_uptime(void)
{
    return s_system_uptime;
}
