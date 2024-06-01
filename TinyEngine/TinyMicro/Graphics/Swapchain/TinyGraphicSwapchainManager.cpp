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
TinyGraphicSwapchainManager::TinyGraphicSwapchainManager( )
	: m_swapchain{ },
	m_properties{ },
	m_targets{ },
	m_syncs{ }
{ }

bool TinyGraphicSwapchainManager::Create( TinyGraphicWrapper& graphic ) {
	return  CreateSwapchain( graphic ) &&
			CreateSwapchainSyncs( graphic.Logical );
}

void TinyGraphicSwapchainManager::ReCreate( TinyGraphicWrapper& graphic ) {
	TerminateSwapchain( graphic.Logical );
	CreateSwapchain( graphic );
}

bool TinyGraphicSwapchainManager::Acquire(
	const TinyGraphicLogical& logical, 
	TinyGraphicWorkContext& work_context 
) {
	work_context.Sync = tiny_rvalue( m_syncs[ work_context.WorkID ] );
	
	return  vk::Check( vkResetFences( logical, 1, work_context.Sync->GetFence( ) ) ) &&
			vk::Check( vkAcquireNextImageKHR( logical, m_swapchain, UINT_MAX, tiny_lvalue( work_context.Sync->GetAcquire( ) ), VK_NULL_HANDLE, tiny_rvalue( work_context.WorkImage ) ) );
}

bool TinyGraphicSwapchainManager::Present(
	const TinyGraphicLogical& logical,
	TinyGraphicQueueManager& queues, 
	TinyGraphicWorkContext& work_context 
) {
	work_context.Flush( queues, { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT } );
	work_context.Acquire( queues, VK_QUEUE_TYPE_PRESENT );

	auto present_info = VkPresentInfoKHR{ VK_STRUCTURE_TYPE_PRESENT_INFO_KHR };

	present_info.pNext				= VK_NULL_HANDLE;
	present_info.waitSemaphoreCount = 1;
	present_info.pWaitSemaphores	= work_context.Sync->GetPresent( );
	present_info.swapchainCount		= 1;
	present_info.pSwapchains		= m_swapchain;
	present_info.pImageIndices		= tiny_rvalue( work_context.WorkImage );
	present_info.pResults			= VK_NULL_HANDLE;

	auto state = vk::Check( vkQueuePresentKHR( work_context.Queue->Queue, tiny_rvalue( present_info ) ) ) &&
				 vk::Check( vkQueueWaitIdle( work_context.Queue->Queue ) );

	work_context.Release( queues );
	work_context.WorkID = ( work_context.WorkID + 1 ) % m_swapchain.GetProperties( ).Capacity;

	return state;
}

void TinyGraphicSwapchainManager::Terminate( 
	const TinyGraphicLogical& logical, 
	const TinyGraphicQueueManager& queues
) {
	for ( auto& sync : m_syncs )
		sync.Terminate( logical );

	TerminateSwapchain( logical );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyGraphicSwapchainManager::CreateSwapchainTargets( 
	const TinyGraphicLogical& logical 
)  {
	auto swap_images = tiny_list<VkImage>{ };
	auto state		 = vk::GetSwapchainImages( logical, m_swapchain, swap_images );

	if ( state ) {
		auto& properties = m_swapchain.GetProperties( );
		auto image_id    = tiny_cast( 0, tiny_uint );

		m_targets = properties.Capacity;

		for ( auto& target : m_targets ) {
			state = target.Create( logical, properties, swap_images[ image_id++ ] );

			if ( !state )
				break;
		}
	}

	return state;
}

bool TinyGraphicSwapchainManager::CreateSwapchainSyncs(
	const TinyGraphicLogical& logical
) {
	auto& properties = m_swapchain.GetProperties( );
	auto state		 = false;

	m_syncs = properties.Capacity;

	for ( auto& sync : m_syncs ) {
		state = sync.Create( logical );

		if ( !state )
			break;
	}

	return state;
}

bool TinyGraphicSwapchainManager::CreateSwapchain( TinyGraphicWrapper& graphic ) {
	auto state = m_swapchain.Create( graphic ) && 
				 CreateSwapchainTargets( graphic.Logical );

	if ( state )
		GetProperties( graphic.Boundaries );

	return state;
}

void TinyGraphicSwapchainManager::TerminateSwapchain(
	const TinyGraphicLogical& logical
) {
	for ( auto& target : m_targets )
		target.Terminate( logical );

	m_swapchain.Terminate( logical );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
const TinyGraphicSwapchain& TinyGraphicSwapchainManager::Get( ) const { 
	return m_swapchain; 
}

const TinyGraphicSwapchainTarget& TinyGraphicSwapchainManager::GetTarget( 
	tiny_uint target
) const {
	return m_targets[ target ];
}

TinyGraphicTextureProperties TinyGraphicSwapchainManager::GetTargetProperties(
	tiny_uint target
) const {
	auto properties = m_properties;

	properties.Image = m_targets[ target ].GetImage( );
	properties.View  = m_targets[ target ].GetView( );

	return properties;
}

const TinyGraphicSwapchainProperties& TinyGraphicSwapchainManager::GetProperties( ) const { 
	return m_swapchain.GetProperties( );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE GET ===
////////////////////////////////////////////////////////////////////////////////////////////
void TinyGraphicSwapchainManager::GetProperties( const TinyGraphicBoundaries& boundaries ) {
	auto dimensions = boundaries.GetSwapScissor( ).extent;

	m_properties.Type	 = TGT_TYPE_TEXTURE_2D;
	m_properties.Format  = m_swapchain.GetProperties( ).Format;
	m_properties.Layout  = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
	m_properties.Width   = dimensions.width;
	m_properties.Height  = dimensions.height;
	m_properties.Depth   = 1;
	m_properties.Aspect  = VK_IMAGE_ASPECT_COLOR_BIT;
	m_properties.Levels  = 1;
	m_properties.Samples = VK_SAMPLE_COUNT_1_BIT;
	m_properties.Tiling  = VK_IMAGE_TILING_OPTIMAL;
	m_properties.Usage	 = TGT_USAGE_TARGET;
}
