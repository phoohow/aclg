#include <aclg/aclg_f.h>
#include <iostream>
#include <string>

// Console logger callback
void console_logger(uint32_t level, const char* message, void* user_data)
{
    const char* level_str = "";
    switch (level)
    {
        case aclg_Level_trace: level_str = "TRACE"; break;
        case aclg_Level_debug: level_str = "DEBUG"; break;
        case aclg_Level_info: level_str = "INFO"; break;
        case aclg_Level_warn: level_str = "WARN"; break;
        case aclg_Level_error: level_str = "ERROR"; break;
        case aclg_Level_critical: level_str = "CRITICAL"; break;
        default: level_str = "UNKNOWN"; break;
    }

    std::cout << "[" << level_str << "] " << message << std::endl;
}

int main()
{
    // Set up console logger
    aclg_set_logger_callback(console_logger, nullptr);

    // Test printf-style formatting with C-string
    const char* filepath_cstr = "example.txt";
    ACLG_INFO("Packing (C-string): %s", filepath_cstr);

    // Test printf-style formatting with std::string
    std::string filepath_std = "example2.txt";
    ACLG_INFO("Packing (std::string): %s", filepath_std.c_str());

    // Test the new {} formatting macros
    std::string name   = "Alice";
    int         age    = 30;
    double      height = 5.6;

    ACLG_INFO_F("Person info: name={}, age={}, height={}", name, age, height);
    ACLG_DEBUG_F("Testing with integers: {} + {} = {}", 5, 3, 5 + 3);
    ACLG_WARN_F("Warning: {} is greater than {}", 10, 5);

    // Test with boolean
    bool is_valid = true;
    ACLG_ERROR_F("Validation result: {}", is_valid);

    // Test with C-strings
    const char* cstr = "Hello World";
    ACLG_CRITICAL_F("C-string test: {}", cstr);

    // Clean up
    aclg_clear_logger_callback();

    return 0;
}