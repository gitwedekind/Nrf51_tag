/**
* @file nrf51_tag_activity_log_service.c
* @brief Source file for the Tag Activity Log Service.
*
*/

#include "nrf51_tag_error.h"
#include "nrf51_tag_headers.h"

//-------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------

static ble_tag_activity_log_service_t s_ble_tag_activity_log_service = {0};

//-------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------

/** @brief Initialises the Tag Activity Log Service / Characteristics
 */
void nrf51_tag_activity_log_service_initialize(void)
{
    uint32_t err_code = NRF_SUCCESS;
    
    // -----------------------------------
    // Initialize Service Structure Values
    // -----------------------------------
    
    // Add UUID Base
    // Note: Populates the uuid_type field
    //
    ble_uuid128_t base_uuid = BLE_UUID_TAG_ACTIVITY_LOG_BASE;
    
    err_code = sd_ble_uuid_vs_add(&base_uuid, &s_ble_tag_activity_log_service.uuid_type);
    APP_ERROR_CHECK(err_code);

    // Add Service ID
    // Note: Populates the service_handle field
    //
    ble_uuid_t ble_uuid = {0};
    
    ble_uuid.type = s_ble_tag_activity_log_service.uuid_type;
    ble_uuid.uuid = BLE_UUID_TAG_ACTIVITY_LOG_SERVICE;

    err_code = sd_ble_gatts_service_add
    (
        BLE_GATTS_SRVC_TYPE_PRIMARY, 
        &ble_uuid, 
        &s_ble_tag_activity_log_service.service_handle
    );
    
    APP_ERROR_CHECK(err_code);
    
    // ------------------------------------------------------------------------
    // Tag Activity Log Characteristics
    // ------------------------------------------------------------------------

    // Add Tag Activity Log Record Size Characteristic
    //
    void nrf51_tag_activity_log_record_size_char_add(ble_tag_activity_log_service_t* p_tag_activity_log_service);
    nrf51_tag_activity_log_record_size_char_add(&s_ble_tag_activity_log_service);

    // Add Tag Activity Log Record Count Characteristic
    //
    void nrf51_tag_activity_log_record_count_char_add(ble_tag_activity_log_service_t* p_tag_activity_log_service);
    nrf51_tag_activity_log_record_count_char_add(&s_ble_tag_activity_log_service);

    // Add Tag Activity Log Read Records Count Characteristic
    //
    void nrf51_tag_activity_log_read_records_count_char_add(ble_tag_activity_log_service_t* p_tag_activity_log_service);
    nrf51_tag_activity_log_read_records_count_char_add(&s_ble_tag_activity_log_service);

    // Add Tag Activity Log Read Records Characteristic
    //
    void nrf51_tag_activity_log_read_records_char_add(ble_tag_activity_log_service_t* p_tag_activity_log_service);
    nrf51_tag_activity_log_read_records_char_add(&s_ble_tag_activity_log_service);

    // Add Tag Activity Log Create Records Characteristic
    //
    void nrf51_tag_activity_log_create_records_char_add(ble_tag_activity_log_service_t* p_tag_activity_log_service);
    nrf51_tag_activity_log_create_records_char_add(&s_ble_tag_activity_log_service);
}

//-------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------

/** @brief
 */
uint16_t nrf51_tag_activity_log_record_size_value_handle(void)
{
    return s_ble_tag_activity_log_service.tag_activity_log_record_size_char_handles.value_handle;
}

/** @brief
 */
uint16_t nrf51_tag_activity_log_record_size_cccd_handle(void)
{
    return s_ble_tag_activity_log_service.tag_activity_log_record_size_char_handles.cccd_handle;
}

/** @brief
 */
uint16_t nrf51_tag_activity_log_record_count_value_handle(void)
{
    return s_ble_tag_activity_log_service.tag_activity_log_record_count_char_handles.value_handle;
}

/** @brief
 */
uint16_t nrf51_tag_activity_log_record_count_cccd_handle(void)
{
    return s_ble_tag_activity_log_service.tag_activity_log_record_count_char_handles.cccd_handle;
}

/** @brief
 */
uint16_t nrf51_tag_activity_log_read_records_count_value_handle(void)
{
    return s_ble_tag_activity_log_service.tag_activity_log_read_records_count_char_handles.value_handle;
}

/** @brief
 */
uint16_t nrf51_tag_activity_log_read_records_count_cccd_handle(void)
{
    return s_ble_tag_activity_log_service.tag_activity_log_read_records_count_char_handles.cccd_handle;
}

/** @brief
 */
uint16_t nrf51_tag_activity_log_read_records_value_handle(void)
{
    return s_ble_tag_activity_log_service.tag_activity_log_read_records_char_handles.value_handle;
}

/** @brief
 */
uint16_t nrf51_tag_activity_log_read_records_cccd_handle(void)
{
    return s_ble_tag_activity_log_service.tag_activity_log_read_records_char_handles.cccd_handle;
}

/** @brief
 */
uint16_t nrf51_tag_activity_log_create_records_value_handle(void)
{
    return s_ble_tag_activity_log_service.tag_activity_log_create_records_char_handles.value_handle;
}

/** @brief
 */
uint16_t nrf51_tag_activity_log_create_records_cccd_handle(void)
{
    return s_ble_tag_activity_log_service.tag_activity_log_create_records_char_handles.cccd_handle;
}
