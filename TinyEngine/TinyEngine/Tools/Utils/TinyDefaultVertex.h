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
 * @creation : 04/02/2023
 * @version  : 2024.1.2
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include <TinyEngine/Tools/Fonts/TinyFont.h>

static const c_string TinyDefaultSpriteVertex = R"(
#version 450 core
#pragma shader_stage( vertex )

layout( location=0 ) in vec4 v_Position;
layout( location=1 ) in vec4 v_Texture;
layout( location=2 ) in vec4 v_Color;

tiny_ubo( TinySetID_Core, 0, TinyUBOContext ) {

	mat4 Projection;
	mat4 View;
	mat4 ProjView;
	mat4 Inverse;
	float Time_f;
	double Time_d;

} ubo_context;

layout( location=0 ) out TinyVertexSCV { 
	vec4 Color;
	vec2 UV;
	int TextureSlot;
	int TextureCount;
} scv_vertex;

void main( ) {
	gl_Position = ubo_context.ProjView * v_Position;

	scv_vertex.Color 		= v_Color;
	scv_vertex.UV 			= vec2( v_Texture.x, v_Texture.y );
	scv_vertex.TextureSlot  = int( v_Texture.z );
	scv_vertex.TextureCount = int( v_Texture.w );
}
)";

static const c_string TinyDefaultTextVertex = R"(
#version 450 core
#pragma shader_stage( vertex )

layout( location=0 ) in vec4 v_Position;
layout( location=1 ) in vec2 v_UV;
layout( location=2 ) in uint v_Parameters;

tiny_ubo( TinySetID_Core, 0, TinyUBOContext ) {

	mat4 Projection;
	mat4 View;
	mat4 ProjView;
	mat4 Inverse;
	float Time_f;
	double Time_d;

} ubo_context;

struct TinyTextParameters {
	
	vec4 Background;
	vec4 Foreground;
	vec2 Range;
	vec2 Miter;
	uint Font;

};

tiny_ubo( TinySetID_Render, 0, TinyUBOParameters ) {

	TinyTextParameters Parameters[ TinyMaxFonts ];

} ubo_parameters;

layout( location=0 ) out TinyVertexSCV { 
	vec4 Background;
	vec4 Foreground;
	vec2 UV;
	vec2 Range;
	vec2 Miter;
	uint Font;
} scv_vertex;

void main( ) {
	gl_Position = ubo_context.ProjView * v_Position;
	
	scv_vertex.Background = ubo_parameters.Parameters[ v_Parameters ].Background;
	scv_vertex.Foreground = ubo_parameters.Parameters[ v_Parameters ].Foreground;
	scv_vertex.UV		  = v_UV;
	scv_vertex.Range	  = ubo_parameters.Parameters[ v_Parameters ].Range;
	scv_vertex.Miter	  = ubo_parameters.Parameters[ v_Parameters ].Miter;
	scv_vertex.Font		  = ubo_parameters.Parameters[ v_Parameters ].Font;
}
)";
