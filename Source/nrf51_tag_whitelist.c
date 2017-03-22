/**
* @file nrf51_tag_whitelist.c
* @brief Source file for the Radio Interface Whitelist.
*
*/

#include "nrf51_tag_error.h"
#include "nrf51_tag_whitelist.h"

// ---------------------------------------------------------------------------
// Whitelist Variables
// ---------------------------------------------------------------------------

static ble_gap_whitelist_t s_ble_gap_whitelist = {0};

static const uint8_t MAX_GAP_ADDR_IN_WHITE_LIST = 1;

static ble_gap_addr_t s_addr_list[MAX_GAP_ADDR_IN_WHITE_LIST] = {0};
static ble_gap_addr_t* s_p_addr_list = NULL;

static const uint8_t MAX_GAP_IRK_IN_WHITE_LIST = 1;

static ble_gap_irk_t s_irk_list[MAX_GAP_IRK_IN_WHITE_LIST] = {0};
static ble_gap_irk_t* s_p_irk_list = NULL;

// ---------------------------------------------------------------------------
// Interface Functions
// ---------------------------------------------------------------------------

/**@brief Whitelist initialization.
 */
void nrf51_tag_whitelist_init(void)
{
    nrf51_tag_clear_whitelist();
}

/**@brief Clear the Whitelist.
 */
void nrf51_tag_clear_whitelist(void)
{
    memset(&s_ble_gap_whitelist, '\0', sizeof(s_ble_gap_whitelist));
    
    memset(&s_addr_list, '\0', sizeof(s_addr_list));
    s_p_addr_list = NULL;

    memset(&s_irk_list, '\0', sizeof(s_irk_list));
    s_p_irk_list = NULL;

    s_ble_gap_whitelist.addr_count = 0;
    s_ble_gap_whitelist.pp_addrs   = NULL;

    s_ble_gap_whitelist.irk_count  = 0;
    s_ble_gap_whitelist.pp_irks    = NULL;
}

/**@brief Set the active Whitelist to use a gap address.
 */
void nrf51_tag_set_whitelist_gap_addr(ble_gap_addr_t gap_addr)
{
    nrf51_tag_clear_whitelist();

    s_addr_list[0] = gap_addr;
    s_p_addr_list  = &s_addr_list[0];
    
    s_ble_gap_whitelist.addr_count = MAX_GAP_ADDR_IN_WHITE_LIST;
    s_ble_gap_whitelist.pp_addrs   = &s_p_addr_list;
}

/**@brief Set the active Whitelist to use an gap irk.
 */
void nrf51_tag_set_whitelist_gap_irk(ble_gap_irk_t gap_irk)
{
    nrf51_tag_clear_whitelist();

    s_irk_list[0] = gap_irk;
    s_p_irk_list  = &s_irk_list[0];
    
    s_ble_gap_whitelist.irk_count = MAX_GAP_IRK_IN_WHITE_LIST;
    s_ble_gap_whitelist.pp_irks   = &s_p_irk_list;
}

/**@brief Return the pointer to the active Whitelist.
 */
ble_gap_whitelist_t* nrf51_tag_get_whitelist(void)
{
    bool use_whitelist = false;
    
    if ( s_ble_gap_whitelist.addr_count || s_ble_gap_whitelist.irk_count )
    {
        use_whitelist = true;
    }
    
    return (use_whitelist == false) ? NULL : &s_ble_gap_whitelist;
}

/**@brief Return the active Whitelist filter policy.
 */
uint8_t nrf51_tag_get_whitelist_filter_policy(void)
{
    uint8_t filter_policy = BLE_GAP_ADV_FP_ANY;
    
    if ( s_ble_gap_whitelist.addr_count || s_ble_gap_whitelist.irk_count )
    {
        filter_policy = BLE_GAP_ADV_FP_FILTER_BOTH;
    }
    
    return filter_policy;
}
