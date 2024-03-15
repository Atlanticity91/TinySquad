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
 * @creation : 13/03/2024
 * @version  : 2024.2.6
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "TinyRenderDebugPrimitive.h"

// === VERTEX INPUT ===
te_struct TinyRenderDebugVertex {

	tiny_vec4 Position{ };
	tiny_vec4 Color{ };

};

te_struct TinyRenderDebugShader {

	tiny_uint ShaderID			= 0;
	VkShaderStageFlagBits Stage = VK_SHADER_STAGE_VERTEX_BIT;
	tiny_string Name			= "";
	tiny_string Source			= "";

};

static const tiny_string TinyDebugLineVertex = tiny_string{
	R"(
		#version 450 core
		#pragma shader_stage( vertex )

		layout( location=0 ) in vec4 Position;
		layout( location=1 ) in vec4 Color;

		layout( location=0 ) out vec4 scm_color;

		void main( ) {
			gl_Position = Position;
			scm_color = Color;
		}
	)"
};

static const tiny_string TinyDebugLineFragment = tiny_string{
	R"(
		#version 450 core
		#pragma shader_stage( fragment )

		layout( location=TinyOutputID_Color ) out vec4 o_Colors;

		layout( location=0 ) in vec4 scm_color;

		void main( ) {
			o_Colors = scm_color;
		}
	)"
};

static const tiny_string TinyDebugCircleVertex = tiny_string{ 
	R"(
		#version 450 core
		#pragma shader_stage( vertex )

		layout( location=0 ) in vec4 Position;
		layout( location=1 ) in vec4 Color;

		layout( location=0 ) out vec4 scm_color;

		void main( ) {
			gl_Position = Position;
			scm_color = Color;
		}
	)"
};

static const tiny_string TinyDebugCircleFragment = tiny_string{ 
	R"(
		#version 450 core
		#pragma shader_stage( fragment )

		layout( location=TinyOutputID_Color ) out vec4 o_Colors;

		layout( location=0 ) in vec4 scm_color;

		void main( ) {
			o_Colors = scm_color;
		}
	)"
};
