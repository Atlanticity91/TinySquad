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
	: m_title{ title },
	m_handle{ },
	m_flags{ is_headless * TW_FLAG_HEADLESS }
{ }

bool TinyWindow::Initialize( const TinyAppConfig& config, native_pointer user_data ) {
	auto* title = m_title.get( );
	auto state  = glfwCreateWindow( m_handle, title, config.Width, config.Height, m_flags & TW_FLAG_HEADLESS, config.IsFullScreen );

	if ( state ) {
		if ( config.IsFullScreen )
			m_flags |= TW_FLAG_FULL_SCREEN;

		if ( config.Icon.Pixels ) {
			auto icon = GLFWimage{ };

			icon.width  = tiny_cast( config.Icon.Width, tiny_int );
			icon.height = tiny_cast( config.Icon.Height, tiny_int );
			icon.pixels = tiny_cast( config.Icon.Pixels.GetAddress( ), tiny_ubyte* );

			glfwSetWindowIcon( m_handle, 1, tiny_rvalue( icon ) );
		}

		glfwSetWindowUserPointer( m_handle, user_data );
	}

	return state;
}

void TinyWindow::SetCallback( TinyWindowCallbacks query, native_pointer callback ) {
	switch ( query ) {
		case TWC_WINDOW_SIZE   : glfwSetWindowSizeCallback( m_handle, tiny_cast( callback, GLFWwindowsizefun ) );   break;
		case TWC_WINDOW_CLOSE  : glfwSetWindowCloseCallback( m_handle, tiny_cast( callback, GLFWwindowclosefun ) ); break;
		case TWC_WINDOW_HIT	   : glfwSetTitlebarHitCallback( tiny_cast( callback, glfwTitlebarHitCallback ) );	    break;
		case TWC_KEY		   : glfwSetKeyCallback( m_handle, tiny_cast( callback, GLFWkeyfun ) );				    break;
		case TWC_CURSOR		   : glfwSetCursorPosCallback( m_handle, tiny_cast( callback, GLFWcursorposfun ) );	    break;
		case TWC_MOUSE		   : glfwSetMouseButtonCallback( m_handle, tiny_cast( callback, GLFWmousebuttonfun ) ); break;
		case TWC_SCROLL		   : glfwSetScrollCallback( m_handle, tiny_cast( callback, GLFWscrollfun ) );		    break;
		case TWC_DRAG_AND_DROP : glfwSetDropCallback( m_handle, tiny_cast( callback, GLFWdropfun ) );			    break;

		default : break;
	}
	
}

void TinyWindow::SetIcon( tiny_int width, tiny_int height, tiny_pointer pixels ) {
	auto icon = GLFWimage{ width, height, pixels };

	glfwSetWindowIcon( m_handle, 1, tiny_rvalue( icon ) );
}

void TinyWindow::ToggleMinimized( bool is_minimized ) {
	if ( is_minimized )
		m_flags |= TW_FLAG_MINIMIZED; 
	else
		m_flags ^= TW_FLAG_MINIMIZED;
}

void TinyWindow::Minimize( ) { 
	glfwIconifyWindow( m_handle );

	m_flags |= TW_FLAG_MINIMIZED;
}

void TinyWindow::Restore( ) { glfwRestoreWindow( m_handle ); }

void TinyWindow::Maximize( ) { glfwMaximizeWindow( m_handle ); }

bool TinyWindow::Tick( ) { 
	glfwPollEvents( ); 

	return !( m_flags & TW_FLAG_MINIMIZED );
}

void TinyWindow::Terminate( ) { glfwDestroyWindow( m_handle ); }

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
tiny_string TinyWindow::GetTitle( ) const { return m_title; }

bool TinyWindow::GetIsHeadless( ) const { return ( m_flags & TW_FLAG_HEADLESS ); }

bool TinyWindow::GetIsFullScreen( ) const { return ( m_flags & TW_FLAG_FULL_SCREEN ); }

const GlfwWindow& TinyWindow::GetHandle( ) const { return m_handle; }

HWND TinyWindow::GetWin32Handle( ) const { return glfwGetWin32Window( m_handle ); }

bool TinyWindow::GetShouldRun( ) const { return !glfwWindowShouldClose( m_handle ); }

tiny_vec2 TinyWindow::GetDimensions_v( ) const {
	auto _point = GetDimensions_p( );

	return { tiny_cast( _point.x, float ), tiny_cast( _point.y, float ) };
}

tiny_point TinyWindow::GetDimensions_p( ) const {
	auto dimensions = tiny_point{ };

	glfwGetWindowSize( m_handle, tiny_rvalue( dimensions.x ), tiny_rvalue( dimensions.y ) );

	return dimensions;
}

bool TinyWindow::GetIsMinimized( ) const { return ( m_flags & TW_FLAG_MINIMIZED ); }

bool TinyWindow::GetIsMaximized( ) const {
	return tiny_cast( glfwGetWindowAttrib( m_handle, GLFW_MAXIMIZED ), bool );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	OPERATOR ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyWindow::operator bool ( ) const { return GetShouldRun( ); }

TinyWindow::operator GLFWwindow* ( ) const { return GetHandle( ); }

TinyWindow::operator HWND ( ) const { return GetWin32Handle( ); }

TinyWindow::operator tiny_vec2 ( ) const { return GetDimensions_v( ); }

TinyWindow::operator tiny_point ( ) const { return GetDimensions_p( ); }
