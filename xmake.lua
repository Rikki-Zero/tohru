add_rules("mode.debug", "mode.release")
add_rules("plugin.compile_commands.autoupdate", {outputdir = ".vscode"})

add_includedirs("src","kobayashi-std")

target("kobayashi-std")
    set_kind("shared")
    set_languages("c11")
    set_optimize("fastest")
    add_files("kobayashi-std/**.c")

target("tohru")
    set_kind("binary")
    set_languages("c11")
    set_optimize("fastest")
    add_files("src/**.c")