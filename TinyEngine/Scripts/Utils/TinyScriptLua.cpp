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
	: _source{ }
{ }

bool TinyScriptLua::Create( TinyLuaContext& context, TinyFile& file ) {
	auto length = tiny_cast( 0, tiny_uint );
	auto state  = file.Read( length ) > 0 && tiny_allocate( _source, length );

	if ( state ) {
		auto* address = _source.GetAddress( );

		state = file.Read( length, address );

		if ( state ) {
			auto source = tiny_string{ _source.As<const char>( ) };

			state = context.Compile( source );
		}
	}

	return state;
}

bool TinyScriptLua::Create( TinyLuaContext& context, tiny_ptr source ) {
	auto* address = tiny_cast( source, tiny_uint* );
	auto state    = address != nullptr;

	if ( state ) {
		auto length = tiny_lvalue( address );
		auto src	= tiny_string{ tiny_cast( address + 1 , c_ptr ), length };

		state = context.Compile( src );
	}

	return state;
}

void TinyScriptLua::Terminate( TinyLuaContext& context ) {

	tiny_deallocate( _source );
}
