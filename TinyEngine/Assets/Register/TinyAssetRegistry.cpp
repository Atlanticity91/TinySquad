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
 * @creation : 08/11/2023
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
TinyAssetRegistry::TinyAssetRegistry( )
	: _metadatas{ }
{ }

tiny_uint TinyAssetRegistry::Append(
	const tiny_string& name, 
	const TinyAssetMetadata& metadata 
) {
	auto metadata_id = tiny_cast( 0, tiny_uint );

	if ( !_metadatas.find( name ) )
		_metadatas.emplace( name, metadata );

	_metadatas.find( name, metadata_id );

	return metadata_id;
}

void TinyAssetRegistry::Remove( const tiny_hash asset_hash ) {
	_metadatas.erase( asset_hash );
}

void TinyAssetRegistry::Remove( const tiny_string& name ) {
	_metadatas.erase( name );
}

bool TinyAssetRegistry::Load( TinyFilesystem& filesystem ) {
#	ifdef TE_DEV
	auto dev_path = std::string{ filesystem.GetGameDir( ).as_chars( ) } + "Dev\\Dev.tinyregistry";

	return Load( filesystem, { dev_path } );
#	endif

	return false;
}

bool TinyAssetRegistry::Load( TinyFilesystem& filesystem, const tiny_string& path ) {
	_metadatas.clear( );

	try {
		auto node	  = YAML::LoadFile( path.get( ) );
		auto rootNode = node[ "Registry" ];

		if ( !rootNode )
			return false;

		auto asset = TinyAssetMetadata{ };

		for ( const auto& node : rootNode ) {
			auto name = node[ "Name" ].as<std::string>( );

			asset.Reference = 0;
			asset.Type	    = tiny_cast( node[ "Type" ].as<tiny_uint>( ), TinyAssetTypes );
			asset.Handle    = TINY_UINT_MAX;
			asset.Source	= node[ "Source" ].as<std::string>( );
			asset.Target	= node[ "Target" ].as<std::string>( );

			_metadatas.emplace( name.c_str( ), asset );
		}
	} catch ( YAML::ParserException e ) {
		return false;
	}

	return true;
}

void TinyAssetRegistry::Save( TinyFilesystem& filesystem, const tiny_string& path ) {
	YAML::Emitter emitter{ };

	emitter << YAML::BeginMap << YAML::Key << "Registry" << YAML::Value << YAML::BeginSeq;

	for ( auto& metadata : _metadatas ) {
		if ( metadata.Data.Target == "" )
			continue;

		emitter << YAML::BeginMap;
		emitter << YAML::Key << "Name"   << YAML::Value << metadata.String;
		emitter << YAML::Key << "Type"   << YAML::Value << tiny_cast( metadata.Data.Type, tiny_uint );
		emitter << YAML::Key << "Source" << YAML::Value << metadata.Data.Source;
		emitter << YAML::Key << "Target" << YAML::Value << metadata.Data.Target;
		emitter << YAML::EndMap;
	}

	emitter << YAML::EndSeq << YAML::EndMap;

	filesystem.Dump( path, emitter.c_str( ) );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyAssetRegistry::GetExist( const tiny_string& asset ) const {
	return _metadatas.find( asset );
}

bool TinyAssetRegistry::GetExist( const tiny_hash asset_hash ) const {
	return _metadatas.find( asset_hash );
}

bool TinyAssetRegistry::FindMetadata( const tiny_hash asset_hash, tiny_uint& metadata_id ) {
	return _metadatas.find( asset_hash, metadata_id );
}

tiny_map<TinyAssetMetadata>& TinyAssetRegistry::GetMetadatas( ) { 
	return _metadatas;
}

tiny_list<tiny_string> TinyAssetRegistry::GetAssets( tiny_uint type ) const {
	auto assets = tiny_list<tiny_string>{ };

	for ( auto& metadata : _metadatas ) {
		if ( metadata.Data.Type != type )
			continue;

		assets.emplace_back( metadata.String.c_str( ) );
	}

	return assets;
}

tiny_list<TinyAssetRegistry::MetaNode*> TinyAssetRegistry::GetMetadatas( tiny_uint type ) {
	auto metadatas = tiny_list<TinyAssetRegistry::MetaNode*>{ };

	for ( auto& metadata : _metadatas ) {
		if ( metadata.Data.Type != type )
			continue;

		metadatas.emplace_back( tiny_rvalue( metadata ) );
	}

	return metadatas;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		=== OPERATOR ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyAssetMetadata& TinyAssetRegistry::operator[]( tiny_uint metadata_id ) {
	return _metadatas[ metadata_id ];
}
