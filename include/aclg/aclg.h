#pragma once

#ifdef _WIN32
#    ifdef ACLG_EXPORT_DLL
#        define ACLG_API __declspec(dllexport)
#    else
#        define ACLG_API __declspec(dllimport)
#    endif
#else
#    define ACLG_API
#endif

#include <cstdarg>
#include <cstdint>

extern "C"
{

    enum aclg_Level : uint32_t
    {
        aclg_Level_trace    = 0,
        aclg_Level_debug    = 1,
        aclg_Level_info     = 2,
        aclg_Level_warn     = 3,
        aclg_Level_error    = 4,
        aclg_Level_critical = 5,
        aclg_Level_off      = 6
    };

    // Logger callback: level, null-terminated message, user_data pointer
    typedef void (*aclg_logger_cb)(uint32_t level, const char* message, void* user_data);

    // Register a logger callback and optional user_data.
    // The callback will be invoked from aclg_log.
    // This function does not take ownership of user_data.
    ACLG_API void aclg_set_logger_callback(aclg_logger_cb cb, void* user_data);
    // To unregister, call aclg_clear_logger_callback().
    ACLG_API void aclg_clear_logger_callback();

    // Log with printf-style formatting. Accepts variable args like printf.
    ACLG_API void aclg_log(uint32_t level, const char* fmt, ...);

// Convenience macros
#define ACLG_TRACE(...)    aclg_log(aclg_Level_trace, __VA_ARGS__)
#define ACLG_DEBUG(...)    aclg_log(aclg_Level_debug, __VA_ARGS__)
#define ACLG_INFO(...)     aclg_log(aclg_Level_info, __VA_ARGS__)
#define ACLG_WARN(...)     aclg_log(aclg_Level_warn, __VA_ARGS__)
#define ACLG_ERROR(...)    aclg_log(aclg_Level_error, __VA_ARGS__)
#define ACLG_CRITICAL(...) aclg_log(aclg_Level_critical, __VA_ARGS__)

} // extern "C"
