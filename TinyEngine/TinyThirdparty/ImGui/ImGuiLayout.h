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
 * @creation : 28/03/2024
 * @version  : 2024.2.7
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include <TinyLibs/ImGui/imgui.h>
#include <TinyLibs/ImGui/imgui_internal.h>
#include <TinyLibs/ImGui/imgui_impl_vulkan.h>
#include <TinyLibs/ImGui/imgui_impl_glfw.h>

//-----------------------------------------------------------------------------
// [SECTION] Stack Layout Internal API
//-----------------------------------------------------------------------------

namespace ImGuiInternal {

    IMGUI_API ImGuiLayoutType GetCurrentLayoutType( ImGuiID window_id );
    IMGUI_API void            UpdateItemRect( ImGuiID window_id, const ImVec2& min, const ImVec2& max );

};

//-----------------------------------------------------------------------------
// [SECTION] Stack Layout API
//-----------------------------------------------------------------------------

namespace ImGui 
{

    IMGUI_API void BeginHorizontal( const char* str_id, const ImVec2& size = ImVec2( 0, 0 ), float align = -1.0f );
    IMGUI_API void BeginHorizontal( const void* ptr_id, const ImVec2& size = ImVec2( 0, 0 ), float align = -1.0f );
    IMGUI_API void BeginHorizontal( int id, const ImVec2& size = ImVec2( 0, 0 ), float align = -1 );
    IMGUI_API void EndHorizontal( );
    IMGUI_API void BeginVertical( const char* str_id, const ImVec2& size = ImVec2( 0, 0 ), float align = -1.0f );
    IMGUI_API void BeginVertical( const void* ptr_id, const ImVec2& size = ImVec2( 0, 0 ), float align = -1.0f );
    IMGUI_API void BeginVertical( int id, const ImVec2& size = ImVec2( 0, 0 ), float align = -1 );
    IMGUI_API void EndVertical( );
    IMGUI_API void Spring( const ImVec2& data );
    IMGUI_API void Spring( float weight = 1.0f, float spacing = -1.0f );
    IMGUI_API void SuspendLayout( );
    IMGUI_API void ResumeLayout( );

};
