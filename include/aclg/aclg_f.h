#pragma once

#include <aclg/aclg.h>

#include <string>
#include <sstream>
#include <type_traits>

// Helper function to convert any type to string
template <typename T>
std::string aclg_to_string(const T& value)
{
    if constexpr (std::is_same_v<T, bool>)
    {
        return value ? "true" : "false";
    }
    else if constexpr (std::is_arithmetic_v<T>)
    {
        if constexpr (std::is_floating_point_v<T>)
        {
            std::ostringstream oss;
            oss.precision(6);
            oss << value;
            return oss.str();
        }
        else
        {
            return std::to_string(value);
        }
    }
    else if constexpr (std::is_same_v<T, const char*>)
    {
        return std::string(value ? value : "null");
    }
    else if constexpr (std::is_same_v<T, std::string>)
    {
        return value;
    }
    else
    {
        std::ostringstream oss;
        oss << value;
        return oss.str();
    }
}

// Function to format string with {} placeholders
template <typename... Args>
std::string aclg_format(const std::string& format_str, Args&&... args)
{
    std::string                        result      = format_str;
    std::initializer_list<std::string> arg_strings = {aclg_to_string(args)...};

    for (const auto& arg : arg_strings)
    {
        auto pos = result.find("{}");
        if (pos != std::string::npos)
        {
            result.replace(pos, 2, arg);
        }
    }

    return result;
}

// Macro to stringify arguments and format them
#define ACLG_STRINGIFY(format_str, ...) aclg_format(format_str, __VA_ARGS__)

// Convenience macros with {} formatting
#define ACLG_TRACE_F(fmt, ...)    aclg_log(aclg_Level_trace, "%s", aclg_format(fmt, __VA_ARGS__).c_str())
#define ACLG_DEBUG_F(fmt, ...)    aclg_log(aclg_Level_debug, "%s", aclg_format(fmt, __VA_ARGS__).c_str())
#define ACLG_INFO_F(fmt, ...)     aclg_log(aclg_Level_info, "%s", aclg_format(fmt, __VA_ARGS__).c_str())
#define ACLG_WARN_F(fmt, ...)     aclg_log(aclg_Level_warn, "%s", aclg_format(fmt, __VA_ARGS__).c_str())
#define ACLG_ERROR_F(fmt, ...)    aclg_log(aclg_Level_error, "%s", aclg_format(fmt, __VA_ARGS__).c_str())
#define ACLG_CRITICAL_F(fmt, ...) aclg_log(aclg_Level_critical, "%s", aclg_format(fmt, __VA_ARGS__).c_str())
