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
#include <string>

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

class ACLG_API Logger
{
public:
    virtual ~Logger()                                      = default;
    virtual void  log(Level level, const std::string& msg) = 0;
    virtual void  set_level(Level level)                   = 0;
    virtual Level get_level() const                        = 0;
};

class ACLG_API NullLogger : public Logger
{
public:
    void  log(Level, const std::string&) override {}
    void  set_level(Level) override {}
    Level get_level() const override { return Level::off; }
};

class ACLG_API ConsoleLogger : public Logger
{
    Level m_level;

public:
    ConsoleLogger() : m_level(Level::info) {}
    void  log(Level level, const std::string& msg) override;
    void  set_level(Level level) override { m_level = level; }
    Level get_level() const override { return m_level; }
};

// Factory functions
ACLG_API ConsoleLogger* create_console_logger();
ACLG_API void           destroy_console_logger(ConsoleLogger* logger);

// Global logger functions
ACLG_API void    set_logger(Logger* l);
ACLG_API Logger* get_logger();
ACLG_API void    clear_logger();

// Formatting log function
ACLG_API void log(Level lvl, const char* fmt, ...);

// Convenience macros
#define ACLG_TRACE(...)    ::aclg::log(::aclg::Level::trace, __VA_ARGS__)
#define ACLG_DEBUG(...)    ::aclg::log(::aclg::Level::debug, __VA_ARGS__)
#define ACLG_INFO(...)     ::aclg::log(::aclg::Level::info, __VA_ARGS__)
#define ACLG_WARN(...)     ::aclg::log(::aclg::Level::warn, __VA_ARGS__)
#define ACLG_ERROR(...)    ::aclg::log(::aclg::Level::error, __VA_ARGS__)
#define ACLG_CRITICAL(...) ::aclg::log(::aclg::Level::critical, __VA_ARGS__)

#define ACLG_STRINGIFY(str) ((str).c_str())

} // namespace aclg
