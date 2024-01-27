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

#include "TinyLuaExecution.h"

#define TINY_LUA_TOP -1

typedef lua_CFunction TinyLuaPrototype;

te_class TinyLuaContext final {

private:
	lua_State* _lua_state;

public:
	TinyLuaContext( );

	~TinyLuaContext( ) = default;

	bool Create( );

	bool Compile( c_string source );

	bool Compile( const tiny_string& source );

	void SetGlobal( const tiny_string& name, c_pointer value );

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

	void SetGlobal( const tiny_string& name, TinyLuaPrototype function );

	bool Execute( TinyGame* game, TinyLuaExecution& execution );

	bool Execute( TinyGame* game, const tiny_string& script, c_pointer instigator );

	void Terminate( );

public:
	operator lua_State* ( );

};
