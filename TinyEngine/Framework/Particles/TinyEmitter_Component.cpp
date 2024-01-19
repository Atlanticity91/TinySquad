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
 * @creation : 14/11/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#include <TinyEngine/__tiny_engine_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyEmitter::TinyEmitter( )
	: TinyEmitter{ TINY_NO_ENTITY }
{ }

TinyEmitter::TinyEmitter( const tiny_hash entity_hash )
	: TinyComponent{ entity_hash }
{ }

bool TinyEmitter::Create( TinyGame* game, TinyEngine& engine ) {
	return false;
}

void TinyEmitter::Delete( TinyGame* game, TinyEngine& engine ) {
}

void TinyEmitter::DisplayWidget(
	TinyGame* game,
	TinyEngine& engine,
	TinyToolbox& toolbox
) { 
	TinyComponent::DisplayWidget( game, engine, toolbox );
}
