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

#include "TinyRenderSprite.h"

typedef tiny_uint TinyRenderIndex;

te_struct TinyRenderVertice {

	tiny_vec4 Location{ };
	tiny_vec2 UV{ };

};

te_struct TinyRenderVertexContext {

	TinyAsset Material{ };
	tiny_list<TinyTexture2D*> Textures{ };
	tiny_list<TinyRenderIndex> Indexes{ };
	tiny_list<TinyRenderVertice> Vertex{ };

};
