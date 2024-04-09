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
	: TinyAsset{ TA_TYPE_TEXTURE_ATLAS },
	_albedo{ TA_TYPE_TEXTURE_2D },
	_normal{ TA_TYPE_TEXTURE_2D },
	_specular{ TA_TYPE_TEXTURE_2D }
{ }

TinyTextureAtlas& TinyTextureAtlas::SetAlbedo( TinyGame* game, const tiny_string& name ) {
	auto hash = tiny_hash{ name };

	return SetAlbedo( game, hash );
}

TinyTextureAtlas& TinyTextureAtlas::SetAlbedo( TinyGame* game, const tiny_hash hash ) {
	auto& assets = game->GetAssets( );

	if ( assets.GetExist( TA_TYPE_TEXTURE_2D, hash ) ) {
		assets.Release( game, _albedo );

		_albedo.Hash = hash;

		assets.Acquire( game, _albedo );
	}

	return tiny_self;
}

TinyTextureAtlas& TinyTextureAtlas::SetNormal( TinyGame* game, const tiny_string& name ) {
	auto hash = tiny_hash{ name };

	return SetNormal( game, hash );
}

TinyTextureAtlas& TinyTextureAtlas::SetNormal( TinyGame* game, const tiny_hash hash ) {
	auto& assets = game->GetAssets( );

	if ( assets.GetExist( TA_TYPE_TEXTURE_2D, hash ) ) {
		assets.Release( game, _normal );

		_normal.Hash = hash;

		assets.Acquire( game, _normal );
	}

	return tiny_self;
}

TinyTextureAtlas& TinyTextureAtlas::SetSpecular( TinyGame* game, const tiny_string& name ) {
	auto hash = tiny_hash{ name };

	return SetSpecular( game, hash );
}

TinyTextureAtlas& TinyTextureAtlas::SetSpecular( TinyGame* game, const tiny_hash hash ) {
	auto& assets = game->GetAssets( );

	if ( assets.GetExist( TA_TYPE_TEXTURE_2D, hash ) ) {
		assets.Release( game, _specular );

		_specular.Hash = hash;

		assets.Acquire( game, _specular );
	}

	return tiny_self;
}

TinyTextureAtlas& TinyTextureAtlas::Set(
	TinyGame* game,
	const tiny_string& albedo,
	const tiny_string& normal,
	const tiny_string& specular
) {
	auto albedo_hash = tiny_hash{ albedo };
	auto normal_hash = tiny_hash{ normal };
	auto spec_hash = tiny_hash{ specular };

	return Set( game, albedo_hash, normal_hash, spec_hash );
}

TinyTextureAtlas& TinyTextureAtlas::Set(
	TinyGame* game,
	const tiny_hash albedo,
	const tiny_hash normal,
	const tiny_hash specular
) {
	SetAlbedo( game, albedo );
	SetNormal( game, normal );
	SetSpecular( game, specular );

	return tiny_self;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
tiny_uint TinyTextureAtlas::GetComponents( ) const { return 3; }

const TinyAssetHandle& TinyTextureAtlas::GetAlbedo( ) const { return _albedo; }

const TinyAssetHandle& TinyTextureAtlas::GetNormal( ) const { return _normal; }

const TinyAssetHandle& TinyTextureAtlas::GetSpecular( ) const { return _specular; }

const TinyAssetHandle* TinyTextureAtlas::begin( ) const { return tiny_rvalue( _albedo ); }

const TinyAssetHandle* TinyTextureAtlas::end( ) const { return tiny_rvalue( _specular ) + 1; }
