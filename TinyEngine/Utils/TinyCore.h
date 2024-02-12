/******************************************************************************************
 *
 *   _______ _             __  __ _
 *  |__   __(_)           |  \/  (_)
 *     | |   _ _ __  _   _| \  / |_  ___ _ __ ___
 *     | |  | | '_ \| | | | |\/| | |/ __| '__/ _ \
 *     | |  | | | | | |_| | |  | | | (__| | | (_) |
 *     |_|  |_|_| |_|\__, |_|  |_|_|\___|_|  \___/
 *                    __/ |
 *	                 |___/
 *
 * @author   : ALVES Quentin
 * @creation : 11/10/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#define TINY_ENGINE_VERSION_MAJOR 2024
#define TINY_ENGINE_VERSION_MINOR 1
#define TINY_ENGINE_VERSION_PATCH 4
#define TINY_ENGINE_VERSION tiny_cast( (\
		( TINY_ENGINE_VERSION_MAJOR << 16 ) |\
		( TINY_ENGINE_VERSION_MINOR <<  8 ) |\
		TINY_ENGINE_VERSION_PATCH\
	), tiny_uint )

#define IMGUI_IMPL_VULKAN_NO_PROTOTYPES

#include <TinyMicro/Jobs/TinyJobManager.h>

#include <TinyThirdparty/ImGui/imgui.h>
#include <TinyThirdparty/ImGui/imgui_internal.h>
#include <TinyThirdparty/ImGui/imgui_impl_vulkan.h>
#include <TinyThirdparty/ImGui/imgui_impl_glfw.h>
#include <TinyThirdparty/ImGui/imgui_compress_ttf.h>
#include <TinyThirdparty/ImGuiknobs/ImGuiknobs.h>
#include <TinyThirdparty/ImGuizmo/ImGuizmo.h>
#include <TinyThirdparty/Lua/lua.hpp>
#include <TinyThirdparty/STB/STB.h>
#include <TinyThirdparty/Yaml/yaml.h>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// HELPER'S
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef _WIN64
#	ifdef TE_BUILD
#		define tiny_dll __declspec( dllexport )
#		pragma message( "Defining tiny_dll as export" )
#	else
#		define tiny_dll __declspec( dllimport )
#		pragma message( "Defining tiny_dll as import" )
#	endif
#else
#	define tiny_dll
#endif

#define te_union union tiny_dll
#define te_interface struct tiny_dll
#define te_struct te_interface
#define te_class class tiny_dll
#define te_abstract_class te_class
#define te_enumerable( NAME ) enum te_class NAME

class TinyEngine;
class TinyGame;
class TinyToolbox;
