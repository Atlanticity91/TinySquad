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

#include "TinyDefaultVertex.h"

static const c_string TinyDefaultSpriteFragment = R"(
#version 450 core
#pragma shader_stage( fragment )
#extension GL_EXT_nonuniform_qualifier : require

tiny_sampler_list( s_Textures );

layout( location=0 ) in TinyVertexSCV { 
	vec4 Color;
	vec2 UV;
	int TextureSlot;
	int TextureCount;
} scv_vertex;

layout( location=TinyOutputID_Color ) out vec4 o_Colors;

void main( ) {
	o_Colors = tiny_texture( s_Textures, scv_vertex.TextureSlot, scv_vertex.UV ) * scv_vertex.Color;
}
)";

static const c_string TinyDefaultTextFragment = R"(
#version 450 core
#pragma shader_stage( fragment )

tiny_sampler2D( 0, s_Font );

struct TinyVertexSCV { 
	vec2 UV;
	vec4 Background;
	vec4 Foreground;
};

layout( location=0 ) flat in TinyVertexSCV scv_vertex;

layout( location=TinyOutputID_Color ) out vec4 o_Colors;

float msdf_median( vec3 msdf ) {
	float min_rg  = min( r, g );
	float max_rg  = max( r, g );
	float min_rgb = min( max_rg, b );

    return max( min_rg, min_rgb );
}

const vec2 msdf_range = vec2( 2.0 );
const vec2 msdf_miter = vec2( 1.0 );

float msdf_px_range( ) {
    vec2 range = msdf_range / vec2( textureSize( s_Font, 0 ) );
    vec2 size  = msdf_miter / fwidth( scv_vertex.UV );

    return max( 0.5 * dot( range, size ), 1.0 );
}

void main( ) {
    vec3 msdf	   = texture( s_Font, scv_vertex.UV ).rgb;
    float median   = msdf_median( msdf );
    float distance = msdf_px_range( ) * ( median - 0.5 );
    float opacity  = clamp( distance + 0.5, 0.0, 1.0 );

	if ( opacity == 0.0 )
		discard;

    o_Colors = mix( scv_vertex.Background, scv_vertex.Foreground, opacity );
}
)";
