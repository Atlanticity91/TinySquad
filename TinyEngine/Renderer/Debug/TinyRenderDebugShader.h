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

		layout( location=0 ) out vec4 scv_color;

		tiny_ubo( TinySetID_Core, 0, TinyUBOContext ) {
			mat4 Projection;
			mat4 View;
			mat4 ProjView;
			mat4 Inverse;
			float Time_f;
			double Time_d;
		} ubo_context;

		void main( ) {
			gl_Position = ubo_context.ProjView * Position;
			scv_color   = Color;
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

		layout( location=0 ) in vec4 Circle;
		layout( location=1 ) in vec4 Color;

		layout( location=0 ) out vec4 scv_circle;
		layout( location=1 ) out vec4 scv_color;

		vec4 TinyCoords[6] = {
			vec4( -0.5, -0.5, 0.0, 1.0 ),
			vec4(  0.5, -0.5, 0.0, 1.0 ),
			vec4(  0.5,  0.5, 0.0, 1.0 ),

			vec4(  0.5,  0.5, 0.0, 1.0 ),
			vec4( -0.5, -0.5, 0.0, 1.0 ),
			vec4( -0.5,  0.5, 0.0, 1.0 )
		};

		tiny_ubo( TinySetID_Core, 0, TinyUBOContext ) {
			mat4 Projection;
			mat4 View;
			mat4 ProjView;
			float Time_f;
			double Time_d;
		} ubo_context;

		mat4 translate( ) {
			return mat4(1.0, 0.0, 0.0, Circle.x,
						0.0, 1.0, 0.0, Circle.y,
						0.0, 0.0, 1.0, 0.0,
						0.0, 0.0, 0.0, 1.0);
		}

		mat4 scale( ) {
			return mat4(Circle.z, 0.0, 0.0, 0.0,
						0.0, Circle.z, 0.0, 0.0,
						0.0, 0.0, 1.0, 0.0,
						0.0, 0.0, 0.0, 1.0);
		}

		void main( ) {
			mat4 t = translate( ) * scale( );

			gl_Position = ubo_context.ProjView * t * TinyCoords[ gl_VertexIndex ];
			scv_circle  = Circle;
			scv_color   = Color;
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

		const float attenuation = 0.5;

		void main( ) {
			vec2 local_pos   = vec2( scv_circle.x, scv_circle.y );
			float distance   = 1.0 - length( local_pos );
			float fade_value = smoothstep( 0.0, attenuation, distance );
			
			fade_value *= smoothstep( scv_circle.w + attenuation, scv_circle.w, distance );

			if ( fade_value == 0.0 )
				discard;
			
			o_Colors = scv_color;
			o_Colors.a *= fade_value;
		}
	)"
};
