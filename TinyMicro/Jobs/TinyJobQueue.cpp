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
 * @creation : 24/10/2023
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
TinyJobQueue::TinyJobQueue( ) 
    : _mutex{ },
    _capacity{ 0 },
	_head{ 0 },
	_tail{ 0 },
	_jobs{ }
{ }

bool TinyJobQueue::EnQueue( const TinyJob& job ) {
    _mutex.lock( );

    auto state = _capacity < TINY_MAX_JOB;

    if ( state ) {
        _capacity += 1;
        _tail = ( _tail + 1 ) % TINY_MAX_JOB;

        _jobs[ _tail ] = job;
    }

    _mutex.unlock( );

    return state;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyJobQueue::GetHasJob( ) const { return _capacity > 0; }

bool TinyJobQueue::DeQueue( TinyJob& job ) {
    _mutex.lock( );

    auto state = _capacity > 0;

    if ( state ) {
        _capacity -= 1;

        job = _jobs[ _head ];

        _head = ( _head + 1 ) % TINY_MAX_JOB;
    }

    _mutex.unlock( );

    return state;
}
