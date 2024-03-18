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
TinyThreadManager::TinyThreadManager( ) 
	: _threads{ }
{ }

bool TinyThreadManager::Create( TinyThreadRun thread_run, c_pointer data ) {
	auto state = !FAILED( CoInitializeEx( nullptr, COINIT_MULTITHREADED ) );

	if ( state ) {
		_threads = tiny_cast( std::thread::hardware_concurrency( ) / 2, tiny_uint );

		for ( auto& thread : _threads )
			thread.Create( thread_run, data );
	}

	return state;
}

void TinyThreadManager::Terminate( ) {
	for ( auto& thread : _threads )
		thread.Terminate( );

	CoUninitialize( );
}
