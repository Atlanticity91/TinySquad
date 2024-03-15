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
	float radius
)
	: TinyRenderDebugPrimitive{ position, radius, TinyPalettes::SUN_FLOWER }
{ }

TinyRenderDebugPrimitive::TinyRenderDebugPrimitive(
	const tiny_vec2& position,
	float radius,
	const tiny_color& color
) 
	: Type{ TRD_PRIMITIVE_CIRCLE },
	Src{ position },
	Dst{ radius, .0f },
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
