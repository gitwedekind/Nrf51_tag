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

int8_t nrf51_tag_temperature_get(void);

uint8_t nrf51_tag_lf_clock_enabled(void);

// ------------------------------------------------------------------------------------------------
// Debug Message(s)
// ------------------------------------------------------------------------------------------------
#define ENABLE_INITIALIZE_MESSAGES

#if defined(ENABLE_INITIALIZE_MESSAGES)

static inline uint32_t ram_total_size_get(void)
{
    uint32_t size_ram_blocks = (uint32_t)NRF_FICR->SIZERAMBLOCKS;
    uint32_t total_ram_size = size_ram_blocks;
    total_ram_size = total_ram_size * (NRF_FICR->NUMRAMBLOCK);
    return total_ram_size;
}

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
    
#define DBG_LF_CLOCK() {\
    DBG("--> LF Clock Status: %d\r\n", NRF_CLOCK->EVENTS_LFCLKSTARTED ); }

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
    
#define DBG_LF_CLOCK()

#endif

