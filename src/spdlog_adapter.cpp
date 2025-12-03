#include <aclg/spdlog_adapter.h>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include <memory>

static std::shared_ptr<spdlog::logger> g_spdlogger;

static void spdlog_callback(uint32_t level, const char* message, void* user)
{
    if (!g_spdlogger) return;

    switch (level)
    {
        case aclg_Level_trace: g_spdlogger->trace(message); break;
        case aclg_Level_debug: g_spdlogger->debug(message); break;
        case aclg_Level_info: g_spdlogger->info(message); break;
        case aclg_Level_warn: g_spdlogger->warn(message); break;
        case aclg_Level_error: g_spdlogger->error(message); break;
        case aclg_Level_critical: g_spdlogger->critical(message); break;
        default: g_spdlogger->info(message); break;
    }
}

// Initialize spdlog adapter and register callback. Call from application startup.
ACLG_API void init_aclg_spdlog_adapter(const char* name)
{
    g_spdlogger = spdlog::stdout_color_mt(name);
    g_spdlogger->set_level(spdlog::level::debug);
    aclg_set_logger_callback(&spdlog_callback, nullptr);
}

// Unregister adapter and release resources.
ACLG_API void shutdown_aclg_spdlog_adapter(const char* name)
{
    aclg_clear_logger_callback();
    if (g_spdlogger)
    {
        spdlog::drop(name);
        g_spdlogger.reset();
    }
}
