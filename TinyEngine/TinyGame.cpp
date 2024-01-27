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
	: _engine{ title, orientation }
{ }

bool TinyGame::Start( tiny_int argc, char** argv ) {
	auto state = _engine.Initialize( this, argc, argv ) && 
				 ProcessArguments( argc, argv )		    &&
				 Initialize( _engine );

	if ( state )
		Load( );

	return state;
}

void TinyGame::Run( ) {
	while ( _engine.GetShouldRun( ) ) {
		_engine.PreTick( this );

		Tick( );

		_engine.PostTick( this );
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

void TinyGame::LoadDefault2D( TinyECS& ecs ) {
	ecs._RegisterComp( TinyScript );
	ecs._RegisterComp( TinyTransform2D );
	ecs._RegisterComp( TinySound2D );
	ecs._RegisterComp( TinyCamera );
	ecs._RegisterComp( TinyAnim2D );
	ecs._RegisterComp( TinySkin2D );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE ===
////////////////////////////////////////////////////////////////////////////////////////////
void TinyGame::Load( ) {
	auto& scripts = _engine.GetScripts( );
	auto& context = scripts.GetLua( );
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

TinyScriptManager& TinyGame::GetScripts( ) { return _engine.GetScripts( ); }

TinyRenderer& TinyGame::GetRenderer( ) { return _engine.GetRenderer( ); }

TinyECS& TinyGame::GetECS( ) { return _engine.GetECS( ); }

TinyAddonManager& TinyGame::GetAddons( ) { return _engine.GetAddons( ); }

TinyToolbox& TinyGame::GetToolbox( ) { return _engine.GetToolbox( ); }
