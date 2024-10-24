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
 * @creation : 11/10/2023
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
TinyGame::TinyGame(
	const tiny_string& developer, 
	const tiny_string& title, 
	TinyGameOrientations orientation
)
	: TinyGame{ developer, title, orientation, false }
{ }

TinyGame::TinyGame( 
	const tiny_string& developer,
	const tiny_string& title,
	TinyGameOrientations orientation,
	bool is_headless
)
	: m_engine{ developer, title, orientation, is_headless }
{ }

bool TinyGame::Start( tiny_int argc, char** argv ) {
	auto state = m_engine.Initialize( this, argc, argv );

	if ( state ) {
		auto& graphics = m_engine.GetGraphics( );

		SetupBundles( graphics );

		graphics.ReCreate( );

		state = ProcessArguments( argc, argv ) && Initialize( );
	}

	if ( state )
		Load( );

	return state;
}

void TinyGame::Minimize( ) { m_engine.Minimize( ); }

void TinyGame::Restore( ) { m_engine.Restore( ); }

void TinyGame::Maximize( ) { m_engine.Maximize( ); }

void TinyGame::Stop( ) { m_engine.Stop( ); }

void TinyGame::DisableCache( ) { m_engine.DisableCache( ); }

void TinyGame::EnableCache( ) { m_engine.EnableCache( ); }

void TinyGame::Dispatch( const TinyJob& job ) { m_engine.Dispatch( job ); }

void TinyGame::SwitchGameState( TinyGame* game, const tiny_uint state_id ) {
	m_engine.Switch( game, state_id );
}

void TinyGame::SwitchGameState( TinyGame* game, const tiny_string& state_name ) {
	m_engine.Switch( game, state_name );
}

void TinyGame::SwitchGameState( TinyGame* game, const tiny_hash state_hash ) {
	m_engine.Switch( game, state_hash );
}

void TinyGame::Run( ) {
	while ( m_engine.GetShouldRun( ) ) {
		if ( m_engine.PreTick( this ) ) {
			Tick( );

			m_engine.PostTick( this );
		} else 
			tiny_sleep_for( 15 );
	}
}

void TinyGame::Close( ) {
	Terminate( );

	m_engine.Terminate( this );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PROTECTED ===
////////////////////////////////////////////////////////////////////////////////////////////
void TinyGame::DisableGameFolder( ) { m_engine.DisableGameFolder( ); }

bool TinyGame::ProcessArguments( tiny_int argc, char** argv ) { return true; }

void TinyGame::SetupBundles2D( TinyGraphicManager& graphics ) {
	auto bundle_2d = TinyGraphicRenderBundle{ };

	bundle_2d.Targets = 4;
	bundle_2d.Targets[ 0 ].Name = "Color 2D";
	bundle_2d.Targets[ 0 ].Type = TRT_TYPE_COLOR;
	bundle_2d.Targets[ 0 ].Clear = TinyPalettes::ASBESTOS;

	bundle_2d.Targets[ 1 ].Name  = "Position 2D";
	bundle_2d.Targets[ 1 ].Type  = TRT_TYPE_COLOR;
	bundle_2d.Targets[ 1 ].Clear = TinyPalettes::ASBESTOS;

	bundle_2d.Targets[ 2 ].Name  = "Normal 2D";
	bundle_2d.Targets[ 2 ].Type  = TRT_TYPE_COLOR;
	bundle_2d.Targets[ 2 ].Clear = TinyPalettes::ASBESTOS;

	bundle_2d.Targets[ 3 ].Name   = "Depth 2D";
	bundle_2d.Targets[ 3 ].Type   = TRT_TYPE_DEPTH;
	bundle_2d.Targets[ 3 ].Format = VK_FORMAT_D24_UNORM_S8_UINT;
	bundle_2d.Targets[ 3 ].Clear  = { .0f, 0 };

	bundle_2d.Passes = 1;
	bundle_2d.Passes[ 0 ].Type	  = TGR_TYPE_RENDER;
	bundle_2d.Passes[ 0 ].Stage	  = TGR_STAGE_BEGIN;
	bundle_2d.Passes[ 0 ].Targets = 3;
	bundle_2d.Passes[ 0 ].Targets[ 0 ] = { "Color 2D", TGR_ACCESS_WRITE };
	bundle_2d.Passes[ 0 ].Targets[ 1 ] = { "Position 2D", TGR_ACCESS_WRITE };
	bundle_2d.Passes[ 0 ].Targets[ 2 ] = { "Normal 2D", TGR_ACCESS_WRITE };
	bundle_2d.Passes[ 0 ].Targets[ 2 ] = { "Depth 2D", TGR_ACCESS_WRITE };

	graphics.AddBundle( "Render2DPass", bundle_2d );
}

void TinyGame::LoadDefault2D( TinyECS& ecs ) {
	ecs._eRegisterComp( TinyScript );
	ecs._eRegisterComp( TinyTransform2D );
	ecs._eRegisterComp( TinySound2D );
	ecs._eRegisterComp( TinyCamera );
	ecs._eRegisterComp( TinyAnim2D );
	ecs._eRegisterComp( TinySkin2D );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE ===
////////////////////////////////////////////////////////////////////////////////////////////
void TinyGame::Load( ) {
	auto& scripts = m_engine.GetScripts( );
	auto& context = scripts.GetContext( );
	auto& assets  = m_engine.GetAssets( );
	auto& ecs	  = m_engine.GetECS( );

	LoadInterop( context );
	LoadContent( assets );
	LoadECS( ecs );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyGame::GetIsRunning( ) const { return m_engine.GetIsRunning( ); }

TinyEngine& TinyGame::GetEngine( ) { return m_engine; }

TinyJobManager& TinyGame::GetJobs( ) { return m_engine.GetJobs( ); }

TinyFilesystem& TinyGame::GetFilesystem( ) { return m_engine.GetFilesystem( ); }

TinyAssetManager& TinyGame::GetAssets( ) { return m_engine.GetAssets( ); }

TinyWindow& TinyGame::GetWindow( ) { return m_engine.GetWindow( ); }

TinyInputManager& TinyGame::GetInputs( ) { return m_engine.GetInputs( ); }

TinyAudioManager& TinyGame::GetAudio( ) { return m_engine.GetAudio( ); }

TinyGraphicManager& TinyGame::GetGraphics( ) { return m_engine.GetGraphics( ); }

TinyNativeRegister& TinyGame::GetNatives( ) { return m_engine.GetNatives( ); }

TinyScriptManager& TinyGame::GetScripts( ) { return m_engine.GetScripts( ); }

TinyRenderer& TinyGame::GetRenderer( ) { return m_engine.GetRenderer( ); }

TinyECS& TinyGame::GetECS( ) { return m_engine.GetECS( ); }

TinySceneManager& TinyGame::GetScenes( ) { return m_engine.GetScenes( ); }

TinyUXManager& TinyGame::GetUX( ) { return m_engine.GetUX( ); }

TinyAddonManager& TinyGame::GetAddons( ) { return m_engine.GetAddons( ); }

TinyGameStateManager& TinyGame::GetGameStates( ) { return m_engine.GetGameStates( ); }

TinyDebugManager& TinyGame::GetDebug( ) { return m_engine.GetDebug( ); }

////////////////////////////////////////////////////////////////////////////////////////////
//		===	OPERATOR ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyGame::operator bool( ) const { return GetIsRunning( ); }
