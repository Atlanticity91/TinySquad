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
#	ifdef TE_PROVIDER_IMP
	: _provider{ }
#	endif
{ }

bool TinyProviderManager::Initialize( TinyFilesystem& filesystem ) {
	auto state = true;

#	ifdef TE_PROVIDER_IMP
	state = _provider.Initialize( filesystem );
#	endif

	return state;
}

void TinyProviderManager::Terminate( TinyFilesystem& filesystem ) {
#	if TE_PROVIDER_IMP
	_provider.Terminate( filesystem );
#	endif
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
#ifdef TE_PROVIDER_IMP
##TE_PROVIDER_TYPE##& TinyProviderManager::GetProvider( ) { return _provider; }

const ##TE_PROVIDER_TYPE##& TinyProviderManager::GetProvider( ) const { return _provider; }
#endif
