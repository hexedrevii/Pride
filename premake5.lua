workspace "Pride"
    configurations { "Debug", "Release" }
    location "build"


-- SDL compilation
project "SDL"
    kind "StaticLib"
    language "C"
    targetdir "bin/%{cfg.buildcfg}"
    location "Pride/External/SDL"

    files {
        "Pride/External/SDL/src/*.c",
        "Pride/External/SDL/include/**.h"
    }

    includedirs { 
        "Pride/External/SDL/include",
        "Pride/External/SDL/include/build_config",
        "Pride/External/SDL/src"
    }

    defines { "SDL_STATIC", "HAVE_LIBC" }


-- SDL_image compilation
project "SDL_image"
    kind "StaticLib"
    language "C"
    targetdir "bin/%{cfg.buildcfg}"
    location "Pride/External/SDL_image"

    files { "Pride/External/SDL_image/*.c" }

    includedirs {
        "Pride/External/SDL/include",
        "Pride/External/SDL_image/include"
    }

    libdirs { "bin/%{cfg.buildcfg}" }
    links { "SDL3" }


project "Pride"
    kind "StaticLib"
    language "C++"
    buildoptions { "-std=c++23" }
    targetdir "bin/%{cfg.buildcfg}"

    files { "Pride/Source/**.cpp", "Pride/Headers/**.h" }

    includedirs {
        -- Self
        "Pride/Headers",

        -- SDL
        "Pride/External/SDL/include",
        "Pride/External/SDL_image/include"
    }

    libdirs { "bin/%{cfg.buildcfg}" }
    links { "SDL3", "SDL3_image" }

    filter "configurations:Debug"
        symbols "On"

    filter "configurations:Release"
        optimize "On"


-- Test window
newoption {
    trigger = "compile-example",
    description = "Build text executable."
}

if _OPTIONS["compile-example"] then
    project "WindowExample"
        kind "ConsoleApp"
        language "C++"
        buildoptions { "-std=c++23" }
        targetdir "bin/%{cfg.buildcfg}"

        files { "Examples/window.cpp" }

        includedirs {
            -- Engine
            "Pride/Headers",

            -- SDL
            "Pride/External/SDL/include",
            "Pride/External/SDL_image/include"
        }

        libdirs { "bin/%{cfg.buildcfg}" }
        links { "Pride", "SDL3", "SDL3_image" }
end