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

bool TinyLuaContext::Compile( native_string alias, native_string source ) {
	auto state = luaL_dostring( _lua_state, source ) == LUA_OK;

	if ( state ) {
		lua_setglobal( _lua_state, alias );
		lua_settop( _lua_state, 0 );
	}

	return state;
}

bool TinyLuaContext::Compile( const tiny_string& alias, const tiny_string& source ) {
	auto* alias_str  = alias.as_chars( );
	auto* source_str = source.as_chars( );

	return Compile( alias_str, source_str );
}

void TinyLuaContext::Register( const tiny_string& name, TinyLuaPrototype prototype ) {
	if ( name.is_valid( ) ) {
		auto* name_str = name.as_chars( );

		if ( prototype )
			lua_register( _lua_state, name_str, prototype );
		else {
			lua_pushnil( _lua_state );
			lua_setglobal( _lua_state, name_str );
		}
	}
}

void TinyLuaContext::UnRegister( const tiny_string& name ) { RemoveGlobal( name ); }

void TinyLuaContext::SetGlobal( const tiny_string& name, bool value ) {
	if ( name.is_valid( ) ) {
		auto name_str = name.as_chars( );

		lua_pushboolean( _lua_state, value );
		lua_setglobal( _lua_state, name_str );
	}
}

void TinyLuaContext::SetGlobal( const tiny_string& name, tiny_int value ) {
	if ( name.is_valid( ) ) {
		auto name_str = name.as_chars( );

		lua_pushinteger( _lua_state, value );
		lua_setglobal( _lua_state, name_str );
	}
}

void TinyLuaContext::SetGlobal( const tiny_string& name, tiny_uint value ) {
	if ( name.is_valid( ) ) {
		auto name_str = name.as_chars( );

		lua_pushinteger( _lua_state, value );
		lua_setglobal( _lua_state, name_str );
	}
}

void TinyLuaContext::SetGlobal( const tiny_string& name, tiny_long value ) {
	if ( name.is_valid( ) ) {
		auto name_str = name.as_chars( );

		lua_pushinteger( _lua_state, value );
		lua_setglobal( _lua_state, name_str );
	}
}

void TinyLuaContext::SetGlobal( const tiny_string& name, tiny_ulong value ) {
	if ( name.is_valid( ) ) {
		auto name_str = name.as_chars( );

		lua_pushinteger( _lua_state, value );
		lua_setglobal( _lua_state, name_str );
	}
}

void TinyLuaContext::SetGlobal( const tiny_string& name, float value ) {
	if ( name.is_valid( ) ) {
		auto name_str = name.as_chars( );

		lua_pushnumber( _lua_state, value );
		lua_setglobal( _lua_state, name_str );
	}
}

void TinyLuaContext::SetGlobal( const tiny_string& name, double value ) {
	if ( name.is_valid( ) ) {
		auto name_str = name.as_chars( );

		lua_pushnumber( _lua_state, value );
		lua_setglobal( _lua_state, name_str );
	}
}

void TinyLuaContext::SetGlobal( const tiny_string& name, const tiny_point& value ) {
	if ( name.is_valid( ) ) {
		auto name_str = name.as_chars( );

		TinyLua::Point::Create( tiny_self, value );

		lua_setglobal( _lua_state, name_str );
	}
}

void TinyLuaContext::SetGlobal( const tiny_string& name, const tiny_vec2& value ) {
	if ( name.is_valid( ) ) {
		auto name_str = name.as_chars( );

		TinyLua::Vec2::Create( tiny_self, value );

		lua_setglobal( _lua_state, name_str );
	}
}

void TinyLuaContext::SetGlobal( const tiny_string& name, const tiny_vec3& value ) {
	if ( name.is_valid( ) ) {
		auto name_str = name.as_chars( );

		TinyLua::Vec3::Create( tiny_self, value );

		lua_setglobal( _lua_state, name_str );
	}
}

void TinyLuaContext::SetGlobal( const tiny_string& name, const tiny_vec4& value ) {
	if ( name.is_valid( ) ) {
		auto name_str = name.as_chars( );

		TinyLua::Vec4::Create( tiny_self, value );

		lua_setglobal( _lua_state, name_str );
	}
}

void TinyLuaContext::SetGlobal( const tiny_string& name, const tiny_color& value ) {
	if ( name.is_valid( ) ) {
		auto name_str = name.as_chars( );

		TinyLua::Color::Create( tiny_self, value );

		lua_setglobal( _lua_state, name_str );
	}
}

void TinyLuaContext::RemoveGlobal( const tiny_string& name ) {
	if ( name.is_valid( ) ) {
		auto* name_str = name.as_chars( );

		lua_pushnil( _lua_state );
		lua_setglobal( _lua_state, name_str );
	}
}

#define _tlc_parameter_val( TYPE ) tiny_lvalue( tiny_cast( parameter.Value, TYPE* ) )
#define _tlc_parameter_get( TYPE, LUA )\
	_tlc_parameter_val( TYPE ) = tiny_cast( ##LUA##( _lua_state, TINY_LUA_TOP ), TYPE )

void TinyLuaContext::Push( const TinyLuaParameter& parameter ) {
	switch ( parameter.Type ) {
		case TL_TYPE_BOOL	  : lua_pushboolean( _lua_state, _tlc_parameter_val( bool ) );		 break;
		case TL_TYPE_INT	  : lua_pushinteger( _lua_state, _tlc_parameter_val( tiny_int ) );   break;
		case TL_TYPE_UINT	  : lua_pushinteger( _lua_state, _tlc_parameter_val( tiny_uint ) );  break;
		case TL_TYPE_LONG	  : lua_pushinteger( _lua_state, _tlc_parameter_val( tiny_long ) );  break;
		case TL_TYPE_ULONG	  : lua_pushinteger( _lua_state, _tlc_parameter_val( tiny_ulong ) ); break;
		case TL_TYPE_FLOAT	  : lua_pushnumber( _lua_state, _tlc_parameter_val( float ) );		 break;
		case TL_TYPE_DOUBLE   : lua_pushnumber( _lua_state, _tlc_parameter_val( double ) );		 break;
		case TL_TYPE_USERDATA : lua_pushlightuserdata( _lua_state, parameter.Value );			 break;

		default : break;
	}
}

bool TinyLuaContext::Pop( TinyLuaParameter& parameter ) {
	auto state = false;

	switch ( parameter.Type ) {
		case TL_TYPE_BOOL:
			state = lua_isboolean( _lua_state, TINY_LUA_TOP );

			if ( state )
				_tlc_parameter_get( bool, lua_toboolean );

			break;

		case TL_TYPE_INT : 
			state = lua_isinteger( _lua_state, TINY_LUA_TOP );

			if ( state )
				_tlc_parameter_get( tiny_int, lua_tointeger );

			break;

		case TL_TYPE_UINT:
			state = lua_isinteger( _lua_state, TINY_LUA_TOP );

			if ( state )
				_tlc_parameter_get( tiny_uint, lua_tointeger );

			break;

		case TL_TYPE_LONG :
			state = lua_isinteger( _lua_state, TINY_LUA_TOP );

			if ( state )
				_tlc_parameter_get( tiny_long, lua_tointeger );

			break;

		case TL_TYPE_ULONG :
			state = lua_isinteger( _lua_state, TINY_LUA_TOP );

			if ( state )
				_tlc_parameter_get( tiny_ulong, lua_tointeger );

			break;

		case TL_TYPE_FLOAT :
			state = lua_isnumber( _lua_state, TINY_LUA_TOP );

			if ( state )
				_tlc_parameter_get( float, lua_tointeger );

			break;

		case TL_TYPE_DOUBLE :
			state = lua_isnumber( _lua_state, TINY_LUA_TOP );

			if ( state )
				_tlc_parameter_get( double, lua_tointeger );

			break;

		case TL_TYPE_USERDATA :
			state = lua_isnumber( _lua_state, TINY_LUA_TOP );

			if ( state )
				parameter.Value = lua_touserdata( _lua_state, TINY_LUA_TOP );

			break;

		default : break;
	}

	return state;
}

bool TinyLuaContext::Execute( native_string source ) {
	return source && luaL_dostring( _lua_state, source ) == LUA_OK;
}

bool TinyLuaContext::Execute( const tiny_string& source ) {
	auto state = source.is_valid( );

	if ( state ) {
		auto* source_str = source.as_chars( );

		state = Execute( source_str );
	}

	return state;
}

void TinyLuaContext::Terminate( ) {
	if ( _lua_state )
		lua_close( _lua_state );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyLuaContext::GetExist( const tiny_string& name ) const {
	auto* name_str = name.as_chars( );

	return lua_getglobal( _lua_state, name_str ) == LUA_OK;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	OPERATOR ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyLuaContext::operator lua_State* ( ) { return _lua_state; };
