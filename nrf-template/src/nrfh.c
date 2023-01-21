#include "nrfh.h"

#include <string.h>

#include "nrfh_simple.h"

NrfhConfig nrfh_config = {0};

static ModeFunctions mode_functions[2] = {{// SIMPLE_ADVERTISER
                                           .setup = nrfh_simple_setup,
                                           .start = nrfh_simple_start}};

void nrfh_simple_init(DeviceMode device_mode, char* device_name,
                      uint16_t device_id, uint16_t appearance) {
  memset(&nrfh_config, 0, sizeof(NrfhConfig));

  nrfh_config.functions = &mode_functions[device_mode];
  nrfh_config.device_name = device_name;
  nrfh_config.appearance = appearance;
  nrfh_config.device_id = device_id;
}

void nrfh_start() {
  nrfh_config.functions->setup();
  nrfh_config.functions->start();
}