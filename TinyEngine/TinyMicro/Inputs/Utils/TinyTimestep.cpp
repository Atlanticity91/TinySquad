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
	: m_game_start{ },
	m_game_tick{ }
{ }

void TinyTimestep::Initialize( ) {
	m_game_start = Now( );
	m_game_tick  = m_game_start;
}

void TinyTimestep::Tick( ) { m_game_tick = Now( ); }

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyTimestep::time_point TinyTimestep::Now( ) const { return time_clock::now( ); }

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
float TinyTimestep::GetElapsed( ) const { 
	auto now	  = Now( );
	auto duration = time_duration{ now - m_game_tick };

	return duration.count( );
}

float TinyTimestep::GetTotal( ) const { 
	auto now	  = Now( );
	auto duration = time_duration{ now - m_game_start };

	return duration.count( );
}
