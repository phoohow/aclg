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

    // Source code information structure
    struct aclg_source_info
    {
        const char* file;     // Source file path
        uint32_t    line;     // Line number
        const char* function; // Function name
    };

    // Logger callback: level, null-terminated message, user_data pointer
    typedef void (*aclg_logger_cb)(uint32_t level, const char* message, void* user_data);

    // Logger callback with source info: level, source info, null-terminated message, user_data pointer
    typedef void (*aclg_logger_cb_with_source)(uint32_t level, const aclg_source_info* source, const char* message, void* user_data);

    // Register a logger callback and optional user_data.
    // The callback will be invoked from aclg_log.
    // This function does not take ownership of user_data.
    ACLG_API void aclg_set_logger_callback(aclg_logger_cb cb, void* user_data);
    // To unregister, call aclg_clear_logger_callback().
    ACLG_API void aclg_clear_logger_callback();

    // Register a logger callback with source info support
    ACLG_API void aclg_set_logger_callback_with_source(aclg_logger_cb_with_source cb, void* user_data);
    // To unregister, call aclg_clear_logger_callback_with_source().
    ACLG_API void aclg_clear_logger_callback_with_source();

    // Log with printf-style formatting. Accepts variable args like printf.
    ACLG_API void aclg_log(uint32_t level, const char* fmt, ...);

    // Log with source info and printf-style formatting.
    ACLG_API void aclg_log_with_source(uint32_t level, const char* file, uint32_t line, const char* function, const char* fmt, ...);

// Convenience macros (printf-style)
#define ACLG_TRACE(...)    aclg_log(aclg_Level_trace, __VA_ARGS__)
#define ACLG_DEBUG(...)    aclg_log(aclg_Level_debug, __VA_ARGS__)
#define ACLG_INFO(...)     aclg_log(aclg_Level_info, __VA_ARGS__)
#define ACLG_WARN(...)     aclg_log(aclg_Level_warn, __VA_ARGS__)
#define ACLG_ERROR(...)    aclg_log(aclg_Level_error, __VA_ARGS__)
#define ACLG_CRITICAL(...) aclg_log(aclg_Level_critical, __VA_ARGS__)

// Convenience macros with source info (printf-style)
#define ACLG_TRACE_S(...)    aclg_log_with_source(aclg_Level_trace, __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__)
#define ACLG_DEBUG_S(...)    aclg_log_with_source(aclg_Level_debug, __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__)
#define ACLG_INFO_S(...)     aclg_log_with_source(aclg_Level_info, __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__)
#define ACLG_WARN_S(...)     aclg_log_with_source(aclg_Level_warn, __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__)
#define ACLG_ERROR_S(...)    aclg_log_with_source(aclg_Level_error, __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__)
#define ACLG_CRITICAL_S(...) aclg_log_with_source(aclg_Level_critical, __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__)

} // extern "C"
