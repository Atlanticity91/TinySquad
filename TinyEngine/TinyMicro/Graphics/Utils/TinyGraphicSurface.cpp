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
 * @creation : 13/10/2023
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
TinyGraphicSurface::TinyGraphicSurface( )
	: m_handle{ VK_NULL_HANDLE },
    m_formats{ }
{ }

bool TinyGraphicSurface::Create( TinyWindow& window , TinyGraphicInstance& instance ) {
#   ifdef _WIN64
    auto surface_info = VkWin32SurfaceCreateInfoKHR{ VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR };

    surface_info.pNext     = VK_NULL_HANDLE;
    surface_info.flags     = VK_NULL_FLAGS;
    surface_info.hwnd      = glfwGetWin32Window( window );
    surface_info.hinstance = GetModuleHandle( nullptr );

    return vk::Check( vkCreateWin32SurfaceKHR( instance, tiny_rvalue( surface_info ), vk::GetAllocator( ), tiny_rvalue( m_handle ) ) );
#   elif TINY_LINUX
#   elif TINY_APPLE
#   endif
}

bool TinyGraphicSurface::Initialize( const TinyGraphicPhysical& physical ) {
    return vk::GetPhysicalDeviceSurfaceFormats( physical, m_handle, m_formats );
}

void TinyGraphicSurface::Terminate( TinyGraphicInstance& instance ) {
    if ( vk::GetIsValid( m_handle ) )
        vkDestroySurfaceKHR( instance, m_handle, vk::GetAllocator( ) );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
const VkSurfaceCapabilitiesKHR TinyGraphicSurface::GetCapabilities( 
    const TinyGraphicPhysical& physical 
) const {
    auto capabilities = VkSurfaceCapabilitiesKHR{ };
    
    vk::Check( vkGetPhysicalDeviceSurfaceCapabilitiesKHR( physical, m_handle, tiny_rvalue( capabilities ) ) );
    
    return capabilities;
}

const TinyGraphicSurface::VkSurfaceFormatList& TinyGraphicSurface::GetFormats( ) const { 
    return m_formats; 
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	OPERATOR ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyGraphicSurface::operator VkSurfaceKHR ( ) const { return m_handle; }
