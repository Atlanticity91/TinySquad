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
 * @creation : 17/12/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "TinyScript_Interop.h"

te_class TinyScriptSystem : tiny_inherit( TinySystem<TinyScript> ) {

public:
	TinyScriptSystem( );

	~TinyScriptSystem( ) = default;

	tiny_implement( void RegisterInterop( TinyGame* game ) );

protected:
	tiny_implement( void PreTick( TinyGame* game, TinyEngine& engine ) );

	tiny_implement( void PostTick( TinyGame* game, TinyEngine& engine ) );

};
