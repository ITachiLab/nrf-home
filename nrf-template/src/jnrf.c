#include "jnrf.h"

#include <string.h>

#include "jnrf_simple.h"

JnrfConfig jnrf_config = {0};

static ModeFunctions mode_functions[2] = {{// SIMPLE_ADVERTISER
                                           .setup = jnrf_simple_setup,
                                           .start = jnrf_simple_start}};

void jnrf_simple_init(DeviceMode device_mode, char* device_name,
                      uint16_t device_id, uint16_t appearance) {
  memset(&jnrf_config, 0, sizeof(JnrfConfig));

  jnrf_config.functions = &mode_functions[device_mode];
  jnrf_config.device_name = device_name;
  jnrf_config.appearance = appearance;
  jnrf_config.device_id = device_id;
}

void jnrf_start() {
  jnrf_config.functions->setup();
  jnrf_config.functions->start();
}