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

#include <TinyMicro/__tiny_micro_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	INTERNAL ===
////////////////////////////////////////////////////////////////////////////////////////////
#ifdef TINY_WIN
#define _CRTDBG_MAP_ALLOC

#ifdef _MSC_BUILD
#	include <crtdbg.h>
#endif

#include <corecrt_io.h>
#include <fcntl.h>
#include <shlobj.h>
#include <Windows.h>

WIN32_FIND_DATAA intern_tp_find_data{ };
HANDLE			 intern_tp_file_handle = INVALID_HANDLE_VALUE;

Tiny::FileEntry intern_tp_CreateEntry( ) { 
	auto entry  = Tiny::FileEntry{ };
	auto length = tiny_cast( strlen( intern_tp_find_data.cFileName ) + 1, tiny_uint );

	Tiny::Memcpy( intern_tp_find_data.cFileName, entry.Name, length );

	if ( length > 3 ) {
		while ( length > 0 && entry.Name[ length ] != '.' )
			length -= 1;

		if ( entry.Name[ length ] == '.' )
			entry.Extension = length + 1;
	}

	entry.Size = tiny_cast( intern_tp_find_data.nFileSizeLow, tiny_ulong );
	
	if ( intern_tp_find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
		entry.Type = Tiny::TF_TYPE_DIRECTORY;

	return entry;
}
#endif

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
void Tiny::DumpLeaks( ) {
#	ifdef TINY_WIN
	_CrtDumpMemoryLeaks( );
#	endif
}

bool Tiny::Memcpy( const c_pointer src, c_pointer dst, tiny_uint size ) {
	auto state = false;

#	ifdef TINY_WIN
	state = ( memmove_s( dst, size, src, size ) == 0 );
#	endif

	return state;
}

std::string Tiny::GetWorkingDir( ) {
	auto path = std::string{ };

#	ifdef TINY_WIN
	char dir_path[ MAX_PATH ];
	auto length = GetCurrentDirectoryA( MAX_PATH, dir_path );

	if ( length > 0 ) {
		path  = dir_path;
		path += '\\';
	}
#	endif

	return path;
}

std::string Tiny::GetDocumentDir( ) {
	auto path = std::string{ };

#	ifdef TINY_WIN
	char dir_path[ MAX_PATH ];

	if ( SUCCEEDED( SHGetFolderPathA( NULL, CSIDL_PERSONAL, NULL, 0, dir_path ) ) ) {
		path  = dir_path;
		path += '\\';
	}
#	endif

	return path;
}

bool Tiny::CreateDir( c_string path ) {
	auto state = false;

#	ifdef TINY_WIN
	state = CreateDirectoryA( path, NULL ) == TRUE;
#	endif

	return state;
}

bool Tiny::RemoveDir( c_string path ) {
	auto state = false;

#	ifdef TINY_WIN
	state = RemoveDirectoryA( path ) == TRUE;
#	endif
	
	return state;
}

bool Tiny::GetIsDir( c_string path ) {
	auto state = false;

#	ifdef TINY_WIN
	auto attribute_data = WIN32_FILE_ATTRIBUTE_DATA{ };

	state = GetFileAttributesExA( path, GetFileExInfoStandard, tiny_rvalue( attribute_data ) ) == TRUE;

	if ( state )
		state = attribute_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY;
#	endif

	return state;
}

bool Tiny::GetIsFile( c_string path ) {
	auto state = false;

#	ifdef TINY_WIN
	auto attribute_data = WIN32_FILE_ATTRIBUTE_DATA{ };

	state = GetFileAttributesExA( path, GetFileExInfoStandard, tiny_rvalue( attribute_data ) ) == TRUE;
	
	if ( state )
		state = !( attribute_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY );
#	endif

	return state;
}

std::optional<Tiny::FileEntry> Tiny::FindEntry( c_string path ) {
	intern_tp_file_handle = FindFirstFileExA( path, FindExInfoStandard, tiny_rvalue( intern_tp_find_data ), FindExSearchNameMatch, NULL, 0 );

	if ( intern_tp_file_handle != INVALID_HANDLE_VALUE )
		return intern_tp_CreateEntry( );

	FindClose( intern_tp_file_handle );

	return { };
}

std::optional<Tiny::FileEntry> Tiny::NextEntry( ) {
	if ( intern_tp_file_handle != INVALID_HANDLE_VALUE ) { 
		if ( FindNextFileA( intern_tp_file_handle, tiny_rvalue( intern_tp_find_data ) ) )
			return intern_tp_CreateEntry( );
		
		FindClose( intern_tp_file_handle );

		intern_tp_file_handle = INVALID_HANDLE_VALUE;
	}

	return { };
}

Tiny::File Tiny::FileOpen( c_string path, FileAccesses access ) {
	auto file = Tiny::File{ access };

#	ifdef TINY_WIN
	auto flags = GENERIC_READ;
	auto mode  = CREATE_NEW;

	if ( access == TF_ACCESS_WRITE )
		flags = GENERIC_WRITE;
	else if ( access == TF_ACCESS_EDIT )
		flags |= GENERIC_WRITE;

	auto data   = WIN32_FIND_DATAA{ };
	auto handle = FindFirstFileA( path, &data );

	if ( handle != INVALID_HANDLE_VALUE ) {
		mode = access == TF_ACCESS_EDIT ? TRUNCATE_EXISTING : OPEN_EXISTING;

		FindClose( handle );
	}

	file.Handle = CreateFileA( path, flags, FILE_SHARE_READ, NULL, mode, FILE_ATTRIBUTE_NORMAL, NULL );

	if ( Tiny::GetFileIsValid( file ) ) {
		auto tmp_size = LARGE_INTEGER{ };

		GetFileSizeEx( file.Handle, tiny_rvalue( tmp_size ) );

		file.Size = tiny_cast( tmp_size.LowPart, tiny_uint );
	}
#	endif

	return file;
}

bool Tiny::FileSeek( File& file, FileOrigin origin ) {
	return Tiny::FileSeek( file, origin, 0 );
}

bool Tiny::FileSeek( File& file, FileOrigin origin, tiny_uint offset ) {
	auto state = false;

#	ifdef TINY_WIN
	auto flag = FILE_BEGIN;

	if ( origin == TF_ORIGIN_CURSOR )
		flag = FILE_CURRENT;
	else if ( origin == TF_ORIGIN_END )
		flag = FILE_END;

	state = SetFilePointer( file.Handle, tiny_cast( offset, LONG ), NULL, flag ) != INVALID_SET_FILE_POINTER;
#	endif

	return state;
}

tiny_uint Tiny::FileRead( File& file, tiny_uint length, c_pointer data ) {
	auto read_bytes = tiny_cast( 0, tiny_uint );

#	ifdef TINY_WIN
	auto tmp_read = tiny_cast( 0, DWORD );

	if ( ReadFile( file.Handle, data, length, tiny_rvalue( tmp_read ), NULL ) == TRUE )
		read_bytes = tiny_cast( tmp_read, tiny_uint );
#	endif

	return read_bytes;
}

tiny_uint Tiny::FileWrite( File& file, tiny_uint length, const c_pointer data ) {
	auto write_bytes = tiny_cast( 0, tiny_uint );

#	ifdef TINY_WIN
	auto tmp_write = tiny_cast( 0, DWORD );

	if ( WriteFile( file.Handle, data, length, tiny_rvalue( tmp_write ), NULL ) == TRUE )
		write_bytes = tiny_cast( tmp_write, tiny_uint );
#	endif

	return write_bytes;
}

void Tiny::FileClose( File& file ) {
#	ifdef TINY_WIN
	if ( CloseHandle( file.Handle ) == TRUE )
		file.Handle = INVALID_HANDLE_VALUE;
#	endif
}

bool Tiny::RemoveFile( c_string path ) {
	auto state = false;

#	ifdef TINY_WIN
	state = DeleteFileA( path ) == TRUE;
#	endif

	return state;
}

bool Tiny::GetFileIsValid( const File& file ) { 
#	ifdef TINY_WIN
	return file.Handle != INVALID_HANDLE_VALUE; 
#	else
	return false;
#	endif
}

bool Tiny::GetFileCan( const File& file, FileAccesses access ) {
	return Tiny::GetFileIsValid( file ) && ( file.Access & access );
}

tiny_uint Tiny::GetFileCursor( const File& file ) {
	auto cursor = tiny_cast( 0, tiny_uint );
	
	if ( Tiny::GetFileIsValid( file ) ) {
#		ifdef TINY_WIN
		cursor = tiny_cast( SetFilePointer( file.Handle, 0, NULL, FILE_CURRENT ), tiny_uint );
#		endif
	}

	return cursor;
}

bool Tiny::OpenDialog( DialogTypes type, c_string filters, tiny_uint length, char* data ) {
	return Tiny::OpenDialog( type, nullptr, filters, length, data );
}

bool Tiny::OpenDialog( DialogTypes type, c_string path, c_string filters, tiny_uint length, char* data ) {
	auto state = false;

#	ifdef TINY_WIN
	auto context = OPENFILENAMEA{ };

	ZeroMemory( &context, sizeof( OPENFILENAMEA ) );

	context.lStructSize  = sizeof( OPENFILENAMEA );
	context.hwndOwner	 = GetActiveWindow( );
	context.lpstrFile	 = data;
	context.nMaxFile	 = length;
	context.lpstrFilter  = filters;
	context.nFilterIndex = 1;
	context.Flags		 = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

	if ( path )
		context.lpstrInitialDir = path;

	if ( type == Tiny::TD_TYPE_OPEM_FILE )
		state = GetOpenFileNameA( tiny_rvalue( context ) ) == TRUE;
	else if ( type == Tiny::TD_TYPE_SAVE_FILE )
		state = GetSaveFileNameA( tiny_rvalue( context ) ) == TRUE;
#	endif

	return state;
}

bool Tiny::OpenDialog( DialogTypes type, std::string path, c_string filters, tiny_uint length, char* data ) {
	auto* _path = path.size( ) > 0 ? path.c_str( ) : nullptr;

	return Tiny::OpenDialog( type, _path, filters, length, data );
}

Tiny::Date Tiny::GetDate( ) {
	auto date = Tiny::Date{ };

#	ifdef TINY_WIN
	auto time = SYSTEMTIME{ };

	GetSystemTime( tiny_rvalue( time ) );

	date.Year   = tiny_cast( time.wYear, tiny_ushort );
	date.Day    = tiny_cast( time.wDay, tiny_ubyte );
	date.Month  = tiny_cast( time.wMonth, tiny_ubyte );
	date.Hour   = tiny_cast( time.wHour, tiny_ubyte );
	date.Minute = tiny_cast( time.wMinute, tiny_ubyte );
	date.Second = tiny_cast( time.wSecond, tiny_ubyte );
#	else
#	endif

	return date;
}

bool Tiny::LoadLib( c_string& path, Library& library ) {
	auto state = path && strlen( path ) > 0;

	if ( state ) {
#		ifdef TINY_WIN
		library.Handle = LoadLibraryA( path );

		state = library.Handle != 0;
#		endif
	}

	return state;
}

c_pointer Tiny::GetLibProcedure( Library& library, c_string& address ) {
	auto procedure = tiny_cast( nullptr, c_pointer );

#	ifdef TINY_WIN
	if ( library.Handle != 0 && address && strlen( address ) > 0 )
		procedure = tiny_cast( GetProcAddress( library.Handle, address ), c_pointer );
#	endif

	return procedure;
}

bool Tiny::UnloadLib( Library& library ) {
	auto state = false;

#	ifdef TINY_WIN
	state = FreeLibrary( library.Handle ) == TRUE;
#	endif

	return state;
}
