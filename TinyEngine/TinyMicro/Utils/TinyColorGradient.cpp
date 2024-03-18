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
 * @creation : 01/01/2024
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#include <TinyMicro/__tiny_micro_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
tiny_color_gradient::tiny_color_gradient( )
	: Colors{ }
{ }

tiny_color_gradient::tiny_color_gradient(
	const tiny_color& c0,
	const tiny_color& c1,
	const tiny_color& c2,
	const tiny_color& c3
) : Colors{ c0, c1, c2, c3 }
{ }

tiny_color tiny_color_gradient::Caculate( float scalar ) {
	return { };//Colors[ 0 ] + Colors[ 1 ] * cosf( 6.28318f * ( Colors[ 2 ] * scalar + Colors[ 3 ] ) );
}
