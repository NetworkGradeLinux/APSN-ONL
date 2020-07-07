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
 * Fan Platform Implementation Defaults.
 *
 ***********************************************************/
#include <onlp/platformi/fani.h>
#include "x86_64_stordis_bf2556x_1t_int.h"

#include <stdio.h>
#include <string.h>
#include <fcntl.h>

#include "platform_lib.h"
#include "dpapi/dpapi.h"
#include "dpapi/dpapi_fan.h"


#define FAN_INFO_ENTRY_INIT(_id, _desc)         \
    {                                           \
        {                                       \
            .id = ONLP_FAN_ID_CREATE(_id),      \
            .description = _desc,               \
            .poid = 0,                          \
        },                                      \
        .status = 0,                            \
        .caps = (ONLP_FAN_CAPS_GET_PERCENTAGE), \
    }


static onlp_fan_info_t onlp_fan_info[] = {
    { }, /* Not used */
    FAN_INFO_ENTRY_INIT(FAN_1_ON_FAN_BOARD, "FanPWM_0"),
    FAN_INFO_ENTRY_INIT(FAN_2_ON_FAN_BOARD, "FanPWM_0_1"),
    FAN_INFO_ENTRY_INIT(FAN_3_ON_FAN_BOARD, "FanPWM_1"),
    FAN_INFO_ENTRY_INIT(FAN_4_ON_FAN_BOARD, "FanPWM_1_1"),
    FAN_INFO_ENTRY_INIT(FAN_5_ON_FAN_BOARD, "FanPWM_2"),
    FAN_INFO_ENTRY_INIT(FAN_6_ON_FAN_BOARD, "FanPWM_2_1"),
    FAN_INFO_ENTRY_INIT(FAN_7_ON_FAN_BOARD, "FanPWM_3"),
    FAN_INFO_ENTRY_INIT(FAN_8_ON_FAN_BOARD, "FanPWM_3_1")
};


int onlp_fani_init(void)
{
    return ONLP_STATUS_OK;
}

int onlp_fani_hdr_get(onlp_oid_t oid, onlp_oid_hdr_t* hdr)
{
    int id = ONLP_OID_ID_GET(oid);

    *hdr = onlp_fan_info[id].hdr;
    return ONLP_STATUS_OK;
}

int onlp_fani_info_get(onlp_oid_t oid, onlp_fan_info_t* info)
{
    int id = ONLP_OID_ID_GET(oid);
    uint8_t present = 0;
    uint16_t percentage = 0;

    *info = onlp_fan_info[id];

    dpapi_fan_is_present(id-1, &present);
    if (present)
    {
        info->status |= ONLP_FAN_STATUS_PRESENT;
        info->status &= ~(ONLP_FAN_STATUS_FAILED);
    }
    else
    {
        info->status &= ~(ONLP_FAN_STATUS_PRESENT);
        return ONLP_STATUS_OK;
    }

    if(dpapi_fan_percentage_get(id-1, &percentage) != ONLP_STATUS_OK)
    {
        info->status |= ONLP_FAN_STATUS_FAILED;
        info->percentage = 0;
    }
    info->percentage = percentage;

    return ONLP_STATUS_OK;
}

int onlp_fani_ioctl(onlp_oid_t fid, va_list vargs)
{
    return ONLP_STATUS_E_UNSUPPORTED;
}
