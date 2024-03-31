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
 * @creation : 31/03/2024
 * @version  : 2024.2.7
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once 

#include <TinyEngine/TinyGameEntry.h>

#ifdef _WIN32
#	ifdef TN_BUILD
#		define tiny_nut_dll __declspec( dllexport )
#	else
#		define tiny_nut_dll __declspec( dllimport )
#	endif
#else
#	define tiny_nut_dll
#endif

#define tn_struct struct tiny_nut_dll
#define tn_class class tiny_nut_dll
