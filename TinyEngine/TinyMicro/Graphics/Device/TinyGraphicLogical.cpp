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
TinyGraphicLogical::TinyGraphicLogical( )
	: _handle{ VK_NULL_HANDLE }
{ }

bool TinyGraphicLogical::Create( const TinyGraphicPhysical& physical ) {
	auto device_info = VkDeviceCreateInfo{ VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO };
	auto queues		 = GetQueuesCreateInfos( physical );

	device_info.pNext					= physical.GetFeatures( );
	device_info.flags					= VK_NULL_FLAGS;
	device_info.queueCreateInfoCount	= queues.size( );
	device_info.pQueueCreateInfos		= queues.data( );
	device_info.enabledLayerCount		= tiny_size_array( vk::LAYERS );
	device_info.ppEnabledLayerNames		= vk::LAYERS;
	device_info.enabledExtensionCount   = tiny_size_array( vk::EXTENSIONS );
	device_info.ppEnabledExtensionNames = vk::EXTENSIONS;
	device_info.pEnabledFeatures		= VK_NULL_HANDLE;

	return vk::Check( vkCreateDevice( physical, tiny_rvalue( device_info ), vk::GetAllocator( ), tiny_rvalue( _handle ) ) );
}

bool TinyGraphicLogical::Wait( ) {
	return vk::GetIsValid( _handle ) ? vk::Check( vkDeviceWaitIdle( _handle ) ) : false;
}

void TinyGraphicLogical::Terminate( ) {
	if ( vk::GetIsValid( _handle ) )
		vkDestroyDevice( _handle, vk::GetAllocator( ) );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
VkDevice TinyGraphicLogical::Get( ) const { return _handle; }

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE GET ===
////////////////////////////////////////////////////////////////////////////////////////////
tiny_list<VkDeviceQueueCreateInfo> TinyGraphicLogical::GetQueuesCreateInfos( 
	const TinyGraphicPhysical& physical 
) {
	auto queues_infos = tiny_list<VkDeviceQueueCreateInfo>{ };
	auto queue_info   = VkDeviceQueueCreateInfo{ VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO };
	auto queue_list	  = physical.GetQueues( );

	queue_info.pNext			= VK_NULL_HANDLE;
	queue_info.flags			= VK_NULL_FLAGS;
	queue_info.pQueuePriorities = vk::QUEUES_PRIORITIES;

	for ( auto& queue : queue_list ) {
		queue_info.queueFamilyIndex = queue.Family;
		queue_info.queueCount		= queue.Count;

		queues_infos.emplace_back( queue_info );
	}

	return queues_infos;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	OPERATOR ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyGraphicLogical::operator VkDevice ( ) const { return Get( ); }
