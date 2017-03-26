/**
* @file nrf51_tag_initialize.h
* @brief Header file for the nrf51 tag initialization functions.
*
*/

#pragma once

#include "nrf51_tag_headers.h"

// ------------------------------------------------------------------------------------------------
// Global Variables
// ------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------
// Initialize Interface Functions
// ------------------------------------------------------------------------------------------------

/**@brief Function for initializing the application code.
 */
void nrf51_tag_initialize(void);

uint32_t nrf51_tag_temperature_get(void);

// ------------------------------------------------------------------------------------------------
// Debug Message(s)
// ------------------------------------------------------------------------------------------------
#define ENABLE_INITIALIZE_MESSAGES

#if defined(ENABLE_INITIALIZE_MESSAGES)

#define DBG_INITIALIZE() FUNCTION()
#define DBG_INITIALIZE_COMPLETE() FUNCTION_COMPLETE()

#define DBG_TOTAL_RAM_SIZE() {\
    DBG("--> total ram size: %d\r\n", ram_total_size_get() ); }

    #define DBG_RAMON() {\
    DBG("--> power ram blocks  : 0x%x\r\n", NRF_POWER->RAMON ); }

#define DBG_RESET_REASON() {\
    DBG("--> power reset reason: 0x%x\r\n", NRF_POWER->RESETREAS ); }

#define DBG_GPRR() {\
    DBG("--> retention register: 0x%x\r\n", NRF_POWER->GPREGRET ); }

#define DBG_TX_POWER() \
    DBG("--> TX Power: %d (dBm)\r\n", nrf51_tag_get_tx_power())

#define DBG_GAP_ADDR() { \
    ble_gap_addr_t gap_addr = {0}; \
    nrf51_tag_ble_get_gap_address(&gap_addr); \
    DBG("--> GAP Address, type: %s\r\n", BLE_GAP_ADDR_TYPE[gap_addr.addr_type]); \
    DBG_ADDRESS(NULL, gap_addr.addr, BLE_GAP_ADDR_LEN); }

//#define DBG_ENABLE_TEMPERATURE    
#ifdef DBG_ENABLE_TEMPERATURE    
#define DBG_TEMPERATURE() { \
    nrf51_tag_enable_16MHz_crystal(); \
    DBG("--> Temperature: %d\r\n", nrf51_tag_temperature_get()); }
#else
#define DBG_TEMPERATURE()
#endif
    
#else

#define DBG_INITIALIZE()
#define DBG_INITIALIZE_COMPLETE()

#define DBG_TOTAL_RAM_SIZE()

#define DBG_RAMON()
#define DBG_RESET_REASON()
#define DBG_GPRR()
#define DBG_TX_POWER()

#define DBG_GAP_ADDR()
#define DBG_TEMPERATURE()
    
#endif

