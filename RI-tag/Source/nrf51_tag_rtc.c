/**
* @file nrf51_tag_rtc.c
* @brief Header file for tag RTC.
 */

#include "nrf51_tag_error.h"
#include "nrf51_tag_lis3dh.h"
#include "nrf51_tag_rtc.h"

// ------------------------------------------------------------------------------------------------
// LIS3DH Data
// ------------------------------------------------------------------------------------------------

static uint32_t s_adv_trigger_time = 0;

static uint32_t s_adv_trigger_threshold = 0;

static uint8_t s_tag_threshold = 0;

static uint8_t s_tag_sample_time = 0;

#ifdef ENABLE_8_BIT_MODE
static int8_t s_x = {0};
static int8_t s_y = {0};
static int8_t s_z = {0};
#else
static LIS3DH_RAW_CONVERTER_T s_x = {0};
static LIS3DH_RAW_CONVERTER_T s_y = {0};
static LIS3DH_RAW_CONVERTER_T s_z = {0};
#endif

static const uint32_t SYSTEM_SIGNATURE = 0xBADDC0FF;
    
static __attribute__((zero_init)) uint32_t s_system_signature;
static __attribute__((zero_init)) uint32_t s_system_uptime;

static uint8_t s_tag_data_ready = 0;

static uint32_t s_reference_time = 0;

#define MAX_RTC_DB_ENTRIES 2

static __align(4) ble_tag_db_entry_t s_tag_db_entry[MAX_RTC_DB_ENTRIES] = {0};

static uint8_t s_db_record_index = 0;

static uint8_t s_db_entry_index = 0;

static uint8_t s_db_entry_count = 0;

static void lis3dh_read_int1_data(void)
{
#ifdef ENABLE_8_BIT_MODE
    
    if ( s_db_record_index == 0 )
    {
        s_tag_db_entry[s_db_entry_index].timestamp = s_system_uptime;
    }
    
    s_x = s_tag_db_entry[s_db_entry_index].data[s_db_record_index].x = nrf51_tag_lis3dh_read_register(LIS3DH_OUT_X_H_r);
    s_y = s_tag_db_entry[s_db_entry_index].data[s_db_record_index].y = nrf51_tag_lis3dh_read_register(LIS3DH_OUT_Y_H_r);
    s_z = s_tag_db_entry[s_db_entry_index].data[s_db_record_index].z = nrf51_tag_lis3dh_read_register(LIS3DH_OUT_Z_H_r);
    
    DBG("INT1: %d, %d, %d\r\n", s_x, s_y, s_z); 

    ++s_db_record_index;
    
    if ( s_db_record_index == MAX_DB_RECORDS_PER_ENTRY )
    {
        nrf51_tag_db_write_entry(&s_tag_db_entry[s_db_entry_index]);
        
        ++s_db_entry_count;
        
        s_db_record_index = 0;
        
        s_db_entry_index = (s_db_entry_index == 0) ? 1 : 0;
        
        memset(&s_tag_db_entry[s_db_entry_index], 0, sizeof(ble_tag_db_entry_t));
    }
#else
    uint8_t xl = nrf51_tag_lis3dh_read_register(LIS3DH_OUT_X_L_r);
    uint8_t xh = nrf51_tag_lis3dh_read_register(LIS3DH_OUT_X_H_r);
    s_x.raw = MAKE_U16(xl,xh);
    
    uint8_t yl = nrf51_tag_lis3dh_read_register(LIS3DH_OUT_Y_L_r);
    uint8_t yh = nrf51_tag_lis3dh_read_register(LIS3DH_OUT_Y_H_r);
    s_y.raw = MAKE_U16(yl,yh);

    uint8_t zl = nrf51_tag_lis3dh_read_register(LIS3DH_OUT_Z_L_r);
    uint8_t zh = nrf51_tag_lis3dh_read_register(LIS3DH_OUT_Z_H_r);
    s_z.raw = MAKE_U16(zl,zh);
#endif
}

//-------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------

void nrf51_tag_system_uptime_callback(void)
{
    ++s_system_uptime;
    
    nrf51_tag_diagnostic_rtc_timer();
    
    if ( s_tag_data_ready )
    {
        if ( (s_system_uptime - s_reference_time) >= s_tag_sample_time ) 
        {
            s_reference_time = s_system_uptime;
            
            lis3dh_read_int1_data();
        
            if ( ( abs(s_x) < s_tag_threshold) && 
                 ( abs(s_y) < s_tag_threshold) &&
                 ( abs(s_z) < s_tag_threshold) )
            {
                if ( s_db_record_index == 0 )
                {
                    s_tag_data_ready = 0;
                    
                    DBG("s_tag_data_ready: %d, s_db_entry_count: %d\r\n", s_tag_data_ready, s_db_entry_count);
                    
                    s_db_entry_count = 0;
                }
            }
        }
    }
    
    if ( (s_system_uptime - s_adv_trigger_time) >= s_adv_trigger_threshold )
    {
        s_adv_trigger_time = s_system_uptime; 
        
        if ( nrf51_tag_get_connection_handle() == BLE_CONN_HANDLE_INVALID )
        {
            nrf51_tag_start_advertising();
        }
    }
}

uint32_t nrf51_tag_get_system_uptime(void)
{
    return s_system_uptime * RTC_OFFSET;
}

void nrf51_tag_initialize_rtc(void)
{
    //s_adv_trigger_threshold = ( get_adv_time() * 60 ) * RTC_SAMPLE_RATE;
    s_adv_trigger_threshold = ( get_adv_time() * 15 ) * RTC_SAMPLE_RATE;
    
    uint32_t reset_reason = 0;
    sd_power_reset_reason_get(&reset_reason);
    
    if ( s_system_signature != SYSTEM_SIGNATURE )
    {
        DBG("--> system_uptime reset:  %d\r\n", nrf51_tag_get_system_uptime()); 
        s_system_signature = SYSTEM_SIGNATURE;
        s_system_uptime = 0;
    }
    
    DBG("--> system_uptime %d\r\n", nrf51_tag_get_system_uptime()); 
}

void nrf51_tag_data_ready(void)
{
    s_tag_threshold = get_accelerometer_threshold() / 2;
    
    s_tag_sample_time = get_rtc_sample_rate() / get_accelerometer_sample_rate();
    
    s_reference_time = s_system_uptime - s_tag_sample_time;
    
    s_tag_data_ready = 1;
}
