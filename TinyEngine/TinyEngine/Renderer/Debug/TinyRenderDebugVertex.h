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
 * @creation : 21/03/2024
 * @version  : 2024.2.7
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "TinyRenderDebugPrimitive.h"

te_struct TinyRenderDebugLineVertice {

	tiny_vec4 Position{ };
	tiny_vec4 Color{ };

};

te_struct TinyRenderDebugLine {

	TinyRenderDebugLineVertice Vertice[ 2 ];

};

te_struct TinyRenderDebugIndex {

	tiny_uint Index[ TinyQuadIndexCount ];

};

te_struct TinyRenderDebugCircleVertice {

	tiny_vec4 Position{ };
	tiny_vec4 Circle{ };
	tiny_vec4 Color{ };

};

te_struct TinyRenderDebugCircle {

	TinyRenderDebugCircleVertice Vertice[ TinyQuadVerticeCount ];

};

te_struct TinyRenderDebugShader {

	tiny_uint ShaderID			= 0;
	VkShaderStageFlagBits Stage = VK_SHADER_STAGE_VERTEX_BIT;
	tiny_string Name			= "";
	tiny_string Source			= "";

};
