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

#include <TinyEditor/__tiny_edittor_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
// === PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyEditor::TinyEditor( )
	: TinyGame{ "Tiny Editor", TGO_PAYSAGE_16x9 }
{ }

////////////////////////////////////////////////////////////////////////////////////////////
// === PROTECTED ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyEditor::Initialize( TinyEngine& engine ) { return true; }

void TinyEditor::SetupBundles( TinyGraphicManager& graphics ) { }

void TinyEditor::LoadInterop( TinyLuaContext& lua_context ) { }

void TinyEditor::LoadContent( TinyAssetManager& assets ) { }

void TinyEditor::LoadECS( TinyECS& ecs ) { }

void TinyEditor::Tick( ) { 
	auto& graphics = GetGraphics( );

	graphics.BeginPass( TINY_OUTPASS_HASH );
	graphics.NextSubpass( );
}

void TinyEditor::Terminate( ) { }
