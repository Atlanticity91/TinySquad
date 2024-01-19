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

#include "TinyString.h"

template<tiny_uint Length>
struct tiny_buffer {

	tiny_uint Cursor;
	tiny_ubyte Values[ Length ];

	tiny_buffer( )
		: Cursor{ 0 },
		Values{ }
	{ };

	~tiny_buffer( ) = default;

	bool store( tiny_uint length, const c_ptr data ) { 
		auto state = length > 0 && data && Length - Cursor >= length;

		if ( state ) {
			Tiny::Memcpy( data, &Values[ Cursor ], length );

			Cursor += length;
		}

		return state;
	};

	bool unstore( tiny_uint length, c_ptr data ) { 
		auto state = length > 0 && data && Cursor > 0 && Cursor - length >= 0;

		if ( state ) {
			Cursor -= length;

			Tiny::Memcpy( &Values[ Cursor ], data, length );
		}

		return state;
	};

	tiny_buffer& clear( ) { Cursor = 0; };

	template<typename Type>
	bool store( Type& element ) { return store( tiny_sizeof( Type ), &element ); };

	template<typename Type>
	bool unstore( Type& element ) { return unstore( tiny_sizeof( Type ), &element ); };

	tiny_uint length( ) const { return Length; };

	c_ptr get( ) { return (c_ptr)Values; };

	const c_ptr get( ) const { return (c_ptr)Values; };

	char* as_chars( ) { return (char*)Values; };

	c_str as_chars( ) const { return (c_str)Values; };

	tiny_string as_string( ) { return tiny_string{ (c_str)Values }; };

	const tiny_string as_string( ) const { return tiny_string{ (c_str)Values }; };

	operator c_ptr ( ) const { return (c_ptr)Values; };

	operator const c_ptr ( ) const { return (const c_ptr)Values; };

	operator char* ( ) { return as_chars( ); };

	operator c_str ( ) const { return as_chars( ); };

	operator tiny_string ( ) { return as_string( ); }

	operator const tiny_string( ) const { return as_string( ); };

};
