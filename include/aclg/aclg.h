#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/fmt/ostr.h>

namespace aclg
{
enum class Level
{
    trace,
    debug,
    info,
    warn,
    error,
    critical,
    off
};

struct SourceInfo
{
    const char* file;
    uint32_t    line;
    const char* function;
};

using LoggerCallback           = std::function<void(Level, const std::string&, void*)>;
using LoggerCallbackWithSource = std::function<void(Level, const SourceInfo&, const std::string&, void*)>;

namespace detail
{
inline LoggerCallback           g_callback;
inline LoggerCallbackWithSource g_callback_with_source;
inline void*                    g_user_data             = nullptr;
inline void*                    g_user_data_with_source = nullptr;
inline std::mutex               g_callback_mutex;
} // namespace detail

inline std::shared_ptr<spdlog::logger> get_default_logger() { return spdlog::default_logger(); }

inline void register_callback(LoggerCallback cb, void* user_data)
{
    std::lock_guard<std::mutex> lock(detail::g_callback_mutex);
    detail::g_callback  = std::move(cb);
    detail::g_user_data = user_data;
}

inline void register_callback_with_source(LoggerCallbackWithSource cb, void* user_data)
{
    std::lock_guard<std::mutex> lock(detail::g_callback_mutex);
    detail::g_callback_with_source  = std::move(cb);
    detail::g_user_data_with_source = user_data;
}

template <typename... Args>
inline void trace(const char* fmt, const Args&... args) { spdlog::default_logger_raw()->trace(fmt::runtime(fmt), args...); }
template <typename... Args>
inline void debug(const char* fmt, const Args&... args) { spdlog::default_logger_raw()->debug(fmt::runtime(fmt), args...); }
template <typename... Args>
inline void info(const char* fmt, const Args&... args) { spdlog::default_logger_raw()->info(fmt::runtime(fmt), args...); }
template <typename... Args>
inline void warn(const char* fmt, const Args&... args) { spdlog::default_logger_raw()->warn(fmt::runtime(fmt), args...); }
template <typename... Args>
inline void error(const char* fmt, const Args&... args) { spdlog::default_logger_raw()->error(fmt::runtime(fmt), args...); }
template <typename... Args>
inline void critical(const char* fmt, const Args&... args) { spdlog::default_logger_raw()->critical(fmt::runtime(fmt), args...); }

inline void trace(const std::string& msg) { spdlog::default_logger_raw()->trace(msg); }
inline void debug(const std::string& msg) { spdlog::default_logger_raw()->debug(msg); }
inline void info(const std::string& msg) { spdlog::default_logger_raw()->info(msg); }
inline void warn(const std::string& msg) { spdlog::default_logger_raw()->warn(msg); }
inline void error(const std::string& msg) { spdlog::default_logger_raw()->error(msg); }
inline void critical(const std::string& msg) { spdlog::default_logger_raw()->critical(msg); }

template <typename... Args>
inline void trace_s(const char* file, uint32_t line, const char* function, const char* fmt, const Args&... args) { spdlog::default_logger_raw()->log(spdlog::source_loc{file, static_cast<int>(line), function}, spdlog::level::trace, fmt::runtime(fmt), args...); }
template <typename... Args>
inline void debug_s(const char* file, uint32_t line, const char* function, const char* fmt, const Args&... args) { spdlog::default_logger_raw()->log(spdlog::source_loc{file, static_cast<int>(line), function}, spdlog::level::debug, fmt::runtime(fmt), args...); }
template <typename... Args>
inline void info_s(const char* file, uint32_t line, const char* function, const char* fmt, const Args&... args) { spdlog::default_logger_raw()->log(spdlog::source_loc{file, static_cast<int>(line), function}, spdlog::level::info, fmt::runtime(fmt), args...); }
template <typename... Args>
inline void warn_s(const char* file, uint32_t line, const char* function, const char* fmt, const Args&... args) { spdlog::default_logger_raw()->log(spdlog::source_loc{file, static_cast<int>(line), function}, spdlog::level::warn, fmt::runtime(fmt), args...); }
template <typename... Args>
inline void error_s(const char* file, uint32_t line, const char* function, const char* fmt, const Args&... args) { spdlog::default_logger_raw()->log(spdlog::source_loc{file, static_cast<int>(line), function}, spdlog::level::err, fmt::runtime(fmt), args...); }
template <typename... Args>
inline void critical_s(const char* file, uint32_t line, const char* function, const char* fmt, const Args&... args) { spdlog::default_logger_raw()->log(spdlog::source_loc{file, static_cast<int>(line), function}, spdlog::level::critical, fmt::runtime(fmt), args...); }

inline void trace_s(const char* file, uint32_t line, const char* function, const std::string& msg) { spdlog::default_logger_raw()->log(spdlog::source_loc{file, static_cast<int>(line), function}, spdlog::level::trace, msg); }
inline void debug_s(const char* file, uint32_t line, const char* function, const std::string& msg) { spdlog::default_logger_raw()->log(spdlog::source_loc{file, static_cast<int>(line), function}, spdlog::level::debug, msg); }
inline void info_s(const char* file, uint32_t line, const char* function, const std::string& msg) { spdlog::default_logger_raw()->log(spdlog::source_loc{file, static_cast<int>(line), function}, spdlog::level::info, msg); }
inline void warn_s(const char* file, uint32_t line, const char* function, const std::string& msg) { spdlog::default_logger_raw()->log(spdlog::source_loc{file, static_cast<int>(line), function}, spdlog::level::warn, msg); }
inline void error_s(const char* file, uint32_t line, const char* function, const std::string& msg) { spdlog::default_logger_raw()->log(spdlog::source_loc{file, static_cast<int>(line), function}, spdlog::level::err, msg); }
inline void critical_s(const char* file, uint32_t line, const char* function, const std::string& msg) { spdlog::default_logger_raw()->log(spdlog::source_loc{file, static_cast<int>(line), function}, spdlog::level::critical, msg); }

} // namespace aclg

// Explicit source location macros always capture source location information
#define ACLG_TRACE_S(...)    SPDLOG_LOGGER_TRACE(spdlog::default_logger_raw(), __VA_ARGS__)
#define ACLG_DEBUG_S(...)    SPDLOG_LOGGER_DEBUG(spdlog::default_logger_raw(), __VA_ARGS__)
#define ACLG_INFO_S(...)     SPDLOG_LOGGER_INFO(spdlog::default_logger_raw(), __VA_ARGS__)
#define ACLG_WARN_S(...)     SPDLOG_LOGGER_WARN(spdlog::default_logger_raw(), __VA_ARGS__)
#define ACLG_ERROR_S(...)    SPDLOG_LOGGER_ERROR(spdlog::default_logger_raw(), __VA_ARGS__)
#define ACLG_CRITICAL_S(...) SPDLOG_LOGGER_CRITICAL(spdlog::default_logger_raw(), __VA_ARGS__)

#ifdef _DEBUG
#    define ACLG_TRACE(...)    ACLG_TRACE_S(__VA_ARGS__)
#    define ACLG_DEBUG(...)    ACLG_DEBUG_S(__VA_ARGS__)
#    define ACLG_INFO(...)     ACLG_INFO_S(__VA_ARGS__)
#    define ACLG_WARN(...)     ACLG_WARN_S(__VA_ARGS__)
#    define ACLG_ERROR(...)    ACLG_ERROR_S(__VA_ARGS__)
#    define ACLG_CRITICAL(...) ACLG_CRITICAL_S(__VA_ARGS__)
#else
#    define ACLG_TRACE(...)    SPDLOG_TRACE(__VA_ARGS__)
#    define ACLG_DEBUG(...)    SPDLOG_DEBUG(__VA_ARGS__)
#    define ACLG_INFO(...)     SPDLOG_INFO(__VA_ARGS__)
#    define ACLG_WARN(...)     SPDLOG_WARN(__VA_ARGS__)
#    define ACLG_ERROR(...)    SPDLOG_ERROR(__VA_ARGS__)
#    define ACLG_CRITICAL(...) SPDLOG_CRITICAL(__VA_ARGS__)
#endif
