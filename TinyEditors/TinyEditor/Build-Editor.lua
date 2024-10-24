project "TinyEditor"
	kind "ConsoleApp"
	language "C++"
	cdialect "C17"
	cppdialect "C++20"
	staticruntime "off"

	defines { "_CRT_SECURE_NO_WARNINGS" }

	files { "**.h", "**.hpp", "**.cpp" }

	pchheader "TinyEditor/__tiny_edittor_pch.h"
	pchsource "%{wks.location}/TinyEditors/TinyEditor/__tiny_edittor_pch.cpp"

	vulkan = os.getenv( "VULKAN_PATH" )

	includedirs {
        "%{wks.location}/",
        "%{wks.location}/TinyEditors/",
        "%{wks.location}/TinyLibs/",
        "%{wks.location}/TinyEngine/",
        vulkan.."/Include/"
    }

    externalincludedirs {
        "%{wks.location}/",
        "%{wks.location}/TinyEditors/",
        "%{wks.location}/TinyLibs/",
        "%{wks.location}/TinyEngine/",
        vulkan.."/Include/" 
    } 

    targetdir "%{wks.location}/bin/"
    debugdir "%{wks.location}/bin/"
    objdir "%{wks.location}/bin-int/%{prj.name}"

    links { "TinyEngine", "ImGui" }
    
    filter "system:windows"
        systemversion "latest"
        defines { "WINDOWS" }
        flags { "MultiProcessorCompile" }
        links {
            vulkan.."/Lib/SPIRV.lib",
            vulkan.."/Lib/vulkan-1.lib",
        }

    filter "configurations:Debug"
        defines { "DEBUG" }
        runtime "Debug"
        symbols "On"
        links {
            vulkan.."/Lib/shadercd.lib",
            vulkan.."/Lib/shaderc_combinedd.lib",
            vulkan.."/Lib/shaderc_utild.lib"
        }

    filter "configurations:Release"
        defines { "RELEASE" }
        runtime "Release"
        optimize "On"
        symbols "On"
        links {
            vulkan.."/Lib/shaderc.lib",
            vulkan.."/Lib/shaderc_combined.lib",
            vulkan.."/Lib/shaderc_util.lib"
        }

    filter "configurations:Dist"
        kind "WindowedApp"
        defines { "DIST" }
        runtime "Release"
        optimize "On"
        symbols "Off"
        links {
            vulkan.."/Lib/shaderc.lib",
            vulkan.."/Lib/shaderc_combined.lib",
            vulkan.."/Lib/shaderc_util.lib"
        }
