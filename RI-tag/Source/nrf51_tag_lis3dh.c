/** 
 * @file nrf51)tag_lis3dh.c
 *
 */

#include "nrf51_tag_error.h"
#include "nrf51_tag_lis3dh.h"

/**
*/
static uint8_t s_lis3dh_ready = 0;

static uint8_t nrf51_tag_spi0_lis3dh_set_register(uint8_t reg_cmd, uint8_t reg_value);

uint8_t tx_data[LIS3DH_CMD_LENGTH] = {0x00, 0x00};
uint8_t rx_data[LIS3DH_CMD_LENGTH] = {0x00, 0x00};

LIS3DH_RAW_CONVERTER_T x, y, z;

uint8_t xl, yl, zl;
uint8_t xh, yh, zh;

void lis3dh_read_data(void)
{
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

    x.raw = MAKE_U16(xl,xh);
    y.raw = MAKE_U16(yl,yh);
    z.raw = MAKE_U16(zl,zh);
}

uint8_t clearInterrupt() 
{
    uint8_t tx_data[LIS3DH_CMD_LENGTH] = {0x00, 0x00};
    uint8_t rx_data[LIS3DH_CMD_LENGTH] = {0x00, 0x00};
    
    LIS3DH_CMD(tx_data, LIS3DH_INT1_SRC_r, LIS3DH_READ, 0);
    nrf51_tag_spi_lis3dh_cmd(tx_data, rx_data);
    uint8_t int1_src = rx_data[LIS3DH_CMD_DATA_INDEX_1]; 
    
    return int1_src;

    nrf_delay_us(10);
    
    uint32_t wake_pin = nrf_gpio_pin_read(LIS3DH_WAKE_IRQ_PIN);
    
	while( wake_pin ) 
    {
        LIS3DH_CMD(tx_data, LIS3DH_INT1_SRC_r, LIS3DH_READ, 0);
        nrf51_tag_spi_lis3dh_cmd(tx_data, rx_data);
        
        nrf_delay_us(10);

        wake_pin = nrf_gpio_pin_read(LIS3DH_WAKE_IRQ_PIN);
	}

	return int1_src;
}

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
        
#if 1
        uint8_t tx_data[LIS3DH_CMD_LENGTH] = {0x00, 0x00};
        uint8_t rx_data[LIS3DH_CMD_LENGTH] = {0x00, 0x00};
        
        LIS3DH_CMD(tx_data, LIS3DH_INT1_SRC_r, LIS3DH_READ, 0);
        nrf51_tag_spi_lis3dh_cmd(tx_data, rx_data);
        uint8_t int_src_pre = rx_data[LIS3DH_CMD_DATA_INDEX_1];

        LIS3DH_CMD(tx_data, LIS3DH_STATUS_REG_r, LIS3DH_READ, 0);
        nrf51_tag_spi_lis3dh_cmd(tx_data, rx_data);
        uint8_t status_pre = rx_data[LIS3DH_CMD_DATA_INDEX_1];

        lis3dh_read_data();
        
        LIS3DH_CMD(tx_data, LIS3DH_INT1_SRC_r, LIS3DH_READ, 0);
        nrf51_tag_spi_lis3dh_cmd(tx_data, rx_data);
        uint8_t int_src_post = rx_data[LIS3DH_CMD_DATA_INDEX_1];

        LIS3DH_CMD(tx_data, LIS3DH_STATUS_REG_r, LIS3DH_READ, 0);
        nrf51_tag_spi_lis3dh_cmd(tx_data, rx_data);
        uint8_t status_post = rx_data[LIS3DH_CMD_DATA_INDEX_1];

        LIS3DH_CMD(tx_data, LIS3DH_STATUS_REG_AUX_r, LIS3DH_READ, 0);
        nrf51_tag_spi_lis3dh_cmd(tx_data, rx_data);
        uint8_t status_aux = rx_data[LIS3DH_CMD_DATA_INDEX_1];

#if 1   
        DBG("%d, %d, %d, src: 0x%02x, 0x%02x - status: 0x%02x 0x%02x 0x%02x\r\n", 
            x.highPower.value, 
            y.highPower.value, 
            z.highPower.value, 
            int_src_pre, 
            int_src_post, 
            status_pre, 
            status_post,
            status_aux);
#endif
#endif

#if 0   
        while ( int_src )
        {
            LIS3DH_CMD(tx_data, LIS3DH_INT1_SRC_r, LIS3DH_READ, 0);
            nrf51_tag_spi_lis3dh_cmd(tx_data, rx_data);
            int_src = rx_data[LIS3DH_CMD_DATA_INDEX_1];
        }
#endif
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
static void nrf51_tag_spi0_lis3dh_reg_dump(uint8_t reg_selection)
{
    uint8_t tx_data[LIS3DH_CMD_LENGTH] = {0x00, 0x00};
    uint8_t rx_data[LIS3DH_CMD_LENGTH] = {0x00, 0x00};

    uint32_t index = 0;
    
    if ( reg_selection == DUMP_ALL_REGS )
    {
        for ( index = 0; index < LIS3DH_REG_COUNT; ++index)
        {
            LIS3DH_CMD(tx_data, LIS3DH_Registers[index], LIS3DH_READ, 0);
            nrf51_tag_spi_lis3dh_cmd(tx_data, rx_data);
            DBG("--> Reg: 0x%02x, Data: 0x%02x\r\n", LIS3DH_Registers[index], rx_data[LIS3DH_CMD_DATA_INDEX_1]);
        }
    }
    else
    {
        for ( index = 10; index < 18; ++index)
        {
            LIS3DH_CMD(tx_data, LIS3DH_Registers[index], LIS3DH_READ, 0);
            nrf51_tag_spi_lis3dh_cmd(tx_data, rx_data);
            DBG("--> Reg: 0x%02x, Data: 0x%02x\r\n", LIS3DH_Registers[index], rx_data[LIS3DH_CMD_DATA_INDEX_1]);
        }

        LIS3DH_CMD(tx_data, LIS3DH_INT1_CFG_rw, LIS3DH_READ, 0);
        nrf51_tag_spi_lis3dh_cmd(tx_data, rx_data);
        DBG("--> Reg: 0x%02x, Data: 0x%02x\r\n", LIS3DH_INT1_CFG_rw, rx_data[LIS3DH_CMD_DATA_INDEX_1]);

        LIS3DH_CMD(tx_data, LIS3DH_INT1_SRC_r, LIS3DH_READ, 0);
        nrf51_tag_spi_lis3dh_cmd(tx_data, rx_data);
        DBG("--> Reg: 0x%02x, Data: 0x%02x\r\n", LIS3DH_INT1_SRC_r, rx_data[LIS3DH_CMD_DATA_INDEX_1]);

        LIS3DH_CMD(tx_data, LIS3DH_INT1_THS_rw, LIS3DH_READ, 0);
        nrf51_tag_spi_lis3dh_cmd(tx_data, rx_data);
        DBG("--> Reg: 0x%02x, Data: 0x%02x\r\n", LIS3DH_INT1_THS_rw, rx_data[LIS3DH_CMD_DATA_INDEX_1]);

        LIS3DH_CMD(tx_data, LIS3DH_INT1_DURATION_rw, LIS3DH_READ, 0);
        nrf51_tag_spi_lis3dh_cmd(tx_data, rx_data);
        DBG("--> Reg: 0x%02x, Data: 0x%02x\r\n", LIS3DH_INT1_DURATION_rw, rx_data[LIS3DH_CMD_DATA_INDEX_1]);
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

/**
 */
void nrf51_tag_spi0_lis3dh_enable_temperature(void)
{
    uint8_t tx_data[LIS3DH_CMD_LENGTH] = {0x00, 0x00};
    uint8_t rx_data[LIS3DH_CMD_LENGTH] = {0x00, 0x00};
    
    uint8_t reg_value = 0;
    
    reg_value = nrf51_tag_spi0_lis3dh_set_register(LIS3DH_TEMP_CFG_REG_rw, 0xC0);
    DBG("--> LIS3DH_TEMP_CFG_REG_rw: 0x%02x\r\n", reg_value);

    reg_value = nrf51_tag_spi0_lis3dh_set_register(LIS3DH_CTRL_REG4_rw, 0x88);
    DBG("--> LIS3DH_CTRL_REG4_rw: 0x%02x\r\n", reg_value);

    reg_value = nrf51_tag_spi0_lis3dh_set_register(LIS3DH_CTRL_REG1_rw, 0x10);
    DBG("--> LIS3DH_CTRL_REG1_rw: 0x%02x\r\n", reg_value);

    //nrf51_tag_spi0_lis3dh_reg_dump(DUMP_ALL_REGS);
}

// ------------------------------------------------------------------------------------------------
// Public Module Interface Functions
// ------------------------------------------------------------------------------------------------

/**
 */
void nrf51_tag_lis3dh_init(void)
{
    uint8_t tx_data[LIS3DH_CMD_LENGTH] = {0x00, 0x00};
    uint8_t rx_data[LIS3DH_CMD_LENGTH] = {0x00, 0x00};
    
    //nrf51_tag_spi0_lis3dh_set_register(LIS3DH_CTRL_REG5_rw, 0x80);
    //nrf51_tag_spi0_lis3dh_set_register(LIS3DH_CTRL_REG5_rw, 0x00);

    LIS3DH_CMD(tx_data, LIS3DH_WHO_AM_I_r, LIS3DH_READ, 0);
    nrf51_tag_spi_lis3dh_cmd(tx_data, rx_data);
    
    s_lis3dh_ready = 0;
    
    if ( rx_data[LIS3DH_CMD_DATA_INDEX_1] == LIS3DH_WHO_AM_1_DEFAULT )
    {
        nrf51_tag_spi0_lis3dh_reset();
    }
}

void nrf51_tag_lis3dh_configure(void)
{
    #define LIS3DH_CONFIG_CTRL_REG1 0x21 // 1 Hz, Zen, Yen, Xen
    #define LIS3DH_CONFIG_CTRL_REG2 0x00 // Default Settings
    #define LIS3DH_CONFIG_CTRL_REG3 0x40 //
    #define LIS3DH_CONFIG_CTRL_REG4 0x88 // 
    #define LIS3DH_CONFIG_CTRL_REG5 0x00 // 
    #define LIS3DH_CONFIG_CTRL_REG6 0x00 // 
    
    #define LIS3DH_CONFIG_REFERENCE 0x00 // 
    
    #define LIS3DH_CONFIG_INT1_CFG      0x42 //
    #define LIS3DH_CONFIG_INT1_THS      0x04 //
    #define LIS3DH_CONFIG_INT1_DURATION 0x00 //
    
    uint8_t tx_data[LIS3DH_CMD_LENGTH] = {0x00, 0x00};
    uint8_t rx_data[LIS3DH_CMD_LENGTH] = {0x00, 0x00};

    nrf51_tag_spi0_lis3dh_set_register(LIS3DH_CTRL_REG1_rw, LIS3DH_CONFIG_CTRL_REG1);
    
    nrf_delay_us(6000);
    
    nrf51_tag_spi0_lis3dh_set_register(LIS3DH_CTRL_REG2_rw, LIS3DH_CONFIG_CTRL_REG2);
    nrf51_tag_spi0_lis3dh_set_register(LIS3DH_CTRL_REG3_rw, LIS3DH_CONFIG_CTRL_REG3);
    nrf51_tag_spi0_lis3dh_set_register(LIS3DH_CTRL_REG4_rw, LIS3DH_CONFIG_CTRL_REG4);
    nrf51_tag_spi0_lis3dh_set_register(LIS3DH_CTRL_REG5_rw, LIS3DH_CONFIG_CTRL_REG5);
    nrf51_tag_spi0_lis3dh_set_register(LIS3DH_CTRL_REG6_rw, LIS3DH_CONFIG_CTRL_REG6);

    nrf51_tag_spi0_lis3dh_set_register(LIS3DH_REFERENCE_rw, LIS3DH_CONFIG_REFERENCE);

    nrf51_tag_spi0_lis3dh_set_register(LIS3DH_INT1_THS_rw,      LIS3DH_CONFIG_INT1_THS);
    nrf51_tag_spi0_lis3dh_set_register(LIS3DH_INT1_DURATION_rw, LIS3DH_CONFIG_INT1_DURATION);

    //lis3dh_read_data();

    LIS3DH_CMD(tx_data, LIS3DH_STATUS_REG_r, LIS3DH_READ, 0);
    nrf51_tag_spi_lis3dh_cmd(tx_data, rx_data);
    uint8_t status_pre = rx_data[LIS3DH_CMD_DATA_INDEX_1];
    DBG("--> STATUS: 0x%x\r\n", status_pre );

    uint8_t int_src = 0xFF;
    
    //lis3dh_read_data();
#if 0
    while ( int_src )
    {
        LIS3DH_CMD(tx_data, LIS3DH_INT1_SRC_r, LIS3DH_READ, 0);
        nrf51_tag_spi_lis3dh_cmd(tx_data, rx_data);
        int_src = rx_data[LIS3DH_CMD_DATA_INDEX_1];
        
        nrf_delay_us(100);
    }
#endif    
    //DBG("--> INT1 SRC: 0x%x\r\n", clearInterrupt() );
    
    nrf51_tag_spi0_lis3dh_set_register(LIS3DH_INT1_CFG_rw, LIS3DH_CONFIG_INT1_CFG);
    //nrf51_tag_spi0_lis3dh_set_register(LIS3DH_CTRL_REG1_rw, LIS3DH_CONFIG_CTRL_REG1);

    //DBG("--> INT1 SRC: 0x%x\r\n", clearInterrupt() );

    s_lis3dh_ready = 1;
    DBG("--> %s\r\n", LIS3DH_READY(s_lis3dh_ready) );
    
    //nrf51_tag_spi0_lis3dh_reg_dump(DUMP_ALL_REGS);
}
