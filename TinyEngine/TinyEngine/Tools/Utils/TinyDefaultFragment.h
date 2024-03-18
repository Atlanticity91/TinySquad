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

static const c_string TinyDefaultFragment = R"(
#version 450 core
#pragma shader_stage( fragment )

layout( location=TinyOutputID_Color ) out vec4 o_Colors;

struct TinyRenderData {	
	vec4 Color;
	vec2 UV;
};

layout( location=0 ) in TinyRenderData sd_sprite;

tiny_sampler2D( 0, t_Albedo );

void main( ) {
	o_Colors = texture( t_Albedo, sd_sprite.UV ) * sd_sprite.Color;
}

)";
