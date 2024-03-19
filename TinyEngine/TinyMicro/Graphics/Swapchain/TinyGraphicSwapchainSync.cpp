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
TinyGraphicSwapchainSync::TinyGraphicSwapchainSync( )
	: _acquire{ VK_NULL_HANDLE },
	_present{ VK_NULL_HANDLE },
	_fence{ VK_NULL_HANDLE }
{ }

bool TinyGraphicSwapchainSync::Create( const TinyGraphicLogical& logical ) {
	return  CreateSwapchainSemaphore( logical, _acquire ) &&
			CreateSwapchainSemaphore( logical, _present ) &&
			CreateSwapchainFence( logical );
}

void TinyGraphicSwapchainSync::Terminate( const TinyGraphicLogical& logical ) {
	if ( vk::GetIsValid( _acquire ) )
		vkDestroySemaphore( logical, _acquire, vk::GetAllocator( ) );

	if ( vk::GetIsValid( _present ) )
		vkDestroySemaphore( logical, _present, vk::GetAllocator( ) );

	if ( vk::GetIsValid( _fence ) )
		vkDestroyFence( logical, _fence, vk::GetAllocator( ) );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyGraphicSwapchainSync::CreateSwapchainSemaphore( 
	const TinyGraphicLogical& logical, 
	VkSemaphore& semaphore 
) {
	auto semaphore_info = VkSemaphoreCreateInfo{ VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO };

	semaphore_info.pNext = VK_NULL_HANDLE;
	semaphore_info.flags = VK_NULL_FLAGS;

	return vk::Check( vkCreateSemaphore( logical, tiny_rvalue( semaphore_info ), vk::GetAllocator( ), tiny_rvalue( semaphore ) ) );
}

bool TinyGraphicSwapchainSync::CreateSwapchainFence( const TinyGraphicLogical& logical ) {
	auto fence_info = VkFenceCreateInfo{ VK_STRUCTURE_TYPE_FENCE_CREATE_INFO };

	fence_info.pNext = VK_NULL_HANDLE;
	fence_info.flags = VK_FENCE_CREATE_SIGNALED_BIT;

	return vk::Check( vkCreateFence( logical, tiny_rvalue( fence_info ), vk::GetAllocator( ), tiny_rvalue( _fence ) ) );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
const VkSemaphore* TinyGraphicSwapchainSync::GetAcquire( ) const { 
	return tiny_rvalue( _acquire ); 
}

const VkSemaphore* TinyGraphicSwapchainSync::GetPresent( ) const { 
	return tiny_rvalue( _present ); 
}

const VkFence* TinyGraphicSwapchainSync::GetFence( ) const { 
	return tiny_rvalue( _fence ); 
}
