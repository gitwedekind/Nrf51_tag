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
// LIS3DH Mode 
//-------------------------------------------------------------------------------------------------

#define ENABLE_8_BIT_MODE
//#define ENABLE_10_BIT_MODE
//#define ENABLE_12_BIT_MODE

//-------------------------------------------------------------------------------------------------
// BLE Parameters
//-------------------------------------------------------------------------------------------------

static const char * const NRF51_TAG_DEVICE_NAME = "RI_Tag #";

#define TAG_DEVICE_NAME_LENGTH   8
#define TAG_SERIAL_NUMBER_LENGTH 5

#define TAG_SHORT_DEVICE_NAME_LENGTH 6

#define TAG_MANUFACTURING_DATA_LENGTH 9

static const char * const NRF51_TAG_MANUFACTURE_NAME = "RemoteInsights";

#define NRF_BLE_CENTRAL_LINK_COUNT    0
#define NRF_BLE_PERIPHERAL_LINK_COUNT 1

#define ADV_COMPANY_ID 0xFFFF

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
// Tag Status Service                    = {0DE35B69-A433-47AE-AF41-668B002001CD}
// Tag Status Uptime Char                = {0DE35B69-A433-47AE-AF41-668B012001CD}
// Tag Status Temperature Char           = {0DE35B69-A433-47AE-AF41-668B022001CD}
// Tag Status Battery Level Char         = {0DE35B69-A433-47AE-AF41-668B032001CD}
// Tag Status Firmware Revision Char     = {0DE35B69-A433-47AE-AF41-668B042001CD}
// Tag Status Beacon Record Count Char   = {0DE35B69-A433-47AE-AF41-668B052001CD}
// Tag Status Beacon Read Records Char   = {0DE35B69-A433-47AE-AF41-668B062001CD}
// Tag Status Activity Record Count Char = {0DE35B69-A433-47AE-AF41-668B072001CD}
// Tag Status Activity Read Records Char = {0DE35B69-A433-47AE-AF41-668B082001CD}

// Tag Status 128-bit Base Service UUID
//
#define BLE_UUID_TAG_STATUS_BASE \
    { 0x0D, 0xE3, 0x5B, 0x69, 0xA4, 0x33, 0x47, 0xAE, 0xAF, 0x41, 0x66, 0x8B, 0x00, 0x00, 0x01, 0xCD }

// Status Characteristics using the 128-bit Base Service UUID
//
#define BLE_UUID_TAG_STATUS_SERVICE                    0x2000
#define BLE_UUID_TAG_STATUS_UPTIME_CHAR                0x2001
#define BLE_UUID_TAG_STATUS_TEMPERATURE_CHAR           0x2002
#define BLE_UUID_TAG_STATUS_BATTERY_LEVEL_CHAR         0x2003
#define BLE_UUID_TAG_STATUS_FIRMWARE_REVISION_CHAR     0x2004
#define BLE_UUID_TAG_STATUS_BEACON_RECORD_COUNT_CHAR   0x2005
#define BLE_UUID_TAG_STATUS_BEACON_READ_RECORDS_CHAR   0x2006
#define BLE_UUID_TAG_STATUS_ACTIVITY_RECORD_COUNT_CHAR 0x2007
#define BLE_UUID_TAG_STATUS_ACTIVITY_READ_RECORDS_CHAR 0x2008

//-----------------------------------------------------------------------------
// Tag Configuration Service Definitions
//-----------------------------------------------------------------------------

// Tag Configuration 128-bit Generated UUID
// {EACDBBA3-C972-4536-9D70-8CA907D41F3C}
// 0xeacdbba3, 0xc972, 0x4536, 0x9d, 0x70, 0x8c, 0xa9, 0x7, 0xd4, 0x1f, 0x3c
// { 0xEA, 0xCD, 0xBB, 0xA3, 0xC9, 0x72, 0x45, 0x36, 0x9D, 0x70, 0x8C, 0xA9, 0x07, 0xD4, 0x1F, 0x3C }
    
// Tag Configuration 128-bit Gateway UUID's
// Tag Configuration Service                 = {EACDBBA3-C972-4536-9D70-8CA900030F3C}
// Tag Configuration Sample Rate Char        = {EACDBBA3-C972-4536-9D70-8CA900130F3C}
// Tag Configuration Serial Number Char      = {EACDBBA3-C972-4536-9D70-8CA900230F3C}

// Tag Configuration 128-bit Base Service UUID
//
#define BLE_UUID_TAG_CONFIGURATION_BASE \
    { 0xEA, 0xCD, 0xBB, 0xA3, 0xC9, 0x72, 0x45, 0x36, 0x9D, 0x70, 0x8C, 0xA9, 0x00, 0x00, 0x1F, 0x3C }

// Configuration Characteristics using the 128-bit Base Service UUID
//
#define BLE_UUID_TAG_CONFIGURATION_SERVICE                 0x3000
#define BLE_UUID_TAG_CONFIGURATION_SAMPLE_RATE_CHAR        0x3001
#define BLE_UUID_TAG_CONFIGURATION_SERIAL_NUMBER_CHAR      0x3002
