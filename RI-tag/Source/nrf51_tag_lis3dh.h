/** 
 * @file nrf51_tag_lis3dh.h
 *
 */
 
#pragma once 

#include "nrf51_tag_headers.h"

#include <math.h>

// ------------------------------------------------------------------------------------------------
// LIS3DH
// ------------------------------------------------------------------------------------------------

#define LIS3DH_READ  0x80
#define LIS3DH_WRITE 0x00
#define LIS3DH_MS    0x40

#define LIS3DH_CMD_LENGTH       2
#define LIS3DH_CMD_REG_INDEX_0  0
#define LIS3DH_CMD_DATA_INDEX_1 1

#define LIS3DH_REG_COUNT 42
#define LIS3DH_RW_REG_COUNT 23

#define LIS3DH_CMD(x_tx_buffer, x_cmd_reg, x_flags, x_config) \
    x_tx_buffer[LIS3DH_CMD_REG_INDEX_0] = x_cmd_reg | x_flags; \
    x_tx_buffer[LIS3DH_CMD_DATA_INDEX_1] = x_config;

#define LIS3DH_WHO_AM_1_DEFAULT 0x33

#define LIS3DH_READY(x_status) x_status == 1 ? "LIS3DH Ready" : "LIS3DH Offline" 

#define LIS3DH_ADC_ENABLE         0x80
#define LIS3DH_TEMPERATURE_ENABLE 0x40

#define LIS3DH_BDU_ENABLE         0x80

#define LIS3DH_LPEN_ENABLE        0x08
#define LIS3DH_HR_ENABLE          0x08
#define LIS3DH_SELF_TEST_0_ENABLE 0x02
#define LIS3DH_SELF_TEST_1_ENABLE 0x04

#define LIS3DH_LPM_ENABLE 0x80
#define LIS3DH_NORMAL_1HZ_ENABLE 0x10

#define DUMP_ALL_REGS  0
#define DUMP_CTRL_REGS 1
#define DUMP_DATA_REGS 2

#define LIS3DH_RANGE_16_G 1365
#define LIS3DH_RANGE_8_G  4096
#define LIS3DH_RANGE_4_G  8190
#define LIS3DH_RANGE_2_G  16380

#define GRAVITY_EARTH (9.80665F) /**< Earth's gravity in m/s^2 */

typedef union
{
    struct
    {
        // in low power - 8 significant bits, left justified
        int16_t reserved : 8;
        int16_t value    : 8;
    } lowPower;

    struct
    {
        // in normal power - 10 significant bits, left justified
        int16_t reserved : 6;
        int16_t value    : 10;
    } normalPower;

    struct
    {
        // in high resolution - 12 significant bits, left justified
        int16_t reserved : 4;
        int16_t value    : 12;

    } highPower;
    
    // the raw data as read from registers H and L
    uint16_t  raw;
} LIS3DH_RAW_CONVERTER_T;

typedef struct 
{
    float x;
    float y;
    float z;
} sensors_vec_t;

// ------------------------------------------------------------------------------------------------
// LIS3DH Control Registers
// ------------------------------------------------------------------------------------------------

static const uint8_t LIS3DH_STATUS_REG_AUX_r  = 0x07;

static const uint8_t LIS3DH_OUT_ADC1_L_r      = 0x08;
static const uint8_t LIS3DH_OUT_ADC1_H_r      = 0x09;
static const uint8_t LIS3DH_OUT_ADC2_L_r      = 0x0A;
static const uint8_t LIS3DH_OUT_ADC2_H_r      = 0x0B;
static const uint8_t LIS3DH_OUT_ADC3_L_r      = 0x0C;
static const uint8_t LIS3DH_OUT_ADC3_H_r      = 0x0D;

static const uint8_t LIS3DH_WHO_AM_I_r        = 0x0F;

static const uint8_t LIS3DH_CTRL_REG0_rw      = 0x1E;

static const uint8_t LIS3DH_TEMP_CFG_REG_rw   = 0x1F;

static const uint8_t LIS3DH_CTRL_REG1_rw      = 0x20;
static const uint8_t LIS3DH_CTRL_REG2_rw      = 0x21;
static const uint8_t LIS3DH_CTRL_REG3_rw      = 0x22;
static const uint8_t LIS3DH_CTRL_REG4_rw      = 0x23;
static const uint8_t LIS3DH_CTRL_REG5_rw      = 0x24;
static const uint8_t LIS3DH_CTRL_REG6_rw      = 0x25;

static const uint8_t LIS3DH_REFERENCE_rw      = 0x26;
static const uint8_t LIS3DH_STATUS_REG_r      = 0x27;

static const uint8_t LIS3DH_OUT_X_L_r         = 0x28;
static const uint8_t LIS3DH_OUT_X_H_r         = 0x29;
static const uint8_t LIS3DH_OUT_Y_L_r         = 0x2A;
static const uint8_t LIS3DH_OUT_Y_H_r         = 0x2B;
static const uint8_t LIS3DH_OUT_Z_L_r         = 0x2C;
static const uint8_t LIS3DH_OUT_Z_H_r         = 0x2D;

static const uint8_t LIS3DH_FIFO_CTRL_REG_rw  = 0x2E;
static const uint8_t LIS3DH_FIFO_SRC_REG_r    = 0x2F;

static const uint8_t LIS3DH_INT1_CFG_rw       = 0x30;
static const uint8_t LIS3DH_INT1_SRC_r        = 0x31;
static const uint8_t LIS3DH_INT1_THS_rw       = 0x32;
static const uint8_t LIS3DH_INT1_DURATION_rw  = 0x33;

static const uint8_t LIS3DH_INT2_CFG_rw       = 0x34;
static const uint8_t LIS3DH_INT2_SRC_r        = 0x35;
static const uint8_t LIS3DH_INT2_THS_rw       = 0x36;
static const uint8_t LIS3DH_INT2_DURATION_rw  = 0x37;

static const uint8_t LIS3DH_CLICK_CFG_rw      = 0x38;
static const uint8_t LIS3DH_CLICK_SRC_r       = 0x39;
static const uint8_t LIS3DH_CLICK_THS_rw      = 0x3A;

static const uint8_t LIS3DH_TIME_LIMIT_rw     = 0x3B;
static const uint8_t LIS3DH_TIME_LATENCY_rw   = 0x3C;
static const uint8_t LIS3DH_TIME_WINDOW_rw    = 0x3D;

static const uint8_t LIS3DH_ACT_THS_rw        = 0x3E;
static const uint8_t LIS3DH_ACT_DUR_rw        = 0x3F;

// ------------------------------------------------------------------------------------------------
// LIS3DH Control Registers Array
// ------------------------------------------------------------------------------------------------

static const uint8_t LIS3DH_Registers[LIS3DH_REG_COUNT] =
{    
    LIS3DH_STATUS_REG_AUX_r,
    LIS3DH_OUT_ADC1_L_r,
    LIS3DH_OUT_ADC1_H_r,
    LIS3DH_OUT_ADC2_L_r,
    LIS3DH_OUT_ADC2_H_r,
    LIS3DH_OUT_ADC3_L_r,
    LIS3DH_OUT_ADC3_H_r,
    LIS3DH_WHO_AM_I_r,
    LIS3DH_CTRL_REG0_rw,
    LIS3DH_TEMP_CFG_REG_rw,
    LIS3DH_CTRL_REG1_rw,
    LIS3DH_CTRL_REG2_rw,
    LIS3DH_CTRL_REG3_rw,
    LIS3DH_CTRL_REG4_rw,
    LIS3DH_CTRL_REG5_rw,
    LIS3DH_CTRL_REG6_rw,
    LIS3DH_REFERENCE_rw,
    LIS3DH_STATUS_REG_r,
    LIS3DH_OUT_X_L_r,
    LIS3DH_OUT_X_H_r,
    LIS3DH_OUT_Y_L_r,
    LIS3DH_OUT_Y_H_r,
    LIS3DH_OUT_Z_L_r,
    LIS3DH_OUT_Z_H_r,
    LIS3DH_FIFO_CTRL_REG_rw,
    LIS3DH_FIFO_SRC_REG_r,
    LIS3DH_INT1_CFG_rw,
    LIS3DH_INT1_SRC_r,
    LIS3DH_INT1_THS_rw,
    LIS3DH_INT1_DURATION_rw,
    LIS3DH_INT2_CFG_rw,
    LIS3DH_INT2_SRC_r,
    LIS3DH_INT2_THS_rw,
    LIS3DH_INT2_DURATION_rw,
    LIS3DH_CLICK_CFG_rw,
    LIS3DH_CLICK_SRC_r,
    LIS3DH_CLICK_THS_rw,
    LIS3DH_TIME_LIMIT_rw,
    LIS3DH_TIME_LATENCY_rw,
    LIS3DH_TIME_WINDOW_rw,
    LIS3DH_ACT_THS_rw,
    LIS3DH_ACT_DUR_rw,
};

// ------------------------------------------------------------------------------------------------
// LIS3DH Reset Control Register Array
// ------------------------------------------------------------------------------------------------

static const uint8_t LIS3DH_ResetRegisters[LIS3DH_RW_REG_COUNT][LIS3DH_CMD_LENGTH] =
{
    LIS3DH_CTRL_REG0_rw,     0x10,
    LIS3DH_TEMP_CFG_REG_rw,  0x00,
    LIS3DH_CTRL_REG1_rw,     0x07,
    LIS3DH_CTRL_REG2_rw,     0x00,
    LIS3DH_CTRL_REG3_rw,     0x00,
    LIS3DH_CTRL_REG4_rw,     0x00,
    LIS3DH_CTRL_REG5_rw,     0x00,
    LIS3DH_CTRL_REG6_rw,     0x00,
    LIS3DH_REFERENCE_rw,     0x00,
    LIS3DH_FIFO_CTRL_REG_rw, 0x00,
    LIS3DH_INT1_CFG_rw,      0x00,
    LIS3DH_INT1_THS_rw,      0x00,
    LIS3DH_INT1_DURATION_rw, 0x00,
    LIS3DH_INT2_CFG_rw,      0x00,
    LIS3DH_INT2_THS_rw,      0x00,
    LIS3DH_INT2_DURATION_rw, 0x00,
    LIS3DH_CLICK_CFG_rw,     0x00,
    LIS3DH_CLICK_THS_rw,     0x00,
    LIS3DH_TIME_LIMIT_rw,    0x00,
    LIS3DH_TIME_LATENCY_rw,  0x00,
    LIS3DH_TIME_WINDOW_rw,   0x00,
    LIS3DH_ACT_THS_rw,       0x00,
    LIS3DH_ACT_DUR_rw,       0x00,
};

/**
 */
void nrf51_tag_lis3dh_init(void);

/**
 */
void nrf51_tag_lis3dh_configure(void);

