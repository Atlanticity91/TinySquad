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
	: TinyGame( "Game Title", TinyGameOrientations::TGO_PAYSAGE_16x9 )
{ }

////////////////////////////////////////////////////////////////////////////////////////////
// === PROTECTED ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyProduction::Initialize( TinyEngine& engine ) {
	// CUSTOM INIT CODE HERE 
	return true; 
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
	LoadDefault2D( ecs );
}

void TinyProduction::Tick( ) {
	// CUSTOM GAME TICK CODE HERE

	if ( GetEngine( ).GetInputs( ).Evaluate( "Show Dev", false ) ) {
		auto p = (TinyMaterialBuilder)GetEngine( ).GetGraphics( ).CreatePipeline( TGP_TYPE_2D, "OutPass", 0 );

		p.InputBinding.clear( );
		p.InputAttributes.clear( );

		p.PassName = "OutPass";
		p.ShaderStages = 2;
		p.ShaderStages[ 0 ] = "s_test_v";
		p.ShaderStages[ 1 ] = "s_test_f";

		p.Descriptors = 3;
		p.Descriptors[ 0 ] = 1;
		p.Descriptors[ 1 ] = 2;
		p.Descriptors[ 2 ] = 1;

		_TinyCreateSetBind( p.Descriptors[ 0 ], 0, TGBP_TYPE_UNIFORM, TGS_STAGE_VERTEX );
		_TinyCreateSetBind( p.Descriptors[ 1 ], 0, TGBP_TYPE_UNIFORM, TGS_STAGE_VERTEX );
		_TinyCreateSetBind( p.Descriptors[ 1 ], 1, TGBP_TYPE_UNIFORM, TGS_STAGE_VERTEX );
		_TinyCreateSetBind( p.Descriptors[ 2 ], 0, TGBP_TYPE_COMBINED, TGS_STAGE_FRAGMENT );

		auto* pp = (c_pointer)&p;

		GetEngine( ).GetAssets( ).Export( this, TA_TYPE_MATERIAL, "Dev\\m_test.tinyasset", pp );
	}
}

void TinyProduction::Terminate( ) {
	// CUSTOM TERMINATE CODE HERE
}
