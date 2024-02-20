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
 * @creation : 14/01/2024
 * @version  : 2024.2
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#include <TinyEngine/__tiny_engine_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
tiny_int TinyLua::Component::Create( lua_State* context, const tiny_string& name ) {
	auto* game = tli_get_game( tli_param_one );

	if ( game && lua_istable( context, tli_param_two ) ) {
		auto* name_str = name.as_chars( );
		auto hash	   = Component::GetHash( context, tli_param_two );

		game->GetECS( ).Append( game, hash, name_str );
	} else
		lua_pushnil( context );

	return 1;
}

tiny_hash TinyLua::Component::GetHash( lua_State* context, tiny_int param_id ) {
	auto hash = lua_Integer{ };

	tli_get_field( param_id, "hash", hash );

	return tiny_hash{ tiny_cast( hash, tiny_uint ) };
}

tiny_int TinyLua::Component::ToString( lua_State* context, const tiny_string& name ) {
	auto* name_str = name.as_chars( );
	auto* comp	   = Get<TinyComponent>( context, tli_self );
	auto owner	   = tiny_cast( 0, tiny_uint );

	if ( comp )
		owner = comp->GetOwner( );

	lua_pushfstring( context, "%s:%u", name_str, owner );

	return 1;
}
