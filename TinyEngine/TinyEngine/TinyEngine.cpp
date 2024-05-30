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
	const tiny_string& developer,
	const tiny_string& title,
	TinyGameOrientations orientation, 
	bool is_headless 
)
	: _is_running{ true },
	_jobs{ },
	_filesystem{ developer },
	_assets{ },
	_window{ title, is_headless },
	_inputs{ },
	_audio{ },
	_graphics{ orientation },
	_natives{ },
	_renderer{ },
	_ecs{ },
	_ux{ },
	_addons{ },
	_provider{ },
	_states{ },
	_toolbox{ }
{ }

bool TinyEngine::Initialize( TinyGame* game, tiny_int argc, char** argv ) {
	auto* game_config = tiny_cast( nullptr, TinyConfig* );
	
	if ( 
		PreInit( game, game_config )			 &&
		Init( game, tiny_lvalue( game_config ) ) &&
		PostInit( game )						 && 
		ProcessArgs( game, argc, argv )
	) {
		if ( !_window.GetIsHeadless( ) ) {
			_inputs.Register(
				"Show Dev",
				{
					{ TinyInputKey( KEY_F1 ), TI_STATE_PRESSED, TI_MODIFIER_UNDEFINED },
					{ TinyInputKey( KEY_GRAVE_ACCENT ), TI_STATE_PRESSED, TI_MODIFIER_UNDEFINED },
				}
			);
		}

		_is_running = true;
	}

	return _is_running;
}

void TinyEngine::Minimize( ) { _window.Minimize( ); }

void TinyEngine::Restore( ) { _window.Restore( ); }

void TinyEngine::Maximize( ) { _window.Maximize( ); }

void TinyEngine::Stop( ) { _is_running = false; }

void TinyEngine::Dispatch( const TinyJob& job ) { _jobs.Dispatch( job ); }

void TinyEngine::Switch( TinyGame* game, const tiny_uint state_id ) {
	_states.Switch( game, state_id );
}

void TinyEngine::Switch( TinyGame* game, const tiny_string& state_name ) {
	_states.Switch( game, state_name );
}

void TinyEngine::Switch( TinyGame* game, const tiny_hash state_hash ) {
	_states.Switch( game, state_hash );
}

bool TinyEngine::PreTick( TinyGame* game ) {
	auto state = _window.Tick( );

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
	_ux.Tick( game );
	_audio.Tick( _inputs );
	_jobs.Wait( );
	_renderer.Compose( game );
	_toolbox.Tick( game );
	_graphics.Present( _window );
	_inputs.Tick( );
}

void TinyEngine::Terminate( TinyGame* game ) {
	auto& scripts = _assets.GetScripts( );

	_toolbox.Terminate( game );
	_provider.Terminate( _filesystem );
	_addons.Terminate( game );
	
	scripts.Terminate( );
	
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
	auto state = _jobs.Initialize( game, TinyEngine::JobWorkerRun ) &&
				_filesystem.Initialize( _window )					&&
				_assets.Initialize( game, game_config );

	if ( state ) {
		auto& scripts = _assets.GetScripts( );

		state = scripts.Initialize( ) &&
				_addons.Initialize( game );
	}

	return state;
}

bool TinyEngine::Init( TinyGame* game, const TinyConfig& config ) {
	return  _window.Initialize( config, tiny_cast( game, native_pointer ) ) &&
			_inputs.Initialize( _filesystem, _window )						&&
			_audio.Initialize( _filesystem, _window )						&&
			_graphics.Initialize( _filesystem, _window );
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
void TinyEngine::JobWorkerRun(
	const TinyJobFilters filter,
	native_pointer game,
	TinyJobQueue& queues
) {
	auto thread_guard = std::mutex{ };
	auto priority	  = TJ_PRIORITY_HIGH;
	auto* game_		  = tiny_cast( game, TinyGame* );
	auto job		  = TinyJob{ };

	while ( game_->GetIsRunning( ) ) {
		auto lock = std::unique_lock{ thread_guard };

		if ( queues.GetHasJob( filter, priority ) || queues.GetHasJob( TJ_FILTER_NONE, priority ) ) {
			queues.DeQueue( priority, job );

			auto result = std::invoke( job.Task, job.Data, game );

			if ( result && job.Success )
				std::invoke( job.Success, job.Data, game );
			else if ( !result && job.Failure )
				std::invoke( job.Failure, job.Data, game );
		} else
			tiny_sleep_for( 250 );
	}
}

void TinyEngine::Resize( GLFWwindow* handle, tiny_int width, tiny_int height ) {
	auto* engine   = tiny_cast( glfwGetWindowUserPointer( handle ), TinyGame* );
	auto& window   = engine->GetWindow( );
	auto& graphics = engine->GetGraphics( );
	auto state	   = width > 0 && height > 0;

	if ( state )
		graphics.ReCreate( );

	window.ToggleMinimized( !state );
}

void TinyEngine::Close( GLFWwindow* handle ) {
	auto* engine = tiny_cast( glfwGetWindowUserPointer( handle ), TinyGame* );

	engine->Stop( );
}

void TinyEngine::ProcessKey( 
	GLFWwindow* handle,
	tiny_int key,
	tiny_int scancode,
	tiny_int action,
	tiny_int mods 
) {
	auto* engine	= tiny_cast( glfwGetWindowUserPointer( handle ), TinyGame* );
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
	auto* engine	= tiny_cast( glfwGetWindowUserPointer( handle ), TinyGame* );
	auto& inputs	= engine->GetInputs( );
	auto descriptor = TinyInputDescriptor{ TI_DEVICE_MOUSE, TI_TYPE_AXIS_2D, TIK_MOUSE_CURSOR };

	inputs.Notify( 
		{ 
			descriptor, TI_MODIFIER_UNDEFINED, 
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
	auto* engine	= tiny_cast( glfwGetWindowUserPointer( handle ), TinyGame* );
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
	auto* engine	= tiny_cast( glfwGetWindowUserPointer( handle ), TinyGame* );
	auto& inputs	= engine->GetInputs( );
	auto descriptor = TinyInputDescriptor{ TI_DEVICE_MOUSE, TI_TYPE_AXIS_2D, TIK_MOUSE_SCROLL };

	inputs.Notify( 
		{ 
			descriptor, TI_MODIFIER_UNDEFINED, 
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

TinyScriptManager& TinyEngine::GetScripts( ) { return _assets.GetScripts( ); }

TinyRenderer& TinyEngine::GetRenderer( ) { return _renderer; }

TinyECS& TinyEngine::GetECS( ) { return _ecs; }

TinySceneManager& TinyEngine::GetScenes( ) { return _assets.GetScenes( ); }

TinyUXManager& TinyEngine::GetUX( ) { return _ux; }

TinyAddonManager& TinyEngine::GetAddons( ) { return _addons; }

TinyGameStateManager& TinyEngine::GetGameStates( ) { return _states; }

TinyToolbox& TinyEngine::GetToolbox( ) { return _toolbox; }
