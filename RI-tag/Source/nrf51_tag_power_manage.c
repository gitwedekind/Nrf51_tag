/**
* @file nrf51_tag_power_manage.c
* @brief Source File for Power Management Control.
*
*/

#include "nrf51_tag_error.h"
#include "nrf51_tag_power_manage.h"

//----------------------------------------------------------------------------
// Radio Interface Power Manage Variables
//----------------------------------------------------------------------------

static power_mode_t s_power_mode = PM_SLEEP;

//----------------------------------------------------------------------------
// static support functions
//----------------------------------------------------------------------------

void nrf51_tag_enable_16MHz_crystal(void)
{
    uint32_t is_running = 0;

    sd_clock_hfclk_is_running(&is_running);
    
    if ( !is_running )
    {
        sd_clock_hfclk_request();
        
        while (!is_running)
        {
            sd_clock_hfclk_is_running(&is_running);
            __NOP();
            __NOP();
            __NOP();
        }
    }
}

void nrf51_tag_disable_16MHz_crystal(void)
{
    uint32_t is_running = 1;

    sd_clock_hfclk_is_running(&is_running);
    
    if ( is_running )
    {
        NRF_CLOCK->EVENTS_HFCLKSTARTED = 0;
        
        sd_clock_hfclk_release();
        
        while (is_running)
        {
            sd_clock_hfclk_is_running(&is_running);

            __NOP();
            __NOP();
            __NOP();
        }
    }
}

/**@brief Function to configure the power for the system modules.
 *
 * The Nordic Chip system modules are at "Power ON" at system startup.  
 * Modules not used are set to "Power OFF" to ensure Low Power Operation
 * of the chip.  Modules without a POWER bit are commented so this function
 * can be used as a quick reference for all the system modules (nrf51.h).
 *
 */
static void nrf51_tag_module_power_settings(void)
{
    // NRF_POWER - Power Control
    // NRF_CLOCK - Clock Control
    // NRF_MPU   - Memory Protection Unit  
    // NRF_PU    - Patch Unit
    // NRF_AMLI  - AHB Multi-Layer Interface
    // NRF_RADIO - 2.4 GHz Radio

    NRF_UART0->POWER  = 0; // Universal Asynchronous Receiver / Transmitter 0
    NRF_SPI0->POWER   = 0; // Serial Peripheral Interface (Master) 0
    NRF_TWI0->POWER   = 0; // Two Wire Interface (Master) 0 Note: will not work without enabling this 
    NRF_SPI1->POWER   = 0; // Serial Peripheral Interface (Slave) 1
    NRF_TWI1->POWER   = 0; // Two Wire Interface (Slave) 1
    NRF_SPIS1->POWER  = 0; // Serial Peripheral Interface 0
    NRF_GPIOTE->POWER = 0; // GPIO Tasks and Events
    NRF_ADC->POWER    = 0; // Analog-to-Digital Controller
    NRF_TIMER0->POWER = 1; // Timer / Counter 0
    NRF_TIMER1->POWER = 0; // Timer / Counter 1
    NRF_TIMER2->POWER = 0; // Timer / Counter 2
    NRF_RTC0->POWER   = 1; // Real Time Counter 0 
    NRF_TEMP->POWER   = 0; // Temperature Sensor
    NRF_RNG->POWER    = 1; // Random Number Generator
    NRF_ECB->POWER    = 1; // Crypto ECB
    NRF_AAR->POWER    = 1; // Accelerated Address Resolver
    NRF_CCM->POWER    = 1; // AES CCM Mode Encryption
    NRF_WDT->POWER    = 0; // Watchdog Timer
    NRF_RTC1->POWER   = 1; // Real Time Counter 1
    NRF_QDEC->POWER   = 0; // Rotary Quadrature Decoder
    NRF_LPCOMP->POWER = 0; // Low Power Comparator
    
    // NRF_SWI  - Software Interrupts 
    // NRF_NVMC - non-volatile memory controller 
    // NRF_PPI  - Programmable Peripheral Interconnect 
    // NRF_FICR - Factory Information Configuration Registers 
    // NRF_UICR - User Information Configuration Registers 
    // NRF_GPIO - General Purpose Input / Output
}

void nrf51_tag_module_power_settings_debug(void)
{
    DBG("NRF_UART0->POWER: %d\r\n", NRF_UART0->POWER);
    DBG("NRF_SPI0->POWER: %d\r\n", NRF_SPI0->POWER);
    DBG("NRF_TWI0->POWER: %d\r\n", NRF_TWI0->POWER);
    DBG("NRF_SPI1->POWER: %d\r\n", NRF_SPI1->POWER);
    DBG("NRF_TWI1->POWER: %d\r\n", NRF_TWI1->POWER);
    DBG("NRF_SPIS1->POWER: %d\r\n", NRF_SPIS1->POWER);
    DBG("NRF_GPIOTE->POWER: %d\r\n", NRF_GPIOTE->POWER);
    DBG("NRF_ADC->POWER: %d\r\n", NRF_ADC->POWER);
    DBG("NRF_TIMER0->POWER: %d\r\n", NRF_TIMER0->POWER);
    DBG("NRF_TIMER1->POWER: %d\r\n", NRF_TIMER1->POWER);
    DBG("NRF_TIMER2->POWER: %d\r\n", NRF_TIMER2->POWER);
    DBG("NRF_RTC0->POWER: %d\r\n", NRF_RTC0->POWER);
    DBG("NRF_TEMP->POWER: %d\r\n", NRF_TEMP->POWER);
    DBG("NRF_RNG->POWER: %d\r\n", NRF_RNG->POWER);
    DBG("NRF_ECB->POWER: %d\r\n", NRF_ECB->POWER);
    DBG("NRF_AAR->POWER: %d\r\n", NRF_AAR->POWER);
    DBG("NRF_CCM->POWER: %d\r\n", NRF_CCM->POWER);
    DBG("NRF_WDT->POWER: %d\r\n", NRF_WDT->POWER);
    DBG("NRF_RTC1->POWER: %d\r\n", NRF_RTC1->POWER);
    DBG("NRF_QDEC->POWER: %d\r\n", NRF_QDEC->POWER);
    DBG("NRF_LPCOMP->POWER: %d\r\n", NRF_LPCOMP->POWER);

}

/**@brief
 */
static bool softdevice_is_enabled(void)
{
    uint8_t sd_is_enabled = 0;
    
    sd_softdevice_is_enabled(&sd_is_enabled);
    
    return sd_is_enabled ? true : false;
}

/**@brief
 */
static void enter_low_power_mode(void)
{
    uint32_t err_code = 0;
    
    if ( softdevice_is_enabled() )
    {
        //DBG_POWER_MANAGE_ENTER();
        
        //nrf51_tag_enable_16MHz_crystal();
        //nrf51_tag_disable_16MHz_crystal();

        err_code = sd_app_evt_wait();
        APP_ERROR_CHECK(err_code);

        //DBG_POWER_MANAGE_EXIT();
    }
    else // no soft device - sleep
    {
        // Clear Event Register
        //
        __SEV();

        // Wait for next event - need to call this twice
        //
        __WFE();
        __WFE();
    }
}

//----------------------------------------------------------------------------
// Radio Interface Power Manage Functions
//----------------------------------------------------------------------------

/**@brief Function for the Initializing the Power Manager Module.
 */
void initialize_power_manage(void)
{
    DBG_INITIALIZE_POWER_MANAGE();
    
    nrf51_tag_module_power_settings();
    
    s_power_mode = PM_IDLE;
}

/**@brief Radio Interface Power Manage function.
*/
void power_manage(void)
{
    if ( s_power_mode == PM_IDLE )
    {
        enter_low_power_mode();
    }
    else if ( s_power_mode == PM_SLEEP )
    {
        sd_power_system_off();
    }
    else if ( s_power_mode == PM_OFF )
    {
        power_mode_off();
    }
}

/**@brief Function to set the Power Mode to RDI_PM_IDLE.
 */
void set_power_mode_idle(void)
{
    s_power_mode = PM_IDLE;
}

/**@brief Function to set the Power Mode to RDI_PM_SLEEP.
 */
void set_power_mode_sleep(void)
{
    s_power_mode = PM_SLEEP;
}

/**@brief Function to set the Power Mode to RDI_PM_OFF.
 */
void set_power_mode_off(void)
{
    s_power_mode = PM_OFF;
}

/**@brief Function to get the Power Mode.
 */
power_mode_t get_power_mode(void)
{
    return s_power_mode;
}

/**@brief
 */
void power_mode_off(void)
{
    NRF_POWER->SYSTEMOFF = 1;
}
