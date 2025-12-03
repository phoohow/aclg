#include <aclg/aclg.h>
#include <cstdlib>
#include <cstring>
#include <cstdarg>
#include <iostream>

// Internal null logger implementation
typedef struct aclg_null_logger
{
    aclg_logger_t base;
} aclg_null_logger_t;

static void null_logger_log(aclg_logger_t* logger, aclg_level_t level, const char* fmt, va_list args)
{
    // Do nothing
}

static void null_logger_destroy(aclg_logger_t* logger)
{
    free(logger);
}

static aclg_logger_t* create_null_logger(void)
{
    aclg_null_logger_t* logger = (aclg_null_logger_t*)malloc(sizeof(aclg_null_logger_t));
    if (!logger)
    {
        return nullptr;
    }

    memset(logger, 0, sizeof(aclg_null_logger_t));
    logger->base.log     = null_logger_log;
    logger->base.destroy = null_logger_destroy;

    return (aclg_logger_t*)logger;
}

// Global logger pointer
static aclg_logger_t* g_logger = nullptr;

// Public API functions
void aclg_set_logger(aclg_logger_t* logger)
{
    // Destroy the previous logger if it exists
    if (g_logger && g_logger->destroy)
    {
        g_logger->destroy(g_logger);
    }

    g_logger = logger;
}

aclg_logger_t* aclg_get_logger(void)
{
    if (!g_logger)
    {
        // Create a null logger as default
        g_logger = create_null_logger();
    }
    return g_logger;
}

void aclg_log(aclg_level_t level, const char* fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    aclg_logger_t* logger = aclg_get_logger();
    if (logger && logger->log)
    {
        logger->log(logger, level, fmt, ap);
    }
    va_end(ap);
}