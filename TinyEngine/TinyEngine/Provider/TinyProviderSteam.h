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

#include "TinyProvider.h"

#ifdef TE_PROVIDER_STEAM

te_class TinyProviderSteam : tiny_inherit( TinyProvider ) {

public:
	TinyProviderSteam( );

	~TinyProviderSteam( ) = default;

	tiny_implement( bool Initialize( TinyFilesystem& filesystem ) );

	tiny_implement( bool UnLock( const tiny_hash trophy_hash ) );

	tiny_implement( void Terminate( TinyFilesystem& filesystem ) );

};

#endif
