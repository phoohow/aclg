#include <aclg/aclg.h>
#include <aclg/aclg_f.h>
#include <aclg/spdlog_adapter.h>

void example_function()
{
    ACLG_INFO_S("Called from example_function");
    ACLG_WARN_S("Warning: %s", "something");
    ACLG_ERROR_S("Error code: %d", 42);
}

int main()
{
    const char* name = "aclg";
    init_aclg_spdlog_adapter_with_source(name);

    ACLG_INFO_S("Application started");
    ACLG_DEBUG_S("Debug with source: %s", "hello");
    ACLG_TRACE_S("Trace message from main");

    example_function();

    shutdown_aclg_spdlog_adapter_with_source(name);
    return 0;
}
