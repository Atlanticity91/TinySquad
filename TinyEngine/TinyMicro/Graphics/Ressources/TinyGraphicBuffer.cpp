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
	: _descriptor{ },
	_properties{ },
	_memory{ }
{ }

bool TinyGraphicBuffer::Create(
	TinyGraphicContext& context,
	const TinyGraphicBufferProperties& properties
) {
	_descriptor.offset = 0;
	_descriptor.range  = properties.Size;
	_properties		   = properties;

	return  properties.Size > 0 &&
			CreateBuffer( context.Logical, context.Queues ) &&
			AllocateBuffer( context );
}

void TinyGraphicBuffer::Terminate( TinyGraphicContext& context ) {
	if ( vk::GetIsValid( _descriptor.buffer ) ) {
		vkDestroyBuffer( context.Logical, _descriptor.buffer, vk::GetAllocator( ) );

		context.Memory.DeAllocate( context, _memory );
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
	buffer_info.size				  = _properties.Size;
	buffer_info.usage				  = tiny_cast( _properties.Type, VkBufferUsageFlags );
	buffer_info.sharingMode			  = tiny_cast( buffer_queues.Sharing, VkSharingMode );
	buffer_info.queueFamilyIndexCount = buffer_queues.Queues.size( );
	buffer_info.pQueueFamilyIndices   = buffer_queues.Queues.data( );

	return vk::Check( vkCreateBuffer( logical, tiny_rvalue( buffer_info ), vk::GetAllocator( ), tiny_rvalue( _descriptor.buffer ) ) );
}

bool TinyGraphicBuffer::AllocateBuffer( TinyGraphicContext& graphic ) {
	switch ( _properties.Type ) {
		case TGB_TYPE_VERTEX  :
		case TGB_TYPE_INDEX   :
		case TGB_TYPE_STORAGE : _memory.Usage = TGM_USAGE_GPU_ONLY; break;
		case TGB_TYPE_STAGING : _memory.Usage = TGM_USAGE_CPU_ONLY; break;
		case TGB_TYPE_UNIFORM : _memory.Usage = TGM_USAGE_SHARE;    break;

		default : break;
	}

	return graphic.Memory.Allocate( graphic, _memory, _descriptor.buffer );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyGraphicBuffer::GetIsValid( ) const { return vk::GetIsValid( _descriptor.buffer ); }

const VkBuffer TinyGraphicBuffer::Get( ) const { return _descriptor.buffer; }

VkDescriptorType TinyGraphicBuffer::GetDescriptorType( ) const {
	auto type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;

	if ( _properties.Type == TGB_TYPE_STORAGE )
		type = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;

	return type;
}

const VkDescriptorBufferInfo* TinyGraphicBuffer::GetDescriptor( ) const { 
	return tiny_rvalue( _descriptor );
}

const TinyGraphicBufferProperties& TinyGraphicBuffer::GetProperties( ) const { 
	return _properties;
}

const TinyGraphicMemory& TinyGraphicBuffer::GetMemory( ) const { return _memory; }

////////////////////////////////////////////////////////////////////////////////////////////
//		===	OPERATOR ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyGraphicBuffer::operator bool( ) const { return GetIsValid( ); }

TinyGraphicBuffer::operator const VkBuffer( ) const { return Get( ); }

TinyGraphicBuffer::operator const VkDescriptorBufferInfo* ( ) const { 
	return GetDescriptor( );
}
