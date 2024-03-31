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
TinyGame::TinyGame( const tiny_string& title, TinyGameOrientations orientation )
	: TinyGame{ title, orientation, false }
{ }

TinyGame::TinyGame( 
	const tiny_string& title,
	TinyGameOrientations orientation,
	bool is_headless
)
	: _engine{ title, orientation, is_headless }
{ }

bool TinyGame::Start( tiny_int argc, char** argv ) {
	auto state = _engine.Initialize( this, argc, argv );

	if ( state ) {
		auto& graphics = _engine.GetGraphics( );

		SetupBundles( graphics );

		graphics.ReCreate( );

		state = ProcessArguments( argc, argv ) && Initialize( _engine );
	}

	if ( state )
		Load( );

	return state;
}

void TinyGame::Minimize( ) { _engine.Minimize( ); }

void TinyGame::Restore( ) { _engine.Restore( ); }

void TinyGame::Maximize( ) { _engine.Maximize( ); }

void TinyGame::Stop( ) { _engine.Stop( ); }

void TinyGame::Run( ) {
	while ( _engine.GetShouldRun( ) ) {
		if ( _engine.PreTick( this ) ) {
			Tick( );

			_engine.PostTick( this );
		} else 
			tiny_sleep_for( 15 );
	}
}

void TinyGame::Close( ) {
	Terminate( );

	_engine.Terminate( this );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PROTECTED ===
////////////////////////////////////////////////////////////////////////////////////////////
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
	auto& scripts = _engine.GetScripts( );
	auto& context = scripts.GetContext( );
	auto& assets  = _engine.GetAssets( );
	auto& ecs	  = _engine.GetECS( );

	LoadInterop( context );
	LoadContent( assets );
	LoadECS( ecs );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyEngine& TinyGame::GetEngine( ) { return _engine; }

TinyJobManager& TinyGame::GetJobs( ) { return _engine.GetJobs( ); }

TinyFilesystem& TinyGame::GetFilesystem( ) { return _engine.GetFilesystem( ); }

TinyAssetManager& TinyGame::GetAssets( ) { return _engine.GetAssets( ); }

TinyWindow& TinyGame::GetWindow( ) { return _engine.GetWindow( ); }

TinyInputManager& TinyGame::GetInputs( ) { return _engine.GetInputs( ); }

TinyAudioManager& TinyGame::GetAudio( ) { return _engine.GetAudio( ); }

TinyGraphicManager& TinyGame::GetGraphics( ) { return _engine.GetGraphics( ); }

TinyNativeRegister& TinyGame::GetNatives( ) { return _engine.GetNatives( ); }

TinyScriptManager& TinyGame::GetScripts( ) { return _engine.GetScripts( ); }

TinyRenderer& TinyGame::GetRenderer( ) { return _engine.GetRenderer( ); }

TinyECS& TinyGame::GetECS( ) { return _engine.GetECS( ); }

TinyAddonManager& TinyGame::GetAddons( ) { return _engine.GetAddons( ); }

TinyToolbox& TinyGame::GetToolbox( ) { return _engine.GetToolbox( ); }
