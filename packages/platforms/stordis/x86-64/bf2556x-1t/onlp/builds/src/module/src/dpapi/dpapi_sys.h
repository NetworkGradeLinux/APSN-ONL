#ifndef __DPAPI_SYS_H__
#define __DPAPI_SYS_H__

#include "dpapi.h"

typedef struct dpapi_list_links {
    struct dpapi_list_links *prev;
    struct dpapi_list_links *next;
} dpapi_list_links_t;

typedef struct dpapi_list_head {
    struct dpapi_list_links links;
} dpapi_list_head_t;

typedef struct dpapi_onie_vendor_ext_s
{
    uint8_t size;
    uint8_t *value;
}dpapi_onie_vendor_ext_t;

typedef struct dpapi_onie_info_s
{

    char *product_name;
    char *part_number;
    char *serial_number;
    uint8_t     mac[6];
    char *manufacture_date;
    uint8_t     device_version;
    char *label_revision;
    char *platform_name;
    char *onie_version;
    uint16_t    mac_range;
    char *manufacturer;
    char *country_code;
    char *vendor;
    char *diag_version;
    char *service_tag;
    uint32_t    crc;

    /**
     * Vendor Extensions list, if available.
     */
    dpapi_list_head_t vx_list;
    
    /* Internal/debug */
    char *_hdr_id_string;
    uint8_t     _hdr_version;
    uint8_t     _hdr_length;
    uint8_t     _hdr_valid_crc;
    uint8_t     _is_valid;
    dpapi_onie_vendor_ext_t vendor_extension;

} dpapi_onie_info_t;

dpapi_status dpapi_sys_onie_info_get(uint16_t instance, dpapi_onie_info_t *onie_info);
dpapi_status dpapi_sys_onie_info_set(uint16_t instance, uint8_t opcode, char *value);


#endif /* __DPAPI_SYS_H__ */