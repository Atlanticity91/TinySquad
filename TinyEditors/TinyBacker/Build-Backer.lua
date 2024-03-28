project "TinyBacker"
	kind "ConsoleApp"
	language "C++"
	cdialect "C17"
	cppdialect "C++20"
	staticruntime "off"

	defines { "_CRT_SECURE_NO_WARNINGS" }

	files { "**.h", "**.hpp", "**.cpp" }

	pchheader "TinyBacker/__tiny_backer_pch.h"
	pchsource "%{wks.location}/TinyEditors/TinyBacker/__tiny_backer_pch.cpp"

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

    links { "TinyNut", "TinyEngine" }
    
    filter "system:windows"
        systemversion "latest"
        defines { "WINDOWS" }

    filter "configurations:Debug"
        defines { "DEBUG" }
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines { "RELEASE" }
        runtime "Release"
        optimize "On"
        symbols "On"

    filter "configurations:Dist"
        kind "WindowedApp"
        defines { "DIST" }
        runtime "Release"
        optimize "On"
        symbols "Off"
