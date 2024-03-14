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
 * @creation : 26/11/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "TinyRenderBatch.h"

te_struct TinyRenderDraw2DContext {

	TinyAsset Material{ };
	tiny_list<TinyTexture2D*> Textures{ };
	TinyRenderSprite Sprite{ };
	tiny_mat4 Tranform{ };

};

te_struct TinyRenderDraw3DContext {

	TinyAsset Material{ };
	tiny_list<TinyTexture2D*> Textures{ };
	tiny_list<tiny_uint> Indexes{ };
	tiny_list<tiny_vec4> Vertices{ };
	tiny_list<tiny_vec2> Uvs{ };

};
