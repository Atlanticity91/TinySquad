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
TinyGraphicSwapchainTarget::TinyGraphicSwapchainTarget( )
	: m_image{ VK_NULL_HANDLE },
	m_view{ VK_NULL_HANDLE }
{ }

bool TinyGraphicSwapchainTarget::Create( 
    const TinyGraphicLogical& logical, 
    const TinyGraphicSwapchainProperties& properties,
    VkImage image 
) {
    auto view_info = VkImageViewCreateInfo{ VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO };

    view_info.pNext    = VK_NULL_HANDLE;
    view_info.flags    = VK_NULL_FLAGS;
    view_info.image    = image;
    view_info.viewType = VK_IMAGE_VIEW_TYPE_2D;
    view_info.format   = properties.Format;

    view_info.components = {

        VK_COMPONENT_SWIZZLE_IDENTITY,
        VK_COMPONENT_SWIZZLE_IDENTITY,
        VK_COMPONENT_SWIZZLE_IDENTITY,
        VK_COMPONENT_SWIZZLE_IDENTITY

    };

    view_info.subresourceRange = { VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1 };

    m_image = image;

    return vk::Check( vkCreateImageView( logical, tiny_rvalue( view_info ), vk::GetAllocator( ), tiny_rvalue( m_view ) ) );
}

void TinyGraphicSwapchainTarget::Terminate( const TinyGraphicLogical& logical ) {
    if ( vk::GetIsValid( m_view ) )
        vkDestroyImageView( logical, m_view, vk::GetAllocator( ) );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
const VkImage TinyGraphicSwapchainTarget::GetImage( ) const { return m_image; }

const VkImageView TinyGraphicSwapchainTarget::GetView( ) const { return m_view; }
