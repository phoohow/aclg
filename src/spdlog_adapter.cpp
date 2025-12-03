#include <aclg/spdlog_adapter.h>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include <memory>
#include <string>

static std::shared_ptr<spdlog::logger> g_spdlogger;
static std::shared_ptr<spdlog::logger> g_spdlogger_src;

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

static void spdlog_callback_with_source(uint32_t level, const aclg_source_info* source, const char* message, void* user)
{
    if (!g_spdlogger_src) return;

    // Format message with source info
    std::string full_msg = std::string(source->file) + ":" + std::to_string(source->line) +
        " in " + source->function + "() - " + message;

    switch (level)
    {
        case aclg_Level_trace: g_spdlogger_src->trace(full_msg); break;
        case aclg_Level_debug: g_spdlogger_src->debug(full_msg); break;
        case aclg_Level_info: g_spdlogger_src->info(full_msg); break;
        case aclg_Level_warn: g_spdlogger_src->warn(full_msg); break;
        case aclg_Level_error: g_spdlogger_src->error(full_msg); break;
        case aclg_Level_critical: g_spdlogger_src->critical(full_msg); break;
        default: g_spdlogger_src->info(full_msg); break;
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

// Initialize spdlog adapter with source info support and register callback with source info.
ACLG_API void init_aclg_spdlog_adapter_with_source(const char* name)
{
    g_spdlogger_src = spdlog::stdout_color_mt(std::string(name) + "_src");
    g_spdlogger_src->set_level(spdlog::level::debug);
    aclg_set_logger_callback_with_source(&spdlog_callback_with_source, nullptr);
}

// Unregister adapter with source info support and release resources.
ACLG_API void shutdown_aclg_spdlog_adapter_with_source(const char* name)
{
    aclg_clear_logger_callback_with_source();
    if (g_spdlogger_src)
    {
        spdlog::drop(std::string(name) + "_src");
        g_spdlogger_src.reset();
    }
}
