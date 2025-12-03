#include <aclg/aclgMgr.h>
#include <iostream>
#include <memory>

int main()
{
    // Create and set logger
    auto logger = std::make_shared<aclg::ConsoleLogger>();
    aclg::set_logger(logger);

    // Use logging
    ACLG_INFO("Application started");
    ACLG_DEBUG("Debug message: %d", 42);
    ACLG_WARN("Warning message");
    ACLG_ERROR("Error occurred: %s", "Something went wrong");

    return 0;
}