/**
* @file nrf51_tag_on_ble_evt_sd.c
* @brief Source file Radio Interface BLE Event SD Handler(s).
*
*/

#include "nrf51_tag_error.h"
#include "nrf51_tag_headers.h"

//-------------------------------------------------------------------------------------------------
// Soft Device Handler(s) 
//-------------------------------------------------------------------------------------------------

/**@brief Function for handling the TX Complete event.
 *
 * @param[in]   p_ble_evt   Pointer to the BLE Event structure.
 */
void nrf51_tag_sd_evt_tx_complete(ble_evt_t* p_ble_evt)
{
}

/**@brief Function for handling the User Memory event.
 *
 * @param[in]   p_ble_evt   Pointer to the BLE Event structure.
 */
void nrf51_tag_sd_evt_user_memory(ble_evt_t* p_ble_evt)
{
}

/**@brief Function for handling the User Memory Release event.
 *
 * @param[in]   p_ble_evt   Pointer to the BLE Event structure.
 */
void nrf51_tag_sd_evt_user_memory_release(ble_evt_t* p_ble_evt)
{
}
