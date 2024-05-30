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

#include "Tools/TinyToolbox.h"

te_class TinyEngine final {

private:
	bool			     _is_running;

	// === LOW LEVEL ===
	TinyJobManager		 _jobs;
	TinyFilesystem		 _filesystem;
	TinyAssetManager	 _assets;
	TinyWindow			 _window;
	TinyInputManager	 _inputs;
	TinyAudioManager	 _audio;
	TinyGraphicManager	 _graphics;
	TinyNativeRegister   _natives;

	// === MID LEVEL ===
	//TinyNetwork		 _network;
	TinyRenderer		 _renderer;
	TinyECS				 _ecs;

	// === HIGH LEVEL ===
	TinyUXManager		 _ux;
	TinyAddonManager	 _addons;
	TinyProviderManager	 _provider;
	TinyGameStateManager _states;
	TinyToolbox			 _toolbox;

public:
	/**
	 * Constructor
	 * @param developer : Game developer.
	 * @param title : Game window title.
	 * @param orientation : Desired game orientation for graphics adaptation.
	 * @param is_headless : Defined is the game window as OS decoration.
	 **/
	TinyEngine( 
		const tiny_string& developer,
		const tiny_string& title, 
		TinyGameOrientations orientation, 
		bool is_headless 
	);

	/**
	 * Destructor
	 **/
	~TinyEngine( ) = default;

	/**
	 * Initialize function
	 * @note : Initialize current engine instance.
	 * @param game : Pointer to current game class instance.
	 * @param argc : Executable argument count.
	 * @param argv : Executable argument value(s).
	 * @return : True for success.
	 **/
	bool Initialize( TinyGame* game, tiny_int argc, char** argv );

	/**
	 * Minimize method
	 * @note : Minimize current game window.
	 **/
	void Minimize( );

	/**
	 * Restore method
	 * @note : Restore current game window to previous un-minimized window state.
	 **/
	void Restore( );

	/**
	 * Maximize method
	 * @note : Maximize current game window.
	 **/
	void Maximize( );

	/**
	 * Stop method
	 * @note : Signal the game to shutdown.
	 **/
	void Stop( );

	void Dispatch( const TinyJob& job );

	void Switch( TinyGame* game, const tiny_uint state_id );

	void Switch( TinyGame* game, const tiny_string& state_name );

	void Switch( TinyGame* game, const tiny_hash state_hash );

	/**
	 * PreTick function
	 * @note : Called once per tick, before game tick. Perform tick pre-action.
	 * @param game : Pointer to current game class instance.
	 * @return : bool
	 **/
	bool PreTick( TinyGame* game );

	/**
	 * PreTick method
	 * @note : Called once per tick, after game tick. Perform tick post-action.
	 * @param game : Pointer to current game class instance.
	 **/
	void PostTick( TinyGame* game );

	/**
	 * Terminate method
	 * @note : Terminate current engine instance.
	 * @param game : Pointer to current game class instance.
	 **/
	void Terminate( TinyGame* game );

public:
	template<typename GameState>
		requires TinyIsGameState<GameState>
	void Register( const tiny_string& name ) {
		_states.Register<GameState>( name );
	};

private:
	/**
	 * PreInit function
	 * @note : Pre Initialize the current game engine instance.
	 * @param game : Pointer to current game class instance.
	 * @param game_config : Current game config instance.
	 **/
	bool PreInit( TinyGame* game, TinyConfig*& game_config );

	bool Init( TinyGame* game, const TinyConfig& config );

	/**
	 * PostInit function
	 * @note : Post Initialize the current game engine instance.
	 * @param game : Pointer to current game class instance.
	 **/
	bool PostInit( TinyGame* game );

	/**
	 * ProcessArgs function
	 * @note : Process arguments of the executable.
	 * @param game : Pointer to current game class instance.
	 * @param argc : Executable argument count.
	 * @param argv : Executable argument value(s).
	 * @return : True for success.
	 **/
	bool ProcessArgs( TinyGame* game, tiny_int argc, char** argv );

private:
	/**
	 * JobWorkerRun static method
	 * @note : Child Thread execution loop.
	 * @param filter : Current thread task type.
	 * @param game : Pointer to current game class instance.
	 * @param : Reference to current thread task queue.
	 **/
	static void JobWorkerRun( 
		const TinyJobFilters filter,
		native_pointer game,
		TinyJobQueue& queues 
	);

	/**
	 * Resize static method
	 * @note : GFLW Resize callback.
	 * @param handle : Current GLFW window handle.
	 * @param width  : New window width.
	 * @param height : New window height.
	 **/
	static void Resize( GLFWwindow* handle, tiny_int width, tiny_int height );

	/**
	 * Close static function
	 * @note : GFLW Close callback.
	 * @param handle : Current GLFW window handle.
	 **/
	static void Close( GLFWwindow* handle );

	/**
	 * ProcessKey static function
	 * @note : GFLW Key callback.
	 * @param handle   : Current GLFW window handle.
	 * @param key	   : GLFW key notification.
	 * @param scancode : Native OS scancode.
	 * @param action   : Key state.
	 * @param mods	   : Key modifier.
	 **/
	static void ProcessKey(
		GLFWwindow* handle, 
		tiny_int key, 
		tiny_int scancode,
		tiny_int action, 
		tiny_int mods 
	);
	
	/**
	 * ProcessCursor static method
	 * @note : GFLW Cursor callback.
	 * @param handle   : Current GLFW window handle.
	 * @param cursor_x : New cursor x value.
	 * @param cursor_y : New cursor y value.
	 **/
	static void ProcessCursor( GLFWwindow* handle, double cursor_x, double cursor_y );
	
	/**
	 * ProcessMouse static method
	 * @note : GFLW Mouse callback.
	 * @param handle : Current GLFW window handle.
	 * @param button : Mouse button.
	 * @param action : Button state.
	 * @param mods   : Button modifier.
	 **/
	static void ProcessMouse(
		GLFWwindow* handle, 
		tiny_int button, 
		tiny_int action, 
		tiny_int mods 
	);

	/**
	 * ProcessScroll static method
	 * @note : GFLW Scroll callback.
	 * @param handle : Current GLFW window handle.
	 * @param offset_x : New scroll x offset.
	 * @param offset_y : New scroll y offset.
	 **/
	static void ProcessScroll( GLFWwindow* handle, double offset_x, double offset_y );

public:
	/**
	 * GetIsRunning const function
	 * @note : Get if current engine instance is running.
	 * @return : True for success.
	 **/
	bool GetIsRunning( ) const;

	/**
	 * GetShouldRun const function
	 * @note : Get if current engine should run.
	 * @return : True for success.
	 **/
	bool GetShouldRun( ) const;

	/**
	 * GetJobs function
	 * @note : Get current job manager instance.
	 * @return : TinyJobManager
	 **/
	TinyJobManager& GetJobs( );

	/**
	 * GetFilesystem function
	 * @note : Get current file system instance.
	 * @return : TinyFilesystem
	 **/
	TinyFilesystem& GetFilesystem( );

	/**
	 * GetAssets function
	 * @note : Get current asset manager instance.
	 * @return : TinyAssetManager
	 **/
	TinyAssetManager& GetAssets( );

	/**
	 * GetWindow function
	 * @note : Get current window instance.
	 * @return : TinyWindow
	 **/
	TinyWindow& GetWindow( );

	/**
	 * GetInputs function
	 * @note : Get current input manager instance.
	 * @return : TinyInputManager
	 **/
	TinyInputManager& GetInputs( );

	/**
	 * GetAudio function
	 * @note : Get current audio manager instance.
	 * @return : TinyAudioManager
	 **/
	TinyAudioManager& GetAudio( );

	/**
	 * GetGraphics function
	 * @note : Get current graphic manager instance.
	 * @return : TinyGraphicManager
	 **/
	TinyGraphicManager& GetGraphics( );

	/**
	 * GetNatives function
	 * @note : Get current native function register instance.
	 * @return : TinyNativeRegister
	 **/
	TinyNativeRegister& GetNatives( );

	/**
	 * GetScripts function
	 * @note : Get current script manager instance.
	 * @return : TinyScriptManager
	 **/
	TinyScriptManager& GetScripts( );

	/**
	 * GetRenderer function
	 * @note : Get current renderer instance.
	 * @return : TinyRenderer
	 **/
	TinyRenderer& GetRenderer( );

	/**
	 * GetECS function
	 * @note : Get current entity component system instance.
	 * @return : TinyECS
	 **/
	TinyECS& GetECS( );

	/**
	 * GetScenes function
	 * @note : Get current scene manager instance.
	 * @return : TinySceneManager
	 **/
	TinySceneManager& GetScenes( );

	/**
	 * GetUX function
	 * @note : Get current UX manager instance.
	 * @return : TinyUXManager
	 **/
	TinyUXManager& GetUX( );

	/**
	 * GetAddons function
	 * @note : Get current addon manager instance.
	 * @return : TinyAddonManager
	 **/
	TinyAddonManager& GetAddons( );

	TinyGameStateManager& GetGameStates( );

	/**
	 * GetToolbox function
	 * @note : Get current toolbox instance.
	 * @return : TinyToolbox
	 **/
	TinyToolbox& GetToolbox( );

};
