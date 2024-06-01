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
	m_config{  }
{ }

bool TinyConfigContainer::Load( TinyFilesystem& filesystem, TinyConfig*& config ) {
	auto state = true;
	auto path  = filesystem.GetConfigPath( );

	if ( filesystem.GetFileExist( path ) ) {
		auto file = filesystem.OpenFile( path, TF_ACCESS_BINARY_READ );

		state = m_config.Load( filesystem, file );
	} else {
		auto file = filesystem.OpenFile( path, TF_ACCESS_BINARY_WRITE );

		m_config.Save( filesystem, file );
	}

	config = tiny_rvalue( m_config );

	return state;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyAsset* TinyConfigContainer::GetAsset( const tiny_hash asset_hash ) {
	return tiny_rvalue( m_config );
}

const TinyAsset* TinyConfigContainer::GetAsset( const tiny_hash asset_hash ) const {
	return tiny_rvalue( m_config );
}
