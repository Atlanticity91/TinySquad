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
    : _mutex_guard{ },
    _condition_guard{ },
    _queues{ }
{ }

void TinyJobQueue::EnQueue( const TinyJob& job ) {
    _mutex_guard.lock( );

    auto& queue = _queues[ job.Priority ];
    
    queue.enqueue( job );

    _mutex_guard.unlock( );
}

void TinyJobQueue::DeQueue( const TinyJobPriorities priority, TinyJob& job ) {
    _mutex_guard.lock( );

    auto& queue = _queues[ priority ];
    auto task   = queue.dequeue( );
    auto task_job = task.value( );

    Tiny::Memcpy( task_job, job );

    _mutex_guard.unlock( );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyJobQueue::GetHasTask( ) const {
    auto task_count = tiny_cast( 0, tiny_uint );

    _mutex_guard.lock( );

    for ( auto& queue: _queues )
        task_count += queue.size( );

    _mutex_guard.unlock( );

    return task_count > 0;
}

bool TinyJobQueue::GetHasJob( 
    const TinyJobFilters filter, 
    TinyJobPriorities& priority 
) const { 
    auto state = false;

    _mutex_guard.lock( );

    for ( auto& queue : _queues ) {
        auto* task = queue.peek( );

        state = task != nullptr && task->Filter == filter;

        if ( state ) {
            priority = task->Priority;

            break;
        }
    }

    _mutex_guard.unlock( );

    return state;
}
