#pragma once

#include <aclg/aclg.h>

#ifdef __cplusplus
extern "C"
{
#endif

    // Console logger implementation
    typedef struct aclg_console_logger
    {
        aclg_logger_t base;
        aclg_level_t  level;
    } aclg_console_logger_t;

    ACLG_API aclg_logger_t* aclg_console_logger_create(void);
    ACLG_API void           aclg_console_logger_set_level(aclg_logger_t* logger, aclg_level_t level);
    ACLG_API aclg_level_t   aclg_console_logger_get_level(aclg_logger_t* logger);

#ifdef __cplusplus
}
#endif