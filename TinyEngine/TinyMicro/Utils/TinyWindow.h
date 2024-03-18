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
	TWC_KEY,
	TWC_CURSOR,
	TWC_MOUSE,
	TWC_SCROLL

};

tm_class TinyWindow final { 

private:
	tiny_string _title;
	GLFWwindow* _handle;

public:
	TinyWindow( tiny_string title );

	~TinyWindow( ) = default;

	bool Initialize( const TinyAppConfig& config, c_pointer user_data );

	void SetCallback( TinyWindowCallbacks query, c_pointer callback );

	void Tick( );

	void Terminate( );

public:
	tiny_string GetTitle( ) const;

	GLFWwindow* GetHandle( ) const;

	HWND GetWin32Handle( ) const;

	bool GetShouldRun( ) const;

	tiny_vec2 GetDimensions_v( ) const;

	tiny_point GetDimensions_p( ) const;

public:
	operator GLFWwindow* ( ) const;

	operator HWND ( ) const;

	operator bool( ) const;

	operator tiny_vec2 ( ) const;

	operator tiny_point ( ) const;

};
