#pragma once

#include <aclg/aclg.h>
#include <memory>

namespace aclg
{

    // Console logger implementation
    class ACLG_API ConsoleLogger : public Logger
    {
    public:
        void log(Level level, const char *fmt, va_list args) override;

        void set_level(Level level) { m_level = level; }
        Level get_level() const { return m_level; }

    private:
        Level m_level = Level::info;
    };

} // namespace aclg
