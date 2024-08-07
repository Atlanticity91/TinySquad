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
 *			  Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#include <TinyEngine/__tiny_engine_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyAssetManager::TinyAssetManager( ) 
	: m_importer{ },
	m_containers{ TA_TYPE_COUNT }
{ }

bool TinyAssetManager::Initialize( TinyGame* game, TinyConfig*& game_config ) {
	m_importer.Initialize( );

	RegisterTypes( );

	return LoadConfig( game, game_config );
}

bool TinyAssetManager::Import( TinyGame* game, const tiny_string& path ) {
	auto& filesystem = game->GetFilesystem( );
	auto state		 = false;

	if ( path.get_is_valid( ) && filesystem.GetFileExist( path ) ) {
		auto path_info = filesystem.GetInformation( path );
		auto file	   = filesystem.OpenFile( path, TF_ACCESS_READ );

		state = m_importer.Import( game, tiny_rvalue( file ), path_info );
	}

	return state;
}

bool TinyAssetManager::Export(
	TinyGame* game,
	const tiny_uint type,
	const tiny_string& alias,
	const native_pointer builder
) {
	return m_importer.Export( game, type, alias, builder );
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

	if ( path.get_is_valid( ) ) {
		if ( path[ 0 ] == '@' )
			state = LoadArchiveFile( game, path );
		else
			state = LoadAssetFile( game, alias, path );
	}

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

			state = tiny_cast( container, TinyArchiveContainer* )->Load( game, handle );
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
	for ( auto& containter : m_containers ) {
		if ( containter.GetIsValid( ) )
			containter.As<ITinyAssetContainer>( )->Terminate( game );
	}
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC STATIC ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyAssetManager::Export( TinyFile& file, const TinyArchiveBuilder& archive_builder ) {
	auto state = file.GetIsValid( );

	if ( state ) {
		auto entry_count = archive_builder.Entries.size( );
		auto header		 = TinyAssetHeader{ TA_TYPE_ARCHIVE };

		file.Write( header );
		file.Write( archive_builder.Author );
		file.Write( entry_count );

		for ( auto& entry : archive_builder.Entries ) {
			auto& entry_data = entry.Data;

			file.Write( entry.Alias );
			file.Write( entry_data.Path );
			file.Write( entry_data.Date );
			file.Write( entry_data.Type );
			file.Write( entry_data.Offset );
			file.Write( entry_data.Size );
			file.Write( entry_data.Compresed );
		}
	}

	return state;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE ===
////////////////////////////////////////////////////////////////////////////////////////////
void TinyAssetManager::RegisterTypes( ) {
	Register<TinyConfigContainer>( TA_TYPE_CONFIG );
	Register<TinyArchiveContainer>( TA_TYPE_ARCHIVE );
	Register<TinyTexture2DManager>( TA_TYPE_TEXTURE_2D );
	Register<TinyTexture3DManager>( TA_TYPE_TEXTURE_3D );
	Register<TinyTextureAtlasManager>( TA_TYPE_TEXTURE_ATLAS );
	Register<TinyTextureCubemapManager>( TA_TYPE_TEXTURE_CUBEMAP );
	Register<TinyTextureLutManager>( TA_TYPE_TEXTURE_LUT );
	Register<TinyAnimation2DManager>( TA_TYPE_ANIMATION_2D );
	Register<TinyAnimation3DManager>( TA_TYPE_ANIMATION_3D );
	Register<TinyFontManager>( TA_TYPE_FONT );
	Register<TinyShaderManager>( TA_TYPE_SHADER );
	Register<TinyMaterialManager>( TA_TYPE_MATERIAL );
	Register<TinyGeometryManager>( TA_TYPE_GEOMETRY );
	Register<TinyCueManager>( TA_TYPE_CUE );
	Register<TinySampleManager>( TA_TYPE_SANPLES );
	Register<TinyScriptManager>( TA_TYPE_SCRIPT );
	Register<TinyPrefabManager>( TA_TYPE_PREFAB );
	Register<TinySceneManager>( TA_TYPE_SCENE );
	Register<TinyLocalisationManager>( TA_TYPE_LOCALISATION );
	Register<TinyTrophyManager>( TA_TYPE_TROPHY );
}

bool TinyAssetManager::LoadConfig( TinyGame* game, TinyConfig*& game_config ) {
	auto& filesystem = game->GetFilesystem( );
	auto* container  = tiny_cast( GetContainer( TA_TYPE_CONFIG ), TinyConfigContainer* );
	auto state		 = false;

	if ( container )
		state = container->Load( filesystem, game_config );

	return state;
}

bool TinyAssetManager::LoadArchiveFile( TinyGame* game, const tiny_string& path ) {
	auto* container = tiny_cast( GetContainer( TA_TYPE_ARCHIVE ), TinyArchiveContainer* );
	auto state		= false;

	if ( container ) {
		auto asset_name = path.sub_string( 1 );

		state = container->Load( game, asset_name );
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

	if ( !path.get_is_empty( ) && filesystem.GetFileExist( path ) ) {
		auto file = filesystem.OpenFile( path, TF_ACCESS_READ );

		if ( file.GetIsValid( ) ) {
			auto header = TinyAssetHeader{ };

			file.Read( tiny_sizeof( header ), tiny_rvalue( header ) );

			if ( header.GetIsAsset( ) ) {
				auto* container = GetContainer( header.Type );

				if ( container ) {
					if ( !alias.get_is_empty( ) )
						state = container->Load( game, alias, file );
					else {
						auto file_info  = filesystem.GetInformation( path );
						auto asset_name = tiny_string{ file_info.Name };

						state = container->Load( game, asset_name, file );
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
TinyAssetImportManager& TinyAssetManager::GetImporter( ) { return m_importer; }

ITinyAssetContainer* TinyAssetManager::GetContainer( const tiny_uint asset_type ) {
	auto container = tiny_cast( nullptr, ITinyAssetContainer* );

	if ( asset_type < m_containers.size( ) )
		container = m_containers[ asset_type ].As<ITinyAssetContainer>( );

	return container;
}

const ITinyAssetContainer* TinyAssetManager::GetContainer( 
	const tiny_uint asset_type 
) const {
	auto container = tiny_cast( nullptr, const ITinyAssetContainer* );

	if ( asset_type < m_containers.size( ) )
		container = m_containers[ asset_type ].As<ITinyAssetContainer>( );

	return container;
}

TinyScriptManager& TinyAssetManager::GetScripts( ) { 
	auto* container = GetContainerAs<TinyScriptManager>( TA_TYPE_SCRIPT );

	return tiny_lvalue( container );
}

TinySceneManager& TinyAssetManager::GetScenes( ) {
	auto* container = GetContainerAs<TinySceneManager>( TA_TYPE_SCENE );

	return tiny_lvalue( container );
}

bool TinyAssetManager::GetExist( const TinyAssetHandle& handle ) const {
	return GetExist( handle.Type, handle.Hash );
}

bool TinyAssetManager::GetExist( const tiny_uint type, const tiny_hash asset_hash ) const {
	auto* container = GetContainer( type );
	auto state		= false;

	if ( container )
		state = container->Find( asset_hash );

	return state;
}

TinyAsset* TinyAssetManager::GetAsset( const TinyAssetHandle& handle ) {
	auto* container = GetContainer( handle.Type );
	auto* asset		= tiny_cast( nullptr, TinyAsset* );

	if ( container )
		asset = container->GetAsset( handle );

	return  asset;
}

const TinyAsset* TinyAssetManager::GetAsset( const TinyAssetHandle& handle ) const {
	auto* container = GetContainer( handle.Type );
	auto* asset		= tiny_cast( nullptr, const TinyAsset* );

	if ( container )
		asset = container->GetAsset( handle );

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
