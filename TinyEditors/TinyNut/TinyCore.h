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
 * @creation : 26/03/2024
 * @version  : 2024.2.7
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include <TinyEngine/TinyGameEntry.h>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// HELPER'S
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef _WIN64
#	ifdef TN_BUILD
#		define tiny_nut_dll __declspec( dllexport )
#		pragma message( "Defining tiny_nut_dll as export" )
#	else
#		define tiny_nut_dll __declspec( dllimport )
#		pragma message( "Defining tiny_nut_dll as import" )
#	endif
#else
#	define tiny_nut_dll
#endif

#define tiny_nut_class class tiny_nut_dll
#define tiny_nut_struct struct tiny_nut_dll
