/**
* @file nrf51_tag_advertising.c
* @brief Source File for Radio Interface Advertising.
*
*/

#include "nrf51_tag_error.h"
#include "nrf51_tag_advertising.h"

//----------------------------------------------------------------------------
// BLE Advertising Variables
//----------------------------------------------------------------------------

static ble_gap_adv_params_t s_adv_params = {0};

static int8_t s_tx_power_level = 0;

static char s_device_name_with_tag_id[TAG_DEVICE_NAME_LENGTH + TAG_SERIAL_NUMBER_LENGTH + 1] = {0};

static uint8_t s_manufacturing_data[TAG_MANUFACTURING_DATA_LENGTH + 1] = {0};

/** @brief Update Device Name.
*/
void nrf51_tag_update_device_name(uint32_t tag_serial_number)
{
    memset(s_device_name_with_tag_id, '\0', sizeof(s_device_name_with_tag_id));

    memcpy(
        s_device_name_with_tag_id, 
        NRF51_TAG_DEVICE_NAME, 
        TAG_DEVICE_NAME_LENGTH);
    
    snprintf(&s_device_name_with_tag_id[TAG_DEVICE_NAME_LENGTH], TAG_SERIAL_NUMBER_LENGTH+1, "%05d", tag_serial_number);
    
    DBG("--> %s, length: %d\r\n", s_device_name_with_tag_id, nrf51_tag_get_device_name_length());
    
    nrf51_tag_set_gap_device_name((uint8_t*)s_device_name_with_tag_id, nrf51_tag_get_device_name_length());
}

uint8_t* nrf51_tag_get_device_name(void)
{
    return (uint8_t*)&s_device_name_with_tag_id[0];
}

uint8_t nrf51_tag_get_device_name_length(void)
{
    return TAG_DEVICE_NAME_LENGTH + TAG_SERIAL_NUMBER_LENGTH;
}

/** @brief Update Manufacturing Data.
*/
void nrf51_tag_update_manufacturing_data(uint8_t ping, uint16_t tag_id, uint16_t beacon_record_count, uint16_t activity_log_record_count)
{
    memset(s_manufacturing_data, '\0', sizeof(s_manufacturing_data));
    
    uint16_encode(0xFFFF, &s_manufacturing_data[0]);                    // 0,1
    s_manufacturing_data[2] = ping;                                     // 2
    uint16_encode(tag_id, &s_manufacturing_data[3]);                    // 3, 4
    uint16_encode(beacon_record_count, &s_manufacturing_data[5]);       // 5, 6
    uint16_encode(activity_log_record_count, &s_manufacturing_data[7]); // 7, 8
}

uint8_t* nrf51_tag_get_manufacturing_data(void)
{
    return (uint8_t*)&s_manufacturing_data[0];
}

uint8_t nrf51_tag_get_manufacturing_data_length(void)
{
    return TAG_MANUFACTURING_DATA_LENGTH;
}

/**@brief Function for handling advertising events.
 *
 * @details This function will be called for advertising events which are passed to the application.
 *
 * @param[in] ble_adv_evt  Advertising event.
 */
static void on_adv_evt(ble_adv_evt_t ble_adv_evt)
{
    //uint32_t err_code;

    DBG_EVENT_ADVERTISING(ble_adv_evt);

    switch (ble_adv_evt)
    {
    case BLE_ADV_EVT_FAST:
        break;

    case BLE_ADV_EVT_IDLE:
        break;

    default:
        break;
    }
}

//----------------------------------------------------------------------------
// Radio Advertising Functions
//----------------------------------------------------------------------------

/**@brief Function for initializing the Advertising Parameters.
 *
 * The function sets the advertising packet to the default settings, no central
 * devices have connected / bonded to the Transmitter.
 */
bool nrf51_tag_set_advertising_parameters(uint16_t interval, uint16_t timeout)
{
    // Initialize advertising parameters
    //
    memset(&s_adv_params, 0, sizeof(s_adv_params));
    
    s_adv_params.fp          = nrf51_tag_get_whitelist_filter_policy(); // Filter Policy
    s_adv_params.p_whitelist = nrf51_tag_get_whitelist();               // NULL if no whitelist configured
    
    s_adv_params.interval    = interval; // advertising interval
    s_adv_params.timeout     = timeout;  // advertising timeout
    
    return (s_adv_params.p_whitelist != NULL);
}

/**@brief Function for initializing the Advertising Packet.
 *
 * Encodes the Dexcom advertising data and passes it to the stack.
 */
void nrf51_tag_advertising_packet_initialize(void)
{
    uint32_t err_code = NRF_SUCCESS;
    
    s_tx_power_level = (int8_t)nrf51_tag_get_tx_power();
    
    ble_advdata_t advdata;
    ble_adv_modes_config_t options = {0};

    ble_advdata_manuf_data_t manuf_data = {0};
    
    uint8_t flags = BLE_GAP_ADV_FLAG_BR_EDR_NOT_SUPPORTED;
    
    DBG_INITIALIZE_ADVERTISING();
    
    // Note: If the whitelist is enabled BLE_ERROR_GAP_DISCOVERABLE_WITH_WHITELIST
    // will trigger if this flag is set
    //
    if ( s_adv_params.p_whitelist == NULL )
    {
        flags |= BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE;
    }
    
    ble_uuid_t adv_uuids[] =
    {
        {BLE_UUID_BATTERY_SERVICE, BLE_UUID_TYPE_BLE}
    };

    memset(&advdata, 0, sizeof(advdata));

    advdata.name_type                     = BLE_ADVDATA_SHORT_NAME;
    advdata.short_name_len                = TAG_SHORT_DEVICE_NAME_LENGTH;
    advdata.include_appearance            = false;
    advdata.flags                         = flags;
    
    //advdata.include_ble_device_addr       = true;
    //advdata.p_tx_power_level              = &s_tx_power_level;
    
    advdata.uuids_more_available.uuid_cnt = sizeof(adv_uuids) / sizeof(adv_uuids[0]);
    advdata.uuids_more_available.p_uuids  = adv_uuids;
    
    manuf_data.company_identifier  = ADV_COMPANY_ID;
    manuf_data.data.p_data         = nrf51_tag_get_manufacturing_data();
    manuf_data.data.size           = nrf51_tag_get_manufacturing_data_length();
    advdata.p_manuf_specific_data  = &manuf_data;

    memset(&options, 0, sizeof(options));
    options.ble_adv_fast_enabled  = true;
    options.ble_adv_fast_interval = NRF51_TAG_ADV_INTERVAL;
    options.ble_adv_fast_timeout  = NRF51_TAG_ADV_TIMEOUT_IN_SECONDS;
    
    err_code = ble_advertising_init(&advdata, NULL, &options, on_adv_evt, NULL);
    APP_ERROR_CHECK(err_code);
}

/**@brief
 */
uint32_t nrf51_tag_start_advertising()
{
    uint32_t err_code = ble_advertising_start(BLE_ADV_MODE_FAST);
    APP_ERROR_CHECK(err_code);
    
    DBG_START_ADVERTISING();
    
    return get_system_time();
}

/**@brief
 */
void nrf51_tag_stop_advertising(void)
{
    uint32_t err_code = sd_ble_gap_adv_stop();
    APP_ERROR_CHECK(err_code);

    DBG_STOP_ADVERTISING();
}
