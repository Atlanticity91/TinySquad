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

#include "TinyJob.h"

tm_class TinyJobQueue final {

	static const tiny_uint MaxJobs = 16;

	using JobQueue = tiny_queue<TinyJob, MaxJobs>;

private:
	mutable std::mutex m_mutex_guard;
	std::condition_variable m_condition_guard;
	tiny_array<JobQueue, TJ_PRIORITY_COUNT> m_queues;

public:
	TinyJobQueue( );

	~TinyJobQueue( ) = default;

	void EnQueue( const TinyJob& job );

	void DeQueue( const TinyJobPriorities priority, TinyJob& job );

public:
	bool GetHasTask( ) const;

	bool GetHasJob( const TinyJobFilters filter, TinyJobPriorities& priority ) const;

};
