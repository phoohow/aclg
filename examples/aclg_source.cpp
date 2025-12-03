#include <aclg/aclg.h>
#include <aclg/aclg_f.h>

void example_function()
{
    ACLG_INFO_S("Called from example_function");
    ACLG_WARN_S("Warning: %s", "something");
    ACLG_ERROR_S("Error code: %d", 42);
}

int main(int argc, char* argv[])
{
    ACLG_INFO_S("Application started");

    ACLG_DEBUG_S("Debug with source: %s", "hello");
    ACLG_TRACE_S("Trace message from main");

    example_function();

    ACLG_INFO_FS("Application started with {} args", argc);
    ACLG_DEBUG_FS("Using formatted string: {}", "hello world");
    ACLG_ERROR_FS("Error occurred at level {}", 5);

    return 0;
}
