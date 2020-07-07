/************************************************************
 * <bsn.cl fy=2014 v=onl>
 *
 *        Copyright 2014, 2015 Big Switch Networks, Inc.
 *        Copyright 2017 Delta Networks, Inc.
 *
 * Licensed under the Eclipse Public License, Version 1.0 (the
 * "License"); you may not use this file except in compliance
 * with the License. You may obtain a copy of the License at
 *
 *        http://www.eclipse.org/legal/epl-v10.html
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied. See the License for the specific
 * language governing permissions and limitations under the
 * License.
 *
 * </bsn.cl>
 ************************************************************
 *
 *
 ***********************************************************/
#include <onlp/platformi/sfpi.h>
#include <x86_64_stordis_bf2556x_1t/x86_64_stordis_bf2556x_1t_config.h>
#include "x86_64_stordis_bf2556x_1t_log.h"

#include <stdio.h>
#include <string.h>
#include <fcntl.h>

#include "platform_lib.h"
#include "dpapi/dpapi.h"
#include "dpapi/dpapi_sfp.h"


int onlp_sfpi_init(void)
{
    return ONLP_STATUS_OK;
}

int onlp_sfpi_bitmap_get(onlp_sfp_bitmap_t* bmap)
{
    uint8_t i, max_ports;

    if(dpapi_sfp_quantity_of_ports_get(&max_ports) != ONLP_STATUS_OK)
    {
        return ONLP_STATUS_E_INVALID;
    }

    AIM_BITMAP_CLR_ALL(bmap);

    for(i = 1; i <= max_ports; i++) 
    {
        AIM_BITMAP_SET(bmap, i);
    }

    return ONLP_STATUS_OK;
}

/*
 * Return 1 if present.
 * Return 0 if not present.
 * Return < 0 if error.
 */
int onlp_sfpi_is_present(int port)
{
    uint8_t present = 0;

    dpapi_sfp_is_present((port-1), &present);
    return (int)present;
}

int onlp_sfpi_presence_bitmap_get(onlp_sfp_bitmap_t* dst)
{
    uint8_t max_ports, i, *pbmap;

    if(dpapi_sfp_quantity_of_ports_get(&max_ports) != ONLP_STATUS_OK)
    {
        return ONLP_STATUS_E_INVALID;
    }

    pbmap = (uint8_t *)calloc(1, sizeof(uint8_t) * max_ports);

    if(dpapi_sfp_presence_bitmap_get(pbmap) != ONLP_STATUS_OK)
    {
        return ONLP_STATUS_E_INVALID;
    }

    for(i = 0; i < max_ports; i++)
    {
        AIM_BITMAP_MOD(dst, (i+1), pbmap[i]);
    }

    free(pbmap);
    return ONLP_STATUS_OK;
}

int onlp_sfpi_eeprom_read(int port, uint8_t data[256])
{
    if(dpapi_sfp_eeprom_read((port-1), data) != ONLP_STATUS_OK)
    {
        return ONLP_STATUS_E_INVALID;
    }

    return ONLP_STATUS_OK;
}

int onlp_sfpi_dev_readb(int port, uint8_t devaddr, uint8_t addr)
{
    uint8_t value = 0;

    if (dpapi_sfp_eeprom_readb((port-1), addr, &value) != ONLP_STATUS_OK)
    {
        return ONLP_STATUS_E_INVALID;
    }

    return (int)value;
}

int onlp_sfpi_dev_writeb(int port, uint8_t devaddr, uint8_t addr, uint8_t value)
{
    if (dpapi_sfp_eeprom_writeb((port-1), addr, value) != ONLP_STATUS_OK)
    {
        return ONLP_STATUS_E_INVALID;
    }

    return ONLP_STATUS_OK;
}

int onlp_sfpi_control_supported(int port, onlp_sfp_control_t control, int* value)
{
    return ONLP_STATUS_E_UNSUPPORTED;
}

int onlp_sfpi_control_get(int port, onlp_sfp_control_t control, int* value)
{
    return ONLP_STATUS_E_UNSUPPORTED;
}

int onlp_sfpi_control_set(int port, onlp_sfp_control_t control, int value)
{
    return ONLP_STATUS_E_UNSUPPORTED;
}

int onlp_sfpi_rx_los_bitmap_get(onlp_sfp_bitmap_t* dst)
{
    return ONLP_STATUS_E_UNSUPPORTED;
}

int onlp_sfpi_dom_read(int port, uint8_t data[256])
{
    if(port > NUM_OF_SFP)
    {
        return ONLP_STATUS_E_UNSUPPORTED;
    }

    if(dpapi_sfp_dom_eeprom_read((port-1), data) != ONLP_STATUS_OK)
    {
        return ONLP_STATUS_E_INVALID;
    }

    return ONLP_STATUS_OK;
}

int onlp_sfpi_ioctl(int port, va_list vargs)
{
    return ONLP_STATUS_E_UNSUPPORTED;
}

