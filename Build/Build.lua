workspace "TinySquad"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "TinyProduction"

   -- Workspace-wide build options for MSVC
   filter "system:windows"
      buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus" }

group "Tiny Libraries"
   include "TinyLibs/Build-Libs.lua"
group "Tiny Engine"
   include "TinyEngine/Build-Engine.lua"
group "Tiny Editors"
   include "TinyEditors/Build-Editors.lua"
group "Tiny Sharp"
   include "TinySharp/Build-Sharp.lua"
group ""

include "TinyProduction/Build-Production.lua"
