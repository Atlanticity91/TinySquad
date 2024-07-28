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

#else
#endif

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
namespace Tiny {

	char tiny_date_buffer[ 20 ] = "";

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

	bool OpenDialog(
		const TinyFileDialog& file_dialog,
		tiny_uint length, 
		char* data 
	) {
		auto state = false;

	#	ifdef TINY_WIN
		auto context = OPENFILENAMEA{ };

		ZeroMemory( tiny_rvalue( context ), sizeof( OPENFILENAMEA ) );

		context.lStructSize		= sizeof( OPENFILENAMEA );
		context.hwndOwner		= GetActiveWindow( );
		context.lpstrFile		= tiny_cast( data, LPSTR );
		context.nMaxFile		= length;
		context.lpstrFilter		= tiny_cast( file_dialog.Filters, LPCSTR );
		context.nFilterIndex	= 1;
		context.Flags			= OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
		context.lpstrInitialDir = tiny_cast( file_dialog.Path, LPCSTR );
		context.lpstrTitle		= tiny_cast( file_dialog.Name, LPCSTR );

		if ( file_dialog.Type == TD_TYPE_OPEM_FILE )
			state = GetOpenFileNameA( tiny_rvalue( context ) ) == TRUE;
		else if ( file_dialog.Type == TD_TYPE_SAVE_FILE )
			state = GetSaveFileNameA( tiny_rvalue( context ) ) == TRUE;
	#	else
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

	std::string GetDateAsString( ) { 
		auto date = GetDate( );

		sprintf(
			tiny_date_buffer, 
			"%04d-%02d-%02d-%02d-%02d-%02d",
			date.Year, date.Month, date.Day, date.Hour, date.Minute, date.Second 
		);

		return { tiny_date_buffer };
	}

};
