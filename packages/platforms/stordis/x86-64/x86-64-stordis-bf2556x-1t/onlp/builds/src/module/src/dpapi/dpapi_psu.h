#ifndef __DPAPI_PSU_H__
#define __DPAPI_PSU_H__

#include "dpapi.h"

typedef int dpapi_psu_volt;
typedef int dpapi_psu_amp;
typedef int dpapi_psu_watt;

dpapi_status dpapi_psu_init(uint16_t instance);
dpapi_status dpapi_psu_deinit(uint16_t instance);
dpapi_status dpapi_psu_model_get(uint16_t instance, char **model);
dpapi_status dpapi_psu_serial_get(uint16_t instance, char **serial);
dpapi_status dpapi_psu_volt_get(uint16_t instance, dpapi_psu_volt *volt);
dpapi_status dpapi_psu_amp_get(uint16_t instance, dpapi_psu_amp *amp);
dpapi_status dpapi_psu_watt_get(uint16_t instance, dpapi_psu_watt *watt);
dpapi_status dpapi_psu_eeprom_dump(uint16_t instance, uint8_t *data);
dpapi_status dpapi_psu_eeprom_readb(uint16_t instance, uint8_t offest, uint8_t len, uint8_t *data);
dpapi_status dpapi_psu_is_present(uint16_t instance, uint8_t *present);
dpapi_status dpapi_psu_is_powergood(uint16_t instance, uint8_t *powergood);

#endif /* __DPAPI_PSU_H__ */