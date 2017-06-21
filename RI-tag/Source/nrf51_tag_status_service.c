/**
* @file nrf51_tag_status_service.c
* @brief Source file for the Tag Status Service.
*
*/

#include "nrf51_tag_error.h"
#include "nrf51_tag_headers.h"

//-------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------

static ble_tag_status_service_t s_ble_tag_status_service = {0};

//-------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------

/** @brief Initialises the Tag Status Service / Characteristics
 */
void nrf51_tag_status_service_initialize(void)
{
    uint32_t err_code = NRF_SUCCESS;
    
    // -----------------------------------
    // Initialize Service Structure Values
    // -----------------------------------
    
    // Add UUID Base
    // Note: Populates the uuid_type field
    //
    ble_uuid128_t base_uuid = BLE_UUID_TAG_STATUS_BASE;
    
    err_code = sd_ble_uuid_vs_add(&base_uuid, &s_ble_tag_status_service.uuid_type);
    APP_ERROR_CHECK(err_code);

    // Add Service ID
    // Note: Populates the service_handle field
    //
    ble_uuid_t ble_uuid = {0};
    
    ble_uuid.type = s_ble_tag_status_service.uuid_type;
    ble_uuid.uuid = BLE_UUID_TAG_STATUS_SERVICE;

    err_code = sd_ble_gatts_service_add
    (
        BLE_GATTS_SRVC_TYPE_PRIMARY, 
        &ble_uuid, 
        &s_ble_tag_status_service.service_handle
    );
    
    APP_ERROR_CHECK(err_code);
    
    // ------------------------------------------------------------------------
    // Tag Status Characteristics
    // ------------------------------------------------------------------------

    // Add Tag Status Uptime Characteristic
    //
    void nrf51_tag_status_uptime_char_add(ble_tag_status_service_t* p_tag_status_service);
    nrf51_tag_status_uptime_char_add(&s_ble_tag_status_service);

    // Add Tag Status Temperature Characteristic
    //
    void nrf51_tag_status_temperature_char_add(ble_tag_status_service_t* p_tag_status_service);
    nrf51_tag_status_temperature_char_add(&s_ble_tag_status_service);

    // Add Tag Status Battery Level Characteristic
    //
    void nrf51_tag_status_battery_level_char_add(ble_tag_status_service_t* p_tag_status_service);
    nrf51_tag_status_battery_level_char_add(&s_ble_tag_status_service);

    // Add Tag Status Firmware Revision Characteristic
    //
    void nrf51_tag_status_firmware_revision_char_add(ble_tag_status_service_t* p_tag_status_service);
    nrf51_tag_status_firmware_revision_char_add(&s_ble_tag_status_service);

    // Add Tag Status Activity Record Count Characteristic
    //
    void nrf51_tag_status_activity_record_count_char_add(ble_tag_status_service_t* p_tag_status_service);
    nrf51_tag_status_activity_record_count_char_add(&s_ble_tag_status_service);
    
    // Add Tag Status Activity Read Records Characteristic
    //
    void nrf51_tag_status_activity_read_records_char_add(ble_tag_status_service_t* p_tag_status_service);
    nrf51_tag_status_activity_read_records_char_add(&s_ble_tag_status_service);

    // Add Tag Status Diagnostics Characteristic
    //
    void nrf51_tag_status_diagnostics_char_add(ble_tag_status_service_t* p_tag_status_service);
    nrf51_tag_status_diagnostics_char_add(&s_ble_tag_status_service);

    // Add Tag Status Serial Number Characteristic
    //
    void nrf51_tag_status_serial_number_char_add(ble_tag_status_service_t* p_tag_status_service);
    nrf51_tag_status_serial_number_char_add(&s_ble_tag_status_service);

    // Add Tag Status Buzzer Characteristic
    //
    void nrf51_tag_status_buzzer_char_add(ble_tag_status_service_t* p_tag_status_service);
    nrf51_tag_status_buzzer_char_add(&s_ble_tag_status_service);
}

//-------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------

/** @brief
 */
uint16_t nrf51_tag_status_uptime_value_handle(void)
{
    return s_ble_tag_status_service.tag_status_uptime_char_handles.value_handle;
}

/** @brief
 */
uint16_t nrf51_tag_status_uptime_cccd_handle(void)
{
    return s_ble_tag_status_service.tag_status_uptime_char_handles.cccd_handle;
}

/** @brief
 */
uint16_t nrf51_tag_status_temperature_value_handle(void)
{
    return s_ble_tag_status_service.tag_status_temperature_char_handles.value_handle;
}

/** @brief
 */
uint16_t nrf51_tag_status_temperature_cccd_handle(void)
{
    return s_ble_tag_status_service.tag_status_temperature_char_handles.cccd_handle;
}

/** @brief
 */
uint16_t nrf51_tag_status_battery_level_value_handle(void)
{
    return s_ble_tag_status_service.tag_status_battery_level_char_handles.value_handle;
}

/** @brief
 */
uint16_t nrf51_tag_status_battery_level_cccd_handle(void)
{
    return s_ble_tag_status_service.tag_status_battery_level_char_handles.cccd_handle;
}

/** @brief
 */
uint16_t nrf51_tag_status_firmware_revision_value_handle(void)
{
    return s_ble_tag_status_service.tag_status_firmware_revision_char_handles.value_handle;
}

/** @brief
 */
uint16_t nrf51_tag_firmware_revision_cccd_handle(void)
{
    return s_ble_tag_status_service.tag_status_firmware_revision_char_handles.cccd_handle;
}

#if 0
/** @brief
 */
uint16_t nrf51_tag_status_beacon_record_count_value_handle(void)
{
    return s_ble_tag_status_service.tag_status_beacon_record_count_char_handles.value_handle;
}

/** @brief
 */
uint16_t nrf51_tag_beacon_record_count_cccd_handle(void)
{
    return s_ble_tag_status_service.tag_status_beacon_record_count_char_handles.cccd_handle;
}

/** @brief
 */
uint16_t nrf51_tag_status_beacon_read_records_value_handle(void)
{
    return s_ble_tag_status_service.tag_status_beacon_read_records_char_handles.value_handle;
}

/** @brief
 */
uint16_t nrf51_tag_beacon_read_records_cccd_handle(void)
{
    return s_ble_tag_status_service.tag_status_beacon_read_records_char_handles.cccd_handle;
}
#endif

/** @brief
 */
uint16_t nrf51_tag_status_activity_record_count_value_handle(void)
{
    return s_ble_tag_status_service.tag_status_activity_record_count_char_handles.value_handle;
}

/** @brief
 */
uint16_t nrf51_tag_activity_record_count_cccd_handle(void)
{
    return s_ble_tag_status_service.tag_status_activity_record_count_char_handles.cccd_handle;
}

/** @brief
 */
uint16_t nrf51_tag_status_activity_read_records_value_handle(void)
{
    return s_ble_tag_status_service.tag_status_activity_read_records_char_handles.value_handle;
}

/** @brief
 */
uint16_t nrf51_tag_activity_read_records_cccd_handle(void)
{
    return s_ble_tag_status_service.tag_status_activity_read_records_char_handles.cccd_handle;
}

/** @brief
 */
uint16_t nrf51_tag_status_diagnostics_value_handle(void)
{
    return s_ble_tag_status_service.tag_status_diagnostics_char_handles.value_handle;
}

/** @brief
 */
uint16_t nrf51_tag_diagnostics_cccd_handle(void)
{
    return s_ble_tag_status_service.tag_status_diagnostics_char_handles.cccd_handle;
}

/** @brief
 */
uint16_t nrf51_tag_status_serial_number_value_handle(void)
{
    return s_ble_tag_status_service.tag_status_serial_number_char_handles.value_handle;
}

/** @brief
 */
uint16_t nrf51_tag_serial_number_cccd_handle(void)
{
    return s_ble_tag_status_service.tag_status_serial_number_char_handles.cccd_handle;
}

/** @brief
 */
uint16_t nrf51_tag_status_buzzer_value_handle(void)
{
    return s_ble_tag_status_service.tag_status_buzzer_char_handles.value_handle;
}

/** @brief
 */
uint16_t nrf51_tag_buzzer_cccd_handle(void)
{
    return s_ble_tag_status_service.tag_status_buzzer_char_handles.cccd_handle;
}
