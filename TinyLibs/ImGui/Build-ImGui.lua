project "ImGui"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
    staticruntime "off"

    defines { "IM_BUILD" }

    vulkan = os.getenv( "VULKAN_PATH" )

	files { "*.h", "*.cpp" }

	targetdir "%{wks.location}/bin/Thirdparty/"
	objdir "%{wks.location}/bin-int/%{prj.name}"

	includedirs {  
		"%{wks.location}/TinyLibs/",
		"%{wks.location}/TinyEngine/",
		vulkan.."/Include/"
	}
	externalincludedirs { 
		"%{wks.location}/TinyLibs/",
		"%{wks.location}/TinyEngine/",
		vulkan.."/Include/"
	}

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
