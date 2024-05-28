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

#pragma once

#include <TinyEngine/Scripts/TinyScriptLua.h>

#define tli_make_lua_context( NAME ) auto& NAME = game->GetScripts( ).GetContext( )
#define tli_metaname( NAME ) ( NAME"Metatable" )
#define tli_create( NAME ) auto table_id = TinyLua::CreateTable( context, NAME )
#define tli_createmeta( NAME ) TinyLua::CreateMetatable( context, tli_metaname( NAME ), table_id )
#define tli_createfn( NAME, FN ) TinyLua::CreateFunction( context, NAME, FN )
#define tli_createop( NAME, FN ) TinyLua::CreateOperator( context, NAME, FN )
#define tli_create_new( NAME, ... )\
	lua_newtable( context );\
	__VA_ARGS__\
	TinyLua::LinkMetatable( context, tli_metaname( NAME ) )
#define tli_create_field( NAME, VALUE ) TinyLua::CreateField( context, NAME, VALUE )
#define tli_get_field( TABLE, NAME, VALUE ) TinyLua::GetField( context, TABLE, NAME, VALUE )
#define tli_set_field( NAME, VALUE ) TinyLua::SetField( context, NAME, VALUE )
#define tli_prototypefn( NAME ) tiny_int  NAME( lua_State* )
#define tli_implementfn( NAME ) tiny_int NAME( lua_State* context )

#define tli_stack_top TINY_LUA_TOP
#define tli_self 1
#define tli_param_one 1
#define tli_param_two 2
#define tli_param_three 3
#define tli_param_four 4
#define tli_param_five 5
#define tli_get_game( PARAM ) tiny_cast( lua_touserdata( context, PARAM ), TinyGame* )

namespace TinyLua { 

	tiny_dll tiny_int CreateTable( TinyLuaContext& context, const tiny_string& name );

	tiny_dll void CreateFunction( 
		TinyLuaContext& context,
		const tiny_string& name,
		TinyLuaPrototype callback
	);

	tiny_dll bool CreateMetatable(
		TinyLuaContext& context, 
		const tiny_string& name, 
		tiny_int table_id 
	);

	tiny_dll void CreateOperator(
		TinyLuaContext& context, 
		const tiny_string& name, 
		TinyLuaPrototype callback
	);

	tiny_dll void CreateField(
		lua_State* context,
		const tiny_string& name,
		const tiny_string& value
	);

	tiny_dll void CreateField(
		lua_State* context,
		const tiny_string& name,
		const lua_Integer& value
	);

	tiny_dll void CreateField(
		lua_State* context,
		const tiny_string& name,
		const lua_Number& value
	);

	tiny_dll void CreateField(
		lua_State* context,
		const tiny_string& name,
		native_pointer& value
	);

	tiny_dll void LinkMetatable( lua_State* context, const tiny_string& name );

	tiny_dll bool GetField(
		lua_State* context,
		tiny_int table_id,
		const tiny_string& name,
		lua_Integer& value
	);

	tiny_dll bool GetField(
		lua_State* context,
		tiny_int table_id,
		const tiny_string& name,
		lua_Number& value
	);

	tiny_dll bool GetField(
		lua_State* context,
		tiny_int table_id,
		const tiny_string& name,
		native_pointer& value
	);

	tiny_dll void SetField( 
		lua_State* context,
		const tiny_string& name,
		const lua_Integer& value
	);

	tiny_dll void SetField(
		lua_State* context,
		const tiny_string& name,
		const lua_Number& value
	);

};
