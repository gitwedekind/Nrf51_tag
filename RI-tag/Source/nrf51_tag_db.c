/**
* @file nrf51_tag_db.c
* @brief Header file for Tag Database.
*
*/

#include "nrf51_tag_error.h"
#include "nrf51_tag_db.h"

#ifdef __cplusplus
extern "C" {
#endif

#define CRC8_TABLE_LENGTH 256 ///< 8-bit CRC table size

/* 8-bit CRC Lookup table
*/
static const uint8_t crc8_table[CRC8_TABLE_LENGTH] =
{
	0x00, 0x07, 0x0e, 0x09, 0x1c, 0x1b, 0x12, 0x15,
	0x38, 0x3f, 0x36, 0x31, 0x24, 0x23, 0x2a, 0x2d,
	0x70, 0x77, 0x7e, 0x79, 0x6c, 0x6b, 0x62, 0x65,
	0x48, 0x4f, 0x46, 0x41, 0x54, 0x53, 0x5a, 0x5d,
	0xe0, 0xe7, 0xee, 0xe9, 0xfc, 0xfb, 0xf2, 0xf5,
	0xd8, 0xdf, 0xd6, 0xd1, 0xc4, 0xc3, 0xca, 0xcd,
	0x90, 0x97, 0x9e, 0x99, 0x8c, 0x8b, 0x82, 0x85,
	0xa8, 0xaf, 0xa6, 0xa1, 0xb4, 0xb3, 0xba, 0xbd,
	0xc7, 0xc0, 0xc9, 0xce, 0xdb, 0xdc, 0xd5, 0xd2,
	0xff, 0xf8, 0xf1, 0xf6, 0xe3, 0xe4, 0xed, 0xea,
	0xb7, 0xb0, 0xb9, 0xbe, 0xab, 0xac, 0xa5, 0xa2,
	0x8f, 0x88, 0x81, 0x86, 0x93, 0x94, 0x9d, 0x9a,
	0x27, 0x20, 0x29, 0x2e, 0x3b, 0x3c, 0x35, 0x32,
	0x1f, 0x18, 0x11, 0x16, 0x03, 0x04, 0x0d, 0x0a,
	0x57, 0x50, 0x59, 0x5e, 0x4b, 0x4c, 0x45, 0x42,
	0x6f, 0x68, 0x61, 0x66, 0x73, 0x74, 0x7d, 0x7a,
	0x89, 0x8e, 0x87, 0x80, 0x95, 0x92, 0x9b, 0x9c,
	0xb1, 0xb6, 0xbf, 0xb8, 0xad, 0xaa, 0xa3, 0xa4,
	0xf9, 0xfe, 0xf7, 0xf0, 0xe5, 0xe2, 0xeb, 0xec,
	0xc1, 0xc6, 0xcf, 0xc8, 0xdd, 0xda, 0xd3, 0xd4,
	0x69, 0x6e, 0x67, 0x60, 0x75, 0x72, 0x7b, 0x7c,
	0x51, 0x56, 0x5f, 0x58, 0x4d, 0x4a, 0x43, 0x44,
	0x19, 0x1e, 0x17, 0x10, 0x05, 0x02, 0x0b, 0x0c,
	0x21, 0x26, 0x2f, 0x28, 0x3d, 0x3a, 0x33, 0x34,
	0x4e, 0x49, 0x40, 0x47, 0x52, 0x55, 0x5c, 0x5b,
	0x76, 0x71, 0x78, 0x7f, 0x6a, 0x6d, 0x64, 0x63,
	0x3e, 0x39, 0x30, 0x37, 0x22, 0x25, 0x2c, 0x2b,
	0x06, 0x01, 0x08, 0x0f, 0x1a, 0x1d, 0x14, 0x13,
	0xae, 0xa9, 0xa0, 0xa7, 0xb2, 0xb5, 0xbc, 0xbb,
	0x96, 0x91, 0x98, 0x9f, 0x8a, 0x8d, 0x84, 0x83,
	0xde, 0xd9, 0xd0, 0xd7, 0xc2, 0xc5, 0xcc, 0xcb,
	0xe6, 0xe1, 0xe8, 0xef, 0xfa, 0xfd, 0xf4, 0xf3
};

uint8_t nrf51_tag_crc8(uint8_t *p_data, uint32_t length)
{
	uint16_t index = 0;
	uint16_t crc = 0x0;

	while (length--)
	{
		index = (crc ^ *p_data++) & 0xFF;
		crc = (crc8_table[index] ^ (crc << 8)) & 0xFF;
	}

	return crc & 0xFF;
}

static ble_tag_db_ring_buffer_t s_db_ring_buffer =
{
    0,
    0,
    0,
	0,
};

static __align(4) ble_tag_db_entry_t s_db_entry = { 0 };

static uint8_t s_erase_database_page_number = 0;

static uint8_t s_database_erased = 0;
static uint8_t s_database_page_erased = 0;
static uint8_t s_database_write_complete = 0;

static uint16_t s_database_write_count = 0;

static uint8_t s_db_command = DB_CMD_IDLE;

static uint32_t nrf51_tag_db_flash_read(uint32_t * const p_dst, uint32_t const * const p_src, uint32_t size)
{
#ifdef WIN32
	uint32_t sd_flash_read(uint32_t * const p_dst, uint32_t const * const p_src, uint32_t size);
    sd_flash_read(p_dst, p_src, size);
#else
    memcpy(p_dst, p_src, size);
#endif
    
    return 0;
}

static uint8_t nrf51_tag_db_entry_empty(uint32_t* p_entry_address)
{
    nrf51_tag_db_flash_read((uint32_t*)&s_db_entry, p_entry_address, sizeof(ble_tag_db_entry_t));

    return s_db_entry.timestamp == FLASH_BLANK_VALUE ? 1 : 0;
}

static uint16_t nrf51_tag_db_find_tail(void)
{
    uint16_t tail = 0;

    uint32_t* p_entry_address = (uint32_t*)DB_ADDRESS_START;

    while (p_entry_address < (uint32_t*)DB_ADDRESS_END)
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

static uint8_t nrf51_tag_db_head_slot_empty(void)
{
	uint32_t* p_entry_address = (uint32_t*)(DB_ADDRESS_START + (sizeof(ble_tag_db_entry_t) * s_db_ring_buffer.head));

	return nrf51_tag_db_entry_empty(p_entry_address);
}

static uint16_t nrf51_tag_db_next_head_position(void)
{
	uint16_t head = s_db_ring_buffer.head + 1;

	if ( head > (MAX_DB_ENTRIES-1 ) )
	{
		head = 0;
	}

	return head;
}

static void nrf51_tag_db_advance_head_position(void)
{
	s_db_ring_buffer.head = nrf51_tag_db_next_head_position();
}

static void nrf51_tag_db_advance_tail_position(void)
{
	++s_db_ring_buffer.tail;

	if ( s_db_ring_buffer.tail > (MAX_DB_ENTRIES-1) )
	{
		s_db_ring_buffer.tail = 0;
	}
}

static uint8_t nrf51_tag_db_full(void)
{
	uint8_t db_full = 0;

	if ( (s_db_ring_buffer.head == s_db_ring_buffer.tail) && !nrf51_tag_db_head_slot_empty() )
	{
		db_full = 1;
	}

	return db_full;
}

static uint8_t nrf51_tag_db_empty(void)
{
	uint8_t db_empty = 0;

	if ( (s_db_ring_buffer.head == s_db_ring_buffer.tail) && nrf51_tag_db_head_slot_empty() )
	{
		db_empty = 1;
	}

	return db_empty;
}

uint16_t nrf51_tag_db_entry_count_scan(void)
{
    s_db_ring_buffer.head = 0;
    s_db_ring_buffer.tail = 0;

    s_db_ring_buffer.entry_count     = 0;
    s_db_ring_buffer.max_entry_count = 0;

    uint32_t* p_entry_address = (uint32_t*)DB_ADDRESS_START;

    while (p_entry_address < (uint32_t*)DB_ADDRESS_END)
    {
        if (!nrf51_tag_db_entry_empty(p_entry_address))
        {
            ++s_db_ring_buffer.entry_count;
        }
        
        ++s_db_ring_buffer.max_entry_count;

        p_entry_address += DB_ENTRY_LENGTH_32;
    }

    if (s_db_ring_buffer.entry_count != 0)
    {
        s_db_ring_buffer.tail = nrf51_tag_db_find_tail();
        s_db_ring_buffer.head = s_db_ring_buffer.tail + s_db_ring_buffer.entry_count;
    }

    DB_RING_BUFFER(s_db_ring_buffer);

    return s_db_ring_buffer.entry_count;
}

uint8_t nrf51_tag_get_db_cmd(void)
{
	return s_db_command;
}

void nrf51_tag_database_sys_evt(uint32_t sys_evt)
{
    if (sys_evt == NRF_EVT_FLASH_OPERATION_SUCCESS)
    {
        if (s_db_command == DB_CMD_ERASE_DB)
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
        else if (s_db_command == DB_CMD_ERASE_PAGE)
        {
            s_database_page_erased = 1;
            s_db_command = DB_CMD_IDLE;
            DBG("--> Db Page Erased: %d\r\n", s_erase_database_page_number);
        }
        else if (s_db_command == DB_CMD_WRITE_ENTRY)
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
	if ( nrf51_tag_db_empty() )
	{
		s_db_ring_buffer.entry_count = 0;
	}
	else if ( nrf51_tag_db_full() )
	{
		s_db_ring_buffer.entry_count = MAX_DB_ENTRIES;
	}
	else
	{
		if ( s_db_ring_buffer.head > s_db_ring_buffer.tail )
		{
			s_db_ring_buffer.entry_count = s_db_ring_buffer.head - s_db_ring_buffer.tail;
		}
		else
		{
			s_db_ring_buffer.entry_count = (s_db_ring_buffer.head) + (MAX_DB_ENTRIES - s_db_ring_buffer.tail);
		}
	}

	return s_db_ring_buffer.entry_count;
}

uint16_t nrf51_tag_db_max_entry_count(void)
{
    return s_db_ring_buffer.max_entry_count;
}

uint16_t nrf51_tag_db_ring_buffer_head(void)
{
    return s_db_ring_buffer.head;
}

uint16_t nrf51_tag_db_ring_buffer_tail(void)
{
    return s_db_ring_buffer.tail;
}

void nrf51_tag_db_write_entry(ble_tag_db_entry_t* p_ble_tag_db_entry)
{
    if ( !nrf51_tag_db_full() )
    {
		uint32_t* p_write_address = (uint32_t*)(DB_ADDRESS_START + (sizeof(ble_tag_db_entry_t) * s_db_ring_buffer.head));

		DBG("--> s_p_write_address: 0x%x\r\n", p_write_address);

        s_db_command = DB_CMD_WRITE_ENTRY;
        s_database_write_complete = 0;

		// Note: sd_flash_write() needs size as the number of 32-bit words
		//
        uint32_t err_code = sd_flash_write(p_write_address, (uint32_t*)p_ble_tag_db_entry, DB_ENTRY_LENGTH_32);
        APP_ERROR_CHECK(err_code);

		nrf51_tag_db_advance_head_position();
    }
}

void nrf51_tag_db_read_entry(ble_tag_db_entry_t* p_ble_tag_db_entry)
{
    if ( !nrf51_tag_db_empty() )
    {
        uint32_t* p_read_address = (uint32_t*)(DB_ADDRESS_START + (sizeof(ble_tag_db_entry_t) * s_db_ring_buffer.tail));

        nrf51_tag_db_flash_read((uint32_t*)p_ble_tag_db_entry, p_read_address, sizeof(ble_tag_db_entry_t));

		nrf51_tag_db_advance_tail_position();

		if ( !(s_db_ring_buffer.tail % MAX_DB_ENTRIES_PER_PAGE) )
		{
			uint32_t page_number = DB_PAGE_END;

			if ( s_db_ring_buffer.tail != 0 )
			{
				uint32_t p_tail_address = (uint32_t)(DB_ADDRESS_START + (sizeof(ble_tag_db_entry_t) * (s_db_ring_buffer.tail - 1)));

				page_number = p_tail_address / CODE_PAGE_SIZE;
			}

			s_db_command = DB_CMD_ERASE_PAGE;
			s_database_page_erased = 0;

			sd_flash_page_erase(page_number);
			DBG("--> page %d erased, head: %d, tail: %d\r\n", page_number, s_db_ring_buffer.head, s_db_ring_buffer.tail);
		}

        DBG("--> nrf51_tag_db_read_entry(): head: %d, tail: %d\r\n", s_db_ring_buffer.head, s_db_ring_buffer.tail);
        DBG("--> p_read_address: 0x%x\r\n", p_read_address);
    }
    else
    {
        memset(p_ble_tag_db_entry, 0, sizeof(ble_tag_db_entry_t));

		uint32_t nrf51_tag_get_system_uptime(void);
		p_ble_tag_db_entry->timestamp = nrf51_tag_get_system_uptime();
    }
}

#ifdef __cplusplus
}
#endif
