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

#include <TinyEngine/__tiny_engine_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyAssetManager::TinyAssetManager( ) 
	: _importers{ },
	_registry{ },
	_managers{ }
{ }

bool TinyAssetManager::Initialize(
	TinyFilesystem& filesystem,
	TinyGameConfig& game_config 
) {
	_importers.Initialize( );

	_managers.TAL_MAP( TinyConfig );
	_managers.TAL_MAP( TinyTexture2D );
	//_managers.TAL_MAP( TinyTexture3D );
	//_managers.TAL_MAP( TinyTextureCubemap );
	//_managers.TAL_MAP( TinyTextureAtlas );
	//_managers.TAL_MAP( TinyTextureLut );
	//_managers.TAL_MAP( TinyFont );
	_managers.TAL_MAP( TinyShader );
	_managers.TAL_MAP( TinyMaterial );
	//_managers.TAL_MAP( TinyGeometry );
	_managers.TAL_MAP( TinyCue );
	_managers.TAL_MAP( TinyScript );
	//_managers.TAL_MAP( TinyAnimation2D );
	//_managers.TAL_MAP( TinyAnimation3D );
	//_managers.TAL_MAP( TinyScene );
	//_managers.TAL_MAP( TinyLocalisation );
	//_managers.TAL_MAP( TinyTrophy );
	//_managers.TAL_MAP( TinyArchive );
	//_managers.TAL_MAP( TinySave );
	//_managers.TAL_MAP( TinyAddon );
	//_managers.TAL_MAP( TinyToolbox );

	return LoadConfig( filesystem, game_config );
}

bool TinyAssetManager::Import( TinyGame* game, const tiny_string& path ) {
	auto& filesystem = game->GetFilesystem( );
	auto file_memory = tiny_storage{ };
	auto state		 = !path.is_empty( ) && filesystem.GetFileExist( path );

	if ( state ) {
		auto file = filesystem.OpenFile( path, Tiny::TF_ACCESS_READ );
		auto size = file.GetSize( );

		state = size > 0 && tiny_allocate( file_memory, size );

		if ( state ) {
			auto* buffer = file_memory.GetAddress( );

			size  = file.ReadAll( size, buffer );
			state = size > 0;

			if ( state ) {
				auto path_info = filesystem.GetInformation( path );
				auto builder   = tiny_storage{ };

				GenerateMetadata( filesystem, path_info );

				state = _importers.Import( game, path_info, file_memory, builder );

				if ( state ) {
					auto* asset_builder = builder.GetAddress( );

					state = Export( game, path_info.Name, asset_builder );
				}

				tiny_deallocate( builder );
			}

			tiny_deallocate( file_memory );
		}
	}

	return state;
}

bool TinyAssetManager::Export(
	TinyGame* game,
	const tiny_string& name,
	c_ptr& asset_builder
) { 
	auto metadata_hash = tiny_hash{ name };
	auto metadata_id   = tiny_cast( 0, tiny_uint );
	auto& filesystem   = game->GetFilesystem( );
	auto state		   = _registry.FindMetadata( metadata_hash, metadata_id );

	if ( state ) {
		auto& filesystem = game->GetFilesystem( );
		auto& metadata	 = _registry.GetMetadatas( ).at( metadata_id );
		auto file		 = filesystem.OpenFile( metadata.Target.c_str( ), Tiny::TF_ACCESS_WRITE );

		state = file.GetIsValid( );

		if ( state ) {
			state = _importers.Export( game, metadata.Type, file, asset_builder );

			if ( state && metadata.Reference > 0 )
				state = _managers.ReLoad( game, tiny_self, metadata );
		}
	}

	return state;
}

bool TinyAssetManager::Export( 
	TinyGame* game, 
	TinyAssetTypes type,
	const tiny_string& path,
	c_ptr& asset_builder
) {
	auto& filesystem = game->GetFilesystem( );
	auto state		 = !path.is_empty( );
	
	if ( state ) {
		auto name = filesystem.GetInformation( path ).Name;

		if ( !_registry.GetExist( name ) ) {
			state = filesystem.GetIsAssetFile( path );

			if ( state ) {
				_registry.Append( name, { type, path, path } );

				auto file = filesystem.OpenFile( path, Tiny::TF_ACCESS_WRITE );

				state = file.GetIsValid( );

				if ( state )
					state = _importers.Export( game, type, file, asset_builder );
			}
		} else
			state = Export( game, name, asset_builder );
	}

	return state;
}

bool TinyAssetManager::LoadRegistry( TinyGame* game, const tiny_string& path ) {
	auto& filesystem = game->GetFilesystem( );

	return _registry.Load( filesystem, path );
}

bool TinyAssetManager::LoadPath( TinyGame* game, const tiny_string& path ) {
	auto& filesystem = game->GetFilesystem( );
	auto path_info   = filesystem.GetInformation( path );
	auto asset_hash  = GenerateMetadata( filesystem, path_info );
	auto state		 = Load( game, asset_hash );

	if ( !state )
		_registry.Remove( asset_hash );

	return state;
}

bool TinyAssetManager::Load( TinyGame* game, const tiny_string& asset_name ) {
	auto asset_hash = tiny_hash{ asset_name };

	return Load( game, asset_hash );
}

bool TinyAssetManager::Load( TinyGame* game, const tiny_hash asset_hash ) {
	auto metadata_id = tiny_cast( 0, tiny_uint );
	auto state		 = _registry.FindMetadata( asset_hash, metadata_id );

	if ( state ) 
		state = _managers.Load( game, tiny_self, _registry[ metadata_id ] );

	return state;
}

bool TinyAssetManager::ReLoad( TinyGame* game, const tiny_string& asset_name ) {
	auto asset_hash = tiny_hash{ asset_name };

	return ReLoad( game, asset_hash );
}

bool TinyAssetManager::ReLoad( TinyGame* game, const tiny_hash asset_hash ) {
	auto metadata_id = tiny_cast( 0, tiny_uint );
	auto state = _registry.FindMetadata( asset_hash, metadata_id );

	if ( state )
		state = _managers.ReLoad( game, tiny_self, _registry[ metadata_id ] );

	return state;
}

void TinyAssetManager::Unload( TinyGame* game, const tiny_hash asset_hash ) {
	auto metadata_id = tiny_cast( 0, tiny_uint );
	
	if ( _registry.FindMetadata( asset_hash, metadata_id ) )
		_managers.Unload( game, tiny_self, _registry[ metadata_id ] );
}

bool TinyAssetManager::Create(
	TinyGame* game,
	const tiny_string& name,
	TinyAssetTypes type,
	c_ptr asset_builder
) {
	auto state = !name.is_empty( )		  && 
				 asset_builder != nullptr && 
				 !_registry.GetExist( name );

	if ( state ) {
		auto metadata_id = _registry.Append( name, { type } );
		auto& metadata   = _registry.GetMetadatas( ).at( metadata_id );

		state = _managers.Create( game, metadata, asset_builder );

		if ( !state )
			_registry.Remove( name );
	}

	return state;
}

bool TinyAssetManager::ReCreate(
	TinyGame* game,
	const tiny_string& name,
	TinyAssetTypes type,
	c_ptr asset_builder
) {
	auto asset_hash = tiny_hash{ name };
	auto asset_id   = tiny_cast( 0, tiny_uint );
	auto state		= !name.is_empty( ) && _registry.FindMetadata( asset_hash, asset_id );

	if ( state ) {
		auto& metadata = _registry.GetMetadatas( ).at( asset_id );

		state = metadata.Type == type;

		if ( state )
			state = _managers.ReCreate( game, metadata, asset_builder );

		if ( !state )
			_registry.Remove( name );
	} else
		state = Create( game, name, type, asset_builder );

	return state;
}

bool TinyAssetManager::Acquire( TinyGame* game, TinyAsset& asset ) {
	auto metadata_id = tiny_cast( 0, tiny_uint );
	auto state		 = _registry.FindMetadata( asset.Hash, metadata_id );

	if ( state ) {
		auto& metadata = _registry[ metadata_id ];

		if ( metadata.Handle == TINY_UINT_MAX )
			state = _managers.Load( game, tiny_self, metadata );

		if ( state ) {
			metadata.Reference += 1;

			asset.Handle = metadata.Handle;
		}
	}

	return state;
}

void TinyAssetManager::Release( TinyGame* game, TinyAsset& asset ) {
	auto metadata_id = tiny_cast( 0, tiny_uint );
	auto state		 = _registry.FindMetadata( asset.Hash, metadata_id );

	if ( state ) {
		auto& metadata = _registry[ metadata_id ];

		metadata.Reference -= 1;

		if ( metadata.Reference == 0 )
			_managers.Unload( game, tiny_self, metadata );

		asset.Hash   = tiny_cast( 0, tiny_uint );
		asset.Handle = TINY_UINT_MAX;
	}
}

void TinyAssetManager::Terminate( TinyGame* game ) {
	auto& graphics = game->GetGraphics( );
	auto context   = graphics.GetContext( );

	_managers.Terminate( game );
}

bool TinyAssetManager::LoadConfig( 
	TinyFilesystem& filesystem, 
	TinyGameConfig& game_config 
) {
	auto* manager = tiny_cast( _managers.GetManager( TA_TYPE_CONFIG ), TinyConfigManager* );
	
	return manager && manager->Load( filesystem, game_config );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyAssetImportManager& TinyAssetManager::GetImporter( ) { return _importers; }

TinyAssetRegistry& TinyAssetManager::GetRegistry( ) { return _registry; }

tiny_hash TinyAssetManager::GenerateMetadata( 
	TinyFilesystem& filesystem,
	TinyPathInformation& path_info
) {
	auto new_path = filesystem.ConvertToAsset( path_info.Full );
	auto type	  = _importers.GetTypeOf( path_info.Extension );

	if ( _registry.GetExist( path_info.Name.c_str( ) ) )
		 path_info.Name += "_";

	_registry.Append( path_info.Name, { type, path_info.Full, new_path } );

	return tiny_hash{ path_info.Name };
}

TinyGameConfig& TinyAssetManager::GetGameConfig( ) {
	auto* manager = _managers.GetManager( TA_TYPE_CONFIG );

	return tiny_cast( manager, TinyConfigManager* )->GetGameConfig( );
}

bool TinyAssetManager::GetExist( const tiny_string& asset ) const {
	return _registry.GetExist( asset );
}

bool TinyAssetManager::GetExist( const tiny_string& asset, tiny_hash& asset_hash ) const {
	auto state = GetExist( asset );

	if ( state )
		asset_hash = tiny_hash{ asset };

	return state;
}

c_ptr TinyAssetManager::GetAsset( const TinyAsset& asset ) {
	auto* asset_value = tiny_cast( nullptr, c_ptr );

	if ( _registry.GetExist( asset.Hash ) )
		asset_value = _managers.Get( asset );

	return  asset_value;
}

tiny_list<tiny_string> TinyAssetManager::GetAssets( TinyAssetTypes type ) {
	return _registry.GetAssets( type );
}
