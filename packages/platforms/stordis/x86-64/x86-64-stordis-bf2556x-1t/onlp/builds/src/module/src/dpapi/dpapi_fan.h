#ifndef __DPAPI_FAN_H__
#define __DPAPI_FAN_H__

#include "dpapi.h"

typedef uint16_t dpapi_fan_percentage;
typedef enum 
{
    DPAPI_FAN_DIR_B2F,
    DPAPI_FAN_DIR_F2B,
    DPAPI_FAN_DIR_LAST = DPAPI_FAN_DIR_F2B,
    DPAPI_FAN_DIR_COUNT,
    DPAPI_FAN_DIR_INVALID = -1,
} dpapi_fan_dir_t;

dpapi_status dpapi_fan_init(uint16_t instance);
dpapi_status dpapi_fan_deinit(uint16_t instance);
dpapi_status dpapi_fan_percentage_get(uint16_t instance, dpapi_fan_percentage *percentage);
dpapi_status dpapi_fan_percentage_set(uint16_t instance, dpapi_fan_percentage percentage);
dpapi_status dpapi_fan_dir_get(uint16_t instance, dpapi_fan_dir_t *dir);
dpapi_status dpapi_fan_dir_set(uint16_t instance, dpapi_fan_dir_t dir);
dpapi_status dpapi_fan_is_present(uint16_t instance, uint8_t *present);

#endif /* __DPAPI_FAN_H__ */