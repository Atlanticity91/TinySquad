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
 * @creation : 29/03/2024
 * @version  : 2024.2.7
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#include <TinyNut/TinyNut.h>

////////////////////////////////////////////////////////////////////////////////////////////
// === PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyNutContext::TinyNutContext( )
    : _local_pools{ VK_NULL_HANDLE },
    _imgui{ nullptr }
{ }

bool TinyNutContext::Create( TinyNut* nut_game ) { return true; }

void TinyNutContext::Prepare( TinyNut* nut_game ) {
	auto& graphics = nut_game->GetGraphics( );

	graphics.BeginPass( TINY_OUTPASS_HASH );
    graphics.NextSubpass( );

    ImGui::SetCurrentContext( nut_game->GetToolbox().GetContext( ) );

    ImGui_ImplVulkan_NewFrame( );
    ImGui_ImplGlfw_NewFrame( );

    ImGui::NewFrame( );
}

void TinyNutContext::Flush( TinyNut* nut_game ) {
	auto& graphics     = nut_game->GetGraphics( );
    auto& work_context = graphics.GetWorkdContext( );

    ImGui::Render( );

    auto* draw_data = ImGui::GetDrawData( );

    ImGui_ImplVulkan_RenderDrawData( draw_data, work_context.Queue->CommandBuffer );
}

void TinyNutContext::Terminate( TinyNut* nut_game ) {
    ImGui::SetCurrentContext( nullptr );
}

////////////////////////////////////////////////////////////////////////////////////////////
// === PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
ImGuiContext* TinyNutContext::GetContext( ) { return ImGui::GetCurrentContext( ); }
