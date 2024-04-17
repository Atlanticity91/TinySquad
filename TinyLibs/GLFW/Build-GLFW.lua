project "GLFW"
	kind "StaticLib"
	language "C"
	cdialect "C17"
    staticruntime "off"

	files {
		"glfw3.h",
		"glfw3native.h",
		"glfw_config.h",
		"context.c",
		"init.c",
		"input.c",
		"monitor.c",
		"null_init.c",
		"null_joystick.c",
		"null_monitor.c",
		"null_window.c",
		"platform.c",
		"vulkan.c",
		"window.c"
	}

	targetdir "%{wks.location}/bin/Thirdparty/"
	objdir "%{wks.location}/bin-int/%{prj.name}"

	includedirs { "%{wks.location}/TinyLibs/" }
	externalincludedirs { "%{wks.location}/TinyLibs/" }

	filter "system:windows"
		systemversion "latest"
		defines { 
			"WINDOWS", 
			"_CRT_SECURE_NO_WARNINGS",
			"_GLFW_WIN32" 
		}

		files {
			"win32_init.c",
			"win32_joystick.c",
			"win32_module.c",
			"win32_monitor.c",
			"win32_time.c",
			"win32_thread.c",
			"win32_window.c",
			"wgl_context.c",
			"egl_context.c",
			"osmesa_context.c"
		}

	filter "system:linux"
		systemversion "latest"
		pic "On"
		
		defines { "_GLFW_X11" }

		files {
			"x11_init.c",
			"x11_monitor.c",
			"x11_window.c",
			"xkb_unicode.c",
			"posix_module.c",
			"posix_time.c",
			"posix_thread.c",
			"posix_module.c",
			"glx_context.c",
			"egl_context.c",
			"osmesa_context.c",
			"linux_joystick.c"
		}

	filter "system:macosx"
		pic "On"

		defines { "_GLFW_COCOA" }

		files {
			"cocoa_init.m",
			"cocoa_monitor.m",
			"cocoa_window.m",
			"cocoa_joystick.m",
			"cocoa_time.c",
			"nsgl_context.m",
			"posix_thread.c",
			"posix_module.c",
			"osmesa_context.c",
			"egl_context.c"
		}

	filter "configurations:Debug"
		defines { "DEBUG" }
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines { "RELEASE" }
		runtime "Release"
		optimize "speed"

	filter "configurations:Dist"
		defines { "DIST" }
		runtime "Release"
		optimize "speed"
		symbols "Off"
