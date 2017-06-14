/**
* @file nrf51_tag_db.c
* @brief Header file for Tag Database.
*
*/

#include "nrf51_tag_error.h"
#include "nrf51_tag_db.h"

static const uint8_t DEFAULT_THRESHOLD = 0x10; // .25g  
static const uint8_t DEFAULT_SAMPLE_RATE = 2;  // 2 Hz  

static const uint32_t CONFIG_SIGNATURE = 0xBADDC0FF;

#pragma pack(1)

typedef struct ble_tag_config_params_t ble_tag_config_params_t;
struct ble_tag_config_params_t
{
    uint32_t signature;
    uint16_t adv_interval;
    uint16_t adv_timeout;
    uint32_t tag_serial_number;
    uint32_t adv_duration;
    uint8_t accelerometer_sample_rate;
    uint8_t rtc_sample_rate;
    uint8_t accelerometer_threshold;
    uint8_t res;
};

#pragma pack()

static __align(4) ble_tag_config_params_t s_config_params =
{
    CONFIG_SIGNATURE,
    NRF51_TAG_ADV_INTERVAL, 
    NRF51_TAG_ADV_TIMEOUT_IN_SECONDS,
    200,
    15,
    DEFAULT_SAMPLE_RATE,
    10,
    DEFAULT_THRESHOLD
};

void initialize_config_parameters(void)
{
    ble_tag_config_params_t config_params = {0};
    
    nrf51_tag_db_read_sector(GP0_PAGE, (uint8_t*)&config_params, sizeof(config_params));
    
    if ( config_params.signature == CONFIG_SIGNATURE )
    {
        memcpy(&s_config_params, &config_params, sizeof(config_params));
    }
    
    DBG("--> signature: 0x%x\r\n",s_config_params.signature);
    DBG("--> adv_interval: %d\r\n",s_config_params.adv_interval);
    DBG("--> adv_timeout: %d\r\n",s_config_params.adv_timeout);
    DBG("--> tag_serial_number: %d\r\n",s_config_params.tag_serial_number);
    DBG("--> adv_duration: %d\r\n",s_config_params.adv_duration);
    DBG("--> accelerometer_sample_rate: %d\r\n",s_config_params.accelerometer_sample_rate);
    DBG("--> rtc_sample_rate: %d\r\n",s_config_params.rtc_sample_rate);
    DBG("--> accelerometer_threshold: %d\r\n",s_config_params.accelerometer_threshold);
}

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

void set_tag_serial_number(uint32_t serial_number)
{
    s_config_params.tag_serial_number = serial_number;
    
    nrf51_tag_db_write_sector(GP0_PAGE);
}

uint32_t* get_tag_config_params(void)
{
    return (uint32_t*)&s_config_params;
}

uint32_t get_tag_config_params_length(void)
{
    return sizeof(s_config_params) / sizeof(uint32_t);
}

uint16_t get_tag_serial_number_length(void)
{
    return sizeof(s_config_params.tag_serial_number);
}

uint32_t get_adv_duration(void)
{
    return s_config_params.adv_duration;
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
