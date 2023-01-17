#include "jnrf_timer.h"

#include <app_error.h>
#include <app_timer.h>

void jnrf_timer_init() {
  ret_code_t err_code = app_timer_init();
  APP_ERROR_CHECK(err_code);
}