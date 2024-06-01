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
 * @creation : 20/10/2023
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
TinyGraphicBuffer::TinyGraphicBuffer( )
	: m_descriptor{ },
	m_properties{ },
	m_memory{ }
{ }

bool TinyGraphicBuffer::Create(
	TinyGraphicWrapper& graphic,
	const TinyGraphicBufferSpecification& specification
) {
	m_descriptor.offset = 0;
	m_descriptor.range  = specification.Size;
	m_properties		= specification;

	return  specification.Size > 0 &&
			CreateBuffer( graphic.Logical, graphic.Queues ) &&
			AllocateBuffer( graphic );
}

void TinyGraphicBuffer::Terminate( TinyGraphicWrapper& graphic ) {
	if ( vk::GetIsValid( m_descriptor.buffer ) ) {
		vkDestroyBuffer( graphic.Logical, m_descriptor.buffer, vk::GetAllocator( ) );

		graphic.Memory.DeAllocate( graphic, m_memory );
	}
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyGraphicBuffer::CreateBuffer(
	const TinyGraphicLogical& logical, 
	const TinyGraphicQueueManager& queues 
) {
	auto buffer_info   = VkBufferCreateInfo{ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO };
	auto buffer_queues = queues.GetRessourceQueues( );

	buffer_info.pNext				  = VK_NULL_HANDLE;
	buffer_info.flags				  = VK_NULL_FLAGS;
	buffer_info.size				  = m_properties.Size;
	buffer_info.usage				  = tiny_cast( m_properties.Type, VkBufferUsageFlags );
	buffer_info.sharingMode			  = tiny_cast( buffer_queues.Sharing, VkSharingMode );
	buffer_info.queueFamilyIndexCount = buffer_queues.Queues.size( );
	buffer_info.pQueueFamilyIndices   = buffer_queues.Queues.data( );

	return vk::Check( vkCreateBuffer( logical, tiny_rvalue( buffer_info ), vk::GetAllocator( ), tiny_rvalue( m_descriptor.buffer ) ) );
}

bool TinyGraphicBuffer::AllocateBuffer( TinyGraphicWrapper& graphic ) {
	switch ( m_properties.Type ) {
		case TGB_TYPE_VERTEX  :
		case TGB_TYPE_INDEX   :
		case TGB_TYPE_STORAGE : m_memory.Usage = TGM_USAGE_GPU_ONLY; break;
		case TGB_TYPE_STAGING : m_memory.Usage = TGM_USAGE_CPU_ONLY; break;
		case TGB_TYPE_UNIFORM : m_memory.Usage = TGM_USAGE_SHARE;    break;

		default : break;
	}

	return graphic.Memory.Allocate( graphic, m_memory, m_descriptor.buffer );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyGraphicBuffer::GetIsValid( ) const { 
	return vk::GetIsValid( m_descriptor.buffer ); 
}

const VkBuffer TinyGraphicBuffer::Get( ) const { return m_descriptor.buffer; }

VkDescriptorType TinyGraphicBuffer::GetDescriptorType( ) const {
	auto type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;

	if ( m_properties.Type == TGB_TYPE_STORAGE )
		type = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;

	return type;
}

const VkDescriptorBufferInfo* TinyGraphicBuffer::GetDescriptor( ) const { 
	return tiny_rvalue( m_descriptor );
}

const TinyGraphicBufferSpecification& TinyGraphicBuffer::GetProperties( ) const {
	return m_properties;
}

const TinyGraphicMemory& TinyGraphicBuffer::GetMemory( ) const { return m_memory; }

////////////////////////////////////////////////////////////////////////////////////////////
//		===	OPERATOR ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyGraphicBuffer::operator bool( ) const { return GetIsValid( ); }

TinyGraphicBuffer::operator const VkBuffer( ) const { return Get( ); }

TinyGraphicBuffer::operator const VkDescriptorBufferInfo* ( ) const { 
	return GetDescriptor( );
}
