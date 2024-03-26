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

#include <TinyFoundry/__tiny_foundry_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
// === PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyFoundry::TinyFoundry( )
	: TinyGame{ "Tiny Foundry", TGO_PAYSAGE_16x9 }
{ }

////////////////////////////////////////////////////////////////////////////////////////////
// === PROTECTED ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyFoundry::Initialize( TinyEngine& engine ) { return true; }

void TinyFoundry::SetupBundles( TinyGraphicManager& graphics ) { }

void TinyFoundry::LoadInterop( TinyLuaContext& lua_context ) { }

void TinyFoundry::LoadContent( TinyAssetManager& assets ) { }

void TinyFoundry::LoadECS( TinyECS& ecs ) { }

void TinyFoundry::Tick( ) { 
	auto& graphics = GetGraphics( );

	graphics.BeginPass( TINY_OUTPASS_HASH );
	graphics.NextSubpass( );
}

void TinyFoundry::Terminate( ) { }
