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
 * @creation : 28/03/2024
 * @version  : 2024.2.7
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "TinyNutIcon.h"

struct tiny_nut_dll TinyNutIcon {

	using Callback_t = std::function<void( TinyGame* )>;

	Callback_t Callback;

};

namespace TinyNutUI { 

	tiny_nut_dll ImRect GetItemRect( );

	tiny_nut_dll ImRect RectExpanded( const ImRect& rect, float x, float y );
	
	tiny_nut_dll ImRect RectOffset( const ImRect& rect, float x, float y );
	
	tiny_nut_dll ImRect RectOffset( const ImRect& rect, ImVec2 xy );

	tiny_nut_dll bool BeginMenubar( const ImRect& barRectangle );

	tiny_nut_dll void EndMenubar( );

};
