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

	namespace Theme {

		constexpr auto accent = IM_COL32( 236, 158, 36, 255 );
		constexpr auto highlight = IM_COL32( 39, 185, 242, 255 );
		constexpr auto niceBlue = IM_COL32( 83, 232, 254, 255 );
		constexpr auto compliment = IM_COL32( 78, 151, 166, 255 );
		constexpr auto background = IM_COL32( 36, 36, 36, 255 );
		constexpr auto backgroundDark = IM_COL32( 26, 26, 26, 255 );
		constexpr auto Titlebar = IM_COL32( 21, 21, 21, 255 );
		constexpr auto propertyField = IM_COL32( 15, 15, 15, 255 );
		constexpr auto text = IM_COL32( 192, 192, 192, 255 );
		constexpr auto textBrighter = IM_COL32( 210, 210, 210, 255 );
		constexpr auto textDarker = IM_COL32( 128, 128, 128, 255 );
		constexpr auto textError = IM_COL32( 230, 51, 51, 255 );
		constexpr auto muted = IM_COL32( 77, 77, 77, 255 );
		constexpr auto groupHeader = IM_COL32( 47, 47, 47, 255 );
		constexpr auto selection = IM_COL32( 237, 192, 119, 255 );
		constexpr auto selectionMuted = IM_COL32( 237, 201, 142, 23 );
		constexpr auto backgroundPopup = IM_COL32( 50, 50, 50, 255 );
		constexpr auto validPrefab = IM_COL32( 82, 179, 222, 255 );
		constexpr auto invalidPrefab = IM_COL32( 222, 43, 43, 255 );
		constexpr auto missingMesh = IM_COL32( 230, 102, 76, 255 );
		constexpr auto meshNotSet = IM_COL32( 250, 101, 23, 255 );

	};

	tn_struct Image {

		TinyGraphicTexture Texture{ };
		ImTextureID Descriptor = nullptr;

	};

	tn_struct Icon {

		using Callback_t = std::function<void( TinyNut* )>;
		
		Image Icon;
		Callback_t Callback;

		operator ImTextureID ( ) const { return Icon.Descriptor; };

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

	tiny_nut_dll void ButtonImage(
		const Image& image,
		const ImU32& normal,
		const ImU32& hovered,
		const ImU32& pressed,
		const ImRect& bounding
	);

};
