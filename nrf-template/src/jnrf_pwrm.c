#include "jnrf_pwrm.h"

#include <app_error.h>
#include <nrf_pwr_mgmt.h>

void jnrf_power_manager_init(void) {
  ret_code_t err_code;
  err_code = nrf_pwr_mgmt_init();
  APP_ERROR_CHECK(err_code);
}