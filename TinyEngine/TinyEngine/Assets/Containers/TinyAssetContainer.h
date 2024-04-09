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

#include "ITinyAssetContainer.h"

template<typename Asset>
	requires tiny_is_child_of( Asset, TinyAsset )
class TinyAssetContainer : tiny_inherit( ITinyAssetContainer ) {

private:
	tiny_map<Asset> _assets;

public:
	TinyAssetContainer( ) 
		: _assets{ } 
	{ };

	virtual ~TinyAssetContainer( ) = default;

	tiny_implement( bool Create( TinyGame* game, const c_pointer builder ) ) { 
		return false;
	};

	tiny_implement( bool Load(
		TinyGame* game,
		const tiny_string& alias,
		TinyFile& file
	) ) { 
		return false;
	};

	tiny_implement( void UnLoad( TinyGame* game, const tiny_hash asset_hash ) ) { 
	};

	tiny_implement( void Acquire( TinyGame* game, const tiny_hash asset_hash ) ) { 
	};

	tiny_implement( void Release( TinyGame* game, const tiny_hash asset_hash ) ) { 
	};

	tiny_implement( void Terminate( TinyGame* game ) ) { 
	};

public:
	tiny_implement( void GetAssetList( tiny_list<tiny_string>& list ) const ) { 
	};

	tiny_implement( bool Find( const tiny_hash asset_hash ) const ) { 
		return false;
	};

	tiny_implement( const TinyAsset* GetAsset( const tiny_hash asset_hash ) const ) {
		return nullptr;
	};

};
