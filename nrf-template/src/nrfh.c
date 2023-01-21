#include "nrfh.h"

#include <string.h>

#include "nrfh_simple.h"

NrfhConfig * nrfh_config = NULL;

static ModeFunctions mode_functions[2] = {{// SIMPLE_ADVERTISER
                                           .setup = nrfh_simple_setup,
                                           .start = nrfh_simple_start}};

void nrfh_simple_init(NrfhConfig * nrfh_user_config,
                      NrfhSimpleConfig * nrfh_simple_config) {
  nrfh_config = nrfh_user_config;
  nrfh_config->_functions = &mode_functions[SIMPLE_ADVERTISER];
  nrfh_config->_simple = nrfh_simple_config;
}

void nrfh_start() {
  nrfh_config->_functions->setup();
  nrfh_config->_functions->start();
}