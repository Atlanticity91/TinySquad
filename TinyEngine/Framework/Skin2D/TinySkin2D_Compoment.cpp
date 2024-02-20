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
	_material{ TA_TYPE_MATERIAL },
	_texture{ TA_TYPE_TEXTURE_2D },
	_color{ },
	_sprite{ 0, 0 }
{ }

bool TinySkin2D::Create( TinyGame* game ) {
	auto& ecs  = game->GetECS( );
	auto state = ecs.GetHasComponent( _owner, "TinyTransform2D" );

	if ( !state )
		state = ecs.Append( game, _owner, "TinyTransform2D" ) != nullptr;

	return state;
}

TinySkin2D& TinySkin2D::SetSpriteColumn( tiny_uint column ) {
	return SetSprite( column, _sprite.y );
}

TinySkin2D& TinySkin2D::SetSpriteRow( tiny_uint row ) {
	return SetSprite( _sprite.x, row );
}

TinySkin2D& TinySkin2D::SetSprite( const tiny_upoint& sprite ) {
	return SetSprite( sprite.x, sprite.y );
}

TinySkin2D& TinySkin2D::SetSprite( tiny_uint column, tiny_uint row ) {
	_sprite.x = column;
	_sprite.y = row;

	return tiny_self;
}

void TinySkin2D::Delete( TinyGame* game ) { 
	auto& ecs = game->GetECS( );

	if ( ecs.GetHasComponent( _owner, "TinyAnim2D" ) )
		ecs.Remove( game, _owner, "TinyAnim2D" );
}

void TinySkin2D::DisplayWidget( TinyGame* game, TinyToolbox& toolbox ) {
	TinyComponent::DisplayWidget( game, toolbox );

	toolbox.DisplayAsset( game, "Material", _material );
	toolbox.DisplayAsset( game, "Texture", _texture );

	TinyImGui::InputColor( "Color", _color );
	TinyImGui::EndVars( );

	ImGui::PushStyleVar( ImGuiStyleVar_FramePadding, { 3.5f, 3.5f } );
	
	if ( ImGui::TreeNodeEx( "Sprite", ImGuiTreeNodeFlags_FramePadding | ImGuiTreeNodeFlags_SpanAllColumns | ImGuiTreeNodeFlags_SpanAllColumns ) ) {
		ImGui::Separator( );

		TinyImGui::BeginVars( );
		TinyImGui::InputScalar( "Column", _sprite.x );
		TinyImGui::InputScalar( "Row", _sprite.y );

		ImGui::TreePop( );
	} else 
		TinyImGui::BeginVars( );

	ImGui::PopStyleVar( );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinySkin2D::GetIsActive( ) const { 
	return  TinyComponent::GetIsActive( ) && 
			_material.GetIsValid( )		  && 
			_texture.GetIsValid( );
}

TinyAsset& TinySkin2D::GetMaterial( ) { return _material; }

TinyAsset& TinySkin2D::GetTexture( ) { return _texture; }

tiny_color& TinySkin2D::GetColor( ) { return _color; }

tiny_upoint& TinySkin2D::GetSprite( ) { return _sprite; }
