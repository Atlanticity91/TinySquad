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

#include "TinyNut.h"

////////////////////////////////////////////////////////////////////////////////////////////
// === PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyNut::TinyNut( const tiny_string& title )
	: TinyGame{ title, TGO_PAYSAGE_16x9 }
{ }

////////////////////////////////////////////////////////////////////////////////////////////
// === PROTECTED ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyNut::Initialize( TinyEngine& engine ) {
	auto& inputs  = engine.GetInputs( );
	auto& toolbox = engine.GetToolbox( );

	inputs.Erase( "Show Dev" );
	toolbox.Clear( );

	return Initialize( engine, toolbox );
}

void TinyNut::Tick( ) { 
	auto& graphics = GetGraphics( );

	graphics.BeginPass( TINY_OUTPASS_HASH );
	graphics.NextSubpass( );
}
