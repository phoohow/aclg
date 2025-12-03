set_languages("c++20")
add_rules("mode.debug", "mode.release")

option("enable_aclg_test", function()
    set_default(false)
    set_showmenu(true)
    set_description("Enable test for aclg simple")
end)

option("enable_aclg_spdlog", function()
    set_default(false)
    set_showmenu(true)
    set_description("Enable test for aclg spdlog adapter")
end)

if has_config("enable_aclg_spdlog") then
    add_requires("spdlog")
end

target("aclg", function()
    set_kind("shared")
    add_includedirs("include", {public = true})
    
    add_files("src/aclg.cpp")
    if has_config("enable_aclg_spdlog") then
        add_files("src/spdlog_adapter.cpp")
        add_packages("spdlog")
    end
    
    if is_plat("windows") then
        add_defines("ACLG_EXPORT_DLL")
    end
    
    add_headerfiles("include/(**.h)")
end)

if has_config("enable_aclg_test") then
    target("aclg_simple", function()
        set_kind("binary")
        add_deps("aclg")
        add_includedirs("include")
        add_files("examples/aclg_simple.cpp")
    end)
    
    target("aclg_format", function()
        set_kind("binary")
        add_deps("aclg")
        add_includedirs("include")
        add_files("examples/aclg_format.cpp")
    end)
    
    target("aclg_source", function()
        set_kind("binary")
        add_deps("aclg")
        add_includedirs("include")
        add_files("examples/aclg_source.cpp")
    end)
end

if has_config("enable_aclg_spdlog") then
    target("aclg_spdlog", function()
        set_kind("binary")
        add_deps("aclg")
        add_includedirs("include")
        add_files("examples/aclg_spdlog.cpp")
    end)
    
    target("aclg_spdlog_source", function()
        set_kind("binary")
        add_deps("aclg")
        add_includedirs("include")
        add_files("examples/aclg_spdlog_source.cpp")
    end)
end
