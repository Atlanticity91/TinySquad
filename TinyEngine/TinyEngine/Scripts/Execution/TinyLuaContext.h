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

#pragma once

#include "TinyLuaParameter.h"

#define TINY_LUA_TOP -1

typedef lua_CFunction TinyLuaPrototype;

te_class TinyLuaContext final {

private:
	lua_State* _lua_state;

public:
	TinyLuaContext( );

	~TinyLuaContext( ) = default;

	bool Create( );

	bool Compile( native_string alias, native_string source );

	tiny_inline bool Compile( const tiny_string& alias, const tiny_string& source );

	void Register( const tiny_string& name, TinyLuaPrototype prototype );

	tiny_inline void UnRegister( const tiny_string& name );

	void SetGlobal( const tiny_string& name, bool value );

	void SetGlobal( const tiny_string& name, tiny_int value );
	
	void SetGlobal( const tiny_string& name, tiny_uint value );
	
	void SetGlobal( const tiny_string& name, tiny_long value );
	
	void SetGlobal( const tiny_string& name, tiny_ulong value );
	
	void SetGlobal( const tiny_string& name, float value );
	
	void SetGlobal( const tiny_string& name, double value );
	
	void SetGlobal( const tiny_string& name, const tiny_point& value );
	
	void SetGlobal( const tiny_string& name, const tiny_vec2& value );
	
	void SetGlobal( const tiny_string& name, const tiny_vec3& value );
	
	void SetGlobal( const tiny_string& name, const tiny_vec4& value );
	
	void SetGlobal( const tiny_string& name, const tiny_color& value );

	void RemoveGlobal( const tiny_string& name );

	void Push( const TinyLuaParameter& parameter );

	bool Pop( TinyLuaParameter& parameter );

	bool Execute( native_string source );

	tiny_inline bool Execute( const tiny_string& source );

	void Terminate( );

public:
	template<typename Type>
	void SetGlobal( const tiny_string& name, Type* value ) { 
		if ( value ) {
			auto name_str = name.get( );

			lua_pushlightuserdata( _lua_state, value );
			lua_setglobal( _lua_state, name_str );
		}
	};

public:
	bool GetExist( const tiny_string& name ) const;

public:
	template<typename Type>
	Type GetGlobal( const tiny_string& name ) {
		auto* name_str = name.get( );
		auto value	   = Type{ };

		lua_getglobal( _lua_state, name_str );

		tiny_compile_if( tiny_is_int( Type ) ) {
			value = tiny_cast( lua_tointeger( _lua_state, TINY_LUA_TOP ), Type );
		} tiny_compile_elif( tiny_is_float( Type ) ) {
			value = tiny_cast( lua_tonumber( _lua_state, TINY_LUA_TOP ), Type );
		} tiny_compile_elif( tiny_is_pointer( Type ) ) {
			value = tiny_cast( lua_topointer( _lua_state, TINY_LUA_TOP ), Type );
		}

		lua_pop( _lua_state, 1 );

		return value;
	};

public:
	operator lua_State* ( );

};
