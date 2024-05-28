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

#include <TinyMicro/Kernel/TinyUUID.h>

template<tiny_uint Length>
	requires ( Length > 0 )
struct tiny_buffer {

	tiny_uint Cursor;
	tiny_ubyte Values[ Length ];

	tiny_buffer( ) 
	{ };

	~tiny_buffer( ) = default;

	tiny_buffer& operator=( native_string& string );
	
	tiny_buffer& operator=( const std::string& string );

	tiny_buffer& operator=( const tiny_string& string );

};
