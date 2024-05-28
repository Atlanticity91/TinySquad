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
 * @creation : 11/01/2024
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
tiny_int TinyLua::CreateTable( TinyLuaContext& context, const tiny_string& name ) {
	lua_newtable( context );

	auto name_str = name.as_chars( );
	auto table_id = lua_gettop( context );

	lua_pushvalue( context, table_id );
	lua_setglobal( context, name_str );

	return table_id;
}

void TinyLua::CreateFunction(
	TinyLuaContext& context,
	const tiny_string& name,
	TinyLuaPrototype callback
) {
	if ( callback ) {
		auto name_str = name.as_chars( );

		lua_pushcfunction( context, callback );
		lua_setfield( context, -2, name_str );
	}
}

bool TinyLua::CreateMetatable(
	TinyLuaContext& context,
	const tiny_string& name,
	tiny_int table_id
) {
	auto state = lua_istable( context, table_id );

	if ( state ) {
		auto name_str = name.as_chars( );

		luaL_newmetatable( context, name_str );
		lua_pushstring( context, "__index" );
		lua_pushvalue( context, table_id );
		lua_settable( context, -3 );
	}

	return state;
}

void TinyLua::CreateOperator(
	TinyLuaContext& context,
	const tiny_string& name,
	TinyLuaPrototype callback
) {
	if ( callback ) {
		auto name_str = name.as_chars( );

		lua_pushstring( context, name_str );
		lua_pushcfunction( context, callback );
		lua_settable( context, -3 );
	}
}

void TinyLua::CreateField(
	lua_State* context,
	const tiny_string& name,
	const tiny_string& value
) {
	auto value_str = value.as_chars( );
	auto name_str = name.as_chars( );

	lua_pushstring( context, name_str );
	lua_pushstring( context, name_str );
	lua_settable( context, -3 );
}

void TinyLua::CreateField(
	lua_State* context,
	const tiny_string& name,
	const lua_Integer& value
) {
	auto name_str = name.as_chars( );

	lua_pushstring( context, name_str );
	lua_pushinteger( context, value );
	lua_settable( context, -3 );
}

void TinyLua::CreateField(
	lua_State* context,
	const tiny_string& name,
	const lua_Number& value
) {
	auto name_str = name.as_chars( );

	lua_pushstring( context, name_str );
	lua_pushnumber( context, value );
	lua_settable( context, -3 );
}

void TinyLua::CreateField(
	lua_State* context,
	const tiny_string& name,
	native_pointer& value
) {
	if ( value ) {
		auto name_str = name.as_chars( );
		
		lua_pushstring( context, name_str );
		lua_pushlightuserdata( context, value );
		lua_settable( context, -3 );
	}
}

void TinyLua::LinkMetatable( lua_State* context, const tiny_string& name ) {
	auto name_str = name.as_chars( );

	luaL_getmetatable( context, name_str );
	lua_setmetatable( context, -2 );
}

bool TinyLua::GetField(
	lua_State* context,
	tiny_int table_id,
	const tiny_string& name,
	lua_Integer& value
) {
	auto name_str = name.as_chars( );

	lua_pushstring( context, name_str );
	lua_gettable( context, table_id );

	auto state = lua_isinteger( context, tli_stack_top );

	if ( state )
		value = lua_tointeger( context, tli_stack_top );

	return state;
}

bool TinyLua::GetField(
	lua_State* context,
	tiny_int table_id,
	const tiny_string& name,
	lua_Number& value
) {
	auto name_str = name.as_chars( );

	lua_pushstring( context, name_str );
	lua_gettable( context, table_id );

	auto state = lua_isnumber( context, tli_stack_top );

	if ( state )
		value = lua_tonumber( context, tli_stack_top );

	return state;
}

bool TinyLua::GetField(
	lua_State* context,
	tiny_int table_id,
	const tiny_string& name,
	native_pointer& value
) {
	auto name_str = name.as_chars( );

	lua_pushstring( context, name_str );
	lua_gettable( context, table_id );

	auto state = lua_isuserdata( context, tli_stack_top );

	if ( state )
		value = lua_touserdata( context, tli_stack_top );

	return state;
}

void TinyLua::SetField(
	lua_State* context,
	const tiny_string& name,
	const lua_Integer& value
) { 
	auto name_str = name.as_chars( );

	lua_pushinteger( context, value );
	lua_setfield( context, tli_self, name_str );
}

void TinyLua::SetField(
	lua_State* context,
	const tiny_string& name,
	const lua_Number& value
) {
	auto name_str = name.as_chars( );

	lua_pushnumber( context, value );
	lua_setfield( context, tli_self, name_str );
}
