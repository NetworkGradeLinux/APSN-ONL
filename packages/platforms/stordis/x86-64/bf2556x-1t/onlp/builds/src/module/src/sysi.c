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
 * HardwareVersion: 02
 *
 ***********************************************************/
 
#include <onlp/platformi/sysi.h>
#include <onlplib/crc32.h>
#include <onlplib/file.h>
#include <onlp/platformi/sysi.h>
#include <onlp/platformi/ledi.h>
#include <onlp/platformi/thermali.h>
#include <onlp/platformi/fani.h>
#include <onlp/platformi/psui.h>

#include "x86_64_stordis_bf2556x_1t_log.h"
#include "platform_lib.h"
#include "dpapi/dpapi.h"
#include "dpapi/dpapi_init.h"
#include "dpapi/dpapi_sys.h"


const char* onlp_sysi_platform_get(void)
{
    return "x86-64-stordis-bf2556x-1t-r0";
}

int onlp_sysi_init(void)
{
    if(dpapi_init() != ONLP_STATUS_OK){
        return ONLP_STATUS_E_INVALID;
    }
    return ONLP_STATUS_OK;
}

int
onlp_sysi_onie_info_get(onlp_onie_info_t* onie)
{   
    dpapi_onie_info_t *sys_onie_info;
    struct dpapi_list_links *prev, *next;

    sys_onie_info = calloc(1,sizeof(dpapi_onie_info_t));
    memset(sys_onie_info, 0, sizeof(dpapi_onie_info_t));
    list_init((struct list_head *)&sys_onie_info->vx_list);
    
    if(dpapi_sys_onie_info_get(0,sys_onie_info) != ONLP_STATUS_OK)
    {
        free(sys_onie_info);
        return ONLP_STATUS_E_INVALID;
    }
 
    /* adjust vx_list to point to the one in onie instead of sys_onie_info */
    prev = sys_onie_info->vx_list.links.prev;
    next = sys_onie_info->vx_list.links.next;
    prev->next = (struct dpapi_list_links *)&(onie->vx_list.links);
    next->prev = (struct dpapi_list_links *)&(onie->vx_list.links);

    memcpy(onie, (uint8_t*)sys_onie_info, sizeof(onlp_onie_info_t));

    free(sys_onie_info);
    return ONLP_STATUS_OK;   
}

int onlp_sysi_onie_data_get(uint8_t** data, int* size)

{
    return ONLP_STATUS_E_UNSUPPORTED;   
}

int onlp_sysi_platform_info_get(onlp_platform_info_t* pi)
{
    return ONLP_STATUS_E_UNSUPPORTED;
}

void onlp_sysi_platform_info_free(onlp_platform_info_t* pi)
{
    aim_free(pi->cpld_versions);
}

int onlp_sysi_oids_get(onlp_oid_t* table, int max)
{
    int i;
    onlp_oid_t* e = table;
    memset(table, 0, max*sizeof(onlp_oid_t));

    /* 4 Thermal sensors on the chassis */
    for (i = 1; i <= NUM_OF_THERMAL_ON_MAIN_BROAD; i++)
    {
        *e++ = ONLP_THERMAL_ID_CREATE(i);
    }

    /* 8 FANs on the chassis */
    for (i = 1; i <= NUM_OF_FAN_ON_MAIN_BROAD; i++)
    {
        *e++ = ONLP_FAN_ID_CREATE(i);
    }
    
    /* 2 PSUs on the chassis */
    for (i = 1; i <= NUM_OF_PSU_ON_MAIN_BROAD; i++)
    {
        *e++ = ONLP_PSU_ID_CREATE(i);
    }

    return 0;
}

int onlp_sysi_platform_manage_leds(void)
{ 
   return ONLP_STATUS_E_UNSUPPORTED;
}
