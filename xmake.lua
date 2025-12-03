set_languages("c++20")
add_rules("mode.debug", "mode.release")

option("test_aclg_simple", function()
    set_default(false)
    set_showmenu(true)
    set_description("Enable test for aclg_simple")
end)

target("aclg", function()
    set_kind("shared")
    add_includedirs("include", { public = true })
    add_files("src/*.cpp")

    if is_plat("windows") then
        add_defines("ACLG_EXPORT_DLL")
    end

    add_headerfiles("include/(**.h)")

    set_targetdir("$(buildir)/lib")
end)

if has_config("test_aclg_simple") then
    target("aclg_simple", function()
        set_kind("binary")
        add_deps("aclg")
        add_includedirs("include")
        add_files("examples/aclg_simple.cpp")
        set_targetdir("$(buildir)/examples")
    end)
end
