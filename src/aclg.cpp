#include <aclg/aclg.h>

#include <cstdarg>
#include <cstdio>
#include <iostream>
#include <mutex>
#include <vector>

namespace aclg
{

// Atomic pointer to current logger
static std::atomic<Logger*> g_logger{nullptr};

// Holder for logger objects created by this module
static std::mutex              g_holder_mutex;
static std::unique_ptr<Logger> g_owner_holder;

// Null logger instance
static NullLogger g_null_logger;

ConsoleLogger* create_console_logger()
{
    return new ConsoleLogger();
}

void destroy_console_logger(ConsoleLogger* logger)
{
    if (!logger) return;
    // if this logger is currently registered, clear it first
    Logger* cur = g_logger.load(std::memory_order_acquire);
    if (cur == logger)
    {
        g_logger.store(nullptr, std::memory_order_release);
    }
    delete logger;
}

void set_logger(Logger* l)
{
    g_logger.store(l, std::memory_order_release);
}

Logger* get_logger()
{
    Logger* cur = g_logger.load(std::memory_order_acquire);
    return cur ? cur : static_cast<Logger*>(&g_null_logger);
}

void clear_logger()
{
    g_logger.store(nullptr, std::memory_order_release);
}

static std::string vformat(const char* fmt, va_list ap)
{
    va_list ap_copy;
    va_copy(ap_copy, ap);
    int needed = std::vsnprintf(nullptr, 0, fmt, ap_copy);
    va_end(ap_copy);
    if (needed < 0)
    {
        return std::string();
    }
    std::vector<char> buf((size_t)needed + 1);
    std::vsnprintf(buf.data(), buf.size(), fmt, ap);
    return std::string(buf.data(), (size_t)needed);
}

void log(Level lvl, const char* fmt, ...)
{
    Logger* cur = g_logger.load(std::memory_order_acquire);
    if (!cur)
    {
        cur = &g_null_logger;
    }
    // level check
    if (lvl < cur->get_level())
        return;

    va_list ap;
    va_start(ap, fmt);
    std::string msg = vformat(fmt, ap);
    va_end(ap);

    cur->log(lvl, msg);
}

void ConsoleLogger::log(Level level, const std::string& msg)
{
    if (level < m_level)
        return;

    const char* lvlstr = "unknown";
    switch (level)
    {
        case Level::trace: lvlstr = "trace"; break;
        case Level::debug: lvlstr = "debug"; break;
        case Level::info: lvlstr = "info"; break;
        case Level::warn: lvlstr = "warn"; break;
        case Level::error: lvlstr = "error"; break;
        case Level::critical: lvlstr = "critical"; break;
        default: break;
    }

    std::printf("[%s] %s\n", lvlstr, msg.c_str());
    std::fflush(stdout);
}

} // namespace aclg
