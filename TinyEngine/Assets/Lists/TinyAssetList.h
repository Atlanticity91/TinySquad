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
 * @creation : 10/11/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "ITinyAssetList.h"

template<typename Type>
struct TinyAssetNode {

	bool IsActive;
	Type Element;

	TinyAssetNode( ) 
		: IsActive { false },
		Element{ }
	{ };

	TinyAssetNode( const TinyAssetNode& other ) 
		: IsActive{ other.IsActive },
		Element{ other.Element }
	{ };

	TinyAssetNode& operator=( const TinyAssetNode& other ) { 
		IsActive = other.IsActive;
		Element  = other.Element;

		return tiny_self;
	};

};

template<TinyAssetTypes Type, typename Asset>
class TinyAssetList : tiny_inherit( ITinyAssetList ) {

	using Node = TinyAssetNode<Asset>;

protected:
	tiny_list<Node> _assets;

public:
	TinyAssetList( )
		: ITinyAssetList{ Type },
		_assets { }
	{ };

	~TinyAssetList( ) = default;

	tiny_implement( tiny_uint Load( 
		TinyGame* game,
		TinyFilesystem& filesystem,
		TinyAssetManager& assets, 
		TinyAssetMetadata& metadata 
	) ) {
		auto asset_handle = TINY_UINT_MAX;
		auto asset_id	  = FindEmpty( );
		auto file		  = filesystem.OpenFile( metadata.Target.c_str( ), Tiny::TF_ACCESS_READ );

		if ( asset_id == _assets.size( ) || _assets[ asset_id ].IsActive ) {
			_assets.create_back( );

			asset_id = _assets.size( ) - 1;
		}

		if ( file.GetIsValid( ) && OnLoad( game, file, _assets[ asset_id ].Element ) ) {
			_assets[ asset_id ].IsActive = true;

			asset_handle = asset_id;
		} else
			OnUnLoad( game, _assets[ asset_id ].Element );

		return asset_handle;
	};

	tiny_implement( void Unload(
		TinyGame* game,
		TinyAssetManager& assets,
		TinyAssetMetadata& metadata 
	) ) {
		auto handle = metadata.Handle;

		if ( GetIsValid( handle ) ) {
			_assets[ handle ].IsActive = false;

			OnUnLoad( game, _assets[ handle ].Element );
		}
	};

	tiny_implement( bool ReLoad(
		TinyGame* game,
		TinyFilesystem& filesystem,
		TinyAssetManager& assets,
		TinyAssetMetadata& metadata
	) ) { 
		auto state		 = false;

		if ( GetIsValid( metadata.Handle ) ) {
			auto file = filesystem.OpenFile( metadata.Target.c_str( ), Tiny::TF_ACCESS_READ );

			OnUnLoad( game, _assets[ metadata.Handle ].Element );

			state = OnLoad( game, file, _assets[ metadata.Handle ].Element );
		} else
			state = Load( game, filesystem, assets, metadata ) < _assets.size( );

		return state;
	};

	tiny_implement( tiny_uint Create(
		TinyGame* game,
		TinyAssetMetadata& metadata,
		c_ptr asset_builder
	) ) { 
		auto asset_handle = TINY_UINT_MAX;
		auto asset_id	  = FindEmpty( );

		if ( asset_id == _assets.size( ) || _assets[ asset_id ].IsActive )
				_assets.create_back( );

		if ( OnCreate( game, asset_builder, _assets[ asset_id ].Element ) ) {
			_assets[ asset_id ].IsActive = true;

			asset_handle = asset_id;
		} else
			OnUnLoad( game, _assets[ asset_id ].Element );

		return asset_handle;
	}

	tiny_implement( bool ReCreate(
		TinyGame* game,
		TinyAssetMetadata& metadata,
		c_ptr asset_builder
	) ) {
		auto handle = metadata.Handle;
		auto state  = false;

		if ( GetIsValid( handle ) ) {
			OnUnLoad( game, _assets[ handle ].Element );

			state = OnCreate( game, asset_builder, _assets[ handle ].Element );
		} else
			state = Create( game, metadata, asset_builder ) < _assets.size( );

		return state;
	}

	tiny_implement( void Clear( TinyGame* game ) ) { 
		for ( auto& asset : _assets ) {
			if ( asset.IsActive ) {
				asset.IsActive = false;

				OnUnLoad( game, asset.Element );
			}
		}
	};

	tiny_implement( void Terminate( TinyGame* game ) ) { Clear( game ); };

protected:
	tiny_abstract( bool OnLoad( 
		TinyGame* game,
		TinyFile& file, 
		Asset& element 
	) );

	tiny_abstract( bool OnCreate(
		TinyGame* game,
		c_ptr asset_builder, 
		Asset& element 
	) );

	tiny_abstract( void OnUnLoad( TinyGame* game, Asset& element ) );

public:
	tiny_implement( bool GetIsValid( tiny_uint handle ) const ) {
		return handle < _assets.size( ) && _assets[ handle ].IsActive;
	};

	tiny_implement( c_ptr GetAsset( const TinyAsset& asset ) ) {
		auto* element = ( c_ptr )nullptr;

		if ( GetIsValid( asset.Handle ) )
			element = tiny_cast( &_assets[ asset.Handle ].Element, c_ptr );

		return element;
	};

	tiny_implement( const c_ptr GetAsset( const TinyAsset& asset ) const ) {
		auto* element = (const c_ptr)nullptr;

		if ( GetIsValid( asset.Handle ) )
			element = tiny_cast( &_assets[ asset.Handle ].Element, const c_ptr );

		return element;
	};

private:
	tiny_uint FindEmpty( ) const {
		auto asset_id = _assets.size( );

		while ( asset_id > 0 && asset_id-- > 0 ) {
			if ( _assets[ asset_id ].IsActive )
				continue;

			break;
		}

		return asset_id;
	};

};
