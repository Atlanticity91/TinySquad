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
TinyGraphicRenderBarrier::TinyGraphicRenderBarrier( )
	: m_barriers{ }
{ }

void TinyGraphicRenderBarrier::Create( const tiny_list<TinyGraphicRenderBarrierBundle>& bundles ) {
	auto barrier_id = bundles.size( );
	
	m_barriers = barrier_id;

	while ( barrier_id-- > 0 ) {
		auto& bundle  = bundles[ barrier_id ];
		auto& barrier = m_barriers[ barrier_id ];
		auto image_id = bundle.Images.size( );

		barrier.Source   = bundle.Source;
		barrier.Target   = bundle.Target;
		barrier.Barriers = image_id;

		while ( image_id-- > 0 )
			barrier.Barriers[ image_id ] = CreateBarriers( image_id, bundle.Images );
	}
}

void TinyGraphicRenderBarrier::Transit( TinyGraphicWorkContext& work_context ) {
	auto& barrier = m_barriers[ work_context.WorkPass ];
	auto& list	  = barrier.Barriers[ work_context.WorkID ];
	
	vkCmdPipelineBarrier(
		work_context.Queue->CommandBuffer,
		barrier.Source,
		barrier.Target,
		0,
		0, VK_NULL_HANDLE,
		0, VK_NULL_HANDLE,
		list.size( ), list.data( )
	);
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE ===
////////////////////////////////////////////////////////////////////////////////////////////
tiny_list<VkImageMemoryBarrier> TinyGraphicRenderBarrier::CreateBarriers( 
	tiny_uint image_id,
	const tiny_list<TinyGraphicRenderBarrierImage>& images
) {
	auto barriers = tiny_list<VkImageMemoryBarrier>{ };
	auto local_id = images.size( );

	barriers = local_id;

	while ( local_id-- > 0 ) {
		auto& barrier = barriers[ local_id ];
		auto& image   = images[ local_id ];

		barrier.sType				= VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
		barrier.pNext				= VK_NULL_HANDLE;
		barrier.srcAccessMask		= image.AccessSource;
		barrier.dstAccessMask		= image.AccessTarget;
		barrier.oldLayout			= image.Source;
		barrier.newLayout			= image.Target;
		barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		barrier.image				= image.Images[ image_id ];
		barrier.subresourceRange	= { image.Aspect, 0, 1, 0, 1 };
	}

	return barriers;
}
