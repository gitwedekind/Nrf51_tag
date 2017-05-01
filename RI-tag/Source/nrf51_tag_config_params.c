/**
* @file nrf51_tag_db.c
* @brief Header file for Tag Database.
*
*/

#include "nrf51_tag_error.h"
#include "nrf51_tag_db.h"

static const uint8_t DEFAULT_THRESHOLD = 0x10; // .25g  
static const uint8_t DEFAULT_SAMPLE_RATE = 2; // 2 Hz  


#pragma pack(1)

typedef struct ble_tag_config_params_t ble_tag_config_params_t;
struct ble_tag_config_params_t
{
    uint16_t adv_interval;
    uint16_t adv_timeout;
    uint32_t tag_serial_number;
    uint32_t adv_time;
    uint8_t accelerometer_sample_rate;
    uint8_t rtc_sample_rate;
    uint8_t accelerometer_threshold;
};

#pragma pack()

static ble_tag_config_params_t s_config_params =
{
    NRF51_TAG_ADV_INTERVAL, 
    NRF51_TAG_ADV_TIMEOUT_IN_SECONDS,
    153,
    1,
    DEFAULT_SAMPLE_RATE,
    10,
    DEFAULT_THRESHOLD
};

void nrf51_tag_config_param_sys_evt(uint32_t sys_evt)
{
    if ( sys_evt == NRF_EVT_FLASH_OPERATION_SUCCESS)
    {
    }
}

uint16_t get_adv_interval(void)
{
    return s_config_params.adv_interval;
}

uint16_t get_adv_timeout(void)
{
    return s_config_params.adv_timeout;
}

uint32_t get_tag_serial_number(void)
{
    return s_config_params.tag_serial_number;
}

uint32_t get_adv_time(void)
{
    return s_config_params.adv_time;
}

uint8_t get_accelerometer_sample_rate(void)
{
    return s_config_params.accelerometer_sample_rate;
}

uint8_t get_rtc_sample_rate(void)
{
    return s_config_params.rtc_sample_rate;
}

uint8_t get_accelerometer_threshold(void)
{
    return s_config_params.accelerometer_threshold;
}
