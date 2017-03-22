/**
* @file nrf51_tag_configuration_characteristic.c
* @brief Source file for the Tag Configuration Characteristic.
*
*/

#include "nrf51_tag_error.h"
#include "nrf51_tag_headers.h"

/**@brief Add Tag Configuration Beacon Ids Characteristic to the Service.
*/
void nrf51_tag_configuration_beacon_ids_char_add(ble_tag_configuration_service_t* p_tag_configuration_service)
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
    
    char_md.char_props.write = 1;
    char_md.char_props.read  = 1;
    
    char_md.p_cccd_md = &cccd_md;
    
    // Characteristic UUID Configuration
    //
    ble_uuid_t ble_uuid = {0};
    
    ble_uuid.type = p_tag_configuration_service->uuid_type;
    ble_uuid.uuid = BLE_UUID_TAG_CONFIGURATION_BEACON_IDS_CHAR;

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
    
    ble_tag_configuration_beacon_ids_t tag_configuration_beacon_ids = {0};

    attr_char_value.p_uuid    = &ble_uuid;
    attr_char_value.p_attr_md = &attr_md;
    attr_char_value.init_len  = sizeof(tag_configuration_beacon_ids);
    attr_char_value.init_offs = 0;
    attr_char_value.max_len   = sizeof(tag_configuration_beacon_ids);
    attr_char_value.p_value   = (uint8_t*)&tag_configuration_beacon_ids;
    
    // Add Tag Configuration Characteristic
    // Note: Populates the tag_configuration_cmd_char_handles field 
    //
    err_code = sd_ble_gatts_characteristic_add
    (
        p_tag_configuration_service->service_handle, 
        &char_md,
        &attr_char_value,
        &p_tag_configuration_service->tag_configuration_beacon_ids_char_handles
    );
    
    APP_ERROR_CHECK(err_code);
}

/**@brief Add Tag Configuration Adv Burst Interval Characteristic to the Service.
*/
void nrf51_tag_configuration_adv_burst_interval_char_add(ble_tag_configuration_service_t* p_tag_configuration_service)
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
    
    char_md.char_props.write = 1;
    char_md.char_props.read  = 1;
    
    char_md.p_cccd_md = &cccd_md;
    
    // Characteristic UUID Configuration
    //
    ble_uuid_t ble_uuid = {0};
    
    ble_uuid.type = p_tag_configuration_service->uuid_type;
    ble_uuid.uuid = BLE_UUID_TAG_CONFIGURATION_ADV_BURST_INTERVAL_CHAR;

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
    
    ble_tag_configuration_adv_burst_interval_t tag_configuration_adv_burst_interval = {0};

    attr_char_value.p_uuid    = &ble_uuid;
    attr_char_value.p_attr_md = &attr_md;
    attr_char_value.init_len  = sizeof(tag_configuration_adv_burst_interval);
    attr_char_value.init_offs = 0;
    attr_char_value.max_len   = sizeof(tag_configuration_adv_burst_interval);
    attr_char_value.p_value   = (uint8_t*)&tag_configuration_adv_burst_interval;
    
    // Add Tag Configuration Characteristic
    // Note: Populates the tag_configuration_cmd_char_handles field 
    //
    err_code = sd_ble_gatts_characteristic_add
    (
        p_tag_configuration_service->service_handle, 
        &char_md,
        &attr_char_value,
        &p_tag_configuration_service->tag_configuration_adv_burst_interval_char_handles
    );
    
    APP_ERROR_CHECK(err_code);
}

/**@brief Add Tag Configuration Adv Burst Duration Characteristic to the Service.
*/
void nrf51_tag_configuration_adv_burst_duration_char_add(ble_tag_configuration_service_t* p_tag_configuration_service)
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
    
    char_md.char_props.write = 1;
    char_md.char_props.read  = 1;
    
    char_md.p_cccd_md = &cccd_md;
    
    // Characteristic UUID Configuration
    //
    ble_uuid_t ble_uuid = {0};
    
    ble_uuid.type = p_tag_configuration_service->uuid_type;
    ble_uuid.uuid = BLE_UUID_TAG_CONFIGURATION_ADV_BURST_DURATION_CHAR;

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
    
    ble_tag_configuration_adv_burst_duration_t tag_configuration_adv_burst_duration = {0};

    attr_char_value.p_uuid    = &ble_uuid;
    attr_char_value.p_attr_md = &attr_md;
    attr_char_value.init_len  = sizeof(tag_configuration_adv_burst_duration);
    attr_char_value.init_offs = 0;
    attr_char_value.max_len   = sizeof(tag_configuration_adv_burst_duration);
    attr_char_value.p_value   = (uint8_t*)&tag_configuration_adv_burst_duration;
    
    // Add Tag Configuration Characteristic
    // Note: Populates the tag_configuration_cmd_char_handles field 
    //
    err_code = sd_ble_gatts_characteristic_add
    (
        p_tag_configuration_service->service_handle, 
        &char_md,
        &attr_char_value,
        &p_tag_configuration_service->tag_configuration_adv_burst_duration_char_handles
    );
    
    APP_ERROR_CHECK(err_code);
}
