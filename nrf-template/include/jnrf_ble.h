#ifndef LIBJNRF_INCLUDE_JNRF_BLE_H_
#define LIBJNRF_INCLUDE_JNRF_BLE_H_

#define APP_BLE_OBSERVER_PRIO   3
#define APP_BLE_CONN_CFG_TAG    1
#define MIN_CONN_INTERVAL       MSEC_TO_UNITS(100, UNIT_1_25_MS)
#define MAX_CONN_INTERVAL       MSEC_TO_UNITS(200, UNIT_1_25_MS)
#define SLAVE_LATENCY           0
#define CONN_SUP_TIMEOUT        MSEC_TO_UNITS(4000, UNIT_10_MS)

void jnrf_ble_init(void);

void jnrf_ble_gap_init(void);

#endif  // LIBJNRF_INCLUDE_JNRF_BLE_H_
