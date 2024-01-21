project "TinyMicro"
   kind "StaticLib"
   language "C++"
   cdialect "C17"
   cppdialect "C++20"
   staticruntime "on"

   defines { "_CRT_SECURE_NO_WARNINGS", "TM_BUILD" }

   pchheader "TinyMicro/__tiny_micro_pch.h"
   pchsource "%{wks.location}/TinyMicro/__tiny_micro_pch.cpp"

   files { "**.h", "**.cpp", "**.hpp", "**.c" }

   vulkan = os.getenv( "VULKAN_PATH" )

   includedirs { "%{wks.location}/", vulkan.."/Include/" }
   externalincludedirs { "%{wks.location}/", vulkan.."/Include/" }

   targetdir "%{wks.location}/bin/"
   objdir "%{wks.location}/bin-int/%{prj.name}"

   links { "TinyThirdparty" }
   
   filter "system:windows"
       systemversion "latest"
       defines { "WINDOWS" }

   filter "configurations:Debug"
       defines { "DEBUG", "TM_DEBUG" }
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
