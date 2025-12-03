#include <aclg/aclg.h>

int main(int argc, char* argv[])
{
    // Create console logger
    aclg::ConsoleLogger* logger = aclg::create_console_logger();
    if (!logger)
    {
        return -1;
    }

    // Set logger
    aclg::set_logger(logger);

    // Set log level
    logger->set_level(aclg::Level::debug);

    // Log messages
    ACLG_TRACE("This is a trace message");
    ACLG_DEBUG("This is a debug message");
    ACLG_INFO("This is an info message");
    ACLG_WARN("This is a warning message");
    ACLG_ERROR("This is an error message");
    ACLG_CRITICAL("This is a critical message");

    // Clean up
    aclg::destroy_console_logger(logger);

    return 0;
}