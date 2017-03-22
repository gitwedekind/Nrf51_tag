/**
* @file main.h
* @brief Header file for main.
*
*/

#pragma once

#include "nrf51_tag_error.h"
#include "nrf51_tag_headers.h"

//-------------------------------------------------------------------------------------------------
// Main Loop Tasks
//-------------------------------------------------------------------------------------------------

static const uint32_t MAIN_LOOP_TASK_IDLE         = 0x00000000; 
static const uint32_t MAIN_LOOP_TASK_BLE_TRANSMIT = 0x00000001;
static const uint32_t MAIN_LOOP_TASK_BLE_RECEIVE  = 0x00000002;
static const uint32_t MAIN_LOOP_TASK_BLE_START    = 0x00000004;
static const uint32_t MAIN_LOOP_TASK_BLE_STOP     = 0x00000008;
static const uint32_t MAIN_LOOP_TASK_RESERVED     = 0xFFFFFFF0;

//-------------------------------------------------------------------------------------------------
// Main Loop Interface Functions
//-------------------------------------------------------------------------------------------------

/**@brief Sets the active task bit to trigger main loop processing. 
 */
void ml_set_active_task(uint32_t TaskId);

/**@brief Sets the active task bits to idle.
 */
void ml_active_tasks_idle(void);

// ------------------------------------------------------------------------------------------------
// Debug Message(s)
// ------------------------------------------------------------------------------------------------
#define ENABLE_MAIN_MESSAGES

#if defined(ENABLE_MAIN_MESSAGES)

#define DBG_MAIN_ENTERED() \
    DBG_PRINT(CLEAR_SCREEN_STR); \
    DBG("--> main(), %s %s\r\n", __DATE__, __TIME__); \
    DBG("--> app name: %s\r\n", nrf51_tag_version_get_name()); \
    DBG("--> version : %s\r\n", nrf51_tag_version_get_version())

#define DBG_MAIN_STACK() \
    DBG("--> stack base: 0x%x, stack top: 0x%x\r\n", STACK_BASE, STACK_TOP)

extern uint32_t Image$$RW_IRAM1$$Base;
#define DBG_RAM_START() { \
    const volatile uint32_t ram_start = (uint32_t) &Image$$RW_IRAM1$$Base; \
    DBG("--> RAM Start: 0x%x\r\n", ram_start); }

#else

#define DBG_MAIN_ENTERED()
#define DBG_MAIN_STACK()
#define DBG_RAM_START()

#endif
