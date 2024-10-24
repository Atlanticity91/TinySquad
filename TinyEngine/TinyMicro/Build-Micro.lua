project "TinyMicro"
    kind "StaticLib"
    language "C++"
    cdialect "C17"
    cppdialect "C++20"
    staticruntime "off"

    defines { "_CRT_SECURE_NO_WARNINGS", "TM_BUILD" }

    pchheader "TinyMicro/__tiny_micro_pch.h"
    pchsource "%{wks.location}/TinyEngine/TinyMicro/__tiny_micro_pch.cpp"

    files { "**.h", "**.cpp", "**.hpp", "**.c" }

    vulkan = os.getenv( "VULKAN_PATH" )

    includedirs { 
        "%{wks.location}/",
        "%{wks.location}/TinyEngine/",
        vulkan.."/Include/" 
    }
    externalincludedirs {
        "%{wks.location}/",
        "%{wks.location}/TinyEngine/",
        vulkan.."/Include/" 
    }

    targetdir "%{wks.location}/bin/"
    objdir "%{wks.location}/bin-int/%{prj.name}"

    links { "TinyThirdparty" }

    filter "system:windows"
        systemversion "latest"
        defines { "WINDOWS" }
        flags { "MultiProcessorCompile" }

    filter "configurations:Debug"
        defines { "DEBUG", "TINY_DEBUG" }
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines { "RELEASE", "TINY_DEBUG" }
        runtime "Release"
        optimize "On"
        symbols "On"

    filter "configurations:Dist"
        defines { "DIST" }
        runtime "Release"
        optimize "On"
        symbols "Off"
