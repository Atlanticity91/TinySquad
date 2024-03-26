project "TinyNut"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
    staticruntime "off"

    defines { "_CRT_SECURE_NO_WARNINGS", "TN_BUILD" }

	files { "*.h", "*.hpp", "*.cpp" }

	targetdir "%{wks.location}/bin/Thirdparty/"
	objdir "%{wks.location}/bin-int/%{prj.name}"

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

	links { "TinyEngine" }

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
		defines { "DIST" }
		runtime "Release"
		optimize "On"
		symbols "Off"
