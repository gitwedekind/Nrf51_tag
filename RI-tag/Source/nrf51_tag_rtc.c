/**
* @file nrf51_tag_rtc.c
* @brief Header file for tag RTC.
 */

#include "nrf51_tag_error.h"
#include "nrf51_tag_spi0_lis3dh.h"
#include "nrf51_tag_rtc.h"

//-------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------

static uint32_t s_system_uptime = 0;

static uint8_t s_suspend = 1;

void nrf51_tag_system_uptime_callback(void)
{
    ++s_system_uptime;
#if 0    
    if ( s_system_uptime % 5)
        return;
    
    if ( s_suspend )
    {
        s_suspend = 0;
        
        nrf51_tag_lis3dh_suspend();
    }
    else
    {
        s_suspend = 1;
        
        nrf51_tag_lis3dh_data_ready();
    }
#endif    
}

uint32_t nrf51_tag_get_system_uptime(void)
{
    return s_system_uptime;
}
