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
	: _source{ },
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
			auto source = tiny_string{ _source.GetAddress( ), length + 1 };

			source[ length ] = '\0';

			PreProcess( source );

			state = context.Compile( source );
		}
	}

	return state;
}

bool TinyScriptLua::Create( TinyLuaContext& context, tiny_pointer source ) {
	auto* address = tiny_cast( source, tiny_uint* );
	auto state    = address != nullptr;

	if ( state ) {
		auto length = tiny_lvalue( address );
		auto source = tiny_string{ tiny_cast( address + 1 , c_pointer ), length };

		PreProcess( source );

		state = context.Compile( source );
	}

	return state;
}

void TinyScriptLua::Execute( TinyLuaContext& context, const TinyScriptExecution& execution ) {
	auto* function_str = execution.Function.as_chars( );
	auto* table_str	   = _table.as_chars( );

	lua_getglobal( context, table_str );
	lua_pushstring( context, function_str );
	
	auto type = lua_gettable( context, -2 );

	if ( lua_isfunction( context, type ) ) {
		TinyLua::Script::Convert( context, tiny_cast( execution.Component, TinyComponent* ) );

		lua_pcall( context, 1, 0, 0 );
	}
}

void TinyScriptLua::Terminate( TinyLuaContext& context ) {
	auto* table_str = _table.as_chars( );

	lua_pushnil( context );
	lua_setglobal( context, table_str );

	tiny_deallocate( _source );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE ===
////////////////////////////////////////////////////////////////////////////////////////////
void TinyScriptLua::PreProcess( tiny_string& source ) {
	auto keyword = "function";
	auto char_id = tiny_cast( 0, tiny_uint );
	auto char_offset = tiny_cast( 1, tiny_uint );

	//while ( char_id < source.length( ) ) { }

	_functions.emplace_back( { "Test" } );
	_functions.emplace_back( { "Test01" } );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
const tiny_string& TinyScriptLua::GetTable( ) const { return _table; }

const tiny_list<tiny_string>& TinyScriptLua::GetFunctions( ) const { return _functions; }
