/**
* @file nrf51_tag_radio_notification.h
* @brief Header file for the Nordic Radio Notfication Interface.
*
*/

#pragma once

#include "nrf51_tag_headers.h"

// ---------------------------------------------------------------------------
// Interface Functions
// ---------------------------------------------------------------------------

/**@brief Function for the Bond Manager initialization.
 */
void nrf51_tag_radio_notification_init(void);

// ------------------------------------------------------------------------------------------------
// Debug Message(s)
// ------------------------------------------------------------------------------------------------
#define ENABLE_NOTIFICATION_MESSAGES

#if defined(ENABLE_NOTIFICATION_MESSAGES)

#define DBG_INITIALIZE_NOTIFICATION() FUNCTION()

#else

#define DBG_INITIALIZE_NOTIFICATION()

#endif
