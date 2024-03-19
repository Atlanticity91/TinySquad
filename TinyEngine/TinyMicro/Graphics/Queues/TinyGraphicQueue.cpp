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
 * @creation : 17/10/2023
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
TinyGraphicQueue::TinyGraphicQueue( ) 
	: _physical{ },
	_sharing_mode{ },
	_queues{ }
{ }

bool TinyGraphicQueue::Create( 
	const TinyGraphicLogical& logical, 
	const VkPhysicalDeviceQueue& physical 
) {
	_physical	  = physical;
	_sharing_mode = physical.Count > 0 ? VK_SHARING_MODE_CONCURRENT : VK_SHARING_MODE_EXCLUSIVE;
	_queues		  = physical.Count;

	return CreateQueues( logical, physical );
}

void TinyGraphicQueue::Release( VkLogicalQueue* queue ) { queue->InUse = VK_FALSE; }

void TinyGraphicQueue::Terminate( const TinyGraphicLogical& logical ) {
	for ( auto& queue : _queues ) {
		vk::DestroyCommandBuffer( logical, queue, queue.CommandBuffer );

		if ( vk::GetIsValid( queue.CommandPool ) )
			vkDestroyCommandPool( logical, queue.CommandPool, vk::GetAllocator( ) );
	}
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyGraphicQueue::CreateQueuePool(
	const TinyGraphicLogical& logical,
	const VkPhysicalDeviceQueue& physical, 
	VkLogicalQueue& queue
) {
	auto pool_info = VkCommandPoolCreateInfo{ VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO };

	pool_info.pNext			   = VK_NULL_HANDLE;
	pool_info.flags			   = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
	pool_info.queueFamilyIndex = physical.Family;

	return vk::Check( vkCreateCommandPool( logical, tiny_rvalue( pool_info ), vk::GetAllocator( ), tiny_rvalue( queue.CommandPool ) ) );
}

bool TinyGraphicQueue::CreateQueueCommands(
	const TinyGraphicLogical& logical,
	VkLogicalQueue& queue 
) {
	return vk::CreateCommandBuffer( logical, queue, queue.CommandBuffer );
}

bool TinyGraphicQueue::CreateQueues(
	const TinyGraphicLogical& logical, 
	const VkPhysicalDeviceQueue& physical 
) {
	auto queue_id = tiny_cast( 0, tiny_uint );
	auto state	  = false;

	for ( auto& queue : _queues ) {
		queue.InUse		   = VK_FALSE;

		vkGetDeviceQueue( logical, physical.Family, queue_id++, tiny_rvalue( queue.Queue ) );

		state = CreateQueuePool( logical, physical, queue ) &&
				CreateQueueCommands( logical, queue );

		if ( !state )
			break;
	}

	return state;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
const VkPhysicalDeviceQueue& TinyGraphicQueue::GetPhysical( ) const { return _physical; }

VkLogicalQueue* TinyGraphicQueue::Acquire( ) {
	auto queue_id = _queues.find( 
		[]( const VkLogicalQueue& queue ) {
			return queue.InUse == VK_FALSE;
		} 
	);

	auto* queue = _queues.exist( queue_id ) ? tiny_rvalue( _queues[ queue_id ] ) : nullptr;

	if ( queue )
		queue->InUse = VK_TRUE;

	return queue;
}

const VkLogicalQueue& TinyGraphicQueue::GetQueue( tiny_uint queue_id ) const {
	return _queues[ queue_id ];
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	OPERATOR ===
////////////////////////////////////////////////////////////////////////////////////////////
const VkLogicalQueue& TinyGraphicQueue::operator[]( tiny_uint queue_id ) const { 
	return GetQueue( queue_id );
}
