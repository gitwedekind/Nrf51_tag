/**
* @file nrf51_sys_defines.h
* @brief nrf51 System Header files.
*
*/

#pragma once

/**
*/
#define MAKE_U16( x_lo, x_hi ) \
    ( ( ((uint16_t)x_hi ) << 8 ) | (0x00FF & ((uint16_t)x_lo) ) )

//-------------------------------------------------------------------------------------------------
// Debug Options
//-------------------------------------------------------------------------------------------------
//#define TAG_UART_ENABLED
#define TAG_RTT_ENABLED

#define ENABLE_BLE400_DEV_BOARD
//#define ENABLE_CJMCU_DEV_BOARD

//-------------------------------------------------------------------------------------------------
// BLE Parameters
//-------------------------------------------------------------------------------------------------

static const char * const NRF51_TAG_DEVICE_NAME = "RI_Tag #";

#define TAG_DEVICE_NAME_LENGTH   8
#define TAG_SERIAL_NUMBER_LENGTH 5

#define TAG_SHORT_DEVICE_NAME_LENGTH 6

#define TAG_MANUFACTURING_DATA_LENGTH 3

static const char * const NRF51_TAG_MANUFACTURE_NAME = "RemoteInsights";

#define NRF_BLE_CENTRAL_LINK_COUNT    0
#define NRF_BLE_PERIPHERAL_LINK_COUNT 1

#define ADV_COMPANY_ID 0x0001

//-------------------------------------------------------------------------------------------------
// Tag Activity Log Record Format
//-------------------------------------------------------------------------------------------------
#pragma pack(1)

/** @brief Tag Accelerometer Packet
*/
typedef struct ble_tag_accelerometer_t ble_tag_accelerometer_t;
struct ble_tag_accelerometer_t
{
    int16_t x;
    int16_t y;
    int16_t z;
};

#define BEACON_ADDR_LENGTH 6

typedef struct ble_tag_beacon_log_record_format_t ble_tag_beacon_log_record_format_t;
struct ble_tag_beacon_log_record_format_t
{
    uint32_t time_stamp;
    uint8_t beacon_addr[BEACON_ADDR_LENGTH];
};

/** @brief Tag Activity Log Record Format
*/
typedef struct ble_tag_activity_log_record_format_t ble_tag_activity_log_record_format_t;
struct ble_tag_activity_log_record_format_t
{
    uint32_t time_stamp;
    ble_tag_accelerometer_t accelerometer;
};

#pragma pack()

//-----------------------------------------------------------------------------
// Tag Debug Service Definitions
//-----------------------------------------------------------------------------

// The RI Tag 128-bit base service UUID
//
#define BLE_UUID_TAG_DEBUG_BASE \
    { 0xB9, 0x12, 0xF1, 0x53, 0x98, 0xDD, 0x4E, 0x7E, 0xA9, 0x66, 0xE9, 0x33, 0x00, 0x00, 0xEF, 0xD3 }

// The Characteristics using the 128-bit base service UUID
//
#define BLE_UUID_TAG_DEBUG_SERVICE  0x1000
#define BLE_UUID_TAG_VERSION_CHAR   0x1001
#define BLE_UUID_TAG_DEBUG_CMD_CHAR 0x1002

//-----------------------------------------------------------------------------
// Tag Status Service Definitions
//-----------------------------------------------------------------------------

// Tag Status 128-bit base service UUID
//
#define BLE_UUID_TAG_STATUS_BASE \
    { 0xCC, 0x8D, 0x6F, 0xF4, 0xFD, 0x87, 0x40, 0x5F, 0xA4, 0xAA, 0xDF, 0xB5, 0x00, 0x00, 0xAB, 0x0E }

// Status Characteristics using the 128-bit base service UUID
//
#define BLE_UUID_TAG_STATUS_SERVICE          0x2000
#define BLE_UUID_TAG_STATUS_UPTIME_CHAR      0x2001
#define BLE_UUID_TAG_STATUS_TEMPERATURE_CHAR 0x2002

//-----------------------------------------------------------------------------
// Tag Configuration Service Definitions
//-----------------------------------------------------------------------------

// Configuration RI Tag 128-bit base service UUID
//
#define BLE_UUID_TAG_CONFIGURATION_BASE \
    { 0x61, 0x71, 0x00, 0x71, 0xE2, 0xB5, 0x4C, 0x96, 0x9C, 0x22, 0x3C, 0xE7, 0x00, 0x00, 0x4E, 0x7F }

// Configuration Characteristics using the 128-bit base service UUID
//
#define BLE_UUID_TAG_CONFIGURATION_SERVICE                 0x3000
#define BLE_UUID_TAG_CONFIGURATION_BEACON_IDS_CHAR         0x3001
#define BLE_UUID_TAG_CONFIGURATION_ADV_BURST_INTERVAL_CHAR 0x3002
#define BLE_UUID_TAG_CONFIGURATION_ADV_BURST_DURATION_CHAR 0x3002

//-----------------------------------------------------------------------------
// Tag Activity Log Service Definitions
//-----------------------------------------------------------------------------

// The RI Tag Activity Log 128-bit base service UUID
//
#define BLE_UUID_TAG_ACTIVITY_LOG_BASE \
    { 0xD7, 0xFD, 0x59, 0x89, 0xC5, 0xC7, 0x40, 0x1E, 0xBB, 0xEF, 0x24, 0x89, 0x00, 0x00, 0x79, 0x15 }

// Activity Log Characteristics using the 128-bit base service UUID
//
#define BLE_UUID_TAG_ACTIVITY_LOG_SERVICE                 0x4000
#define BLE_UUID_TAG_ACTIVITY_LOG_RECORD_SIZE_CHAR        0x4001
#define BLE_UUID_TAG_ACTIVITY_LOG_RECORD_COUNT_CHAR       0x4002
#define BLE_UUID_TAG_ACTIVITY_LOG_READ_RECORDS_COUNT_CHAR 0x4003
#define BLE_UUID_TAG_ACTIVITY_LOG_READ_RECORDS_CHAR       0x4004
#define BLE_UUID_TAG_ACTIVITY_LOG_CREATE_RECORDS_CHAR     0x4005

//-----------------------------------------------------------------------------
// Tag Beacon Log Service Definitions
//-----------------------------------------------------------------------------

// The RI Tag Beacon Log 128-bit base service UUID
//
#define BLE_UUID_TAG_BEACON_LOG_BASE \
    { 0x48, 0x0B, 0xAC, 0x53, 0xD2, 0x05, 0x4C, 0x55, 0x9E, 0x2D, 0x4E, 0x79, 0x00, 0x00, 0xCF, 0xF8 }

// Activity Log Characteristics using the 128-bit base service UUID
//
#define BLE_UUID_TAG_BEACON_LOG_SERVICE                 0x5000
#define BLE_UUID_TAG_BEACON_LOG_RECORD_SIZE_CHAR        0x5001
#define BLE_UUID_TAG_BEACON_LOG_RECORD_COUNT_CHAR       0x5002
#define BLE_UUID_TAG_BEACON_LOG_READ_RECORDS_COUNT_CHAR 0x5003
#define BLE_UUID_TAG_BEACON_LOG_READ_RECORDS_CHAR       0x5004
#define BLE_UUID_TAG_BEACON_LOG_CREATE_RECORDS_CHAR     0x5005
