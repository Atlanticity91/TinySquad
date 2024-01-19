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
 * @creation : 26/12/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include <TinyEngine/Renderer/Uniforms/TinyRenderUniformManager.h>

#define TINY_MAX_INSTANCE 1024
#define TINY_MAX_VERTICES 4 * TINY_MAX_INSTANCE
#define TINY_MAX_INDEX 6 * TINY_MAX_INSTANCE
#define TINY_MAX_LIGHT 512

#define TINY_RENDER_SET_CONTEXT 0 
#define TINY_RENDER_SET_RENDER 1
#define TINY_RENDER_SET_LIGHT 2
#define TINY_RENDER_SET_TEXTURE 3

typedef tiny_mat4 TinyRenderTransform;
typedef tiny_uint TinyRenderIndex;
typedef tiny_vec4 TinyRenderVertex;
typedef tiny_vec2 TinyRenderUV;

te_struct TinyRenderSprite {

	tiny_vec4 Color;
	tiny_vec4 UV;

};

te_struct TinyRenderLight {

	tiny_vec4 Color;

};
