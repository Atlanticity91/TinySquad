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

te_struct TinyRenderDebugLineVertice {

	tiny_vec4 Position{ };
	tiny_vec4 Color{ };

};

te_struct TinyRenderDebugLine {

	TinyRenderDebugLineVertice Vertice[ 2 ];

};

te_struct TinyRenderDebugIndex {

	tiny_uint Index[ 6 ] = {
		0, 1, 2,
		2, 0, 3
	};

};

te_struct TinyRenderDebugCircleVertice {

	tiny_vec4 Position{ };
	tiny_vec4 Circle{ };
	tiny_vec4 Color{ };

};

te_struct TinyRenderDebugCircle {

	TinyRenderDebugCircleVertice Vertice[ 4 ];

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

		layout( location=0 ) in vec4 v_Position;
		layout( location=1 ) in vec4 v_Color;

		layout( location=0 ) out vec4 scv_color;

		void main( ) {
			gl_Position = v_Position;
			
			scv_color   = v_Color;
		}
	)"
};

static const tiny_string TinyDebugLineFragment = tiny_string{
	R"(
		#version 450 core
		#pragma shader_stage( fragment )

		layout( location=TinyOutputID_Color ) out vec4 o_Colors;

		layout( location=0 ) in vec4 scv_color;

		void main( ) {
			o_Colors = scv_color;
		}
	)"
};

static const tiny_string TinyDebugCircleVertex = tiny_string{ 
	R"(
		#version 450 core
		#pragma shader_stage( vertex )

		layout( location=0 ) in vec4 v_Position;
		layout( location=1 ) in vec4 v_Circle;
		layout( location=2 ) in vec4 v_Color;

		layout( location=0 ) out vec4 scv_circle;
		layout( location=1 ) out vec4 scv_color;
		
		void main( ) {
			gl_Position = v_Position;

			scv_circle  = v_Circle;
			scv_color   = v_Color;
		}
	)"
};

static const tiny_string TinyDebugCircleFragment = tiny_string{ 
	R"(
		#version 450 core
		#pragma shader_stage( fragment )

		layout( location=TinyOutputID_Color ) out vec4 o_Colors;

		layout( location=0 ) in vec4 scv_circle;
		layout( location=1 ) in vec4 scv_color;

		const float attenuation = 0.005;

		void main( ) {
			vec2 local_pos	  = vec2( scv_circle.x, scv_circle.y );
			float distance	  = 1.0 - length( local_pos );
			float fade_scalar = smoothstep( 0.0, attenuation, distance ) *
								smoothstep( scv_circle.w + attenuation, scv_circle.w, distance );

			// float angle = (atan(local_pos.x, local_pos.y) + TinyPI) / (TinyPI * 2);
			// angle < 0.25 || angle > 0.5 -> discard
			// Draw an arc that cover 1/4 of the circle

			if ( fade_scalar == 0.0 )
				discard;
	
			o_Colors = vec4( scv_color.rgb, scv_color.a * fade_scalar );
		}
	)"
};
