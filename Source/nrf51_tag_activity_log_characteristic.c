/**
* @file nrf51_tag_activity_log_characteristic.c
* @brief Source file for the Tag Activity Log Characteristic.
*
*/

#include "nrf51_tag_error.h"
#include "nrf51_tag_headers.h"

/**@brief Add Tag Activity Log Record Size Characteristic to the Service.
*/
void nrf51_tag_activity_log_record_size_char_add(ble_tag_activity_log_service_t* p_tag_activity_log_service)
{
    uint32_t err_code = NRF_SUCCESS;

    // Client Characteristic Activity Log Descriptor
    //
    ble_gatts_attr_md_t cccd_md = {0};

    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&cccd_md.read_perm);
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&cccd_md.write_perm);
    
    cccd_md.vloc = BLE_GATTS_VLOC_STACK;

    // Characteristic Meta Data
    //
    ble_gatts_char_md_t char_md = {0};
    
    char_md.char_props.write = 1;
    char_md.char_props.read  = 1;
    
    char_md.p_cccd_md = &cccd_md;
    
    // Characteristic UUID Activity Log
    //
    ble_uuid_t ble_uuid = {0};
    
    ble_uuid.type = p_tag_activity_log_service->uuid_type;
    ble_uuid.uuid = BLE_UUID_TAG_ACTIVITY_LOG_RECORD_SIZE_CHAR;

    // Attribute Meta Data
    //
    ble_gatts_attr_md_t attr_md = {0};
    
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.read_perm);
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.write_perm);

    attr_md.vloc = BLE_GATTS_VLOC_STACK;
    
    attr_md.rd_auth = 1;
    attr_md.wr_auth = 0;
    
    attr_md.vlen = 0;

    // Attribute / Value Activity Log
    //
    ble_gatts_attr_t attr_char_value = {0};
    
    ble_tag_activity_log_record_size_t tag_activity_log_record_size = {0};

    attr_char_value.p_uuid    = &ble_uuid;
    attr_char_value.p_attr_md = &attr_md;
    attr_char_value.init_len  = sizeof(tag_activity_log_record_size);
    attr_char_value.init_offs = 0;
    attr_char_value.max_len   = sizeof(tag_activity_log_record_size);
    attr_char_value.p_value   = (uint8_t*)&tag_activity_log_record_size;
    
    // Add Tag Activity Log Record Size Characteristic
    //
    err_code = sd_ble_gatts_characteristic_add
    (
        p_tag_activity_log_service->service_handle, 
        &char_md,
        &attr_char_value,
        &p_tag_activity_log_service->tag_activity_log_record_size_char_handles
    );
    
    APP_ERROR_CHECK(err_code);
}

/**@brief Add Tag Activity Log Record Count Characteristic to the Service.
*/
void nrf51_tag_activity_log_record_count_char_add(ble_tag_activity_log_service_t* p_tag_activity_log_service)
{
    uint32_t err_code = NRF_SUCCESS;

    // Client Characteristic Activity Log Descriptor
    //
    ble_gatts_attr_md_t cccd_md = {0};

    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&cccd_md.read_perm);
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&cccd_md.write_perm);
    
    cccd_md.vloc = BLE_GATTS_VLOC_STACK;

    // Characteristic Meta Data
    //
    ble_gatts_char_md_t char_md = {0};
    
    char_md.char_props.write = 1;
    char_md.char_props.read  = 1;
    
    char_md.p_cccd_md = &cccd_md;
    
    // Characteristic UUID Activity Log
    //
    ble_uuid_t ble_uuid = {0};
    
    ble_uuid.type = p_tag_activity_log_service->uuid_type;
    ble_uuid.uuid = BLE_UUID_TAG_ACTIVITY_LOG_RECORD_COUNT_CHAR;

    // Attribute Meta Data
    //
    ble_gatts_attr_md_t attr_md = {0};
    
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.read_perm);
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.write_perm);

    attr_md.vloc = BLE_GATTS_VLOC_STACK;
    
    attr_md.rd_auth = 1;
    attr_md.wr_auth = 0;
    
    attr_md.vlen = 0;

    // Attribute / Value Activity Log
    //
    ble_gatts_attr_t attr_char_value = {0};
    
    ble_tag_activity_log_record_count_t tag_activity_log_record_count = {0};

    attr_char_value.p_uuid    = &ble_uuid;
    attr_char_value.p_attr_md = &attr_md;
    attr_char_value.init_len  = sizeof(tag_activity_log_record_count);
    attr_char_value.init_offs = 0;
    attr_char_value.max_len   = sizeof(tag_activity_log_record_count);
    attr_char_value.p_value   = (uint8_t*)&tag_activity_log_record_count;
    
    // Add Tag Activity Log Record Count Characteristic
    //
    err_code = sd_ble_gatts_characteristic_add
    (
        p_tag_activity_log_service->service_handle, 
        &char_md,
        &attr_char_value,
        &p_tag_activity_log_service->tag_activity_log_record_count_char_handles
    );
    
    APP_ERROR_CHECK(err_code);
}

/**@brief Add Tag Activity Log Read Records Count Characteristic to the Service.
*/
void nrf51_tag_activity_log_read_records_count_char_add(ble_tag_activity_log_service_t* p_tag_activity_log_service)
{
    uint32_t err_code = NRF_SUCCESS;

    // Client Characteristic Activity Log Descriptor
    //
    ble_gatts_attr_md_t cccd_md = {0};

    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&cccd_md.read_perm);
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&cccd_md.write_perm);
    
    cccd_md.vloc = BLE_GATTS_VLOC_STACK;

    // Characteristic Meta Data
    //
    ble_gatts_char_md_t char_md = {0};
    
    char_md.char_props.write = 1;
    char_md.char_props.read  = 1;
    
    char_md.p_cccd_md = &cccd_md;
    
    // Characteristic UUID Activity Log
    //
    ble_uuid_t ble_uuid = {0};
    
    ble_uuid.type = p_tag_activity_log_service->uuid_type;
    ble_uuid.uuid = BLE_UUID_TAG_ACTIVITY_LOG_READ_RECORDS_COUNT_CHAR;

    // Attribute Meta Data
    //
    ble_gatts_attr_md_t attr_md = {0};
    
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.read_perm);
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.write_perm);

    attr_md.vloc = BLE_GATTS_VLOC_STACK;
    
    attr_md.rd_auth = 1;
    attr_md.wr_auth = 0;
    
    attr_md.vlen = 0;

    // Attribute / Value Activity Log
    //
    ble_gatts_attr_t attr_char_value = {0};
    
    ble_tag_activity_log_read_records_count_t tag_activity_log_read_records_count = {0};

    attr_char_value.p_uuid    = &ble_uuid;
    attr_char_value.p_attr_md = &attr_md;
    attr_char_value.init_len  = sizeof(tag_activity_log_read_records_count);
    attr_char_value.init_offs = 0;
    attr_char_value.max_len   = sizeof(tag_activity_log_read_records_count);
    attr_char_value.p_value   = (uint8_t*)&tag_activity_log_read_records_count;
    
    // Add Tag Activity Log Read Records Count Characteristic
    //
    err_code = sd_ble_gatts_characteristic_add
    (
        p_tag_activity_log_service->service_handle, 
        &char_md,
        &attr_char_value,
        &p_tag_activity_log_service->tag_activity_log_read_records_count_char_handles
    );
    
    APP_ERROR_CHECK(err_code);
}

/**@brief Add Tag Activity Log Read Records Characteristic to the Service.
*/
void nrf51_tag_activity_log_read_records_char_add(ble_tag_activity_log_service_t* p_tag_activity_log_service)
{
    uint32_t err_code = NRF_SUCCESS;

    // Client Characteristic Activity Log Descriptor
    //
    ble_gatts_attr_md_t cccd_md = {0};

    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&cccd_md.read_perm);
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&cccd_md.write_perm);
    
    cccd_md.vloc = BLE_GATTS_VLOC_STACK;

    // Characteristic Meta Data
    //
    ble_gatts_char_md_t char_md = {0};
    
    char_md.char_props.write = 1;
    char_md.char_props.read  = 1;
    
    char_md.p_cccd_md = &cccd_md;
    
    // Characteristic UUID Activity Log
    //
    ble_uuid_t ble_uuid = {0};
    
    ble_uuid.type = p_tag_activity_log_service->uuid_type;
    ble_uuid.uuid = BLE_UUID_TAG_ACTIVITY_LOG_READ_RECORDS_CHAR;

    // Attribute Meta Data
    //
    ble_gatts_attr_md_t attr_md = {0};
    
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.read_perm);
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.write_perm);

    attr_md.vloc = BLE_GATTS_VLOC_STACK;
    
    attr_md.rd_auth = 1;
    attr_md.wr_auth = 0;
    
    attr_md.vlen = 0;

    // Attribute / Value Activity Log
    //
    ble_gatts_attr_t attr_char_value = {0};
    
    ble_tag_activity_log_read_records_t tag_activity_log_read_records = {0};

    attr_char_value.p_uuid    = &ble_uuid;
    attr_char_value.p_attr_md = &attr_md;
    attr_char_value.init_len  = sizeof(tag_activity_log_read_records);
    attr_char_value.init_offs = 0;
    attr_char_value.max_len   = sizeof(tag_activity_log_read_records);
    attr_char_value.p_value   = (uint8_t*)&tag_activity_log_read_records;
    
    // Add Tag Activity Log Read Records Characteristic
    //
    err_code = sd_ble_gatts_characteristic_add
    (
        p_tag_activity_log_service->service_handle, 
        &char_md,
        &attr_char_value,
        &p_tag_activity_log_service->tag_activity_log_read_records_char_handles
    );
    
    APP_ERROR_CHECK(err_code);
}

/**@brief Add Tag Activity Log Create Records Characteristic to the Service.
*/
void nrf51_tag_activity_log_create_records_char_add(ble_tag_activity_log_service_t* p_tag_activity_log_service)
{
    uint32_t err_code = NRF_SUCCESS;

    // Client Characteristic Activity Log Descriptor
    //
    ble_gatts_attr_md_t cccd_md = {0};

    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&cccd_md.read_perm);
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&cccd_md.write_perm);
    
    cccd_md.vloc = BLE_GATTS_VLOC_STACK;

    // Characteristic Meta Data
    //
    ble_gatts_char_md_t char_md = {0};
    
    char_md.char_props.write = 1;
    char_md.char_props.read  = 1;
    
    char_md.p_cccd_md = &cccd_md;
    
    // Characteristic UUID Activity Log
    //
    ble_uuid_t ble_uuid = {0};
    
    ble_uuid.type = p_tag_activity_log_service->uuid_type;
    ble_uuid.uuid = BLE_UUID_TAG_ACTIVITY_LOG_CREATE_RECORDS_CHAR;

    // Attribute Meta Data
    //
    ble_gatts_attr_md_t attr_md = {0};
    
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.read_perm);
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.write_perm);

    attr_md.vloc = BLE_GATTS_VLOC_STACK;
    
    attr_md.rd_auth = 1;
    attr_md.wr_auth = 0;
    
    attr_md.vlen = 0;

    // Attribute / Value Activity Log
    //
    ble_gatts_attr_t attr_char_value = {0};
    
    ble_tag_activity_log_create_records_t tag_activity_log_create_records = {0};

    attr_char_value.p_uuid    = &ble_uuid;
    attr_char_value.p_attr_md = &attr_md;
    attr_char_value.init_len  = sizeof(tag_activity_log_create_records);
    attr_char_value.init_offs = 0;
    attr_char_value.max_len   = sizeof(tag_activity_log_create_records);
    attr_char_value.p_value   = (uint8_t*)&tag_activity_log_create_records;
    
    // Add Tag Activity Log Create Records Characteristic
    //
    err_code = sd_ble_gatts_characteristic_add
    (
        p_tag_activity_log_service->service_handle, 
        &char_md,
        &attr_char_value,
        &p_tag_activity_log_service->tag_activity_log_create_records_char_handles
    );
    
    APP_ERROR_CHECK(err_code);
}
