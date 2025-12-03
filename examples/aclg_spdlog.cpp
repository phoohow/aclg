#include <aclg/aclg.h>
#include <aclg/aclg_f.h>
#include <aclg/spdlog_adapter.h>

int main()
{
    const char* name = "aclg";
    init_aclg_spdlog_adapter(name);

    ACLG_INFO("demo started: %d", 123);
    ACLG_DEBUG("debug value: %s", "hello");

    ACLG_DEBUG_F("debug value: {}", "yes, backend is spdlog");

    shutdown_aclg_spdlog_adapter(name);
    return 0;
}
