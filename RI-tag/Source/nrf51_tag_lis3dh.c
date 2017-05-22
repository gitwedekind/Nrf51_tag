 /** 
 * @file nrf51)tag_lis3dh.c
 *
 */

#include "nrf51_tag_error.h"
#include "nrf51_tag_lis3dh.h"

// ------------------------------------------------------------------------------------------------
// GPIOTE Ready Flag for Accelerometer Read 
// ------------------------------------------------------------------------------------------------

static uint8_t s_lis3dh_ready = 0;

static uint8_t s_lis3dh_enabled = 0;

// ------------------------------------------------------------------------------------------------
// LIS3Dh Read / Write Functions
// ------------------------------------------------------------------------------------------------

static uint8_t s_tx_data[LIS3DH_CMD_LENGTH] = {0x00, 0x00};
static uint8_t s_rx_data[LIS3DH_CMD_LENGTH] = {0x00, 0x00};

// ------------------------------------------------------------------------------------------------
// LIS3DH Register Dump Functions
// ------------------------------------------------------------------------------------------------

/**
 */
static void nrf51_tag_lis3dh_reg_dump(void)
{
    uint32_t index = 0;
    
    DBG("\r\n--> Reg Dump\r\n");

    for ( index = 0; index < LIS3DH_REG_COUNT; ++index)
    {
        uint8_t reg_value = nrf51_tag_lis3dh_read_register(LIS3DH_Registers[index]);

        DBG("[%02d] Reg: 0x%02x, Data: 0x%02x\r\n", index, LIS3DH_Registers[index], reg_value);
    }

    DBG("---\r\n");
}

/**
 */
static void nrf51_tag_lis3dh_reset_reg_dump(void)
{
    uint32_t index = 0;
    
    DBG("\r\n--> Reset Reg Dump\r\n");

    for ( index = 0; index < LIS3DH_RW_REG_COUNT; ++index)
    {
        uint8_t reg_value = nrf51_tag_lis3dh_read_register(LIS3DH_ResetRegisters[index][LIS3DH_CMD_REG_INDEX_0]);
        
        DBG("%s[%02x]: 0x%02x\r\n", LIS3DH_RESET_REGISTERS_str[index], LIS3DH_ResetRegisters[index][LIS3DH_CMD_REG_INDEX_0], reg_value);
        nrf_delay_us(1000);
    }
    
    DBG("---\r\n");
}

/**
 */
static uint8_t nrf51_tag_lis3dh_reset(void)
{
    uint32_t index = 0;
    uint8_t reg_value = 0;
    
    for ( index = 0; index < LIS3DH_RW_REG_COUNT; ++index)
    {
        nrf51_tag_lis3dh_write_register
        (
            LIS3DH_ResetRegisters[index][LIS3DH_CMD_REG_INDEX_0], 
            LIS3DH_ResetRegisters[index][LIS3DH_CMD_DATA_INDEX_1]
        );
    }
    
    nrf51_tag_lis3dh_read_register(LIS3DH_INT1_SRC_r);
    nrf51_tag_lis3dh_read_register(LIS3DH_INT2_SRC_r);

    for ( index = 0; index < LIS3DH_RW_REG_COUNT; ++index)
    {
        reg_value = nrf51_tag_lis3dh_read_register(LIS3DH_ResetRegisters[index][LIS3DH_CMD_REG_INDEX_0]);
        
        if ( reg_value != LIS3DH_ResetRegisters[index][LIS3DH_CMD_DATA_INDEX_1] )
        {
            APP_ERROR_CHECK(NRF_TAG_ERROR_LIS3DH_RESET);
        }
    }
    
    //nrf51_tag_lis3dh_reg_dump();

    return index < LIS3DH_RW_REG_COUNT ? 0 : 1;
}

/**
 */
static void nrf51_tag_lis3dh_int1_enabled(void)
{
#ifdef ENABLE_8_BIT_MODE
    #define LIS3DH_INT1_REG1 0x2F // 10 Hz, LPM, Zen, Yen, Xen
#else
    #define LIS3DH_INT1_REG1 0x27 // 10 Hz, Normal (10-bit) / High Resolution Mode (12-bit), Zen, Yen, Xen
#endif
    
    #define LIS3DH_INT1_REG2 0x09 // FDS, HP_IA1
    
    #define LIS3DH_INT1_ALL_OFF 0x00 // Interrupts OFF
    #define LIS3DH_INT1_REG3    0x40 // I1_IA1
    
#ifdef ENABLE_8_BIT_MODE
    #define LIS3DH_INT1_REG4 0x00 // Note: BDU must be off for 8-bit Mode
#elif ENABLE_10_BIT_MODE
    #define LIS3DH_INT1_REG4 0x80 // BDU Normal Mode (10-bit)
#else
    #define LIS3DH_INT1_REG4 0x88 // BDU High Resolution Mode (12-bit)
#endif
    
    #define LIS3DH_INT1_REG5 0x00 // Defaults
    #define LIS3DH_INT1_REG6 0x00 // Defaults
    
    #define LIS3DH_INT1_REFERENCE 0x00 // Defaults
    
    #define LIS3DH_INT1_CFG      0x2A // Defaults
    #define LIS3DH_INT1_DURATION 0x00 // Defaults
    
    nrf51_tag_lis3dh_write_register(LIS3DH_CTRL_REG1_rw, LIS3DH_INT1_REG1);
    nrf_delay_ms(6);
    
    nrf51_tag_lis3dh_write_register(LIS3DH_CTRL_REG2_rw, LIS3DH_INT1_REG2);
    nrf51_tag_lis3dh_write_register(LIS3DH_CTRL_REG3_rw, LIS3DH_INT1_REG3);
    nrf51_tag_lis3dh_write_register(LIS3DH_CTRL_REG4_rw, LIS3DH_INT1_REG4);
    nrf51_tag_lis3dh_write_register(LIS3DH_CTRL_REG5_rw, LIS3DH_INT1_REG5);
    nrf51_tag_lis3dh_write_register(LIS3DH_CTRL_REG6_rw, LIS3DH_INT1_REG6);

    nrf51_tag_lis3dh_write_register(LIS3DH_REFERENCE_rw, LIS3DH_INT1_REFERENCE);

    nrf51_tag_lis3dh_write_register(LIS3DH_INT1_THS_rw,      get_accelerometer_threshold());
    nrf51_tag_lis3dh_write_register(LIS3DH_INT1_DURATION_rw, LIS3DH_INT1_DURATION);

    LIS3DH_CMD(s_tx_data, LIS3DH_INT1_SRC_r, LIS3DH_READ, 0);
    nrf51_tag_spi_lis3dh_cmd(s_tx_data, s_rx_data);

    //nrf51_tag_lis3dh_reset_reg_dump();

    s_lis3dh_ready = 1;

    nrf51_tag_lis3dh_write_register(LIS3DH_INT1_CFG_rw, LIS3DH_INT1_CFG);
}

// ------------------------------------------------------------------------------------------------
// Public Module Interface Functions
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
        nrf51_tag_data_ready();
        
        nrf51_tag_diagnostic_lis3dh_int1();
    }
}

/**
 */
void nrf51_tag_lis3dh_init(void)
{
    s_lis3dh_enabled = 0;
    s_lis3dh_ready   = 0;
    
    nrf51_tag_spi0_lis3dh_init();
    
    LIS3DH_CMD(s_tx_data, LIS3DH_WHO_AM_I_r, LIS3DH_READ, 0);
    nrf51_tag_spi_lis3dh_cmd(s_tx_data, s_rx_data);
    
    if ( s_rx_data[LIS3DH_CMD_DATA_INDEX_1] == LIS3DH_WHO_AM_1_DEFAULT )
    {
        s_lis3dh_enabled = 1;
        
        nrf51_tag_lis3dh_reset();

        nrf51_tag_lis3dh_int1_enabled();
    }
    
    nrf51_tag_diagnostic_lis3dh_enabled(s_lis3dh_enabled);
}

/**
 */
uint8_t nrf51_tag_lis3dh_enabled(void)
{
    return s_lis3dh_enabled ;
}

/**
 */
void nrf51_tag_lis3dh_write_register(uint8_t reg_cmd, uint8_t reg_value)
{
    LIS3DH_CMD(s_tx_data, reg_cmd, LIS3DH_WRITE, reg_value);
    nrf51_tag_spi_lis3dh_cmd(s_tx_data, s_rx_data);
}

/**
 */
uint8_t nrf51_tag_lis3dh_read_register(uint8_t reg_cmd)
{
    LIS3DH_CMD(s_tx_data, reg_cmd, LIS3DH_READ, 0);
    nrf51_tag_spi_lis3dh_cmd(s_tx_data, s_rx_data);

    return s_rx_data[LIS3DH_CMD_DATA_INDEX_1];
}
