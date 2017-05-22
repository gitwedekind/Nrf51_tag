/**
* @file nrf51_tag_flash.h
* @brief Header file for Raw Flash Commands.
*
*/

#pragma once

#include "nrf51_tag_headers.h"

#ifdef __cplusplus
extern "C" {
#endif

	//-----------------------------------------------------------------------------
	// Interface Functions
	//-----------------------------------------------------------------------------

#define CODE_PAGE_SIZE 0x400 

	static const uint32_t FLASH_BLANK_VALUE = 0xFFFFFFFF;

	static const uint8_t FLASH_BYTE_ERASED = 0xFF;

	static uint8_t const * const SOFT_DEVICE_ADDRESS_START = (uint8_t*)0x00000000;
	static uint8_t const * const SOFT_DEVICE_ADDRESS_END = (uint8_t*)0x0001AC00 + (CODE_PAGE_SIZE-1);

	static const uint8_t SOFT_DEVICE_PAGE_START = 0;
	static const uint8_t SOFT_DEVICE_PAGE_END = 107;

	static uint8_t const * const PROGRAM_ADDRESS_START = (uint8_t*)0x0001B000;
	static uint8_t const * const PROGRAM_ADDRESS_END = (uint8_t*)0x00024C00 + (CODE_PAGE_SIZE - 1);

	static const uint8_t PROGRAM_PAGE_START = 108;
	static const uint8_t PROGRAM_PAGE_END = 147;

	static uint8_t const * const DB_ADDRESS_START = (uint8_t*)0x00025000;
	static uint8_t const * const DB_ADDRESS_END = (uint8_t*)0x0003BC00 + (CODE_PAGE_SIZE - 1);

	enum DbPage_t
	{
		DB_PAGE_START = 148,
		DB_PAGE_END = 239
	};

	static const uint32_t DB_PAGE_MAX = (DB_PAGE_END - DB_PAGE_START) + 1;
	
	#define DB_SIZE (DB_PAGE_MAX * CODE_PAGE_SIZE)

	static uint8_t const * const GP0_BLOCK_ADDRESS = (uint8_t*)0x0003C000;
	static uint8_t const * const GP1_BLOCK_ADDRESS = (uint8_t*)0x0003C400;
	static uint8_t const * const GP2_BLOCK_ADDRESS = (uint8_t*)0x0003C800;
	static uint8_t const * const GP3_BLOCK_ADDRESS = (uint8_t*)0x0003CC00;
	static uint8_t const * const GP4_BLOCK_ADDRESS = (uint8_t*)0x0003D000;
	static uint8_t const * const GP5_BLOCK_ADDRESS = (uint8_t*)0x0003D400;
	static uint8_t const * const GP6_BLOCK_ADDRESS = (uint8_t*)0x0003D800;
	static uint8_t const * const GP7_BLOCK_ADDRESS = (uint8_t*)0x0003DC00;

	static const uint8_t GP0_PAGE = 240;
	static const uint8_t GP1_PAGE = 241;
	static const uint8_t GP2_PAGE = 242;
	static const uint8_t GP3_PAGE = 243;
	static const uint8_t GP4_PAGE = 244;
	static const uint8_t GP5_PAGE = 245;
	static const uint8_t GP6_PAGE = 246;
	static const uint8_t GP7_PAGE = 247;

	static uint8_t const * const BOOTLOADER_ADDRESS_START = (uint8_t*)0x0003E000;
	static uint8_t const * const BOOTLOADER_ADDRESS_END   = (uint8_t*)0x0003FFFF;

	static const uint8_t BOOTLOADER_PAGE_START = 248;
	static const uint8_t BOOTLOADER_PAGE_END = 255;

	//-----------------------------------------------------------------------------
	// Interface Functions
	//-----------------------------------------------------------------------------

	void nrf51_tag_flash_page_erase(uint32_t page_number);

#ifdef __cplusplus
}
#endif
