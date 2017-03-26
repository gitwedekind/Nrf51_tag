/**
* @file nrf51_tag_sys_timers.c
* @brief Source file for System Timer Functions.
*
*/

#include "nrf51_tag_error.h"
#include "nrf51_tag_timers.h"

APP_TIMER_DEF(s_connection_interval_timer_id);
APP_TIMER_DEF(s_uptime_timer_id);
//APP_TIMER_DEF(s_ble_start_timer_id);
//APP_TIMER_DEF(s_ble_stop_timer_id);
//APP_TIMER_DEF(s_stack_check_timer_id);

// ------------------------------------------------------------------------------------------------
//
// ------------------------------------------------------------------------------------------------

void nrf51_tag_connection_interval_timer_start(void)
{
    uint32_t err_code = app_timer_start(s_connection_interval_timer_id, APP_TIMER_TICKS(1000, SYS_TIMER_PRESCALER), NULL);
    APP_ERROR_CHECK(err_code);
}

void nrf51_tag_connection_interval_timer_stop(void)
{
    uint32_t err_code = app_timer_stop(s_connection_interval_timer_id);
    APP_ERROR_CHECK(err_code);
}

void nrf51_tag_connection_interval_timeout_handler(void* p_context)
{
    extern void timer_test(void);
    timer_test();
}

void nrf51_tag_system_uptime_timer_start(void)
{
    uint32_t err_code = app_timer_start(s_uptime_timer_id, APP_TIMER_TICKS(1000, SYS_TIMER_PRESCALER), NULL);
    APP_ERROR_CHECK(err_code);
}

void nrf51_tag_uptime_timeout_handler(void* p_context)
{
    void nrf51_tag_system_uptime_callback(void);
    nrf51_tag_system_uptime_callback();
}

// ------------------------------------------------------------------------------------------------
//
// ------------------------------------------------------------------------------------------------

/**@brief Function to initialize System Timers.
 */
void nrf51_tag_timers_init(void)
{
    uint32_t err_code = NRF_SUCCESS;
    
    DBG_INITIALIZE_TIMERS();
    
    // Initialize the app timer module
    //
    APP_TIMER_INIT
    (
        SYS_TIMER_PRESCALER, 
        SYS_TIMER_OP_QUEUE_SIZE, 
        false // Note: Do not use the scheduler
    );

    err_code = app_timer_create
    (
        &s_connection_interval_timer_id,
        APP_TIMER_MODE_REPEATED,
        nrf51_tag_connection_interval_timeout_handler
    );
    APP_ERROR_CHECK(err_code);

    err_code = app_timer_create
    (
        &s_uptime_timer_id,
        APP_TIMER_MODE_SINGLE_SHOT,
        nrf51_tag_uptime_timeout_handler
    );
    APP_ERROR_CHECK(err_code);
        
    nrf51_tag_system_uptime_timer_start();
}

/**@brief
 */
uint32_t get_system_time(void)
{
    return NRF_RTC0->COUNTER;
}

/**@brief
 */
uint32_t get_system_diff(uint32_t start_time)
{
    uint32_t system_ticks = NRF_RTC0->COUNTER;
    
    return (system_ticks - start_time) / RTC1_SCALER;
}

/**@brief
 */
uint32_t get_system_diff_ms(uint32_t start_time)
{
    uint32_t system_ticks = NRF_RTC0->COUNTER;
    
    return (system_ticks - start_time) / RTC2_SCALER;
}
