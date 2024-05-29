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
 * @creation : 24/05/2023
 * @version  : 2024.2.8
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "TinyPlatformDirectory.h"

#ifdef TINY_DEBUG
#	define tiny_dump_leaks( ) Tiny::DumpLeaks( )
#else
#	define tiny_dump_leaks( )
#endif

template<tiny_uint Length> 
	requires ( Length > 0 ) 
struct tiny_buffer;

tm_struct tiny_date {

	tiny_ushort Year   = 0x00;
	tiny_ubyte Day	   = 0x00;
	tiny_ubyte Month   = 0x00;
	tiny_ubyte Hour    = 0x00;
	tiny_ubyte Minute  = 0x00;
	tiny_ubyte Second  = 0x00;
	tiny_ubyte Padding = 0xff;

};

tiny_enum( TinyDialogTypes ) {

	TD_TYPE_OPEM_FILE = 0,
	TD_TYPE_SAVE_FILE

};

template<typename Type_a, typename Type_b >
concept TinyIsCopyable = ( !tiny_is_pointer( Type_a ) && !tiny_is_pointer( Type_b ) );

namespace Tiny {

	tm_dll bool Initialize( );

	tm_dll void Terminate( );

	tm_dll void DumpLeaks( );

	template<typename Type_a, typename Type_b>
		requires TinyIsCopyable<Type_a, Type_b>
	bool Memcpy( const Type_a* src, Type_b* dst, const tiny_ulong length ) {
		auto* src_ = tiny_cast( src, const native_pointer );
		auto* dst_ = tiny_cast( dst, native_pointer );
		auto state = false;

	#	ifdef TINY_WIN
		state = ( memmove_s( dst, length, src, length ) == 0 );
	#	else
		state = ( memmove( dst, src, length ) == dst );
	#	endif

		return state;
	};

	template<typename Type>
		requires TinyIsCopyable<Type, Type>
	bool Memcpy( const Type& src, Type& dst ) {
		return Memcpy<Type, Type>( tiny_rvalue( src ), tiny_rvalue( dst ), tiny_sizeof( Type ) );
	};

	template<tiny_uint Length, typename... Args >
	bool Sprintf( tiny_buffer<Length>& buffer, const tiny_string& format, Args&&... args ) { 
		auto* buffer_str = buffer.as_chars( );
		auto* format_str = format.get( );

	#	ifdef TINY_WIN
		auto count = tiny_cast( sprintf_s( buffer_str, Length, format_str, std::forward<Args>( args )... ), tiny_uint );
	#	else
		auto count = sprintf( buffer_str, format_str, args... ), tiny_uint );
	#	endif
		
		buffer.set_cursor( count );

		return count > 0;
	};

	tm_dll bool OpenDialog( 
		TinyDialogTypes type,
		const tiny_string& path,
		const tiny_string& filters,
		tiny_uint length,
		char* data 
	);

	tm_dll tiny_date GetDate( );

};
