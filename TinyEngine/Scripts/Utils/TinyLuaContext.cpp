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

bool TinyLuaContext::Compile( c_str source ) {
	return luaL_loadstring( _lua_state, source ) == LUA_OK;
}

bool TinyLuaContext::Compile( const tiny_string& source ) {
	auto* chars = source.as_chars( );

	return Compile( chars );
}

void TinyLuaContext::SetGlobal( const tiny_string& name, c_ptr value ) {
	if ( value ) {
		auto name_str = name.as_chars( );

		lua_pushlightuserdata( _lua_state, value );
		lua_setglobal( _lua_state, name_str );
	}
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

bool TinyLuaContext::Execute( TinyGame* game, TinyLuaExecution& execution ) {
	auto* name = execution.Function.as_chars( );
	auto state = lua_getglobal( _lua_state, name ) == LUA_OK;

	if ( state && lua_isfunction( _lua_state, TINY_LUA_TOP ) ) {
		SetGlobal( "game", tiny_cast( game, c_ptr ) );

		state = lua_pcall( _lua_state, execution.Inputs.size( ), execution.Outputs.size( ), 0 ) == LUA_OK;

		if ( state ) {
			state = tiny_cast( lua_toboolean( _lua_state, TINY_LUA_TOP ), bool );
		}
	}

	return state;
}

bool TinyLuaContext::Execute( TinyGame* game, const tiny_string& function ) {
	auto execution = TinyLuaExecution{ function };

	return Execute( game, execution );
}

void TinyLuaContext::Terminate( ) {
	if ( _lua_state )
		lua_close( _lua_state );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	OPERATOR ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyLuaContext::operator lua_State* ( ) { return _lua_state; };
