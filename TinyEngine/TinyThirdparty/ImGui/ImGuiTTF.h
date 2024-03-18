// dear imgui, v1.90.2 WIP
// (headers)

#pragma once

#include <TinyLibs/ImGui/imgui.h>

namespace ImGui 
{

	IMGUI_API bool CompressTTF( const char* filename, const char* symbol, bool use_base85_encoding, bool use_compression, bool use_static );

};
