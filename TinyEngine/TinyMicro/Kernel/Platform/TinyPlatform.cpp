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

#	define _CRTDBG_MAP_ALLOC

#	ifdef _MSC_BUILD
#		include <crtdbg.h>
#	endif

#	include <corecrt_io.h>
#	include <fcntl.h>
#	include <shlobj.h>
#	include <Windows.h>

#else
#endif

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
namespace Tiny {

	bool Initialize( ) {
		auto state = false;

	#	ifdef TINY_WIN
		state = !FAILED( CoInitializeEx( nullptr, COINIT_MULTITHREADED ) );
	#	else
	#	endif

		return state;
	}

	void Terminate( ) {
	#	ifdef TINY_WIN
		CoUninitialize( );
	#	else
	#	endif
	}

	void DumpLeaks( ) {
	#	ifdef TINY_WIN
		_CrtDumpMemoryLeaks( );
	#	endif
	}

	bool Tiny::Memcpy( const native_pointer src, native_pointer dst, const tiny_ulong size ) {
		auto state = false;

	#	ifdef TINY_WIN
		state = ( memmove_s( dst, size, src, size ) == 0 );
	#	else
		state = memmove( dst, src, size ) == dst;
	#	endif

		return state;
	}

	bool OpenDialog(
		TinyDialogTypes type, 
		const tiny_string& path,
		const tiny_string& filters,
		tiny_uint length, 
		char* data 
	) {
		auto state = false;

	#	ifdef TINY_WIN
		auto context = OPENFILENAMEA{ };

		ZeroMemory( tiny_rvalue( context ), sizeof( OPENFILENAMEA ) );

		context.lStructSize  = sizeof( OPENFILENAMEA );
		context.hwndOwner    = GetActiveWindow( );
		context.lpstrFile    = data;
		context.nMaxFile	 = length;
		context.lpstrFilter  = filters.as_chars( );
		context.nFilterIndex = 1;
		context.Flags		 = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

		if ( path )
			context.lpstrInitialDir = path.as_chars( );

		if ( type == TD_TYPE_OPEM_FILE )
			state = GetOpenFileNameA( tiny_rvalue( context ) ) == TRUE;
		else if ( type == TD_TYPE_SAVE_FILE )
			state = GetSaveFileNameA( tiny_rvalue( context ) ) == TRUE;
	#	endif

		return state;
	}

	tiny_date GetDate( ) {
		auto date = tiny_date{ };

	#	ifdef TINY_WIN
		auto time = SYSTEMTIME{ };

		GetSystemTime( tiny_rvalue( time ) );

		date.Year   = tiny_cast( time.wYear,   tiny_ushort );
		date.Day    = tiny_cast( time.wDay,    tiny_ubyte  );
		date.Month  = tiny_cast( time.wMonth,  tiny_ubyte  );
		date.Hour   = tiny_cast( time.wHour,   tiny_ubyte  );
		date.Minute = tiny_cast( time.wMinute, tiny_ubyte  );
		date.Second = tiny_cast( time.wSecond, tiny_ubyte  );
	#	else
	#	endif

		return date; 
	}

};
