/************************************************************
 * <bsn.cl fy=2014 v=onl>
 *
 *           Copyright 2014 Big Switch Networks, Inc.
 *           Copyright (C) 2019 Delta Electronics, Inc.
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
#include <linux/i2c-dev.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <time.h>
#include <onlp/platformi/sysi.h>
#include <onlp/platformi/sfpi.h>
#include <onlp/platformi/ledi.h>
#include <onlp/platformi/fani.h>
#include "x86_64_stordis_bf6064x_t_int.h"
#include "x86_64_stordis_bf6064x_t_log.h"
#include "vendor_driver_pool.h"
#include "vendor_i2c_device_list.h"

/**
 * @brief Return the name of the the platform implementation.
 * @notes This will be called PRIOR to any other calls into the
 * platform driver, including the sysi_init() function below.
 *
 * The platform implementation name should match the current
 * ONLP platform name.
 *
 * IF the platform implementation name equals the current platform name,
 * initialization will continue.
 *
 * If the platform implementation name does not match, the following will be
 * attempted:
 *
 *    onlp_sysi_platform_set(current_platform_name);
 * If this call is successful, initialization will continue.
 * If this call fails, platform initialization will abort().
 *
 * The onlp_sysi_platform_set() function is optional.
 * The onlp_sysi_platform_get() is not optional.
 */
const char *onlp_sysi_platform_get(void)
{
    /*
        ONIE NAME USING "_" FOR MACHINE NAME, BUT ONL USING "-" FOR EACH FIELD
    */
    char *buffer = calloc(30, sizeof(char));
    int idx = 0;

    strncpy(buffer, platform_name, VENDOR_MAX_NAME_SIZE);

    while (buffer[idx] != '\0')
    {
        if (buffer[idx] == '_')
            buffer[idx] -= 50; // Change '_' to '-'
        idx++;
    }

    return buffer;
}

/**
 * @brief Attempt to set the platform personality
 * in the event that the current platform does not match the
 * reported platform.
 * @note Optional
 */
int onlp_sysi_platform_set(const char *platform)
{
    return ONLP_STATUS_E_UNSUPPORTED;
}

/**
 * @brief Initialize the system platform subsystem.
 */
int onlp_sysi_init(void)
{
    vendor_driver_init();

    i2c_bus_driver_t *i2c =
        (i2c_bus_driver_t *)vendor_find_driver_by_name("I2C");
    uint16_t data = 0;

    i2c->set(0, 0x70, 0x00, 1, 0x20, 1);
    i2c->set(0, 0x32, 0x0e, 1, 0x00, 1);
    i2c->set(0, 0x32, 0x0f, 1, 0x00, 1);
    i2c->set(0, 0x34, 0x02, 1, 0x00, 1);
    i2c->set(0, 0x34, 0x03, 1, 0x00, 1);
    i2c->set(0, 0x34, 0x04, 1, 0x00, 1);
    i2c->set(0, 0x35, 0x02, 1, 0x00, 1);
    i2c->set(0, 0x35, 0x03, 1, 0x00, 1);
    i2c->set(0, 0x35, 0x04, 1, 0x00, 1);
    i2c->set(0, 0x32, 0x14, 1, 0xff, 1);
    i2c->set(0, 0x32, 0x15, 1, 0xff, 1);
    i2c->set(0, 0x34, 0x0b, 1, 0xff, 1);
    i2c->set(0, 0x34, 0x0c, 1, 0xff, 1);
    i2c->set(0, 0x34, 0x0d, 1, 0xff, 1);
    i2c->set(0, 0x35, 0x0b, 1, 0xff, 1);
    i2c->set(0, 0x35, 0x0c, 1, 0xff, 1);
    i2c->set(0, 0x35, 0x0d, 1, 0xff, 1);
    i2c->set(0, 0x70, 0x00, 1, 0x00, 1);

    i2c = (i2c_bus_driver_t *)vendor_find_driver_by_name("IPMB");

    i2c->get(0, 0x4d, 0x24, 1, &data, 1);
    i2c->get(2, 0x4d, 0x24, 1, &data, 1);

    return ONLP_STATUS_OK;
}

/**
 * @brief Provide the physical base address for the ONIE eeprom.
 * @param param [out] physaddr Receives the physical address.
 * @notes If your platform provides a memory-mappable base
 * address for the ONIE eeprom data you can return it here.
 * The ONLP common code will then use this address and decode
 * the ONIE TLV specification data. If you cannot return a mappable
 * address due to the platform organization see onlp_sysi_onie_data_get()
 * instead.
 */
int onlp_sysi_onie_data_phys_addr_get(void **physaddr)
{
    return ONLP_STATUS_E_UNSUPPORTED;
}

/**
 * @brief Return the raw contents of the ONIE system eeprom.
 * @param data [out] Receives the data pointer to the ONIE data.
 * @param size [out] Receives the size of the data (if available).
 * @notes This function is only necessary if you cannot provide
 * the physical base address as per onlp_sysi_onie_data_phys_addr_get().
 */
int onlp_sysi_onie_data_get(uint8_t **data, int *size)
{
    int id = 0, rv = 0;
    uint8_t *rdata = aim_zmalloc(256);
    *size = 256;

    void *busDrv = (void *)vendor_find_driver_by_name(eeprom_dev_list[id].bus_drv_name);
    eeprom_dev_driver_t *eeprom =
        (eeprom_dev_driver_t *)vendor_find_driver_by_name(eeprom_dev_list[id].dev_drv_name);

    vendor_dev_do_oc(eeprom_o_list[id]);
    rv = eeprom->load(
        busDrv,
        eeprom_dev_list[id].bus,
        eeprom_dev_list[id].dev,
        eeprom_dev_data_list[id].offset,
        eeprom_dev_data_list[id].alen,
        rdata);
    vendor_dev_do_oc(eeprom_c_list[id]);

    if (rv < 0)
    {
        return ONLP_STATUS_E_INVALID;
    }

    *data = rdata;

    return ONLP_STATUS_OK;
}

/**
 * @brief Free the data returned by onlp_sys_onie_data_get()
 * @param data The data pointer.
 * @notes If onlp_sysi_onie_data_get() is called to retreive the
 * contents of the ONIE system eeprom then this function
 * will be called to perform any cleanup that may be necessary
 * after the data has been used.
 */
void onlp_sysi_onie_data_free(uint8_t *data)
{
    aim_free(data);
}

int onlp_sysi_onie_info_get(onlp_onie_info_t *onie)
{
    uint8_t data[256] = {0};
    int rv = 0, id = 0;
    void *busDrv = (void *)vendor_find_driver_by_name(eeprom_dev_list[id].bus_drv_name);
    eeprom_dev_driver_t *eeprom =
        (eeprom_dev_driver_t *)vendor_find_driver_by_name(eeprom_dev_list[id].dev_drv_name);

    if (onie == NULL)
        return 0;

    vendor_dev_do_oc(eeprom_o_list[id]);
    rv = eeprom->load(
        busDrv,
        eeprom_dev_list[id].bus,
        eeprom_dev_list[id].dev,
        eeprom_dev_data_list[id].offset,
        eeprom_dev_data_list[id].alen,
        data);
    vendor_dev_do_oc(eeprom_c_list[id]);

    rv = onlp_onie_decode(onie, data, eeprom_dev_data_list[id].len);

    if (rv < 0)
    {
        return ONLP_STATUS_E_INVALID;
    }

    return ONLP_STATUS_OK;
}

/**
 * @brief This function returns the root oid list for the platform.
 * @param table [out] Receives the table.
 * @param max The maximum number of entries you can fill.
 */
int onlp_sysi_oids_get(onlp_oid_t *table, int max)
{
    int i;
    onlp_oid_t *e = table;
    memset(table, 0, max * sizeof(onlp_oid_t));

    for (i = 1; i <= psu_list_size; i++)
    {
        *e++ = ONLP_PSU_ID_CREATE(i);
    }

    for (i = 1; i <= thermal_list_size; i++)
    {
        *e++ = ONLP_THERMAL_ID_CREATE(i);
    }

    for (i = 1; i <= led_list_size; i++)
    {
        *e++ = ONLP_LED_ID_CREATE(i);
    }

    for (i = 1; i <= fan_list_size; i++)
    {
        *e++ = ONLP_FAN_ID_CREATE(i);
    }

    return ONLP_STATUS_OK;
}

/**
 * @brief This function provides a generic ioctl interface.
 * @param code context dependent.
 * @param vargs The variable argument list for the ioctl call.
 * @notes This is provided as a generic expansion and
 * and custom programming mechanism for future and non-standard
 * functionality.
 * @notes Optional
 */
int onlp_sysi_ioctl(int code, va_list vargs)
{
    return ONLP_STATUS_E_UNSUPPORTED;
}

/**
 * @brief Platform management initialization.
 */
int onlp_sysi_platform_manage_init(void)
{
    return ONLP_STATUS_E_UNSUPPORTED;
}

/**
 * @brief Perform necessary platform fan management.
 * @note This function should automatically adjust the FAN speeds
 * according to the platform conditions.
 */
int onlp_sysi_platform_manage_fans(void)
{
    return ONLP_STATUS_E_UNSUPPORTED;
}

/**
 * @brief Perform necessary platform LED management.
 * @note This function should automatically adjust the LED indicators
 * according to the platform conditions.
 */
int onlp_sysi_platform_manage_leds(void)
{
    return ONLP_STATUS_E_UNSUPPORTED;
}

/**
 * @brief Return custom platform information.
 */
int onlp_sysi_platform_info_get(onlp_platform_info_t *pi)
{
    int rv = 0, cpld_idx = 0;
    uint8_t cpld_version[cpld_list_size];
    char buffer[256] = "";

    void *busDrv = (void *)vendor_find_driver_by_name("I2C");
    cpld_dev_driver_t *cpld = (cpld_dev_driver_t *)vendor_find_driver_by_name("CPLD");

    for (cpld_idx = 0; cpld_idx < cpld_list_size; cpld_idx++)
    {
        vendor_dev_do_oc(cpld_o_list[cpld_idx]);
        rv = cpld->readb(
            busDrv,
            cpld_version_list[cpld_idx].bus,
            cpld_version_list[cpld_idx].dev,
            cpld_version_list[cpld_idx].addr,
            &cpld_version[cpld_idx]);
        vendor_dev_do_oc(cpld_c_list[cpld_idx]);

        if (rv < 0)
        {
            return ONLP_STATUS_E_INTERNAL;
        }
        sprintf(buffer, "%s \n\t\t%s: 0x%02x ", buffer, cpld_version_list[cpld_idx].name, cpld_version[cpld_idx]);
    }

    pi->cpld_versions = aim_fstrdup(buffer);

    return ONLP_STATUS_OK;
}

/**
 * @brief Friee a custom platform information structure.
 */
void onlp_sysi_platform_info_free(onlp_platform_info_t *pi)
{
    aim_free(pi->cpld_versions);
}
/**
 * @brief Builtin platform debug tool.
 */
int onlp_sysi_debug(aim_pvs_t *pvs, int argc, char **argv)
{
    return ONLP_STATUS_E_UNSUPPORTED;
}
