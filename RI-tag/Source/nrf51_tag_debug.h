/** @file nrf51_tag_debug.h
 */

#pragma once

#include "nrf51_std_headers.h"
#include "nrf51_sys_headers.h"

#include "BLE400_Utils.h"

#include "nrf51_tag_uart.h"

#ifdef ENABLE_CJMCU_DEV_BOARD

#define LED0_PIN 07

#define LED0_ENABLE() nrf_gpio_cfg_output(LED0_PIN)
#define LED0_ON() nrf_gpio_pin_write(LED0_PIN, 0)
#define LED0_OFF() nrf_gpio_pin_write(LED0_PIN, 1);
#define LED0_TOGGLE() nrf_gpio_pin_toggle(LED0_PIN);

#else

#define LED0_ENABLE() 
#define LED0_ON() 
#define LED0_OFF() 
#define LED0_TOGGLE()

#endif
// ------------------------------------------------------------------------------------------------
// Debug constants
// ------------------------------------------------------------------------------------------------

//#define TAG_UART_ENABLED
//#define TAG_RTT_ENABLED

// ------------------------------------------------------------------------------------------------
// UART API
// ------------------------------------------------------------------------------------------------

#if defined(TAG_UART_ENABLED) || defined(TAG_RTT_ENABLED)

static const char* CLEAR_SCREEN_STR = "\033[2J\033[1;1H";

static const char* CRLF  = "\r\n";
static const char* ARROW = "\r\n--> ";

//-------------------------------------------------------------------------------------------------
// Preprocessor Magic
//-------------------------------------------------------------------------------------------------
#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define LINE_NO TOSTRING(__LINE__)

#endif

#if defined(TAG_UART_ENABLED)

#define UART_TX_BUFFER_LENGTH 128
extern char g_uart_tx[UART_TX_BUFFER_LENGTH];

void uart_hex_dump(const char* p_msg, const uint8_t* p_data, size_t length);
void bd_address(const char* p_msg, const uint8_t* p_data, size_t length);

#define DBG_PRINT(x_str) tag_uart_tx_string_isr_pend((uint8_t*)x_str)

#define DBG(...) \
    snprintf(g_uart_tx, UART_TX_BUFFER_LENGTH-1, __VA_ARGS__); \
    DBG_PRINT(g_uart_tx)
    
#define DBG_HEX_DUMP(x_msg, x_data, x_length) \
	uart_hex_dump(x_msg, x_data, x_length)

#define DBG_ADDRESS(x_msg, x_data, x_length) \
	bd_address(x_msg, x_data, x_length)

#define FUNCTION() DBG("--> %s\r\n", __PRETTY_FUNCTION__ );
#define FUNCTION_COMPLETE() DBG("<-- %s\r\n", __PRETTY_FUNCTION__ );

#endif // TAG_UART_ENABLED

#if defined(TAG_RTT_ENABLED)

#include "SEGGER_RTT.h"

int SEGGER_RTT_printf(unsigned BufferIndex, const char * sFormat, ...);

void uart_hex_dump(const char* p_msg, const uint8_t* p_data, size_t length);
void bd_address(const char* p_msg, const uint8_t* p_data, size_t length);

#define DBG_PRINT(x_str) SEGGER_RTT_printf(0, (char*)x_str)

#define DBG(...) \
	SEGGER_RTT_printf(0, __VA_ARGS__);

#define DBG_HEX_DUMP(x_msg, x_data, x_length) \
	uart_hex_dump(x_msg, x_data, x_length)

#define DBG_ADDRESS(x_msg, x_data, x_length) \
	bd_address(x_msg, x_data, x_length)

#define FUNCTION() DBG("--> %s\r\n", __PRETTY_FUNCTION__ );
#define FUNCTION_COMPLETE() DBG("<-- %s\r\n", __PRETTY_FUNCTION__ );

#endif // TAG_RTT_ENABLED

#if !defined(TAG_UART_ENABLED) && !defined(TAG_RTT_ENABLED)

#define DBG_PRINT(x_str)
#define DBG(...)

#define DBG_HEX_DUMP(x_msg, x_data, x_length)
#define DBG_ADDRESS(x_msg, x_data, x_length)

#define FUNCTION()
#define FUNCTION_COMPLETE()

#endif // TAG_UART_ENABLED || TAG_RTT_ENABLED
