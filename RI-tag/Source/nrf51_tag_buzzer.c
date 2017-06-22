/**
* @file nrf51_tag_buzzer.c
* @brief ource file for tag buzzer.
 */

#include "nrf51_tag_error.h"
#include "nrf51_tag_headers.h"

#define BUZZER_01 13
#define BUZZER_02 30

static uint8_t s_buzzer_state  = 0;
static uint8_t s_toggle        = 0;
static uint8_t s_timer_on      = 0;
static uint8_t s_total_time_on = 0;
static uint32_t s_timer_ref    = 0;

#define TIMER_CYCLE_TIME 2
#define TIMER_ON_TIME_MAX (30 * TIMER_CYCLE_TIME)

#define FREQ_2KHZ 250
#define FREQ_1KHZ 500
#define FREQ_500HZ 1000

//-------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------

static void configure_timer(void)
{		
    NRF_TIMER2->TASKS_STOP  = 1;
    NRF_TIMER2->TASKS_CLEAR = 1;
    
    NRF_TIMER2->MODE        =  TIMER_MODE_MODE_Timer;
    NRF_TIMER2->PRESCALER   = 4; // SysClk / 2^ PRESCALER) =  16,000,000/16 = 1us resolution
    NRF_TIMER2->BITMODE     = (TIMER_BITMODE_BITMODE_16Bit << TIMER_BITMODE_BITMODE_Pos);
    NRF_TIMER2->CC[0]       = FREQ_2KHZ-1;

    // Enable interrupt on Timer 2, both for CC[0] and CC[1] compare match events
    //
    NRF_TIMER2->INTENSET = 0;
    NRF_TIMER2->INTENSET |= (TIMER_INTENSET_COMPARE0_Enabled << TIMER_INTENSET_COMPARE0_Pos);
    
    NVIC_SetPriority(TIMER2_IRQn, 3);
    NVIC_EnableIRQ(TIMER2_IRQn);
}

static void nrf51_tag_buzzer_timer_start(void)
{
    NRF_TIMER2->POWER = 1;
    
    configure_timer();
        
    s_buzzer_state  = 1;
    s_timer_on      = 1;
    s_total_time_on = 0;
    
    s_toggle = 1;
    
     nrf_gpio_pin_write(BUZZER_01, OFF);
    nrf_gpio_pin_write(BUZZER_02, ON);

    s_timer_ref = nrf51_tag_get_system_uptime() - 1;

    NRF_TIMER2->TASKS_START = 1;
}

static void nrf51_tag_buzzer_timer_stop(void)
{
    nrf_gpio_pin_write(BUZZER_01, OFF);
    nrf_gpio_pin_write(BUZZER_02, OFF);

    NRF_TIMER2->TASKS_STOP  = 1;
    NRF_TIMER2->TASKS_CLEAR = 1;
    NRF_TIMER2->POWER       = 0;
    
    s_buzzer_state = 0;
}

/** TIMTER2 peripheral interrupt handler. This interrupt handler is called whenever there it a TIMER2 interrupt
 */
void TIMER2_IRQHandler(void)
{
    if ( (NRF_TIMER2->EVENTS_COMPARE[0] != 0) && 
       ((NRF_TIMER2->INTENSET & TIMER_INTENSET_COMPARE0_Msk) != 0))
    {
        
        NRF_TIMER2->EVENTS_COMPARE[0] = 0;
        NRF_TIMER2->TASKS_CLEAR       = 1;
        
        if ( (nrf51_tag_get_system_uptime() - s_timer_ref) > TIMER_CYCLE_TIME )
        {
            s_timer_ref = nrf51_tag_get_system_uptime();
            
            s_total_time_on += TIMER_CYCLE_TIME;
            
            if ( s_timer_on )
            {
                s_timer_on = 0;
            }
            else
            {
                s_timer_on = 1;
            }
        }

        if ( s_timer_on )
        {
            if ( s_toggle )
            {
                s_toggle = 0;
                nrf_gpio_pin_write(BUZZER_01, ON);
                nrf_gpio_pin_write(BUZZER_02, OFF);
            }
            else
            {
                s_toggle = 1;
                nrf_gpio_pin_write(BUZZER_01, OFF);
                nrf_gpio_pin_write(BUZZER_02, ON);
            }
        }
        
        if ( s_total_time_on >= TIMER_ON_TIME_MAX )
        {
            nrf51_tag_buzzer_timer_stop();
        }
    }
}

void nrf51_tag_initialize_buzzer(void)
{
    nrf_gpio_cfg_output(BUZZER_01);
    nrf_gpio_pin_write(BUZZER_01, OFF);

    nrf_gpio_cfg_output(BUZZER_02);
    nrf_gpio_pin_write(BUZZER_02, OFF);
}

uint8_t get_tag_buzzer_state(void)
{
    return s_buzzer_state;
}

void set_tag_buzzer_state(uint8_t buzzer_state)
{
    s_buzzer_state = buzzer_state;
    
    if ( s_buzzer_state )
    {
        nrf51_tag_buzzer_timer_start();
    }
    else
    {
        nrf51_tag_buzzer_timer_stop();    
    }
}
