/**
* @file nrf51_tag_version.h
* @brief Header file for tag version info.
*
*/

#pragma once

#include "nrf51_std_headers.h"

// ------------------------------------------------------------------------------------------------
// Version API's
// ------------------------------------------------------------------------------------------------

#define USE_AS_TAG

#if defined (USE_AS_TAG)
#define VERSION_APP_NAME	 	"RI TAG"
#elif defined (USE_AS_BEACON)
#define VERSION_APP_NAME		"RI_BEACON"
#else
#error define VERSION_APP_NAME
#endif

#define VERSION_FW_MAJOR		1
#define VERSION_FW_MINOR		0
#define VERSION_FW_REVISION		0

char const* nrf51_tag_version_get_name(void);
char const* nrf51_tag_version_get_version(void);
