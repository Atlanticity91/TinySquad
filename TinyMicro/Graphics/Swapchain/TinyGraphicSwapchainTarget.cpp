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
	: _image{ VK_NULL_HANDLE },
	_view{ VK_NULL_HANDLE }
{ }

bool TinyGraphicSwapchainTarget::Create( const TinyGraphicLogical& logical, const TinyGraphicSwapchainProperties& properties, VkImage image ) {
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

    _image = image;

    return vk::Check( vkCreateImageView( logical, &view_info, vk::GetAllocator( ), &_view ) );
}

void TinyGraphicSwapchainTarget::Terminate( const TinyGraphicLogical& logical ) {
    if ( vk::GetIsValid( _view ) )
        vkDestroyImageView( logical, _view, vk::GetAllocator( ) );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
const VkImage TinyGraphicSwapchainTarget::GetImage( ) const { return _image; }

const VkImageView TinyGraphicSwapchainTarget::GetView( ) const { return _view; }
