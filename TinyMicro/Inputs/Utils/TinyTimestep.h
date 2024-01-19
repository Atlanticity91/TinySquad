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
 * @creation : 11/10/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include <TinyMicro/Utils/ITinyManager.h>

tm_class TinyTimestep final {

	typedef std::chrono::duration<float> time_duration;
	typedef std::chrono::steady_clock time_clock;
	typedef std::chrono::time_point<time_clock> time_point;

private:
	time_point _game_start;
	time_point _game_tick;

public:
	TinyTimestep( );

	~TinyTimestep( ) = default;

	void Initialize( );

	void Tick( );

private:
	tiny_inline time_point Now( ) const;

public:
	float GetElapsed( ) const;

	float GetTotal( ) const;

};
