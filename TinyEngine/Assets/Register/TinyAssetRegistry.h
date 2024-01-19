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

#pragma once

#include "TinyAssetMetadata.h"

te_class TinyAssetRegistry final {

private:
	tiny_map<TinyAssetMetadata> _metadatas;

public:
	TinyAssetRegistry( );

	~TinyAssetRegistry( ) = default;

	tiny_uint Append( const tiny_string& name, const TinyAssetMetadata& metadata );

	void Remove( const tiny_hash asset_hash );

	void Remove( const tiny_string& name );

	bool Load( TinyFilesystem& filesystem );

	bool Load( TinyFilesystem& filesystem, const tiny_string& path );

	void Save( TinyFilesystem& filesystem, const tiny_string& path );

public:
	bool GetExist( const tiny_string& asset ) const;
	
	bool GetExist( const tiny_hash asset_hash ) const;

	bool FindMetadata( const tiny_hash asset_hash, tiny_uint& metadata_id );

	tiny_map<TinyAssetMetadata>& GetMetadatas( );

	tiny_list<tiny_string> GetAssets( TinyAssetTypes type ) const;

public:
	TinyAssetMetadata& operator[]( tiny_uint metadata_id );

};
