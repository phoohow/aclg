#include <aclg/aclg.h>

int main(int argc, char* argv[])
{
    // Log messages using the C API directly
    ACLG_TRACE("This is a trace message");
    ACLG_DEBUG("This is a debug message");
    ACLG_INFO("This is an info message");
    ACLG_WARN("This is a warning message");
    ACLG_ERROR("This is an error message");
    ACLG_CRITICAL("This is a critical message");

    return 0;
}