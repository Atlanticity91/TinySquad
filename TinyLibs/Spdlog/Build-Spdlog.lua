project "Spdlog"
	kind "StaticLib"
	language "C"
	cdialect "C17"
    staticruntime "off"

	files { "**.h", "**.hpp", "**.cpp" }

	targetdir "%{wks.location}/bin/Thirdparty/"
	objdir "%{wks.location}/bin-int/%{prj.name}"

	includedirs { "%{wks.location}/" }
	externalincludedirs { "%{wks.location}/" }

	defines { "_CRT_SECURE_NO_WARNINGS", "SPDLOG_COMPILED_LIB" }

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
