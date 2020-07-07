#ifndef __DPAPI_SFP_H__
#define __DPAPI_SFP_H__

#include "dpapi.h"

typedef uint8_t dpapi_sfp_bitmap;
typedef uint8_t dpapi_sfp_control_value;

typedef enum
{
    DPAPI_SFP_CONTROL_RESET,
    DPAPI_SFP_CONTROL_RESET_STATE,
    DPAPI_SFP_CONTROL_RX_LOS,
    DPAPI_SFP_CONTROL_TX_FAULT,
    DPAPI_SFP_CONTROL_TX_DISABLE,
    DPAPI_SFP_CONTROL_TX_DISABLE_CHANNEL,
    DPAPI_SFP_CONTROL_LP_MODE,
    DPAPI_SFP_CONTROL_POWER_OVERRIDE,
    DPAPI_SFP_CONTROL_LAST = DPAPI_SFP_CONTROL_POWER_OVERRIDE,
    DPAPI_SFP_CONTROL_COUNT,
    DPAPI_SFP_CONTROL_INVALID = -1,
} dpapi_sfp_control_t;

dpapi_status dpapi_sfp_init(uint16_t instance);
dpapi_status dpapi_sfp_deinit(uint16_t instance);
dpapi_status dpapi_sfp_is_fiber(uint16_t instance, uint8_t *is_fiber);
dpapi_status dpapi_sfp_is_present(uint16_t instance, uint8_t *present);
dpapi_status dpapi_sfp_eeprom_read(uint16_t instance, uint8_t data[256]);
dpapi_status dpapi_sfp_dom_eeprom_read(uint16_t instance, uint8_t data[256]);
dpapi_status dpapi_sfp_eeprom_readb(uint16_t instance, uint8_t offset, uint8_t *data);
dpapi_status dpapi_sfp_eeprom_writeb(uint16_t instance, uint8_t offset, uint8_t data);
dpapi_status dpapi_sfp_control_is_support(uint16_t instance, dpapi_sfp_control_t control, uint8_t *is_support);
dpapi_status dpapi_sfp_control_get(uint16_t instance, dpapi_sfp_control_t control, dpapi_sfp_control_value *value);
dpapi_status dpapi_sfp_control_set(uint16_t instance, dpapi_sfp_control_t control, dpapi_sfp_control_value value);
dpapi_status dpapi_sfp_quantity_of_ports_get(uint8_t *ports);
dpapi_status dpapi_sfp_bitmap_get(uint8_t *pbmap);
dpapi_status dpapi_sfp_presence_bitmap_get(uint8_t *pbmap);
dpapi_status dpapi_sfp_rx_los_bitmap_get(uint8_t *pbmap);

#endif /* __DPAPI_SFP_H__ */
