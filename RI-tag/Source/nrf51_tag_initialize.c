/**
* @file nrf51_tag_initialize.c
* @brief Source file for Initializing the nrf51 tag application code.
*
*/

#include "nrf51_tag_error.h"
#include "nrf51_tag_initialize.h"

#include "nrf51_tag_flash.h"
#include "nrf51_tag_db.h"

// ----------------------------------------------------------------------------
// 
// ----------------------------------------------------------------------------

static uint8_t s_lf_clock_enabled = 0;

int8_t nrf51_tag_temperature_get(void)
{
    int32_t temp = 0;
    uint32_t err_code = NRF_SUCCESS;
    
    err_code = sd_temp_get(&temp);
    APP_ERROR_CHECK(err_code);
    
    temp /= 4;
    
    return temp;
}

static void Enable_LF32k(void)
{
    uint32_t CNT = 0;
    
    s_lf_clock_enabled = 0;
    
    NRF_CLOCK->LFCLKSRC = (CLOCK_LFCLKSRCCOPY_SRC_Xtal << CLOCK_LFCLKSRCCOPY_SRC_Pos);

    NRF_CLOCK->EVENTS_LFCLKSTARTED = 0;
    NRF_CLOCK->TASKS_LFCLKSTART    = 1;
    
    while ( NRF_CLOCK->EVENTS_LFCLKSTARTED == 0 )
    {
        ++CNT;
        
        if ( CNT >= (16 * 1000 * 100) )
        {
            break;
        }
    }
    
    s_lf_clock_enabled = (NRF_CLOCK->EVENTS_LFCLKSTARTED == 1);
    
    nrf51_tag_diagnostic_lfclk(s_lf_clock_enabled);
    
    DBG_LF_CLOCK();
}

uint8_t nrf51_tag_lf_clock_enabled(void)
{
    return s_lf_clock_enabled;
}

/**@brief Function for initializing the Dexcom application code.
 */
void nrf51_tag_initialize(void)
{
    DBG_INITIALIZE();
    
    DBG_TOTAL_RAM_SIZE();
    
    DBG_RAMON();
    DBG_RESET_REASON();
    DBG_GPRR();
    DBG_TX_POWER();
    
    nrf51_tag_initialize_diagnostics();
    
    initialize_power_manage();
 
    Enable_LF32k();
    
    nrf51_tag_timers_init();

    nrf51_tag_stack_init();

    nrf51_tag_initialize_rtc();

    nrf51_tag_db_initialize();
    
    nrf51_tag_lis3dh_init();
    
    DBG_GAP_ADDR();
    DBG_TEMPERATURE();

    DBG_INITIALIZE_COMPLETE();
}
