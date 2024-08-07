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

#include "TinyAppConfig.h"

tiny_enum( TinyWindowCallbacks ) {

	TWC_WINDOW_SIZE = 0,
	TWC_WINDOW_CLOSE,
	TWC_WINDOW_HIT,
	TWC_KEY,
	TWC_CURSOR,
	TWC_MOUSE,
	TWC_SCROLL,
	TWC_DRAG_AND_DROP

};

tiny_enum( TinyWindowFlags ) {

	TW_FLAG_MINIMIZED   = TINY_LEFT_SHIFT( 1, 0 ),
	TW_FLAG_HEADLESS    = TINY_LEFT_SHIFT( 1, 1 ),
	TW_FLAG_FULL_SCREEN = TINY_LEFT_SHIFT( 1, 2 )

};

tm_class TinyWindow final { 

private:
	tiny_string m_title;
	GlfwWindow m_handle;
	tiny_uint m_flags;

public:
	TinyWindow( tiny_string title, bool is_headless );

	~TinyWindow( ) = default;

	bool Initialize( const TinyAppConfig& config, native_pointer user_data );

	void SetCallback( TinyWindowCallbacks query, native_pointer callback );

	void SetIcon( tiny_int width, tiny_int height, tiny_pointer pixels );

	void ToggleMinimized( bool is_minimized );

	void Minimize( );

	void Restore( );

	void Maximize( );

	bool Tick( );

	void Terminate( );

public:
	tiny_string GetTitle( ) const;

	bool GetIsHeadless( ) const;

	bool GetIsFullScreen( ) const;

	const GlfwWindow& GetHandle( ) const;

#	ifdef TINY_WIN
	HWND GetWin32Handle( ) const;
#	elif TINY_LINUX
	Window GetLinuxHandle( ) const;
#	elif TINY_APPLE
	id TinyWindow::GetOsXHandle( ) const;
#	endif

	bool GetShouldRun( ) const;

	tiny_vec2 GetDimensions_v( ) const;

	tiny_point GetDimensions_p( ) const;

	bool GetIsMinimized( ) const;

	bool GetIsMaximized( ) const;

public:
	operator GLFWwindow* ( ) const;
#	ifdef TINY_WIN
	operator HWND ( ) const;
#	elif TINY_LINUX
	operator Window const;
#	elif TINY_APPLE
	operator id ( ) const;
#	endif

	operator bool( ) const;

	operator tiny_vec2 ( ) const;

	operator tiny_point ( ) const;

};
