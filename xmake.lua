add_rules("mode.debug", "mode.release")
add_rules("plugin.compile_commands.autoupdate", {outputdir = ".vscode"})

add_includedirs("src")

target("tohru")
    set_kind("binary")
    set_languages("c11")
    set_optimize("fastest")

    add_files("src/**.c")