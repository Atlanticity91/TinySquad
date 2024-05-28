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

namespace Tiny {

	tm_dll bool Initialize( );

	tm_dll void Terminate( );

	tm_dll void DumpLeaks( );

	tm_dll bool Memcpy( const native_pointer src, native_pointer dst, const tiny_ulong size );

	template<typename Type>
	bool Memcpy( const Type* src, Type* dst, const tiny_uint count ) {
		auto block_size = tiny_cast( count * tiny_sizeof( Type ), tiny_ulong );

		return Memcpy( tiny_cast( src, const native_pointer ), tiny_cast( dst, native_pointer ), block_size );
	};

	template<typename Type>
	bool Memcpy( const Type* src, Type* dst ) {
		return Memcpy( src, dst, 1 );
	};

	template<tiny_uint Length, typename... Args >
	bool Sprintf( tiny_buffer<Length>& buffer, const tiny_string& format, Args&&... args ) { 
	#	ifdef TINY_WIN
		auto* buffer_str = buffer.as_chars( );
		auto* format_str = format.as_chars( );

		buffer.Cursor = sprintf_s( buffer_str, Length, format_str, std::forward<Args>( args )... );
	#	else
		buffer.Cursor = sprintf( buffer_str, format_str, args... );
	#	endif

		return buffer.Cursor > 0;
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
