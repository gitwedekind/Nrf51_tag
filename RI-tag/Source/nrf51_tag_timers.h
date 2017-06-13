/**
* @file nrf51_tag_sys_timers.h
* @brief System Header for System Timer Functions.
*
*/

#pragma once

#include "nrf51_std_headers.h"
#include "nrf51_sys_headers.h"

//----------------------------------------------------------------------------
// System Timer Constants
//----------------------------------------------------------------------------

#define SYS_TIMER_PRESCALER     326   /**< Value of the RTC1 PRESCALER register. - 100 Hz */
#define SYS_TIMER_MAX_TIMERS    5     /**< Maximum number of simultaneously created timers. */
#define SYS_TIMER_OP_QUEUE_SIZE 15    /**< Size of timer operation queues. */

static const uint16_t RTC1_SCALER = 1;
static const uint16_t RTC2_SCALER = 1;

#define RTC_SAMPLE_RATE             1    ///< 1 Hz
#define RTC_SYSTEM_UPTIME_INTERVAL  1000 ///< 1 second
#define RTC_DATA_READY_INTERVAL     100  ///< .1 seconds

#define RTC_DATA_READY_OFFSET 100 ///< ms

//----------------------------------------------------------------------------
// System Timer Functions
//----------------------------------------------------------------------------

void nrf51_tag_connection_interval_timer_start(void);
void nrf51_tag_connection_interval_timer_stop(void);

void nrf51_tag_system_uptime_timer_start(void);

void nrf51_tag_data_ready_timer_start(void);
void nrf51_tag_data_ready_timer_stop(void);

/**@brief Function to initialize System Timers.
 */
void nrf51_tag_timers_init(void);

/**@brief
 */
uint32_t get_system_time(void);

/**@brief
 */
uint32_t get_system_diff(uint32_t start_time);

/**@brief
 */
uint32_t get_system_diff_ms(uint32_t start_time);

// ------------------------------------------------------------------------------------------------
// Debug Message(s)
// ------------------------------------------------------------------------------------------------
#define ENABLE_TIMER_MESSAGES

#if defined(ENABLE_TIMER_MESSAGES)

#define DBG_INITIALIZE_TIMERS() FUNCTION()

#else

#define DBG_INITIALIZE_TIMERS()

#endif
