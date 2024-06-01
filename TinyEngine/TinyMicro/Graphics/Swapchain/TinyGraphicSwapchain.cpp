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
TinyGraphicSwapchain::TinyGraphicSwapchain( )
	: m_swap_chain{ VK_NULL_HANDLE },
	m_properties{ }
{ }

bool TinyGraphicSwapchain::Create( TinyGraphicWrapper& graphic ) {
	auto swapchain_info = VkSwapchainCreateInfoKHR{ VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR };
	auto& surface		= graphic.Surface;
	auto capabilities   = surface.GetCapabilities( graphic.Physical );
	auto swap_queues	= GetSwapchainQueues( graphic.Queues );

	GetSwapchainProperties( surface, capabilities );

	swapchain_info.pNext				 = VK_NULL_HANDLE;
	swapchain_info.flags				 = VK_NULL_FLAGS;
	swapchain_info.surface				 = surface;
	swapchain_info.minImageCount		 = m_properties.Capacity;
	swapchain_info.imageFormat			 = m_properties.Format;
	swapchain_info.imageColorSpace		 = m_properties.ColorSpace;
	swapchain_info.imageExtent			 = GetSwapchainExtent( graphic.Boundaries, capabilities );
	swapchain_info.imageArrayLayers		 = 1;
	swapchain_info.imageUsage			 = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
	swapchain_info.imageSharingMode		 = swap_queues.size( ) > 0 ? VK_SHARING_MODE_CONCURRENT : VK_SHARING_MODE_EXCLUSIVE;
	swapchain_info.queueFamilyIndexCount = swap_queues.size( );
	swapchain_info.pQueueFamilyIndices   = swap_queues.data( );
	swapchain_info.preTransform			 = capabilities.currentTransform;
	swapchain_info.compositeAlpha		 = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	swapchain_info.presentMode			 = m_properties.PresentMode;
	swapchain_info.clipped				 = VK_TRUE;
	swapchain_info.oldSwapchain			 = VK_NULL_HANDLE;

	return vk::Check( vkCreateSwapchainKHR( graphic.Logical, tiny_rvalue( swapchain_info ), vk::GetAllocator( ), tiny_rvalue( m_swap_chain ) ) );
}

void TinyGraphicSwapchain::Terminate( const TinyGraphicLogical& logical ) {
	if ( vk::GetIsValid( m_swap_chain ) )
		vkDestroySwapchainKHR( logical, m_swap_chain, vk::GetAllocator( ) );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
const VkSwapchainKHR TinyGraphicSwapchain::Get( ) const { return m_swap_chain; }

const TinyGraphicSwapchainProperties& TinyGraphicSwapchain::GetProperties( ) const {
	return m_properties;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE GET ===
////////////////////////////////////////////////////////////////////////////////////////////
void TinyGraphicSwapchain::GetSwapchainProperties( 
	const TinyGraphicSurface& surface,
	const VkSurfaceCapabilitiesKHR& capabilities 
) {
	m_properties.Capacity    = capabilities.maxImageCount < TINY_DESIRED_BUFFERING ? capabilities.maxImageCount : TINY_DESIRED_BUFFERING;
	m_properties.PresentMode = VK_PRESENT_MODE_FIFO_KHR;

	auto formats = surface.GetFormats( );

	for ( auto& format : formats ) {
		if ( format.format == VK_FORMAT_R8G8B8A8_UNORM ) {
			m_properties.Format	   = format.format;
			m_properties.ColorSpace = format.colorSpace;

			break;
		}
	}
}

tiny_list<tiny_uint> TinyGraphicSwapchain::GetSwapchainQueues(
	const TinyGraphicQueueManager& queues 
) {
	auto swap_queues   = tiny_list<tiny_uint>{ };
	auto present_queue = queues.GetPhysicalQueue( VK_QUEUE_TYPE_PRESENT ).Family;
	auto graphic_queue = queues.GetPhysicalQueue( VK_QUEUE_TYPE_GRAPHIC ).Family;

	swap_queues.emplace_back( present_queue );

	if ( present_queue != graphic_queue )
		swap_queues.emplace_back( graphic_queue );

	return swap_queues;
}

VkExtent2D TinyGraphicSwapchain::GetSwapchainExtent(
	const TinyGraphicBoundaries& boundaries, 
	const VkSurfaceCapabilitiesKHR& capabilities 
) const {
	auto extent = boundaries.GetSwapScissor( ).extent;

	extent.width  = tiny_clamp( extent.width,  capabilities.minImageExtent.width,  capabilities.maxImageExtent.width  );
	extent.height = tiny_clamp( extent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height );

	return extent;

}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	OPERATOR ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyGraphicSwapchain::operator const VkSwapchainKHR ( ) const { return Get( ); }

TinyGraphicSwapchain::operator const VkSwapchainKHR* ( ) const {
	return tiny_rvalue( m_swap_chain );
}
