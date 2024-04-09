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
 * @creation : 09/04/2024
 * @version  : 2024.2.7
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#include <TinyEngine/__tiny_engine_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyConfigContainer::TinyConfigContainer( )
	: ITinyAssetContainer{ },
	_config{  }
{ }

bool TinyConfigContainer::Load( TinyFilesystem& filesystem, TinyConfig*& config ) {
	auto state = true;
	auto path  = filesystem.GetConfigPath( );

	if ( filesystem.GetFileExist( path ) ) {
		auto file = filesystem.OpenFile( path, Tiny::FileAccesses::TF_ACCESS_READ );

		state = _config.Load( file );
	} else {
		auto file = filesystem.OpenFile( path, Tiny::FileAccesses::TF_ACCESS_WRITE );

		_config.Save( file );
	}

	config = tiny_rvalue( _config );

	return state;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
const TinyAsset* TinyConfigContainer::GetAsset( const tiny_hash asset_hash ) const {
	return tiny_cast( tiny_rvalue( _config ), const TinyAsset* );
}
