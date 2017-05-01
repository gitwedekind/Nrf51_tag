/**
* @file dbg_ble_on_evt.h
* @brief Source file for the BLE Event Debugging.
*
*/

#pragma once 

#include "nrf51_tag_headers.h"

//-------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------
#define ENABLE_GAP_DEBUG
#define ENABLE_GATTS_DEBUG
#define ENABLE_SD_DEBUG
#define ENABLE_AUTH_STATUS_DEBUG

//#define ENABLE_WHITELIST_DEBUG
//#define ENABLE_ADV_FILTER_POLICY_DEBUG
//#define ENABLE_SEC_INFO_REQUEST_DEBUG
//#define ENABLE_GAP_ENC_INFO_DEBUG

static char const * const BLE_GAP_ROLE[] =
{
    "BLE_GAP_ROLE_INVALID",
    "BLE_GAP_ROLE_PERIPH",
    "BLE_GAP_ROLE_CENTRAL",
};

static char const * const BLE_GAP_TIMEOUT[] =
{
    "BLE_GAP_TIMEOUT_SRC_ADVERTISING",
    "BLE_GAP_TIMEOUT_SRC_SECURITY_REQUEST",
    "BLE_GAP_TIMEOUT_SRC_SCAN",
    "BLE_GAP_TIMEOUT_SRC_CONN",
};

static char const * const BLE_GAP_ADDR_TYPE[] =
{
    "BLE_GAP_ADDR_TYPE_PUBLIC",
    "BLE_GAP_ADDR_TYPE_RANDOM_STATIC",
    "BLE_GAP_ADDR_TYPE_RANDOM_PRIVATE_RESOLVABLE",
    "BLE_GAP_ADDR_TYPE_RANDOM_PRIVATE_NON_RESOLVABLE",
};

//-------------------------------------------------------------------------------------------------
// ENABLE_GAP_DEBUG
//-------------------------------------------------------------------------------------------------
#ifdef ENABLE_GAP_DEBUG

void nrf51_tag_ble_gap_evt_debug(uint32_t evt_id);
#define DBG_GAP(x_evt) nrf51_tag_ble_gap_evt_debug(x_evt)

#else
#define DBG_GAP(x_evt)
#endif

//-------------------------------------------------------------------------------------------------
// ENABLE_GATTS_DEBUG
//-------------------------------------------------------------------------------------------------
#ifdef ENABLE_GATTS_DEBUG

void nrf51_tag_dbg_ble_gatts_evt(uint32_t evt_id);
#define DBG_GATTS(x_evt) nrf51_tag_dbg_ble_gatts_evt(x_evt)

#else
#define DBG_GATTS(x_evt)
#endif

//-------------------------------------------------------------------------------------------------
// ENABLE_SD_DEBUG
//-------------------------------------------------------------------------------------------------
#ifdef ENABLE_SD_DEBUG

void nrf51_tag_dbg_sd_evt(uint32_t evt_id);
#define DBG_SD(x_evt) nrf51_tag_dbg_sd_evt(x_evt)

#else
#define DBG_SD(x_evt)
#endif

//-------------------------------------------------------------------------------------------------
// ENABLE_AUTH_STATUS_DEBUG
//-------------------------------------------------------------------------------------------------
#ifdef ENABLE_AUTH_STATUS_DEBUG

void nrf51_tag_dbg_authentication_status(ble_gap_evt_auth_status_t as);
#define DBG_AUTH_STATUS(x_as) nrf51_tag_dbg_authentication_status(x_as)

void nrf51_tag_dbg_gap_enc_key(char* p_key_name, ble_gap_enc_key_t key);
#define DBG_GAP_ENC_KEY(x_key_name, x_key) nrf51_tag_dbg_gap_enc_key(x_key_name, x_key)

void nrf51_tag_dbg_gap_id_key(char* p_key_name, ble_gap_id_key_t key);
#define DBG_GAP_ID_KEY(x_key_name, x_key) nrf51_tag_dbg_gap_id_key(x_key_name, x_key)

#else
#define DBG_AUTH_STATUS(x_as)
#define DBG_GAP_ENC_KEY(x_key_name, x_key)
#define DBG_GAP_ID_KEY(x_key_name, x_key)
#endif

//-------------------------------------------------------------------------------------------------
// ENABLE_WHITELIST_DEBUG
//-------------------------------------------------------------------------------------------------
#ifdef ENABLE_WHITELIST_DEBUG

void nrf51_tag_whitelist(ble_gap_whitelist_t* p_whitelist);
#define DBG_WHITELIST(x_wl) nrf51_tag_whitelist(x_wl)

#else
#define DBG_WHITELIST(x_wl)
#endif

//-------------------------------------------------------------------------------------------------
// ENABLE_ADV_FILTER_POLICY_DEBUG
//-------------------------------------------------------------------------------------------------
#ifdef ENABLE_ADV_FILTER_POLICY_DEBUG

void nrf51_tag_adv_filter_policy(uint8_t fp);
#define ADV_FILTER_POLICY(x_fp) nrf51_tag_adv_filter_policy(x_fp)

#else
#define ADV_FILTER_POLICY(x_fp)
#endif

//-------------------------------------------------------------------------------------------------
// ENABLE_SEC_INFO_REQUEST_DEBUG
//-------------------------------------------------------------------------------------------------
#ifdef ENABLE_SEC_INFO_REQUEST_DEBUG

void nrf51_tag_sec_info_request(ble_gap_evt_sec_info_request_t sir);
#define DBG_SEC_INFO_REQUEST(x_sir) nrf51_tag_sec_info_request(x_sir)

#else
#define DBG_SEC_INFO_REQUEST(x_sir)
#endif

//-------------------------------------------------------------------------------------------------
// ENABLE_GAP_ENC_INFO_DEBUG
//-------------------------------------------------------------------------------------------------
#ifdef ENABLE_GAP_ENC_INFO_DEBUG

void nrf51_tag_dbg_gap_enc_info(ble_gap_enc_info_t gei);
#define DBG_GAP_ENC_INFO(x_gei) nrf51_tag_dbg_gap_enc_info(x_gei)

#else
#define DBG_GAP_ENC_INFO(x_gei)
#endif

