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
	: TinySystem{ true, true }
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
void TinyScriptSystem::PreTick( TinyGame* game ) { 
	auto& natives = game->GetNatives( );
	auto& lua	  = game->GetScripts( );

	for ( auto& comp : m_components ) {
		if ( comp.GetHasPreTick( ) ) {
			auto* pre_comp = tiny_rvalue( comp );
			auto& pre_tick = comp.GetPreTick( );

			switch ( pre_tick.Type ) {
				case TS_TYPE_NATIVE : natives._nExecute( pre_tick.Function, game, pre_comp ); break;
				case TS_TYPE_LUA	: lua.Execute( game, { pre_tick.Asset, pre_tick.Function, pre_comp } ); break;

				default : break;
			}
		}
	}
}

void TinyScriptSystem::PostTick( TinyGame* game ) {
	auto& natives = game->GetNatives( );
	auto& lua	  = game->GetScripts( );

	for ( auto& comp : m_components ) {
		if ( comp.GetHasPostTick( ) ) {
			auto* post_comp = tiny_rvalue( comp );
			auto& post_tick = comp.GetPostTick( );

			switch ( post_tick.Type ) {
				case TS_TYPE_NATIVE : natives._nExecute( post_tick.Function, game, post_comp ); break;
				case TS_TYPE_LUA	: lua.Execute( game, { post_tick.Asset, post_tick.Function, post_comp } ); break;

				default : break;
			}
		}
	}
}
