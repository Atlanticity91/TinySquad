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
 * @creation : 13/11/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "TinyAsset.h"

te_abstract_class ITinyAssetList {

private:
	TinyAssetTypes _type;

public:
	ITinyAssetList( TinyAssetTypes type );

	virtual ~ITinyAssetList( ) = default;

	tiny_abstract( tiny_uint Load(
		TinyGame* game,
		TinyFilesystem& filesystem,
		TinyAssetManager& assets,
		TinyAssetMetadata& metadata
	) );

	tiny_abstract( void Unload(
		TinyGame* game,
		TinyAssetManager& assets,
		TinyAssetMetadata& metadata
	) );

	tiny_abstract( bool ReLoad(
		TinyGame* game,
		TinyFilesystem& filesystem,
		TinyAssetManager& assets,
		TinyAssetMetadata& metadata
	) );

	tiny_abstract( tiny_uint Create( 
		TinyGame* game,
		TinyAssetMetadata& metadata, 
		c_pointer asset_builder
	) );

	tiny_abstract( bool ReCreate(
		TinyGame* game,
		TinyAssetMetadata& metadata,
		c_pointer asset_builder
	) );

	tiny_abstract( void Clear( TinyGame* game ) );

	tiny_abstract( void Terminate( TinyGame* game ) );

public:
	TinyAssetTypes GetType( ) const;

	tiny_abstract( bool GetIsValid( tiny_uint handle ) const );

	tiny_abstract( c_pointer GetAsset( const TinyAsset& asset ) );

	tiny_abstract( const c_pointer GetAsset( const TinyAsset& asset ) const );

};
