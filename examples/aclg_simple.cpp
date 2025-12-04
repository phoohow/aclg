#include <aclg/aclg.h>
#include <iostream>

void basic_logging()
{
    std::cout << "\n=== Basic Logging Demo ===" << std::endl;

    ACLG_INFO("macro info");
    ACLG_DEBUG("macro debug: value = {}", 42);
    ACLG_WARN("macro warn");
    ACLG_ERROR("macro error: An error occurred - {}", "Something went wrong");
    ACLG_CRITICAL("macro critical: Critical error - Program will terminate");
}

void log_levels()
{
    std::cout << "\n=== Log Levels Demo ===" << std::endl;

    aclg::trace("func trace: Most detailed");
    aclg::debug("func debug: Used during development");
    aclg::info("func info: Normal operation status");
    aclg::warn("func warn: Potential issues");
    aclg::error("func error: Errors occurred");
    aclg::critical("func critical: Program may not continue");
}

void source_info_logging()
{
    std::cout << "\n=== Logging With Source Info Demo ===" << std::endl;

    // In debug mode, these macros are the same as the _S variants (include source location)
    // In release mode, they don't include source location information and lower levels are disabled
    ACLG_INFO("mac info: Normal operation status");
    ACLG_WARN("mac warn: Potential issues");

    // Explicit source location macros always capture source location information
    ACLG_INFO_S("mac info with source: Normal operation status");
    ACLG_WARN_S("mac warn with source: Potential issues");

    // Manual way (not recommended)
    aclg::info_s(__FILE__, __LINE__, __FUNCTION__, "fun info with source: Normal operation status");
}

int main()
{
    std::cout << "ACLG Logging Library Example Program" << std::endl;
    std::cout << "===================================" << std::endl;

    basic_logging();
    log_levels();
    source_info_logging();

    std::cout << "\nExample program completed" << std::endl;
    return 0;
}