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

#include <TinyMicro/__tiny_micro_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
namespace Tiny {

	tiny_file FileOpen( native_string path, TinyFileAccesses access ) {
		auto file = tiny_file{ };

		if ( path && strlen( path ) > 0 && access > TF_ACCESS_BINARY ) {
			auto* mode = "w";

			switch ( access ) {
				case TF_ACCESS_READ			: mode = "r";   break;
				case TF_ACCESS_EDIT			: mode = "w+";  break;
				case TF_ACCESS_BINARY_READ  : mode = "rb";  break;
				case TF_ACCESS_BINARY_WRITE : mode = "wb";  break;
				case TF_ACCESS_BINARY_EDIT  : mode = "wb+"; break;

				default : break;
			}

	#		ifdef TINY_WIN
			fopen_s( tiny_rvalue( file.Handle ), path, mode );
	#		else
			file.Handle = fopen( path, mode );
	#		endif

			if ( file.Handle != nullptr ) {
				file.Size   = GetSize( file );
				file.Access = access;
			}
		}

		return file;
	}

	bool FileSeek( tiny_file& file, TinyFileOrigin origin, tiny_ulong offset ) {
		auto state = false;

		if ( GetFileIsValid( file ) && file.Access > TF_ACCESS_NONE ) {
			auto offset_ = tiny_cast( offset, long );

			state = fseek( file.Handle, offset_, tiny_cast( origin, tiny_int ) ) == 0;
		}

		return state;
	}
	
	tiny_ulong FileRead(
		tiny_file& file,
		const tiny_ulong length,
		native_pointer data
	) {
		auto read_bytes = tiny_cast( 0, tiny_ulong );

		if ( GetFileIsValid( file ) ) {
	#		ifdef TINY_WIN
			read_bytes = tiny_cast( fread_s( data, length, tiny_sizeof( tiny_ubyte ), length, file.Handle ), tiny_ulong );
	#		else
			read_bytes = tiny_cast( fread( data, tiny_sizeof( tiny_ubyte ), length, file.Handle ), tiny_ulong );
	#		endif
		}

		return read_bytes;
	}
	
	tiny_ulong FileWrite(
		tiny_file& file,
		const tiny_ulong length,
		const native_pointer data
	) {
		auto write_bytes = tiny_cast( 0, tiny_ulong );

		if ( GetFileIsValid( file ) )
			write_bytes = tiny_cast( fwrite( data, tiny_sizeof( tiny_ubyte ), length, file.Handle ), tiny_ulong );

		return write_bytes;
	}
	
	void FileClose( tiny_file& file ) {
		if ( GetFileIsValid( file ) )
			fclose( file.Handle );
	}
	
	bool GetFileIsValid( const tiny_file& file ) { return file.Handle != nullptr; }
	
	bool GetFileCan( const tiny_file& file, TinyFileAccesses access ) {
		return GetFileIsValid( file ) && ( file.Access & access );
	}
	
	tiny_ulong GetFileCursor( const tiny_file& file ) {
		auto cursor = tiny_cast( 0, tiny_ulong );

		if ( GetFileIsValid( file ) )
			cursor = ftell( file.Handle );

		return cursor;
	}

	tiny_ulong GetSize( const tiny_file& file ) {
		auto size = tiny_cast( 0, tiny_ulong );

		if ( file.Handle != nullptr ) {
			fseek( file.Handle, 0, SEEK_END );

			size = tiny_cast( ftell( file.Handle ), tiny_ulong );

			fseek( file.Handle, 0, SEEK_SET );
		}

		return size;
	}

};
