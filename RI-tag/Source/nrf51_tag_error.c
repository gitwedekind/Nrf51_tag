/* 
 */

#include "nrf51_tag_error.h"

static void nrf51_tag_app_error(uint32_t id, uint32_t pc, uint32_t info)
{
    /* static error variables - in order to prevent removal by optimizers 
    */
    static volatile struct
    {
        uint32_t        fault_id;
        uint32_t        pc;
        uint32_t        error_info;
        assert_info_t * p_assert_info;
        error_info_t  * p_error_info;
        ret_code_t      err_code;
        uint32_t        line_num;
        const uint8_t * p_file_name;
    } m_error_data = {0};

    m_error_data.fault_id   = id;
    m_error_data.pc         = pc;
    m_error_data.error_info = info;

    switch (id)
    {
    case NRF_FAULT_ID_SDK_ASSERT:
        m_error_data.p_assert_info = (assert_info_t *)info;
        m_error_data.err_code      = NRF_TAG_ERROR_ASSERT;
        m_error_data.line_num      = m_error_data.p_assert_info->line_num;
        m_error_data.p_file_name   = m_error_data.p_assert_info->p_file_name;
        break;

    case NRF_FAULT_ID_SDK_ERROR:
        m_error_data.p_error_info = (error_info_t *)info;
        m_error_data.err_code     = m_error_data.p_error_info->err_code;
        m_error_data.line_num     = m_error_data.p_error_info->line_num;
        m_error_data.p_file_name  = m_error_data.p_error_info->p_file_name;
        break;
    }

    PRINT_NRF_TAG_ERROR(m_error_data);
    UNUSED_VARIABLE(m_error_data);

#ifdef DEBUG
    PRINT_ENTERING_SLEEP_MODE();
    LOOP_WHILE_TAG_UART_ACTIVE();
    set_power_mode_off();
    power_manage();
#else
    PRINT_SYSTEM_RESET();
    LOOP_WHILE_TAG_UART_ACTIVE();
    NVIC_SystemReset();
#endif
}

void app_error_fault_handler(uint32_t id, uint32_t pc, uint32_t info)
{
    nrf51_tag_app_error(id, pc, info);
}
