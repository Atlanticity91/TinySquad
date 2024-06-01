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

#include <TinyEngine/__tiny_engine_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyProviderManager::TinyProviderManager( ) 
#	ifdef TEm_provider_IMP
	: m_provider{ }
#	endif
{ }

bool TinyProviderManager::Initialize( TinyFilesystem& filesystem ) {
	auto state = true;

#	ifdef TEm_provider_IMP
	state = m_provider.Initialize( filesystem );
#	endif

	return state;
}

bool TinyProviderManager::UnLock( const tiny_string& trophy_name ) {
	auto hash = tiny_hash{ trophy_name };

	return UnLock( hash );
}

bool TinyProviderManager::UnLock( const tiny_hash trophy_hash ) {
	return false;
}

void TinyProviderManager::Terminate( TinyFilesystem& filesystem ) {
#	if TEm_provider_IMP
	m_provider.Terminate( filesystem );
#	endif
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
#ifdef TEm_provider_IMP
##TEm_provider_TYPE##& TinyProviderManager::GetProvider( ) { return m_provider; }

const ##TEm_provider_TYPE##& TinyProviderManager::GetProvider( ) const { return m_provider; }
#endif
