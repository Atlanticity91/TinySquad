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

#include "TinyProviderEpic.h"

#ifdef TE_PROVIDER_STEAM
#	define TE_PROVIDER_IMP
#	define TE_PROVIDER_TYPE TinyProviderSteam
#elif defined TE_PROVIDER_EPIC 
#	define TE_PROVIDER_IMP
#	define TE_PROVIDER_TYPE TinyProviderEpic
#endif

te_class TinyProviderManager final : tiny_inherit( TinyProvider ) {

#	ifdef TE_PROVIDER_IMP
	TE_PROVIDER_TYPE _provider;
#	endif

public:
	TinyProviderManager( );

	~TinyProviderManager( ) = default;

	tiny_implement( bool Initialize( TinyFilesystem& filesystem ) );

	tiny_implement( void Terminate( TinyFilesystem& filesystem ) );

public:
#	ifdef TE_PROVIDER_IMP
	##TE_PROVIDER_TYPE##& GetProvider( );

	const ##TE_PROVIDER_TYPE##& GetProvider( ) const;
#	endif

};
