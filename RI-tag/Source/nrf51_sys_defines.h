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

// Tag Debug 128-bit Generated UUID
//
// {124B88F6-5ED2-4729-A4AA-F6C1685AB62D}
// 0x124b88f6, 0x5ed2, 0x4729, 0xa4, 0xaa, 0xf6, 0xc1, 0x68, 0x5a, 0xb6, 0x2d
// { 0x12, 0x4B, 0x88, 0xF6, 0x5E, 0xD2, 0x47, 0x29, 0xA4, 0xAA, 0xF6, 0xC1, 0x68, 0x5a, 0xB6, 0x2D }

// Tag Debug 128-bit Gateway UUID's
// Tag Debug Service      = {124B88F6-5ED2-4729-A4AA-F6C10010B62D}
// Tag Debug Version Char = {124B88F6-5ED2-4729-A4AA-F6C10110B62D}
// Tag Debug Cmd Char     = {124B88F6-5ED2-4729-A4AA-F6C10210B62D}

// Tag Debug 128-bit Base Service UUID
//
#define BLE_UUID_TAG_DEBUG_BASE \
    { 0x12, 0x4B, 0x88, 0xF6, 0x5E, 0xD2, 0x47, 0x29, 0xA4, 0xAA, 0xF6, 0xC1, 0x00, 0x00, 0xB6, 0x2D }

// Debug Characteristics using the 128-bit Base Service UUID
//
#define BLE_UUID_TAG_DEBUG_SERVICE  0x1000
#define BLE_UUID_TAG_VERSION_CHAR   0x1001
#define BLE_UUID_TAG_DEBUG_CMD_CHAR 0x1002

//-----------------------------------------------------------------------------
// Tag Status Service Definitions
//-----------------------------------------------------------------------------

// Tag Status 128-bit Generated UUID
//
// {0DE35B69-A433-47AE-AF41-668B04F201CD}
// 0xde35b69, 0xa433, 0x47ae, 0xaf, 0x41, 0x66, 0x8b, 0x4, 0xf2, 0x1, 0xcd
// { 0x0D, 0xE3, 0x5B, 0x69, 0xA4, 0x33, 0x47, 0xAE, 0xAF, 0x41, 0x66, 0x8B, 0x04, 0xF2, 0x01, 0xCD }
 
// Tag Status 128-bit Gateway UUID's
// Tag Status Service          = {0DE35B69-A433-47AE-AF41-668B002001CD}
// Tag Status Uptime Char      = {0DE35B69-A433-47AE-AF41-668B012001CD}
// Tag Status Tempurature Char = {0DE35B69-A433-47AE-AF41-668B022001CD}

// Tag Status 128-bit Base Service UUID
//
#define BLE_UUID_TAG_STATUS_BASE \
    { 0x0D, 0xE3, 0x5B, 0x69, 0xA4, 0x33, 0x47, 0xAE, 0xAF, 0x41, 0x66, 0x8B, 0x00, 0x00, 0x01, 0xCD }

// Status Characteristics using the 128-bit Base Service UUID
//
#define BLE_UUID_TAG_STATUS_SERVICE          0x2000
#define BLE_UUID_TAG_STATUS_UPTIME_CHAR      0x2001
#define BLE_UUID_TAG_STATUS_TEMPERATURE_CHAR 0x2002

//-----------------------------------------------------------------------------
// Tag Configuration Service Definitions
//-----------------------------------------------------------------------------

// Tag Configuration 128-bit Generated UUID
// {EACDBBA3-C972-4536-9D70-8CA907D41F3C}
// 0xeacdbba3, 0xc972, 0x4536, 0x9d, 0x70, 0x8c, 0xa9, 0x7, 0xd4, 0x1f, 0x3c
// { 0xEA, 0xCD, 0xBB, 0xA3, 0xC9, 0x72, 0x45, 0x36, 0x9D, 0x70, 0x8C, 0xA9, 0x07, 0xD4, 0x1F, 0x3C }
    
// Tag Configuration 128-bit Gateway UUID's
// Tag Configuration Service                 = {EACDBBA3-C972-4536-9D70-8CA900030F3C}
// Tag Configuration Beacon IDS Char         = {EACDBBA3-C972-4536-9D70-8CA900130F3C}
// Tag Configuration Adv Burst Interval Char = {EACDBBA3-C972-4536-9D70-8CA900230F3C}
// Tag Configuration Adv Burst Duration Char = {EACDBBA3-C972-4536-9D70-8CA900330F3C}

// Tag Configuration 128-bit Base Service UUID
//
#define BLE_UUID_TAG_CONFIGURATION_BASE \
    { 0xEA, 0xCD, 0xBB, 0xA3, 0xC9, 0x72, 0x45, 0x36, 0x9D, 0x70, 0x8C, 0xA9, 0x00, 0x00, 0x1F, 0x3C }

// Configuration Characteristics using the 128-bit Base Service UUID
//
#define BLE_UUID_TAG_CONFIGURATION_SERVICE                 0x3000
#define BLE_UUID_TAG_CONFIGURATION_BEACON_IDS_CHAR         0x3001
#define BLE_UUID_TAG_CONFIGURATION_ADV_BURST_INTERVAL_CHAR 0x3002
#define BLE_UUID_TAG_CONFIGURATION_ADV_BURST_DURATION_CHAR 0x3003

//-----------------------------------------------------------------------------
// Tag Activity Log Service Definitions
//-----------------------------------------------------------------------------

// Tag Activity Log 128-bit Generated UUID
// {51B08C47-F9D0-492D-AFD7-B976CFE8EC92}
// 0x51b08c47, 0xf9d0, 0x492d, 0xaf, 0xd7, 0xb9, 0x76, 0xcf, 0xe8, 0xec, 0x92
// { 0x51, 0xB0, 0x8C, 0x47, 0xF9, 0xD0, 0x49, 0x2D, 0xAF, 0xD7, 0xB9, 0x76, 0xCF, 0xE8, 0xEC, 0x92 }
    
// Tag Activity Log 128-bit Gateway UUID's
// Tag Activity Log Service                 = {51B08C47-F9D0-492D-AFD7-B9760040EC92}
// Tag Activity Log Record Size Char        = {51B08C47-F9D0-492D-AFD7-B9760140EC92}
// Tag Activity Log Record Count Char       = {51B08C47-F9D0-492D-AFD7-B9760240EC92}
// Tag Activity Log Read Records Count Char = {51B08C47-F9D0-492D-AFD7-B9760340EC92}
// Tag Activity Log Read Records Char       = {51B08C47-F9D0-492D-AFD7-B9760440EC92}
// Tag Activity Log Create Records Char     = {51B08C47-F9D0-492D-AFD7-B9760540EC92}

// Tag Activity Log 128-bit Base Service UUID
//
#define BLE_UUID_TAG_ACTIVITY_LOG_BASE \
    { 0x51, 0xB0, 0x8C, 0x47, 0xF9, 0xD0, 0x49, 0x2D, 0xAF, 0xD7, 0xB9, 0x76, 0x00, 0x00, 0xEC, 0x92 }

// Activity Log Characteristics using the 128-bit Base Service UUID
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

// Tag Beacon Log 128-bit Generated UUID
// {DABDA4B6-A6E6-42AB-952B-5B07F4AA20CE}
// 0xdabda4b6, 0xa6e6, 0x42ab, 0x95, 0x2b, 0x5b, 0x7, 0xf4, 0xaa, 0x20, 0xce
// { 0xDA, 0xBD, 0xA4, 0xB6, 0xA6, 0xE6, 0x42, 0xAB, 0x95, 0x2B, 0x5B, 0x07, 0xF4, 0xAA, 0x20, 0xCE }
    
// Tag Beacon Log 128-bit Gateway UUID's
// Tag Beacon Log Service                 = {DABDA4B6-A6E6-42AB-952B-5B07005020CE}
// Tag Beacon Log Record Size Char        = {DABDA4B6-A6E6-42AB-952B-5B07015020CE}
// Tag Beacon Log Record Count Char       = {DABDA4B6-A6E6-42AB-952B-5B07025020CE}
// Tag Beacon Log Read Records Count Char = {DABDA4B6-A6E6-42AB-952B-5B07035020CE}
// Tag Beacon Log Read Records Char       = {DABDA4B6-A6E6-42AB-952B-5B07045020CE}
// Tag Beacon Log Create Records Char     = {DABDA4B6-A6E6-42AB-952B-5B07055020CE}

// Beacon Log 128-bit Base Service UUID
//
#define BLE_UUID_TAG_BEACON_LOG_BASE \
    { 0xDA, 0xBD, 0xA4, 0xB6, 0xA6, 0xE6, 0x42, 0xAB, 0x95, 0x2B, 0x5B, 0x07, 0x00, 0x00, 0x20, 0xCE }

// Beacon Log Characteristics using the 128-bit Base Service UUID
//
#define BLE_UUID_TAG_BEACON_LOG_SERVICE                 0x5000
#define BLE_UUID_TAG_BEACON_LOG_RECORD_SIZE_CHAR        0x5001
#define BLE_UUID_TAG_BEACON_LOG_RECORD_COUNT_CHAR       0x5002
#define BLE_UUID_TAG_BEACON_LOG_READ_RECORDS_COUNT_CHAR 0x5003
#define BLE_UUID_TAG_BEACON_LOG_READ_RECORDS_CHAR       0x5004
#define BLE_UUID_TAG_BEACON_LOG_CREATE_RECORDS_CHAR     0x5005
