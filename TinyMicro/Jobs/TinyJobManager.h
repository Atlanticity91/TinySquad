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

#include "TinyJobQueueManager.h"

tm_class TinyJobManager final {

private:
	TinyThreadManager   _threads;
	TinyJobQueueManager _queues;

public:
	TinyJobManager( );

	~TinyJobManager( ) = default;

	bool Initialize( TinyThreadRun thread_run, c_ptr data );

	bool Dispatch( const TinyJob& job );

	void Wait( );

	void Terminate( );

public:
	bool DeQueue( TinyJob& job );

};
