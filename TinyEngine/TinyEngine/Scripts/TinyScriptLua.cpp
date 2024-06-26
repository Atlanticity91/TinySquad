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
TinyScriptLua::TinyScriptLua( )
	: TinyAsset{ TA_TYPE_SCRIPT },
	_source{ },
	_table{ },
	_functions{ }
{ 
	_functions.emplace_back( "Undefined" );
}

bool TinyScriptLua::Create( TinyLuaContext& context, TinyFile& file ) {
	auto length = tiny_cast( 0, tiny_uint );
	auto state  = file.Read( length ) > 0 && tiny_allocate( _source, length + 1 );

	if ( state ) {
		auto* address = _source.GetAddress( );

		state = file.Read( length, address );

		if ( state ) {
			auto source = tiny_string{ length + 1, _source.GetAddress( ), };

			source[ length ] = '\0';

			state = context.Compile( _table, source );
		}
	}

	return state;
}

bool TinyScriptLua::Create( TinyLuaContext& context, tiny_pointer source ) {
	auto* address = tiny_cast( source, tiny_uint* );
	auto state    = address != nullptr;

	if ( state ) {
		auto length = tiny_lvalue( address );
		auto source = tiny_string{ length, tiny_cast( address + 1 , native_pointer ) };

		source[ length ] = '\0';

		state = context.Compile( _table, source );
	}

	return state;
}

void TinyScriptLua::Execute( TinyLuaContext& context, const TinyScriptExecution& execution ) {
	auto* function_str = execution.Function.get( );
	auto* table_str	   = _table.get( );

	TinyLua::Script::Convert( context, tiny_cast( execution.Component, TinyComponent* ) );

	lua_getglobal( context, table_str );
	lua_getfield( context, TINY_LUA_TOP, function_str );
	lua_pushvalue( context, -2 );
	lua_pcall( context, 1, 0, 0 );
}

void TinyScriptLua::Terminate( TinyGame* game ) {
	auto* table_str = _table.get( );
	auto& scripts   = game->GetScripts( );
	auto& context   = scripts.GetContext( );

	lua_pushnil( context );
	lua_setglobal( context, table_str );

	tiny_deallocate( _source );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
const tiny_string& TinyScriptLua::GetTable( ) const { return _table; }

const tiny_list<tiny_string>& TinyScriptLua::GetFunctions( ) const { return _functions; }
