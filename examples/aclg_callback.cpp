#include <aclg/aclg.h>

#include <iostream>
#include <fstream>
#include <string>

// Callback function for basic logging (no source info)
void log_callback(aclg::Level level, const std::string& message, void* user_data)
{
    std::ofstream* log_file = static_cast<std::ofstream*>(user_data);
    if (log_file && log_file->is_open())
    {
        *log_file << "[LEVEL " << static_cast<int>(level) << "] " << message << std::endl;
    }
}

// Callback function with source information
void log_callback_with_source(aclg::Level level, const aclg::SourceInfo& source_info, const std::string& message, void* user_data)
{
    std::ofstream* log_file = static_cast<std::ofstream*>(user_data);
    if (log_file && log_file->is_open())
    {
        *log_file << "[LEVEL " << static_cast<int>(level) << "] "
                  << source_info.file << "(" << source_info.line << ") "
                  << source_info.function << ": " << message << std::endl;
    }
}

int main()
{
    std::cout << "\n=== Callback Registration Demo ===" << std::endl;

    // Open a file for logging
    std::ofstream log_file("callback_demo.log");

    if (!log_file.is_open())
    {
        ACLG_ERROR("Failed to open log file for callback demo");
        return 1;
    }

    // Register basic callback (no source info)
    aclg::register_callback(log_callback, &log_file);

    ACLG_INFO("macro info: Normal operation status");
    ACLG_WARN("macro warn: Potential issues");

    // Register callback with source information
    aclg::register_callback_with_source(log_callback_with_source, &log_file);

    ACLG_INFO_S("macro info with source: Normal operation status");
    ACLG_WARN_S("macro warn with source: Potential issues");

    // Close the file
    log_file.close();

    ACLG_INFO("macro info: Callback demo completed. Check callback_demo.log for results.");

    return 0;
}