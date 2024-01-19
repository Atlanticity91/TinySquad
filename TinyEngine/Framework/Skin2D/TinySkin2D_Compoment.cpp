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

bool TinySkin2D::Create( TinyGame* game, TinyEngine& engine ) {
	auto& ecs  = engine.GetECS( );
	auto state = ecs.GetHasComponent( _owner, "TinyTransform2D" );

	if ( !state )
		state = ecs.Append( game, engine, _owner, "TinyTransform2D" ) != nullptr;

	return state;
}

void TinySkin2D::Delete( TinyGame* game, TinyEngine& engine ) {
}

void TinySkin2D::DisplayWidget(
	TinyGame* game,
	TinyEngine& engine,
	TinyToolbox& toolbox
) {
	TinyComponent::DisplayWidget( game, engine, toolbox );

	toolbox.DisplayAsset( game, "Material", _material );
	toolbox.DisplayAsset( game, "Texture", _texture );

	TinyImGui::InputColor( "Color", _color );
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
