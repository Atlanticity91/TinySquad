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

#include <TinyEngine/__tiny_engine_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyAssetListManager::TinyAssetListManager( )
	: _assets{ }
{ }

bool TinyAssetListManager::Load( 
	TinyGame* game,
	TinyAssetManager& assets, 
	TinyAssetMetadata& metadata 
) {
	auto& filesystem = game->GetFilesystem( );
	auto* manager    = GetManager( metadata.Type );
	auto state		 = manager != nullptr && !metadata.Target.empty( );

	if ( state ) {
		metadata.Handle = manager->Load( game, filesystem, assets, metadata );

		state = metadata.Handle != TINY_UINT_MAX;
	}

	return state;
}

bool TinyAssetListManager::ReLoad(
	TinyGame* game,
	TinyAssetManager& assets,
	TinyAssetMetadata& metadata
) {
	auto& filesystem = game->GetFilesystem( );
	auto* manager	 = GetManager( TA_TYPE_TEXTURE_2D );
	auto state		 = manager != nullptr;

	if ( state )
		state = manager->ReLoad( game, filesystem, assets, metadata );

	return state;
}

void TinyAssetListManager::Unload(
	TinyGame* game,
	TinyAssetManager& assets, 
	TinyAssetMetadata& metadata 
) {
	auto* manager = GetManager( metadata.Type );
	
	if ( manager ) {
		manager->Unload( game, assets, metadata );

		metadata.Handle = TINY_UINT_MAX;
	}
}

bool TinyAssetListManager::Create(
	TinyGame* game,
	TinyAssetMetadata& metadata,
	c_ptr asset_builder
) {
	auto* manager = GetManager( metadata.Type );
	auto state    = manager != nullptr && asset_builder != nullptr;

	if ( state ) {
		metadata.Handle = manager->Create( game, metadata, asset_builder );

		state = metadata.Handle != TINY_UINT_MAX;
	}

	return state;
}

bool TinyAssetListManager::ReCreate(
	TinyGame* game,
	TinyAssetMetadata& metadata,
	c_ptr asset_builder
) {
	auto* manager = GetManager( TA_TYPE_TEXTURE_2D );
	auto state    = manager != nullptr && asset_builder != nullptr;

	if ( state )
		state = manager->ReCreate( game, metadata, asset_builder );

	return state;
}

void TinyAssetListManager::Clear( TinyGame* game ) {
	auto type = tiny_cast( 0, tiny_uint );

	while ( type < TA_TYPE_COUNT ) {
		auto* manager = _assets[ type ];

		if ( manager != nullptr )
			manager->Clear( game );

		type += 1;
	}
}

void TinyAssetListManager::Terminate( TinyGame* game ) {
	auto type = tiny_cast( 0, tiny_uint );

	while ( type < TA_TYPE_COUNT ) {
		auto* manager = _assets[ type ];
		
		if ( manager != nullptr ) {
			manager->Terminate( game );

			delete manager;

			_assets[ type ] = nullptr;
		}

		type += 1;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
ITinyAssetList* TinyAssetListManager::GetManager( TinyAssetTypes type ) const {
	auto* manager = tiny_cast( nullptr, ITinyAssetList* );

	if ( type < TA_TYPE_COUNT )
		manager = _assets[ tiny_cast( type, tiny_uint ) ];

	return manager;
}

c_ptr TinyAssetListManager::Get( const TinyAsset& asset ) {
	auto* asset_value = tiny_cast( nullptr, c_ptr );
	auto* manager	  = GetManager( asset.Type );

	if ( manager && manager->GetIsValid( asset.Handle ) )
		asset_value = manager->GetAsset( asset );

	return asset_value;
}

const c_ptr TinyAssetListManager::Get( const TinyAsset& asset ) const {
	auto* asset_value = tiny_cast( nullptr, const c_ptr );
	auto* manager	  = GetManager( asset.Type );

	if ( manager && manager->GetIsValid( asset.Handle ) )
		asset_value = manager->GetAsset( asset );

	return asset_value;
}
