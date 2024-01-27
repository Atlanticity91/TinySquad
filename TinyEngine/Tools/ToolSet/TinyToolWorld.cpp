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
	: TinyToolCategory{ "World" },
	_new_entity{ "New Entity" },
	_new_entity_id{ 0 },
	_selection_hash{ },
	_query_hash{ }
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

	for ( auto& entity : ecs.GetEntities( ) )
		DrawEntity( game, ecs, entity );

	ImGui::Separator( );

	DrawNewEntity( ecs );

	DrawAddComp( game, engine, ecs );

	if ( _query_hash ) {
		ecs.Kill( game, game->GetEngine( ), _query_hash );

		_query_hash.empty( );
	}
	/*
	auto entity_id = tiny_cast( 0, tiny_uint );

	for ( auto& entity : ecs.GetEntities( ) ) {
		if ( entity.Data.GetIsAlive( ) ) {
			bool is_visible = entity.Data.GetHasFlag( TE_FLAG_VISIBLE );

			sprintf_s( _buffer, tiny_size_chars( _buffer ), "%s", entity.String.c_string( ) );

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
					ecs.ToggleFlag( entity.String.c_string( ), TE_FLAG_VISIBLE );
			);

			ImGui::SameLine( );

			TINY_IMGUI_SCOPE_ID(
				if ( ImGui::InputText( IMGUI_NO_LABEL, _buffer, tiny_size_chars( _buffer ) ) )
					ecs.Rename( entity.String.c_string( ), _buffer );
			);

			ImGui::SameLine( );

			TINY_IMGUI_SCOPE_ID(
				if ( ImGui::Button( "X" ) ) {
					ecs.Kill( game, engine, entity.String.c_string( ) );

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

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE ===
////////////////////////////////////////////////////////////////////////////////////////////
void TinyToolWorld::DrawAddComp( TinyGame* game, TinyEngine& engine, TinyECS& ecs ) {
	if ( ImGui::BeginPopup( "AddComp" ) ) {
		for ( auto& comp : ecs.GetComponentListFor( _selection_hash ) ) {
			if ( ImGui::Button( comp.get( ) ) ) {
				ecs.Append( game, engine, _selection_hash, comp );

				_selection_hash.empty( );

				ImGui::CloseCurrentPopup( );
			}
		}

		ImGui::EndPopup( );
	}
}

void TinyToolWorld::DrawEntity( 
	TinyGame* game,
	TinyECS& ecs, 
	tiny_map_node<TinyEntity>& entity 
) {
	const auto flags = ImGuiTreeNodeFlags_SpanAvailWidth |
					   ImGuiTreeNodeFlags_AllowOverlap   |
					   ImGuiTreeNodeFlags_FramePadding;

	auto entity_name = tiny_buffer<32>{ entity.String };
	auto* name_str   = entity_name.as_chars( );
	auto region		 = ImGui::GetContentRegionAvail( );

	ImGui::PushStyleVar( ImGuiStyleVar_FramePadding, { 4.f, 4.f } );

	auto open = ImGui::TreeNodeEx( name_str, flags, name_str );

	ImGui::PopStyleVar( );

	auto font_size   = ImGui::GetFontSize( );
	auto& style	     = ImGui::GetStyle( );
	auto line_height = font_size + style.FramePadding.y * 2.f;

	ImGui::SameLine( region.x - line_height * 1.6f );

	if ( TinyImGui::Button( TF_ICON_PLUS, { line_height, line_height } ) ) {
		_selection_hash = entity.Hash;

		ImGui::OpenPopup( "AddComp" );
	}

	ImGui::SameLine( region.x - line_height * .5f );

	if ( TinyImGui::Button( TF_ICON_TRASH_ALT, { line_height, line_height } ) )
		_query_hash = entity.Hash;

	if ( open ) {
		auto components = ecs.GetComponents( entity.Hash );
		auto& engine	= game->GetEngine( );
		auto& toolbox	= game->GetToolbox( );

		for ( auto& component : components ) {
			auto comp_name = component->GetName( );
			auto* name_str = comp_name.as_chars( );

			if ( ImGui::CollapsingHeader( name_str ) ) {
				TinyImGui::BeginVars( );

				component->DisplayWidget( game, engine, toolbox );

				TinyImGui::EndVars( );

				ImGui::Separator( );
			}
		}

		ImGui::TreePop( );
	}
}

void TinyToolWorld::DrawNewEntity( TinyECS& ecs ) {
	TinyImGui::InputText( _new_entity );

	ImGui::SameLine( );

	if ( ImGui::Button( TF_ICON_SHARE_SQUARE ) ) {
		auto entity_name = _new_entity.as_string( );

		if ( ecs.FindEntity( entity_name ) )
			_new_entity.store( "New Entity %u", _new_entity_id++ );

		ecs.Create( entity_name );
	}
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE STATIC ===
////////////////////////////////////////////////////////////////////////////////////////////
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
			if ( ImGui::Button( TF_ICON_CHEVRON_UP ) )
				ecs.Remap( name_str, systen_id - 1 );
		);

		ImGui::EndDisabled( );
		ImGui::SameLine( );
		ImGui::BeginDisabled( systen_id > 0 );

		TINY_IMGUI_SCOPE_ID(
			if ( ImGui::Button( TF_ICON_CHEVRON_DOWN ) )
				ecs.Remap( name_str, systen_id + 1 );
		);

		ImGui::EndDisabled( );
		ImGui::SameLine( );

		TINY_IMGUI_SCOPE_ID(
			if ( TinyImGui::Checkbox( IMGUI_NO_LABEL, is_active ) )
				system->Toggle( game, engine );
		);

		ImGui::SameLine( );
		ImGui::Text( name_str );

		systen_id += 1;
	}
}
