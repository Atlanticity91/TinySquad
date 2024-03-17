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

#include <TinyEngine/__tiny_engine_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyRenderDebugPrimitive::TinyRenderDebugPrimitive(
	const tiny_vec2& position,
	float diameter
)
	: TinyRenderDebugPrimitive{ position, diameter, TinyPalettes::SUN_FLOWER }
{ }

TinyRenderDebugPrimitive::TinyRenderDebugPrimitive( 
	const tiny_vec2& position, 
	float diameter,
	float thickness
)
	: TinyRenderDebugPrimitive{ position, diameter, ( .5f * diameter ) * thickness, TinyPalettes::SUN_FLOWER }
{ }

TinyRenderDebugPrimitive::TinyRenderDebugPrimitive( 
	const tiny_vec2& position, 
	float diameter,
	const tiny_color& color
)
	: TinyRenderDebugPrimitive{ position, diameter, ( .5f * diameter ) *.0001f, color }
{ }

TinyRenderDebugPrimitive::TinyRenderDebugPrimitive(
	const tiny_vec2& position,
	float diameter,
	float thickness,
	const tiny_color& color
) 
	: Type{ TRD_PRIMITIVE_CIRCLE },
	Src{ position },
	Dst{ diameter, thickness },
	Color{ color }
{ }

TinyRenderDebugPrimitive::TinyRenderDebugPrimitive( 
	const tiny_vec2& src, 
	const tiny_vec2& dst 
)
	: TinyRenderDebugPrimitive{ src, dst, TinyPalettes::SUN_FLOWER }
{ }

TinyRenderDebugPrimitive::TinyRenderDebugPrimitive(
	const tiny_vec2& src,
	const tiny_vec2& dst,
	const tiny_color& color
)
	: TinyRenderDebugPrimitive{ TRD_PRIMITIVE_LINE, src, dst, color } 
{ }

TinyRenderDebugPrimitive::TinyRenderDebugPrimitive(
	TinyRenderDebugPrimitives type,
	const tiny_vec2& src,
	const tiny_vec2& dst,
	const tiny_color& color
)
	: Type{ type },
	Src{ src },
	Dst{ dst },
	Color{ color } 
{ }
