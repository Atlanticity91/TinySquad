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
 * @creation : 28/03/2024
 * @version  : 2024.2.7
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#include <TinyEngine/__tiny_engine_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyToolWindowManager::TinyToolWindowManager( )
	: _windows{ }
{ }

void TinyToolWindowManager::Show( const tiny_string& name ) {
	auto* window = Get( name );

	if ( window )
		window->Show( );
}

void TinyToolWindowManager::Hide( const tiny_string& name ) {
	auto* window = Get( name );

	if ( window )
		window->Hide( );
}

void TinyToolWindowManager::Delete( 
	TinyGame* game, 
	TinyToolbox& toolbox, 
	const tiny_string& name
) {
	auto window_id = tiny_cast( 0, tiny_uint );
	auto* window   = tiny_cast( nullptr, TinyToolWindow* );

	if ( _windows.find( name, window_id ) ) {
		window = _windows.at( window_id );

		window->Delete( game, toolbox );

		_windows.erase( window_id );
	}
}

void TinyToolWindowManager::Tick( TinyGame* game, TinyToolbox& toolbox ) { 
	for ( auto& pair : _windows ) {
		auto& window = pair.Data;

		if ( window->GetIsVisible( ) )
			window->Tick( game, toolbox );
	}
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyToolWindow* TinyToolWindowManager::Get( const tiny_string& name ) const {
	auto window_id = tiny_cast( 0, tiny_uint );
	auto* window   = tiny_cast( nullptr, TinyToolWindow* );

	if ( _windows.find( name, window_id ) )
		window = _windows.at( window_id );

	return window;
}
