project "TinyEngine"
    kind "SharedLib"
    language "C++"
    cdialect "C17"
    cppdialect "C++20"
    staticruntime "off"

    defines { "_CRT_SECURE_NO_WARNINGS", "TE_BUILD" }

    files { "**.h", "**.cpp", "**.hpp", "**.c" }

    pchheader "TinyEngine/__tiny_engine_pch.h"
    pchsource "%{wks.location}/TinyEngine/TinyEngine/__tiny_engine_pch.cpp"

    vulkan = os.getenv( "VULKAN_PATH" )

    includedirs {
        "%{wks.location}/",
        "%{wks.location}/TinyLibs/",
        "%{wks.location}/TinyEngine/",
        vulkan.."/Include/"
    }

    externalincludedirs {  
        "%{wks.location}/",
        "%{wks.location}/TinyLibs/",
        "%{wks.location}/TinyEngine/",
        vulkan.."/Include/" 
    } 

    targetdir "%{wks.location}/bin/"
    objdir "%{wks.location}/bin-int/%{prj.name}"

    links { "TinyMicro" }

    filter "system:windows"
        systemversion "latest"
        defines { "WINDOWS" }
        links {
            vulkan.."/Lib/SPIRV.lib",
            vulkan.."/Lib/vulkan-1.lib",
            "%{wks.location}/bin/Thirdparty/GLFW.lib",
            "%{wks.location}/bin/Thirdparty/Lz4.lib",
            "%{wks.location}/bin/Thirdparty/EOSSDK-Win64-Shipping.lib",
            "%{wks.location}/bin/Thirdparty/steam_api64.lib",
            "%{wks.location}/bin/Thirdparty/FreeType.lib",
            "%{wks.location}/bin/Thirdparty/MSDF.lib",
            "%{wks.location}/bin/Thirdparty/MSDF-Atlas.lib",
            "%{wks.location}/bin/Thirdparty/Lua.lib",
            "%{wks.location}/bin/Thirdparty/Yaml.lib",
            "%{wks.location}/bin/Thirdparty/ImGui.lib"
        }
        libdirs { 
            "%{wks.location}/bin/",
            "%{wks.location}/bin/Thirdparty/"
        }

    filter "configurations:Debug"
        defines { "DEBUG", "TINY_DEBUG" }
        runtime "Debug"
        optimize "Off"
        symbols "On"
        links {
            vulkan.."/Lib/shadercd.lib",
            vulkan.."/Lib/shaderc_combinedd.lib",
            vulkan.."/Lib/shaderc_utild.lib"
        }

    filter "configurations:Release"
        defines { "RELEASE", "TINY_DEBUG" }
        runtime "Release"
        optimize "On"
        symbols "On"
        links {
            vulkan.."/Lib/shaderc.lib",
            vulkan.."/Lib/shaderc_combined.lib",
            vulkan.."/Lib/shaderc_util.lib"
        }

    filter "configurations:Dist"
        defines { "DIST" }
        runtime "Release"
        optimize "On"
        symbols "Off"
        links {
            vulkan.."/Lib/shaderc.lib",
            vulkan.."/Lib/shaderc_combined.lib",
            vulkan.."/Lib/shaderc_util.lib"
        }
