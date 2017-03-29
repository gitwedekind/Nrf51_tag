/**
* @file nrf51_tag_LIS3DH.h
* @brief Header file for tag STM LIS3DH Accelerometer.
*
*/

#pragma once

#include "nrf51_tag_headers.h"

// ------------------------------------------------------------------------------------------------
// LIS3DH API's
// ------------------------------------------------------------------------------------------------

void nrf51_tag_i2c_init(void);

void nrf51_tag_lis3dh_set_mode(void);
