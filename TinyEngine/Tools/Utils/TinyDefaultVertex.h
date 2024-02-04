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

static const c_string TinyDefaultVertex = R"(
#version 450 core
#pragma shader_stage( vertex )

vec4 TinyCoords[6] = {
	vec4( -0.5, -0.5, 0.0, 1.0 ),
	vec4(  0.5, -0.5, 0.0, 1.0 ),
	vec4(  0.5,  0.5, 0.0, 1.0 ),

	vec4(  0.5,  0.5, 0.0, 1.0 ),
	vec4( -0.5, -0.5, 0.0, 1.0 ),
	vec4( -0.5,  0.5, 0.0, 1.0 )
};

vec2 TinyUVs[6] = {	
	vec2( 0.0, 0.0 ),
	vec2( 1.0, 0.0 ),
	vec2( 1.0, 1.0 ),

	vec2( 1.0, 1.0 ),
	vec2( 0.0, 0.0 ),
	vec2( 0.0, 1.0 ),
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

struct TinyRenderData {	
	vec4 Color;
	vec2 UV;
};

layout( location=0 ) out TinyRenderData sd_sprite;

void main( ) {
	gl_Position = ubo_transforms.Transfroms[ gl_InstanceIndex ] * TinyCoords[ gl_VertexIndex ];
	sd_sprite.Color = ubo_sprites.Sprites[ gl_InstanceIndex ].Color;

	if ( TinyUVs[ gl_VertexIndex ].x < 1.0 )
		sd_sprite.UV.x = ubo_sprites.Sprites[ gl_InstanceIndex ].UV.x;
	else
		sd_sprite.UV.x = ubo_sprites.Sprites[ gl_InstanceIndex ].UV.z;

	if ( TinyUVs[ gl_VertexIndex ].y < 1.0 )
		sd_sprite.UV.y = ubo_sprites.Sprites[ gl_InstanceIndex ].UV.y;
	else
		sd_sprite.UV.y = ubo_sprites.Sprites[ gl_InstanceIndex ].UV.w;
}
)";
