/** 
 * @file nrf51)tag_lis3dh.c
 *
 */

#include "nrf51_tag_error.h"
#include "nrf51_tag_lis3dh.h"

// ------------------------------------------------------------------------------------------------
// GPIOTE Ready Flag for Accelerometer Read 
// ------------------------------------------------------------------------------------------------

/**
*/
static uint8_t s_lis3dh_ready = 0;

/**
*/
static uint8_t s_self_test_enabled = 0;

/**
*/
static void lis3dh_default_data_callback(void)
{
}

/**
*/
PFN_LIS3DH_CB s_pfn_lis3dh_data_callback = lis3dh_default_data_callback;

// ------------------------------------------------------------------------------------------------
// LIS3Dh Read / Write Functions
// ------------------------------------------------------------------------------------------------

static uint8_t s_tx_data[LIS3DH_CMD_LENGTH] = {0x00, 0x00};
static uint8_t s_rx_data[LIS3DH_CMD_LENGTH] = {0x00, 0x00};

/**
 */
static void nrf51_tag_lis3dh_write_register(uint8_t reg_cmd, uint8_t reg_value)
{
    LIS3DH_CMD(s_tx_data, reg_cmd, LIS3DH_WRITE, reg_value);
    nrf51_tag_spi_lis3dh_cmd(s_tx_data, s_rx_data);
}

/**
 */
static uint8_t nrf51_tag_lis3dh_read_register(uint8_t reg_cmd)
{
    LIS3DH_CMD(s_tx_data, reg_cmd, LIS3DH_READ, 0);
    nrf51_tag_spi_lis3dh_cmd(s_tx_data, s_rx_data);

    return s_rx_data[LIS3DH_CMD_DATA_INDEX_1];
}

// ------------------------------------------------------------------------------------------------
// LIS3DH Data Read / Convert Function
// ------------------------------------------------------------------------------------------------

static LIS3DH_RAW_CONVERTER_T s_x = {0};
static LIS3DH_RAW_CONVERTER_T s_y = {0};
static LIS3DH_RAW_CONVERTER_T s_z = {0};

#define AVERAGE_COUNT 5

static int32_t s_x_avg = 0;
static int32_t s_y_avg = 0;
static int32_t s_z_avg = 0;

static uint16_t s_avg_index = 0;

static void lis3dh_average(void)
{
    s_x_avg += s_x.highPower.value;
    s_y_avg += s_y.highPower.value;
    s_z_avg += s_z.highPower.value;
    
    ++s_avg_index;
    
    if ( s_avg_index > AVERAGE_COUNT-1 )
    {
        s_avg_index = 0;
        
        s_x_avg /= AVERAGE_COUNT;
        s_y_avg /= AVERAGE_COUNT;
        s_z_avg /= AVERAGE_COUNT;
        
        s_pfn_lis3dh_data_callback();
        
        s_x_avg = 0;
        s_y_avg = 0;
        s_z_avg = 0;
    }
}

static void lis3dh_read_data(void)
{
    uint8_t xl = nrf51_tag_lis3dh_read_register(LIS3DH_OUT_X_L_r);
    uint8_t xh = nrf51_tag_lis3dh_read_register(LIS3DH_OUT_X_H_r);
    s_x.raw = MAKE_U16(xl,xh);
    
    uint8_t yl = nrf51_tag_lis3dh_read_register(LIS3DH_OUT_Y_L_r);
    uint8_t yh = nrf51_tag_lis3dh_read_register(LIS3DH_OUT_Y_H_r);
    s_y.raw = MAKE_U16(yl,yh);

    uint8_t zl = nrf51_tag_lis3dh_read_register(LIS3DH_OUT_Z_L_r);
    uint8_t zh = nrf51_tag_lis3dh_read_register(LIS3DH_OUT_Z_H_r);
    s_z.raw = MAKE_U16(zl,zh);
    
    lis3dh_average();
}

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

// ------------------------------------------------------------------------------------------------
// LIS3DH Control Functions
// ------------------------------------------------------------------------------------------------

#define SELF_TEST_SAMPLES 5

static uint8_t s_st_normal_active = 0;

static uint8_t s_st_normal_count = 0;
static uint8_t s_st_test_count   = 0;

static int32_t s_st_x_normal_data = 0;
static int32_t s_st_y_normal_data = 0;
static int32_t s_st_z_normal_data = 0;

static int32_t s_st_x_test_data   = 0;
static int32_t s_st_y_test_data   = 0;
static int32_t s_st_z_test_data   = 0;

/**
 */
static void nrf51_tag_lis3dh_clear_variables(void)
{
    s_st_normal_active = 0;
    
    s_self_test_enabled = 0;
    
    s_st_normal_count = 0;
    s_st_test_count   = 0;

    s_st_x_normal_data = 0;
    s_st_y_normal_data = 0;
    s_st_y_normal_data = 0;
    
    s_st_x_test_data   = 0;
    s_st_y_test_data   = 0;
    s_st_z_test_data   = 0;
}

/**
 */
static void nrf51_tag_lis3dh_enable_self_test(void)
{
    #define LIS3DH_SET_SELF_TEST0_REG4 0x84 // BDU, FS = +/- 2G, HR, ST0

    s_lis3dh_ready = 0;
    
    nrf51_tag_lis3dh_write_register(LIS3DH_CTRL_REG4_rw, LIS3DH_SET_SELF_TEST0_REG4);

    s_lis3dh_ready = 1;
}

/**
 */
static void nrf51_tag_lis3dh_enable_data_ready(void)
{
    #define LIS3DH_SET_DATA_READY_REG4 0x80 // BDU, FS = +/- 2G, HR, NORMAL

    s_lis3dh_ready = 0;
    
    nrf51_tag_lis3dh_write_register(LIS3DH_CTRL_REG4_rw, LIS3DH_SET_DATA_READY_REG4);

    s_lis3dh_ready = 1;
}

static void lis3dh_self_test_callback(void)
{
    DBG("ST: %d, %d, %d\r\n", s_x_avg, s_y_avg, s_z_avg);

    if ( s_st_normal_active )
    {
        if ( s_st_normal_count < SELF_TEST_SAMPLES+1 )
        {
            if ( s_st_normal_count )
            {
                s_st_x_normal_data += s_x_avg;
                s_st_y_normal_data += s_y_avg;
                s_st_z_normal_data += s_z_avg;
            }

            ++s_st_normal_count;
            
            if ( s_st_normal_count == SELF_TEST_SAMPLES+1 )
            {
                s_st_x_normal_data /= SELF_TEST_SAMPLES;
                s_st_y_normal_data /= SELF_TEST_SAMPLES;
                s_st_z_normal_data /= SELF_TEST_SAMPLES;
                
                DBG("ST ND: %d, %d, %d\r\n", s_st_x_normal_data, s_st_y_normal_data, s_st_z_normal_data);

                s_st_normal_active = 0;
                
                nrf51_tag_lis3dh_enable_self_test();
            }
        }
    }
    else
    {
        if ( s_st_test_count < SELF_TEST_SAMPLES+1 )
        {
            if ( s_st_test_count )
            {
                s_st_x_test_data += s_x_avg;
                s_st_y_test_data += s_y_avg;
                s_st_z_test_data += s_z_avg;
            }

            ++s_st_test_count;
        
            if ( s_st_test_count == SELF_TEST_SAMPLES+1 )
            {
                s_st_x_test_data /= SELF_TEST_SAMPLES;
                s_st_y_test_data /= SELF_TEST_SAMPLES;
                s_st_z_test_data /= SELF_TEST_SAMPLES;
                
                DBG("ST TD: %d, %d, %d\r\n", s_st_x_test_data, s_st_y_test_data, s_st_z_test_data);

                DBG("ST DIFF: %d, %d, %d\r\n", 
                    abs(s_st_x_normal_data - s_st_x_test_data), 
                    abs(s_st_y_normal_data - s_st_y_test_data), 
                    abs(s_st_z_normal_data - s_st_z_test_data));

                s_st_x_normal_data = 0;
                s_st_y_normal_data = 0;
                s_st_z_normal_data = 0;
                
                s_st_normal_count = 0;
                
                s_st_x_test_data = 0;
                s_st_y_test_data = 0;
                s_st_z_test_data = 0;
                
                s_st_test_count = 0;

                s_st_normal_active = 1;

                nrf51_tag_lis3dh_enable_data_ready();
            }
        }
    }
}
    
static int32_t x_avg = 0;
static int32_t y_avg = 0;
static int32_t z_avg = 0;
    
static void lis3dh_data_ready_callback(void)
{
    x_avg = s_x_avg;
    y_avg = s_y_avg;
    z_avg = s_z_avg;

    DBG("DR: %d, %d, %d\r\n", x_avg, y_avg, z_avg); 
}

/**
 */
static void nrf51_tag_lis3dh_self_test(void)
{
    s_pfn_lis3dh_data_callback = lis3dh_self_test_callback;

    nrf51_tag_lis3dh_clear_variables();

    s_self_test_enabled = 1;
    
    s_st_normal_active = 1;

    nrf51_tag_lis3dh_data_ready();
}

/**
 */
static void nrf51_tag_lis3dh_normal_mode(void)
{
    s_pfn_lis3dh_data_callback = lis3dh_data_ready_callback;

    nrf51_tag_lis3dh_clear_variables();

    nrf51_tag_lis3dh_data_ready();
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
        lis3dh_read_data();
    }
}

/**
 */
void nrf51_tag_lis3dh_init(void)
{
    s_lis3dh_ready = 0;
    
    s_self_test_enabled = 0;

    nrf51_tag_spi0_lis3dh_init();
    
    LIS3DH_CMD(s_tx_data, LIS3DH_WHO_AM_I_r, LIS3DH_READ, 0);
    nrf51_tag_spi_lis3dh_cmd(s_tx_data, s_rx_data);
    
    if ( s_rx_data[LIS3DH_CMD_DATA_INDEX_1] == LIS3DH_WHO_AM_1_DEFAULT )
    {
        nrf51_tag_lis3dh_reset();
    }
    
    nrf51_tag_lis3dh_suspend();
    
    //nrf51_tag_lis3dh_self_test();
    
    nrf51_tag_lis3dh_normal_mode();
}

/**
 */
void nrf51_tag_lis3dh_suspend(void)
{
    #define LIS3DH_SUSPEND_REG1 0x07
    #define LIS3DH_SUSPEND_REG2 0x00
    #define LIS3DH_SUSPEND_REG3 0x00
    #define LIS3DH_SUSPEND_REG4 0x00
    #define LIS3DH_SUSPEND_REG5 0x00
    #define LIS3DH_SUSPEND_REG6 0x00
    
    #define LIS3DH_SUSPEND_REFERENCE 0x00 
    
    #define LIS3DH_SUSPEND_INT1_CFG      0x00
    #define LIS3DH_SUSPEND_INT1_THS      0x00
    #define LIS3DH_SUSPEND_INT1_DURATION 0x00

    s_lis3dh_ready = 0;

    nrf51_tag_lis3dh_write_register(LIS3DH_INT1_CFG_rw, LIS3DH_SUSPEND_INT1_CFG);
    
    nrf51_tag_lis3dh_write_register(LIS3DH_CTRL_REG1_rw, LIS3DH_SUSPEND_REG1);
    
    nrf_delay_ms(6);
    
    nrf51_tag_lis3dh_write_register(LIS3DH_CTRL_REG2_rw, LIS3DH_SUSPEND_REG2);
    nrf51_tag_lis3dh_write_register(LIS3DH_CTRL_REG3_rw, LIS3DH_SUSPEND_REG3);
    nrf51_tag_lis3dh_write_register(LIS3DH_CTRL_REG4_rw, LIS3DH_SUSPEND_REG4);
    nrf51_tag_lis3dh_write_register(LIS3DH_CTRL_REG5_rw, LIS3DH_SUSPEND_REG5);
    nrf51_tag_lis3dh_write_register(LIS3DH_CTRL_REG6_rw, LIS3DH_SUSPEND_REG6);

    nrf51_tag_lis3dh_write_register(LIS3DH_REFERENCE_rw, LIS3DH_SUSPEND_REFERENCE);

    nrf51_tag_lis3dh_write_register(LIS3DH_INT1_THS_rw,      LIS3DH_SUSPEND_INT1_THS);
    nrf51_tag_lis3dh_write_register(LIS3DH_INT1_DURATION_rw, LIS3DH_SUSPEND_INT1_DURATION);

    //nrf51_tag_lis3dh_reg_dump();
}

/**
 */
void nrf51_tag_lis3dh_data_ready(void)
{
    #define LIS3DH_DATA_READY_REG1 0x27 // 1 Hz, Zen, Yen, Xen
    #define LIS3DH_DATA_READY_REG2 0x00 // Default Settings
    #define LIS3DH_DATA_READY_REG3 0x10 // I1_ZYXDA (DATA_RDY)
    #define LIS3DH_DATA_READY_REG4 0x88 // BDU, FS +/- 2G, HR
    #define LIS3DH_DATA_READY_REG5 0x00 // Defaults
    #define LIS3DH_DATA_READY_REG6 0x00 // Defaults
    
    #define LIS3DH_DATA_READY_REFERENCE 0x00 // Defaults
    
    #define LIS3DH_DATA_READY_INT1_CFG      0x00 // Defaults
    #define LIS3DH_DATA_READY_INT1_THS      0x00 // Defaults
    #define LIS3DH_DATA_READY_INT1_DURATION 0x00 // Defaults
    
    nrf51_tag_lis3dh_write_register(LIS3DH_CTRL_REG1_rw, LIS3DH_DATA_READY_REG1);
    nrf_delay_ms(6);
    
    nrf51_tag_lis3dh_write_register(LIS3DH_CTRL_REG2_rw, LIS3DH_DATA_READY_REG2);
    nrf51_tag_lis3dh_write_register(LIS3DH_CTRL_REG4_rw, LIS3DH_DATA_READY_REG4);
    nrf51_tag_lis3dh_write_register(LIS3DH_CTRL_REG5_rw, LIS3DH_DATA_READY_REG5);
    nrf51_tag_lis3dh_write_register(LIS3DH_CTRL_REG6_rw, LIS3DH_DATA_READY_REG6);

    nrf51_tag_lis3dh_write_register(LIS3DH_REFERENCE_rw, LIS3DH_DATA_READY_REFERENCE);

    nrf51_tag_lis3dh_write_register(LIS3DH_INT1_THS_rw,      LIS3DH_DATA_READY_INT1_THS);
    nrf51_tag_lis3dh_write_register(LIS3DH_INT1_DURATION_rw, LIS3DH_DATA_READY_INT1_DURATION);
    nrf51_tag_lis3dh_write_register(LIS3DH_INT1_CFG_rw,      LIS3DH_SUSPEND_INT1_CFG);
    
    LIS3DH_CMD(s_tx_data, LIS3DH_INT1_SRC_r, LIS3DH_READ, 0);
    nrf51_tag_spi_lis3dh_cmd(s_tx_data, s_rx_data);

    s_lis3dh_ready = 1;
    
    nrf51_tag_lis3dh_write_register(LIS3DH_CTRL_REG3_rw, LIS3DH_DATA_READY_REG3);

    //nrf51_tag_lis3dh_reset_reg_dump();
}
