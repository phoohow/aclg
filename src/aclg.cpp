#include "aclg/aclg.h"

#include <atomic>
#include <cstdarg>
#include <cstdio>
#include <cstdint>
#include <cstring>
#include <string>
#include <vector>

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

extern "C"
{

    static std::atomic<aclg_logger_cb>             g_cb{nullptr};
    static std::atomic<void*>                      g_user{nullptr};
    static std::atomic<aclg_logger_cb_with_source> g_cb_src{nullptr};
    static std::atomic<void*>                      g_user_src{nullptr};

    ACLG_API void aclg_set_logger_callback(aclg_logger_cb cb, void* user_data)
    {
        g_user.store(user_data, std::memory_order_release);
        g_cb.store(cb, std::memory_order_release);
    }

    ACLG_API void aclg_clear_logger_callback()
    {
        g_cb.store(nullptr, std::memory_order_release);
        g_user.store(nullptr, std::memory_order_release);
    }

    ACLG_API void aclg_set_logger_callback_with_source(aclg_logger_cb_with_source cb, void* user_data)
    {
        g_user_src.store(user_data, std::memory_order_release);
        g_cb_src.store(cb, std::memory_order_release);
    }

    ACLG_API void aclg_clear_logger_callback_with_source()
    {
        g_cb_src.store(nullptr, std::memory_order_release);
        g_user_src.store(nullptr, std::memory_order_release);
    }

    ACLG_API void aclg_log(uint32_t level, const char* fmt, ...)
    {
        aclg_logger_cb cb   = g_cb.load(std::memory_order_acquire);
        void*          user = g_user.load(std::memory_order_acquire);

        va_list ap;
        va_start(ap, fmt);
        std::string msg = vformat(fmt, ap);
        va_end(ap);

        if (cb)
        {
            cb(level, msg.c_str(), user);
            return;
        }

        const char* lvlstr = "UNKNOWN";
        switch (level)
        {
            case 0: lvlstr = "TRACE"; break;
            case 1: lvlstr = "DEBUG"; break;
            case 2: lvlstr = "INFO"; break;
            case 3: lvlstr = "WARN"; break;
            case 4: lvlstr = "ERROR"; break;
            case 5: lvlstr = "CRITICAL"; break;
            default: break;
        }

        std::printf("[%s] %s\n", lvlstr, msg.c_str());
        std::fflush(stdout);
    }

    ACLG_API void aclg_log_with_source(uint32_t level, const char* file, uint32_t line, const char* function, const char* fmt, ...)
    {
        aclg_logger_cb_with_source cb_src   = g_cb_src.load(std::memory_order_acquire);
        void*                      user_src = g_user_src.load(std::memory_order_acquire);

        va_list ap;
        va_start(ap, fmt);
        std::string msg = vformat(fmt, ap);
        va_end(ap);

        aclg_source_info source = {file, line, function};

        if (cb_src)
        {
            cb_src(level, &source, msg.c_str(), user_src);
            return;
        }

        const char* lvlstr = "UNKNOWN";
        switch (level)
        {
            case 0: lvlstr = "TRACE"; break;
            case 1: lvlstr = "DEBUG"; break;
            case 2: lvlstr = "INFO"; break;
            case 3: lvlstr = "WARN"; break;
            case 4: lvlstr = "ERROR"; break;
            case 5: lvlstr = "CRITICAL"; break;
            default: break;
        }

        std::printf("[%s] %s:%u in %s() - %s\n", lvlstr, file, line, function, msg.c_str());
        std::fflush(stdout);
    }

} // extern "C"
