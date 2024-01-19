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

#pragma once

#include <TinyEngine/Assets/Lists/TinyAssetListManager.h>

te_struct TinyGameConfig : tiny_inherit( TinyAppConfig ) { };

te_class TinyConfigManager final : tiny_inherit( ITinyAssetList ) {

private:
	TinyGameConfig _config;

public:
	TinyConfigManager( );

	~TinyConfigManager( ) = default;

	bool Load( TinyFilesystem& filesystem, TinyGameConfig& game_config );

	tiny_implement( tiny_uint Load(
		TinyGame* game,
		TinyFilesystem & filesystem,
		TinyAssetManager& assets,
		TinyAssetMetadata& metadata
	) );

	tiny_implement( bool ReLoad(
		TinyGame* game,
		TinyFilesystem& filesystem,
		TinyAssetManager& assets,
		TinyAssetMetadata& metadata
	) );

	tiny_implement( void Unload(
		TinyGame* game,
		TinyAssetManager& assets,
		TinyAssetMetadata& metadata
	) );

	tiny_implement( tiny_uint Create(
		TinyGame* game,
		TinyAssetMetadata& metadata,
		c_ptr asset_builder
	) );

	tiny_implement( bool ReCreate(
		TinyGame* game,
		TinyAssetMetadata& metadata,
		c_ptr asset_builder
	) );

	tiny_implement( void Clear( TinyGame* game ) );

	tiny_implement( void Terminate( TinyGame* game ) );

public:
	tiny_implement( bool GetIsValid( tiny_uint asset_id ) const );

	tiny_implement( c_ptr GetAsset( const TinyAsset& asset ) );

	tiny_implement( const c_ptr GetAsset( const TinyAsset& asset ) const );

	TinyGameConfig& GetGameConfig( );

};
