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
 * @creation : 22/10/2023
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
TinyGraphicBufferBinder::TinyGraphicBufferBinder( )
{ }

bool TinyGraphicBufferBinder::Read( 
	TinyGraphicContext& context, 
	const TinyGraphicBufferBind& bind
) {
	auto storage = tiny_cast( nullptr, native_pointer );
	auto state   = bind.Data && bind.Offset + bind.Size <= bind.Buffer.GetProperties( ).Size;

	if ( state ) {
		auto* memory = Map( context.Logical, bind, storage );

		state = memory != nullptr;

		if ( state ) {
			Tiny::Memcpy( storage, bind.Data, tiny_cast( bind.Size, tiny_ulong ) );

			Unmap( context.Logical, memory );
		}
	}

	return state;
}

bool TinyGraphicBufferBinder::Write(
	TinyGraphicContext& context,
	const TinyGraphicBufferBind& bind
) {
	auto storage = tiny_cast( nullptr, native_pointer );
	auto state   = bind.Data && bind.Offset + bind.Size <= bind.Buffer.GetProperties( ).Size;

	if ( state ) {
		auto* memory = Map( context.Logical, bind, storage );

		state = memory != nullptr;

		if ( state ) {
			Tiny::Memcpy( bind.Data, storage, tiny_cast( bind.Size, tiny_ulong ) );

			Unmap( context.Logical, memory );
		}
	}

	return state;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE ===
////////////////////////////////////////////////////////////////////////////////////////////
VkDeviceMemory TinyGraphicBufferBinder::Map(
	TinyGraphicLogical& logical,
	const TinyGraphicBufferBind& bind,
	native_pointer& storage
) {
	auto& properties = bind.Buffer.GetProperties( );
	auto memory		 = bind.Buffer.GetMemory( ).Memory;
	auto size		 = bind.Size > 0 ? bind.Size : properties.Size;

	if ( bind.Offset + size > properties.Size )
		size = properties.Size - bind.Offset;

	if ( !vk::Check( vkMapMemory( logical, memory, bind.Offset, size, VK_NULL_FLAGS, tiny_rvalue( storage ) ) ) )
		memory = VK_NULL_HANDLE;
	
	return memory;
}

void TinyGraphicBufferBinder::Unmap( 
	TinyGraphicLogical& logical, 
	VkDeviceMemory memory 
) {
	vkUnmapMemory( logical, memory );
}
