project "TinyThirdparty"
   kind "StaticLib"
   language "C++"
   cdialect "C17"
   cppdialect "C++20"
   staticruntime "on"

   files { "**.h", "**.cpp", "**.hpp", "**.c" }

   vulkan = os.getenv( "VULKAN_PATH" )

   includedirs { "%{wks.location}/", vulkan.."/Include/" }
   externalincludedirs { "%{wks.location}/", vulkan.."/Include/" }

   targetdir "%{wks.location}/bin/"
   objdir "%{wks.location}/bin-int/%{prj.name}"

   filter "system:windows"
       systemversion "latest"
       defines { "WINDOWS" }

   filter "configurations:Debug"
       defines { "DEBUG", "YAML_CPP_STATIC_DEFINE" }
       runtime "Debug"
       symbols "On"

   filter "configurations:Release"
       defines { "RELEASE", "YAML_CPP_STATIC_DEFINE" }
       runtime "Release"
       optimize "On"
       symbols "On"

   filter "configurations:Dist"
       defines { "DIST", "YAML_CPP_STATIC_DEFINE" }
       runtime "Release"
       optimize "On"
       symbols "Off"
