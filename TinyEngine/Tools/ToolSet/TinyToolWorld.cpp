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
 * @creation : 19/01/2024
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#include <TinyEngine/__tiny_engine_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyToolWorld::TinyToolWorld( ) 
	: TinyToolCategory{ "World" }
{ }

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PROTECTED ===
////////////////////////////////////////////////////////////////////////////////////////////
void TinyToolWorld::OnTick(
	TinyGame* game,
	TinyEngine& engine,
	TinyToolbox& toolbox
) {
	auto& ecs = engine.GetECS( );

	TinyImGui::Collapsing( "Systems", DrawSystems, game, engine, ecs );

	ImGui::SeparatorText( "Entities" );

	/*
	auto entity_id = tiny_cast( 0, tiny_uint );

	for ( auto& entity : ecs.GetEntities( ) ) {
		if ( entity.Data.GetIsAlive( ) ) {
			bool is_visible = entity.Data.GetHasFlag( TE_FLAG_VISIBLE );

			sprintf_s( _buffer, tiny_size_chars( _buffer ), "%s", entity.String.c_str( ) );

			TINY_IMGUI_SCOPE_ID(
				if ( ImGui::Selectable( IMGUI_NO_LABEL, false ) ) {
					if ( _selection != entity.Hash )
						_selection = entity.Hash;
					else
						_selection = 0;
				}
			);

			ImGui::SameLine( );
			ImGui::SetItemAllowOverlap( );
			ImGui::Text( "%c", _selection != entity.Hash ? ' ' : '#' );
			ImGui::SameLine( );

			TINY_IMGUI_SCOPE_ID(
				if ( ImGui::Checkbox( IMGUI_NO_LABEL, &is_visible ) )
					ecs.ToggleFlag( entity.String.c_str( ), TE_FLAG_VISIBLE );
			);

			ImGui::SameLine( );

			TINY_IMGUI_SCOPE_ID(
				if ( ImGui::InputText( IMGUI_NO_LABEL, _buffer, tiny_size_chars( _buffer ) ) )
					ecs.Rename( entity.String.c_str( ), _buffer );
			);

			ImGui::SameLine( );

			TINY_IMGUI_SCOPE_ID(
				if ( ImGui::Button( "X" ) ) {
					ecs.Kill( game, engine, entity.String.c_str( ) );

					if ( _selection == entity.Hash )
						_selection = 0;
				}
			);

			entity_id += 1;
		}
	}

	if ( _selection.is_valid( ) && ecs.GetEntityID( _selection, entity_id ) ) {
		if ( ImGui::Begin( "Components" ) ) {
			if ( ImGui::BeginPopupContextWindow( ) ) {
				for ( auto& comp : ecs.GetComponentListFor( _selection ) ) {
					if ( ImGui::Button( comp.get( ) ) ) {
						ecs.Append( game, engine, _selection, comp );

						ImGui::CloseCurrentPopup( );
					}
				}

				ImGui::EndPopup( );
			}

			auto components = ecs.GetComponents( entity_id );

			for ( auto& component : components ) {
				if ( ImGui::CollapsingHeader( component->GetName( ).get( ) ) ) {
					TinyImGui::BeginVars( );

					component->DisplayWidget( game, engine, toolbox );

					TinyImGui::EndVars( );
				}
			}
		}

		ImGui::End( );
	}
	*/
}

void TinyToolWorld::DrawSystems( TinyGame* game, TinyEngine& engine, TinyECS& ecs ) {
	auto& systems	  = ecs.GetSystems( );
	auto system_count = systems.size( );
	auto systen_id	  = tiny_cast( 0, tiny_uint );

	while ( systen_id < system_count ) {
		auto* system   = systems[ systen_id ];
		auto is_active = system->GetIsActive( );
		auto* name_str = system->GetName( ).as_chars( );

		ImGui::BeginDisabled( system_count - systen_id > 1 );

		TINY_IMGUI_SCOPE_ID(
			if ( ImGui::Button( "-" ) )
				ecs.Remap( name_str, systen_id - 1 );
		);

		ImGui::EndDisabled( );
		ImGui::SameLine( );
		ImGui::BeginDisabled( systen_id > 0 );

		TINY_IMGUI_SCOPE_ID(
			if ( ImGui::Button( "+" ) )
				ecs.Remap( name_str, systen_id + 1 );
		);

		ImGui::EndDisabled( );
		ImGui::SameLine( );

		TINY_IMGUI_SCOPE_ID(
			if ( ImGui::Checkbox( IMGUI_NO_LABEL, tiny_rvalue( is_active ) ) )
				system->Toggle( game, engine );
		);

		ImGui::SameLine( );
		ImGui::Text( name_str );

		systen_id += 1;
	}
}
