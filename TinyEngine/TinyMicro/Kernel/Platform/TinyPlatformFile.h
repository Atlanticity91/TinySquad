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

#include "TinyPlatformLibrary.h"

tiny_enum( TinyFileAccesses ) {

	TF_ACCESS_NONE		   = 0,
	TF_ACCESS_BINARY	   = TINY_LEFT_SHIFT( 1, 0 ),
	TF_ACCESS_READ		   = TINY_LEFT_SHIFT( 1, 1 ),
	TF_ACCESS_WRITE		   = TINY_LEFT_SHIFT( 1, 2 ),
	TF_ACCESS_EDIT		   = TF_ACCESS_READ | TF_ACCESS_WRITE,
	TF_ACCESS_BINARY_READ  = TF_ACCESS_BINARY | TF_ACCESS_READ,
	TF_ACCESS_BINARY_WRITE = TF_ACCESS_BINARY | TF_ACCESS_WRITE,
	TF_ACCESS_BINARY_EDIT  = TF_ACCESS_BINARY | TF_ACCESS_EDIT,

};

tiny_enum( TinyFileOrigin ) {

	TF_ORIGIN_BEGIN = 0,
	TF_ORIGIN_CURSOR,
	TF_ORIGIN_END

};

tm_struct tiny_file {

	FILE* Handle			= nullptr;
	tiny_ulong Size			= 0;
	TinyFileAccesses Access = TF_ACCESS_NONE;

};

namespace Tiny {

	tm_dll tiny_file FileOpen( native_string path, TinyFileAccesses access );

	tm_dll bool FileSeek( tiny_file& file, TinyFileOrigin origin, tiny_ulong offset );

	tm_dll tiny_uint FileRead( 
		tiny_file& file, 
		const tiny_ulong length,
		native_pointer data 
	);

	tm_dll tiny_uint FileWrite( 
		tiny_file& file, 
		const tiny_uint length, 
		const native_pointer data 
	);

	tm_dll void FileClose( tiny_file& file );

	tm_dll bool GetFileIsValid( const tiny_file& file );

	tm_dll bool GetFileCan( const tiny_file& file, TinyFileAccesses access );

	tm_dll tiny_ulong GetFileCursor( const tiny_file& file );

	tm_dll tiny_ulong GetSize( const tiny_file& file );

};
