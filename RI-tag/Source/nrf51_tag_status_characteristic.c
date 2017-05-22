/**
* @file nrf51_tag_status_characteristic.c
* @brief Source file for the Tag Status Characteristic.
*
*/

#include "nrf51_tag_error.h"
#include "nrf51_tag_headers.h"

/**@brief Add Tag Status Uptime Characteristic to the Service.
*/
void nrf51_tag_status_uptime_char_add(ble_tag_status_service_t* p_tag_status_service)
{
    uint32_t err_code = NRF_SUCCESS;

    // Client Characteristic Configuration Descriptor
    //
    ble_gatts_attr_md_t cccd_md = {0};

    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&cccd_md.read_perm);
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&cccd_md.write_perm);
    
    cccd_md.vloc = BLE_GATTS_VLOC_STACK;

    // Characteristic Meta Data
    //
    ble_gatts_char_md_t char_md = {0};
    
    char_md.char_props.write = 0;
    char_md.char_props.read  = 1;
    
    char_md.p_cccd_md = &cccd_md;
    
    // Characteristic UUID Configuration
    //
    ble_uuid_t ble_uuid = {0};
    
    ble_uuid.type = p_tag_status_service->uuid_type;
    ble_uuid.uuid = BLE_UUID_TAG_STATUS_UPTIME_CHAR;

    // Attribute Meta Data
    //
    ble_gatts_attr_md_t attr_md = {0};
    
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.read_perm);
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.write_perm);

    attr_md.vloc = BLE_GATTS_VLOC_STACK;
    
    attr_md.rd_auth = 1;
    attr_md.wr_auth = 0;
    
    attr_md.vlen = 0;

    // Attribute / Value Configuration
    //
    ble_gatts_attr_t attr_char_value = {0};
    
    ble_tag_status_uptime_t tag_status_uptime = {0};

    attr_char_value.p_uuid    = &ble_uuid;
    attr_char_value.p_attr_md = &attr_md;
    attr_char_value.init_len  = sizeof(tag_status_uptime);
    attr_char_value.init_offs = 0;
    attr_char_value.max_len   = sizeof(tag_status_uptime);
    attr_char_value.p_value   = (uint8_t*)&tag_status_uptime;
    
    // Add Tag Status Characteristic
    // Note: Populates the tag_status_cmd_char_handles field 
    //
    err_code = sd_ble_gatts_characteristic_add
    (
        p_tag_status_service->service_handle, 
        &char_md,
        &attr_char_value,
        &p_tag_status_service->tag_status_uptime_char_handles
    );
    
    APP_ERROR_CHECK(err_code);
}

/**@brief Add Tag Status Temperature Characteristic to the Service.
*/
void nrf51_tag_status_temperature_char_add(ble_tag_status_service_t* p_tag_status_service)
{
    uint32_t err_code = NRF_SUCCESS;

    // Client Characteristic Configuration Descriptor
    //
    ble_gatts_attr_md_t cccd_md = {0};

    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&cccd_md.read_perm);
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&cccd_md.write_perm);
    
    cccd_md.vloc = BLE_GATTS_VLOC_STACK;

    // Characteristic Meta Data
    //
    ble_gatts_char_md_t char_md = {0};
    
    char_md.char_props.write = 0;
    char_md.char_props.read  = 1;
    
    char_md.p_cccd_md = &cccd_md;
    
    // Characteristic UUID Configuration
    //
    ble_uuid_t ble_uuid = {0};
    
    ble_uuid.type = p_tag_status_service->uuid_type;
    ble_uuid.uuid = BLE_UUID_TAG_STATUS_TEMPERATURE_CHAR;

    // Attribute Meta Data
    //
    ble_gatts_attr_md_t attr_md = {0};
    
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.read_perm);
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.write_perm);

    attr_md.vloc = BLE_GATTS_VLOC_STACK;
    
    attr_md.rd_auth = 1;
    attr_md.wr_auth = 0;
    
    attr_md.vlen = 0;

    // Attribute / Value Configuration
    //
    ble_gatts_attr_t attr_char_value = {0};
    
    ble_tag_status_temperature_t tag_status_temperature = {0};

    attr_char_value.p_uuid    = &ble_uuid;
    attr_char_value.p_attr_md = &attr_md;
    attr_char_value.init_len  = sizeof(tag_status_temperature);
    attr_char_value.init_offs = 0;
    attr_char_value.max_len   = sizeof(tag_status_temperature);
    attr_char_value.p_value   = (uint8_t*)&tag_status_temperature;
    
    // Add Tag Status Characteristic
    // Note: Populates the tag_status_cmd_char_handles field 
    //
    err_code = sd_ble_gatts_characteristic_add
    (
        p_tag_status_service->service_handle, 
        &char_md,
        &attr_char_value,
        &p_tag_status_service->tag_status_temperature_char_handles
    );
    
    APP_ERROR_CHECK(err_code);
}

/**@brief Add Tag Status Battery Level Characteristic to the Service.
*/
void nrf51_tag_status_battery_level_char_add(ble_tag_status_service_t* p_tag_status_service)
{
    uint32_t err_code = NRF_SUCCESS;

    // Client Characteristic Configuration Descriptor
    //
    ble_gatts_attr_md_t cccd_md = {0};

    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&cccd_md.read_perm);
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&cccd_md.write_perm);
    
    cccd_md.vloc = BLE_GATTS_VLOC_STACK;

    // Characteristic Meta Data
    //
    ble_gatts_char_md_t char_md = {0};
    
    char_md.char_props.write = 0;
    char_md.char_props.read  = 1;
    
    char_md.p_cccd_md = &cccd_md;
    
    // Characteristic UUID Configuration
    //
    ble_uuid_t ble_uuid = {0};
    
    ble_uuid.type = p_tag_status_service->uuid_type;
    ble_uuid.uuid = BLE_UUID_TAG_STATUS_BATTERY_LEVEL_CHAR;

    // Attribute Meta Data
    //
    ble_gatts_attr_md_t attr_md = {0};
    
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.read_perm);
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.write_perm);

    attr_md.vloc = BLE_GATTS_VLOC_STACK;
    
    attr_md.rd_auth = 1;
    attr_md.wr_auth = 0;
    
    attr_md.vlen = 0;

    // Attribute / Value Configuration
    //
    ble_gatts_attr_t attr_char_value = {0};
    
    ble_tag_status_battery_level_t tag_status_battery_level = {0};

    attr_char_value.p_uuid    = &ble_uuid;
    attr_char_value.p_attr_md = &attr_md;
    attr_char_value.init_len  = sizeof(tag_status_battery_level);
    attr_char_value.init_offs = 0;
    attr_char_value.max_len   = sizeof(tag_status_battery_level);
    attr_char_value.p_value   = (uint8_t*)&tag_status_battery_level;
    
    // Add Tag Status Characteristic
    // Note: Populates the tag_status_cmd_char_handles field 
    //
    err_code = sd_ble_gatts_characteristic_add
    (
        p_tag_status_service->service_handle, 
        &char_md,
        &attr_char_value,
        &p_tag_status_service->tag_status_battery_level_char_handles
    );
    
    APP_ERROR_CHECK(err_code);
}

/**@brief Add Tag Status Firmware Revision Characteristic to the Service.
*/
void nrf51_tag_status_firmware_revision_char_add(ble_tag_status_service_t* p_tag_status_service)
{
    uint32_t err_code = NRF_SUCCESS;

    // Client Characteristic Configuration Descriptor
    //
    ble_gatts_attr_md_t cccd_md = {0};

    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&cccd_md.read_perm);
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&cccd_md.write_perm);
    
    cccd_md.vloc = BLE_GATTS_VLOC_STACK;

    // Characteristic Meta Data
    //
    ble_gatts_char_md_t char_md = {0};
    
    char_md.char_props.write = 0;
    char_md.char_props.read  = 1;
    
    char_md.p_cccd_md = &cccd_md;
    
    // Characteristic UUID Configuration
    //
    ble_uuid_t ble_uuid = {0};
    
    ble_uuid.type = p_tag_status_service->uuid_type;
    ble_uuid.uuid = BLE_UUID_TAG_STATUS_FIRMWARE_REVISION_CHAR;

    // Attribute Meta Data
    //
    ble_gatts_attr_md_t attr_md = {0};
    
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.read_perm);
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.write_perm);

    attr_md.vloc = BLE_GATTS_VLOC_STACK;
    
    attr_md.rd_auth = 1;
    attr_md.wr_auth = 0;
    
    attr_md.vlen = 0;

    // Attribute / Value Configuration
    //
    ble_gatts_attr_t attr_char_value = {0};
    
    ble_tag_status_firmware_revision_t tag_status_firmware_revision = {0};

    attr_char_value.p_uuid    = &ble_uuid;
    attr_char_value.p_attr_md = &attr_md;
    attr_char_value.init_len  = sizeof(tag_status_firmware_revision);
    attr_char_value.init_offs = 0;
    attr_char_value.max_len   = sizeof(tag_status_firmware_revision);
    attr_char_value.p_value   = (uint8_t*)&tag_status_firmware_revision;
    
    // Add Tag Status Characteristic
    // Note: Populates the tag_status_cmd_char_handles field 
    //
    err_code = sd_ble_gatts_characteristic_add
    (
        p_tag_status_service->service_handle, 
        &char_md,
        &attr_char_value,
        &p_tag_status_service->tag_status_firmware_revision_char_handles
    );
    
    APP_ERROR_CHECK(err_code);
}

/**@brief Add Tag Status Activity Record Count Characteristic to the Service.
*/
void nrf51_tag_status_activity_record_count_char_add(ble_tag_status_service_t* p_tag_status_service)
{
    uint32_t err_code = NRF_SUCCESS;

    // Client Characteristic Configuration Descriptor
    //
    ble_gatts_attr_md_t cccd_md = {0};

    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&cccd_md.read_perm);
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&cccd_md.write_perm);
    
    cccd_md.vloc = BLE_GATTS_VLOC_STACK;

    // Characteristic Meta Data
    //
    ble_gatts_char_md_t char_md = {0};
    
    char_md.char_props.write = 0;
    char_md.char_props.read  = 1;
    
    char_md.p_cccd_md = &cccd_md;
    
    // Characteristic UUID Configuration
    //
    ble_uuid_t ble_uuid = {0};
    
    ble_uuid.type = p_tag_status_service->uuid_type;
    ble_uuid.uuid = BLE_UUID_TAG_STATUS_ACTIVITY_RECORD_COUNT_CHAR;

    // Attribute Meta Data
    //
    ble_gatts_attr_md_t attr_md = {0};
    
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.read_perm);
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.write_perm);

    attr_md.vloc = BLE_GATTS_VLOC_STACK;
    
    attr_md.rd_auth = 1;
    attr_md.wr_auth = 0;
    
    attr_md.vlen = 0;

    // Attribute / Value Configuration
    //
    ble_gatts_attr_t attr_char_value = {0};
    
    ble_tag_status_activity_record_count_t tag_status_activity_record_count = {0};

    attr_char_value.p_uuid    = &ble_uuid;
    attr_char_value.p_attr_md = &attr_md;
    attr_char_value.init_len  = sizeof(tag_status_activity_record_count);
    attr_char_value.init_offs = 0;
    attr_char_value.max_len   = sizeof(tag_status_activity_record_count);
    attr_char_value.p_value   = (uint8_t*)&tag_status_activity_record_count;
    
    // Add Tag Status Characteristic
    // Note: Populates the tag_status_cmd_char_handles field 
    //
    err_code = sd_ble_gatts_characteristic_add
    (
        p_tag_status_service->service_handle, 
        &char_md,
        &attr_char_value,
        &p_tag_status_service->tag_status_activity_record_count_char_handles
    );
    
    APP_ERROR_CHECK(err_code);
}

/**@brief Add Tag Status Activity Read Records Characteristic to the Service.
*/
void nrf51_tag_status_activity_read_records_char_add(ble_tag_status_service_t* p_tag_status_service)
{
    uint32_t err_code = NRF_SUCCESS;

    // Client Characteristic Configuration Descriptor
    //
    ble_gatts_attr_md_t cccd_md = {0};

    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&cccd_md.read_perm);
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&cccd_md.write_perm);
    
    cccd_md.vloc = BLE_GATTS_VLOC_STACK;

    // Characteristic Meta Data
    //
    ble_gatts_char_md_t char_md = {0};
    
    char_md.char_props.write = 0;
    char_md.char_props.read  = 1;
    
    char_md.p_cccd_md = &cccd_md;
    
    // Characteristic UUID Configuration
    //
    ble_uuid_t ble_uuid = {0};
    
    ble_uuid.type = p_tag_status_service->uuid_type;
    ble_uuid.uuid = BLE_UUID_TAG_STATUS_ACTIVITY_READ_RECORDS_CHAR;

    // Attribute Meta Data
    //
    ble_gatts_attr_md_t attr_md = {0};
    
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.read_perm);
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.write_perm);

    attr_md.vloc = BLE_GATTS_VLOC_STACK;
    
    attr_md.rd_auth = 1;
    attr_md.wr_auth = 0;
    
    attr_md.vlen = 0;

    // Attribute / Value Configuration
    //
    ble_gatts_attr_t attr_char_value = {0};
    
    //ble_tag_status_activity_read_records_t tag_status_activity_read_records = {0};

    attr_char_value.p_uuid    = &ble_uuid;
    attr_char_value.p_attr_md = &attr_md;
    attr_char_value.init_len  = nrf51_tag_update_gateway_data_length();
    attr_char_value.init_offs = 0;
    attr_char_value.max_len   = nrf51_tag_update_gateway_data_length();
    attr_char_value.p_value   = nrf51_tag_update_gateway_data_ptr();
    
    // Add Tag Status Characteristic
    // Note: Populates the tag_status_cmd_char_handles field 
    //
    err_code = sd_ble_gatts_characteristic_add
    (
        p_tag_status_service->service_handle, 
        &char_md,
        &attr_char_value,
        &p_tag_status_service->tag_status_activity_read_records_char_handles
    );
    
    APP_ERROR_CHECK(err_code);
}

/**@brief Add Tag Status Diagnostics Characteristic to the Service.
*/
void nrf51_tag_status_diagnostics_char_add(ble_tag_status_service_t* p_tag_status_service)
{
    uint32_t err_code = NRF_SUCCESS;

    // Client Characteristic Configuration Descriptor
    //
    ble_gatts_attr_md_t cccd_md = {0};

    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&cccd_md.read_perm);
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&cccd_md.write_perm);
    
    cccd_md.vloc = BLE_GATTS_VLOC_STACK;

    // Characteristic Meta Data
    //
    ble_gatts_char_md_t char_md = {0};
    
    char_md.char_props.write = 0;
    char_md.char_props.read  = 1;
    
    char_md.p_cccd_md = &cccd_md;
    
    // Characteristic UUID Configuration
    //
    ble_uuid_t ble_uuid = {0};
    
    ble_uuid.type = p_tag_status_service->uuid_type;
    ble_uuid.uuid = BLE_UUID_TAG_STATUS_DIAGNOSTICS_CHAR;

    // Attribute Meta Data
    //
    ble_gatts_attr_md_t attr_md = {0};
    
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.read_perm);
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.write_perm);

    attr_md.vloc = BLE_GATTS_VLOC_STACK;
    
    attr_md.rd_auth = 1;
    attr_md.wr_auth = 0;
    
    attr_md.vlen = 0;

    // Attribute / Value Configuration
    //
    ble_gatts_attr_t attr_char_value = {0};
    
    ble_tag_status_diagnostics_t tag_status_diagnostics = {0};

    attr_char_value.p_uuid    = &ble_uuid;
    attr_char_value.p_attr_md = &attr_md;
    attr_char_value.init_len  = sizeof(tag_status_diagnostics);
    attr_char_value.init_offs = 0;
    attr_char_value.max_len   = sizeof(tag_status_diagnostics);
    attr_char_value.p_value   = (uint8_t*)&tag_status_diagnostics;
    
    // Add Tag Status Characteristic
    // Note: Populates the tag_status_cmd_char_handles field 
    //
    err_code = sd_ble_gatts_characteristic_add
    (
        p_tag_status_service->service_handle, 
        &char_md,
        &attr_char_value,
        &p_tag_status_service->tag_status_diagnostics_char_handles
    );
    
    APP_ERROR_CHECK(err_code);
}
