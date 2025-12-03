#pragma once

#include <cstdarg>
#include <stdio.h>
#include <stdlib.h>

#ifdef ACLG_EXPORT_DLL
#    define ACLG_API __declspec(dllexport)
#elif defined(ACLG_STATIC)
#    define ACLG_API
#else
#    define ACLG_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C"
{
#endif

    typedef enum aclg_level
    {
        ACLG_LEVEL_TRACE,
        ACLG_LEVEL_DEBUG,
        ACLG_LEVEL_INFO,
        ACLG_LEVEL_WARN,
        ACLG_LEVEL_ERROR,
        ACLG_LEVEL_CRITICAL,
        ACLG_LEVEL_OFF
    } aclg_level_t;

    // Logger structure - equivalent to C++ Logger class
    typedef struct aclg_logger
    {
        void (*log)(struct aclg_logger* logger, aclg_level_t level, const char* fmt, va_list args);
        void (*destroy)(struct aclg_logger* logger);
    } aclg_logger_t;

    // Global logger functions
    ACLG_API void           aclg_set_logger(aclg_logger_t* logger);
    ACLG_API aclg_logger_t* aclg_get_logger(void);

    // Logging functions
    ACLG_API void aclg_log(aclg_level_t level, const char* fmt, ...);

// Convenience macros
#define ACLG_TRACE(fmt, ...)    aclg_log(ACLG_LEVEL_TRACE, fmt, ##__VA_ARGS__)
#define ACLG_DEBUG(fmt, ...)    aclg_log(ACLG_LEVEL_DEBUG, fmt, ##__VA_ARGS__)
#define ACLG_INFO(fmt, ...)     aclg_log(ACLG_LEVEL_INFO, fmt, ##__VA_ARGS__)
#define ACLG_WARN(fmt, ...)     aclg_log(ACLG_LEVEL_WARN, fmt, ##__VA_ARGS__)
#define ACLG_ERROR(fmt, ...)    aclg_log(ACLG_LEVEL_ERROR, fmt, ##__VA_ARGS__)
#define ACLG_CRITICAL(fmt, ...) aclg_log(ACLG_LEVEL_CRITICAL, fmt, ##__VA_ARGS__)

#ifdef __cplusplus
}
#endif