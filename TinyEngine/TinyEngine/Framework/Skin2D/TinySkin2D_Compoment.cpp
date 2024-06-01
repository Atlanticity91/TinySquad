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
 * @creation : 14/11/2023
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
TinySkin2D::TinySkin2D( )
	: TinySkin2D{ TINY_NO_ENTITY }
{ }

TinySkin2D::TinySkin2D( const tiny_hash entity_hash )
	: TinyComponent{ entity_hash },
	m_material{ TA_TYPE_MATERIAL },
	m_texture{ TA_TYPE_TEXTURE_2D },
	m_color{ },
	m_sprite{ 0, 0 }
{ }

bool TinySkin2D::Create( TinyGame* game ) {
	auto& ecs  = game->GetECS( );
	auto state = ecs.GetHasComponent( m_owner, "TinyTransform2D" );

	if ( !state )
		state = ecs.Append( game, m_owner, "TinyTransform2D" ) != nullptr;

	return state;
}

TinySkin2D& TinySkin2D::SetSpriteColumn( tiny_uint column ) {
	return SetSprite( column, m_sprite.y );
}

TinySkin2D& TinySkin2D::SetSpriteRow( tiny_uint row ) {
	return SetSprite( m_sprite.x, row );
}

TinySkin2D& TinySkin2D::SetSprite( const tiny_upoint& sprite ) {
	return SetSprite( sprite.x, sprite.y );
}

TinySkin2D& TinySkin2D::SetSprite( tiny_uint column, tiny_uint row ) {
	m_sprite.x = column;
	m_sprite.y = row;

	return tiny_self;
}

void TinySkin2D::Delete( TinyGame* game ) { 
	auto& ecs = game->GetECS( );

	if ( ecs.GetHasComponent( m_owner, "TinyAnim2D" ) )
		ecs.Remove( game, m_owner, "TinyAnim2D" );
}

void TinySkin2D::DisplayWidget( TinyGame* game, TinyToolbox& toolbox ) {
	TinyComponent::DisplayWidget( game, toolbox );

	toolbox.DisplayAsset( game, "Material", m_material );
	toolbox.DisplayAsset( game, "Texture", m_texture );

	TinyImGui::InputColor( "Color", m_color );
	TinyImGui::EndVars( );

	ImGui::PushStyleVar( ImGuiStyleVar_FramePadding, { 3.5f, 3.5f } );
	
	if ( ImGui::TreeNodeEx( "Sprite", ImGuiTreeNodeFlags_FramePadding | ImGuiTreeNodeFlags_SpanAllColumns | ImGuiTreeNodeFlags_SpanAllColumns ) ) {
		ImGui::Separator( );

		TinyImGui::BeginVars( );
		TinyImGui::InputScalar( "Column", m_sprite.x );
		TinyImGui::InputScalar( "Row", m_sprite.y );

		ImGui::TreePop( );
	} else 
		TinyImGui::BeginVars( );

	ImGui::PopStyleVar( );
}

void TinySkin2D::OnEnable( TinyGame* game ) {
	auto& ecs = game->GetECS( );

	if ( !ecs.GetHasComponent( m_owner, "TinyTransform2D" ) )
		m_is_active = false;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinySkin2D::GetIsActive( ) const { 
	return  TinyComponent::GetIsActive( ) && 
			m_material.GetIsValid( )		  && 
			m_texture.GetIsValid( );
}

TinyAssetHandle& TinySkin2D::GetMaterial( ) { return m_material; }

TinyAssetHandle& TinySkin2D::GetTexture( ) { return m_texture; }

tiny_color& TinySkin2D::GetColor( ) { return m_color; }

tiny_upoint& TinySkin2D::GetSprite( ) { return m_sprite; }
