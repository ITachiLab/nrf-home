#ifndef NRFH_LIBRARY_H
#define NRFH_LIBRARY_H

#include <ble.h>
#include <stddef.h>

typedef enum {
  SIMPLE_ADVERTISER,
  BONDED_NODE,
} DeviceMode;

typedef struct {
  void (*setup)(void);
  void (*start)(void);
  void (*ble_evt_handler)(ble_evt_t const *p_ble_evt);
} ModeFunctions;

typedef struct {
  uint16_t company_id;
  size_t (*get_data)(uint8_t *buffer, size_t size);
} ManufacturerData;

typedef struct {
  ManufacturerData manufacturer_data;
  uint32_t interval_ms;
  uint32_t advertising_ms;
  uint32_t cycle_ms;
} NrfhSimpleConfig;

typedef struct {
  char *device_name;
  uint16_t appearance;
  NrfhSimpleConfig *_simple;
  ModeFunctions *_functions;
} NrfhConfig;

extern NrfhConfig *nrfh_config;

void nrfh_simple_init(NrfhConfig *config, NrfhSimpleConfig *simple_config);

void nrfh_start(void);

#endif  // NRFH_LIBRARY_H
