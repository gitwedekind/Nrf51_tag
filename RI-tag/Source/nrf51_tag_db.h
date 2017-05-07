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

#pragma pack()

typedef struct ble_tag_db_activity_read_record_t ble_tag_db_activity_read_record_t;
struct ble_tag_db_activity_read_record_t
{
    uint32_t timestamp;
    uint16_t x;
    uint16_t y;
    uint16_t z;
};

#pragma pack()


typedef struct ble_tag_db_ring_buffer_t ble_tag_db_ring_buffer_t;
struct ble_tag_db_ring_buffer_t
{
    uint16_t head;
    uint16_t tail;
    uint16_t entry_count;
};

void nrf51_tag_database_sys_evt(uint32_t sys_evt);

void nrf51_tag_db_initialize(void);

void nrf51_tag_db_erase(void);

uint8_t nrf51_tag_db_erased(void);

uint16_t nrf51_tag_db_entry_count(void);

void nrf51_tag_db_write_entry(ble_tag_db_activity_read_record_t* p_db_activity_read_record);

void nrf51_tag_db_read_entry(ble_tag_db_activity_read_record_t* p_db_activity_read_record, uint16_t length);

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
