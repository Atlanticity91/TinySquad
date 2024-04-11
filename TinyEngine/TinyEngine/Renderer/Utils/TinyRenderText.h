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
 * @creation : 19/03/2024
 * @version  : 2024.2.7
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "TinyRenderLight.h"

#define TINY_MAX_FONTS tiny_cast( 8, tiny_uint )

static constexpr tiny_uint TinyMaxFonts = TINY_MAX_FONTS;

te_struct TinyRenderTextVertice {

	tiny_vec4 Location;
	tiny_vec2 UV;
	tiny_uint Parameters;

};

te_struct TinyRenderTextVertex {

	TinyRenderTextVertice Vertices[ TinyQuadVerticeCount ];

};

te_struct TinyRenderTextParameters {

	tiny_vec4 Background{ };
	tiny_vec4 Foreground{ };
	tiny_vec2 Range{ 2.f };
	tiny_vec2 Miter{ 1.f };
	tiny_uint Font{ 0 };

};

te_struct TinyRenderTextContext {

	TinyAssetHandle Material;
	TinyAssetHandle Font;
	tiny_vec4 Background;
	tiny_vec4 Foreground;
	float Size;
	float Spacing;
	tiny_vec2 Location;
	tiny_string Text;

	TinyRenderTextContext( );

	TinyRenderTextContext( 
		const TinyAssetHandle& material,
		const TinyAssetHandle& font, 
		float size, 
		const tiny_string& text 
	);

	TinyRenderTextContext( 
		const TinyAssetHandle& material,
		const TinyAssetHandle& font,
		const tiny_color& color,
		float size, 
		const tiny_string& text 
	);

};
