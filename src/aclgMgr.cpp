#include <aclg/aclgMgr.h>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdarg>

// Internal function implementations
static void console_logger_log(aclg_logger_t* logger, aclg_level_t level, const char* fmt, va_list args)
{
    aclg_console_logger_t* console_logger = (aclg_console_logger_t*)logger;

    if (level < console_logger->level)
    {
        return;
    }

    // Convert level to string
    const char* levelStr = nullptr;
    switch (level)
    {
        case ACLG_LEVEL_TRACE: levelStr = "TRACE"; break;
        case ACLG_LEVEL_DEBUG: levelStr = "DEBUG"; break;
        case ACLG_LEVEL_INFO: levelStr = "INFO"; break;
        case ACLG_LEVEL_WARN: levelStr = "WARN"; break;
        case ACLG_LEVEL_ERROR: levelStr = "ERROR"; break;
        case ACLG_LEVEL_CRITICAL: levelStr = "CRITICAL"; break;
        case ACLG_LEVEL_OFF: return;
    }

    // Print the log message
    std::cout << "[" << levelStr << "] ";
    vprintf(fmt, args);
    std::cout << std::endl;
}

static void console_logger_destroy(aclg_logger_t* logger)
{
    if (logger)
    {
        free(logger);
    }
}

// Public API functions
aclg_logger_t* aclg_console_logger_create(void)
{
    aclg_console_logger_t* logger = (aclg_console_logger_t*)malloc(sizeof(aclg_console_logger_t));
    if (!logger)
    {
        return nullptr;
    }

    memset(logger, 0, sizeof(aclg_console_logger_t));

    // Initialize the base logger functions
    logger->base.log     = console_logger_log;
    logger->base.destroy = console_logger_destroy;

    // Set default level
    logger->level = ACLG_LEVEL_INFO;

    return (aclg_logger_t*)logger;
}

void aclg_console_logger_set_level(aclg_logger_t* logger, aclg_level_t level)
{
    if (logger)
    {
        aclg_console_logger_t* console_logger = (aclg_console_logger_t*)logger;
        console_logger->level                 = level;
    }
}

aclg_level_t aclg_console_logger_get_level(aclg_logger_t* logger)
{
    if (logger)
    {
        aclg_console_logger_t* console_logger = (aclg_console_logger_t*)logger;
        return console_logger->level;
    }

    return ACLG_LEVEL_INFO;
}