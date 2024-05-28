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
	_delete_hash{ }
{ }

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PROTECTED ===
////////////////////////////////////////////////////////////////////////////////////////////
void TinyToolWorld::OnTick( TinyGame* game, TinyToolbox& toolbox ) {
	auto& ecs = game->GetECS( );

	DrawNewEntity( ecs );

	ImGui::Separator( );

	for ( auto& entity : ecs.GetEntities( ) )
		DrawEntity( game, ecs, entity );

	if ( _delete_hash ) {
		ecs.Kill( game, _delete_hash );

		if ( toolbox.GetGuizmoSelection( ) == _delete_hash )
			toolbox.HideGuizmo( );

		_delete_hash.empty( );
	}
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE ===
////////////////////////////////////////////////////////////////////////////////////////////
void TinyToolWorld::DrawEntity( 
	TinyGame* game,
	TinyECS& ecs, 
	tiny_map_node<TinyEntity>& entity 
) {
	auto flags = ImGuiTreeNodeFlags_SpanAvailWidth |
				 ImGuiTreeNodeFlags_AllowOverlap   | 
				 ImGuiTreeNodeFlags_FramePadding;

	auto entity_name = tiny_buffer<32>{ entity.Alias };
	auto* name_str   = entity_name.as_chars( );
	auto region		 = ImGui::GetContentRegionAvail( );
	auto& toolbox	 = game->GetToolbox( );

	if ( entity.Hash == toolbox.GetGuizmoSelection( ) )
		flags |= ImGuiTreeNodeFlags_Selected;

	TINY_IMGUI_SCOPE_ID(
		ImGui::BeginGroup( );

		auto open		 = ImGui::TreeNodeEx( name_str, flags, name_str );
		auto font_size   = ImGui::GetFontSize( );
		auto& style	     = ImGui::GetStyle( );
		auto line_height = font_size + style.FramePadding.y * 2.f;

		ImGui::SameLine( region.x - line_height * .8f );

		if ( TinyImGui::Button( TF_ICON_TRASH_ALT, { line_height, line_height } ) )
			_delete_hash = entity.Hash;

		if ( open ) {
			auto add_components = ecs.GetComponentListFor( entity.Hash );
			auto components		= ecs.GetComponents( entity.Hash );

			ImGui::BeginDisabled( add_components.size( ) == 0 );
		
			if ( TinyImGui::Button( "Add Component", { -1.f, .0f } ) )
				ImGui::OpenPopup( "AddComp" );

			ImGui::Separator( );

			if ( ImGui::BeginPopup( "AddComp" ) ) {
				for ( auto& comp : add_components ) {
					if ( ImGui::Button( comp.get( ) ) ) {
						ecs.Append( game, entity.Hash, comp );

						ImGui::CloseCurrentPopup( );
					}
				}

				ImGui::EndPopup( );
			}

			ImGui::EndDisabled( );

			for ( auto& component : components ) {
				auto comp_name = component->GetName( );
				auto* name_str = comp_name.as_chars( );
				auto is_active = component->GetIsActive( );

				open = ImGui::CollapsingHeader( name_str, ImGuiTreeNodeFlags_AllowOverlap );

				ImGui::SameLine( region.x - line_height * 3.1f );

				auto button_size = TinyImGui::CalcTextSize( TF_ICON_EYE_SLASH );

				if ( TinyImGui::Button( is_active ? TF_ICON_EYE : TF_ICON_EYE_SLASH, button_size ) )
					component->Toggle( game );

				ImGui::SameLine( region.x - line_height * 1.8f );

				if ( TinyImGui::Button( TF_ICON_TRASH_ALT, { line_height, line_height } ) )
					ecs.Remove( game, entity.Hash, comp_name );

				if ( open ) {
					TinyImGui::BeginVars( );

					component->DisplayWidget( game, toolbox );

					TinyImGui::EndVars( );

					ImGui::Separator( );
				}
			}

			ImGui::TreePop( );
		}

		ImGui::EndGroup( );
	);

	if ( ImGui::IsItemClicked( ImGuiMouseButton_Left ) ) {
		if ( ecs.GetHasComponent<TinyTransform2D>( entity.Hash ) )
			toolbox.ShowGuizmo2D( entity.Hash );
		else
			toolbox.HideGuizmo( );
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
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
