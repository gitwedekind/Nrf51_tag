/**
* @file BLE400_Utils.c
* @brief Source file for BLE400 Development Board
 */

#include "BLE400_Utils.h"

#ifdef ENABLE_BLE400_DEV_BOARD

//-------------------------------------------------------------------------------------------------
// LED Implementation
//-------------------------------------------------------------------------------------------------

static void ble400_initialize_led(uint32_t pin)
{
    nrf_gpio_cfg_output(pin);

    nrf_gpio_pin_write(pin, ON);
    nrf_delay_ms(LED_BLINK_DELAY);
    nrf_gpio_pin_write(pin, OFF);
    nrf_gpio_pin_write(pin, ON);
    nrf_gpio_pin_write(pin, OFF);
}

void ble400_initialize_leds(void)
{
    ble400_initialize_led(LED0);
    ble400_initialize_led(LED1);
    ble400_initialize_led(LED2);
    ble400_initialize_led(LED3);
    ble400_initialize_led(LED4);
}

//-------------------------------------------------------------------------------------------------
// GPIO Implementation
//-------------------------------------------------------------------------------------------------

static void ble400_initialize_gpio(uint32_t pin)
{
    nrf_gpio_cfg_output(pin);

    nrf_gpio_pin_write(pin, ON);
    nrf_delay_ms(GPIO_TOGGLE_DELAY);
    nrf_gpio_pin_write(pin, OFF);
    nrf_gpio_pin_write(pin, ON);
    nrf_gpio_pin_write(pin, OFF);
}

void ble400_initialize_gpio_pins(void)
{
    ble400_initialize_gpio(GPIO0);
    ble400_initialize_gpio(GPIO1);
    ble400_initialize_gpio(GPIO2);
    ble400_initialize_gpio(GPIO3);
    ble400_initialize_gpio(GPIO4);
}

//-------------------------------------------------------------------------------------------------
// Button Implementation
//-------------------------------------------------------------------------------------------------

void GPIOTE_IRQHandler_BLE400(void)
{
    uint32_t b0_pressed = nrf_gpio_pin_read(BUTTON0);
    uint32_t b1_pressed = nrf_gpio_pin_read(BUTTON1);
    
    if (b0_pressed)
    {
        LED_OFF(LED0);
    }
    
    if (b1_pressed)
    {
        LED_ON(LED0);
    }
}
    
void ble400_initialize_buttons(void)
{
    nrf_gpio_cfg_sense_input(BUTTON0, NRF_GPIO_PIN_PULLUP, NRF_GPIO_PIN_SENSE_LOW);
    nrf_gpio_cfg_sense_input(BUTTON1, NRF_GPIO_PIN_PULLUP, NRF_GPIO_PIN_SENSE_LOW);
}

#endif // ENABLE_BLE400_DEV_BOARD
