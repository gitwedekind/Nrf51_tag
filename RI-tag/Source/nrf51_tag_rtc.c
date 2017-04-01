/**
* @file nrf51_tag_rtc.c
* @brief Header file for tag RTC.
 */

#include "nrf51_tag_error.h"
#include "nrf51_tag_spi0_lis3dh.h"
#include "nrf51_tag_rtc.h"

//-------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------

static uint32_t s_system_uptime = 0;

void nrf51_tag_system_uptime_callback(void)
{
    ++s_system_uptime;
#if 0    
    uint8_t tx_data[LIS3DH_CMD_LENGTH] = {0x00, 0x00};
    uint8_t rx_data[LIS3DH_CMD_LENGTH] = {0x00, 0x00};

    LIS3DH_CMD(tx_data, LIS3DH_OUT_X_L, LIS3DH_READ, 0);
    nrf51_tag_spi_lis3dh_cmd(tx_data, rx_data);
    DBG("--> LIS3DH_OUT_X_L: 0x%02x\r\n", rx_data[LIS3DH_CMD_INDEX_1]);

    LIS3DH_CMD(tx_data, LIS3DH_OUT_X_H, LIS3DH_READ, 0);
    nrf51_tag_spi_lis3dh_cmd(tx_data, rx_data);
    DBG("--> LIS3DH_OUT_X_H: 0x%02x\r\n", rx_data[LIS3DH_CMD_INDEX_1]);

    LIS3DH_CMD(tx_data, LIS3DH_OUT_X_L, LIS3DH_READ, 0);
    nrf51_tag_spi_lis3dh_cmd(tx_data, rx_data);
    DBG("--> LIS3DH_OUT_X_L: 0x%02x\r\n", rx_data[LIS3DH_CMD_INDEX_1]);

    LIS3DH_CMD(tx_data, LIS3DH_OUT_X_H, LIS3DH_READ, 0);
    nrf51_tag_spi_lis3dh_cmd(tx_data, rx_data);
    DBG("--> LIS3DH_OUT_X_H: 0x%02x\r\n", rx_data[LIS3DH_CMD_INDEX_1]);
    LIS3DH_CMD(tx_data, LIS3DH_OUT_X_L, LIS3DH_READ, 0);
    nrf51_tag_spi_lis3dh_cmd(tx_data, rx_data);
    DBG("--> LIS3DH_OUT_X_L: 0x%02x\r\n", rx_data[LIS3DH_CMD_INDEX_1]);

    LIS3DH_CMD(tx_data, LIS3DH_OUT_X_H, LIS3DH_READ, 0);
    nrf51_tag_spi_lis3dh_cmd(tx_data, rx_data);
    DBG("--> LIS3DH_OUT_X_H: 0x%02x\r\n", rx_data[LIS3DH_CMD_INDEX_1]);
#endif

#if 0    
    LIS3DH_CMD(tx_data, LIS3DH_OUT_ADC3_L, LIS3DH_READ, 0);
    nrf51_tag_spi_lis3dh_cmd(tx_data, rx_data);
    DBG("--> LIS3DH_OUT_ADC3_L: 0x%02x\r\n", rx_data[LIS3DH_CMD_INDEX_1]);

    LIS3DH_CMD(tx_data, LIS3DH_OUT_ADC3_H, LIS3DH_READ, 0);
    nrf51_tag_spi_lis3dh_cmd(tx_data, rx_data);
    DBG("--> LIS3DH_OUT_ADC3_H: 0x%02x\r\n", rx_data[LIS3DH_CMD_INDEX_1]);
#endif
}

uint32_t nrf51_tag_get_system_uptime(void)
{
    return s_system_uptime;
}
