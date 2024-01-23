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

#include "TinyAssetList.h"

#define TAL_MAP( TYPE ) Map< ##TYPE##Manager>( )

te_class TinyAssetListManager final {

private:
	tiny_array<ITinyAssetList*, TA_TYPE_COUNT> _assets;

public:
	TinyAssetListManager( );

	~TinyAssetListManager( ) = default;

	bool Load( TinyGame* game, TinyAssetManager& assets, TinyAssetMetadata& metadata );

	bool ReLoad( TinyGame* game, TinyAssetManager& assets, TinyAssetMetadata& metadata );

	void Unload( TinyGame* game, TinyAssetManager& assets, TinyAssetMetadata& metadata );

	bool Create( TinyGame* game, TinyAssetMetadata& metadata, c_ptr asset_builder );

	bool ReCreate(
		TinyGame* game,
		TinyAssetMetadata& metadata,
		c_ptr asset_builder
	);

	void Clear( TinyGame* game );

	void Terminate( TinyGame* game );

public:
	template<typename AssetList>
	void Map( ) {
		auto* manager = new AssetList( );

		if ( manager ) {
			auto type = (tiny_uint)manager->GetType( );

			if ( !_assets[ type ] )
				_assets[ type ] = manager;
		}
	};

public:
	ITinyAssetList* GetManager( tiny_uint type ) const;

	c_ptr Get( const TinyAsset& asset );

	const c_ptr Get( const TinyAsset& asset ) const;

};
