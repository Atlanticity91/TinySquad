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

#pragma once

#include "TinyTexture3DManager.h"

te_class TinyTextureAtlas final {

private:
	tiny_uint _albedo;
	tiny_uint _normal;
	tiny_uint _specular;

public:
	TinyTextureAtlas( );

	~TinyTextureAtlas( ) = default;

	TinyTextureAtlas& SetAlbedo( tiny_uint value );

	TinyTextureAtlas& SetNormal( tiny_uint value );

	TinyTextureAtlas& SetSpecular( tiny_uint value );

	TinyTextureAtlas& Set( tiny_uint albedo, tiny_uint normal, tiny_uint specular );

public:
	tiny_uint GetAlbedo( ) const;

	tiny_uint GetNormal( ) const;
	
	tiny_uint GetSpecular( ) const;

};
