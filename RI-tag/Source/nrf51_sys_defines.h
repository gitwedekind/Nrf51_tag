/**
* @file nrf51_sys_defines.h
* @brief nrf51 System Header files.
*
*/

#pragma once

//---------------------------------------------------------------------------
// Macro to remove "Tag vs Type Name" issues when defining structures,
// i.e. removes typo's since the name is typed 3 times.
//
// Note: Based on Embedded.com Article by Dan Saks
//       "Tag vs Type Names" Oct 01 2002
//---------------------------------------------------------------------------
#define STRUCT_DEF(x_struct_name) \
    typedef struct x_struct_name x_struct_name; \
    struct x_struct_name

#define UNION_DEF(x_union_name) \
    typedef union x_union_name x_union_name; \
    union x_union_name

/**
*/
#define MAKE_U16( x_lo, x_hi ) \
    ( ( ((uint16_t)x_hi ) << 8 ) | (0x00FF & ((uint16_t)x_lo) ) )

//-------------------------------------------------------------------------------------------------
// Debug Options
//-------------------------------------------------------------------------------------------------
//#define TAG_UART_ENABLED
#define TAG_RTT_ENABLED

//#define ENABLE_BLE400_DEV_BOARD 1
//#define ENABLE_CJMCU_DEV_BOARD 1
#define ENABLE_RI_TAG_BOARD 1
    
//-------------------------------------------------------------------------------------------------
// LIS3DH Mode 
//-------------------------------------------------------------------------------------------------

#define ENABLE_8_BIT_MODE
//#define ENABLE_10_BIT_MODE
//#define ENABLE_12_BIT_MODE

//#define ENABLE_WHO_AM_1_TEST_MODE    

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
// Tag Status Diagnostics Char           = {0DE35B69-A433-47AE-AF41-668B092001CD}
// Tag Status sERIAL nUMBER Char         = {0DE35B69-A433-47AE-AF41-668B0A2001CD}

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
#define BLE_UUID_TAG_STATUS_ACTIVITY_RECORD_COUNT_CHAR 0x2006
#define BLE_UUID_TAG_STATUS_ACTIVITY_READ_RECORDS_CHAR 0x2008
#define BLE_UUID_TAG_STATUS_DIAGNOSTICS_CHAR           0x2009
#define BLE_UUID_TAG_STATUS_SERIAL_NUMBER_CHAR         0x200A
