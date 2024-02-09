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

#include "Addons/TinyAddonManager.h"

te_class TinyEngine final {

private:
	bool			    _is_running;

	// === LOW LEVEL ===
	TinyJobManager		_jobs;
	TinyFilesystem		_filesystem;
	TinyAssetManager	_assets;
	TinyWindow			_window;
	TinyInputManager	_inputs;
	TinyAudioManager	_audio;
	TinyGraphicManager	_graphics;
	TinyNativeRegister  _natives;

	// === MID LEVEL ===
	TinyScriptManager   _scripts;
	//TinyLocalisation	_localisation;
	TinyRenderer		_renderer;
	TinyECS				_ecs;

	// === HIGH LEVEL ===
	//TinyUXManager		_ux;
	//TinySceneManager  _scenes; // load/unload ecs scene + renderer composer
	TinyProviderManager	_provider;
	TinyAddonManager	_addons;
	TinyToolbox			_toolbox;

public:
	/**
	 * Constructor
	 * @param title : Game window title.
	 * @param orientation : Desired game orientation for graphics adaptation.
	 **/
	TinyEngine( const tiny_string& title, TinyGameOrientations orientation );

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
	 * Stop method
	 * @note : Signal the game to shutdown.
	 **/
	void Stop( );

	/**
	 * PreTick method
	 * @note : Called once per tick, before game tick. Perform tick pre-action.
	 * @param game : Pointer to current game class instance.
	 **/
	void PreTick( TinyGame* game );

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

private:
	bool PreInit( TinyGame* game, TinyGameConfig& game_config );

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
	 * JobRun static method
	 * @note : Child Thread execution loop.
	 * @param game : Pointer to current game class instance.
	 **/
	static void JobRun( c_pointer game );

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
	 * GetAddons function
	 * @note : Get current addon manager instance.
	 * @return : TinyAddonManager
	 **/
	TinyAddonManager& GetAddons( );

	/**
	 * GetToolbox function
	 * @note : Get current toolbox instance.
	 * @return : TinyToolbox
	 **/
	TinyToolbox& GetToolbox( );

};
