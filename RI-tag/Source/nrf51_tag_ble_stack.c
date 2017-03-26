/**
* @file nrf51_tag_stack.c
* @brief Source file for Radio Interface Functions.
*
*/

#include "nrf51_tag_error.h"
#include "nrf51_tag_headers.h"

//-------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------
static nrf_clock_lf_cfg_t nrf_clock_lf_cfg =
{
    NRF_CLOCK_LF_SRC_XTAL,
    0,
    0,
    NRF_CLOCK_LF_XTAL_ACCURACY_250_PPM
};

//-------------------------------------------------------------------------------------------------
// static dispatch functions
//-------------------------------------------------------------------------------------------------

/**@brief Function for dispatching a BLE stack event to all modules with a BLE stack event handler.
 *
 * @details This function is called from the softdevice after a BLE stack
 *          event has been received.
 *
 * @param[in]   p_ble_evt Bluetooth stack event.
 */
static void ble_evt_dispatch(ble_evt_t * p_ble_evt)
{
    softdevice_on_ble_evt(p_ble_evt);
}

/**@brief Function for dispatching a system event to interested modules.
 *
 * @details This function is called from the System event interrupt handler after a system
 *          event has been received.
 *
 * @param[in]   sys_evt   System stack event.
 */
static void sys_evt_dispatch(uint32_t sys_evt)
{
    DBG("--> sys_evt: 0x%x\r\n", sys_evt);
}

/**@brief Function for initializing the Device Information Service.
 */
static void nrf51_tag_service_init_dis(void)
{
    // Clear Device Information Service structure.
    //
    ble_dis_init_t dis_init;
    memset(&dis_init, '\0', sizeof(dis_init));
    
    ble_srv_ascii_to_utf8(&dis_init.manufact_name_str, (char*)NRF51_TAG_MANUFACTURE_NAME);
    
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&dis_init.dis_attr_md.read_perm);
    BLE_GAP_CONN_SEC_MODE_SET_NO_ACCESS(&dis_init.dis_attr_md.write_perm);

    uint32_t err_code = ble_dis_init(&dis_init);
    APP_ERROR_CHECK(err_code);
}

//-------------------------------------------------------------------------------------------------
// Radio Interface Functions
//-------------------------------------------------------------------------------------------------

/**@brief Function to initialize the BLE Stack Interface.
 */
void nrf51_tag_stack_init(void)
{
    nrf51_tag_ble_stack_enable();
    
    nrf51_tag_set_tx_power(DBM_0);
    
    nrf51_tag_set_gap_parameters();
    
    nrf51_tag_set_connection_parameters();
    
    nrf51_tag_set_security_parameters();
    
    nrf51_tag_initialize_authentication_status();

    nrf51_tag_set_gap_device_name((const uint8_t*)NRF51_TAG_DEVICE_NAME, strlen(NRF51_TAG_DEVICE_NAME));
    
//#define ENABLE_RADIO_NOTIFICATIONS
#ifdef ENABLE_RADIO_NOTIFICATIONS
    nrf51_tag_radio_notification_init();
#endif
    
    nrf51_tag_initialize_connection_settings();
    
    nrf51_tag_initialize_gap_conn_sec();
    
    nrf51_tag_initialize_gap_sec_info_request();
    
    nrf51_tag_service_init_dis();
    
    nrf51_tag_initialize_services();
}

/**@brief Function for initializing the BLE stack.
 *
 * @details Initializes the SoftDevice and the BLE event interrupt.
 */
void nrf51_tag_ble_stack_enable(void)
{
    uint32_t err_code = NRF_SUCCESS;
    uint8_t sd_is_enabled = 0;
    
    DBG_STACK_INITIALIZE();
    
    sd_softdevice_is_enabled(&sd_is_enabled);
    
    if ( !sd_is_enabled )
    {
        // Initialize the SoftDevice handler module.
        //
        SOFTDEVICE_HANDLER_INIT(&nrf_clock_lf_cfg, NULL);

        ble_enable_params_t ble_enable_params = {0};
        
        err_code = softdevice_enable_get_default_config
        (
            NRF_BLE_CENTRAL_LINK_COUNT,
            NRF_BLE_PERIPHERAL_LINK_COUNT,
            &ble_enable_params
        );
        APP_ERROR_CHECK(err_code);

        ble_enable_params.common_enable_params.vs_uuid_count = 10;

        // Enable BLE stack
        //
#if (NRF_SD_BLE_API_VERSION == 3)
        ble_enable_params.gatt_enable_params.att_mtu = NRF_BLE_GATT_MAX_MTU_SIZE;
#endif
        err_code = softdevice_enable(&ble_enable_params);
        APP_ERROR_CHECK(err_code);

        // Register with the SoftDevice handler module for BLE events.
        //
        err_code = softdevice_ble_evt_handler_set(ble_evt_dispatch);
        APP_ERROR_CHECK(err_code);
        
        // Register with the SoftDevice handler module for BLE events.
        //
        err_code = softdevice_sys_evt_handler_set(sys_evt_dispatch);
        APP_ERROR_CHECK(err_code);
    }
}

/**@brief Function for disabling the BLE stack.
 *
 * @details
 */
void nrf51_tag_ble_stack_disable(void)
{
    uint8_t sd_is_enabled = 0;
    
    sd_softdevice_is_enabled(&sd_is_enabled);
    
    if ( sd_is_enabled )
    {
        uint32_t err_code = softdevice_handler_sd_disable();
        APP_ERROR_CHECK(err_code);
    }
}

/**@brief Function
 */
void nrf51_tag_ble_set_gap_address(ble_gap_addr_t* p_gap_addr)
{
    uint32_t err_code = NRF_SUCCESS;
    
    err_code = sd_ble_gap_address_set(BLE_GAP_ADDR_CYCLE_MODE_NONE, p_gap_addr);
    APP_ERROR_CHECK(err_code);
}

/**@brief Function
 */
void nrf51_tag_ble_get_gap_address(ble_gap_addr_t* p_gap_addr)
{
    uint32_t err_code = NRF_SUCCESS;
    
    err_code = sd_ble_gap_address_get(p_gap_addr);
    APP_ERROR_CHECK(err_code);
}

/**@brief
 */
bool nrf51_tag_is_cccd_configured(uint16_t cccd_handle)
{
    uint32_t err_code = NRF_SUCCESS;
	uint8_t  cccd_value_buffer[BLE_CCCD_VALUE_LEN] = {0};
    bool is_sync_notif_enabled = false;
    ble_gatts_value_t gatts_value = {0};
	
    gatts_value.len     = BLE_CCCD_VALUE_LEN;
    gatts_value.offset  = 0;
    gatts_value.p_value = cccd_value_buffer;
    
    err_code = sd_ble_gatts_value_get(cccd_handle, 0, &gatts_value);
    APP_ERROR_CHECK(err_code);
    
    is_sync_notif_enabled = ble_srv_is_notification_enabled(cccd_value_buffer);
    
    return is_sync_notif_enabled;
}
