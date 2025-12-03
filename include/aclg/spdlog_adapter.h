#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

    // Initialize spdlog adapter and register callback. Call from application startup.
    void init_aclg_spdlog_adapter();

    // Unregister adapter and release resources.
    void shutdown_aclg_spdlog_adapter();

#ifdef __cplusplus
}
#endif
