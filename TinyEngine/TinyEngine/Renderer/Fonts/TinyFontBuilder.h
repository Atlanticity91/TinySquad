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
 * @creation : 26/03/2023
 * @version  : 2024.2.7
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include <TinyEngine/Renderer/Textures/TinyTextureLutManager.h>

te_struct TinyCharVertice {

	tiny_vec4 Location{ };
	tiny_vec2 UV{ };

};

te_struct TinyCharGeometry {

	float Advance = 0.f;
	TinyCharVertice Vertices[ 4 ];

};

te_struct TinyFontBuilder {

	float Scale;
	MsdfBitmap Bitmap;

	TinyFontBuilder( )
		: Scale{ 1.f },
		Bitmap{ }
	{ };

	TinyFontBuilder( const MsdfBitmap& bitmap )
		: Scale{ 1.f },
		Bitmap{ bitmap } 
	{ };

};
