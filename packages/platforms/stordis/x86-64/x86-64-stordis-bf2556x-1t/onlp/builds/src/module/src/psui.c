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
 *
 ***********************************************************/
#include <onlp/platformi/psui.h>
#include "x86_64_stordis_bf2556x_1t_int.h"

#include <stdio.h>
#include <string.h>
#include <fcntl.h>

#include "platform_lib.h"
#include "dpapi/dpapi.h"
#include "dpapi/dpapi_psu.h"


#define PSU_INFO_ENTRY_INIT(_id, _desc)    \
    {                                      \
        {                                  \
            .id = ONLP_PSU_ID_CREATE(_id), \
            .description = _desc,          \
            .poid = 0,                     \
        },                                 \
        .status = 0,                       \
        .caps = (ONLP_PSU_CAPS_DC12 | ONLP_PSU_CAPS_VOUT | ONLP_PSU_CAPS_POUT), \
    }


static onlp_psu_info_t onlp_psu_info[] = {
    { }, /* Not used */
    PSU_INFO_ENTRY_INIT(PSU_1, "PSU 1"),
    PSU_INFO_ENTRY_INIT(PSU_2, "PSU 2"),
};


int onlp_psui_init(void)
{
    return ONLP_STATUS_OK;
}

int onlp_psui_hdr_get(onlp_oid_t oid, onlp_oid_hdr_t* hdr)
{
    int id = ONLP_OID_ID_GET(oid);

    *hdr = onlp_psu_info[id].hdr;
    return ONLP_STATUS_OK;
}

int onlp_psui_info_get(onlp_oid_t oid, onlp_psu_info_t* info)
{
    int id = ONLP_OID_ID_GET(oid);
    char *model = NULL, *serial = NULL;
    uint8_t present = 0;

    *info = onlp_psu_info[id];

    dpapi_psu_is_present(id-1, &present);
    if(present)
    {
        info->status |= ONLP_PSU_STATUS_PRESENT;
        info->status &= ~(ONLP_PSU_STATUS_FAILED);
        info->status &= ~(ONLP_PSU_STATUS_UNPLUGGED);
    }
    else
    {
        info->status |= ONLP_PSU_STATUS_FAILED;
        info->status &= ~(ONLP_PSU_STATUS_PRESENT);
        info->status &= ~(ONLP_PSU_STATUS_UNPLUGGED);
        return ONLP_STATUS_OK;
    }

    dpapi_psu_model_get(id-1, &model);
    memset(info->model, 0, sizeof(info->model));
    if (model)
    {
        strncpy(info->model, model, (sizeof(info->model)-1));
        free(model);
    }

    dpapi_psu_serial_get(id-1, &serial);
    memset(info->serial, 0, sizeof(info->serial));
    if (serial)
    {
        strncpy(info->serial, serial, (sizeof(info->serial)-1));
        free(serial);
    }

    dpapi_psu_volt_get(id-1,  &(info->mvout));
    dpapi_psu_watt_get(id-1,  &(info->mpout));

    return ONLP_STATUS_OK;
}

int onlp_psui_ioctl(onlp_oid_t pid, va_list vargs)
{
    return ONLP_STATUS_E_UNSUPPORTED;
}
