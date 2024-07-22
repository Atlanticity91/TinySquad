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
 * @creation : 04/04/2024
 * @version  : 2024.2.7
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "TinyConfig.h"

te_class TinyConfigContainer final : tiny_inherit( ITinyAssetContainer ) {

private:
	TinyConfig m_config;

public:
	TinyConfigContainer( );

	~TinyConfigContainer( ) = default;

	bool Load( TinyFilesystem& filesystem, TinyConfig*& config );

	tiny_no_implementv( false, bool Create( 
		TinyGame* game, 
		const tiny_string& alias, 
		const native_pointer builder 
	) );

	tiny_no_implementv( false, bool Load(
		TinyGame* game,
		const tiny_string& alias,
		TinyFile& file
	) );

	tiny_no_implement( void UnLoad( TinyGame* game, const tiny_hash asset_hash ) );

	tiny_no_implement( void Acquire( TinyGame* game, const tiny_hash asset_hash ) );

	tiny_no_implement( void Release( TinyGame* game, const tiny_hash asset_hash ) );

	tiny_no_implement( void Terminate( TinyGame* game ) );

private:
	void GenerateConfig( );

public:
	tiny_no_implement( void GetAssetList( tiny_list<tiny_string>&list ) const );

	tiny_no_implementv( false, bool Find( const tiny_hash asset_hash ) const );

	tiny_implement( TinyAsset* GetAsset( const tiny_hash asset_hash ) );

	tiny_implement( const TinyAsset* GetAsset( const tiny_hash asset_hash ) const );

};
