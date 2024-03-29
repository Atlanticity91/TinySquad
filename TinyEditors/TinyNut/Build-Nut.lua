project "TinyNut"
	kind "SharedLib"
	language "C++"
	cppdialect "C++20"
    staticruntime "off"

    defines { "_CRT_SECURE_NO_WARNINGS", "TN_BUILD" }

	files { "**.h", "**.hpp", "**.cpp" }

	targetdir "%{wks.location}/bin/"
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

	links { "TinyEngine", "TinyMicro", "TinyThirdparty", "Imgui", "GLFW" }

	filter "system:windows"
		systemversion "latest"
		defines { "WINDOWS" }
		links {
            vulkan.."/Lib/SPIRV.lib",
            vulkan.."/Lib/vulkan-1.lib"
        }
        libdirs { 
            "%{wks.location}/bin/",
            "%{wks.location}/bin/Thirdparty/"
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
		defines { "DIST" }
		runtime "Release"
		optimize "On"
		symbols "Off"
		links {
            vulkan.."/Lib/shaderc.lib",
            vulkan.."/Lib/shaderc_combined.lib",
            vulkan.."/Lib/shaderc_util.lib"
        }
