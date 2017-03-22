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
        err_code = sd_app_evt_wait();
        APP_ERROR_CHECK(err_code);
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
