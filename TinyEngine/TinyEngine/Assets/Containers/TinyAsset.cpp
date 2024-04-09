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

#include <TinyEngine/__tiny_engine_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyAsset::TinyAsset( TinyAssetTypes type )
	: TinyAsset{ tiny_cast( type, tiny_uint ) }
{ }

TinyAsset::TinyAsset( tiny_uint type )
	: _type{ type },
	_reference{ }
{ }

bool TinyAsset::Acquire( TinyGame* game ) {
	_reference += 1;

	return OnAcquire( game );
}

bool TinyAsset::Release( TinyGame* game ) {
	_reference -= 1;

	return _reference == 0 && OnRelease( game );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
tiny_uint TinyAsset::GetType( ) const { return _type; }

tiny_uint TinyAsset::GetReference( ) const { return _reference; }
