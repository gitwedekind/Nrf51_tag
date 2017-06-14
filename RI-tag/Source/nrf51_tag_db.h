/**
* @file nrf51_tag_db.h
* @brief Header file for Tag Database.
*
*/

#pragma once

#include "nrf51_tag_headers.h"

#ifdef __cplusplus
extern "C" {
#endif

#pragma pack(1)

STRUCT_DEF( ble_tag_db_record_t )
{
    int8_t x;
    int8_t y;
    int8_t z;
};

#define MAX_DB_RECORDS_PER_ENTRY 4

STRUCT_DEF( ble_tag_db_entry_t )
{
    uint32_t timestamp;
    ble_tag_db_record_t data[MAX_DB_RECORDS_PER_ENTRY];
};

#pragma pack()

STRUCT_DEF( ble_tag_db_ring_buffer_t )
{
	uint16_t head;
	uint16_t tail;
    uint16_t entry_count;
    uint16_t max_entry_count;
};

void nrf51_tag_database_sys_evt(uint32_t sys_evt);

uint16_t nrf51_tag_db_entry_count_scan(void);

void nrf51_tag_db_initialize(void);

void nrf51_tag_db_erase(void);

uint8_t nrf51_tag_db_erased(void);

uint16_t nrf51_tag_db_entry_count(void);

uint16_t nrf51_tag_db_max_entry_count(void);

uint16_t nrf51_tag_db_ring_buffer_head(void);

uint16_t nrf51_tag_db_ring_buffer_tail(void);

void nrf51_tag_db_write_entry(ble_tag_db_entry_t* p_ble_tag_db_entry);

void nrf51_tag_db_read_entry(ble_tag_db_entry_t* p_ble_tag_db_entry);

void nrf51_tag_db_write_sector(uint8_t page_number);

void nrf51_tag_db_read_sector(uint8_t page_number, uint8_t* p_data, uint16_t length);

static const uint16_t MAX_DB_PAGE_NUMBER = DB_PAGE_END - DB_PAGE_START;

static const uint16_t MAX_DB_ENTRIES_PER_PAGE = (CODE_PAGE_SIZE / sizeof(ble_tag_db_entry_t));

#define MAX_DB_ENTRIES (MAX_DB_ENTRIES_PER_PAGE * DB_PAGE_MAX)
#define MAX_DB_RECORDS (MAX_DB_ENTRIES * MAX_DB_RECORDS_PER_ENTRY)

#define DB_ENTRY_LENGTH_32 ( sizeof(ble_tag_db_entry_t) / sizeof(uint32_t) )

#define DB_SECTOR_START(x_num) ( ( (x_num) + (MAX_DB_ENTRIES_PER_PAGE-1) ) &~ (MAX_DB_ENTRIES_PER_PAGE-1) )

#define DB_CMD_IDLE        0x00
#define DB_CMD_ERASE_DB    0x01
#define DB_CMD_ERASE_PAGE  0x02
#define DB_CMD_WRITE_ENTRY 0x03

// ------------------------------------------------------------------------------------------------
// Debug Message(s)
// ------------------------------------------------------------------------------------------------
#define ENABLE_INITIALIZE_DB_MESSAGES

#if defined(ENABLE_INITIALIZE_DB_MESSAGES)

#define ENABLE_DB_INITIALIZE
#define ENABLE_DB_RING_BUFFER
#define ENABLE_DB_WRITE_ADDRESS
#define ENABLE_DB_READ_ADDRESS

#ifdef ENABLE_DB_INITIALIZE
#define DBG_DB_INITIALIZE() FUNCTION() \
    DBG("--> (DB_ADDRESS_END - DB_ADDRESS_START): 0x%x, %d\r\n", (DB_ADDRESS_END - DB_ADDRESS_START), (DB_ADDRESS_END - DB_ADDRESS_START) ); \
    DBG("--> MAX_DB_PAGE_NUMBER     : %d\r\n", MAX_DB_PAGE_NUMBER); \
    DBG("--> MAX_DB_ENTRIES_PER_PAGE: %d\r\n", MAX_DB_ENTRIES_PER_PAGE); \
    DBG("--> DB_ENTRY_LENGTH_32: %d\r\n", DB_ENTRY_LENGTH_32); \
    DBG("--> MAX_DB_ENTRIES    : %d\r\n", MAX_DB_ENTRIES); \
    DBG("--> MAX_DB_RECORDS    : %d\r\n", MAX_DB_RECORDS)
#else
#define DBG_DB_INITIALIZE()
#endif

#ifdef ENABLE_DB_RING_BUFFER
#define DB_RING_BUFFER(x_db_ring_buffer) \
    DBG("--> head: %d\r\n", x_db_ring_buffer.head); \
    DBG("--> tail: %d\r\n", x_db_ring_buffer.tail); \
    DBG("--> entry count: %d\r\n", x_db_ring_buffer.entry_count)
#else
#define DB_RING_BUFFER(x_db_ring_buffer)
#endif

#ifdef ENABLE_DB_WRITE_ADDRESS
#define DBG_DB_WRITE_ADDRESS(x_addr) \
    DBG("--> Tag Db, Write Address: 0x%x\r\n", x_addr)
#else
#define DBG_DB_WRITE_ADDRESS(x_addr)
#endif

#ifdef ENABLE_DB_READ_ADDRESS
#define DBG_DB_READ_ADDRESS(x_addr) \
    DBG("--> Tag Db, Read Address: 0x%x\r\n", x_addr)
#else
#define DBG_DB_READ_ADDRESS(x_addr)
#endif

#else

#define DBG_DB_INITIALIZE()

#define DB_RING_BUFFER(x_db_ring_buffer)

#define DBG_DB_WRITE_ADDRESS(x_addr)
#define DBG_DB_READ_ADDRESS(x_addr)

#endif

#ifdef __cplusplus
}
#endif
