#include <aclg/aclg.h>
#include <string>

int main()
{
    // Create a console logger
    aclg::ConsoleLogger* logger = aclg::create_console_logger();
    if (!logger)
    {
        return -1;
    }

    // Set the global logger
    aclg::set_logger(logger);

    // Test {} formatting with C-string (should work as before)
    const char* filepath_cstr = "example.txt";
    ACLG_INFO("Packing (C-string): {}", filepath_cstr);
    
    // Test {} formatting with std::string (this was problematic before our fix)
    std::string filepath_std = "example2.txt";
    ACLG_INFO("Packing (std::string): {}", ACLG_STRINGIFY(filepath_std));

    // Clean up
    aclg::destroy_console_logger(logger);

    return 0;
}