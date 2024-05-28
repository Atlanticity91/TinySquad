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
 * @creation : 08/02/2024
 * @version  : 2024.1.3
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#include <TinyEngine/__tiny_engine_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyNativeRegister::TinyNativeRegister( )
	: _functions{ }
{ }

void TinyNativeRegister::Register( const tiny_string& alias, const native_pointer function ) {
	if ( !_functions.find( alias ) && function )
		_functions.emplace( alias, function );
}

void TinyNativeRegister::Remove( const tiny_string& function_alias ) {
	auto function_hash = tiny_hash{ function_alias };

	Remove( function_hash );
}

void TinyNativeRegister::Remove( const tiny_hash function_hash ) {
	if ( _functions.find( function_hash ) )
		_functions.erase( function_hash );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyNativeRegister::GetExist( const tiny_string& function_alias ) const {
	auto function_hash = tiny_hash{ function_alias };

	return GetExist( function_hash );
}

bool TinyNativeRegister::GetExist( const tiny_hash function_hash ) const {
	return _functions.find( function_hash );
}

tiny_list<native_string> TinyNativeRegister::GetList( ) const {
	auto count = _functions.size( );
	auto list  = tiny_list<native_string>{ };

	list = count + 1;

	list[ 0 ] = "Undefined";

	while ( count-- > 0) {
		auto& name = _functions.node( count ).Alias;

		list[ count + 1 ] = name.c_str( );
	}

	return list;
}

tiny_map<native_pointer>& TinyNativeRegister::GetNatives( ) { return _functions; }

const tiny_map<native_pointer>& TinyNativeRegister::GetNatives( ) const { return _functions; }
