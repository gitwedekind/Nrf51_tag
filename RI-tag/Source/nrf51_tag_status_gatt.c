/**
* @file nrf51_tag_status_gatt.c
* @brief Source file for the Tag Status Command Read / Write Processing.
*
*/

#include "nrf51_tag_error.h"
#include "nrf51_tag_headers.h"

/** @brief
*
*/
static void nrf51_tag_status_set_authorize_reply_read(ble_evt_t* p_ble_evt, ble_gatts_rw_authorize_reply_params_t* p_authorize_reply_params)
{
    p_authorize_reply_params->type                     = BLE_GATTS_AUTHORIZE_TYPE_READ;
    p_authorize_reply_params->params.read.gatt_status  = BLE_GATT_STATUS_SUCCESS;

    p_authorize_reply_params->params.read.update = 0;
    p_authorize_reply_params->params.read.offset = 0;
    p_authorize_reply_params->params.read.len    = 0;
    p_authorize_reply_params->params.read.p_data = NULL;

    uint32_t err_code = sd_ble_gatts_rw_authorize_reply
    (
        p_ble_evt->evt.gatts_evt.conn_handle,
        p_authorize_reply_params
    );
    
    APP_ERROR_CHECK(err_code);
}

//-------------------------------------------------------------------------------------------------
// Tag Status GATT API
//-------------------------------------------------------------------------------------------------

/** @brief
*
*/
void nrf51_tag_status_write(ble_evt_t* p_ble_evt)
{
    ble_gatts_evt_write_t* p_write = &p_ble_evt->evt.gatts_evt.params.write;
    
    if ( p_write->handle == nrf51_tag_status_uptime_value_handle() )
    {
        //p_write->auth_required;
        //p_write->data;
        //p_write->offset;
        //p_write->len;
    }
    else if ( p_write->handle == nrf51_tag_status_temperature_value_handle() )
    {
    }
    else if ( p_write->handle == nrf51_tag_status_battery_level_value_handle() )
    {
    }
    else if ( p_write->handle == nrf51_tag_status_firmware_revision_value_handle() )
    {
    }
    else if ( p_write->handle == nrf51_tag_status_beacon_record_count_value_handle() )
    {
    }
    else if ( p_write->handle == nrf51_tag_status_beacon_read_records_value_handle() )
    {
    }
    else if ( p_write->handle == nrf51_tag_status_activity_record_count_value_handle() )
    {
    }
    else if ( p_write->handle == nrf51_tag_status_activity_read_records_value_handle() )
    {
    }
}

/** @brief
*
*/
void nrf51_tag_status_authorize_request(ble_evt_t* p_ble_evt)
{
    ble_gatts_evt_rw_authorize_request_t* p_rw_authorize_request = &p_ble_evt->evt.gatts_evt.params.authorize_request;
    
    if ( p_rw_authorize_request->request.read.handle == nrf51_tag_status_uptime_value_handle() )
    {
        ble_gatts_rw_authorize_reply_params_t authorize_reply_params = {0};
        
        if ( p_rw_authorize_request->type == BLE_GATTS_AUTHORIZE_TYPE_READ )
        {
            nrf51_tag_status_set_authorize_reply_read(p_ble_evt, &authorize_reply_params);
        }
        else if ( p_rw_authorize_request->type == BLE_GATTS_AUTHORIZE_TYPE_WRITE )
        {
        }
    }
    else if ( p_rw_authorize_request->request.read.handle == nrf51_tag_status_temperature_value_handle() )
    {
        ble_gatts_rw_authorize_reply_params_t authorize_reply_params = {0};
        
        if ( p_rw_authorize_request->type == BLE_GATTS_AUTHORIZE_TYPE_READ )
        {
            nrf51_tag_status_set_authorize_reply_read(p_ble_evt, &authorize_reply_params);
        }
        else if ( p_rw_authorize_request->type == BLE_GATTS_AUTHORIZE_TYPE_WRITE )
        {
        }
    }
}

/** @brief
*
*/
void nrf51_tag_status_system_attribute_missing(ble_evt_t* p_ble_evt)
{
}

/** @brief
*
*/
void nrf51_tag_status_handle_value_confirmation(ble_evt_t* p_ble_evt)
{
}

/** @brief
*
*/
void nrf51_tag_status_service_change_confirm(ble_evt_t* p_ble_evt)
{
}

/** @brief
*
*/
void nrf51_tag_status_timeout(ble_evt_t* p_ble_evt)
{
}

//-------------------------------------------------------------------------------------------------
// Tag Status Get / Set API
//-------------------------------------------------------------------------------------------------

/** @brief
*
*/
void nrf51_tag_status_uptime_set(ble_tag_status_uptime_t* p_tag_status_uptime)
{
    uint32_t err_code = NRF_SUCCESS;
    
    ble_gatts_value_t gatts_value = {0};
    
    gatts_value.len     = BLE_CCCD_VALUE_LEN;
    gatts_value.offset  = 0;
    gatts_value.p_value = (uint8_t*)p_tag_status_uptime;
        
    err_code = sd_ble_gatts_value_set 
    (
        nrf51_tag_status_uptime_value_handle(), 
        0, 
        &gatts_value
    );
    
    APP_ERROR_CHECK(err_code);
}

/** @brief
*
*/
void nrf51_tag_status_uptime_get(ble_tag_status_uptime_t* p_tag_status_uptime)
{
    uint32_t err_code = NRF_SUCCESS;

    ble_gatts_value_t gatts_value = {0};
    
    gatts_value.len     = BLE_CCCD_VALUE_LEN;
    gatts_value.offset  = 0;
    gatts_value.p_value = (uint8_t*)p_tag_status_uptime;
        
    err_code = sd_ble_gatts_value_get 
    (
        nrf51_tag_status_uptime_value_handle(), 
        0, 
        &gatts_value
    );
    
    APP_ERROR_CHECK(err_code);
}

/** @brief
*
*/
void nrf51_tag_status_temperature_set(ble_tag_status_temperature_t* p_tag_status_temperature)
{
    uint32_t err_code = NRF_SUCCESS;
    
    ble_gatts_value_t gatts_value = {0};
    
    gatts_value.len     = BLE_CCCD_VALUE_LEN;
    gatts_value.offset  = 0;
    gatts_value.p_value = (uint8_t*)p_tag_status_temperature;
        
    err_code = sd_ble_gatts_value_set 
    (
        nrf51_tag_status_temperature_value_handle(), 
        0, 
        &gatts_value
    );
    
    APP_ERROR_CHECK(err_code);
}

/** @brief
*
*/
void nrf51_tag_status_temperature_get(ble_tag_status_temperature_t* p_tag_status_temperature)
{
    uint32_t err_code = NRF_SUCCESS;

    ble_gatts_value_t gatts_value = {0};
    
    gatts_value.len     = BLE_CCCD_VALUE_LEN;
    gatts_value.offset  = 0;
    gatts_value.p_value = (uint8_t*)p_tag_status_temperature;
        
    err_code = sd_ble_gatts_value_get 
    (
        nrf51_tag_status_temperature_value_handle(), 
        0, 
        &gatts_value
    );
    
    APP_ERROR_CHECK(err_code);
}

/** @brief
*
*/
void nrf51_tag_status_battery_level_set(ble_tag_status_battery_level_t* p_tag_status_battery_level)
{
    uint32_t err_code = NRF_SUCCESS;
    
    ble_gatts_value_t gatts_value = {0};
    
    gatts_value.len     = BLE_CCCD_VALUE_LEN;
    gatts_value.offset  = 0;
    gatts_value.p_value = (uint8_t*)p_tag_status_battery_level;
        
    err_code = sd_ble_gatts_value_set 
    (
        nrf51_tag_status_battery_level_value_handle(), 
        0, 
        &gatts_value
    );
    
    APP_ERROR_CHECK(err_code);
}

/** @brief
*
*/
void nrf51_tag_status_battery_level_get(ble_tag_status_battery_level_t* p_tag_status_battery_level)
{
    uint32_t err_code = NRF_SUCCESS;

    ble_gatts_value_t gatts_value = {0};
    
    gatts_value.len     = BLE_CCCD_VALUE_LEN;
    gatts_value.offset  = 0;
    gatts_value.p_value = (uint8_t*)p_tag_status_battery_level;
        
    err_code = sd_ble_gatts_value_get 
    (
        nrf51_tag_status_battery_level_value_handle(), 
        0, 
        &gatts_value
    );
    
    APP_ERROR_CHECK(err_code);
}

/** @brief
*
*/
void nrf51_tag_status_firmware_revision_set(ble_tag_status_firmware_revision_t* p_tag_status_firmware_revision)
{
    uint32_t err_code = NRF_SUCCESS;
    
    ble_gatts_value_t gatts_value = {0};
    
    gatts_value.len     = BLE_CCCD_VALUE_LEN;
    gatts_value.offset  = 0;
    gatts_value.p_value = (uint8_t*)p_tag_status_firmware_revision;
        
    err_code = sd_ble_gatts_value_set 
    (
        nrf51_tag_status_firmware_revision_value_handle(), 
        0, 
        &gatts_value
    );
    
    APP_ERROR_CHECK(err_code);
}

/** @brief
*
*/
void nrf51_tag_status_firmware_revision_get(ble_tag_status_firmware_revision_t* p_tag_status_firmware_revision)
{
    uint32_t err_code = NRF_SUCCESS;

    ble_gatts_value_t gatts_value = {0};
    
    gatts_value.len     = BLE_CCCD_VALUE_LEN;
    gatts_value.offset  = 0;
    gatts_value.p_value = (uint8_t*)p_tag_status_firmware_revision;
        
    err_code = sd_ble_gatts_value_get 
    (
        nrf51_tag_status_firmware_revision_value_handle(), 
        0, 
        &gatts_value
    );
    
    APP_ERROR_CHECK(err_code);
}

/** @brief
*
*/
void nrf51_tag_status_beacon_record_count_set(ble_tag_status_beacon_record_count_t* p_tag_status_beacon_record_count)
{
    uint32_t err_code = NRF_SUCCESS;
    
    ble_gatts_value_t gatts_value = {0};
    
    gatts_value.len     = BLE_CCCD_VALUE_LEN;
    gatts_value.offset  = 0;
    gatts_value.p_value = (uint8_t*)p_tag_status_beacon_record_count;
        
    err_code = sd_ble_gatts_value_set 
    (
        nrf51_tag_status_beacon_record_count_value_handle(), 
        0, 
        &gatts_value
    );
    
    APP_ERROR_CHECK(err_code);
}

/** @brief
*
*/
void nrf51_tag_status_beacon_record_count_get(ble_tag_status_beacon_record_count_t* p_tag_status_beacon_record_count)
{
    uint32_t err_code = NRF_SUCCESS;

    ble_gatts_value_t gatts_value = {0};
    
    gatts_value.len     = BLE_CCCD_VALUE_LEN;
    gatts_value.offset  = 0;
    gatts_value.p_value = (uint8_t*)p_tag_status_beacon_record_count;
        
    err_code = sd_ble_gatts_value_get 
    (
        nrf51_tag_status_beacon_record_count_value_handle(), 
        0, 
        &gatts_value
    );
    
    APP_ERROR_CHECK(err_code);
}

/** @brief
*
*/
void nrf51_tag_status_beacon_read_records_set(ble_tag_status_beacon_read_records_t* p_tag_status_beacon_read_records)
{
    uint32_t err_code = NRF_SUCCESS;
    
    ble_gatts_value_t gatts_value = {0};
    
    gatts_value.len     = BLE_CCCD_VALUE_LEN;
    gatts_value.offset  = 0;
    gatts_value.p_value = (uint8_t*)p_tag_status_beacon_read_records;
        
    err_code = sd_ble_gatts_value_set 
    (
        nrf51_tag_status_beacon_read_records_value_handle(), 
        0, 
        &gatts_value
    );
    
    APP_ERROR_CHECK(err_code);
}

/** @brief
*
*/
void nrf51_tag_status_beacon_read_records_get(ble_tag_status_beacon_read_records_t* p_tag_status_beacon_read_records)
{
    uint32_t err_code = NRF_SUCCESS;

    ble_gatts_value_t gatts_value = {0};
    
    gatts_value.len     = BLE_CCCD_VALUE_LEN;
    gatts_value.offset  = 0;
    gatts_value.p_value = (uint8_t*)p_tag_status_beacon_read_records;
        
    err_code = sd_ble_gatts_value_get 
    (
        nrf51_tag_status_beacon_read_records_value_handle(), 
        0, 
        &gatts_value
    );
    
    APP_ERROR_CHECK(err_code);
}

/** @brief
*
*/
void nrf51_tag_status_activity_record_count_set(ble_tag_status_activity_record_count_t* p_tag_status_activity_record_count)
{
    uint32_t err_code = NRF_SUCCESS;
    
    ble_gatts_value_t gatts_value = {0};
    
    gatts_value.len     = BLE_CCCD_VALUE_LEN;
    gatts_value.offset  = 0;
    gatts_value.p_value = (uint8_t*)p_tag_status_activity_record_count;
        
    err_code = sd_ble_gatts_value_set 
    (
        nrf51_tag_status_activity_record_count_value_handle(), 
        0, 
        &gatts_value
    );
    
    APP_ERROR_CHECK(err_code);
}

/** @brief
*
*/
void nrf51_tag_status_activity_record_count_get(ble_tag_status_activity_record_count_t* p_tag_status_activity_record_count)
{
    uint32_t err_code = NRF_SUCCESS;

    ble_gatts_value_t gatts_value = {0};
    
    gatts_value.len     = BLE_CCCD_VALUE_LEN;
    gatts_value.offset  = 0;
    gatts_value.p_value = (uint8_t*)p_tag_status_activity_record_count;
        
    err_code = sd_ble_gatts_value_get 
    (
        nrf51_tag_status_activity_record_count_value_handle(), 
        0, 
        &gatts_value
    );
    
    APP_ERROR_CHECK(err_code);
}

/** @brief
*
*/
void nrf51_tag_status_activity_read_records_set(ble_tag_status_activity_read_records_t* p_tag_status_activity_read_records)
{
    uint32_t err_code = NRF_SUCCESS;
    
    ble_gatts_value_t gatts_value = {0};
    
    gatts_value.len     = BLE_CCCD_VALUE_LEN;
    gatts_value.offset  = 0;
    gatts_value.p_value = (uint8_t*)p_tag_status_activity_read_records;
        
    err_code = sd_ble_gatts_value_set 
    (
        nrf51_tag_status_activity_read_records_value_handle(), 
        0, 
        &gatts_value
    );
    
    APP_ERROR_CHECK(err_code);
}

/** @brief
*
*/
void nrf51_tag_status_activity_read_records_get(ble_tag_status_activity_read_records_t* p_tag_status_activity_read_records)
{
    uint32_t err_code = NRF_SUCCESS;

    ble_gatts_value_t gatts_value = {0};
    
    gatts_value.len     = BLE_CCCD_VALUE_LEN;
    gatts_value.offset  = 0;
    gatts_value.p_value = (uint8_t*)p_tag_status_activity_read_records;
        
    err_code = sd_ble_gatts_value_get 
    (
        nrf51_tag_status_activity_read_records_value_handle(), 
        0, 
        &gatts_value
    );
    
    APP_ERROR_CHECK(err_code);
}
