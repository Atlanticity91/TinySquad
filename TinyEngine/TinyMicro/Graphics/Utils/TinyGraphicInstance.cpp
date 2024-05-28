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
TinyGraphicInstance::TinyGraphicInstance( )
	: _instance{ VK_NULL_HANDLE }
{ }

bool TinyGraphicInstance::Create( tiny_string title ) {
    auto app_info      = VkApplicationInfo{ VK_STRUCTURE_TYPE_APPLICATION_INFO };
    auto instance_info = VkInstanceCreateInfo{ VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO };
    auto extensions    = GetExtensions( );

    // SETUP VULKAN APP INFO
    app_info.pNext              = VK_NULL_HANDLE;
    app_info.pApplicationName   = title.get( );
    app_info.applicationVersion = TINY_APP_VERSION;
    app_info.pEngineName        = "TinyMicro";
    app_info.engineVersion      = TINY_ENG_VERSION;
    app_info.apiVersion         = TINY_VK_API;

    // SETUP VULKAN INSTANCE INFO
    instance_info.pNext                   = VK_NULL_HANDLE;
    instance_info.flags                   = VK_NULL_FLAGS;
    instance_info.pApplicationInfo        = tiny_rvalue( app_info );
    instance_info.enabledExtensionCount   = extensions.size( );
    instance_info.ppEnabledExtensionNames = extensions.data( );
    instance_info.enabledLayerCount       = tiny_size_array( vk::LAYERS );
    instance_info.ppEnabledLayerNames     = vk::LAYERS;

    return  vk::Check( vkCreateInstance( tiny_rvalue( instance_info ), vk::GetAllocator( ), tiny_rvalue( _instance ) ) ) &&
            vk::CreateDebugReport( _instance );
}

void TinyGraphicInstance::Terminate( ) {
    vk::DestroyDebugReport( _instance );

	if ( _instance )
		vkDestroyInstance( _instance, vk::GetAllocator( ) );
}

tiny_list<native_string> TinyGraphicInstance::GetExtensions( ) const {
    auto extension_count = tiny_cast( 0, tiny_uint );
    auto* required       = glfwGetRequiredInstanceExtensions( tiny_rvalue( extension_count ) );
    auto extensions      = tiny_list<native_string>{ };

#   ifdef TINY_DEBUG
    extensions = extension_count + 2;

    extensions[ extension_count     ] = VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME;
    extensions[ extension_count + 1 ] = VK_EXT_DEBUG_REPORT_EXTENSION_NAME;

    while ( extension_count-- > 0 )
        extensions[ extension_count ] = required[ extension_count ];
#   else
    extensions = extension_count + 1;
    
    extensions[ extension_count ] = VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME;

    while ( extension_count-- > 0 )
        extensions[ extension_count ] = required[ extension_count ];
#   endif

    return extensions;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	OPERATOR ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyGraphicInstance::operator VkInstance ( ) const { return _instance; }
