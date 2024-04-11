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
 * @creation : 06/04/2024
 * @version  : 2024.2.7
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "TinyAsset.h"

te_interface ITinyAssetContainer {

	tiny_abstract( bool Create( 
		TinyGame* game,
		const tiny_string& alias, 
		const c_pointer builder 
	) );

	tiny_abstract( bool Load(
		TinyGame* game,
		const tiny_string& alias,
		TinyFile& file
	) );

	tiny_abstract( void UnLoad( TinyGame* game, const tiny_hash asset_hash ) );

	tiny_abstract( void Acquire( TinyGame* game, const tiny_hash asset_hash ) );

	tiny_abstract( void Release( TinyGame* game, const tiny_hash asset_hash ) );

	tiny_abstract( void Terminate( TinyGame* game ) );

	tiny_abstract( void GetAssetList( tiny_list<tiny_string>& list ) const );

	tiny_abstract( bool Find( const tiny_hash asset_hash ) const );

	tiny_abstract( TinyAsset* GetAsset( const tiny_hash asset_hash ) );

	tiny_abstract( const TinyAsset* GetAsset( const tiny_hash asset_hash ) const );

};
