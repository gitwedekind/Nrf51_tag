/**
* @file nrf51_tag_db.h
* @brief Header file for Tag Database.
*
*/

#pragma once

#include "nrf51_tag_headers.h"

#pragma pack(1)

typedef struct ble_tag_db_record_t ble_tag_db_record_t;
struct ble_tag_db_record_t
{
    uint8_t x;
    uint8_t y;
    uint8_t z;
};

#define MAX_DB_RECORDS 4

typedef struct ble_tag_db_entry_t ble_tag_db_entry_t;
struct ble_tag_db_entry_t
{
    uint32_t timestamp;
    ble_tag_db_record_t data[MAX_DB_RECORDS];
};

typedef struct ble_tag_entry_info_t ble_tag_entry_info_t;
struct ble_tag_entry_info_t
{
    uint32_t total_records;
    uint32_t active_records;
};

#pragma pack()

void nrf51_tag_database_sys_evt(uint32_t sys_evt);

void nrf51_tag_db_initialize(void);

void nrf51_tag_db_erase(void);

uint8_t nrf51_tag_db_erased(void);

ble_tag_entry_info_t nrf51_tag_db_record_count(void);

void nrf51_tag_db_write_entry(ble_tag_db_entry_t* p_ble_tag_db_entry);

void nrf51_tag_db_read_record(ble_tag_status_activity_read_records_t* p_ble_tag_status_activity_read_records);


// ------------------------------------------------------------------------------------------------
// Debug Message(s)
// ------------------------------------------------------------------------------------------------
#define ENABLE_INITIALIZE_DB_MESSAGES

#if defined(ENABLE_INITIALIZE_DB_MESSAGES)

#define DBG_DB_INITIALIZE() FUNCTION()
    
#define DBG_DB_RECORDS(x_info) \
    DBG("--> Tag Db, Total Records: %d Active Records: %d\r\n", x_info.total_records, x_info.active_records)

#define DBG_DB_WRITE_ADDRESS(x_addr) \
DBG("--> Tag Db, Write Address: 0x%x\r\n", x_addr)

#else

#define DBG_DB_INITIALIZE()

#define DBG_DB_RECORDS(x_info)

#define DBG_DB_WRITE_ADDRESS(x_addr)

#endif
