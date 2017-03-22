/**
* @file nrf51_tag_connection_parameters.c
* @brief Source File for the BLE Connection Parameters.
*
*/

#include "nrf51_tag_error.h"
#include "nrf51_tag_headers.h"

// ---------------------------------------------------------------------------
// Connection Parameters Settings
// ---------------------------------------------------------------------------

/**< Time from initiating event (connect or start of notification) to first 
* time sd_ble_gap_conn_param_update is called (20 seconds). 
*/
#define FIRST_CONN_PARAMS_UPDATE_DELAY APP_TIMER_TICKS(20000, SYS_TIMER_PRESCALER)

/**< Time between each call to sd_ble_gap_conn_param_update after the first 
* call (5 seconds). 
*/
#define NEXT_CONN_PARAMS_UPDATE_DELAY APP_TIMER_TICKS(5000, SYS_TIMER_PRESCALER)

/**< Number of attempts before giving up the connection parameter negotiation. 
*/
#define MAX_CONN_PARAMS_UPDATE_COUNT 3                                           

// ---------------------------------------------------------------------------
// Enable Connection Parameters Update
// Note: Add ble_conn_params.c from the SDK if enabled
// ---------------------------------------------------------------------------
//#define ENABLE_CONNECTION_PARAMETERS_UPDATE

// ---------------------------------------------------------------------------
// static support functions
// ---------------------------------------------------------------------------

/**@brief Function for handling a Connection Parameters error.
 *
 * @param[in] nrf_error Error code containing information about what went wrong.
 */
#ifdef ENABLE_CONNECTION_PARAMETERS_UPDATE

static void nrf51_tag_connection_parameters_error_handler(uint32_t nrf_error)
{
    APP_ERROR_HANDLER(nrf_error);
}
#endif

// ---------------------------------------------------------------------------
// Connection Parameters Interface Functions
// Note: Add ble_conn_params.c from the SDK if enabled
// ---------------------------------------------------------------------------
//#define ENABLE_CONNECTION_PARAMETERS_UPDATE

/**@brief Function for setting the BLE Connection Parameters.
 */
void nrf51_tag_set_connection_parameters(void)
{
#ifdef ENABLE_CONNECTION_PARAMETERS_UPDATE
    ble_conn_params_init_t cp_init = {0};

    DBG_INITIALIZE_CONN_PARAM();
    
    cp_init.p_conn_params                  = NULL;
    cp_init.first_conn_params_update_delay = FIRST_CONN_PARAMS_UPDATE_DELAY;
    cp_init.next_conn_params_update_delay  = NEXT_CONN_PARAMS_UPDATE_DELAY;
    cp_init.max_conn_params_update_count   = MAX_CONN_PARAMS_UPDATE_COUNT;
    cp_init.start_on_notify_cccd_handle    = BLE_GATT_HANDLE_INVALID;
    cp_init.disconnect_on_fail             = true;
    cp_init.evt_handler                    = NULL;
    cp_init.error_handler                  = rdi_connection_parameters_error_handler;

    uint32_t err_code = ble_conn_params_init(&cp_init);
    APP_ERROR_CHECK(err_code);
#endif
}
