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
 * @creation : 10/01/2024
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
TinyLuaContext::TinyLuaContext( )
	: _lua_state{ nullptr } 
{ }

bool TinyLuaContext::Create( ) {
	_lua_state = luaL_newstate( );

	if ( _lua_state )
		luaL_openlibs( _lua_state );

	return _lua_state;
}

bool TinyLuaContext::Compile( c_string source ) {
	return luaL_dostring( _lua_state, source ) == LUA_OK;
}

bool TinyLuaContext::Compile( const tiny_string& source ) {
	auto* chars = source.as_chars( );
	auto length = source.length( );

	return luaL_loadbuffer( _lua_state, chars, length, NULL );
}

void TinyLuaContext::SetGlobal( const tiny_string& name, bool value ) {
	auto name_str = name.as_chars( );

	lua_pushboolean( _lua_state, value );
	lua_setglobal( _lua_state, name_str );
}

void TinyLuaContext::SetGlobal( const tiny_string& name, tiny_int value ) {
	auto name_str = name.as_chars( );

	lua_pushinteger( _lua_state, value );
	lua_setglobal( _lua_state, name_str );
}

void TinyLuaContext::SetGlobal( const tiny_string& name, tiny_uint value ) {
	auto name_str = name.as_chars( );

	lua_pushinteger( _lua_state, value );
	lua_setglobal( _lua_state, name_str );
}

void TinyLuaContext::SetGlobal( const tiny_string& name, tiny_long value ) {
	auto name_str = name.as_chars( );

	lua_pushinteger( _lua_state, value );
	lua_setglobal( _lua_state, name_str );
}

void TinyLuaContext::SetGlobal( const tiny_string& name, tiny_ulong value ) {
	auto name_str = name.as_chars( );

	lua_pushinteger( _lua_state, value );
	lua_setglobal( _lua_state, name_str );
}

void TinyLuaContext::SetGlobal( const tiny_string& name, float value ) {
	auto name_str = name.as_chars( );

	lua_pushnumber( _lua_state, value );
	lua_setglobal( _lua_state, name_str );
}

void TinyLuaContext::SetGlobal( const tiny_string& name, double value ) {
	auto name_str = name.as_chars( );

	lua_pushnumber( _lua_state, value );
	lua_setglobal( _lua_state, name_str );
}

void TinyLuaContext::SetGlobal( const tiny_string& name, const tiny_point& value ) {
	auto name_str = name.as_chars( );

	TinyLua::Point::Create( tiny_self, value );

	lua_setglobal( _lua_state, name_str );
}

void TinyLuaContext::SetGlobal( const tiny_string& name, const tiny_vec2& value ) {
	auto name_str = name.as_chars( );

	TinyLua::Vec2::Create( tiny_self, value );

	lua_setglobal( _lua_state, name_str );
}

void TinyLuaContext::SetGlobal( const tiny_string& name, const tiny_vec3& value ) {
	auto name_str = name.as_chars( );

	TinyLua::Vec3::Create( tiny_self, value );

	lua_setglobal( _lua_state, name_str );
}

void TinyLuaContext::SetGlobal( const tiny_string& name, const tiny_vec4& value ) {
	auto name_str = name.as_chars( );

	TinyLua::Vec4::Create( tiny_self, value );

	lua_setglobal( _lua_state, name_str );
}

void TinyLuaContext::SetGlobal( const tiny_string& name, const tiny_color& value ) {
	auto name_str = name.as_chars( );

	TinyLua::Color::Create( tiny_self, value );

	lua_setglobal( _lua_state, name_str );
}

void TinyLuaContext::SetGlobal( const tiny_string& name, TinyLuaPrototype function ) {
	if ( function ) {
		auto name_str = name.as_chars( );

		lua_pushcfunction( _lua_state, function );
		lua_setglobal( _lua_state, name_str );
	}
}

void TinyLuaContext::Execute( const TinyLuaExecution& execution ) {
	if ( GetExist( execution.Function ) ) {
		PushInputs( execution.Inputs );

		if ( lua_pcall( _lua_state, execution.Inputs.size( ), execution.Outputs.size( ), 0 ) == LUA_OK )
			PushOutputs( execution.Outputs );
	}
}

void TinyLuaContext::Terminate( ) {
	if ( _lua_state )
		lua_close( _lua_state );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE ===
////////////////////////////////////////////////////////////////////////////////////////////
void TinyLuaContext::PushInputs( const tiny_list<TinyLuaParameter>& inputs ) { 
}

void TinyLuaContext::PushOutputs( const tiny_list<TinyLuaParameter>& outputs ) {
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyLuaContext::GetExist( const tiny_string& function ) const { 
	auto* name_str = function.as_chars( );

	return  lua_getglobal( _lua_state, name_str ) == LUA_OK &&
			lua_isfunction( _lua_state, TINY_LUA_TOP ) == LUA_OK;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	OPERATOR ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyLuaContext::operator lua_State* ( ) { return _lua_state; };
