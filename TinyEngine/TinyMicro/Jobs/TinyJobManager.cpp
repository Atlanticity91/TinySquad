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

#include <TinyMicro/__tiny_micro_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyJobManager::TinyJobManager( ) 
	: _workers{ },
	_queues{ }
{ }

bool TinyJobManager::Initialize( native_pointer game, WorkerRun worker_run ) {
	auto state = Tiny::Initialize( );
	
	if ( state ) {
		printf( "THREAD COUNT : %u-%u\n", tiny_cast( std::thread::hardware_concurrency( ), tiny_uint ), TJ_FILTER_COUNT );

		auto thread_type = tiny_cast( 0, tiny_uint );

		for ( auto& worker : _workers )
			worker = std::thread( worker_run, tiny_cast( thread_type++, TinyJobFilters), game, std::ref( _queues ) );
	}

	return state;
}

void TinyJobManager::Dispatch( const TinyJob& job ) { 
	if ( job.Task )
		_queues.EnQueue( job ); 
}

void TinyJobManager::Wait( ) { while ( _queues.GetHasTask( ) ); }

void TinyJobManager::Terminate( ) {
	for ( auto& worker : _workers ) {
		if ( worker.joinable( ) )
			worker.join( );
	}

	Tiny::Terminate( );
}
