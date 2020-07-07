/************************************************************
 * <bsn.cl fy=2017 v=onl>
 *
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
#ifndef __PLATFORM_LIB_H__
#define __PLATFORM_LIB_H__

#include "x86_64_stordis_bf2556x_1t_log.h"

#define NUM_OF_THERMAL_ON_MAIN_BROAD    4
#define NUM_OF_LED_ON_MAIN_BROAD        8
#define NUM_OF_PSU_ON_MAIN_BROAD        2
#define NUM_OF_FAN_ON_MAIN_BROAD        8
#define NUM_OF_FAN_ON_PSU_BROAD         2
#define NUM_OF_FAN                      NUM_OF_FAN_ON_MAIN_BROAD + NUM_OF_FAN_ON_PSU_BROAD
#define NUM_OF_SFP                      48
#define NUM_OF_QSFP                     8
                                       
#define OS_MAX_MSG_SIZE                 100

enum onlp_led_id
{
    LED_RESERVED = 0,
    LED_FAN,
    LED_SYS,
    LED_PSU1,
    LED_PSU2,
    LED_FAN_TRAY_1,
    LED_FAN_TRAY_2,
    LED_FAN_TRAY_3,
    LED_FAN_TRAY_4
};

enum onlp_fan_id
{    
    FAN_RESERVED = 0,    
    FAN_1_ON_FAN_BOARD,    
    FAN_2_ON_FAN_BOARD, 
    FAN_3_ON_FAN_BOARD,
    FAN_4_ON_FAN_BOARD,
    FAN_5_ON_FAN_BOARD,
    FAN_6_ON_FAN_BOARD,
    FAN_7_ON_FAN_BOARD,
    FAN_8_ON_FAN_BOARD
};

enum onlp_psu_id
{    
    PSU_RESERVED = 0,    
    PSU_1,
    PSU_2
};

enum onlp_thermal_id
{    
    THERMAL_RESERVED = 0,    
    THERMAL_1_ON_MAIN_BOARD,
    THERMAL_2_ON_MAIN_BOARD,
    THERMAL_3_ON_MAIN_BOARD,
    THERMAL_4_ON_MAIN_BOARD
};

enum led_light_mode 
{
    LED_MODE_OFF = 0,
    LED_MODE_GREEN = 1,
    LED_MODE_RED = 2,
    LED_MODE_FAN_TRAY_GREEN = 1,
    LED_MODE_SYS_RED = 3,
    LED_MODE_FAN_TRAY_AMBER = 0,
    LED_MODE_GREEN_BLINK = 2,
    LED_MODE_UNKNOWN
};

#endif  /* __PLATFORM_LIB_H__ */

