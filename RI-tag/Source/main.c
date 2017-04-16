/** @file main.c
 *  @brief Remote Insight RI-tag main source file
 */

#include "main.h"

//-------------------------------------------------------------------------------------------------
// Static Variables / Constants
//-------------------------------------------------------------------------------------------------

/**
* Active Tasks "Bit-Array".    
*/
static uint32_t s_ActiveTasks = MAIN_LOOP_TASK_IDLE;

//-------------------------------------------------------------------------------------------------
// Main Loop Interface / Support Functions
//-------------------------------------------------------------------------------------------------

/**@brief Clears the active task bit.
 */
static void ml_clear_active_task(uint32_t TaskId)
{
    s_ActiveTasks &= ~TaskId;
    s_ActiveTasks &= ~MAIN_LOOP_TASK_RESERVED;
}

/**@brief Sets the active task bit to trigger main loop processing.
 */
void ml_set_active_task(uint32_t TaskId)
{
    s_ActiveTasks |= TaskId;
}

/**@brief Sets the active task bits to idle.
 */
void ml_active_tasks_idle(void)
{
    s_ActiveTasks = MAIN_LOOP_TASK_IDLE;
}

void timer_test(void)
{
    //LED0_TOGGLE();
}

/**@brief main entry point.
 */
int main(void)
{
	//LED0_ENABLE();
	//LED0_OFF();
    
    TAG_UART_INITIALIZE();
    
    DBG_MAIN_ENTERED();
    DBG_MAIN_STACK();
    DBG_RAM_START();
    
    //DEV_BOARD_INIT_LEDS();
    //DEV_BOARD_INIT_GPIO();
    
    ml_active_tasks_idle();
    
    nrf51_tag_initialize();
    
    nrf51_tag_set_advertising_parameters(NRF51_TAG_ADV_INTERVAL, NRF51_TAG_ADV_TIMEOUT_IN_SECONDS);
    
    nrf51_tag_update_device_name(153);
    nrf51_tag_update_manufacturing_data(0, 153,  0, 1);
    
    nrf51_tag_advertising_packet_initialize();
    
    nrf51_tag_start_advertising();
		
    while (1)
    {
        if ( s_ActiveTasks == MAIN_LOOP_TASK_IDLE )
        {
            power_manage();
        }

        if ( s_ActiveTasks & MAIN_LOOP_TASK_BLE_TRANSMIT )
        {
            ml_clear_active_task(MAIN_LOOP_TASK_BLE_TRANSMIT);
        }
        else if ( s_ActiveTasks & MAIN_LOOP_TASK_BLE_RECEIVE )
        {
            ml_clear_active_task(MAIN_LOOP_TASK_BLE_RECEIVE);
        }
        else if ( s_ActiveTasks & MAIN_LOOP_TASK_BLE_START )
        {
            ml_clear_active_task(MAIN_LOOP_TASK_BLE_START);
        }
        else if ( s_ActiveTasks & MAIN_LOOP_TASK_BLE_STOP )
        {
            ml_clear_active_task(MAIN_LOOP_TASK_BLE_STOP);
        }
    }
}
