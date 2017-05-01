/**
* @file nrf51_tag_db.c
* @brief Header file for Tag Database.
*
*/

#include "nrf51_tag_error.h"
#include "nrf51_tag_db.h"

static uint8_t s_erase_database_page_number = 0;

static uint8_t s_database_erased = 0;
static uint8_t s_database_page_erased = 0;
static uint8_t s_database_write_complete = 0;

static uint16_t s_database_write_count = 0;

static uint32_t* s_p_write_address = 0;

#define DB_CMD_IDLE        0x00
#define DB_CMD_ERASE_DB    0x01
#define DB_CMD_ERASE_PAGE  0x02
#define DB_CMD_WRITE_ENTRY 0x03

static uint8_t s_db_command = DB_CMD_IDLE;

void nrf51_tag_database_sys_evt(uint32_t sys_evt)
{
    if ( sys_evt == NRF_EVT_FLASH_OPERATION_SUCCESS)
    {
        if ( s_db_command == DB_CMD_ERASE_DB )
        {
            ++s_erase_database_page_number;
            
            if (s_erase_database_page_number <= DB_PAGE_END)
            {
                sd_flash_page_erase(s_erase_database_page_number);
            }
            else
            {
                s_database_erased = 1;
                s_db_command = DB_CMD_IDLE;
                DBG("--> Db Erased\r\n");
            }
        }
        else if ( s_db_command == DB_CMD_ERASE_PAGE )
        {
            s_database_page_erased = 1;
            s_db_command = DB_CMD_IDLE;
            DBG("--> Db Page Erased: %d\r\n", s_erase_database_page_number);
        }
        else if ( s_db_command == DB_CMD_WRITE_ENTRY )
        {
            ++s_database_write_count;
            s_database_write_complete = 1;
            s_db_command = DB_CMD_IDLE;
            DBG("--> Db Write Complete: count:%d\r\n", s_database_write_count);
        }
    }
}

void nrf51_tag_db_erase(void)
{
    s_database_erased = 0;
    
    s_db_command = DB_CMD_ERASE_DB;
    
    s_erase_database_page_number = DB_PAGE_START;
    
    sd_flash_page_erase(s_erase_database_page_number);
}

uint8_t nrf51_tag_db_erased(void)
{
    return s_database_erased;
}

void nrf51_tag_db_initialize(void)
{
    DBG_DB_INITIALIZE();
    
    s_database_erased = 0;
    
    s_erase_database_page_number = DB_PAGE_START;
    
    ble_tag_entry_info_t entry_info = nrf51_tag_db_record_count();
    DBG_DB_RECORDS(entry_info);
    
    //nrf51_tag_db_erase();

    s_p_write_address = (uint32_t*)(CODE_PAGE_SIZE * DB_PAGE_START);
    
    const uint32_t length = sizeof(ble_tag_db_entry_t) / sizeof(uint32_t);
    
    s_p_write_address += (length * (entry_info.active_records / MAX_DB_RECORDS));
    DBG_DB_WRITE_ADDRESS(s_p_write_address);
}

ble_tag_entry_info_t nrf51_tag_db_page_record_count(uint16_t page_number)
{
    uint8_t page_entry_number = 0;
    ble_tag_entry_info_t page_entry_info = {0};
    
    const uint16_t MAX_PAGE_ENTRY_NUMBER = CODE_PAGE_SIZE / sizeof(ble_tag_db_entry_t);
    
    const uint32_t length = sizeof(ble_tag_db_entry_t) / sizeof(uint32_t);

    ble_tag_db_entry_t db_entry = {0};

    uint32_t* p_page_address = (uint32_t*)(CODE_PAGE_SIZE * page_number);

    uint32_t* p_entry_address = p_page_address;
    
    for (page_entry_number = 0; page_entry_number < MAX_PAGE_ENTRY_NUMBER; ++page_entry_number)
    {
        memcpy(&db_entry, p_entry_address, sizeof(ble_tag_entry_info_t));
        
        if ( db_entry.timestamp != FLASH_BLANK_VALUE )
        {
            page_entry_info.active_records += MAX_DB_RECORDS;
        }
        
        p_entry_address += length;
        
        page_entry_info.total_records += MAX_DB_RECORDS;
    }
    
    return page_entry_info;
}

ble_tag_entry_info_t nrf51_tag_db_record_count(void)
{
    uint8_t page_number = 0;
    ble_tag_entry_info_t entry_info = {0};

    for (page_number = DB_PAGE_START; page_number <= DB_PAGE_END; ++page_number)
    {
        ble_tag_entry_info_t page_entry_info = nrf51_tag_db_page_record_count(page_number);
        
        entry_info.total_records += page_entry_info.total_records;
        entry_info.active_records += page_entry_info.active_records;
    }
    
    return entry_info;
}

void nrf51_tag_db_write_entry(ble_tag_db_entry_t* p_ble_tag_db_entry)
{
    uint32_t length = sizeof(ble_tag_db_entry_t) / sizeof(uint32_t);
    
    DBG("--> s_p_write_address: 0x%x, data: 0x%x, len: %d\r\n", s_p_write_address, (uint32_t*)p_ble_tag_db_entry, length);
    
    uint32_t err_code = sd_flash_write(s_p_write_address, (uint32_t*)p_ble_tag_db_entry, length);
    APP_ERROR_CHECK(err_code);
    
    s_p_write_address += length;
}

void nrf51_tag_db_read_record(ble_tag_status_activity_read_records_t* p_ble_tag_status_activity_read_records)
{
}
