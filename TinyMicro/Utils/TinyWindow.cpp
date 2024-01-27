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
TinyWindow::TinyWindow( tiny_string title )
	: _title{ title },
	_handle{ nullptr }
{ }

bool TinyWindow::Initialize( const TinyAppConfig& config, c_pointer user_data ) {
	auto state = glfwInit( );

	if ( state ) {
		glfwWindowHint( GLFW_RESIZABLE, GLFW_TRUE );
		glfwWindowHint( GLFW_CLIENT_API, GLFW_NO_API );

		_handle = glfwCreateWindow( config.Width, config.Height, tiny_cast( _title, c_string ), nullptr, nullptr );

		state = _handle != nullptr;

		if ( state ) {
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

void TinyWindow::Tick( ) { glfwPollEvents( ); }

void TinyWindow::Terminate( ) {
	if ( _handle )
		glfwDestroyWindow( _handle );

	glfwTerminate( );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
tiny_string TinyWindow::GetTitle( ) const { return _title; }

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

////////////////////////////////////////////////////////////////////////////////////////////
//		===	OPERATOR ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyWindow::operator bool ( ) const { return GetShouldRun( ); }

TinyWindow::operator GLFWwindow* ( ) const { return GetHandle( ); }

TinyWindow::operator HWND ( ) const { return GetWin32Handle( ); }

TinyWindow::operator tiny_vec2 ( ) const { return GetDimensions_v( ); }

TinyWindow::operator tiny_point ( ) const { return GetDimensions_p( ); }
