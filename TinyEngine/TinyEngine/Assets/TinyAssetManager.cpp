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
	: _importer{ },
	_containers{ TA_TYPE_COUNT }
{ }

bool TinyAssetManager::Initialize(
	TinyFilesystem& filesystem,
	TinyConfig*& game_config
) {
	_importer.Initialize( );

	RegisterTypes( );

	return LoadConfig( filesystem, game_config );
}

bool TinyAssetManager::Import( TinyGame* game, const tiny_string& path ) {
	auto& filesystem = game->GetFilesystem( );
	auto state		 = false;

	if ( path.is_valid( ) && filesystem.GetFileExist( path ) ) {
		auto path_info = filesystem.GetInformation( path );
		auto file	   = filesystem.OpenFile( path, Tiny::TF_ACCESS_READ );

		state = _importer.Import( game, file, path_info );
	}

	return state;
}

bool TinyAssetManager::Export(
	TinyGame* game,
	const tiny_uint type,
	const tiny_string& alias,
	const c_pointer builder
) {
	return _importer.Export( game, type, alias, builder );
}

bool TinyAssetManager::Load( TinyGame* game, const tiny_string& path ) { 
	return Load( game, "", path );
}

bool TinyAssetManager::Load( 
	TinyGame* game, 
	const tiny_string& alias, 
	const tiny_string& path 
) {
	auto state = false;

	if ( path[ 0 ] == '@' )
		state = LoadArchiveFile( game, path );
	else
		state = LoadAssetFile( game, alias, path );

	return state;
}

void TinyAssetManager::UnLoad( TinyGame* game, const TinyAssetHandle& handle ) {
	UnLoad( game, handle.Type, handle.Hash );
}

void TinyAssetManager::UnLoad( 
	TinyGame* game, 
	const tiny_uint asset_type, 
	const tiny_hash& asset_hash 
) {
	auto* container = GetContainer( asset_type );

	if ( container )
		container->UnLoad( game, asset_hash );
}

bool TinyAssetManager::Acquire( TinyGame* game, TinyAssetHandle& handle ) {
	auto* container = GetContainer( handle.Type );
	auto state	    = container != nullptr;

	if ( state ) {
		if ( !container->Find( handle.Hash ) ) {
			auto* container = GetContainer( TA_TYPE_ARCHIVE );

			state = tiny_cast( container, TinyArchiveContainer* )->Load( game, handle.Hash );
		} 
		
		if ( state )
			container->Acquire( game, handle.Hash );
	}

	return state;
}

void TinyAssetManager::Release( TinyGame* game, TinyAssetHandle& handle ) {
	auto* container = GetContainer( handle.Type );

	if ( container )
		container->Release( game, handle.Hash );
}

void TinyAssetManager::Terminate( TinyGame* game ) {
	for ( auto& containter : _containers ) {
		if ( containter.GetIsValid( ) )
			containter.As<ITinyAssetContainer>( )->Terminate( game );
	}
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE ===
////////////////////////////////////////////////////////////////////////////////////////////
void TinyAssetManager::RegisterTypes( ) {
	Register<TinyConfigContainer>( TA_TYPE_CONFIG );
	Register<TinyArchiveContainer>( TA_TYPE_ARCHIVE );
	Register<TinyTexture2DManager>( TA_TYPE_TEXTURE_2D );
	//Register<TinyArchiveContainer>( TA_TYPE_TEXTURE_3D );
	//Register<TinyArchiveContainer>( TA_TYPE_TEXTURE_CUBEMAP );
	//Register<TinyArchiveContainer>( TA_TYPE_TEXTURE_ATLAS );
	//Register<TinyArchiveContainer>( TA_TYPE_TEXTURE_LUT );
	//Register<TinyArchiveContainer>( TA_TYPE_ANIMATION_2D );
	//Register<TinyArchiveContainer>( TA_TYPE_ANIMATION_3D );
	//Register<TinyFontManager>( TA_TYPE_FONT );
	Register<TinyShaderManager>( TA_TYPE_SHADER );
	Register<TinyMaterialManager>( TA_TYPE_MATERIAL );
	//Register<TinyArchiveContainer>( TA_TYPE_GEOMETRY );
	Register<TinyCueManager>( TA_TYPE_CUE );
	//Register<TinyArchiveContainer>( TA_TYPE_SANPLES );
	//Register<TinyArchiveContainer>( TA_TYPE_SCRIPT );
	//Register<TinyArchiveContainer>( TA_TYPE_SCENE );
	//Register<TinyArchiveContainer>( TA_TYPE_LOCALISATION );
	//Register<TinyArchiveContainer>( TA_TYPE_TROPHY );
	//Register<TinyArchiveContainer>( TA_TYPE_SAVE );
	Register<TinyAddonManager>( TA_TYPE_ADDON );
}

bool TinyAssetManager::LoadConfig( TinyFilesystem& filesystem, TinyConfig*& game_config ) {
	auto* container = tiny_cast( GetContainer( TA_TYPE_CONFIG ), TinyConfigContainer* );
	auto state		= false;

	if ( container )
		state = container->Load( filesystem, game_config );

	return state;
}

bool TinyAssetManager::LoadArchiveFile( TinyGame* game, const tiny_string& path ) {
	auto* container = GetContainer( TA_TYPE_ARCHIVE );
	auto state = false;

	if ( container ) {
		auto asset_name = path.sub_string( 1 );

		state = tiny_cast( container, TinyArchiveContainer* )->Load( game, asset_name );
	}

	return state;
}

bool TinyAssetManager::LoadAssetFile( 
	TinyGame* game, 
	const tiny_string& alias, 
	const tiny_string& path 
) {
	auto& filesystem = game->GetFilesystem( );
	auto state		 = false;

	if ( !path.is_empty( ) && filesystem.GetFileExist( path ) ) {
		auto file = filesystem.OpenFile( path, Tiny::TF_ACCESS_READ );

		if ( file.GetIsValid( ) ) {
			auto header = TinyAssetHeader{ };

			file.Read( header );

			if ( header.GetIsAsset( ) ) {
				auto* container = GetContainer( header.Type );

				if ( container ) {
					if ( !alias.is_empty( ) )
						state = container->Load( game, alias, file );
					else {
						auto file_info = filesystem.GetInformation( path );

						state = container->Load( game, { file_info.Name }, file );
					}
				}
			}
		}
	}

	return state;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyAssetImporter& TinyAssetManager::GetImporter( ) { return _importer; }

ITinyAssetContainer* TinyAssetManager::GetContainer( const tiny_uint asset_type ) {
	auto container = tiny_cast( nullptr, ITinyAssetContainer* );

	if ( asset_type < _containers.size( ) )
		container = _containers[ asset_type ].As<ITinyAssetContainer>( );

	return container;
}

const ITinyAssetContainer* TinyAssetManager::GetContainer( 
	const tiny_uint asset_type 
) const {
	return nullptr;
}

bool TinyAssetManager::GetExist( const TinyAssetHandle& handle ) const {
	auto* container = GetContainer( handle.Type );
	auto state		= false;

	if ( container )
		state = container->Find( handle.Hash );

	return state;
}

const TinyAsset* TinyAssetManager::GetAsset( const TinyAssetHandle& handle ) const {
	auto* container = GetContainer( handle.Type );
	auto* asset		= tiny_cast( nullptr, const TinyAsset* );

	if ( container )
		asset = container->GetAsset( handle.Hash );

	return  asset;
}

const tiny_list<tiny_string> TinyAssetManager::GetAssetList( const tiny_uint type ) const {
	auto* container = GetContainer( type );
	auto asset_list = tiny_list<tiny_string>{ };

	asset_list.emplace_back( "Undefined" );

	if ( container )
		container->GetAssetList( asset_list );

	return asset_list;
}
