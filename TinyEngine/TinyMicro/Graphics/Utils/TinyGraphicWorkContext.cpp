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
TinyGraphicWorkContext::TinyGraphicWorkContext( )
	: WorkID{ 0 },
	WorkImage{ 0 },
	WorkPass{ 0 },
	WorkRender{ },
	Type{ VK_QUEUE_TYPE_UNDEFINED },
	Queue{ nullptr },
	Sync{ nullptr }
{ }

void TinyGraphicWorkContext::Acquire( 
	const TinyGraphicLogical& logical,
	TinyGraphicQueueManager& queues, 
	VkQueueTypes type
) {
	if ( type != VK_QUEUE_TYPE_UNDEFINED && Type != type ) {
		if ( Queue ) {
			vk::EndCommandBuffer( Queue->CommandBuffer );

			Release( queues );
		}

		Type  = type;
		Queue = queues.Acquire( type );

		vk::ResetCommandBuffer( Queue->CommandBuffer );

		if ( type != VK_QUEUE_TYPE_PRESENT )
			vk::BeginCommandBuffer( Queue->CommandBuffer );
	}
}

void TinyGraphicWorkContext::Submit(
	const TinyGraphicLogical& logical,
	TinyGraphicQueueManager& queues, 
	tiny_init<VkPipelineStageFlags> stages 
) {
	if ( Type != VK_QUEUE_TYPE_UNDEFINED ) {
		vk::EndCommandBuffer( Queue->CommandBuffer );

		auto submit_info = VkSubmitInfo{ VK_STRUCTURE_TYPE_SUBMIT_INFO };

		submit_info.pNext				 = VK_NULL_HANDLE;
		submit_info.waitSemaphoreCount   = 1;
		submit_info.pWaitSemaphores		 = Sync->GetAcquire( );
		submit_info.pWaitDstStageMask	 = stages.begin( );
		submit_info.commandBufferCount	 = 1;
		submit_info.pCommandBuffers		 = Queue->CommandBuffer;
		submit_info.signalSemaphoreCount = 1;
		submit_info.pSignalSemaphores    = Sync->GetPresent( );

		vk::Check( vkQueueSubmit( Queue->Queue, 1, tiny_rvalue( submit_info ), tiny_lvalue( Sync->GetFence( ) ) ) );
		vk::Check( vkWaitForFences( logical, 1, Sync->GetFence( ), VK_TRUE, UINT_MAX ) );	
	}
}

void TinyGraphicWorkContext::Flush( 
	const TinyGraphicLogical& logical,
	TinyGraphicQueueManager& queues, 
	tiny_init<VkPipelineStageFlags> stages 
) {
	Submit( logical, queues, stages );

	Release( queues );
}

void TinyGraphicWorkContext::Release( TinyGraphicQueueManager& queues ) {
	if ( Type != VK_QUEUE_TYPE_UNDEFINED ) {
		queues.Release( Type, Queue );

		Type  = VK_QUEUE_TYPE_UNDEFINED;
		Queue = nullptr;
	}
}
