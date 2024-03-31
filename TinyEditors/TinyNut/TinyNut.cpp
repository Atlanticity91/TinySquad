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
 * @creation : 26/03/2024
 * @version  : 2024.2.7
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#include <TinyNut/__tiny_nut_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
// === PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyNut::TinyNut( const tiny_string& title )
	: TinyGame{ title, TGO_PAYSAGE_16x9, true },
	_context{ },
	_window{ title }
{ }

////////////////////////////////////////////////////////////////////////////////////////////
// === PROTECTED ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyNut::Initialize( TinyEngine& engine ) {
	auto state = _context.Create( this );
	
	if ( state )
		_window.Create( this );

	return state;
}

void TinyNut::Tick( ) {
	_context.Prepare( this );
	_window.Tick( this );
	_context.Flush( this );
}

void TinyNut::Terminate( ) {
	_window.Terminate( this );
	_context.Terminate( this );
}

////////////////////////////////////////////////////////////////////////////////////////////
// === PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyNutContext& TinyNut::GetNutContext( ) { return _context; }

TinyNutWindow& TinyNut::GetNutWindow( ) { return _window; }
