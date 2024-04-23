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
 * @creation : 23/04/2024
 * @version  : 2024.2.7
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#include <TinyEngine/__tiny_engine_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
namespace Tiny {

	tiny_uint MakeVersion(
		const tiny_ushort major,
		const tiny_ubyte minor,
		tiny_ubyte patch
	) {
		return tiny_cast( (
			TINY_LEFT_SHIFT( major, 16 ) |
			TINY_LEFT_SHIFT( minor, 8 )  |
			patch
		), tiny_uint );
	}

	tiny_uint GetVersionMajor( const tiny_uint version ) {
		return TINY_RIGHT_SHIFT( version, 16 ) & 0x0000ffff;
	}

	tiny_uint GetVersionMinor( const tiny_uint version ) {
		return TINY_RIGHT_SHIFT( version, 8 ) & 0x000000ff;
	}

	tiny_uint GetVersionPatch( const tiny_uint version ) {
		return version & 0x000000ff;
	}

};
