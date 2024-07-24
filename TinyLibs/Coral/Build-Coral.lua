premake.api.addAllowed("debuggertype", "NativeWithManagedCore")

project "Coral"
    language "C++"
    cppdialect "C++20"
    kind "StaticLib"
    staticruntime "Off"

    -- Can't specify 64-bit architecture in the workspace level since VS 2022 (see https://github.com/premake/premake-core/issues/1758)
    architecture "x86_64"

	targetdir "%{wks.location}/bin/Thirdparty/"
    objdir "%{wks.location}/bin-int/%{prj.name}"

    filter { "action:xcode4" }
        pchheader "Source/CoralPCH.hpp"
    filter { }

    files {
        "**.cpp",
        "**.h",
        "**.hpp"
    }

    includedirs { "%{wks.location}/TinyLibs/" }
    externalincludedirs { "%{wks.location}/TinyLibs/" }

    filter { "configurations:Debug" }
        runtime "Debug"
        symbols "On"

    filter { "configurations:Release" }
        runtime "Release"
        symbols "Off"
        optimize "On"

	filter { "system:windows" }
		defines { "CORAL_WINDOWS" }

	filter { "system:linux" }
		defines { "CORAL_LINUX" }

	filter { "system:macosx" }
		defines { "CORAL_MACOSX" }
