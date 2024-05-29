/******************************************************************************************
 * 
 * @author   : ALVES Quentin
 * @creation : 19/01/2024
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Game Production template for Tiny Engine usage.
 *
 ******************************************************************************************/

#include <TinyProduction/__tiny_production_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
// === PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyProduction::TinyProduction( ) 
	: TinyGame( "TinySquadStudio", "Game Title", TinyGameOrientations::TGO_PAYSAGE_16x9 )
{ }

////////////////////////////////////////////////////////////////////////////////////////////
// === PROTECTED ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyProduction::Initialize( TinyEngine& engine ) {
	// CUSTOM INIT CODE HERE 
	return true; 
}

void TinyProduction::SetupBundles( TinyGraphicManager& graphics ) {
	// DEFAULT RENDER PASS BUNDLES
	// SETUP DEFAULT 2D CONFIGURATION
	TinyGame::SetupBundles2D( graphics );
}

void TinyProduction::LoadInterop( TinyLuaContext& lua_context ) {
	// CUSTOM LUA-C++ INTEROP CODE HERE
}

void TinyProduction::LoadContent( TinyAssetManager& assets ) {
	// DEFAULT LOADED CONTENT COD HERE
}

void TinyProduction::LoadECS( TinyECS& ecs ) {
	// DEFAULT ECS SETUP CODE HERE
	// LOAD DEFAULT 2D CONFIGURATION
	TinyGame::LoadDefault2D( ecs );
}

void TinyProduction::Tick( ) {
	// CUSTOM GAME TICK CODE HERE
}

void TinyProduction::Terminate( ) {
	// CUSTOM TERMINATE CODE HERE
}
