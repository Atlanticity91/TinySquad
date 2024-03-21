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

#define TINY_QUAD_VERTICE_COUNT tiny_cast( 4, tiny_uint )
#define TINY_QUAD_INDEX_COUNT tiny_cast( 6, tiny_uint ) 

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

static const tiny_uint TinyQuadVerticeCount = TINY_QUAD_VERTICE_COUNT;
static const tiny_uint TinyQuadIndexCount   = TINY_QUAD_INDEX_COUNT;

static const tiny_vec4 TinyQuadVertex[ TinyQuadVerticeCount ] = {
	{ -.5f, -.5f, .0f, 1.f },
	{  .5f, -.5f, .0f, 1.f },
	{  .5f,  .5f, .0f, 1.f },
	{ -.5f,  .5f, .0f, 1.f }
};

static const tiny_uint TinyQuadInex[ TinyQuadIndexCount ] = {
	0, 1, 2,
	2, 0, 3
};
