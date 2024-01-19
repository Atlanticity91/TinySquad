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

#include <TinyMicro/__tiny_micro_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyGraphicBufferBind::TinyGraphicBufferBind( TinyGraphicBuffer& buffer, c_ptr data )
	: TinyGraphicBufferBind{ buffer, 0, 0, data }
{ }

TinyGraphicBufferBind::TinyGraphicBufferBind(
	TinyGraphicBuffer& buffer,
	tiny_uint size,
	c_ptr data
)
	: TinyGraphicBufferBind{ buffer, 0, size, data }
{ }

TinyGraphicBufferBind::TinyGraphicBufferBind(
	TinyGraphicBuffer& buffer,
	tiny_uint offset,
	tiny_uint size,
	c_ptr data
)
	: Buffer{ buffer },
	Offset{ offset },
	Size{ size },
	Data{ data }
{ }

TinyGraphicBufferBind::TinyGraphicBufferBind( 
	const TinyGraphicBufferBind& other, 
	c_ptr data
)
	: TinyGraphicBufferBind{ other.Buffer, other.Offset, other.Size, data }
{ }
