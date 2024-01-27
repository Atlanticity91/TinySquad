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
 * @creation : 12/10/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#include <TinyMicro/__tiny_micro_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyTimestep::TinyTimestep( )
	: _game_start{ },
	_game_tick{ }
{ }

void TinyTimestep::Initialize( ) {
	_game_start = Now( );
	_game_tick  = _game_start;
}

void TinyTimestep::Tick( ) { _game_tick = Now( ); }

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyTimestep::time_point TinyTimestep::Now( ) const { return time_clock::now( ); }

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
float TinyTimestep::GetElapsed( ) const { 
	auto now	  = Now( );
	auto duration = time_duration{ now - _game_tick };

	return duration.count( );
}

float TinyTimestep::GetTotal( ) const { 
	auto now	  = Now( );
	auto duration = time_duration{ now - _game_start };

	return duration.count( );
}
