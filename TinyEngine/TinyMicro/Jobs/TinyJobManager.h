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

#include "TinyJobQueue.h"

tm_class TinyJobManager final{

	using WorkerRun = std::function<void( const TinyJobFilters, native_pointer, TinyJobQueue& )>;

private:
	std::thread m_workers[ TJ_FILTER_COUNT ];
	TinyJobQueue m_queues;

public:
	TinyJobManager( );

	~TinyJobManager( ) = default;

	bool Initialize( native_pointer game, WorkerRun worker_run );

	void Dispatch( const TinyJob& job );

	void Wait( );

	void Terminate( );

};
