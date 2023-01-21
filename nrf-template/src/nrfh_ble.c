#include "nrfh_ble.h"

#include <app_error.h>
#include <ble.h>
#include <boards.h>
#include <nrf_sdh.h>
#include <nrf_sdh_ble.h>
#include <sdk_common.h>

#include "nrfh.h"
#include "sdk_config.h"

static void ble_evt_handler(ble_evt_t const* p_ble_evt, void* p_context) {
  nrfh_config.functions->ble_evt_handler(p_ble_evt);
}

void nrfh_ble_init() {
  ret_code_t err_code;

  err_code = nrf_sdh_enable_request();
  APP_ERROR_CHECK(err_code);

  // Configure the BLE stack using the default settings.
  // Fetch the start address of the application RAM.
  uint32_t ram_start = 0;
  err_code = nrf_sdh_ble_default_cfg_set(APP_BLE_CONN_CFG_TAG, &ram_start);
  APP_ERROR_CHECK(err_code);

  // Enable BLE stack.
  err_code = nrf_sdh_ble_enable(&ram_start);
  APP_ERROR_CHECK(err_code);

  // Register handler for BLE events.
  NRF_SDH_BLE_OBSERVER(m_ble_observer, APP_BLE_OBSERVER_PRIO, ble_evt_handler,
                       NULL);
}

void nrfh_ble_gap_init() {
  ret_code_t err_code;
  ble_gap_conn_params_t gap_conn_params;
  ble_gap_conn_sec_mode_t sec_mode;

  BLE_GAP_CONN_SEC_MODE_SET_OPEN(&sec_mode);

  err_code = sd_ble_gap_device_name_set(&sec_mode,
                                        (const uint8_t*)nrfh_config.device_name,
                                        strlen(nrfh_config.device_name));
  APP_ERROR_CHECK(err_code);

  err_code = sd_ble_gap_appearance_set(nrfh_config.appearance);
  APP_ERROR_CHECK(err_code);

  memset(&gap_conn_params, 0, sizeof(gap_conn_params));

  gap_conn_params.min_conn_interval = MIN_CONN_INTERVAL;
  gap_conn_params.max_conn_interval = MAX_CONN_INTERVAL;
  gap_conn_params.slave_latency = SLAVE_LATENCY;
  gap_conn_params.conn_sup_timeout = CONN_SUP_TIMEOUT;

  err_code = sd_ble_gap_ppcp_set(&gap_conn_params);
  APP_ERROR_CHECK(err_code);
}