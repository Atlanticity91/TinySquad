project "Lua"
	kind "StaticLib"
	language "C"
	cdialect "C17"
    staticruntime "off"

	files { "*.h", "*.c" }

	targetdir "%{wks.location}/bin/Thirdparty/"
	objdir "%{wks.location}/bin-int/%{prj.name}"

	includedirs { "%{wks.location}/TinyLibs/" }
	externalincludedirs { "%{wks.location}/TinyLibs/" }

	defines { "_CRT_SECURE_NO_WARNINGS" }

	filter "system:windows"
		systemversion "latest"
		defines { "WINDOWS" }
		flags { "MultiProcessorCompile" }

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
