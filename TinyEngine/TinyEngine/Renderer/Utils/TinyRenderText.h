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

te_struct TinyRenderTextVertice {

	tiny_vec4 Location;
	tiny_vec2 UV;

};

te_struct TinyRenderTextVertex {

	TinyRenderTextVertice Vertices[ TinyQuadVerticeCount ];

};

te_struct TinyRenderTextParameters {

	tiny_mat4 Transform{ 1.f };
	tiny_vec4 Background{ };
	tiny_vec4 Foreground{ };

};

te_struct TinyRenderTextContext {

	TinyAsset Font{ };
	tiny_vec4 Background{ };
	tiny_vec4 Foreground{ };
	float Size	  = .0f;
	float Spacing = .0f;
	tiny_mat4 Transform;
	tiny_string Text{ };

	TinyRenderTextContext( );

	TinyRenderTextContext( const TinyAsset& font, float size, const tiny_string& text );

	TinyRenderTextContext( 
		const TinyAsset& font,
		const tiny_color& color,
		float size, 
		const tiny_string& text 
	);

};
