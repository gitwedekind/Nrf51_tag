/** @file nrf51_tag_debug.c
 *
 */

#include "nrf51_tag_debug.h"

// ------------------------------------------------------------------------------------------------
//
// ------------------------------------------------------------------------------------------------

#ifdef TAG_UART_ENABLED
char g_uart_tx[UART_TX_BUFFER_LENGTH] = {0};
#endif

#if defined(TAG_UART_ENABLED) || defined(TAG_RTT_ENABLED)

// ------------------------------------------------------------------------------------------------
//
// ------------------------------------------------------------------------------------------------
void uart_hex_dump(const char* p_msg, const uint8_t* p_data, size_t length)
{
	static const size_t MAX_COLUMNS = 16;
    size_t index = 0;

    if ( p_msg != NULL )
    {
    	DBG_PRINT(p_msg);
    	DBG(", length: %d", length);
    	DBG_PRINT(CRLF);
    }

    for ( index = 0; index < length; ++index)
    {
        uint8_t value = *p_data++;

        if ( index && !(index % MAX_COLUMNS) )
        {
        	DBG_PRINT(CRLF);
        }

        DBG("%02x ", value);
    }

    DBG_PRINT(CRLF);
}

// ------------------------------------------------------------------------------------------------
//
// ------------------------------------------------------------------------------------------------
void bd_address(const char* p_msg, const uint8_t* p_data, size_t length)
{
    size_t index = 0;

    if ( p_msg != NULL )
    {
    	DBG_PRINT(p_msg);
    	DBG(", length: %d", length);
    	DBG_PRINT(", addr: 0x");
    }
    else
    {
    	DBG_PRINT("--> addr: 0x");
    }

    for ( index = 0; index < length; ++index)
    {
        uint8_t value = *p_data++;

        DBG("%02x", value);

    	if ( index < length-1 )
        {
    		DBG_PRINT(":");
        }
    }

    DBG_PRINT(CRLF);
}

#endif
