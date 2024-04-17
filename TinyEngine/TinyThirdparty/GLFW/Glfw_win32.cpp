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
 * @creation : 17/04/2024
 * @version  : 2024.2.7
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#include "Glfw_win32.h"

////////////////////////////////////////////////////////////////////////////////////////////
//		===	INTERNAL ===
////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Hook & Tested headless window idea from the BleasT at :
 * https://discourse.glfw.org/t/making-a-custom-titlebar/2392/6
 **/
WNDPROC glfw_internal_proc;
glfwTitlebarHitCallback glfw_internal_titlebarhit = nullptr;

LRESULT CALLBACK glfwWin32Hook( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam ) {
    auto* window = (GLFWwindow*)GetPropW( hWnd, L"GLFW" );

    switch ( uMsg ) {
        case WM_NCCALCSIZE: 
        {
            // Remove the window's standard sizing border
            if ( wParam == TRUE && lParam != NULL ) {
                NCCALCSIZE_PARAMS* pParams = reinterpret_cast<NCCALCSIZE_PARAMS*>( lParam );
                pParams->rgrc[ 0 ].top    += 1;
                pParams->rgrc[ 0 ].right  -= 2;
                pParams->rgrc[ 0 ].bottom -= 2;
                pParams->rgrc[ 0 ].left   += 2;
            }
            return 0;
        }
        case WM_NCPAINT:
        {
            // Prevent the non-client area from being painted
            return 0;
        }
        case WM_NCHITTEST:
        {
            // Expand the hit test area for resizing
            const int borderWidth = 8; // Adjust this value to control the hit test area size

            auto mousePos       = (POINTS)MAKEPOINTS( lParam );
            auto clientMousePos = POINT{ mousePos.x, mousePos.y };
            auto windowRect     = RECT{ };

            ScreenToClient( hWnd, &clientMousePos );
            GetClientRect( hWnd, &windowRect );

            if ( clientMousePos.y >= windowRect.bottom - borderWidth ) {
                if ( clientMousePos.x <= borderWidth )
                    return HTBOTTOMLEFT;
                else if ( clientMousePos.x >= windowRect.right - borderWidth )
                    return HTBOTTOMRIGHT;
                else
                    return HTBOTTOM;
            } else if ( clientMousePos.y <= borderWidth ) {
                if ( clientMousePos.x <= borderWidth )
                    return HTTOPLEFT;
                else if ( clientMousePos.x >= windowRect.right - borderWidth )
                    return HTTOPRIGHT;
                else
                    return HTTOP;
            } else if ( clientMousePos.x <= borderWidth ) {
                return HTLEFT;
            } else if ( clientMousePos.x >= windowRect.right - borderWidth ) {
                return HTRIGHT;
            }

            if ( glfw_internal_titlebarhit && glfw_internal_titlebarhit( window ) )
                return HTCAPTION;

            return HTCLIENT;
        }
    }

    return CallWindowProc( glfw_internal_proc, hWnd, uMsg, wParam, lParam );
}

void glfwHookProc( GLFWwindow* window ) {
    auto windowRect = RECT{ };
    auto hWnd       = glfwGetWin32Window( window );
    auto lStyle     = GetWindowLongPtr( hWnd, GWL_STYLE );
    
    lStyle |= WS_THICKFRAME;
    lStyle &= ~WS_CAPTION;

    SetWindowLongPtr( hWnd, GWL_STYLE, lStyle );
    GetWindowRect( hWnd, &windowRect );
    
    auto width  = (int)( windowRect.right  - windowRect.left );
    auto height = (int)( windowRect.bottom - windowRect.top  );

    glfw_internal_proc = (WNDPROC)GetWindowLongPtr( hWnd, GWLP_WNDPROC );

    (WNDPROC)SetWindowLongPtr( hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>( glfwWin32Hook ) );

    SetWindowPos( hWnd, NULL, 0, 0, width, height, SWP_FRAMECHANGED | SWP_NOMOVE );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
GlfwWindow::GlfwWindow( )
	: Handle{ nullptr }
{ }

GlfwWindow::operator GLFWwindow* ( ) { return Handle; }

GlfwWindow::operator GLFWwindow* ( ) const { return Handle; }

void glfwSetTitlebarHitCallback( glfwTitlebarHitCallback callback ) {
    glfw_internal_titlebarhit = callback;
}

bool glfwCreateWindow(
	GlfwWindow& window,
	const char* title,
	int width,
	int height,
	bool headless,
    bool full_screen
) {
	auto state = false;

	if ( glfwInit( ) == GLFW_TRUE ) {
		auto* monitor = glfwGetPrimaryMonitor( );

		glfwWindowHint( GLFW_VISIBLE, GLFW_FALSE );
		glfwWindowHint( GLFW_RESIZABLE, GLFW_TRUE );
		glfwWindowHint( GLFW_CLIENT_API, GLFW_NO_API );

		window.Handle = glfwCreateWindow( width, height, title, full_screen ? monitor : nullptr, nullptr );
		
		state = window.Handle != nullptr;

		if ( state ) {
			if ( headless ) {
				auto* mode = glfwGetVideoMode( monitor );
				auto window_x = 0;
				auto window_y = 0;

				glfwGetMonitorPos( monitor, &window_x, &window_y );

				window_x += ( mode->width - width ) / 2;
				window_y += ( mode->height - height ) / 2;

				glfwSetWindowAttrib( window.Handle, GLFW_DECORATED, GLFW_FALSE );
				glfwSetWindowPos( window.Handle, window_x, window_y );
                glfwHookProc( window.Handle );
			}

			glfwSetInputMode( window.Handle, GLFW_LOCK_KEY_MODS, GLFW_TRUE );
			glfwShowWindow( window.Handle );
		}
	}

	return state;
}

void glfwDestroyWindow( GlfwWindow& window ) {
	if ( window.Handle )
		glfwDestroyWindow( window.Handle );

	glfwTerminate( );
}
