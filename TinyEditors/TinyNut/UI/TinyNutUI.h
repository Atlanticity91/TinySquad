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

class TinyNut;

namespace TinyNutUI { 

	tn_struct Image {

		TinyGraphicTexture Texture{ };
		ImTextureID Descriptor = nullptr;

	};

	tn_struct Icon {

		using Callback_t = std::function<void( TinyNut* )>;
		
		Image Icon;
		Callback_t Callback;

	};

	tiny_nut_dll Image CreateImage(
		TinyNut* nut_game,
		tiny_uint length, 
		const tiny_ubyte* image 
	);

	tiny_nut_dll void DeleteImage( TinyNut* nut_game, Image& image );

	tiny_nut_dll ImRect GetItemRect( );

	tiny_nut_dll ImRect RectExpanded( const ImRect& rect, float x, float y );
	
	tiny_nut_dll ImRect RectOffset( const ImRect& rect, float x, float y );
	
	tiny_nut_dll ImRect RectOffset( const ImRect& rect, ImVec2 xy );

	tiny_nut_dll bool BeginMenubar( const ImRect& barRectangle );

	tiny_nut_dll void EndMenubar( );

	tiny_nut_dll void ButtonImage(
		const Image& image,
		const ImU32& normal,
		const ImU32& hovered,
		const ImU32& pressed
	);

};
