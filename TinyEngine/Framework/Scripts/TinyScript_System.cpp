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

#include <TinyEngine/__tiny_engine_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyScriptSystem::TinyScriptSystem( ) 
	: TinySystem{ }
{ }

void TinyScriptSystem::RegisterInterop( TinyGame* game ) {
	tli_make_lua_context( context );

	tli_create( TINY_SCRIPT_NAME );

	tli_createfn( "create", nullptr );
	tli_createfn( "destroy", nullptr );
	tli_createfn( "set_pretick", nullptr );
	tli_createfn( "set_posttick", nullptr );
	tli_createfn( "get_pretick", nullptr );
	tli_createfn( "get_posttick", nullptr );
	tli_createfn( "to_string", nullptr );

	if ( tli_createmeta( TINY_SCRIPT_NAME ) )
		tli_createop( "__tostring", nullptr );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PROTECTED ===
////////////////////////////////////////////////////////////////////////////////////////////
void TinyScriptSystem::PreTick( TinyGame* game, TinyEngine& engine ) { 
}

void TinyScriptSystem::PostTick( TinyGame* game, TinyEngine& engine ) {
}
