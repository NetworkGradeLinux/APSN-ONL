#ifndef __DPAPI_H__
#define __DPAPI_H__

#include <stdint.h>
typedef int dpapi_status;
typedef enum
{
    DPAPI_LOG_TRACE, 
    DPAPI_LOG_DEBUG, 
    DPAPI_LOG_INFO, 
    DPAPI_LOG_WARN, 
    DPAPI_LOG_ERROR, 
    DPAPI_LOG_FATAL 
} dpapi_log_level_t;

dpapi_status dpapi_log_level_set(dpapi_log_level_t level);
dpapi_status dpapi_log_quiet_set(uint8_t enable);

#endif /* __DPAPI_H__ */