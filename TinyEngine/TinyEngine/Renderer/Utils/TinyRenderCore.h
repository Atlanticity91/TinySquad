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
 * @creation : 19/03/2024
 * @version  : 2024.2.7
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include <TinyEngine/Renderer/Uniforms/TinyRenderUniformManager.h>

#define TINY_MAX_VERTEX 1024 //16384

#define TINY_RENDER_SET_CORE 0 
#define TINY_RENDER_SET_RENDER 1
#define TINY_RENDER_SET_TEXTURE 2
#define TINY_RENDER_SET_LIGHT 3

#define TINY_OUTPUT_COLOR 0 
#define TINY_OUTPUT_POSITION 1
#define TINY_OUTPUT_NORMAL 2
#define TINY_OUTPUT_SPECULAR 3
#define TINY_OUTPUT_EMISSIVE 4

static const tiny_uint TinyMaxVertices = TINY_MAX_VERTEX;

tiny_enum( TinyRenderSetIDs ) { 

	TRS_ID_CORE	   = TINY_RENDER_SET_CORE,
	TRS_ID_RENDER  = TINY_RENDER_SET_RENDER,
	TRS_ID_TEXTURE = TINY_RENDER_SET_TEXTURE,
	TRS_ID_LIGHT   = TINY_RENDER_SET_LIGHT

};

tiny_enum( TinyRenderOutputIDs ) { 

	TRO_ID_COLOR	= TINY_OUTPUT_COLOR,
	TRO_ID_POSITION = TINY_OUTPUT_POSITION,
	TRO_ID_NORMAL	= TINY_OUTPUT_NORMAL,
	TRO_ID_SPECULAR = TINY_OUTPUT_SPECULAR,
	TRO_ID_EMISSIVE = TINY_OUTPUT_EMISSIVE,

	TRO_ID_ALBEDO	= TRO_ID_COLOR

};

te_struct TinyRenderCore {

	tiny_mat4 Projection{ 1.f };
	tiny_mat4 View{ 1.f };
	tiny_mat4 ProjView{ 1.f };
	tiny_mat4 Inverse{ 1.f };
	float Time_f  = 0.f;
	double Time_d = 0.0;

};
