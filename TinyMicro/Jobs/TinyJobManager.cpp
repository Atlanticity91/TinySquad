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
	: _threads{ },
	_queues{ }
{ }

bool TinyJobManager::Initialize( TinyThreadRun thread_run, c_ptr data ) {
	return _threads.Create( thread_run, data );
}

bool TinyJobManager::Dispatch( const TinyJob& job ) {
	return _queues.EnQueue( job );
}

void TinyJobManager::Wait( ) { _queues.Wait( ); }

void TinyJobManager::Terminate( ) {
	_threads.Terminate( );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyJobManager::DeQueue( TinyJob& job ) { return _queues.DeQueue( job ); }
