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
 * @creation : 27/07/2024
 * @version  : 2024.2.8
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "TinyRandom.h"

namespace TinyMath {

	/**
	 * CRC32 function
	 * @note : Compute CRC algorithm with 32 bits outputs and 32 bits max input length.
	 * @param buffer_length : Current buffer length.
	 * @param buffer_data   : Current buffer data.
	 **/
	tm_dll tiny_uint CRC32( tiny_uint buffer_length, const native_pointer buffer_data );
	
	/**
	 * CRC32 function
	 * @note : Compute CRC algorithm with 32 bits outputs and 64 bits max input length.
	 * @param buffer_length : Current buffer length.
	 * @param buffer_data   : Current buffer data.
	 **/
	tm_dll tiny_uint CRC32( tiny_ulong buffer_length, const native_pointer buffer_data );

};
