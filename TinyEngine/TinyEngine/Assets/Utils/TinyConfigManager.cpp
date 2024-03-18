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
 * @creation : 24/11/2023
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
TinyConfigManager::TinyConfigManager( ) 
	: ITinyAssetList{ TA_TYPE_CONFIG },
	_config{ 1280, 720 }
{ }

bool TinyConfigManager::Load( TinyFilesystem& filesystem, TinyGameConfig& game_config ) {
	auto path  = filesystem.GetConfigPath( );
	auto state = filesystem.GetFileExist( path );

	if ( state ) {
		auto header = TinyAssetHeader{ };
		auto file = filesystem.OpenFile( path, Tiny::TF_ACCESS_READ );

		file.Read( header );

		state = header.Type == TA_TYPE_CONFIG;

		if ( state ) {
			state = file.Read( _config ) > 0;

			if ( state )
				game_config = _config;
		}
	}

	return state;
}

tiny_uint TinyConfigManager::Load(
	TinyGame* game,
	TinyFilesystem& filesystem,
	TinyAssetManager& assets,
	TinyAssetMetadata& metadata
) {
	auto game_config = TinyGameConfig{ };

	return Load( filesystem, game_config ) ? 0 : TINY_UINT_MAX;
}

bool TinyConfigManager::ReLoad(
	TinyGame* game,
	TinyFilesystem& filesystem,
	TinyAssetManager& assets,
	TinyAssetMetadata& metadata
) {
	auto game_config = TinyGameConfig{ };

	return Load( filesystem, game_config );
}

void TinyConfigManager::Unload(
	TinyGame* game,
	TinyAssetManager& assets,
	TinyAssetMetadata& metadata
) { }

tiny_uint TinyConfigManager::Create(
	TinyGame* game,
	TinyAssetMetadata& metadata,
	c_pointer asset_builder
) { return TINY_UINT_MAX; }

bool TinyConfigManager::ReCreate(
	TinyGame* game,
	TinyAssetMetadata& metadata,
	c_pointer asset_builder
) { return false; }

void TinyConfigManager::Clear( TinyGame* game ) { }

void TinyConfigManager::Terminate( TinyGame* game ) {
	auto& filesystem = game->GetFilesystem( );
	auto path		 = filesystem.GetConfigPath( );
	auto file		 = filesystem.OpenFile( path, Tiny::TF_ACCESS_WRITE );

	file.Write( TinyAssetHeader{ TA_TYPE_CONFIG } );
	file.Write( _config );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyConfigManager::GetIsValid( tiny_uint asset_id ) const { return true; }

c_pointer TinyConfigManager::GetAsset( const TinyAsset& asset ) {
	return tiny_cast( &_config, c_pointer );
}

const c_pointer TinyConfigManager::GetAsset( const TinyAsset& asset ) const {
	return tiny_cast( &_config, const c_pointer );
}

TinyGameConfig& TinyConfigManager::GetGameConfig( ) { return _config; }
