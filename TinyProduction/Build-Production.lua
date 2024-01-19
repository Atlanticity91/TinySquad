project "TinyProduction"
   kind "ConsoleApp"
   language "C++"
   cdialect "C17"
   cppdialect "C++20"
   staticruntime "off"

   defines { "_CRT_SECURE_NO_WARNINGS" }

   files { "**.h", "**.cpp", "**.hpp", "**.c" }

   pchheader "TinyProduction/__tiny_production_pch.h"
   pchsource "%{wks.location}/TinyProduction/__tiny_production_pch.cpp"

   vulkan = os.getenv( "VULKAN_PATH" )

   includedirs { "%{wks.location}/", vulkan.."/Include/" }
   externalincludedirs { "%{wks.location}/", vulkan.."/Include/" }

   targetdir "%{wks.location}/bin/"
   debugdir "%{wks.location}/bin/"
   objdir "%{wks.location}/bin-int/%{prj.name}"

   links { 
        "TinyThirdparty",
        "TinyMicro",
        "TinyEngine"
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
       kind "WindowedApp"
       defines { "DIST" }
       runtime "Release"
       optimize "On"
       symbols "Off"
