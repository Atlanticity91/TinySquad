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
 * @creation : 16/12/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "TinyGame.h"

/**
 * TINY_GAME_ENTRY_IMP macro
 * @param GAME : Game class instance type name.
 * @param MEM_SIZE : Total Game Memory size ( can be inferior if size exceed memory 
 *					 capacity )
 **/
#define TINY_GAME_ENTRY_IMP( GAME, MEM_SIZE )\
	tiny_int main( tiny_int argc, char** argv ) {\
		if ( tiny_initialize( MEM_SIZE ) ) {\
			auto* game = new GAME( );\
			if ( game ) {\
				if ( game->Start( argc, argv ) )\
					game->Run( );\
				game->Close( );\
				delete game;\
			}\
		}\
	}
