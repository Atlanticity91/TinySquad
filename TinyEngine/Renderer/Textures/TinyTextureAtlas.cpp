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
 * @creation : 26/11/2023
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
TinyTextureAtlas::TinyTextureAtlas( ) 
	: _albedo{ 0 },
	_normal{ 0 },
	_specular{ 0 }
{ }

TinyTextureAtlas& TinyTextureAtlas::SetAlbedo( tiny_uint value ) {
	_albedo = value;

	return tiny_self;
}

TinyTextureAtlas& TinyTextureAtlas::SetNormal( tiny_uint value ) {
	_normal = value;
	
	return tiny_self;
}

TinyTextureAtlas& TinyTextureAtlas::SetSpecular( tiny_uint value ) {
	_specular = value;

	return tiny_self;
}

TinyTextureAtlas& TinyTextureAtlas::Set( 
	tiny_uint albedo, 
	tiny_uint normal, 
	tiny_uint specular 
) {
	_albedo   = albedo;
	_normal   = normal;
	_specular = specular;

	return tiny_self;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
tiny_uint TinyTextureAtlas::GetAlbedo( ) const { return _albedo; }

tiny_uint TinyTextureAtlas::GetNormal( ) const { return _normal; }

tiny_uint TinyTextureAtlas::GetSpecular( ) const { return _specular; }
