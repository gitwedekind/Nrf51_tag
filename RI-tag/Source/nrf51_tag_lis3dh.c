/** 
 * @file nrf51)tag_lis3dh.c
 *
 */

#include "nrf51_tag_error.h"
#include "nrf51_tag_lis3dh.h"

/**
*/
static uint8_t s_lis3dh_ready = 0;

// ------------------------------------------------------------------------------------------------
// static Module Interface Functions
// ------------------------------------------------------------------------------------------------

/**
 * GPIOTE_IRQHandler()
 *
 *  GPIOTE interrupt handler - Triggered on pin DTX_NRF_REQ change
 *
 */
void GPIOTE_IRQHandler_LIS3DH(void)
{
    if ( s_lis3dh_ready )
    {
        uint8_t tx_data[LIS3DH_CMD_LENGTH] = {0x00, 0x00};
        uint8_t rx_data[LIS3DH_CMD_LENGTH] = {0x00, 0x00};
    
        LIS3DH_CMD(tx_data, LIS3DH_OUT_X_L_r, LIS3DH_READ, 0);
        nrf51_tag_spi_lis3dh_cmd(tx_data, rx_data);
        DBG("--> LIS3DH_OUT_X_L_r: 0x%02x\r\n", rx_data[LIS3DH_CMD_DATA_INDEX_1]);

        LIS3DH_CMD(tx_data, LIS3DH_OUT_X_H_r, LIS3DH_READ, 0);
        nrf51_tag_spi_lis3dh_cmd(tx_data, rx_data);
        DBG("--> LIS3DH_OUT_X_H_r: 0x%02x\r\n", rx_data[LIS3DH_CMD_DATA_INDEX_1]);

        LIS3DH_CMD(tx_data, LIS3DH_OUT_X_L_r, LIS3DH_READ, 0);
        nrf51_tag_spi_lis3dh_cmd(tx_data, rx_data);
        DBG("--> LIS3DH_OUT_X_L_r: 0x%02x\r\n", rx_data[LIS3DH_CMD_DATA_INDEX_1]);

        LIS3DH_CMD(tx_data, LIS3DH_OUT_X_H_r, LIS3DH_READ, 0);
        nrf51_tag_spi_lis3dh_cmd(tx_data, rx_data);
        DBG("--> LIS3DH_OUT_X_H_r: 0x%02x\r\n", rx_data[LIS3DH_CMD_DATA_INDEX_1]);
        LIS3DH_CMD(tx_data, LIS3DH_OUT_X_L_r, LIS3DH_READ, 0);
        nrf51_tag_spi_lis3dh_cmd(tx_data, rx_data);
        DBG("--> LIS3DH_OUT_X_L_r: 0x%02x\r\n", rx_data[LIS3DH_CMD_DATA_INDEX_1]);

        LIS3DH_CMD(tx_data, LIS3DH_OUT_X_H_r, LIS3DH_READ, 0);
        nrf51_tag_spi_lis3dh_cmd(tx_data, rx_data);
        DBG("--> LIS3DH_OUT_X_H_r: 0x%02x\r\n", rx_data[LIS3DH_CMD_DATA_INDEX_1]);
    }
}

/**
 */
static uint8_t nrf51_tag_spi0_lis3dh_set_register(uint8_t reg_cmd, uint8_t reg_value)
{
    uint8_t tx_data[LIS3DH_CMD_LENGTH] = {0x00, 0x00};
    uint8_t rx_data[LIS3DH_CMD_LENGTH] = {0x00, 0x00};

    LIS3DH_CMD(tx_data, reg_cmd, LIS3DH_WRITE, reg_value);
    nrf51_tag_spi_lis3dh_cmd(tx_data, rx_data);

    LIS3DH_CMD(tx_data, reg_cmd, LIS3DH_READ, 0);
    nrf51_tag_spi_lis3dh_cmd(tx_data, rx_data);
    
    return rx_data[LIS3DH_CMD_DATA_INDEX_1];
}

/**
 */
static uint8_t nrf51_tag_spi0_lis3dh_set_feature(uint8_t reg_cmd, uint8_t reg_value)
{
    uint8_t tx_data[LIS3DH_CMD_LENGTH] = {0x00, 0x00};
    uint8_t rx_data[LIS3DH_CMD_LENGTH] = {0x00, 0x00};

    LIS3DH_CMD(tx_data, reg_cmd, LIS3DH_READ, 0);
    nrf51_tag_spi_lis3dh_cmd(tx_data, rx_data);
    
    uint8_t reg_cfg_value = rx_data[LIS3DH_CMD_DATA_INDEX_1];
    
    reg_cfg_value &= ~reg_value;

    reg_cfg_value |= reg_value;

    LIS3DH_CMD(tx_data, reg_cmd, LIS3DH_WRITE, reg_cfg_value);
    nrf51_tag_spi_lis3dh_cmd(tx_data, rx_data);

    LIS3DH_CMD(tx_data, reg_cmd, LIS3DH_READ, 0);
    nrf51_tag_spi_lis3dh_cmd(tx_data, rx_data);
    
    return rx_data[LIS3DH_CMD_DATA_INDEX_1];
}

/**
 */
static uint8_t nrf51_tag_spi0_lis3dh_clear_feature(uint8_t reg_cmd, uint8_t reg_value)
{
    uint8_t tx_data[LIS3DH_CMD_LENGTH] = {0x00, 0x00};
    uint8_t rx_data[LIS3DH_CMD_LENGTH] = {0x00, 0x00};

    LIS3DH_CMD(tx_data, reg_cmd, LIS3DH_READ, 0);
    nrf51_tag_spi_lis3dh_cmd(tx_data, rx_data);
    
    uint8_t reg_cfg_value = rx_data[LIS3DH_CMD_DATA_INDEX_1];
    
    reg_cfg_value &= ~reg_value;

    LIS3DH_CMD(tx_data, reg_cmd, LIS3DH_WRITE, reg_cfg_value);
    nrf51_tag_spi_lis3dh_cmd(tx_data, rx_data);

    LIS3DH_CMD(tx_data, reg_cmd, LIS3DH_READ, 0);
    nrf51_tag_spi_lis3dh_cmd(tx_data, rx_data);
    
    return rx_data[LIS3DH_CMD_DATA_INDEX_1];
}

/**
 */
static void nrf51_tag_spi0_lis3dh_reg_dump(void)
{
    uint8_t tx_data[LIS3DH_CMD_LENGTH] = {0x00, 0x00};
    uint8_t rx_data[LIS3DH_CMD_LENGTH] = {0x00, 0x00};

    uint32_t index = 0;
    
    for ( index = 0; index < LIS3DH_REG_COUNT; ++index)
    {
        LIS3DH_CMD(tx_data, LIS3DH_Registers[index], LIS3DH_READ, 0);
        nrf51_tag_spi_lis3dh_cmd(tx_data, rx_data);
        DBG("--> Reg: 0x%02x, Data: 0x%02x\r\n", LIS3DH_Registers[index], rx_data[LIS3DH_CMD_DATA_INDEX_1]);
    }
}

/**
 */
static uint8_t nrf51_tag_spi0_lis3dh_reset(void)
{
    uint32_t index = 0;
    uint8_t reg_value = 0;
    
    for ( index = 0; index < LIS3DH_RW_REG_COUNT; ++index)
    {
        reg_value = nrf51_tag_spi0_lis3dh_set_register(
            LIS3DH_ResetRegisters[index][LIS3DH_CMD_REG_INDEX_0], LIS3DH_ResetRegisters[index][LIS3DH_CMD_DATA_INDEX_1]);
        
        if ( reg_value != LIS3DH_ResetRegisters[index][LIS3DH_CMD_DATA_INDEX_1] )
        {
            APP_ERROR_CHECK(NRF_TAG_ERROR_LIS3DH_RESET);
        }
    }

    return index < LIS3DH_RW_REG_COUNT ? 0 : 1;
}

#if 0
/**
 */
static void nrf51_tag_spi0_lis3dh_enable_temperature(void)
{
    uint8_t tx_data[LIS3DH_CMD_LENGTH] = {0x00, 0x00};
    uint8_t rx_data[LIS3DH_CMD_LENGTH] = {0x00, 0x00};
    
    uint8_t reg_value = 0;

    reg_value = nrf51_tag_spi0_lis3dh_set_feature(LIS3DH_TEMP_CFG_REG_rw, LIS3DH_TEMPERATURE_ENABLE);
    DBG("--> LIS3DH_TEMP_CFG_REG: 0x%02x\r\n", reg_value);

    reg_value = nrf51_tag_spi0_lis3dh_set_feature(LIS3DH_TEMP_CFG_REG_rw, LIS3DH_ADC_ENABLE);
    DBG("--> LIS3DH_TEMP_CFG_REG: 0x%02x\r\n", reg_value);

    reg_value = nrf51_tag_spi0_lis3dh_set_feature(LIS3DH_CTRL_REG4_rw, LIS3DH_BDU_ENABLE);
    DBG("--> LIS3DH_CTRL_REG4: 0x%02x\r\n", reg_value);

    reg_value = nrf51_tag_spi0_lis3dh_set_feature(LIS3DH_CTRL_REG1_rw, LIS3DH_NORMAL_1HZ_ENABLE);
    DBG("--> LIS3DH_CTRL_REG1: 0x%02x\r\n", reg_value);

    LIS3DH_CMD(tx_data, LIS3DH_OUT_ADC3_L_r, LIS3DH_READ, 0);
    nrf51_tag_spi_lis3dh_cmd(tx_data, rx_data);
    DBG("--> LIS3DH_OUT_ADC3_L: 0x%02x\r\n", rx_data[LIS3DH_CMD_DATA_INDEX_1]);

    LIS3DH_CMD(tx_data, LIS3DH_OUT_ADC3_H_r, LIS3DH_READ, 0);
    nrf51_tag_spi_lis3dh_cmd(tx_data, rx_data);
    DBG("--> LIS3DH_OUT_ADC3_H: 0x%02x\r\n", rx_data[LIS3DH_CMD_DATA_INDEX_1]);

    LIS3DH_CMD(tx_data, LIS3DH_STATUS_REG_AUX_r, LIS3DH_READ, 0);
    nrf51_tag_spi_lis3dh_cmd(tx_data, rx_data);
    DBG("--> LIS3DH_STATUS_REG_AUX: 0x%02x\r\n", rx_data[LIS3DH_CMD_DATA_INDEX_1]);

    LIS3DH_CMD(tx_data, LIS3DH_STATUS_REG_r, LIS3DH_READ, 0);
    nrf51_tag_spi_lis3dh_cmd(tx_data, rx_data);
    DBG("--> LIS3DH_STATUS_REG: 0x%02x\r\n", rx_data[LIS3DH_CMD_DATA_INDEX_1]);
}
#endif

#if 0
/**
 */
static void nrf51_tag_spi0_lis3dh_self_test(void)
{
    uint8_t tx_data[LIS3DH_CMD_LENGTH] = {0x00, 0x00};
    uint8_t rx_data[LIS3DH_CMD_LENGTH] = {0x00, 0x00};
    
    uint8_t reg_value = 0;

    reg_value = nrf51_tag_spi0_lis3dh_set_feature(LIS3DH_CTRL_REG4_rw, LIS3DH_SELF_TEST_0_ENABLE);
    DBG("--> LIS3DH_CTRL_REG4: 0x%02x\r\n", reg_value);

    LIS3DH_CMD(tx_data, LIS3DH_STATUS_REG_r, LIS3DH_READ, 0);
    nrf51_tag_spi_lis3dh_cmd(tx_data, rx_data);
    DBG("--> LIS3DH_STATUS_REG: 0x%02x\r\n", rx_data[LIS3DH_CMD_DATA_INDEX_1]);

    LIS3DH_CMD(tx_data, LIS3DH_OUT_X_L_r, LIS3DH_READ, 0);
    nrf51_tag_spi_lis3dh_cmd(tx_data, rx_data);
    DBG("--> LIS3DH_OUT_X_L: 0x%02x\r\n", rx_data[LIS3DH_CMD_DATA_INDEX_1]);

    LIS3DH_CMD(tx_data, LIS3DH_OUT_X_H_r, LIS3DH_READ, 0);
    nrf51_tag_spi_lis3dh_cmd(tx_data, rx_data);
    DBG("--> LIS3DH_OUT_X_H: 0x%02x\r\n", rx_data[LIS3DH_CMD_DATA_INDEX_1]);
}
#endif

// ------------------------------------------------------------------------------------------------
// Public Module Interface Functions
// ------------------------------------------------------------------------------------------------

/**
 */
void nrf51_tag_lis3dh_init()
{
    uint8_t tx_data[LIS3DH_CMD_LENGTH] = {0x00, 0x00};
    uint8_t rx_data[LIS3DH_CMD_LENGTH] = {0x00, 0x00};
    
    LIS3DH_CMD(tx_data, LIS3DH_WHO_AM_I_r, LIS3DH_READ, 0);
    nrf51_tag_spi_lis3dh_cmd(tx_data, rx_data);
    
    s_lis3dh_ready = 0;
    
    if ( rx_data[LIS3DH_CMD_DATA_INDEX_1] == LIS3DH_WHO_AM_1_DEFAULT )
    {
        s_lis3dh_ready = 1;
        
        nrf51_tag_spi0_lis3dh_reset();
    }

    DBG("--> %s\r\n", LIS3DH_READY(s_lis3dh_ready) );
}
