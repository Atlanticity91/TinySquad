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
	_handle{ nullptr },
	_is_minimized{ false },
	_is_headless{ is_headless }
{ }

bool TinyWindow::Initialize( const TinyAppConfig& config, c_pointer user_data ) {
	auto state = glfwInit( );

	if ( state ) {
		glfwWindowHint( GLFW_RESIZABLE, GLFW_TRUE );
		glfwWindowHint( GLFW_CLIENT_API, GLFW_NO_API );

		_handle = glfwCreateWindow( config.Width, config.Height, tiny_cast( _title, c_string ), nullptr, nullptr );

		state = _handle != nullptr;

		if ( state ) {
			if ( _is_headless )
				SetupHeadless( config );

			glfwSetWindowIcon( _handle, 1, tiny_cast( tiny_rvalue( config.Icon ), GLFWimage* ) );
			glfwSetInputMode( _handle, GLFW_LOCK_KEY_MODS, GLFW_TRUE );
			glfwSetWindowUserPointer( _handle, user_data );
		}
	}

	return state;
}

void TinyWindow::SetCallback( TinyWindowCallbacks query, c_pointer callback ) {
	switch ( query ) {
		case TWC_WINDOW_SIZE  : glfwSetWindowSizeCallback( _handle, tiny_cast( callback, GLFWwindowsizefun ) );   break;
		case TWC_WINDOW_CLOSE : glfwSetWindowCloseCallback( _handle, tiny_cast( callback, GLFWwindowclosefun ) ); break;
		case TWC_KEY		  : glfwSetKeyCallback( _handle, tiny_cast( callback, GLFWkeyfun ) );				  break;
		case TWC_CURSOR		  : glfwSetCursorPosCallback( _handle, tiny_cast( callback, GLFWcursorposfun ) );	  break;
		case TWC_MOUSE		  : glfwSetMouseButtonCallback( _handle, tiny_cast( callback, GLFWmousebuttonfun ) ); break;
		case TWC_SCROLL		  : glfwSetScrollCallback( _handle, tiny_cast( callback, GLFWscrollfun ) );			  break;

		default: break;
	}
}

void TinyWindow::ToggleMinimized( bool is_minimized ) { _is_minimized = is_minimized; }

void TinyWindow::Minimize( ) { glfwIconifyWindow( _handle ); }

void TinyWindow::Restore( ) { glfwRestoreWindow( _handle ); }

void TinyWindow::Maximize( ) { glfwMaximizeWindow( _handle ); }

bool TinyWindow::Tick( ) { 
	glfwPollEvents( ); 

	return !_is_minimized;
}

void TinyWindow::Terminate( ) {
	if ( _handle )
		glfwDestroyWindow( _handle );

	glfwTerminate( );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE ===
////////////////////////////////////////////////////////////////////////////////////////////
void TinyWindow::SetupHeadless( const TinyAppConfig& config ) {
	auto* monitor = glfwGetPrimaryMonitor( );
	auto* mode	  = glfwGetVideoMode( monitor );
	auto window_x = 0;
	auto window_y = 0;

	
	glfwGetMonitorPos( monitor, tiny_rvalue( window_x ), tiny_rvalue( window_y ) );

	window_x += ( mode->width  - config.Width  ) / 2;
	window_y += ( mode->height - config.Height ) / 2;

	glfwSetWindowAttrib( _handle, GLFW_DECORATED, GLFW_FALSE );
	glfwSetWindowPos( _handle, window_x, window_y );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
tiny_string TinyWindow::GetTitle( ) const { return _title; }

bool TinyWindow::GetIsHeadless( ) const { return _is_headless; }

GLFWwindow* TinyWindow::GetHandle( ) const { return _handle; }

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
