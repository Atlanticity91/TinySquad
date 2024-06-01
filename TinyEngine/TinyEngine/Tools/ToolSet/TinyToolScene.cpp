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
 * @creation : 29/01/2024
 * @version  : 2024.1.2
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#include <TinyEngine/__tiny_engine_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyToolScene::TinyToolScene( )
	: TinyToolCategory{ "Scene" },
    //TinyToolDialog{ "Tiny Scene (*.tinyscene)\0*.tinyscene\0" },
	m_has_changed{ false }
{ }

void TinyToolScene::MarkUnSaved( ) { m_has_changed = true; }

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PROTECTED ===
////////////////////////////////////////////////////////////////////////////////////////////
void TinyToolScene::OnTick( TinyGame* game, TinyToolbox& toolbox ) {
    auto& ecs = game->GetECS( );

    ImGui::SeparatorText( "Systems" );

	DrawSystems( game, ecs );

	ImGui::SeparatorText( "Generals" );

	DrawGenerals( );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE ===
////////////////////////////////////////////////////////////////////////////////////////////
void TinyToolScene::DrawSystems( TinyGame* game, TinyECS& ecs ) {
	auto& systems	  = ecs.GetSystems( );
	auto system_count = systems.size( );
	auto system_id	  = tiny_cast( 0, tiny_uint );

	while ( system_id < system_count ) {
		auto* system   = systems[ system_id ];
		auto is_active = system->GetIsActive( );
		auto* name_str = system->GetName( ).get( );

		ImGui::BeginDisabled( system_id == 0 );
		TINY_IMGUI_SCOPE_ID(
			if ( ImGui::Button( TF_ICON_CHEVRON_UP ) )
				ecs.Remap( name_str, system_id - 1 );
		);
		ImGui::EndDisabled( );
		
		ImGui::SameLine( );

		ImGui::BeginDisabled( system_id == system_count - 1 );
		TINY_IMGUI_SCOPE_ID(
			if ( ImGui::Button( TF_ICON_CHEVRON_DOWN ) )
				ecs.Remap( name_str, system_id + 1 );
		);
		ImGui::EndDisabled( );

		ImGui::SameLine( );

		auto button_size = TinyImGui::CalcTextSize( TF_ICON_EYE_SLASH );

		TINY_IMGUI_SCOPE_ID(
			if ( TinyImGui::Button( is_active ? TF_ICON_EYE : TF_ICON_EYE_SLASH, button_size ) )
				system->Toggle( game );
		);

		ImGui::SameLine( );
		ImGui::Text( name_str );

		system_id += 1;
	}
}

void TinyToolScene::DrawGenerals( ) {
	TinyImGui::BeginVars( );

	auto color = TinyPalettes::EMERALD;

	TinyImGui::InputColor( "Ambient Light", color );

	TinyImGui::EndVars( );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyToolScene::GetHasChanged( ) const { return m_has_changed; }
