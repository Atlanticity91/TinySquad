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
 * @creation : 14/10/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "TinyRange.h"

#define tiny_remap_f( ... ) Tiny::remap<tiny_vec2, float>( __VA_ARGS__ )
#define tiny_remap_f2( SRC_MIN, SRC_MAX, DST_MIN, DST_MAX, VALUE )\
	tiny_remap_f( tiny_vec2{ SRC_MIN, SRC_MAX }, tiny_vec2{ DST_MIN, DST_MAX }, VALUE )
#define tiny_remap_i( ... ) Tiny::remap<tiny_point, tiny_int>( __VA_ARGS__ )
#define tiny_remap_i2( SRC_MIN, SRC_MAX, DST_MIN, DST_MAX, VALUE )\
	tiny_remap_f( tiny_point{ SRC_MIN, SRC_MAX }, tiny_point{ DST_MIN, DST_MAX }, VALUE )

namespace Tiny {

	template<typename Range, typename Type>
	tiny_inline Type remap( const Range& src, const Range& dst, Type value ) {
		return dst.x + ( ( ( value - src.x ) / ( src.y - src.x ) ) * ( dst.y - dst.x ) );
	};

};
