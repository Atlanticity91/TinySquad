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

		layout( location=0 ) out vec4 scv_circle;
		layout( location=1 ) out vec4 scv_color;

		vec4 TinyCoords[ 6 ] = {
			vec4( -0.5, -0.5, 0.0, 1.0 ),
			vec4(  0.5, -0.5, 0.0, 1.0 ),
			vec4(  0.5,  0.5, 0.0, 1.0 ),

			vec4(  0.5,  0.5, 0.0, 1.0 ),
			vec4( -0.5, -0.5, 0.0, 1.0 ),
			vec4( -0.5,  0.5, 0.0, 1.0 )
		};

		vec2 TinyUVs[ 6 ] = {	
			vec2( -1.0, -1.0 ),
			vec2(  1.0, -1.0 ),
			vec2(  1.0,  1.0 ),

			vec2(  1.0,  1.0 ),
			vec2( -1.0, -1.0 ),
			vec2( -1.0,  1.0 ),
		};

		tiny_ubo( TinySetID_Core, 0, TinyUBOContext ) {
			mat4 Projection;
			mat4 View;
			mat4 ProjView;
			float Time_f;
			double Time_d;
		} ubo_context;

		tiny_ubo( TinySetID_Render, 0, TinyUBOTransforms ) {
			mat4 Transfroms[ 1024 ];	
		} ubo_transforms;
		
		struct TinyRenderSprite {
			vec4 Color;
			vec4 UV;
		};

		tiny_ubo( TinySetID_Render, 1, TinyUBOSprites ) {
			TinyRenderSprite Sprites[ 1024 ];
		} ubo_sprites;

		mat4 Transform( vec4 transform ) {
			mat4 identity = mat4(
				vec4( 1.0, 0.0, 0.0, 0.0 ),
				vec4( 0.0, 1.0, 0.0, 0.0 ),
				vec4( 0.0, 0.0, 1.0, 0.0 ),
				vec4( 0.0, 0.0, 0.0, 1.0 )
			);

			mat4 translation = identity;

			translation[ 3 ] = identity[ 0 ] * ( transform.x + 0.5 * transform.z )+ 
							   identity[ 1 ] * ( transform.y + 0.5 * transform.z ) + 
							   identity[ 2 ] * 0.0 + 
							   identity[ 3 ];

			mat4 scale = identity;

			scale[ 0 ] = translation[ 0 ] * transform.z;
			scale[ 1 ] = translation[ 1 ] * transform.z;
			scale[ 2 ] = translation[ 2 ];
			scale[ 3 ] = translation[ 3 ];

			return ubo_context.ProjView * ( translation * scale );
		}

		void main( ) {
			vec2 quad_uv = TinyUVs[ gl_VertexIndex ];
			TinyRenderSprite sprite = ubo_sprites.Sprites[ gl_InstanceIndex ];
			
			gl_Position = Transform( sprite.UV ) * TinyCoords[ gl_VertexIndex ];
			scv_circle  = vec4( quad_uv.x, quad_uv.y, sprite.UV.z, sprite.UV.w );
			scv_color   = sprite.Color;
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
