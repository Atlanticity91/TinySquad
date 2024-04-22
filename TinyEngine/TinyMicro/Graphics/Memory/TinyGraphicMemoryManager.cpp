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
 * @creation : 23/10/2023
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
TinyGraphicMemoryManager::TinyGraphicMemoryManager( )
	: _properties{ }
{ }

bool TinyGraphicMemoryManager::Create( const TinyGraphicContext& graphic ) {
	vkGetPhysicalDeviceMemoryProperties( graphic.Physical, tiny_rvalue( _properties ) );

	return true;
}

bool TinyGraphicMemoryManager::Allocate(
	TinyGraphicContext& graphic,
	TinyGraphicMemory& memory, 
	VkImage& image 
) {
	VkMemoryRequirements requirements;

	vkGetImageMemoryRequirements( graphic.Logical, image, tiny_rvalue( requirements ) );

	memory.Size = tiny_cast( requirements.size, tiny_uint );

	return  Allocate( graphic, memory, requirements ) &&
			vk::Check( vkBindImageMemory( graphic.Logical, image, memory, 0 ) );
}

bool TinyGraphicMemoryManager::Allocate(
	TinyGraphicContext& graphic, 
	TinyGraphicMemory& memory,
	VkBuffer& buffer 
) {
	VkMemoryRequirements requirements;

	vkGetBufferMemoryRequirements( graphic.Logical, buffer, tiny_rvalue( requirements ) );

	memory.Size = tiny_cast( requirements.size, tiny_uint );

	return  Allocate( graphic, memory, requirements ) &&
			vk::Check( vkBindBufferMemory( graphic.Logical, buffer, memory, 0 ) );
}

void TinyGraphicMemoryManager::DeAllocate(
	TinyGraphicContext& graphic,
	TinyGraphicMemory& memory 
) {
	if ( vk::GetIsValid( memory.Memory ) ) {
		vkFreeMemory( graphic.Logical, memory.Memory, vk::GetAllocator( ) );

		memory.Memory = VK_NULL_HANDLE;
	}
}

void TinyGraphicMemoryManager::Terminate( const TinyGraphicContext& graphic ) {
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyGraphicMemoryManager::Allocate( 
	TinyGraphicContext& graphic,
	TinyGraphicMemory& memory, 
	VkMemoryRequirements& requirements 
) {
	auto alloc_info = VkMemoryAllocateInfo{ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO };

	alloc_info.pNext		   = VK_NULL_HANDLE;
	alloc_info.allocationSize  = requirements.size;
	alloc_info.memoryTypeIndex = GetMemoryFamily( graphic, memory.Usage, requirements );

	return vk::Check( vkAllocateMemory( graphic.Logical, tiny_rvalue( alloc_info ), vk::GetAllocator( ), tiny_rvalue( memory.Memory ) ) );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
tiny_uint TinyGraphicMemoryManager::GetMemoryFamily( 
	TinyGraphicContext& graphic, 
	TinyGraphicMemoryUsages usage, 
	VkMemoryRequirements& requirements 
) {
	auto memory_family = tiny_cast( 0, tiny_uint );
	
	while ( memory_family < _properties.memoryTypeCount ) {
		if ( 
			( requirements.memoryTypeBits & TINY_LEFT_SHIFT( 1, memory_family ) ) &&
			( _properties.memoryTypes[ memory_family ].propertyFlags & usage ) == usage 
		)
			break;

		memory_family += 1;
	}

	return memory_family;
}
