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

#pragma once

#include "TinyCore.h"

#define TINY_ENGINE_MAJOR 2024
#define TINY_ENGINE_MINOR 2
#define TINY_ENGINE_PATCH 8
#define TINY_ENGINE_VERSION\
	Tiny::MakeVersion( TINY_ENGINE_MAJOR, TINY_ENGINE_MINOR, TINY_ENGINE_PATCH )

namespace Tiny { 

	tiny_dll tiny_uint MakeVersion(
		const tiny_ushort major, 
		const tiny_ubyte minor, 
		tiny_ubyte patch 
	);

	tiny_dll tiny_uint GetVersionMajor( const tiny_uint version );

	tiny_dll tiny_uint GetVersionMinor( const tiny_uint version );

	tiny_dll tiny_uint GetVersionPatch( const tiny_uint version );

};
