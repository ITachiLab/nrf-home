#include <nrf_log_ctrl.h>
#include <nrf_log_default_backends.h>

#include "nrfh.h"

size_t get_data(uint8_t * buffer, size_t buffer_size) {
  uint8_t data[] = {0xDE, 0xAD, 0xBE, 0xEF};
  size_t data_n = MIN(sizeof(data), buffer_size);
  memcpy(buffer, data, data_n);

  return data_n;
}

int main() {
  NRF_LOG_INIT(NULL);
  NRF_LOG_DEFAULT_BACKENDS_INIT();

  NrfhSimpleConfig simple_config = {
      .advertising_ms = 10000,
      .interval_ms = 300,
      .cycle_ms = 30000,
      .manufacturer_data = {
          .company_id = 0xDEAD,
          .get_data = get_data
      }
  };

  NrfhConfig config = {
      .device_name = "Hello, World!",
      .appearance = BLE_APPEARANCE_UNKNOWN
  };

  nrfh_simple_init(&config, &simple_config);
  nrfh_start();
}