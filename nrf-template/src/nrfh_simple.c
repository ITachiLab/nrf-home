#include "nrfh_simple.h"

#include <app_error.h>
#include <app_timer.h>
#include <ble_advdata.h>
#include <boards.h>
#include <nrf_pwr_mgmt.h>

#include "nrfh.h"
#include "nrfh_ble.h"
#include "nrfh_pwrm.h"
#include "nrfh_timer.h"

#define ADVERTISING_LED BSP_BOARD_LED_0

APP_TIMER_DEF(cycle_timer);

static uint8_t m_adv_handle = BLE_GAP_ADV_SET_HANDLE_NOT_SET;
static uint8_t m_enc_advdata[BLE_GAP_ADV_SET_DATA_SIZE_MAX];

static ble_advdata_service_data_t service_data[1];
static ble_advdata_t adv_data;
static ble_gap_adv_params_t adv_params;
static ble_advdata_manuf_data_t manuf_specific_data;

static ble_gap_adv_data_t gap_adv_data = {
    .adv_data = {.p_data = m_enc_advdata, .len = BLE_GAP_ADV_SET_DATA_SIZE_MAX},
};

static void ble_evt_handler(ble_evt_t const* p_ble_evt) {
  switch (p_ble_evt->header.evt_id) {
    case BLE_GAP_EVT_ADV_SET_TERMINATED:
      bsp_board_led_off(BSP_BOARD_LED_0);
      break;
  }
}

static void ble_init() { nrfh_ble_init(); }

static void gap_init() { nrfh_ble_gap_init(); }

static void power_manager_init() { nrfh_power_manager_init(); }

static void update_manufacturer_data(uint8_t* buffer, size_t size) {
  ManufacturerData m_data = nrfh_config->_simple->manufacturer_data;

  if (m_data.company_id) {
    adv_data.p_manuf_specific_data = &manuf_specific_data;

    manuf_specific_data.company_identifier = m_data.company_id;

    if (m_data.get_data) {
      size_t data_size = m_data.get_data(buffer, size);

      manuf_specific_data.data.size = data_size;
      manuf_specific_data.data.p_data = buffer;
    }
  } else {
    adv_data.p_manuf_specific_data = NULL;
  }
}

//static void update_service_data() {
//  adv_data.p_service_data_array = service_data;
//adv_data.service_data_count = 1;
//
//  service_data[0].service_uuid = 0x181A;
//  service_data[0].data.size = 4;
//  service_data[0].data.p_data = humidity;
//}

static void advertising_init() {
  ret_code_t err_code;

  memset(&manuf_specific_data, 0, sizeof(manuf_specific_data));
  memset(&adv_params, 0, sizeof(adv_params));
  memset(service_data, 0, sizeof(service_data));
  memset(&adv_data, 0, sizeof(adv_data));

  //  update_service_data();

  uint8_t md_buffer[BLE_GAP_ADV_SET_DATA_SIZE_MAX];
  update_manufacturer_data(md_buffer, BLE_GAP_ADV_SET_DATA_SIZE_MAX);

  adv_params.properties.type =
      BLE_GAP_ADV_TYPE_NONCONNECTABLE_NONSCANNABLE_UNDIRECTED;
  adv_params.filter_policy = BLE_GAP_ADV_FP_ANY;
  adv_params.interval =
      MSEC_TO_UNITS(nrfh_config->_simple->interval_ms, UNIT_0_625_MS);
  adv_params.duration =
      MSEC_TO_UNITS(nrfh_config->_simple->advertising_ms, UNIT_10_MS);
  adv_params.primary_phy = BLE_GAP_PHY_AUTO;
  adv_params.secondary_phy = BLE_GAP_PHY_AUTO;

  adv_data.name_type = BLE_ADVDATA_FULL_NAME;
  adv_data.include_appearance = true;
  adv_data.flags = BLE_GAP_ADV_FLAG_BR_EDR_NOT_SUPPORTED;

  err_code = ble_advdata_encode(&adv_data, gap_adv_data.adv_data.p_data,
                                &gap_adv_data.adv_data.len);
  APP_ERROR_CHECK(err_code);

  err_code =
      sd_ble_gap_adv_set_configure(&m_adv_handle, &gap_adv_data, &adv_params);
  APP_ERROR_CHECK(err_code);
}

static void tx_power_set() {
  ret_code_t err_code =
      sd_ble_gap_tx_power_set(BLE_GAP_TX_POWER_ROLE_ADV, m_adv_handle, 4);
  APP_ERROR_CHECK(err_code);
}

static void advertising_start() {
  bsp_board_led_on(ADVERTISING_LED);

  ret_code_t err_code;
  err_code = sd_ble_gap_adv_start(m_adv_handle, APP_BLE_CONN_CFG_TAG);
  APP_ERROR_CHECK(err_code);

  tx_power_set();
}

/**
 *
 * @param p_context
 */
static void timer_handler(void* p_context) {
  uint8_t md_buffer[BLE_GAP_ADV_SET_DATA_SIZE_MAX];
  update_manufacturer_data(md_buffer, BLE_GAP_ADV_SET_DATA_SIZE_MAX);

  //  update_service_data();

  gap_adv_data.adv_data.len = BLE_GAP_ADV_SET_DATA_SIZE_MAX;

  ret_code_t err_code = ble_advdata_encode(
      &adv_data, gap_adv_data.adv_data.p_data, &gap_adv_data.adv_data.len);
  APP_ERROR_CHECK(err_code);

  err_code =
      sd_ble_gap_adv_set_configure(&m_adv_handle, &gap_adv_data, &adv_params);
  APP_ERROR_CHECK(err_code);

  advertising_start();
}

static void timer_init() {
  nrfh_timer_init();

  app_timer_create(&cycle_timer, APP_TIMER_MODE_REPEATED, timer_handler);
}

/**
 *
 */
static void leds_init() { bsp_board_init(BSP_INIT_LEDS); }

void nrfh_simple_setup() {
  leds_init();
  timer_init();
  power_manager_init();
  ble_init();
  gap_init();
  advertising_init();

  nrfh_config->_functions->ble_evt_handler = ble_evt_handler;
}

void nrfh_simple_start() {
  advertising_start();
  app_timer_start(cycle_timer,
                  APP_TIMER_TICKS(nrfh_config->_simple->cycle_ms), NULL);

  for (;;) {
    nrf_pwr_mgmt_run();
  }
}