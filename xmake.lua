set_languages("c++20")
add_rules("mode.debug", "mode.release")

option("enable_aclg_test", function()
    set_default(false)
    set_showmenu(true)
    set_description("Enable test for aclg simple")
end)

target("aclg", function()
    set_kind("headeronly")
    add_headerfiles("include/aclg/*.h")
    add_includedirs("include", { public = true })

    add_defines("SPDLOG_HEADER_ONLY")
end)

if has_config("enable_aclg_test") then
    target("aclg_simple", function()
        set_kind("binary")
        add_deps("aclg")
        add_files("examples/aclg_simple.cpp")
    end)

    target("aclg_callback", function()
        set_kind("binary")
        add_deps("aclg")
        add_files("examples/aclg_callback.cpp")
    end)
end
