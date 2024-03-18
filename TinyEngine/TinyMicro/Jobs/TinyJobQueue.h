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

#define TINY_MAX_JOB 16

tm_class TinyJobQueue final {

private:
	std::mutex						  _mutex;
	tiny_uint						  _capacity;
	tiny_uint						  _head;
	tiny_uint						  _tail;
	tiny_array<TinyJob, TINY_MAX_JOB> _jobs;

public:
	TinyJobQueue( );

	~TinyJobQueue( ) = default;

	bool EnQueue( const TinyJob& job );

public:
	bool GetHasJob( ) const;

	bool DeQueue( TinyJob& job );

};
