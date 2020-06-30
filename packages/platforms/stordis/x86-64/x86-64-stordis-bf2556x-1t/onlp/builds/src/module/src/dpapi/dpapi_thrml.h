#ifndef __DPAPI_THRML_H__
#define __DPAPI_THRML_H__

#include "dpapi.h"

typedef int dpapi_thrml_temp;

typedef enum
{
    DPAPI_LOW_THRESHOLD,
    DPAPI_HIGH_THRESHOLD,
} dpapi_thrml_threshold_t;

dpapi_status dpapi_thrml_init(uint16_t instance);
dpapi_status dpapi_thrml_deinit(uint16_t instance);
dpapi_status dpapi_thrml_temp_get(uint16_t instance, dpapi_thrml_temp *temperature);
dpapi_status dpapi_thrml_limit_get(uint16_t instance, dpapi_thrml_threshold_t type, dpapi_thrml_temp *temperature);
dpapi_status dpapi_thrml_limit_set(uint16_t instance, dpapi_thrml_threshold_t type, dpapi_thrml_temp temperature);

#endif /* __DPAPI_THRML_H__ */