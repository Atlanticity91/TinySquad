project "TinyThirdparty"
    kind "StaticLib"
    language "C++"
    cdialect "C17"
    cppdialect "C++20"
    staticruntime "off"

    files { "**.h", "**.cpp", "**.hpp", "**.c" }

    defines { "TT_BUILD" }

    vulkan = os.getenv( "VULKAN_PATH" )

    includedirs { 
        "%{wks.location}/",
        "%{wks.location}/TinyLibs/",
        "%{wks.location}/TinyEngine/",
        vulkan.."/Include/" 
    }
    externalincludedirs { 
        "%{wks.location}/",
        "%{wks.location}/TinyLibs/",
        "%{wks.location}/TinyEngine/",
        vulkan.."/Include/" 
    }

    links {
        "Lz4",
        "FreeType",
        "MSDF",
        "MSDF-Atlas",
        "Lua",
        "Yaml",
        "GLFW",
        "ImGui",
        "Coral"
    }

    targetdir "%{wks.location}/bin/"
    objdir "%{wks.location}/bin-int/%{prj.name}"

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
