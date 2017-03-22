/**
* @file nrf51_tag_gap_params.c
* @brief Source file for Initializing the nrf51 tag gap parameters.
*
*/

#include "nrf51_tag_error.h"
#include "nrf51_tag_headers.h"

// ------------------------------------------------------------------------------------------------
// Static Variables
// ------------------------------------------------------------------------------------------------

#define MIN_CONN_INTERVAL MSEC_TO_UNITS(500, UNIT_1_25_MS)  /**< Minimum acceptable connection interval (0.5 seconds). */
#define MAX_CONN_INTERVAL MSEC_TO_UNITS(1000, UNIT_1_25_MS) /**< Maximum acceptable connection interval (1.00 second). */
#define SLAVE_LATENCY     0                                 /**< Slave latency. */
#define CONN_SUP_TIMEOUT  MSEC_TO_UNITS(4000, UNIT_10_MS)   /**< Connection supervisory timeout (4 seconds). */

/**@brief Function for the GAP initialization.
 *
 * This function sets up all the necessary GAP (Generic Access Profile) 
 * preferred connection parameters.
 */
void nrf51_tag_set_gap_parameters(void)
{
    uint32_t err_code = NRF_SUCCESS;
    ble_gap_conn_params_t gap_conn_params = {0};
    
    DBG_INITIALIZE_GAP_PARAM();

    gap_conn_params.min_conn_interval = MIN_CONN_INTERVAL;
    gap_conn_params.max_conn_interval = MAX_CONN_INTERVAL;
    gap_conn_params.slave_latency     = SLAVE_LATENCY;
    gap_conn_params.conn_sup_timeout  = CONN_SUP_TIMEOUT;

    err_code = sd_ble_gap_ppcp_set(&gap_conn_params);
    APP_ERROR_CHECK(err_code);
    
    err_code = sd_ble_gap_appearance_set(BLE_APPEARANCE_UNKNOWN);
    APP_ERROR_CHECK(err_code);
}

/**@brief Function for setting the GAP device name.
 */
void nrf51_tag_set_gap_device_name(uint8_t const * const p_dev_name, uint16_t length)
{
    uint32_t err_code = NRF_SUCCESS;
    ble_gap_conn_sec_mode_t sec_mode = {0};
    
    DBG_INITIALIZE_SET_DEVICE_NAME();

    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&sec_mode);

    err_code = sd_ble_gap_device_name_set
    (
        &sec_mode,
        p_dev_name,
        length
    );

    APP_ERROR_CHECK(err_code);
}
