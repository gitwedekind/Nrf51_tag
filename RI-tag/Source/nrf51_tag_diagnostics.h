/* @file nrf51_tag_diagnostics.h
 */

#pragma once

#include "nrf51_std_headers.h"
#include "nrf51_sys_headers.h"

//-------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------

static const uint16_t DIAG_LF_CLK_PASSED         = 0x0001;
static const uint16_t DIAG_RTC_TIMER_PASSED      = 0x0002;
static const uint16_t DIAG_LIS3DH_ENABLED_PASSED = 0x0004;
static const uint16_t DIAG_LIS3DH_INT1_PASSED    = 0x0008;

//-------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------

void nrf51_tag_initialize_diagnostics(void);

uint16_t* nrf51_tag_diagnostics(void);

uint16_t nrf51_tag_diagnostics_length(void);

void nrf51_tag_diagnostic_rtc_timer(void);

void nrf51_tag_diagnostic_lfclk(uint8_t lf_clock_enabled);

void nrf51_tag_diagnostic_lis3dh_enabled(uint8_t lis3dh_enabled);

void nrf51_tag_diagnostic_lis3dh_int1(void);

//-------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------

#ifdef ENABLE_BLE400_DEV_BOARD

static const uint32_t RI_TAG_LIS3DH_ENABLED_GPIO = 1;
static const uint32_t RI_TAG_LIS3DH_INT1_GPIO    = 2;
static const uint32_t RI_TAG_TIMER_GPIO          = 3;
static const uint32_t RI_TAG_LFCLK_GPIO          = 4;

#define DIAG_TIMER_GPIO_INIT() { \
    nrf_gpio_cfg_output(RI_TAG_LIS3DH_ENABLED_GPIO); \
    nrf_gpio_cfg_output(RI_TAG_LIS3DH_INT1_GPIO); \
    nrf_gpio_cfg_output(RI_TAG_TIMER_GPIO); \
    nrf_gpio_cfg_output(RI_TAG_LFCLK_GPIO); }
    
#define DIAG_RTC_TIMER_GPIO_TOGGLE()             nrf_gpio_pin_toggle(RI_TAG_TIMER_GPIO)
#define DIAG_LFCLK_GPIO_STATUS(x_state)          nrf_gpio_pin_write(RI_TAG_LFCLK_GPIO, x_state)
#define DIAG_LIS3DH_ENABLED_GPIO_STATUS(x_state) nrf_gpio_pin_write(RI_TAG_LIS3DH_ENABLED_GPIO, x_state)
#define DIAG_LIS3DH_INT1_GPIO_STATUS()           nrf_gpio_pin_toggle(RI_TAG_LIS3DH_INT1_GPIO)

#elif ENABLE_CJMCU_DEV_BOARD

static const uint32_t RI_TAG_LIS3DH_ENABLED_GPIO = 11;
static const uint32_t RI_TAG_LIS3DH_INT1_GPIO    = 12;
static const uint32_t RI_TAG_TIMER_GPIO          = 8;
static const uint32_t RI_TAG_LFCLK_GPIO          = 9;

#define DIAG_TIMER_GPIO_INIT() { \
    nrf_gpio_cfg_output(RI_TAG_LIS3DH_ENABLED_GPIO); \
    nrf_gpio_cfg_output(RI_TAG_LIS3DH_INT1_GPIO); \
    nrf_gpio_cfg_output(RI_TAG_TIMER_GPIO); \
    nrf_gpio_cfg_output(RI_TAG_LFCLK_GPIO); }

#define DIAG_RTC_TIMER_GPIO_TOGGLE()             nrf_gpio_pin_toggle(RI_TAG_TIMER_GPIO)
#define DIAG_LFCLK_GPIO_STATUS(x_state)          nrf_gpio_pin_write(RI_TAG_LFCLK_GPIO, x_state)
#define DIAG_LIS3DH_ENABLED_GPIO_STATUS(x_state) nrf_gpio_pin_write(RI_TAG_LIS3DH_ENABLED_GPIO, x_state)
#define DIAG_LIS3DH_INT1_GPIO_STATUS()           nrf_gpio_pin_toggle(RI_TAG_LIS3DH_INT1_GPIO)

#elif ENABLE_RI_TAG_BOARD == 1

static const uint32_t RI_TAG_LIS3DH_ENABLED_GPIO = 1;
static const uint32_t RI_TAG_LIS3DH_INT1_GPIO    = 2;
static const uint32_t RI_TAG_TIMER_GPIO          = 3;
static const uint32_t RI_TAG_LFCLK_GPIO          = 4;

#define DIAG_TIMER_GPIO_INIT() { \
    nrf_gpio_cfg_output(RI_TAG_LIS3DH_ENABLED_GPIO); \
    nrf_gpio_cfg_output(RI_TAG_LIS3DH_INT1_GPIO); \
    nrf_gpio_cfg_output(RI_TAG_TIMER_GPIO); \
    nrf_gpio_cfg_output(RI_TAG_LFCLK_GPIO); }

#define DIAG_RTC_TIMER_GPIO_TOGGLE()             nrf_gpio_pin_toggle(RI_TAG_TIMER_GPIO)
#define DIAG_LFCLK_GPIO_STATUS(x_state)          nrf_gpio_pin_write(RI_TAG_LFCLK_GPIO, x_state)
#define DIAG_LIS3DH_ENABLED_GPIO_STATUS(x_state) nrf_gpio_pin_write(RI_TAG_LIS3DH_ENABLED_GPIO, x_state)
#define DIAG_LIS3DH_INT1_GPIO_STATUS()           nrf_gpio_pin_toggle(RI_TAG_LIS3DH_INT1_GPIO)

#else

#define DIAG_TIMER_GPIO_INIT()

#define DIAG_RTC_TIMER_GPIO_TOGGLE()
#define DIAG_LFCLK_GPIO_STATUS(x_state)
#define DIAG_LIS3DH_ENABLED_GPIO_STATUS(x_state)
#define DIAG_LIS3DH_INT1_GPIO_STATUS()

#endif

