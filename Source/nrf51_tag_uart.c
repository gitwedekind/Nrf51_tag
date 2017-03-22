/**
* @file nrf51_tag_uart.c
* @brief Source file for the system UART code.
*
*/

#include "nrf51_tag_uart.h"

#ifdef TAG_UART_ENABLED

//-------------------------------------------------------------------------------------------------
// Module Variables / Constants
//-------------------------------------------------------------------------------------------------

static void default_rx_callback(uint8_t chr)
{
}

static void default_tx_callback(void)
{
}

static void default_error_callback(uint32_t err)
{
}

//-------------------------------------------------------------------------------------------------
// Module Variables / Constants
//-------------------------------------------------------------------------------------------------

static PFN_RX_CALLBACK s_pfn_rx_callback       = default_rx_callback;
static PFN_TX_CALLBACK s_pfn_tx_callback       = default_tx_callback;
static PFN_ERROR_CALLBACK s_pfn_error_callback = default_error_callback;

static uint32_t s_inten_bits = 0x00000000;

static const uint32_t TX_BUFFER_LENGTH = 128;
static volatile uint32_t s_tx_length = 0;

static uint8_t s_tx_buffer[TX_BUFFER_LENGTH] = {0};

static volatile uint32_t s_tx_index = 0;
static volatile uint8_t s_tx_active = 0;
    
#define TX_PIN_NUMBER 9  // UART TX pin number
#define RX_PIN_NUMBER 11 // UART RX pin number

#define DISABLE_HWFC
#define ENABLE_HWFC

#ifdef DISABLE_HWFC
#undef ENABLE_HWFC
#endif

#ifdef ENABLE_HWFC
#define RTS_PIN_NUMBER 8  // UART RTS pin number
#define CTS_PIN_NUMBER 10 // UART CTS pin number
#else
#define RTS_PIN_NUMBER 0xFFFFFFFF // Disable
#define CTS_PIN_NUMBER 0xFFFFFFFF // Disable
#endif

/**
 *
 */
static void tag_uart_clear_events(void)
{
    NRF_UART0->EVENTS_RXDRDY = 0;
    NRF_UART0->EVENTS_TXDRDY = 0;
    NRF_UART0->EVENTS_CTS    = 0;
    NRF_UART0->EVENTS_ERROR  = 0;
    NRF_UART0->EVENTS_NCTS   = 0;
    NRF_UART0->EVENTS_RXTO   = 0;
}

//-------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------

void tag_uart_callback(void)
{
}

//-------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------

/**
 *
 */
static void tag_uart_config(void)
{
    NRF_UART0->TASKS_STOPTX = 1;
    NRF_UART0->TASKS_STOPRX = 1;

    NRF_UART0->ENABLE = (UART_ENABLE_ENABLE_Disabled << UART_ENABLE_ENABLE_Pos);
    
    nrf_gpio_cfg_output(TX_PIN_NUMBER);
    nrf_gpio_pin_set(TX_PIN_NUMBER);
    
    nrf_gpio_cfg_input(RX_PIN_NUMBER, NRF_GPIO_PIN_NOPULL);  

    nrf_gpio_cfg_output(CTS_PIN_NUMBER);
    nrf_gpio_pin_clear(CTS_PIN_NUMBER);

    nrf_gpio_cfg_input(RTS_PIN_NUMBER, NRF_GPIO_PIN_NOPULL);  

    NRF_UART0->CONFIG = 0;
    NRF_UART0->CONFIG |= (UART_CONFIG_PARITY_Excluded << UART_CONFIG_PARITY_Pos);
    NRF_UART0->CONFIG |= (UART_CONFIG_HWFC_Enabled << UART_CONFIG_HWFC_Pos);

    NRF_UART0->BAUDRATE = (UART_BAUDRATE_BAUDRATE_Baud115200 << UART_BAUDRATE_BAUDRATE_Pos);

    NRF_UART0->PSELTXD = TX_PIN_NUMBER;
    NRF_UART0->PSELRXD = RX_PIN_NUMBER;

    NRF_UART0->PSELRTS = RTS_PIN_NUMBER;
    NRF_UART0->PSELCTS = CTS_PIN_NUMBER;
    
    NRF_UART0->INTENCLR = 0xFFFFFFFF;
    
    if ( s_inten_bits & UART_INTENSET_RXDRDY_Msk)
    {
        NRF_UART0->INTENSET = (UART_INTENSET_RXDRDY_Enabled << UART_INTENSET_RXDRDY_Pos);
    }
    
    if ( s_inten_bits & UART_INTENSET_TXDRDY_Msk)
    {
        NRF_UART0->INTENSET = (UART_INTENSET_TXDRDY_Enabled << UART_INTENSET_TXDRDY_Pos);
    }

    if ( s_inten_bits & UART_INTENSET_ERROR_Msk)
    {
        NRF_UART0->INTENSET = (UART_INTENSET_ERROR_Enabled << UART_INTENSET_ERROR_Pos);
    }

    tag_uart_clear_events();

    NVIC_ClearPendingIRQ(UART0_IRQn);
    NVIC_SetPriority(UART0_IRQn, UART_IRQ_PRIORITY);
    NVIC_EnableIRQ(UART0_IRQn);

    NRF_UART0->ENABLE = (UART_ENABLE_ENABLE_Enabled << UART_ENABLE_ENABLE_Pos);
    
    NRF_UART0->TASKS_STARTTX = 1;
    NRF_UART0->TASKS_STARTRX = 1;
}

//-------------------------------------------------------------------------------------------------
// UART Interface functions
//-------------------------------------------------------------------------------------------------

/**
 *
 */
void tag_uart_initialize(void)
{
    s_pfn_rx_callback    = default_rx_callback;
    s_pfn_tx_callback    = default_tx_callback;
    s_pfn_error_callback = default_error_callback;
    
    s_inten_bits = 0x00000000;

    s_inten_bits |= UART_INTENSET_RXDRDY_Msk;
    
    s_inten_bits |= UART_INTENSET_TXDRDY_Msk;

    s_inten_bits |= UART_INTENSET_ERROR_Msk;
    
    tag_uart_config();
}

/**@brief Function for testing UART I/O Status.
 */
bool tag_is_uart_enabled(void)
{
    return NRF_UART0->TASKS_STARTTX;
}

/**@brief Function for disabling UART I/O.
 */
void tag_disable_uart(void)
{
    if ( NRF_UART0->ENABLE )
    {
        NRF_UART0->ENABLE = (UART_ENABLE_ENABLE_Disabled << UART_ENABLE_ENABLE_Pos);

        NRF_UART0->TASKS_STOPTX = 1;
        NRF_UART0->TASKS_STOPRX = 1;
        
        tag_uart_clear_events();
    }
}

/**@brief Function for enabling UART I/O.
 */
void tag_enable_uart(void)
{
    if ( !NRF_UART0->ENABLE )
    {
        // Enable / Configure NRF_UART0
        //        
        tag_uart_config();
    }
}

/**
 *
 */
void tag_uart_tx_buffer_isr(const uint8_t* p_buffer, uint32_t length)
{
    if ( !s_tx_active && NRF_UART0->ENABLE && p_buffer )
    {
        s_tx_active = 1;

        s_tx_length = length;

        memcpy(s_tx_buffer, p_buffer, s_tx_length);
        
        s_tx_index = 0;
        
        NRF_UART0->EVENTS_TXDRDY = 0; 
        
        NRF_UART0->TXD = s_tx_buffer[s_tx_index];
    }
}

/**
 *
 */
void tag_uart_tx_string_isr(const uint8_t* p_string)
{
    tag_uart_tx_buffer_isr(p_string, strlen((char*)p_string));
}

/**
 *
 */
void tag_uart_tx_buffer_isr_pend(const uint8_t* p_buffer, uint32_t length)
{
    if ( NRF_UART0->ENABLE && p_buffer )
    {
        while (s_tx_active);
        
        s_tx_active = 1;

        s_tx_length = length;

        memcpy(s_tx_buffer, p_buffer, s_tx_length);
        
        s_tx_index = 0;
        
        NRF_UART0->EVENTS_TXDRDY = 0; 
        
        NRF_UART0->TXD = s_tx_buffer[s_tx_index];
    }
}

/**
 *
 */
void tag_uart_tx_string_isr_pend(const uint8_t* p_string)
{
    tag_uart_tx_buffer_isr_pend(p_string, strlen((char*)p_string));
}

/**
 *
 */
uint8_t tag_uart_tx_active(void)
{
    return s_tx_active;
}

/**
 *
 */
void UART0_IRQHandler(void)
{
    if ( NRF_UART0->EVENTS_RXDRDY )
    {
        NRF_UART0->EVENTS_RXDRDY = 0;
        
        s_pfn_rx_callback(NRF_UART0->RXD);
    }
    
    if ( NRF_UART0->EVENTS_CTS || NRF_UART0->EVENTS_NCTS )
    {
        NRF_UART0->EVENTS_CTS = 0;
        NRF_UART0->EVENTS_NCTS = 0;
    }
    
    if ( NRF_UART0->EVENTS_TXDRDY )
    {
        NRF_UART0->EVENTS_TXDRDY = 0;

        s_pfn_tx_callback();
        
        ++s_tx_index;
        
        if (s_tx_index < s_tx_length)
        {
            NRF_UART0->TXD = s_tx_buffer[s_tx_index];
        }
        else
        {
            s_tx_active = 0;
        }
    }
    
    if ( NRF_UART0->EVENTS_RXTO )
    {
        NRF_UART0->EVENTS_RXTO = 0;
    }
    
    if ( NRF_UART0->EVENTS_ERROR )
    {
        NRF_UART0->EVENTS_ERROR = 0;
        
        s_pfn_error_callback(NRF_UART0->ERRORSRC);
    }
    
    NVIC_ClearPendingIRQ(UART0_IRQn);
}

#endif // ENABLE_TAG_UART
