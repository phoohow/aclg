#include <aclg/aclgMgr.h>
#include <iostream>

int main()
{
    // Create and set logger
    aclg_logger_t* logger = aclg_console_logger_create();
    aclg_set_logger(logger);

    // Use logging
    ACLG_INFO("Application started");
    ACLG_DEBUG("Debug message: %d", 42);
    ACLG_WARN("Warning message");
    ACLG_ERROR("Error occurred: %s", "Something went wrong");

    // Change log level
    aclg_console_logger_set_level(logger, ACLG_LEVEL_DEBUG);
    ACLG_DEBUG("This debug message should now appear");

    // Cleanup
    if (logger && logger->destroy)
    {
        logger->destroy(logger);
    }

    return 0;
}