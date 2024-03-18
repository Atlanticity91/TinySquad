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
	: _swapchain{ },
	_properties{ },
	_targets{ },
	_syncs{ }
{ }

bool TinyGraphicSwapchainManager::Create( TinyGraphicContext& graphic ) {
	return  CreateSwapchain( graphic ) &&
			CreateSwapchainSyncs( graphic.Logical );
}

void TinyGraphicSwapchainManager::ReCreate( TinyGraphicContext& graphic ) {
	TerminateSwapchain( graphic.Logical );
	CreateSwapchain( graphic );
}

bool TinyGraphicSwapchainManager::Acquire(
	const TinyGraphicLogical& logical, 
	TinyGraphicWorkContext& work_context 
) {
	work_context.Sync = &_syncs[ work_context.WorkID ];
	
	return  vk::Check( vkResetFences( logical, 1, work_context.Sync->GetFence( ) ) ) &&
			vk::Check( vkAcquireNextImageKHR( logical, _swapchain, UINT_MAX, *work_context.Sync->GetAcquire( ), VK_NULL_HANDLE, &work_context.WorkImage ) );
}

bool TinyGraphicSwapchainManager::Present(
	const TinyGraphicLogical& logical,
	TinyGraphicQueueManager& queues, 
	TinyGraphicWorkContext& work_context 
) {
	work_context.Flush( logical, queues, { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT } );
	work_context.Acquire( logical, queues, VK_QUEUE_TYPE_PRESENT );

	auto present_info = VkPresentInfoKHR{ VK_STRUCTURE_TYPE_PRESENT_INFO_KHR };

	present_info.pNext				= VK_NULL_HANDLE;
	present_info.waitSemaphoreCount = 1;
	present_info.pWaitSemaphores	= work_context.Sync->GetPresent( );
	present_info.swapchainCount		= 1;
	present_info.pSwapchains		= _swapchain;
	present_info.pImageIndices		= &work_context.WorkImage;
	present_info.pResults			= VK_NULL_HANDLE;

	auto state = vk::Check( vkQueuePresentKHR( work_context.Queue->Queue, &present_info ) ) &&
				 vk::Check( vkQueueWaitIdle( work_context.Queue->Queue ) );

	work_context.Release( queues );
	work_context.WorkID = ( work_context.WorkID + 1 ) % _swapchain.GetProperties( ).Capacity;

	return state;
}

void TinyGraphicSwapchainManager::Terminate( 
	const TinyGraphicLogical& logical, 
	const TinyGraphicQueueManager& queues
) {
	for ( auto& sync : _syncs )
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
	auto state		 = vk::GetSwapchainImages( logical, _swapchain, swap_images );

	if ( state ) {
		auto& properties = _swapchain.GetProperties( );
		auto image_id    = (tiny_uint)0;

		_targets = properties.Capacity;

		for ( auto& target : _targets ) {
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
	auto& properties = _swapchain.GetProperties( );
	auto state		 = false;

	_syncs = properties.Capacity;

	for ( auto& sync : _syncs ) {
		state = sync.Create( logical );

		if ( !state )
			break;
	}

	return state;
}

bool TinyGraphicSwapchainManager::CreateSwapchain( TinyGraphicContext& graphic ) {
	auto state = _swapchain.Create( graphic ) && 
				 CreateSwapchainTargets( graphic.Logical );

	if ( state )
		GetProperties( graphic.Boundaries );

	return state;
}

void TinyGraphicSwapchainManager::TerminateSwapchain(
	const TinyGraphicLogical& logical
) {
	for ( auto& target : _targets )
		target.Terminate( logical );

	_swapchain.Terminate( logical );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
const TinyGraphicSwapchain& TinyGraphicSwapchainManager::Get( ) const { return _swapchain; }

const TinyGraphicSwapchainTarget& TinyGraphicSwapchainManager::GetTarget( 
	tiny_uint target
) const {
	return _targets[ target ];
}

TinyGraphicTextureProperties TinyGraphicSwapchainManager::GetTargetProperties(
	tiny_uint target
) const {
	auto properties = _properties;

	properties.Image = _targets[ target ].GetImage( );
	properties.View  = _targets[ target ].GetView( );

	return properties;
}

const TinyGraphicSwapchainProperties& TinyGraphicSwapchainManager::GetProperties( ) const { 
	return _swapchain.GetProperties( );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE GET ===
////////////////////////////////////////////////////////////////////////////////////////////
void TinyGraphicSwapchainManager::GetProperties( const TinyGraphicBoundaries& boundaries ) {
	auto dimensions = boundaries.GetSwapScissor( ).extent;

	_properties.Type	= TGT_TYPE_TEXTURE_2D;
	_properties.Format  = _swapchain.GetProperties( ).Format;
	_properties.Layout  = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
	_properties.Width   = dimensions.width;
	_properties.Height  = dimensions.height;
	_properties.Depth   = 1;
	_properties.Aspect  = VK_IMAGE_ASPECT_COLOR_BIT;
	_properties.Levels  = 1;
	_properties.Samples = VK_SAMPLE_COUNT_1_BIT;
	_properties.Tiling  = VK_IMAGE_TILING_OPTIMAL;
	_properties.Usage	= TGT_USAGE_TARGET;
}
