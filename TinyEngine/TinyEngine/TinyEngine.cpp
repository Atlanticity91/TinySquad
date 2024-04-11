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
TinyEngine::TinyEngine(
	const tiny_string& title,
	TinyGameOrientations orientation, 
	bool is_headless 
)
	: _is_running{ true },
	_jobs{ },
	_filesystem{ },
	_assets{ },
	_window{ title, is_headless },
	_inputs{ },
	_audio{ },
	_graphics{ orientation },
	_natives{ },
	//_localisation{ },
	_renderer{ },
	_ecs{ },
	//_ux{ },
	//_scenes{ },
	_addons{ },
	_provider{ },
	_toolbox{ },
	_scripts{ nullptr }
{ }

bool TinyEngine::Initialize( TinyGame* game, tiny_int argc, char** argv ) {
	auto* game_config = tiny_cast( nullptr, TinyConfig* );
	
	_is_running = PreInit( game, game_config );

	if ( _is_running ) {
		_is_running = _window.Initialize( tiny_lvalue( game_config ), tiny_cast( this, c_pointer ) ) &&
					  _inputs.Initialize( _filesystem, _window )									 &&
					  _audio.Initialize( _filesystem, _window )										 &&
					  _graphics.Initialize( _filesystem, _window );

		if ( _is_running ) {
			_is_running = PostInit( game )				  && 
						  ProcessArgs( game, argc, argv );

			if ( _is_running && !_window.GetIsHeadless( ) ) {
				_inputs.Register( 
					"Show Dev", 
					{ 
						{ TinyInputKey( KEY_F1 ), TI_STATE_PRESSED, TI_MODIFIER_UNDEFINED },
						{ TinyInputKey( KEY_GRAVE_ACCENT ), TI_STATE_PRESSED, TI_MODIFIER_UNDEFINED },
					} 
				);
			}
		}
	}

	return _is_running;
}

void TinyEngine::Minimize( ) { _window.Minimize( ); }

void TinyEngine::Restore( ) { _window.Restore( ); }

void TinyEngine::Maximize( ) { _window.Maximize( ); }

void TinyEngine::Stop( ) { _is_running = false; }

bool TinyEngine::PreTick( TinyGame* game ) {
	auto state = _window.Tick( );

	_scripts = _assets.GetContainerAs<TinyScriptManager>( TA_TYPE_SCRIPT );

	if ( state ) {
		_addons.PreTick( game );
		_ecs.PreTick( game );
		_graphics.Acquire( _window );
	}

	return state;
}

void TinyEngine::PostTick( TinyGame* game ) {
	_addons.PostTick( game );
	_ecs.PostTick( game );
	//_ux.Tick( game );
	_audio.Tick( _inputs );
	_renderer.Compose( game );
	_toolbox.Tick( game );
	_graphics.Present( _window );
	_inputs.Tick( );
}

void TinyEngine::Terminate( TinyGame* game ) {
	_toolbox.Terminate( game );
	_provider.Terminate( _filesystem );
	_addons.Terminate( game );
	_scripts->Terminate( );
	_renderer.Terminate( _graphics );
	_assets.Terminate( game );
	_graphics.Terminate( _filesystem, _window );
	_audio.Terminate( _filesystem, _window );
	_inputs.Terminate( _filesystem, _window );
	_window.Terminate( );
	_filesystem.Terminate( );
	_jobs.Terminate( );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyEngine::PreInit( TinyGame* game, TinyConfig*& game_config ) {
	auto state = _jobs.Initialize( TinyEngine::JobRun, game ) &&
				 _filesystem.Initialize( _window )			 &&
				 _assets.Initialize( _filesystem, game_config );

	if ( state ) {
		auto& addons = GetAddons( );

		state = addons.Initialize( game );
	}

	return state;
}

bool TinyEngine::PostInit( TinyGame* game ) {
	_window.SetCallback( TWC_WINDOW_SIZE , TinyEngine::Resize		 );
	_window.SetCallback( TWC_WINDOW_CLOSE, TinyEngine::Close		 );
	_window.SetCallback( TWC_KEY		 , TinyEngine::ProcessKey	 );
	_window.SetCallback( TWC_CURSOR		 , TinyEngine::ProcessCursor );
	_window.SetCallback( TWC_MOUSE		 , TinyEngine::ProcessMouse  );
	_window.SetCallback( TWC_SCROLL		 , TinyEngine::ProcessScroll );

	return  _renderer.Initialize( _graphics, _filesystem ) &&
			_provider.Initialize( _filesystem )			   &&
			_toolbox.Initialize( game );
}

bool TinyEngine::ProcessArgs( TinyGame* game, tiny_int argc, char** argv ) { return true; }

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE STATIC ===
////////////////////////////////////////////////////////////////////////////////////////////
void TinyEngine::JobRun( c_pointer game ) {
	auto* _game  = tiny_cast( game, TinyGame* );
	auto& engine = _game->GetEngine( );

	while ( engine.GetIsRunning( ) ) {
		TinyJob job;
		
		if ( engine.GetJobs( ).DeQueue( job ) ) {
			auto result = std::invoke( job.Execute, job.Data, game );

			if ( result && job.Success )
				std::invoke( job.Success, job.Data, game );
			else if ( !result && job.Failure )
				std::invoke( job.Failure, job.Data, game );
		} else
			tiny_sleep_for( 100 );
	}
}

void TinyEngine::Resize( GLFWwindow* handle, tiny_int width, tiny_int height ) {
	auto* engine   = tiny_cast( glfwGetWindowUserPointer( handle ), TinyEngine* );
	auto& window   = engine->GetWindow( );
	auto& graphics = engine->GetGraphics( );
	auto state	   = width > 0 && height > 0;

	if ( state )
		graphics.ReCreate( );

	window.ToggleMinimized( !state );
}

void TinyEngine::Close( GLFWwindow* handle ) {
	auto* engine = tiny_cast( glfwGetWindowUserPointer( handle ), TinyEngine* );

	engine->Stop( );
}

void TinyEngine::ProcessKey( 
	GLFWwindow* handle,
	tiny_int key,
	tiny_int scancode,
	tiny_int action,
	tiny_int mods 
) {
	auto* engine	= tiny_cast( glfwGetWindowUserPointer( handle ), TinyEngine* );
	auto& inputs    = engine->GetInputs( );
	auto descriptor = TinyInputDescriptor{ TI_DEVICE_KEYBOARD, TI_TYPE_BUTTON, TinyInputs::ConvertKey( key ) };

	if ( descriptor.Key < TIK_KEY_COUNT ) {
		inputs.Notify( {
			descriptor,
			tiny_cast( mods, tiny_uint ),
			action == GLFW_PRESS || action == GLFW_REPEAT 
		} );
	}
}

void TinyEngine::ProcessCursor( GLFWwindow* handle, double cursor_x, double cursor_y ) {
	auto* engine	= tiny_cast( glfwGetWindowUserPointer( handle ), TinyEngine* );
	auto& inputs	= engine->GetInputs( );
	auto descriptor = TinyInputDescriptor{ TI_DEVICE_MOUSE, TI_TYPE_AXIS_2D, TIK_MOUSE_CURSOR };

	inputs.Notify( 
		{ descriptor, TI_MODIFIER_UNDEFINED, 
			{ 
				tiny_cast( cursor_x, float ), 
				tiny_cast( cursor_y, float )
			} 
		} 
	);
}

void TinyEngine::ProcessMouse( 
	GLFWwindow* handle, 
	tiny_int button, 
	tiny_int action,
	tiny_int mods
) {
	auto* engine	= tiny_cast( glfwGetWindowUserPointer( handle ), TinyEngine* );
	auto& inputs	= engine->GetInputs( );
	auto descriptor = TinyInputDescriptor{ TI_DEVICE_MOUSE, TI_TYPE_BUTTON, (TinyInputKeys)button };

	if ( descriptor.Key < TIK_MOUSE_COUNT ) {
		inputs.Notify( { 
			descriptor, 
			tiny_cast( mods, tiny_uint ), 
			action == GLFW_PRESS || action == GLFW_REPEAT
		} );
	}
}

void TinyEngine::ProcessScroll( GLFWwindow* handle, double offset_x, double offset_y ) {
	auto* engine	= tiny_cast( glfwGetWindowUserPointer( handle ), TinyEngine* );
	auto& inputs	= engine->GetInputs( );
	auto descriptor = TinyInputDescriptor{ TI_DEVICE_MOUSE, TI_TYPE_AXIS_2D, TIK_MOUSE_SCROLL };

	inputs.Notify( 
		{ descriptor, TI_MODIFIER_UNDEFINED, 
			{
				tiny_cast( offset_x, float ),
				tiny_cast( offset_y, float ) 
			}
		} 
	);
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyEngine::GetIsRunning( ) const { return _is_running; }

bool TinyEngine::GetShouldRun( ) const { 
	return GetIsRunning( ) && _window.GetShouldRun( );
}

TinyJobManager& TinyEngine::GetJobs( ) { return _jobs; }

TinyFilesystem& TinyEngine::GetFilesystem( ) { return _filesystem; }

TinyAssetManager& TinyEngine::GetAssets( ) { return _assets; }

TinyWindow& TinyEngine::GetWindow( ) { return _window; }

TinyInputManager& TinyEngine::GetInputs( ) { return _inputs; }

TinyAudioManager& TinyEngine::GetAudio( ) { return _audio; }

TinyGraphicManager& TinyEngine::GetGraphics( ) { return _graphics; }

TinyNativeRegister& TinyEngine::GetNatives( ) { return _natives; }

TinyScriptManager& TinyEngine::GetScripts( ) { return tiny_lvalue( _scripts ); }

TinyRenderer& TinyEngine::GetRenderer( ) { return _renderer; }

TinyECS& TinyEngine::GetECS( ) { return _ecs; }

TinyAddonManager& TinyEngine::GetAddons( ) { return _addons; }

TinyToolbox& TinyEngine::GetToolbox( ) { return _toolbox; }
