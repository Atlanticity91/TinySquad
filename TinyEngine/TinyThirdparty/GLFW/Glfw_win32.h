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
 * @creation : 18/03/2024
 * @version  : 2024.2.7
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#define GLFW_EXPOSE_NATIVE_WIN32
#define GLFW_INCLUDE_NONE

#define GLFW_DLL

#include <TinyLibs/GLFW/glfw3.h>
#include <TinyLibs/GLFW/glfw3native.h>

#ifdef _WIN32
#	ifdef TT_BUILD
#		define glfw_api __declspec( dllexport )
#	else
#		define glfw_api __declspec( dllimport )
#	endif
#else
#	define glfw_api
#endif

typedef bool( *glfwTitlebarHitCallback )( GLFWwindow* );

struct GlfwWindow {

	GLFWwindow* Handle;

	GlfwWindow( );

	operator GLFWwindow* ( );

	operator GLFWwindow* ( ) const;

};

glfw_api void glfwSetTitlebarHitCallback( glfwTitlebarHitCallback callback );

glfw_api bool glfwCreateWindow(
	GlfwWindow& window,
	const char* title,
	int width,
	int height,
	bool headless,
	bool full_screen
);

glfw_api void glfwDestroyWindow( GlfwWindow& window );
