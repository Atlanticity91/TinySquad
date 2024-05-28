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
//		===	INTERNAL ===
////////////////////////////////////////////////////////////////////////////////////////////
#ifdef TINY_WIN

#	include <fcntl.h>
#	include <shlobj.h>
#	include <Windows.h>

WIN32_FIND_DATAA intern_tp_find_data{ };
HANDLE			 intern_tp_file_handle = INVALID_HANDLE_VALUE;

tiny_directory_entry intern_tp_CreateEntry( ) {
	auto entry  = tiny_directory_entry{ };
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
		entry.Type = TD_TYPE_DIRECTORY;

	return entry;
}
#else
#endif

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
namespace Tiny { 

	bool CreateDir( native_string path ) {
		auto state = false;

		#	ifdef TINY_WIN
		state = CreateDirectoryA( path, NULL ) == TRUE;
		#	endif

		return state;
	}

	bool RemoveDir( native_string path ) {
		auto state = false;

		#	ifdef TINY_WIN
		state = RemoveDirectoryA( path ) == TRUE;
		#	endif

		return state;
	}

	bool RemoveFile( native_string path ) {
		auto state = false;

		if ( path && strlen( path ) > 0 ) {
	#		ifdef TINY_WIN
			state = DeleteFileA( path ) == TRUE;
	#		endif
		}

		return state;
	}

	bool GetIsDir( native_string path ) {
		auto state = false;

		#	ifdef TINY_WIN
		auto attribute_data = WIN32_FILE_ATTRIBUTE_DATA{ };

		state = GetFileAttributesExA( path, GetFileExInfoStandard, tiny_rvalue( attribute_data ) ) == TRUE;

		if ( state )
			state = attribute_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY;
		#	endif

		return state;
	}

	bool GetIsFile( native_string path ) {
		auto state = false;

		#	ifdef TINY_WIN
		auto attribute_data = WIN32_FILE_ATTRIBUTE_DATA{ };

		state = GetFileAttributesExA( path, GetFileExInfoStandard, tiny_rvalue( attribute_data ) ) == TRUE;

		if ( state )
			state = ( attribute_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ) == 0;
		#	endif

		return state;
	}

	std::string GetWorkingDir( ) {
		auto path = std::string{ };

	#	ifdef TINY_WIN
		char dir_path[ MAX_PATH ];
		auto length = GetCurrentDirectoryA( MAX_PATH, dir_path );

		if ( length > 0 ) {
			path = dir_path;
			path += '\\';
		}
	#	endif

		return path;
	}

	std::string GetDocumentDir( ) {
		auto path = std::string{ };

	#	ifdef TINY_WIN
		char dir_path[ MAX_PATH ];

		if ( SUCCEEDED( SHGetFolderPathA( NULL, CSIDL_PERSONAL, NULL, 0, dir_path ) ) ) {
			path = dir_path;
			path += '\\';
		}
	#	endif

		return path;
	}

	std::optional<tiny_directory_entry> FindEntry( native_string path ) {
		intern_tp_file_handle = FindFirstFileExA( path, FindExInfoStandard, tiny_rvalue( intern_tp_find_data ), FindExSearchNameMatch, NULL, 0 );

		if ( intern_tp_file_handle != INVALID_HANDLE_VALUE )
			return intern_tp_CreateEntry( );

		FindClose( intern_tp_file_handle );

		return { };
	}

	std::optional<tiny_directory_entry> NextEntry( ) {
		if ( intern_tp_file_handle != INVALID_HANDLE_VALUE ) {
			if ( FindNextFileA( intern_tp_file_handle, tiny_rvalue( intern_tp_find_data ) ) )
				return intern_tp_CreateEntry( );

			FindClose( intern_tp_file_handle );

			intern_tp_file_handle = INVALID_HANDLE_VALUE;
		}

		return { };
	}

};
