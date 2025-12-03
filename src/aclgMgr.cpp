#include <aclg/aclgMgr.h>

#include <iostream>
#include <memory>
#include <cstdio>

namespace aclg
{
    void ConsoleLogger::log(Level level, const char *fmt, va_list args)
    {
        if (level < m_level)
        {
            return;
        }

        // Convert level to string
        const char *levelStr = nullptr;
        switch (level)
        {
        case Level::trace:
            levelStr = "TRACE";
            break;
        case Level::debug:
            levelStr = "DEBUG";
            break;
        case Level::info:
            levelStr = "INFO";
            break;
        case Level::warn:
            levelStr = "WARN";
            break;
        case Level::error:
            levelStr = "ERROR";
            break;
        case Level::critical:
            levelStr = "CRITICAL";
            break;
        case Level::off:
            return;
        }

        // Print the log message
        std::cout << "[" << levelStr << "] ";
        vprintf(fmt, args);
        std::cout << std::endl;
    }

} // namespace aclg
