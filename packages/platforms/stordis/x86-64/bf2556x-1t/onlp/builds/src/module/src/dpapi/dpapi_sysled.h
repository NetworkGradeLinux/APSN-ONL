#ifndef __DPAPI_SYSLED_H__
#define __DPAPI_SYSLED_H__

#include "dpapi.h"

typedef enum
{
    DPAPI_LED_MODE_OFF,
    DPAPI_LED_MODE_AUTO,
    DPAPI_LED_MODE_AUTO_BLINKING,
    DPAPI_LED_MODE_CHAR,
    DPAPI_LED_MODE_RED,
    DPAPI_LED_MODE_RED_BLINKING,
    DPAPI_LED_MODE_ORANGE,
    DPAPI_LED_MODE_ORANGE_BLINKING,
    DPAPI_LED_MODE_YELLOW,
    DPAPI_LED_MODE_YELLOW_BLINKING,
    DPAPI_LED_MODE_GREEN,
    DPAPI_LED_MODE_GREEN_BLINKING,
    DPAPI_LED_MODE_BLUE,
    DPAPI_LED_MODE_BLUE_BLINKING,
    DPAPI_LED_MODE_PURPLE,
    DPAPI_LED_MODE_PURPLE_BLINKING,
    DPAPI_LED_MODE_LAST = DPAPI_LED_MODE_PURPLE_BLINKING,
    DPAPI_LED_MODE_COUNT,
    DPAPI_LED_MODE_INVALID = -1,
} dpapi_led_mode_t;

dpapi_status dpapi_sysled_mode_set(uint16_t instance, dpapi_led_mode_t mode);
dpapi_status dpapi_sysled_mode_get(uint16_t instance, dpapi_led_mode_t *mode);

#endif /* __DPAPI_SYSLED_H__ */