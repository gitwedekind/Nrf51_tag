/**
* @file nrf51_tag_buzzer.h
* @brief Header file for tag buzzer.
*
*/

#pragma once

#include "nrf51_std_headers.h"

// ------------------------------------------------------------------------------------------------
// Version API's
// ------------------------------------------------------------------------------------------------

void nrf51_tag_initialize_buzzer(void);

uint8_t get_tag_buzzer_state(void);

void set_tag_buzzer_state(uint8_t buzzer_state);
