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

#pragma once

#include "TinyEngine.h"

te_abstract_class TinyGame {

protected:
	TinyEngine _engine;

public:
	TinyGame( const tiny_string& title, TinyGameOrientations orientation );

	virtual ~TinyGame( ) = default;

	bool Start( tiny_int argc, char** argv );

	void Run( );

	void Close( );

protected:
	virtual bool ProcessArguments( tiny_int argc, char** argv );

	tiny_virtualv( true, bool Initialize( TinyEngine& engine ) );
	
	tiny_virtual( void LoadInterop( TinyLuaContext& lua_context ) );

	tiny_virtual( void LoadContent( TinyAssetManager& assets ) );

	void LoadDefault2D( TinyECS& ecs );

	tiny_virtual( void LoadECS( TinyECS& ecs ) );

	tiny_virtual( void Tick( ) );

	tiny_virtual( void Terminate( ) );

private:
	void Load( );

public:
	TinyEngine& GetEngine( );

	tiny_inline TinyJobManager& GetJobs( );

	tiny_inline TinyFilesystem& GetFilesystem( );

	tiny_inline TinyAssetManager& GetAssets( );

	tiny_inline TinyWindow& GetWindow( );

	tiny_inline TinyInputManager& GetInputs( );

	tiny_inline TinyAudioManager& GetAudio( );

	tiny_inline TinyGraphicManager& GetGraphics( );

	tiny_inline TinyScriptManager& GetScripts( );

	tiny_inline TinyRenderer& GetRenderer( );
	
	tiny_inline TinyECS& GetECS( );

	tiny_inline TinyAddonManager& GetAddons( );
	
	tiny_inline TinyToolbox& GetToolbox( );

};
