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
 * @creation : 16/10/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "TinyCore.h"

#ifdef TM_DEBUG
#	define tiny_dump_leaks( ) Tiny::DumpLeaks( )
#else
#	define tiny_dump_leaks( )
#endif

#define TINY_NO_CFILE (c_file)nullptr

typedef void c_ptr_base;
typedef c_ptr_base* c_ptr;
typedef tiny_ubyte tiny_ptr_base;
typedef tiny_ptr_base* tiny_ptr;

typedef const char* c_str;
typedef FILE* c_file;

namespace Tiny {

	tiny_enum( FileTypes ) {

		TF_TYPE_NORMAL = 0,
		TF_TYPE_DIRECTORY

	};

	tm_struct FileEntry {

		char Name[ 256 ]{ '\0' };
		tiny_uint Extension = 0;
		tiny_ulong Size		= 0;
		FileTypes Type		= TF_TYPE_NORMAL;

	};

	tiny_enum( FileAccesses ) {

		TF_ACCESS_READ  = TINY_LEFT_SHIFT( 0 ),
		TF_ACCESS_WRITE = TINY_LEFT_SHIFT( 1 ),
		TF_ACCESS_EDIT  = TF_ACCESS_READ | TF_ACCESS_WRITE,

	};

	tiny_enum( FileOrigin ) {

		TF_ORIGIN_BEGIN = 0,
		TF_ORIGIN_CURSOR,
		TF_ORIGIN_END

	};

	tm_struct File {

		FileAccesses Access = TF_ACCESS_READ;
		tiny_uint Size		= 0;

#		ifdef TINY_WIN
		HANDLE Handle		= INVALID_HANDLE_VALUE;
#		endif

	};

	tiny_enum( DialogTypes ) {

		TD_TYPE_OPEM_FILE = 0,
		TD_TYPE_SAVE_FILE

	};

	tm_struct Date {

		tiny_ushort Year   = 0;
		tiny_ubyte Day	   = 0;
		tiny_ubyte Month   = 0;
		tiny_ubyte Hour	   = 0;
		tiny_ubyte Minute  = 0;
		tiny_ubyte Second  = 0;
		tiny_ubyte Padding = 0xff;

	};

	tm_struct Library {

#		ifdef TINY_WIN
		HMODULE Handle = 0;
#		endif

	};

	tm_dll void DumpLeaks( );

	tm_dll bool Memcpy( const c_ptr src, c_ptr dst, tiny_uint size );

	template<typename Type>
	bool Memcpy( const Type* src, Type* dst, tiny_uint count ) {
		auto block_size = count * tiny_sizeof( Type );

		return Memcpy( tiny_cast( src, const c_ptr ), tiny_cast( dst, c_ptr ), block_size );
	};

	template<typename Type>
	bool Memcpy( const Type* src, Type* dst ) {
		return Memcpy( src, dst, 1 );
	};

	tm_dll std::string GetWorkingDir( );

	tm_dll std::string GetDocumentDir( );

	tm_dll bool CreateDir( c_str path );

	tm_dll bool RemoveDir( c_str path );

	tm_dll bool GetIsDir( c_str path );

	tm_dll bool GetIsFile( c_str path );

	tm_dll std::optional<FileEntry> FindEntry( c_str path );

	tm_dll std::optional<FileEntry> NextEntry( );

	tm_dll File FileOpen( c_str path, FileAccesses access );

	tm_dll bool FileSeek( File& file, FileOrigin origin );

	tm_dll bool FileSeek( File& file, FileOrigin origin, tiny_uint offset );

	tm_dll tiny_uint FileRead( File& file, tiny_uint length, c_ptr data );

	tm_dll tiny_uint FileWrite( File& file, tiny_uint length, const c_ptr data );

	tm_dll void FileClose( File& file );

	tm_dll bool RemoveFile( c_str path );

	tm_dll bool GetFileIsValid( const File& file );

	tm_dll bool GetFileCan( const File& file, FileAccesses access );

	tm_dll tiny_uint GetFileCursor( const File& file );

	tm_dll bool OpenDialog( DialogTypes type, c_str filters, tiny_uint length, char* data );

	tm_dll bool OpenDialog( 
		DialogTypes type, 
		c_str path,
		c_str filters,
		tiny_uint length,
		char* data 
	);

	tm_dll bool OpenDialog(
		DialogTypes type,
		std::string path, 
		c_str filters, 
		tiny_uint length,
		char* data 
	);

	tm_dll Date GetDate( );

	tm_dll bool LoadLib( c_str& path, Library& library );

	tm_dll c_ptr GetLibProcedure( Library& library, c_str& address );

	tm_dll bool UnloadLib( Library& library );

};
