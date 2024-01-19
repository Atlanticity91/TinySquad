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
TinyJobQueueManager::TinyJobQueueManager( )
	: _high{ },
	_normal{ },
	_low{ }
{ }

bool TinyJobQueueManager::EnQueue( const TinyJob& job ) {
	auto state = false;

	switch ( job.Priority ) {
		case TJ_PRIORITY_HIGH   : state = _high.EnQueue( job );   break;
		case TJ_PRIORITY_NORMAL : state = _normal.EnQueue( job ); break;
		case TJ_PRIORITY_LOW	: state = _low.EnQueue( job );	  break;

		default : break;
	}

	return state;
}

void TinyJobQueueManager::Wait( ) {
	while ( _high.GetHasJob( ) && _normal.GetHasJob( ) );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyJobQueueManager::DeQueue( TinyJob& job ) {
	auto state = false;

	if ( _high.GetHasJob( ) )
		state = _high.DeQueue( job );

	if ( !state && _normal.GetHasJob( ) )
		state = _normal.DeQueue( job );

	if ( !state && _low.GetHasJob( ) )
		state = _low.DeQueue( job );

	return state;
}
