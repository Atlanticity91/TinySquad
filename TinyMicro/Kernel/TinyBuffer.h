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
 * @creation : 13/10/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "TinyHash.h"

template<tiny_uint Length>
	requires ( Length > 0 )
struct tiny_buffer {

	tiny_uint Cursor;
	tiny_ubyte Values[ Length ];

	tiny_buffer( )
		: Cursor{ 0 },
		Values{ }
	{ };

	tiny_buffer( const tiny_string& string )
		: tiny_buffer{ }
	{ 
		auto length = string.length( );
		auto* data  = tiny_cast( string.as_chars( ), tiny_ubyte* );

		if ( length > Length )
			length = Length;

		Tiny::Memcpy( data, Values, length );
	};

	~tiny_buffer( ) = default;

	bool store( tiny_uint length, const c_pointer data ) { 
		auto state = length > 0 && data && Length - Cursor >= length;

		if ( state ) {
			Tiny::Memcpy( data, tiny_rvalue( Values[ Cursor ] ), length );

			Cursor += length;
		}

		return state;
	};

	bool store( const tiny_string& string ) { 
		auto* buffer_str = string.as_chars( );
		auto buffer_len  = string.length( ) + 1;

		return store( buffer_len, tiny_cast( buffer_str, const c_pointer ) );
	};

	template<typename... Args>
	bool store( const tiny_string& format, Args&&... args ) { 
		auto buffer = tiny_string{ Values, Length };

		return Tiny::Sprintf( buffer, format, std::forward<Args>( args )... );
	};

	bool unstore( tiny_uint length, c_pointer data ) { 
		auto state = length > 0 && data && Cursor > 0 && Cursor - length >= 0;

		if ( state ) {
			Cursor -= length;

			Tiny::Memcpy( tiny_rvalue( Values[ Cursor ] ), data, length );
		}

		return state;
	};

	bool unstore( tiny_string& string ) {
		auto* buffer_str = string.as_chars( );
		auto buffer_len  = string.length( );

		return unstore( buffer_len, tiny_cast( buffer_str, c_pointer ) );
	};

	tiny_buffer& clear( ) { Cursor = 0; };

	template<typename Type>
	bool store( Type& element ) { 
		auto* _element = tiny_rvalue( element );

		return store( tiny_sizeof( Type ), tiny_cast( _element, const c_pointer ) );
	};

	template<typename Type>
	bool unstore( Type& element ) {
		auto* _element = tiny_rvalue( element );

		return unstore( tiny_sizeof( Type ), tiny_cast( _element, c_pointer ) );
	};

	tiny_uint length( ) const { return Length; };

	c_pointer get( ) { return tiny_cast( Values, c_pointer ); };

	const c_pointer get( ) const { return tiny_cast( Values, const c_pointer ); };

	char* as_chars( ) { return tiny_cast( Values, char* ); };

	c_string as_chars( ) const { return tiny_cast( Values, c_string ); };

	tiny_string as_string( ) { return tiny_string{ tiny_cast( Values, c_string ) }; };

	const tiny_string as_string( ) const { return tiny_string{ tiny_cast( Values, c_string ) }; };

	operator c_pointer ( ) const { return get( ); };

	operator const c_pointer ( ) const { return get( ); };

	operator char* ( ) { return as_chars( ); };

	operator c_string ( ) const { return as_chars( ); };

	operator tiny_string ( ) { return as_string( ); }

	operator const tiny_string( ) const { return as_string( ); };

	tiny_buffer& operator=( const tiny_string& string ) {
		Cursor = tiny_cast( 0, tiny_uint );

		store( string );

		return tiny_self;
	};

};
