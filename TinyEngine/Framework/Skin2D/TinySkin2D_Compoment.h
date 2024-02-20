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
 * @creation : 24/10/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include <TinyEngine/Framework/Particles/TinyEmitter_System.h>

TINY_FRAMEWORK_COMP( TinySkin2D ) {

private:
	TinyAsset	 _material;
	TinyAsset	 _texture;
	tiny_color	 _color;
	tiny_upoint  _sprite;

public:
	TinySkin2D( );

	TinySkin2D( const tiny_hash entity_hash );

	~TinySkin2D( ) = default;

	tiny_implement( bool Create( TinyGame* game ) );

	tiny_inline TinySkin2D& SetSpriteColumn( tiny_uint column );

	tiny_inline TinySkin2D& SetSpriteRow( tiny_uint row );

	tiny_inline TinySkin2D& SetSprite( const tiny_upoint & sprite );

	TinySkin2D& SetSprite( tiny_uint column, tiny_uint row );

	tiny_implement( void Delete( TinyGame* game ) );

	tiny_implement( void DisplayWidget( TinyGame* game, TinyToolbox& toolbox ) );

public:
	TINY_COMP_NAME( TinySkin2D );

	tiny_implement( bool GetIsActive( ) const );

	TinyAsset& GetMaterial( );
	
	TinyAsset& GetTexture( );

	tiny_color& GetColor( );

	tiny_upoint& GetSprite( );

};
