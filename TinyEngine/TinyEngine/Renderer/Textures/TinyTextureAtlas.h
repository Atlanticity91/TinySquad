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

te_class TinyTextureAtlas final : tiny_inherit( TinyAsset ) {

private:
	TinyAssetHandle _albedo;
	TinyAssetHandle _normal;
	TinyAssetHandle _specular;

public:
	TinyTextureAtlas( );

	~TinyTextureAtlas( ) = default;

	TinyTextureAtlas& SetAlbedo( TinyGame* game, const tiny_string& name );

	TinyTextureAtlas& SetAlbedo( TinyGame* game, const tiny_hash hash );

	TinyTextureAtlas& SetNormal( TinyGame* game, const tiny_string& name );

	TinyTextureAtlas& SetNormal( TinyGame* game, const tiny_hash hash );

	TinyTextureAtlas& SetSpecular( TinyGame* game, const tiny_string& name );

	TinyTextureAtlas& SetSpecular( TinyGame* game, const tiny_hash hash );

	TinyTextureAtlas& Set( 
		TinyGame* game,
		const tiny_string& albedo,
		const tiny_string& normal,
		const tiny_string& specular
	);

	TinyTextureAtlas& Set(
		TinyGame* game,
		const tiny_hash albedo,
		const tiny_hash normal,
		const tiny_hash specular
	);

	tiny_implement( void Terminate( TinyGame* game ) );

public:
	tiny_uint GetComponents( ) const;

	const TinyAssetHandle& GetAlbedo( ) const;

	const TinyAssetHandle& GetNormal( ) const;
	
	const TinyAssetHandle& GetSpecular( ) const;

	const TinyAssetHandle* begin( ) const;

	const TinyAssetHandle* end( ) const;

};
