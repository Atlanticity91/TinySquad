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
 * @creation : 06/04/2024
 * @version  : 2024.2.7
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "ITinyAssetContainer.h"

template<typename Container>
concept TinyIsAssetContainer = tiny_is_child_of( Container, ITinyAssetContainer );

template<typename Asset>
	requires TinyIsAsset<Asset>
class TinyAssetContainer : tiny_inherit( ITinyAssetContainer ) {

protected:
	tiny_map<Asset> m_assets;

public:
	TinyAssetContainer( ) 
		: m_assets{ } 
	{ };

	virtual ~TinyAssetContainer( ) = default;

	tiny_implement( void UnLoad( TinyGame* game, const tiny_hash asset_hash ) ) { 
		auto asset_id = tiny_cast( 0, tiny_uint );
		
		if ( m_assets.find( asset_hash, asset_id ) ) {
			auto& asset = m_assets.at( asset_id );

			asset.Terminate( game );

			m_assets.erase( asset_id );
		}
	};

	tiny_implement( void Acquire( TinyGame* game, const tiny_hash asset_hash ) ) { 
		auto* asset = tiny_cast( GetAsset( asset_hash ), TinyAsset* );

		if ( asset )
			asset->Acquire( game );
	};

	tiny_implement( void Release( TinyGame* game, const tiny_hash asset_hash ) ) { 
		auto* asset = tiny_cast( GetAsset( asset_hash ), TinyAsset* );

		if ( asset )
			asset->Release( game );
	};

	tiny_implement( void Terminate( TinyGame* game ) ) { 
		for ( auto& asset : m_assets )
			asset.Data.Terminate( game );
	};

protected:
	Asset& Emplace( const tiny_string& alias ) { 
		m_assets.emplace( alias, { } );

		return m_assets[ alias ];
	};

public:
	tiny_implement( void GetAssetList( tiny_list<tiny_string>& list ) const ) { 
		for ( auto& asset : m_assets ) {
			auto asset_name = tiny_string{ asset.Alias };

			list.emplace_back( asset_name );
		}
	};

	tiny_implement( bool Find( const tiny_hash asset_hash ) const ) { 
		return m_assets.find( asset_hash );
	};

	tiny_implement( TinyAsset* GetAsset( const tiny_hash asset_hash ) ) {
		auto asset_id = tiny_cast( 0, tiny_uint );
		auto* asset   = tiny_cast( nullptr, TinyAsset* );

		if ( m_assets.find( asset_hash, asset_id ) )
			asset = tiny_rvalue( m_assets.at( asset_id ) );

		return asset;
	};

	tiny_implement( const TinyAsset* GetAsset( const tiny_hash asset_hash ) const ) {
		auto asset_id = tiny_cast( 0, tiny_uint );
		auto* asset   = tiny_cast( nullptr, const TinyAsset* );
		
		if ( m_assets.find( asset_hash, asset_id ) )
			asset = tiny_rvalue( m_assets.at( asset_id ) );

		return asset;
	};

};
