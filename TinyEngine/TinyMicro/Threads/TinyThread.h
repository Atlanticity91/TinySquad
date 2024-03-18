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
 * @creation : 23/10/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include <TinyMicro/Memory/TinyRef.h>

typedef std::function<void( c_pointer )> TinyThreadRun;

tm_class TinyThread final { 

private:
	std::thread _handle;

public:
	TinyThread( );

	TinyThread( const TinyThread& other );

	~TinyThread( ) = default;

	void Create( TinyThreadRun thread_run, c_pointer data );

	void Terminate( );

public:
	TinyThread& operator=( const TinyThread& other );

};
