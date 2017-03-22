/**
* @file nrf51_tag_rtc.c
* @brief Header file for tag RTC.
 */

#include "nrf51_tag_error.h"
#include "nrf51_tag_rtc.h"

#define COMPARE_COUNTERTIME (3UL) /**< Get Compare event COMPARE_TIME seconds after the counter starts from 0. */

//-------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------

static const nrf_drv_rtc_t s_rtc = NRF_DRV_RTC_INSTANCE(0); /**< Declaring an instance of nrf_drv_rtc for RTC0. */

//-------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------

/** @brief: Function for handling the RTC0 interrupts.
 * Triggered on TICK and COMPARE0 match.
 */
static void nrf51_tag_rtc_handler(nrf_drv_rtc_int_type_t int_type)
{
    if (int_type == NRF_DRV_RTC_INT_COMPARE0)
    {
        nrf_gpio_pin_toggle(LED3);
    }
    else if (int_type == NRF_DRV_RTC_INT_TICK)
    {
        nrf_gpio_pin_toggle(LED4);
    }
}

/** @brief Function starting the internal LFCLK XTAL oscillator.
 */
static void nrf51_tag_lfclk_config(void)
{
    uint32_t err_code = nrf_drv_clock_init();
    APP_ERROR_CHECK(err_code);

    nrf_drv_clock_lfclk_request(NULL);
}

/** @brief Function initialization and configuration of RTC driver instance.
 */
void nrf51_tag_rtc_config(void)
{
#if 0
    uint32_t err_code = NRF_SUCCESS;
    
    nrf51_tag_lfclk_config();

    // Initialize RTC instance
    //
    nrf_drv_rtc_config_t config = NRF_DRV_RTC_DEFAULT_CONFIG;
    config.prescaler = 4095;
    
    err_code = nrf_drv_rtc_init(&s_rtc, &config, nrf51_tag_rtc_handler);
    APP_ERROR_CHECK(err_code);

    // Enable tick event & interrupt
    //
    nrf_drv_rtc_tick_enable(&s_rtc,true);

    // Set compare channel to trigger interrupt after COMPARE_COUNTERTIME seconds
    //
    err_code = nrf_drv_rtc_cc_set(&s_rtc, 0, COMPARE_COUNTERTIME * 8, true);
    APP_ERROR_CHECK(err_code);

    // Power on RTC instance
    //
    nrf_drv_rtc_enable(&s_rtc);
#endif
}

