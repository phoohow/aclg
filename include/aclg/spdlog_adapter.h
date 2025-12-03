#pragma once

#include <aclg/aclg.h>

#ifdef __cplusplus
extern "C"
{
#endif

    // Initialize spdlog adapter and register callback. Call from application startup.
    ACLG_API void init_aclg_spdlog_adapter(const char* name);

    // Unregister adapter and release resources.
    ACLG_API void shutdown_aclg_spdlog_adapter(const char* name);

    // Initialize spdlog adapter with source info support and register callback with source info.
    // Call from application startup.
    ACLG_API void init_aclg_spdlog_adapter_with_source(const char* name);

    // Unregister adapter with source info support and release resources.
    ACLG_API void shutdown_aclg_spdlog_adapter_with_source(const char* name);

#ifdef __cplusplus
}
#endif
