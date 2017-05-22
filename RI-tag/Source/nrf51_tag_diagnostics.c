/* 
 */

#include "nrf51_tag_diagnostics.h"

static uint16_t s_diagnostics = 0;

void nrf51_tag_initialize_diagnostics(void)
{
    s_diagnostics = 0x0000;

    DIAG_TIMER_GPIO_INIT();
}

uint16_t* nrf51_tag_diagnostics(void)
{
    return &s_diagnostics;
}

uint16_t nrf51_tag_diagnostics_length(void)
{
    return sizeof(s_diagnostics);
}

void nrf51_tag_diagnostic_rtc_timer(void)
{
    s_diagnostics |= DIAG_RTC_TIMER_PASSED;
    
    DIAG_RTC_TIMER_GPIO_TOGGLE();
}

void nrf51_tag_diagnostic_lfclk(uint8_t lf_clock_enabled)
{
    if (lf_clock_enabled)
    {
        s_diagnostics |= DIAG_LF_CLK_PASSED;
    }
    
    DIAG_LFCLK_GPIO_STATUS(lf_clock_enabled);
}

void nrf51_tag_diagnostic_lis3dh_enabled(uint8_t lis3dh_enabled)
{
    if (lis3dh_enabled)
    {
        s_diagnostics |= DIAG_LIS3DH_ENABLED_PASSED;
    }
    
    DIAG_LIS3DH_ENABLED_GPIO_STATUS(lis3dh_enabled);
}

void nrf51_tag_diagnostic_lis3dh_int1(void)
{
    s_diagnostics |= DIAG_LIS3DH_INT1_PASSED;

    DIAG_LIS3DH_INT1_GPIO_STATUS();
}
