#ifndef NRFH_LIBRARY_H
#define NRFH_LIBRARY_H

#include <ble.h>

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
  DeviceMode device_mode;
  char *device_name;
  ModeFunctions *functions;
  uint16_t device_id;
  uint16_t appearance;
} NrfhConfig;

extern NrfhConfig nrfh_config;

void nrfh_simple_init(DeviceMode device_mode, char *device_name,
                      uint16_t device_id, uint16_t appearance);

void nrfh_start(void);

#endif  // NRFH_LIBRARY_H
