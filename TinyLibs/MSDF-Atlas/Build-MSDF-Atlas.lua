project "MSDF-Atlas"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
    staticruntime "off"

	files { "*.h", "*.hpp", "*.cpp" }

	targetdir "%{wks.location}/bin/Thirdparty/"
	objdir "%{wks.location}/bin-int/%{prj.name}"

	includedirs { "%{wks.location}/TinyLibs/" }
	externalincludedirs { "%{wks.location}/TinyLibs/" }

	defines { "_CRT_SECURE_NO_WARNINGS" }

	links { "MSDF" }
	
	defines {
		"_CRT_SECURE_NO_WARNINGS",
		"_CRT_NONSTDC_NO_WARNINGS",
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
