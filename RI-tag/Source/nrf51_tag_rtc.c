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
    
    uint8_t xl, yl, zl;
    uint8_t xh, yh, zh;

    LIS3DH_CMD(tx_data, LIS3DH_OUT_X_L_r, LIS3DH_READ, 0);
    nrf51_tag_spi_lis3dh_cmd(tx_data, rx_data);
    xl = rx_data[LIS3DH_CMD_DATA_INDEX_1];
    
    LIS3DH_CMD(tx_data, LIS3DH_OUT_Y_L_r, LIS3DH_READ, 0);
    nrf51_tag_spi_lis3dh_cmd(tx_data, rx_data);
    yl = rx_data[LIS3DH_CMD_DATA_INDEX_1];

    LIS3DH_CMD(tx_data, LIS3DH_OUT_Z_L_r, LIS3DH_READ, 0);
    nrf51_tag_spi_lis3dh_cmd(tx_data, rx_data);
    zl = rx_data[LIS3DH_CMD_DATA_INDEX_1];

    LIS3DH_CMD(tx_data, LIS3DH_OUT_X_H_r, LIS3DH_READ, 0);
    nrf51_tag_spi_lis3dh_cmd(tx_data, rx_data);
    xh = rx_data[LIS3DH_CMD_DATA_INDEX_1];
    
    LIS3DH_CMD(tx_data, LIS3DH_OUT_Y_H_r, LIS3DH_READ, 0);
    nrf51_tag_spi_lis3dh_cmd(tx_data, rx_data);
    yh = rx_data[LIS3DH_CMD_DATA_INDEX_1];

    LIS3DH_CMD(tx_data, LIS3DH_OUT_Z_H_r, LIS3DH_READ, 0);
    nrf51_tag_spi_lis3dh_cmd(tx_data, rx_data);
    zh = rx_data[LIS3DH_CMD_DATA_INDEX_1];

    DBG("--> X,Y,Z: %04x:%04x:%04x\r\n", MAKE_U16(xl,xh), MAKE_U16(yl,yh), MAKE_U16(zl,zh));
#endif
}

uint32_t nrf51_tag_get_system_uptime(void)
{
    return s_system_uptime;
}
