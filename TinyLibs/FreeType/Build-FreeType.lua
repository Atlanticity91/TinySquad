project "FreeType"
	kind "StaticLib"
	language "C"
	cdialect "C17"
    staticruntime "off"

	files {
		"ft2build.h",
		"freetype/*.h",
		"freetype/config/*.h",
		"freetype/internal/*.h",

		"autofit/autofit.c",
		"base/ftbase.c",
		"base/ftbbox.c",
		"base/ftbdf.c",
		"base/ftbitmap.c",
		"base/ftcid.c",
		"base/ftdebug.c",
		"base/ftfstype.c",
		"base/ftgasp.c",
		"base/ftglyph.c",
		"base/ftgxval.c",
		"base/ftinit.c",
		"base/ftmm.c",
		"base/ftotval.c",
		"base/ftpatent.c",
		"base/ftpfr.c",
		"base/ftstroke.c",
		"base/ftsynth.c",
		"base/ftsystem.c",
		"base/fttype1.c",
		"base/ftwinfnt.c",
		"bdf/bdf.c",
		"bzip2/ftbzip2.c",
		"cache/ftcache.c",
		"cff/cff.c",
		"cid/type1cid.c",
		"gzip/ftgzip.c",
		"lzw/ftlzw.c",
		"pcf/pcf.c",
		"pfr/pfr.c",
		"psaux/psaux.c",
		"pshinter/pshinter.c",
		"psnames/psnames.c",
		"raster/raster.c",
		"sdf/sdf.c",
		"sfnt/sfnt.c",
		"smooth/smooth.c",
		"truetype/truetype.c",
		"type1/type1.c",
		"type42/type42.c",
		"winfonts/winfnt.c"
	}

	targetdir "%{wks.location}/bin/Thirdparty/"
	objdir "%{wks.location}/bin-int/%{prj.name}"

	includedirs { "%{wks.location}/TinyLibs/FreeType/" }
	externalincludedirs { "%{wks.location}/TinyLibs/FreeType/" }

	defines {
		"FT2_BUILD_LIBRARY",
		"_CRT_SECURE_NO_WARNINGS",
		"_CRT_NONSTDC_NO_WARNINGS",
	}

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
