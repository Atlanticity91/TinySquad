workspace "TinySquad"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "TinyProduction"

   -- Workspace-wide build options for MSVC
   filter "system:windows"
      buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus" }

group "Tiny Engine"
	include "TinyThirdparty/Build-Thirdparty.lua"
   include "TinyMicro/Build-Micro.lua"
   include "TinyEngine/Build-Engine.lua"
group ""

include "TinyProduction/Build-Production.lua"
