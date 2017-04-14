/**
* @file nrf51_tag_configuration_service.c
* @brief Source file for the Tag Configuration Service.
*
*/

#include "nrf51_tag_error.h"
#include "nrf51_tag_headers.h"

//-------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------

static ble_tag_configuration_service_t s_ble_tag_configuration_service = {0};

//-------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------

/** @brief Initialises the Tag Configuration Service / Characteristics
 */
void nrf51_tag_configuration_service_initialize(void)
{
    uint32_t err_code = NRF_SUCCESS;
    
    // -----------------------------------
    // Initialize Service Structure Values
    // -----------------------------------
    
    // Add UUID Base
    // Note: Populates the uuid_type field
    //
    ble_uuid128_t base_uuid = BLE_UUID_TAG_CONFIGURATION_BASE;
    
    err_code = sd_ble_uuid_vs_add(&base_uuid, &s_ble_tag_configuration_service.uuid_type);
    APP_ERROR_CHECK(err_code);

    // Add Service ID
    // Note: Populates the service_handle field
    //
    ble_uuid_t ble_uuid = {0};
    
    ble_uuid.type = s_ble_tag_configuration_service.uuid_type;
    ble_uuid.uuid = BLE_UUID_TAG_CONFIGURATION_SERVICE;

    err_code = sd_ble_gatts_service_add
    (
        BLE_GATTS_SRVC_TYPE_PRIMARY, 
        &ble_uuid, 
        &s_ble_tag_configuration_service.service_handle
    );
    
    APP_ERROR_CHECK(err_code);
    
    // ------------------------------------------------------------------------
    // Tag Configuration Characteristics
    // ------------------------------------------------------------------------

    // Add Tag Configuration Sample Rate Characteristic
    //
    void nrf51_tag_configuration_sample_rate_char_add(ble_tag_configuration_service_t* p_tag_configuration_service);
    nrf51_tag_configuration_sample_rate_char_add(&s_ble_tag_configuration_service);

    // Add Tag Configuration Serial Number Characteristic
    //
    void nrf51_tag_configuration_serial_number_char_add(ble_tag_configuration_service_t* p_tag_configuration_service);
    nrf51_tag_configuration_serial_number_char_add(&s_ble_tag_configuration_service);
}

//-------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------

/** @brief
 */
uint16_t nrf51_tag_configuration_sample_rate_value_handle(void)
{
    return s_ble_tag_configuration_service.tag_configuration_sample_rate_char_handles.value_handle;
}

/** @brief
 */
uint16_t nrf51_tag_configuration_sample_rate_cccd_handle(void)
{
    return s_ble_tag_configuration_service.tag_configuration_sample_rate_char_handles.cccd_handle;
}

/** @brief
 */
uint16_t nrf51_tag_configuration_serial_number_value_handle(void)
{
    return s_ble_tag_configuration_service.tag_configuration_serial_number_char_handles.value_handle;
}

/** @brief
 */
uint16_t nrf51_tag_configuration_serial_number_cccd_handle(void)
{
    return s_ble_tag_configuration_service.tag_configuration_serial_number_char_handles.cccd_handle;
}
