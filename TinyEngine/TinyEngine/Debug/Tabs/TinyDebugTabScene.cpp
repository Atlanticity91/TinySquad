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
 * @creation : 02/08/2024
 * @version  : 2024.2.8
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#include <TinyEngine/__tiny_engine_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyDebugTabScene::TinyDebugTabScene( )
	: TinyImGuiTab{ "Scene" } 
{ }

void TinyDebugTabScene::OnCreate( native_pointer user_data ) {
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PROTECTED ===
////////////////////////////////////////////////////////////////////////////////////////////
void TinyDebugTabScene::OnTick(
	TinyGraphicManager& graphics,
	TinyInputManager& inputs,
	native_pointer user_data
) { 
	tiny_unused( graphics );
	tiny_unused( inputs );

	auto* game   = tiny_cast( user_data, TinyGame* );
	auto& debug  = game->GetDebug( );
	auto& guizmo = debug.GetGuizmo( );
	auto& ecs	 = game->GetECS( );

	ImGui::SeparatorText( "Systems" );

	DrawSystems( game, ecs );

	ImGui::SeparatorText( "Entities" );

	DrawEntities( game, guizmo, ecs );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE ===
////////////////////////////////////////////////////////////////////////////////////////////
void TinyDebugTabScene::DrawSystems( TinyGame* game, TinyECS& ecs ) {
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

void TinyDebugTabScene::DrawNewEntity( TinyECS& ecs ) {
	TinyImGui::InputText( m_new_entity );

	ImGui::SameLine( );

	if ( ImGui::Button( TF_ICON_SHARE_SQUARE ) ) {
		auto entity_name = m_new_entity.as_string( );

		if ( ecs.FindEntity( entity_name ) )
			Tiny::Sprintf( m_new_entity, "New Entity %u", m_new_entity_id++ );

		ecs.Create( entity_name );
	}
}

void TinyDebugTabScene::DrawEntity( TinyGame* game, TinyImGuizmo& guizmo, TinyECS& ecs, tiny_map_node<TinyEntity>& entity ) {
	auto& graphics = game->GetGraphics( );
	auto& inputs = game->GetInputs( );
	auto entity_name = tiny_buffer<32>{ };
	auto* name_str = entity_name.as_chars( );
	auto region = ImGui::GetContentRegionAvail( );
	auto flags = ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_AllowOverlap | ImGuiTreeNodeFlags_FramePadding;

	entity_name = entity.Alias;

	if ( entity.Hash == guizmo.GetSelection( ) )
		flags |= ImGuiTreeNodeFlags_Selected;

	TINY_IMGUI_SCOPE_ID(
		ImGui::BeginGroup( );

		auto open = ImGui::TreeNodeEx( name_str, flags, name_str );
		auto font_size = ImGui::GetFontSize( );
		auto & style = ImGui::GetStyle( );
		auto line_height = font_size + style.FramePadding.y * 2.f;

		ImGui::SameLine( region.x - line_height * .8f );

		if ( TinyImGui::Button( TF_ICON_TRASH_ALT, { line_height, line_height } ) )
			m_delete_hash = entity.Hash;

		if ( open ) {
			auto add_components = ecs.GetComponentListFor( entity.Hash );
			auto components = ecs.GetComponents( entity.Hash );

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
				auto* name_str = comp_name.get( );
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

					component->TickWidget( graphics, inputs, game );

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
			guizmo.Show( entity.Hash, true );
		else
			guizmo.Hide( );
	}
}

void TinyDebugTabScene::DrawEntities( TinyGame* game, TinyImGuizmo& guizmo, TinyECS& ecs ) {
	DrawNewEntity( ecs );

	ImGui::Separator( );

	for ( auto& entity : ecs.GetEntities( ) )
		DrawEntity( game, guizmo, ecs, entity );

	if ( m_delete_hash ) {
		ecs.Kill( game, m_delete_hash );

		if ( guizmo.GetSelection( ) == m_delete_hash )
			guizmo.Hide( );

		m_delete_hash.undefined( );
	}
}
