/**
* @file BLE400_Utils.h
* @brief Header file for BLE400 Development Board
*
*/

#pragma once

#include "nrf51_std_headers.h"
#include "nrf51_sys_headers.h"

#ifdef ENABLE_BLE400_DEV_BOARD

//-------------------------------------------------------------------------------------------------
// LED Defines
//-------------------------------------------------------------------------------------------------

static const uint32_t LED0 = 18;
static const uint32_t LED1 = 19;
static const uint32_t LED2 = 20;
static const uint32_t LED3 = 21;
static const uint32_t LED4 = 22;

static const uint32_t LED_BLINK_DELAY = 100;

#define LED_ON(x_led) nrf_gpio_pin_write(x_led, ON)
#define LED_OFF(x_led) nrf_gpio_pin_write(x_led, OFF)

void ble400_initialize_leds(void);

#define DEV_BOARD_INIT_LEDS() ble400_initialize_leds()

//-------------------------------------------------------------------------------------------------
// GPIO Defines
//-------------------------------------------------------------------------------------------------

static const uint32_t GPIO0 = 0;
static const uint32_t GPIO1 = 1;
static const uint32_t GPIO2 = 2;
static const uint32_t GPIO3 = 3;
static const uint32_t GPIO4 = 4;

static const uint32_t GPIO_TOGGLE_DELAY = 100;

#define GPIO_ON(x_pin) nrf_gpio_pin_write(x_pin, ON)
#define GPIO_OFF(x_pin) nrf_gpio_pin_write(x_pin, OFF)

void ble400_initialize_gpio_pins(void);

#define DEV_BOARD_INIT_GPIO() ble400_initialize_gpio_pins()

//-------------------------------------------------------------------------------------------------
// Button GPIO Defines
//-------------------------------------------------------------------------------------------------

static const uint32_t BUTTON0 = 16;
static const uint32_t BUTTON1 = 17;

#define GPIOTE_CHANNEL_0 0

void ble400_initialize_buttons(void);
#define DEV_BOARD_INIT_BUTTONS() ble400_initialize_buttons()

void GPIOTE_IRQHandler_BLE400(void);
#define DEV_BOARD_BUTTONS() GPIOTE_IRQHandler_BLE400()

#else

#define DEV_BOARD_INIT_LEDS()
#define DEV_BOARD_INIT_GPIO()
#define DEV_BOARD_INIT_BUTTONS()
#define DEV_BOARD_BUTTONS()

#endif
