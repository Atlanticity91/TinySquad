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
 * @creation : 13/10/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "Utils/TinyArchiveContainer.h"

te_class TinyAssetManager final {

private:
	TinyAssetImporter		_importer;
	tiny_list<tiny_storage> _containers;

public:
	TinyAssetManager( );

	~TinyAssetManager( ) = default;

	bool Initialize( TinyFilesystem& filesystem, TinyConfig*& game_config );

	bool Import( TinyGame* game, const tiny_string& path );

	tiny_inline bool Export(
		TinyGame* game,
		const tiny_uint type,
		const tiny_string& alias,
		const c_pointer builder
	);

	tiny_inline bool Load( TinyGame* game, const tiny_string& path );

	bool Load( TinyGame* game, const tiny_string& alias, const tiny_string& path );

	tiny_inline void UnLoad( TinyGame* game, const TinyAssetHandle& handle );

	void UnLoad( TinyGame* game, const tiny_uint asset_type, const tiny_hash& asset_hash );

	bool Acquire( TinyGame* game, TinyAssetHandle& handle );

	void Release( TinyGame* game, TinyAssetHandle& handle );

	void Terminate( TinyGame* game );

public:
	template<typename Container>
		requires tiny_is_child_of( Container, ITinyAssetContainer )
	void Register( const tiny_uint asset_type ) {
		auto container = tiny_storage{ };

		if ( tiny_make_storage( container, Container ) ) {
			if ( asset_type < _containers.size( ) ) {
				if ( !_containers[ asset_type ].GetIsValid( ) )
					_containers[ asset_type ] = container;
				else
					tiny_deallocate( container );
			} else {
				if ( asset_type < _containers.size( ) + 1 )
					_containers.emplace_back( container );
				else
					tiny_deallocate( container );
			}
		}
	};

private:
	void RegisterTypes( );

	bool LoadConfig( TinyFilesystem& filesystem, TinyConfig*& game_config );

	bool LoadArchiveFile( TinyGame* game, const tiny_string& path );

	bool LoadAssetFile( TinyGame* game, const tiny_string& alias, const tiny_string& path );

public:
	TinyAssetImporter& GetImporter( );

	ITinyAssetContainer* GetContainer( const tiny_uint asset_type );

	const ITinyAssetContainer* GetContainer( const tiny_uint asset_type ) const;

	bool GetExist( const TinyAssetHandle& handle ) const;

	bool GetExist( const tiny_uint type, const tiny_hash asset_hash ) const;

	const TinyAsset* GetAsset( const TinyAssetHandle& handle ) const;

	const tiny_list<tiny_string> GetAssetList( const tiny_uint type ) const;

public:
	template<typename Asset>
		requires tiny_is_child_of( Asset, TinyAsset )
	const Asset* GetAssetAs( const TinyAssetHandle& handle ) const {
		auto* asset = GetAsset( handle );

		return tiny_cast( asset, const Asset* );
	};

	template<typename Container>
		requires tiny_is_child_of( Container, ITinyAssetContainer )
	Container* GetContainerAs( const tiny_uint type ) {
		auto* container = GetContainer( type );

		return tiny_cast( container, const Container* );
	};

	template<typename Container>
		requires tiny_is_child_of( Container, ITinyAssetContainer )
	const Container* GetContainerAs( const tiny_uint type ) const {
		auto* container = GetContainer( type );
		
		return tiny_cast( container, const Container* );
	};

};
