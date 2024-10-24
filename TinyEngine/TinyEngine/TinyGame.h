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
	TinyEngine m_engine;

public:
	/**
	 * Constructor
	 * @param developer : Game developer.
	 * @param title : Game window title.
	 * @param orientation : Desired game orientation for graphics adaptation.
	 **/
	TinyGame( 
		const tiny_string& developer, 
		const tiny_string& title,
		TinyGameOrientations orientation 
	);

	/**
	 * Constructor
	 * @param developer : Game developer.
	 * @param title : Game window title.
	 * @param orientation : Desired game orientation for graphics adaptation.
	 * @param is_headless : Defined is the game window as OS decoration.
	 **/
	TinyGame( 
		const tiny_string& developer,
		const tiny_string& title, 
		TinyGameOrientations orientation,
		bool is_headless
	);

	/**
	 * Destructor
	 **/
	virtual ~TinyGame( ) = default;
	
	/**
	 * Start function
	 * @note : Get current engine instance.
	 * @param argc : Current argument count.
	 * @param argv : Current argument values.
	 * @return : bool
	 **/
	bool Start( tiny_int argc, char** argv );

	/**
	 * Minimize method
	 * @note : Minimize current game window.
	 **/
	tiny_inline void Minimize( );

	/**
	 * Restore method
	 * @note : Restore current game window to previous un-minimized window state.
	 **/
	tiny_inline void Restore( );

	/**
	 * Maximize method
	 * @note : Maximize current game window.
	 **/
	tiny_inline void Maximize( );

	/**
	 * Stop method
	 * @note : Signal the game to shutdown.
	 **/
	tiny_inline void Stop( );

	/**
	 * DisableCache method
	 * @note : Disable Graphic cache file loading and saving.
	 **/
	tiny_inline void DisableCache( );

	/**
	 * EnableCache method
	 * @note : Enable Graphic cache file loading and saving.
	 **/
	tiny_inline void EnableCache( );

	/**
	 * Dispatch method
	 * @note : Disaptch job to current job manager.
	 * @param job : Job instance to disaptch.
	 **/
	tiny_inline void Dispatch( const TinyJob& job );

	tiny_inline void SwitchGameState( TinyGame* game, const tiny_uint state_id );

	tiny_inline void SwitchGameState( TinyGame* game, const tiny_string& state_name );

	tiny_inline void SwitchGameState( TinyGame* game, const tiny_hash state_hash );

	/**
	 * Run method
	 * @note : Run the current game.
	 **/
	void Run( );

	/**
	 * Close method
	 * @note : Close current game.
	 **/
	void Close( );

public:
	/**
	 * RegisterGameState template method
	 * @note : Register new game state class to current game state manager.
	 * @template GameState : Game State class only child of TinyGameState.
	 * @param name : Name of the new game state, name is not part of the class
	 *				 so multiple state can use class if needed.
	 **/
	template<typename GameState>
		requires TinyIsGameState<GameState>
	void RegisterGameState( const tiny_string& name ) {
		m_engine.Register<GameState>( name );
	};

protected:
	/**
	 * DisableGameFolder method
	 * @note : Disable the creation and access to default game folder over the api,
	 *		   most use are for Nut Tool.
	 **/
	void DisableGameFolder( );

	/**
	 * ProcessArguments function
	 * @note : Process passed argument.
	 * @param argc : Current argument count.
	 * @param argv : Current argument values.
	 * @return : bool
	 **/
	virtual bool ProcessArguments( tiny_int argc, char** argv );

	/**
	 * SetupBundles method
	 * @note : Setup graphic bundle for rendering.
	 * @param graphics : Default Graphic manager instance.
	 **/
	tiny_virtual( void SetupBundles( TinyGraphicManager& graphics ) );

	/**
	 * SetupBundles method
	 * @note : Default 2D graphic bundle for rendering.
	 * @param graphics : Default Graphic manager instance.
	 **/
	void SetupBundles2D( TinyGraphicManager& graphics );

	/**
	 * Initialize function
	 * @note : Initialize current game instance.
	 * @return : bool
	 **/
	tiny_virtualv( true, bool Initialize( ) );
	
	/**
	 * LoadInterop method
	 * @note : Load game LUA Inter-Operation.
	 * @param lua_context : Current LUA context instance.
	 **/
	tiny_virtual( void LoadInterop( TinyLuaContext& lua_context ) );

	/**
	 * LoadContent method
	 * @note : Load game default content.
	 * @param assets : Current asset manager instance.
	 **/
	tiny_virtual( void LoadContent( TinyAssetManager& assets ) );

	/**
	 * LoadDefault2D method
	 * @note : Load default 2D ECS components and systems.
	 * @param ecs : Current ECS instance.
	 **/
	void LoadDefault2D( TinyECS& ecs );

	/**
	 * LoadECS method
	 * @note : Load default game ECS configuration.
	 * @param ecs : Current ECS instance.
	 **/
	tiny_virtual( void LoadECS( TinyECS& ecs ) );

	/**
	 * Tick method
	 * @note : Tick current game.
	 **/
	tiny_virtual( void Tick( ) );

	/**
	 * Terminate method
	 * @note : Terminate current game.
	 **/
	tiny_virtual( void Terminate( ) );

private:
	/**
	 * Load method
	 * @note : Load Default ECS, Content & LUA Inter-Operation.
	 **/
	void Load( );

public:
	/**
	 * GetIsRunning const virtual function
	 * @note : Get if current engine instance is running.
	 * @return : True for success.
	 **/
	virtual bool GetIsRunning( ) const;

	/**
	 * GetEngine function
	 * @note : Get current engine instance.
	 * @return : TinyEngine
	 **/
	TinyEngine& GetEngine( );

	/**
	 * GetJobs function
	 * @note : Get current job manager instance.
	 * @return : TinyJobManager
	 **/
	tiny_inline TinyJobManager& GetJobs( );

	/**
	 * GetFilesystem function
	 * @note : Get current file system instance.
	 * @return : TinyFilesystem
	 **/
	tiny_inline TinyFilesystem& GetFilesystem( );

	/**
	 * GetAssets function
	 * @note : Get current asset manager instance.
	 * @return : TinyAssetManager
	 **/
	tiny_inline TinyAssetManager& GetAssets( );

	/**
	 * GetWindow function
	 * @note : Get current window instance.
	 * @return : TinyWindow
	 **/
	tiny_inline TinyWindow& GetWindow( );
	
	/**
	 * GetInputs function
	 * @note : Get current input manager instance.
	 * @return : TinyInputManager
	 **/
	tiny_inline TinyInputManager& GetInputs( );

	/**
	 * GetAudio function
	 * @note : Get current audio manager instance.
	 * @return : TinyAudioManager
	 **/
	tiny_inline TinyAudioManager& GetAudio( );

	/**
	 * GetGraphics function
	 * @note : Get current graphic manager instance.
	 * @return : TinyGraphicManager
	 **/
	tiny_inline TinyGraphicManager& GetGraphics( );

	/**
	 * GetNatives function
	 * @note : Get current native function register instance.
	 * @return : TinyNativeRegister
	 **/
	tiny_inline TinyNativeRegister& GetNatives( );

	/**
	 * GetScripts function
	 * @note : Get current script manager instance.
	 * @return : TinyScriptManager
	 **/
	tiny_inline TinyScriptManager& GetScripts( );

	/**
	 * GetRenderer function
	 * @note : Get current renderer instance.
	 * @return : TinyRenderer
	 **/
	tiny_inline TinyRenderer& GetRenderer( );
	
	/**
	 * GetECS function
	 * @note : Get current entity component system instance.
	 * @return : TinyECS
	 **/
	tiny_inline TinyECS& GetECS( );

	/**
	 * GetScenes function
	 * @note : Get current scene manager instance.
	 * @return : TinySceneManager
	 **/
	tiny_inline TinySceneManager& GetScenes( );

	/**
	 * GetUX function
	 * @note : Get current UX manager instance.
	 * @return : TinyUXManager
	 **/
	tiny_inline TinyUXManager& GetUX( );

	/**
	 * GetAddons function
	 * @note : Get current addon manager instance.
	 * @return : TinyAddonManager
	 **/
	tiny_inline TinyAddonManager& GetAddons( );
	
	tiny_inline TinyGameStateManager& GetGameStates( );

	/**
	 * GetDebug function
	 * @note : Get current toolbox instance.
	 * @return : TinyDebugManager
	 **/
	tiny_inline TinyDebugManager& GetDebug( );

public:
	/**
	 * cast operator
	 * @note : Equivalent of calling GetIsRunning( ), return if the game is still running.
	 * @return : bool
	 **/
	operator bool( ) const;

};
