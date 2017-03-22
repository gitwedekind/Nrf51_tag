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

#define SYS_TIMER_PRESCALER     4095  /**< Value of the RTC1 PRESCALER register. */
#define SYS_TIMER_MAX_TIMERS    5     /**< Maximum number of simultaneously created timers. */
#define SYS_TIMER_OP_QUEUE_SIZE 15    /**< Size of timer operation queues. */

static const uint32_t TICK_INTERVAL       = 125;
static const uint32_t TICK_MULTIPLER_SEC  = 1000;
static const uint32_t TICK_MULTIPLER_MSEC = 100;
static const uint32_t MULTIPLER_MSEC      = 10;

static const uint16_t RTC1_SCALER = 32768;
static const uint16_t RTC2_SCALER = 33;

//----------------------------------------------------------------------------
// System Timer Functions
//----------------------------------------------------------------------------

void connection_interval_timer_start(void);
void uart_disable_timer_start(void);

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