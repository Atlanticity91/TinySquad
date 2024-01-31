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

#include "Utils/TinyConfigManager.h"

te_class TinyAssetManager final {

private:
	TinyAssetImportManager _importers;
	TinyAssetRegistry	   _registry;
	TinyAssetListManager   _managers;

public:
	TinyAssetManager( );

	~TinyAssetManager( ) = default;

	bool Initialize( TinyFilesystem& filesystem, TinyGameConfig& game_config );

	bool Import( TinyGame* game, const tiny_string& path );

	bool Export( TinyGame* game, const tiny_string& name, c_pointer& asset_builder );

	bool Export( 
		TinyGame* game, 
		TinyAssetTypes type, 
		const tiny_string& path,
		c_pointer& asset_builder 
	);

	bool LoadRegistry( TinyGame* game, const tiny_string& path );

	bool LoadPath( TinyGame* game, const tiny_string& path );

	bool Load( TinyGame* game, const tiny_string& asset_name );

	bool Load( TinyGame* game, const tiny_hash asset_hash );

	bool ReLoad( TinyGame* game, const tiny_string& asset_name );

	bool ReLoad( TinyGame* game, const tiny_hash asset_hash );

	void Unload( TinyGame* game, const tiny_hash asset_hash );

	bool Create(
		TinyGame* game,
		const tiny_string& name,
		TinyAssetTypes type,
		c_pointer asset_builder
	);

	bool ReCreate(
		TinyGame* game,
		const tiny_string& name,
		TinyAssetTypes type,
		c_pointer asset_builder
	);

	bool Acquire( TinyGame* game, TinyAsset& asset );

	bool Acquire( TinyGame* game, TinyAsset& asset, const tiny_string& new_asset );

	void Release( TinyGame* game, TinyAsset& asset );

	void Terminate( TinyGame* game );

private:
	bool LoadConfig( TinyFilesystem& filesystem, TinyGameConfig& game_config );

public:
	TinyAssetImportManager& GetImporter( );

	TinyAssetRegistry& GetRegistry( );

	tiny_hash GenerateMetadata( TinyFilesystem& filesystem, TinyPathInformation& path );

	TinyGameConfig& GetGameConfig( );

	tiny_inline bool GetExist( const tiny_string& asset ) const;

	bool GetExist( const tiny_string& asset, tiny_hash& asset_hash ) const;

	bool GetMetadata( const tiny_string& asset_name, TinyAssetMetadata& metadata );

	c_pointer GetAsset( const TinyAsset& asset );

	const c_pointer GetAsset( const TinyAsset& asset ) const;

	tiny_inline tiny_list<tiny_string> GetAssets( tiny_uint type );

public:
	template<typename Type>
	Type* GetAssetAs( const TinyAsset& asset ) {
		return tiny_cast( GetAsset( asset ), Type* );
	};

	template<typename Type>
	const Type* GetAssetAs( const TinyAsset& asset ) const {
		return tiny_cast( GetAsset( asset ), const Type* );
	};

};
