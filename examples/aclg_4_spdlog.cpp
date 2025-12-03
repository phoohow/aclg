#include "aclg/aclg.h"
#include "aclg/spdlog_adapter.h"

int main()
{
    init_aclg_spdlog_adapter();

    ACLG_INFO("demo started: %d", 123);
    ACLG_DEBUG("debug value: %s", "hello");

    shutdown_aclg_spdlog_adapter();
    return 0;
}
