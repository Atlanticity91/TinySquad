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
	: m_type{ type },
	m_reference{ }
{ }

bool TinyAsset::Acquire( TinyGame* game ) {
	m_reference += 1;

	return OnAcquire( game );
}

bool TinyAsset::Release( TinyGame* game ) {
	m_reference -= 1;

	return m_reference == 0 && OnRelease( game );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
tiny_uint TinyAsset::GetType( ) const { return m_type; }

tiny_uint TinyAsset::GetReference( ) const { return m_reference; }
