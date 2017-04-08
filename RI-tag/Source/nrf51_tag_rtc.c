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
    
    if ( s_system_uptime % 5)
        return;
    
#if 0
    uint8_t tx_data[LIS3DH_CMD_LENGTH] = {0x00, 0x00};
    uint8_t rx_data[LIS3DH_CMD_LENGTH] = {0x00, 0x00};
    
    LIS3DH_RAW_CONVERTER_T x, y, z;
    
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
    
    LIS3DH_CMD(tx_data, LIS3DH_STATUS_REG_r, LIS3DH_READ, 0);
    nrf51_tag_spi_lis3dh_cmd(tx_data, rx_data);
    uint8_t status_pre = rx_data[LIS3DH_CMD_DATA_INDEX_1];

    LIS3DH_CMD(tx_data, LIS3DH_STATUS_REG_r, LIS3DH_READ, 0);
    nrf51_tag_spi_lis3dh_cmd(tx_data, rx_data);
    uint8_t status_post = rx_data[LIS3DH_CMD_DATA_INDEX_1];

    LIS3DH_CMD(tx_data, LIS3DH_INT1_SRC_r, LIS3DH_READ, 0);
    nrf51_tag_spi_lis3dh_cmd(tx_data, rx_data);
    uint8_t int_src = rx_data[LIS3DH_CMD_DATA_INDEX_1];

    x.raw = MAKE_U16(xl,xh);
    y.raw = MAKE_U16(yl,yh);
    z.raw = MAKE_U16(zl,zh);
 
 #if 1   
    DBG("%d, %d, %d, 0x%02x 0x%02x 0x%02x\r\n", 
        x.highPower.value, 
        y.highPower.value, 
        z.highPower.value, 
        int_src, 
        status_pre, 
        status_post);
 #endif
#endif

}

uint32_t nrf51_tag_get_system_uptime(void)
{
    return s_system_uptime;
}
