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
 * @creation : 12/03/2024
 * @version  : 2024.2.6
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include <TinyEngine/Renderer/Batchs/TinyRenderBatchManager.h>

#define _TinyRenderDebugPrimitiveR2( NAME, SRC, DST, COLOR )\
	auto NAME = TinyRenderDebugPrimitive( SRC, DST, COLOR );\
	NAME.Type = TRD_PRIMITIVE_RECTANGLE
#define _TinyRenderDebugPrimitiveR( NAME, SRC, DST )\
	_TinyRenderDebugPrimitiveR2( NAME, SRC, DST, TinyPalettes::SUN_FLOWER )

tiny_enum( TinyRenderDebugPrimitives ) {

	TRD_PRIMITIVE_LINE = 0,
	TRD_PRIMITIVE_RECTANGLE,
	TRD_PRIMITIVE_CIRCLE

};

te_struct TinyRenderDebugPrimitive {

	TinyRenderDebugPrimitives Type;
	tiny_vec2 Src;
	tiny_vec2 Dst;
	tiny_color Color;

	TinyRenderDebugPrimitive( const tiny_vec2& position, float radius, float thickness );

	TinyRenderDebugPrimitive( 
		const tiny_vec2& position, 
		float radius,
		float thickness,
		const tiny_color& color 
	);

	TinyRenderDebugPrimitive( const tiny_vec2& src, const tiny_vec2& dst );

	TinyRenderDebugPrimitive(
		const tiny_vec2& src,
		const tiny_vec2& dst,
		const tiny_color& color
	);

	TinyRenderDebugPrimitive(
		TinyRenderDebugPrimitives type,
		const tiny_vec2& src,
		const tiny_vec2& dst,
		const tiny_color& color
	);

};
