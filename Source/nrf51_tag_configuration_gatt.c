/**
* @file nrf51_tag_configuration_gatt.c
* @brief Source file for the Tag Configuration Command Read / Write Processing.
*
*/

#include "nrf51_tag_error.h"
#include "nrf51_tag_headers.h"

//-------------------------------------------------------------------------------------------------
// Tag Configuration GATT API
//-------------------------------------------------------------------------------------------------

/** @brief
*
*/
void nrf51_tag_configuration_write(ble_evt_t* p_ble_evt)
{
    ble_gatts_evt_write_t* p_write = &p_ble_evt->evt.gatts_evt.params.write;
    
    if ( p_write->handle == nrf51_tag_configuration_beacon_ids_value_handle() ||
         p_write->handle == nrf51_tag_configuration_adv_burst_interval_value_handle() ||
         p_write->handle == nrf51_tag_configuration_adv_burst_duration_value_handle()
       )
    {
        //p_write->auth_required;
        //p_write->data;
        //p_write->offset;
        //p_write->len;
    }
}

/** @brief
*
*/
void nrf51_tag_configuration_authorize_request(ble_evt_t* p_ble_evt)
{
    ble_gatts_evt_rw_authorize_request_t* p_rw_authorize_request = &p_ble_evt->evt.gatts_evt.params.authorize_request;
    
    if ( p_rw_authorize_request->request.read.handle == nrf51_tag_configuration_beacon_ids_value_handle() ||
         p_rw_authorize_request->request.read.handle == nrf51_tag_configuration_adv_burst_interval_value_handle() ||
         p_rw_authorize_request->request.read.handle == nrf51_tag_configuration_adv_burst_duration_value_handle()
    )
    {
        ble_gatts_rw_authorize_reply_params_t authorize_reply_params = {0};
        
        if ( p_rw_authorize_request->type == BLE_GATTS_AUTHORIZE_TYPE_READ )
        {
            authorize_reply_params.type                     = BLE_GATTS_AUTHORIZE_TYPE_READ;
            authorize_reply_params.params.read.gatt_status  = BLE_GATT_STATUS_SUCCESS;

            authorize_reply_params.params.read.update = 0;
            authorize_reply_params.params.read.offset = 0;
            authorize_reply_params.params.read.len    = 0;
            authorize_reply_params.params.read.p_data = NULL;

            uint32_t err_code = sd_ble_gatts_rw_authorize_reply
            (
                p_ble_evt->evt.gatts_evt.conn_handle,
                &authorize_reply_params
            );
            
            APP_ERROR_CHECK(err_code);
        }
        else if ( p_rw_authorize_request->type == BLE_GATTS_AUTHORIZE_TYPE_WRITE )
        {
        }
    }
}

/** @brief
*
*/
void nrf51_tag_configuration_system_attribute_missing(ble_evt_t* p_ble_evt)
{
}

/** @brief
*
*/
void nrf51_tag_configuration_handle_value_confirmation(ble_evt_t* p_ble_evt)
{
}

/** @brief
*
*/
void nrf51_tag_configuration_service_change_confirm(ble_evt_t* p_ble_evt)
{
}

/** @brief
*
*/
void nrf51_tag_configuration_timeout(ble_evt_t* p_ble_evt)
{
}

//-------------------------------------------------------------------------------------------------
// Tag Configuration Get / Set API
//-------------------------------------------------------------------------------------------------

/** @brief
*
*/
void nrf51_tag_configuration_beacon_ids_set(ble_tag_configuration_beacon_ids_t* p_tag_configuration_beacon_ids)
{
    uint32_t err_code = NRF_SUCCESS;
    
    bool is_cccd_configured = nrf51_tag_is_cccd_configured( nrf51_tag_configuration_beacon_ids_cccd_handle() );
    
    if ( is_cccd_configured )
    {
        ble_gatts_hvx_params_t hvx_params = {0};
        
        uint16_t length = sizeof(ble_tag_configuration_beacon_ids_t);
        
        hvx_params.handle   = nrf51_tag_configuration_beacon_ids_value_handle();
        hvx_params.type     = BLE_GATT_HVX_NOTIFICATION;
        hvx_params.offset   = 0;
        hvx_params.p_len    = &length;
        hvx_params.p_data   = (uint8_t*)p_tag_configuration_beacon_ids;
        
        err_code = sd_ble_gatts_hvx
        (
            nrf51_tag_get_connection_handle(), 
            &hvx_params
        );
        
        APP_ERROR_CHECK(err_code);
    }
    else
    {
        ble_gatts_value_t gatts_value = {0};
        
        gatts_value.len     = BLE_CCCD_VALUE_LEN;
        gatts_value.offset  = 0;
        gatts_value.p_value = (uint8_t*)p_tag_configuration_beacon_ids;
			
        err_code = sd_ble_gatts_value_set 
        (
            nrf51_tag_configuration_beacon_ids_value_handle(), 
            0, 
            &gatts_value
        );
        
        APP_ERROR_CHECK(err_code);
    }
}

/** @brief
*
*/
void nrf51_tag_configuration_beacon_ids_get(ble_tag_configuration_beacon_ids_t* p_tag_configuration_beacon_ids)
{
    uint32_t err_code = NRF_SUCCESS;

    ble_gatts_value_t gatts_value = {0};
    
    gatts_value.len     = BLE_CCCD_VALUE_LEN;
    gatts_value.offset  = 0;
    gatts_value.p_value = (uint8_t*)p_tag_configuration_beacon_ids;
        
    err_code = sd_ble_gatts_value_get 
    (
        nrf51_tag_configuration_beacon_ids_value_handle(), 
        0, 
        &gatts_value
    );
    
    APP_ERROR_CHECK(err_code);
}

/** @brief
*
*/
void nrf51_tag_configuration_adv_burst_interval_set(ble_tag_configuration_adv_burst_interval_t* p_tag_configuration_adv_burst_interval)
{
    uint32_t err_code = NRF_SUCCESS;
    
    bool is_cccd_configured = nrf51_tag_is_cccd_configured( nrf51_tag_configuration_adv_burst_interval_cccd_handle() );
    
    if ( is_cccd_configured )
    {
        ble_gatts_hvx_params_t hvx_params = {0};
        
        uint16_t length = sizeof(ble_tag_configuration_adv_burst_interval_t);
        
        hvx_params.handle   = nrf51_tag_configuration_adv_burst_interval_value_handle();
        hvx_params.type     = BLE_GATT_HVX_NOTIFICATION;
        hvx_params.offset   = 0;
        hvx_params.p_len    = &length;
        hvx_params.p_data   = (uint8_t*)p_tag_configuration_adv_burst_interval;
        
        err_code = sd_ble_gatts_hvx
        (
            nrf51_tag_get_connection_handle(), 
            &hvx_params
        );
        
        APP_ERROR_CHECK(err_code);
    }
    else
    {
        ble_gatts_value_t gatts_value = {0};
        
        gatts_value.len     = BLE_CCCD_VALUE_LEN;
        gatts_value.offset  = 0;
        gatts_value.p_value = (uint8_t*)p_tag_configuration_adv_burst_interval;
			
        err_code = sd_ble_gatts_value_set 
        (
            nrf51_tag_configuration_adv_burst_interval_value_handle(), 
            0, 
            &gatts_value
        );
        
        APP_ERROR_CHECK(err_code);
    }
}

/** @brief
*
*/
void nrf51_tag_configuration_adv_burst_interval_get(ble_tag_configuration_adv_burst_interval_t* p_tag_configuration_adv_burst_interval)
{
    uint32_t err_code = NRF_SUCCESS;

    ble_gatts_value_t gatts_value = {0};
    
    gatts_value.len     = BLE_CCCD_VALUE_LEN;
    gatts_value.offset  = 0;
    gatts_value.p_value = (uint8_t*)p_tag_configuration_adv_burst_interval;
        
    err_code = sd_ble_gatts_value_get 
    (
        nrf51_tag_configuration_adv_burst_interval_value_handle(), 
        0, 
        &gatts_value
    );
    
    APP_ERROR_CHECK(err_code);
}

/** @brief
*
*/
void nrf51_tag_configuration_adv_burst_duration_set(ble_tag_configuration_adv_burst_duration_t* p_tag_configuration_adv_burst_duration)
{
    uint32_t err_code = NRF_SUCCESS;
    
    bool is_cccd_configured = nrf51_tag_is_cccd_configured( nrf51_tag_configuration_adv_burst_duration_cccd_handle() );
    
    if ( is_cccd_configured )
    {
        ble_gatts_hvx_params_t hvx_params = {0};
        
        uint16_t length = sizeof(ble_tag_configuration_adv_burst_duration_t);
        
        hvx_params.handle   = nrf51_tag_configuration_adv_burst_duration_value_handle();
        hvx_params.type     = BLE_GATT_HVX_NOTIFICATION;
        hvx_params.offset   = 0;
        hvx_params.p_len    = &length;
        hvx_params.p_data   = (uint8_t*)p_tag_configuration_adv_burst_duration;
        
        err_code = sd_ble_gatts_hvx
        (
            nrf51_tag_get_connection_handle(), 
            &hvx_params
        );
        
        APP_ERROR_CHECK(err_code);
    }
    else
    {
        ble_gatts_value_t gatts_value = {0};
        
        gatts_value.len     = BLE_CCCD_VALUE_LEN;
        gatts_value.offset  = 0;
        gatts_value.p_value = (uint8_t*)p_tag_configuration_adv_burst_duration;
			
        err_code = sd_ble_gatts_value_set 
        (
            nrf51_tag_configuration_adv_burst_duration_value_handle(), 
            0, 
            &gatts_value
        );
        
        APP_ERROR_CHECK(err_code);
    }
}

/** @brief
*
*/
void nrf51_tag_configuration_adv_burst_duration_get(ble_tag_configuration_adv_burst_duration_t* p_tag_configuration_adv_burst_duration)
{
    uint32_t err_code = NRF_SUCCESS;

    ble_gatts_value_t gatts_value = {0};
    
    gatts_value.len     = BLE_CCCD_VALUE_LEN;
    gatts_value.offset  = 0;
    gatts_value.p_value = (uint8_t*)p_tag_configuration_adv_burst_duration;
        
    err_code = sd_ble_gatts_value_get 
    (
        nrf51_tag_configuration_adv_burst_duration_value_handle(), 
        0, 
        &gatts_value
    );
    
    APP_ERROR_CHECK(err_code);
}
