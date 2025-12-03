#pragma once

#include <cstdarg>
#include <memory>

#ifdef ACLG_EXPORT_DLL
#define ACLG_API __declspec(dllexport)
#elif defined(ACLG_STATIC)
#define ACLG_API
#else
#define ACLG_API __declspec(dllimport)
#endif

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

    struct ACLG_API Logger
    {
        virtual ~Logger() = default;
        virtual void log(Level lvl, const char *fmt, va_list args) = 0;
    };

    class ACLG_API NullLogger : public Logger
    {
    public:
        void log(Level, const char *, va_list) override {}
    };

    inline Logger *&global_logger_ptr()
    {
        static Logger *g = nullptr;
        return g;
    }

    inline void set_logger(std::shared_ptr<Logger> l)
    {
        static std::shared_ptr<Logger> holder;
        holder = std::move(l);
        global_logger_ptr() = holder.get();
    }

    inline Logger *get_logger()
    {
        if (!global_logger_ptr())
        {
            static NullLogger nl;
            global_logger_ptr() = &nl;
        }
        return global_logger_ptr();
    }

    inline void log(Level lvl, const char *fmt, ...)
    {
        va_list ap;
        va_start(ap, fmt);
        get_logger()->log(lvl, fmt, ap);
        va_end(ap);
    }

#define ACLG_TRACE(fmt, ...) ::aclg::log(::aclg::Level::trace, fmt, ##__VA_ARGS__)
#define ACLG_DEBUG(fmt, ...) ::aclg::log(::aclg::Level::debug, fmt, ##__VA_ARGS__)
#define ACLG_INFO(fmt, ...) ::aclg::log(::aclg::Level::info, fmt, ##__VA_ARGS__)
#define ACLG_WARN(fmt, ...) ::aclg::log(::aclg::Level::warn, fmt, ##__VA_ARGS__)
#define ACLG_ERROR(fmt, ...) ::aclg::log(::aclg::Level::error, fmt, ##__VA_ARGS__)
#define ACLG_CRITICAL(fmt, ...) ::aclg::log(::aclg::Level::critical, fmt, ##__VA_ARGS__)

} // namespace aclg
