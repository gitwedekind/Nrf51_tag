/**
* @file nrf51_tag_db.c
* @brief Header file for Tag Database.
*
*/

#include "nrf51_tag_error.h"
#include "nrf51_tag_db.h"

static ble_tag_db_ring_buffer_t s_db_ring_buffer =
{
    0,
    0,
    0,
};

static __align(4) ble_tag_db_entry_t s_db_entry = {0};

static uint8_t s_erase_database_page_number = 0;

static uint8_t s_database_erased = 0;
static uint8_t s_database_page_erased = 0;
static uint8_t s_database_write_complete = 0;

static uint16_t s_database_write_count = 0;

#define DB_CMD_IDLE        0x00
#define DB_CMD_ERASE_DB    0x01
#define DB_CMD_ERASE_PAGE  0x02
#define DB_CMD_WRITE_ENTRY 0x03

static uint8_t s_db_command = DB_CMD_IDLE;

const uint32_t DB_ENTRY_LENGTH_32 = sizeof(ble_tag_db_entry_t) / sizeof(uint32_t);
const uint16_t MAX_DB_PAGE_NUMBER = DB_PAGE_END - DB_PAGE_START;

#define MAX_DB_ENTRIES_PER_PAGE (CODE_PAGE_SIZE / sizeof(ble_tag_db_entry_t))
#define MAX_DB_ENTRIES ((DB_ADDRESS_END - DB_ADDRESS_START) / sizeof(ble_tag_db_entry_t))
#define MAX_DB_RECORDS (MAX_DB_ENTRIES * MAX_DB_RECORDS_PER_ENTRY)

static uint8_t nrf51_tag_db_entry_empty(uint32_t* p_entry_address)
{
    memcpy(&s_db_entry, p_entry_address, sizeof(ble_tag_db_entry_t));
        
    return s_db_entry.timestamp == FLASH_BLANK_VALUE ? 1 : 0;
}

static uint16_t nrf51_tag_db_find_tail(void)
{
    uint16_t tail = 0;
    
    uint32_t* p_entry_address = (uint32_t*)DB_ADDRESS_START;

    while ( p_entry_address < (uint32_t*)DB_ADDRESS_END )
    {
        if ( !nrf51_tag_db_entry_empty(p_entry_address) )
        {
            break;
        }
        
        p_entry_address += DB_ENTRY_LENGTH_32;
        
        ++tail;
    }
    
    return tail;
}

static uint16_t nrf51_tag_db_entry_count_scan(void)
{
    s_db_ring_buffer.head = 0;
    s_db_ring_buffer.tail = 0;
    
    s_db_ring_buffer.entry_count = 0;

    uint32_t* p_entry_address = (uint32_t*)DB_ADDRESS_START;

    while ( p_entry_address < (uint32_t*)DB_ADDRESS_END )
    {
        if ( !nrf51_tag_db_entry_empty(p_entry_address) )
        {
            ++s_db_ring_buffer.entry_count;
        }
        
        p_entry_address += DB_ENTRY_LENGTH_32;
    }
    
    if ( s_db_ring_buffer.entry_count != 0 )
    {
        s_db_ring_buffer.tail = nrf51_tag_db_find_tail();
        s_db_ring_buffer.head = s_db_ring_buffer.tail + s_db_ring_buffer.entry_count; 
    }
    
    DB_RING_BUFFER(s_db_ring_buffer);
    
    return s_db_ring_buffer.entry_count;
}

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
    
    s_erase_database_page_number = DB_PAGE_START;
    
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
    
    //nrf51_tag_db_erase();

    nrf51_tag_db_entry_count_scan();
}

uint16_t nrf51_tag_db_entry_count(void)
{
    return s_db_ring_buffer.entry_count;
}

void nrf51_tag_db_write_entry(ble_tag_db_entry_t* p_ble_tag_db_entry)
{
    uint32_t* p_write_address = (uint32_t*)(DB_ADDRESS_START + (sizeof(ble_tag_db_entry_t) * s_db_ring_buffer.head));
    
    if ( nrf51_tag_db_entry_empty(p_write_address) )
    {
        DBG("--> s_p_write_address: 0x%x\r\n", p_write_address);
        
        s_db_command = DB_CMD_WRITE_ENTRY;
        s_database_write_complete = 0;
        
        uint32_t err_code = sd_flash_write(p_write_address, (uint32_t*)p_ble_tag_db_entry, DB_ENTRY_LENGTH_32);
        APP_ERROR_CHECK(err_code);
        
        ++s_db_ring_buffer.head;
        
        if ( s_db_ring_buffer.head >= MAX_DB_ENTRIES )
        {
            s_db_ring_buffer.head = 0;
        }
    }
}

void nrf51_tag_db_read_entry(ble_tag_db_entry_t* p_ble_tag_db_entry)
{
    if ( s_db_ring_buffer.head != s_db_ring_buffer.tail )
    {
        uint32_t* p_read_address = (uint32_t*)(DB_ADDRESS_START + (sizeof(ble_tag_db_entry_t) * s_db_ring_buffer.tail));
        
        DBG("--> p_read_address: 0x%x\r\n", p_read_address);
            
        memcpy(p_ble_tag_db_entry, p_read_address, sizeof(ble_tag_db_entry_t));
        
        ++s_db_ring_buffer.tail;
        
        if ( s_db_ring_buffer.tail >= MAX_DB_ENTRIES )
        {
            s_db_ring_buffer.tail = 0;
        }

        uint32_t page_number = 0;

        if ( s_db_ring_buffer.head == s_db_ring_buffer.tail )
        {
            page_number = DB_PAGE_START + (s_db_ring_buffer.tail / MAX_DB_ENTRIES_PER_PAGE);
            
            s_db_ring_buffer.head = s_db_ring_buffer.tail = (s_db_ring_buffer.tail / MAX_DB_ENTRIES_PER_PAGE);
        }
        else if ( !(s_db_ring_buffer.tail % MAX_DB_ENTRIES_PER_PAGE) )
        {
            page_number = DB_PAGE_END;
            
            if ( s_db_ring_buffer.tail != 0 )
            {
                uint32_t p_tail_address = (uint32_t)(DB_ADDRESS_START + (sizeof(ble_tag_db_entry_t) * (s_db_ring_buffer.tail-1)));
                
                page_number = p_tail_address / CODE_PAGE_SIZE;
            }
        }
        
        if ( page_number != 0 )
        {
            s_db_command = DB_CMD_ERASE_PAGE;
            s_database_page_erased = 0;
            
            sd_flash_page_erase(page_number);
        }
    }
    else
    {
        memset(p_ble_tag_db_entry, 0xFF, sizeof(ble_tag_db_entry_t));
    }
}
