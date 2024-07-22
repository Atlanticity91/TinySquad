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
 * @creation : 23/02/2024
 * @version  : 2024.2.3
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#include <TinyEngine/__tiny_engine_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyECSDispatch::TinyECSDispatch( ) 
	: m_callbacks{ }
{ }

void TinyECSDispatch::Register( tiny_uint type, native_pointer callback ) {
	Register( type, { callback } );
}

void TinyECSDispatch::Register( tiny_uint type, tiny_init<native_pointer> callbacks ) {
	if ( type >= m_callbacks.size( ) )
		m_callbacks.create_back( type );

	m_callbacks[ type ].append_back( callbacks );
}
