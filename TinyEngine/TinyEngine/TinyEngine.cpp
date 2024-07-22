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
	: m_is_running{ true },
	m_jobs{ },
	m_filesystem{ developer },
	m_assets{ },
	m_window{ title, is_headless },
	m_inputs{ },
	m_audio{ },
	m_graphics{ orientation },
	m_natives{ },
	m_renderer{ },
	m_ecs{ },
	m_ux{ },
	m_addons{ },
	m_provider{ },
	m_states{ },
	m_toolbox{ }
{ }

void TinyEngine::DisableGameFolder( ) {
	m_filesystem.DisableGameFolder( );
	
	DisableCache( );
}

bool TinyEngine::Initialize( TinyGame* game, tiny_int argc, char** argv ) {
	auto* game_config = tiny_cast( nullptr, TinyConfig* );
	
	if ( 
		PreInit( game, game_config )			 &&
		Init( game, tiny_lvalue( game_config ) ) &&
		PostInit( game )						 && 
		ProcessArgs( game, argc, argv )
	) {
		if ( !m_window.GetIsHeadless( ) ) {
			m_inputs.Register(
				"Show Dev",
				{
					{ TinyInputKey( KEY_F1 ), TI_STATE_PRESSED, TI_MODIFIER_UNDEFINED },
					{ TinyInputKey( KEY_GRAVE_ACCENT ), TI_STATE_PRESSED, TI_MODIFIER_UNDEFINED },
				}
			);
		}

		m_is_running = true;
	}

	return m_is_running;
}

void TinyEngine::Minimize( ) { m_window.Minimize( ); }

void TinyEngine::Restore( ) { m_window.Restore( ); }

void TinyEngine::Maximize( ) { m_window.Maximize( ); }

void TinyEngine::Stop( ) { m_is_running = false; }

void TinyEngine::DisableCache( ) { m_graphics.DisableCache( ); }

void TinyEngine::EnableCache( ) { m_graphics.EnableCache( ); }

void TinyEngine::Dispatch( const TinyJob& job ) { m_jobs.Dispatch( job ); }

void TinyEngine::Switch( TinyGame* game, const tiny_uint state_id ) {
	m_states.Switch( game, state_id );
}

void TinyEngine::Switch( TinyGame* game, const tiny_string& state_name ) {
	m_states.Switch( game, state_name );
}

void TinyEngine::Switch( TinyGame* game, const tiny_hash state_hash ) {
	m_states.Switch( game, state_hash );
}

bool TinyEngine::PreTick( TinyGame* game ) {
	auto state = m_window.Tick( );

	if ( state ) {
		m_addons.PreTick( game );
		m_ecs.PreTick( game );
		m_graphics.Acquire( m_window );
	}

	return state;
}

void TinyEngine::PostTick( TinyGame* game ) {
	m_addons.PostTick( game );
	m_ecs.PostTick( game );
	m_ux.Tick( game );
	m_audio.Tick( m_inputs );
	m_jobs.Wait( );
	m_renderer.Compose( game );
	m_toolbox.Tick( game );
	m_graphics.Present( m_window );
	m_inputs.Tick( );
}

void TinyEngine::Terminate( TinyGame* game ) {
	auto& scripts = m_assets.GetScripts( );

	m_is_running = false;
	m_toolbox.Terminate( game );
	m_provider.Terminate( m_filesystem );
	m_addons.Terminate( game );
	
	scripts.Terminate( );
	
	m_renderer.Terminate( m_graphics );
	m_assets.Terminate( game );
	m_graphics.Terminate( m_filesystem, m_window );
	m_audio.Terminate( m_filesystem, m_window );
	m_inputs.Terminate( m_filesystem, m_window );
	m_window.Terminate( );
	m_filesystem.Terminate( );
	m_jobs.Terminate( );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyEngine::PreInit( TinyGame* game, TinyConfig*& game_config ) {
	auto state = m_jobs.Initialize( game, TinyEngine::JobWorkerRun ) &&
				 m_filesystem.Initialize( m_window )				 &&
				 m_assets.Initialize( game, game_config );

	if ( state ) {
		auto& scripts = m_assets.GetScripts( );

		state = scripts.Initialize( ) &&
				m_addons.Initialize( game );
	}

	return state;
}

bool TinyEngine::Init( TinyGame* game, const TinyConfig& config ) {
	return  m_window.Initialize( config, tiny_cast( game, native_pointer ) ) &&
			m_inputs.Initialize( m_filesystem, m_window )					 &&
			m_audio.Initialize( m_filesystem, m_window )					 &&
			m_graphics.Initialize( m_filesystem, m_window );
}

bool TinyEngine::PostInit( TinyGame* game ) {
	m_window.SetCallback( TWC_WINDOW_SIZE , TinyEngine::Resize		  );
	m_window.SetCallback( TWC_WINDOW_CLOSE, TinyEngine::Close		  );
	m_window.SetCallback( TWC_KEY		  , TinyEngine::ProcessKey	  );
	m_window.SetCallback( TWC_CURSOR	  , TinyEngine::ProcessCursor );
	m_window.SetCallback( TWC_MOUSE		  , TinyEngine::ProcessMouse  );
	m_window.SetCallback( TWC_SCROLL	  , TinyEngine::ProcessScroll );

	return  m_renderer.Initialize( m_graphics, m_filesystem ) &&
			m_provider.Initialize( m_filesystem )			  &&
			m_toolbox.Initialize( game );
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

	while ( true ) {
		thread_guard.lock( );
		
		if ( !game_->GetIsRunning( ) )
			return;

		thread_guard.unlock( );

		if ( queues.GetHasJob( filter, priority ) || queues.GetHasJob( TJ_FILTER_NONE, priority ) ) {
			queues.DeQueue( priority, job );

			thread_guard.lock( );

			auto result = std::invoke( job.Task, job.Data, game );

			if ( result && job.Success )
				std::invoke( job.Success, job.Data, game );
			else if ( !result && job.Failure )
				std::invoke( job.Failure, job.Data, game );

			thread_guard.unlock( );
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
bool TinyEngine::GetIsRunning( ) const { return m_is_running; }

bool TinyEngine::GetShouldRun( ) const { 
	return GetIsRunning( ) && m_window.GetShouldRun( );
}

TinyJobManager& TinyEngine::GetJobs( ) { return m_jobs; }

TinyFilesystem& TinyEngine::GetFilesystem( ) { return m_filesystem; }

TinyAssetManager& TinyEngine::GetAssets( ) { return m_assets; }

TinyWindow& TinyEngine::GetWindow( ) { return m_window; }

TinyInputManager& TinyEngine::GetInputs( ) { return m_inputs; }

TinyAudioManager& TinyEngine::GetAudio( ) { return m_audio; }

TinyGraphicManager& TinyEngine::GetGraphics( ) { return m_graphics; }

TinyNativeRegister& TinyEngine::GetNatives( ) { return m_natives; }

TinyScriptManager& TinyEngine::GetScripts( ) { return m_assets.GetScripts( ); }

TinyRenderer& TinyEngine::GetRenderer( ) { return m_renderer; }

TinyECS& TinyEngine::GetECS( ) { return m_ecs; }

TinySceneManager& TinyEngine::GetScenes( ) { return m_assets.GetScenes( ); }

TinyUXManager& TinyEngine::GetUX( ) { return m_ux; }

TinyAddonManager& TinyEngine::GetAddons( ) { return m_addons; }

TinyGameStateManager& TinyEngine::GetGameStates( ) { return m_states; }

TinyToolbox& TinyEngine::GetToolbox( ) { return m_toolbox; }
