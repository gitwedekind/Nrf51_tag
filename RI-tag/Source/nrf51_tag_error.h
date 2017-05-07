/* @file nrf51_tag_error.h
 */

#pragma once

#include "nrf51_std_headers.h"

#ifndef WIN32

#include "nrf51_sys_headers.h"

#include "nrf51_tag_debug.h"
#include "nrf51_tag_power_manage.h"

#else

#define DBG(...)

#define FUNCTION() DBG("--> %s\r\n", __PRETTY_FUNCTION__ );
#define FUNCTION_COMPLETE() DBG("<-- %s\r\n", __PRETTY_FUNCTION__ );

#define __align(x)

#define APP_ERROR_CHECK(err_code)

#endif

#define NRF_TAG_ERROR_BASE (0x8000)

#define NRF_TAG_ERROR_SUCCESS      (NRF_TAG_ERROR_BASE + 0)
#define NRF_TAG_ERROR_ASSERT       (NRF_TAG_ERROR_BASE + 1)
#define NRF_TAG_ERROR_SPI_RX_ERROR (NRF_TAG_ERROR_BASE + 2)
#define NRF_TAG_ERROR_LIS3DH_RESET (NRF_TAG_ERROR_BASE + 3)

#ifdef DEBUG

#define PRINT_NRF_TAG_ERROR(x_error) \
    DBG("\r\n *** NRF ERROR, code: 0x%x (%d)\r\n", x_error.err_code, x_error.err_code); \
    DBG("line    : %d\r\n", x_error.line_num); \
    DBG("file    : %s\r\n", x_error.p_file_name)

#define PRINT_ENTERING_SLEEP_MODE() \
    DBG("--> Entering Sleep Mode...\r\n")

#define PRINT_SYSTEM_RESET() \
    DBG("--> Performing a System Reset\r\n")

#else

#define PRINT_NRF_TAG_ERROR(x_error)

#define PRINT_ENTERING_SLEEP_MODE()
#define PRINT_SYSTEM_RESET()

#endif
