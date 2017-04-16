/**
* @file nrf51_tag_services.c
* @brief Source file for the CGM Service.
*
*/

#include "nrf51_tag_error.h"
#include "nrf51_tag_headers.h"

/**@brief Function for initializing the RI Tag service that will be used by the application.
 */
void nrf51_tag_initialize_services(void)
{
    nrf51_tag_status_service_initialize();

    //nrf51_tag_configuration_service_initialize();

    //nrf51_tag_debug_service_initialize();

}
