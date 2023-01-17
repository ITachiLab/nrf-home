#ifndef LIBJNRF_LIBRARY_H
#define LIBJNRF_LIBRARY_H

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
} JnrfConfig;

extern JnrfConfig jnrf_config;

void jnrf_simple_init(DeviceMode device_mode, char *device_name,
                      uint16_t device_id, uint16_t appearance);

void jnrf_start(void);

#endif  // LIBJNRF_LIBRARY_H
