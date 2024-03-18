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
 * @creation : 01/12/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "TinyGraphicBuffer.h"

tm_struct TinyGraphicBufferBind {

	TinyGraphicBuffer& Buffer;
	tiny_uint Offset;
	tiny_uint Size;
	c_pointer Data;

	TinyGraphicBufferBind( TinyGraphicBuffer& buffer, c_pointer data );

	TinyGraphicBufferBind(
		TinyGraphicBuffer& buffer,
		tiny_uint size,
		c_pointer data
	);

	TinyGraphicBufferBind(
		TinyGraphicBuffer& buffer,
		tiny_uint offset,
		tiny_uint size,
		c_pointer data
	);

	TinyGraphicBufferBind( const TinyGraphicBufferBind& other, c_pointer data );

};
