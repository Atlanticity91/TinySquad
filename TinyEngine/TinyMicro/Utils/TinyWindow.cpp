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

#include <TinyMicro/__tiny_micro_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyWindow::TinyWindow( tiny_string title, bool is_headless )
	: _title{ title },
	_handle{ },
	_is_minimized{ false },
	_is_headless{ is_headless },
	_is_full_screen{ false }
{ }

bool TinyWindow::Initialize( const TinyAppConfig& config, native_pointer user_data ) {
	auto* title = _title.get( );
	auto state  = glfwCreateWindow( _handle, title, config.Width, config.Height, _is_headless, config.IsFullScreen );

	if ( state ) {
		_is_full_screen = config.IsFullScreen;

		if ( config.Icon.Pixels ) {
			auto icon = GLFWimage{ };

			icon.width  = tiny_cast( config.Icon.Width, tiny_int );
			icon.height = tiny_cast( config.Icon.Height, tiny_int );
			icon.pixels = tiny_cast( config.Icon.Pixels.GetAddress( ), tiny_ubyte* );

			glfwSetWindowIcon( _handle, 1, tiny_rvalue( icon ) );
		}

		glfwSetWindowUserPointer( _handle, user_data );
	}

	return state;
}

void TinyWindow::SetCallback( TinyWindowCallbacks query, native_pointer callback ) {
	switch ( query ) {
		case TWC_WINDOW_SIZE  : glfwSetWindowSizeCallback( _handle, tiny_cast( callback, GLFWwindowsizefun ) );	  break;
		case TWC_WINDOW_CLOSE : glfwSetWindowCloseCallback( _handle, tiny_cast( callback, GLFWwindowclosefun ) ); break;
		case TWC_WINDOW_HIT	  : glfwSetTitlebarHitCallback( tiny_cast( callback, glfwTitlebarHitCallback ) );	  break;
		case TWC_KEY		  : glfwSetKeyCallback( _handle, tiny_cast( callback, GLFWkeyfun ) );				  break;
		case TWC_CURSOR		  : glfwSetCursorPosCallback( _handle, tiny_cast( callback, GLFWcursorposfun ) );	  break;
		case TWC_MOUSE		  : glfwSetMouseButtonCallback( _handle, tiny_cast( callback, GLFWmousebuttonfun ) ); break;
		case TWC_SCROLL		  : glfwSetScrollCallback( _handle, tiny_cast( callback, GLFWscrollfun ) );			  break;

		default : break;
	}
	
}

void TinyWindow::SetIcon( tiny_int width, tiny_int height, tiny_pointer pixels ) {
	auto icon = GLFWimage{ width, height, pixels };

	glfwSetWindowIcon( _handle, 1, tiny_rvalue( icon ) );
}

void TinyWindow::ToggleMinimized( bool is_minimized ) { _is_minimized = is_minimized; }

void TinyWindow::Minimize( ) { 
	glfwIconifyWindow( _handle ); 

	_is_minimized = true;
}

void TinyWindow::Restore( ) { glfwRestoreWindow( _handle ); }

void TinyWindow::Maximize( ) { glfwMaximizeWindow( _handle ); }

bool TinyWindow::Tick( ) { 
	glfwPollEvents( ); 

	return !_is_minimized;
}

void TinyWindow::Terminate( ) { glfwDestroyWindow( _handle ); }

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
tiny_string TinyWindow::GetTitle( ) const { return _title; }

bool TinyWindow::GetIsHeadless( ) const { return _is_headless; }

bool TinyWindow::GetIsFullScreen( ) const { return _is_full_screen; }

const GlfwWindow& TinyWindow::GetHandle( ) const { return _handle; }

HWND TinyWindow::GetWin32Handle( ) const { return glfwGetWin32Window( _handle ); }

bool TinyWindow::GetShouldRun( ) const { return !glfwWindowShouldClose( _handle ); }

tiny_vec2 TinyWindow::GetDimensions_v( ) const {
	auto _point = GetDimensions_p( );

	return { tiny_cast( _point.x, float ), tiny_cast( _point.y, float ) };
}

tiny_point TinyWindow::GetDimensions_p( ) const {
	auto dimensions = tiny_point{ };

	glfwGetWindowSize( _handle, tiny_rvalue( dimensions.x ), tiny_rvalue( dimensions.y ) );

	return dimensions;
}

bool TinyWindow::GetIsMinimized( ) const { return _is_minimized; }

bool TinyWindow::GetIsMaximized( ) const {
	return tiny_cast( glfwGetWindowAttrib( _handle, GLFW_MAXIMIZED ), bool );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	OPERATOR ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyWindow::operator bool ( ) const { return GetShouldRun( ); }

TinyWindow::operator GLFWwindow* ( ) const { return GetHandle( ); }

TinyWindow::operator HWND ( ) const { return GetWin32Handle( ); }

TinyWindow::operator tiny_vec2 ( ) const { return GetDimensions_v( ); }

TinyWindow::operator tiny_point ( ) const { return GetDimensions_p( ); }
