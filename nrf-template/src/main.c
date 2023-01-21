#include <nrf_log_ctrl.h>
#include <nrf_log_default_backends.h>

#include "nrfh.h"

int main() {
  NRF_LOG_INIT(NULL);
  NRF_LOG_DEFAULT_BACKENDS_INIT();

  nrfh_simple_init(SIMPLE_ADVERTISER, "Humid", 69, 0x0544);
  nrfh_start();
}