project "TinyThirdparty"
    kind "StaticLib"
    language "C++"
    cdialect "C17"
    cppdialect "C++20"
    staticruntime "off"

    files { "**.h", "**.cpp", "**.hpp", "**.c" }

    vulkan = os.getenv( "VULKAN_PATH" )

    includedirs { 
        "%{wks.location}/",
        "%{wks.location}/TinyEngine/",
        vulkan.."/Include/" 
    }
    externalincludedirs { 
        "%{wks.location}/",
        "%{wks.location}/TinyEngine/",
        vulkan.."/Include/" 
    }

    links {
        "FreeType",
        "MSDF",
        "MSDF-Atlas",
        "Lua",
        "Yaml",
        "ImGui"
    }

    targetdir "%{wks.location}/bin/"
    objdir "%{wks.location}/bin-int/%{prj.name}"

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
