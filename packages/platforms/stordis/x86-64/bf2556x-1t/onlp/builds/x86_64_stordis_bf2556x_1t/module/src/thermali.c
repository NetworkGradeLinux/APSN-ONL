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
 * Thermal Sensor Platform Implementation.
 *
 ***********************************************************/
#include <onlp/platformi/thermali.h>
#include "x86_64_stordis_bf2556x_1t_log.h"

#include <stdio.h>
#include <string.h>
#include <fcntl.h>

#include "platform_lib.h"
#include "dpapi/dpapi.h"
#include "dpapi/dpapi_thrml.h"


#define THERMAL_INFO_ENTRY_INIT(_id, _desc)         \
    {                                               \
        {                                           \
            .id = ONLP_THERMAL_ID_CREATE(_id),      \
            .description = _desc,                   \
            .poid = 0,                              \
        },                                          \
        .status = ONLP_THERMAL_STATUS_PRESENT,      \
        .caps = (ONLP_THERMAL_CAPS_GET_TEMPERATURE), \
    }


static onlp_thermal_info_t onlp_thermal_info[] = {
    { }, /* Not used */
    THERMAL_INFO_ENTRY_INIT(THERMAL_1_ON_MAIN_BOARD, "Temp_L0"),
    THERMAL_INFO_ENTRY_INIT(THERMAL_2_ON_MAIN_BOARD, "Temp_L1"),
    THERMAL_INFO_ENTRY_INIT(THERMAL_3_ON_MAIN_BOARD, "Temp_L2"),
    THERMAL_INFO_ENTRY_INIT(THERMAL_4_ON_MAIN_BOARD, "Temp_L3")
};


int onlp_thermali_init(void)
{
    return ONLP_STATUS_OK;
}

int onlp_thermali_hdr_get(onlp_oid_t oid, onlp_oid_hdr_t* hdr)
{
    int id = ONLP_OID_ID_GET(oid);

    *hdr = onlp_thermal_info[id].hdr;
    return ONLP_STATUS_OK;
}

int onlp_thermali_info_get(onlp_oid_t oid, onlp_thermal_info_t* info)
{
    int id = ONLP_OID_ID_GET(oid);

    *info = onlp_thermal_info[id];
    if(dpapi_thrml_temp_get(id-1, &info->mcelsius) != ONLP_STATUS_OK)
    {
        return ONLP_STATUS_E_INVALID;
    }

    return ONLP_STATUS_OK;
}

int onlp_thermali_ioctl(int id, va_list vargs)
{
    return ONLP_STATUS_E_UNSUPPORTED;
}
