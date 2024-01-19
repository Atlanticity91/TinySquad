project "TinyEngine"
   kind "SharedLib"
   language "C++"
   cdialect "C17"
   cppdialect "C++20"
   staticruntime "off"

   defines { "_CRT_SECURE_NO_WARNINGS", "TE_BUILD" }

   files { "**.h", "**.cpp", "**.hpp", "**.c" }

   pchheader "TinyEngine/__tiny_engine_pch.h"
   pchsource "%{wks.location}/TinyEngine/__tiny_engine_pch.cpp"

   vulkan = os.getenv( "VULKAN_PATH" )

   includedirs { "%{wks.location}/", vulkan.."/Include/" }
   externalincludedirs { "%{wks.location}/", vulkan.."/Include/" }

   targetdir "%{wks.location}/bin/"
   objdir "%{wks.location}/bin-int/%{prj.name}"

   links {
        "TinyThirdparty",
        "TinyMicro"
    }

   filter "system:windows"
       systemversion "latest"
       defines { "WINDOWS" }
       links {
          vulkan.."/Lib/SPIRV.lib",
          vulkan.."/Lib/vulkan-1.lib",
          "%{wks.location}/bin/Thirdparty/glfw3.lib",
          "%{wks.location}/bin/Thirdparty/EOSSDK-Win64-Shipping.lib",
          "%{wks.location}/bin/Thirdparty/steam_api64.lib"
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
