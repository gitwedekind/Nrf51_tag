/**
* @file nrf51_tag_config_params.h
* @brief Header file for Tag Configuation Parameters.
*
*/

#pragma once

#include "nrf51_tag_headers.h"

uint16_t get_adv_interval(void);

uint16_t get_adv_timeout(void);

uint32_t get_tag_serial_number(void);

uint32_t get_adv_duration(void);

uint8_t get_accelerometer_sample_rate(void);

uint8_t get_rtc_sample_rate(void);

uint8_t get_accelerometer_threshold(void);

// ------------------------------------------------------------------------------------------------
// Debug Message(s)
// ------------------------------------------------------------------------------------------------
#define ENABLE_CONFIG_PARAMS_MESSAGES

#if defined(ENABLE_CONFIG_PARAMS_MESSAGES)

#define DBG_CONFIG_PARAMS_INITIALIZE() FUNCTION()

#else

#define DBG_CONFIG_PARAMS_INITIALIZE()

#endif
