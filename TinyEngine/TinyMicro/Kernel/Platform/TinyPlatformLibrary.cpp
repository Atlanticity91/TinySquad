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

	bool LoadLib( native_string& path, tiny_library& library ) {
		auto state = path && strlen( path ) > 0;

		if ( state ) {
	#		ifdef TINY_WIN
			library.Handle = LoadLibraryA( path );

			state = library.Handle != 0;
	#		else
	#		endif
		}

		return state;
	}
	
	native_pointer GetLibProcedure(
		const tiny_library& library,
		const native_string& procedure_name
	) {
		auto procedure = tiny_cast( nullptr, native_pointer );

	#	ifdef TINY_WIN
		if ( library.Handle != 0 && procedure_name && strlen( procedure_name ) > 0 )
			procedure = tiny_cast( GetProcAddress( library.Handle, procedure_name ), native_pointer );
	#	else
	#	endif

		return procedure;
	}
	
	bool UnloadLib( tiny_library& library ) {
		auto state = false;

	#	ifdef TINY_WIN
		state = FreeLibrary( library.Handle ) == TRUE;
	#	else
	#	endif

		return state;
	}

	bool GetIsValid( const tiny_library& library ) {
		auto state = false;

	#	ifdef TINY_WIN
		state = library.Handle != NULL;
	#	else
	#	endif

		return state;
	}

};
