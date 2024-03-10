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
-- include "TinyCoral/Build-Coral.lua"
group "Tiny Editor"
-- include "TinyPacker/Build-Packer.lua"
-- include "TinyTiler/Build-Tiler.lua"
-- include "TinyEditor/Build-Editor.lua"
group ""

include "TinyProduction/Build-Production.lua"
-- include "TinyProductionCoral/Build-ProductionCoral.lua"
