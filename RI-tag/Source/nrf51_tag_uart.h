/**
* @file nrf51_tag_uart.h
* @brief Header file for the nrf51 tag UART.
*
*/

#include "nrf51_std_headers.h"
#include "nrf51_sys_headers.h"

#pragma once

//-------------------------------------------------------------------------------------------------
// RI-tag Headers
//-------------------------------------------------------------------------------------------------
#ifdef TAG_UART_ENABLED

#define UART_IRQ_PRIORITY 3

//-------------------------------------------------------------------------------------------------
// UART Callback(s)
//-------------------------------------------------------------------------------------------------

typedef void (*PFN_RX_CALLBACK)(uint8_t);
typedef void (*PFN_TX_CALLBACK)(void);
typedef void (*PFN_ERROR_CALLBACK)(uint32_t);

//-------------------------------------------------------------------------------------------------
// UART Interface Functions
//-------------------------------------------------------------------------------------------------

void tag_uart_initialize(void);

bool tag_is_uart_enabled(void);
void tag_disable_uart(void);
void tag_enable_uart(void);

void tag_uart_tx_buffer_isr(const uint8_t* p_buffer, uint32_t length);
void tag_uart_tx_string_isr(const uint8_t* pString);
uint8_t tag_uart_tx_active(void);

void tag_uart_tx_buffer_isr_pend(const uint8_t* p_buffer, uint32_t length);
void tag_uart_tx_string_isr_pend(const uint8_t* p_string);

#define TAG_UART_INITIALIZE() tag_uart_initialize()

#define LOOP_WHILE_TAG_UART_ACTIVE() while(tag_uart_tx_active())

#else

#define TAG_UART_INITIALIZE()

#define LOOP_WHILE_TAG_UART_ACTIVE()

#endif
