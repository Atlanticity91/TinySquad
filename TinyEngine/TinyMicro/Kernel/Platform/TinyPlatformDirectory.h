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

#include "TinyPlatformFile.h"

tiny_enum( tiny_directory_types ) {

	TD_TYPE_DIRECTORY,
	TD_TYPE_FILE_TEXT,
	TD_TYPE_FILE_BINARY

};

tm_struct tiny_directory_entry {

	char Name[ 256 ]{ '\0' };
	tiny_uint Extension		  = 0;
	tiny_ulong Size			  = 0;
	tiny_directory_types Type = TD_TYPE_DIRECTORY;

};

namespace Tiny { 

	tm_dll bool CreateDir( native_string path );

	tm_dll bool RemoveDir( native_string path );

	tm_dll bool RemoveFile( native_string path );

	tm_dll bool GetIsDir( native_string path );

	tm_dll bool GetIsFile( native_string path );

	tm_dll std::string GetWorkingDir( );

	tm_dll std::string GetDocumentDir( );

	tm_dll std::optional<tiny_directory_entry> FindEntry( native_string path );

	tm_dll std::optional<tiny_directory_entry> NextEntry( );

};
