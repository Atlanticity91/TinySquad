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
//		===	INTERNAL ===
////////////////////////////////////////////////////////////////////////////////////////////
VkAllocationStas vk_allocation_stats = { 0, 0, 0, 0 };

#	ifdef TINY_DEBUG
VkDebugReportCallbackEXT vk_debug = VK_NULL_HANDLE;
#	endif

tiny_string vkGetResultString( VkResult result ) {
    auto text = tiny_string{ };

    switch ( result ) {
        case  VK_NOT_READY: text = "VK_NOT_READY A fence or query has not yet completed";
        case  VK_TIMEOUT: text = "VK_TIMEOUT A wait operation has not completed in the specified time";
        case  VK_EVENT_SET: text = "VK_EVENT_SET An event is signaled";
        case  VK_EVENT_RESET: text = "VK_EVENT_RESET An event is unsignaled";
        case  VK_INCOMPLETE: text = "VK_INCOMPLETE A return array was too small for the result";
        case  VK_SUBOPTIMAL_KHR: text = "VK_SUBOPTIMAL_KHR A swapchain no longer matches the surface properties exactly, but can still be used to present to the surface successfully.";
        case  VK_THREAD_IDLE_KHR: text = "VK_THREAD_IDLE_KHR A deferred operation is not complete but there is currently no work for this thread to do at the time of this call.";
        case  VK_THREAD_DONE_KHR: text = "VK_THREAD_DONE_KHR A deferred operation is not complete but there is no work remaining to assign to additional threads.";
        case  VK_OPERATION_DEFERRED_KHR: text = "VK_OPERATION_DEFERRED_KHR A deferred operation was requested and at least some of the work was deferred.";
        case  VK_OPERATION_NOT_DEFERRED_KHR: text = "VK_OPERATION_NOT_DEFERRED_KHR A deferred operation was requested and no operations were deferred.";
        case  VK_PIPELINE_COMPILE_REQUIRED_EXT: text = "VK_PIPELINE_COMPILE_REQUIRED_EXT A requested pipeline creation would have required compilation, but the application requested compilation to not be performed.";

        // Error codes
        case  VK_ERROR_OUT_OF_HOST_MEMORY:  text = "VK_ERROR_OUT_OF_HOST_MEMORY A host memory allocation has failed.";
        case  VK_ERROR_OUT_OF_DEVICE_MEMORY: text = "VK_ERROR_OUT_OF_DEVICE_MEMORY A device memory allocation has failed.";
        case  VK_ERROR_INITIALIZATION_FAILED: text = "VK_ERROR_INITIALIZATION_FAILED Initialization of an object could not be completed for implementation-specific reasons.";
        case  VK_ERROR_DEVICE_LOST: text = "VK_ERROR_DEVICE_LOST The logical or physical device has been lost. See Lost Device";
        case  VK_ERROR_MEMORY_MAP_FAILED: text = "VK_ERROR_MEMORY_MAP_FAILED Mapping of a memory object has failed.";
        case  VK_ERROR_LAYER_NOT_PRESENT: text = "VK_ERROR_LAYER_NOT_PRESENT A requested layer is not present or could not be loaded.";
        case  VK_ERROR_EXTENSION_NOT_PRESENT: text = "VK_ERROR_EXTENSION_NOT_PRESENT A requested extension is not supported.";
        case  VK_ERROR_FEATURE_NOT_PRESENT: text = "VK_ERROR_FEATURE_NOT_PRESENT A requested feature is not supported.";
        case  VK_ERROR_INCOMPATIBLE_DRIVER: text = "VK_ERROR_INCOMPATIBLE_DRIVER The requested version of Vulkan is not supported by the driver or is otherwise incompatible for implementation-specific reasons.";
        case  VK_ERROR_TOO_MANY_OBJECTS: text = "VK_ERROR_TOO_MANY_OBJECTS Too many objects of the type have already been created.";
        case  VK_ERROR_FORMAT_NOT_SUPPORTED: text = "VK_ERROR_FORMAT_NOT_SUPPORTED A requested format is not supported on this device.";
        case  VK_ERROR_FRAGMENTED_POOL: text = "VK_ERROR_FRAGMENTED_POOL A pool allocation has failed due to fragmentation of the pool’s memory. This must only be returned if no attempt to allocate host or device memory was made to accommodate the new allocation. This should be returned in preference to VK_ERROR_OUT_OF_POOL_MEMORY, but only if the implementation is certain that the pool allocation failure was due to fragmentation.";
        case  VK_ERROR_SURFACE_LOST_KHR: text = "VK_ERROR_SURFACE_LOST_KHR A surface is no longer available.";
        case  VK_ERROR_NATIVE_WINDOW_IN_USE_KHR: text = "VK_ERROR_NATIVE_WINDOW_IN_USE_KHR The requested window is already in use by Vulkan or another API in a manner which prevents it from being used again.";
        case  VK_ERROR_OUT_OF_DATE_KHR: text = "VK_ERROR_OUT_OF_DATE_KHR A surface has changed in such a way that it is no longer compatible with the swapchain, and further presentation requests using the swapchain will fail. Applications must query the new surface properties and recreate their swapchain if they wish to continue presenting to the surface.";
        case  VK_ERROR_INCOMPATIBLE_DISPLAY_KHR:  text = "VK_ERROR_INCOMPATIBLE_DISPLAY_KHR The display used by a swapchain does not use the same presentable image layout, or is incompatible in a way that prevents sharing an image.";
        case  VK_ERROR_INVALID_SHADER_NV: text = "VK_ERROR_INVALID_SHADER_NV One or more shaders failed to compile or link. More details are reported back to the application via VK_EXT_debug_report if enabled.";
        case  VK_ERROR_OUT_OF_POOL_MEMORY: text = "VK_ERROR_OUT_OF_POOL_MEMORY A pool memory allocation has failed. This must only be returned if no attempt to allocate host or device memory was made to accommodate the new allocation. If the failure was definitely due to fragmentation of the pool, VK_ERROR_FRAGMENTED_POOL should be returned instead.";
        case  VK_ERROR_INVALID_EXTERNAL_HANDLE: text = "VK_ERROR_INVALID_EXTERNAL_HANDLE An external handle is not a valid handle of the specified type.";
        case  VK_ERROR_FRAGMENTATION:  text = "VK_ERROR_FRAGMENTATION A descriptor pool creation has failed due to fragmentation.";
        case  VK_ERROR_INVALID_DEVICE_ADDRESS_EXT: text = "VK_ERROR_INVALID_DEVICE_ADDRESS_EXT A buffer creation failed because the requested address is not available.";
        case  VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT: text = "VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT An operation on a swapchain created with VK_FULL_SCREEN_EXCLUSIVE_APPLICATION_CONTROLLED_EXT failed as it did not have exlusive full-screen access. This may occur due to implementation-dependent reasons, outside of the application’s control.";
        case  VK_ERROR_UNKNOWN: text = "VK_ERROR_UNKNOWN An unknown error has occurred; either the application has provided invalid input, or an implementation failure has occurred.";

        default: break;
    }

    return text;
}

tiny_string vkGetScopeString( VkSystemAllocationScope scope ) {
    auto text = tiny_string{ "" };

    switch ( scope ) {
        case VK_SYSTEM_ALLOCATION_SCOPE_COMMAND: text = "COMMAND"; break;
        case VK_SYSTEM_ALLOCATION_SCOPE_OBJECT: text = "OBJECT"; break;
        case VK_SYSTEM_ALLOCATION_SCOPE_CACHE:text = "CACHE"; break;
        case VK_SYSTEM_ALLOCATION_SCOPE_DEVICE:text = "DEVICE"; break;
        case VK_SYSTEM_ALLOCATION_SCOPE_INSTANCE:text = "INSTANCE"; break;
        default : break;
    }

    return text;
}

native_pointer vk_AllocationFunction(
    native_pointer user_data,
    tiny_ulong size,
    tiny_ulong alignment,
    VkSystemAllocationScope scope 
) {
    auto* memory = malloc( size );
    
#   ifdef TINY_DEBUG
    if ( memory ) {
        vk_allocation_stats.Size  += size;
        vk_allocation_stats.Alloc += 1;
    }
#   endif

    return memory;
}

native_pointer vk_ReallocationFunction(
    native_pointer user_data,
    native_pointer original,
    tiny_ulong size,
    tiny_ulong alignment,
    VkSystemAllocationScope scope
) { 
    auto* memory = tiny_cast( nullptr, native_pointer );

    if ( original ) {
        memory = realloc( original, size );

#       ifdef TINY_DEBUG
        vk_allocation_stats.ReAlloc += 1;
#       endif
    }

    return memory;
}

void vk_FreeFunction( native_pointer user_data, native_pointer memory ) {
    if ( memory ) {
#       ifdef TINY_DEBUG
        vk_allocation_stats.Size -= 1;
        vk_allocation_stats.Free += 1;
#       endif

        free( memory );
    }
}

void vk_InternalAllocationNotification(
    native_pointer user_data,
    tiny_ulong size,
    VkInternalAllocationType type,
    VkSystemAllocationScope scope 
) {
#   ifdef TINY_DEBUG
    auto scope_str = vkGetScopeString( scope );

    printf( "[ VK ] INTERNAL ALLOC : %llu for %s\n", size, scope_str.get( ) );
#   endif
}

void vk_InternalFreeNotification(
    native_pointer user_data,
    tiny_ulong size,
    VkInternalAllocationType type,
    VkSystemAllocationScope scope 
) {
#   ifdef TINY_DEBUG
    auto scope_str = vkGetScopeString( scope );

    printf( "[ VK ] INTERNAL FREE : %llu of %s\n", size, scope_str.get( ) );
#   endif
}

VkAllocationCallbacks vk_allocator = {
    VK_NULL_HANDLE,
    vk_AllocationFunction,
    vk_ReallocationFunction,
    vk_FreeFunction,
    vk_InternalAllocationNotification,
    vk_InternalFreeNotification
};

static VKAPI_ATTR VkBool32 VKAPI_CALL debug_report( 
    VkDebugReportFlagsEXT flags,
    VkDebugReportObjectTypeEXT object_type,
    tiny_ulong object,
    tiny_ulong location, 
    tiny_int message_code,
    native_string layer_prefix,
    native_string message,
    native_pointer user_data 
) {
    (void)flags; (void)object; (void)location; (void)message_code; (void)layer_prefix; (void)user_data;

    printf( "[ VK ] Debug report from ObjectType: %i\n%s\n", object_type, message );

    return VK_FALSE;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
bool vk::Check( VkResult result ) {
    auto state = false;

    switch ( result ) {
        default :
        case  VK_SUCCESS:
        case  VK_NOT_READY:
        case  VK_TIMEOUT:
        case  VK_EVENT_SET:
        case  VK_EVENT_RESET:
        case  VK_INCOMPLETE:
        case  VK_SUBOPTIMAL_KHR:
        case  VK_THREAD_IDLE_KHR:
        case  VK_THREAD_DONE_KHR:
        case  VK_OPERATION_DEFERRED_KHR:
        case  VK_OPERATION_NOT_DEFERRED_KHR:
        case  VK_PIPELINE_COMPILE_REQUIRED_EXT:
            state = true; 
            
            break;

        case  VK_ERROR_OUT_OF_HOST_MEMORY:
        case  VK_ERROR_OUT_OF_DEVICE_MEMORY:
        case  VK_ERROR_INITIALIZATION_FAILED:
        case  VK_ERROR_DEVICE_LOST:
        case  VK_ERROR_MEMORY_MAP_FAILED:
        case  VK_ERROR_LAYER_NOT_PRESENT:
        case  VK_ERROR_EXTENSION_NOT_PRESENT:
        case  VK_ERROR_FEATURE_NOT_PRESENT:
        case  VK_ERROR_INCOMPATIBLE_DRIVER:
        case  VK_ERROR_TOO_MANY_OBJECTS:
        case  VK_ERROR_FORMAT_NOT_SUPPORTED:
        case  VK_ERROR_FRAGMENTED_POOL:
        case  VK_ERROR_SURFACE_LOST_KHR:
        case  VK_ERROR_NATIVE_WINDOW_IN_USE_KHR:
        case  VK_ERROR_OUT_OF_DATE_KHR:
        case  VK_ERROR_INCOMPATIBLE_DISPLAY_KHR:
        case  VK_ERROR_INVALID_SHADER_NV:
        case  VK_ERROR_OUT_OF_POOL_MEMORY:
        case  VK_ERROR_INVALID_EXTERNAL_HANDLE:
        case  VK_ERROR_FRAGMENTATION:
        case  VK_ERROR_INVALID_DEVICE_ADDRESS_EXT:
        case  VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT:
        case  VK_ERROR_UNKNOWN:
            state = false;

            break;
    }

#   ifdef TINY_DEBUG
    auto vk_string = vkGetResultString( result );

    if ( vk_string.length( ) > 0 )
        printf( state ? "[ VK ] %s.\n" : "[ VK - ERROR ] %s.\n", vk_string.get( ) );
#   endif

	return state;
}

VkAllocationCallbacks* vk::GetAllocator( ) { return &vk_allocator; }

VkAllocationStas* vk::GetAllocationStas( ) { return &vk_allocation_stats; }

void vk::DumpAllocationStats( ) {
#   ifdef TINY_DEBUG
    printf( 
        "Allocation Stats:\nAllocation : %llu\nFree : %llu\nSize : %llu\n", 
        vk_allocation_stats.Alloc, 
        vk_allocation_stats.Free, 
        vk_allocation_stats.Size 
    );
#   endif
}

bool vk::CreateDebugReport( VkInstance instance ) {
#   ifdef TINY_DEBUG
    auto vk_function = tiny_cast( vkGetInstanceProcAddr( instance, "vkCreateDebugReportCallbackEXT" ), PFN_vkCreateDebugReportCallbackEXT );
    auto state       = vk_function != nullptr;

    if ( state ) {
        auto debug_info = VkDebugReportCallbackCreateInfoEXT{ VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT };

        debug_info.pNext       = VK_NULL_HANDLE;
        debug_info.flags       = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT | VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT;
        debug_info.pfnCallback = debug_report;
        debug_info.pUserData   = VK_NULL_HANDLE;

        state = vk::Check( vk_function( instance, tiny_rvalue( debug_info ), vk::GetAllocator( ), tiny_rvalue( vk_debug ) ) );
    }

    return state;
#   else
    return true;
#   endif
}

void vk::DestroyDebugReport( VkInstance instance ) {
#   ifdef TINY_DEBUG
    auto vk_function = tiny_cast( vkGetInstanceProcAddr( instance, "vkDestroyDebugReportCallbackEXT" ), PFN_vkDestroyDebugReportCallbackEXT );

    if ( vk_function )
        vk_function( instance, vk_debug, vk::GetAllocator( ) );
#   endif
}

bool vk::EnumeratePhysicalDevices( VkInstance instance, tiny_list<VkPhysicalDevice>& storage ) {
    auto capacity = tiny_cast( 0, tiny_uint );
    auto state    = vk::Check( vkEnumeratePhysicalDevices( instance, tiny_rvalue( capacity ), VK_NULL_HANDLE ) );

    if ( state ) {
        storage.resize( capacity );

        state = vk::Check( vkEnumeratePhysicalDevices( instance, tiny_rvalue( capacity ), storage.data( ) ) );
    }

    return state;
}

bool vk::EnumerateDeviceExtensionProperties( VkPhysicalDevice physical, tiny_list<VkExtensionProperties>& storage ) {
    auto capacity = tiny_cast( 0, tiny_uint );
    auto state    = vk::Check( vkEnumerateDeviceExtensionProperties( physical, VK_NULL_HANDLE, tiny_rvalue( capacity ), VK_NULL_HANDLE ) );

    if ( state ) {
        storage.resize( capacity );

        state = vk::Check( vkEnumerateDeviceExtensionProperties( physical, VK_NULL_HANDLE, tiny_rvalue( capacity ), storage.data( ) ) );
    }

    return state;
}

void vk::GetPhysicalDeviceQueueFamilyProperties( VkPhysicalDevice physical, tiny_list<VkQueueFamilyProperties>& storage ) {
    auto capacity = tiny_cast( 0, tiny_uint );

    vkGetPhysicalDeviceQueueFamilyProperties( physical, tiny_rvalue( capacity ), VK_NULL_HANDLE );

    storage.resize( capacity );

    vkGetPhysicalDeviceQueueFamilyProperties( physical, tiny_rvalue( capacity ), storage.data( ) );
}

bool vk::GetIsQueue( const VkPhysicalDeviceQueue& queue, tiny_init<VkQueueTypes> types ) {
    auto state = false;

    for ( auto& type : types ) {
        state = queue.Type == type;

        if ( state )
            break;
    }

    return state;
}

bool vk::GetPhysicalDeviceSurfaceFormats( VkPhysicalDevice physical, VkSurfaceKHR surface, tiny_list<VkSurfaceFormatKHR>& storage ) {
    auto capacity = tiny_cast( 0, tiny_uint );
    auto state    = vk::Check( vkGetPhysicalDeviceSurfaceFormatsKHR( physical, surface, tiny_rvalue( capacity ), VK_NULL_HANDLE ) );

    if ( state ) {
        storage.resize( capacity );

        state = vk::Check( vkGetPhysicalDeviceSurfaceFormatsKHR( physical, surface, tiny_rvalue( capacity ), storage.data( ) ) );
    }

    return state;
}

bool vk::GetSwapchainImages( VkDevice logical, VkSwapchainKHR swapchain, tiny_list<VkImage>& storage ) {
    auto capacity = tiny_cast( 0, tiny_uint );
    auto state    = vk::Check( vkGetSwapchainImagesKHR( logical, swapchain, tiny_rvalue( capacity ), VK_NULL_HANDLE ) );

    if ( state ) {
        storage.resize( capacity );

        state = vk::Check( vkGetSwapchainImagesKHR( logical, swapchain, tiny_rvalue( capacity ), storage.data( ) ) );
    }

    return state;
}

bool vk::GetPipelineCache( VkDevice logical, VkPipelineCache cache, tiny_list<tiny_ubyte>& storage ) {
    auto capacity = tiny_cast( 0, tiny_ulong );
    auto state    = vk::Check( vkGetPipelineCacheData( logical, cache, tiny_rvalue( capacity ), VK_NULL_FLAGS ) );

    if ( state ) {
        storage.resize( tiny_cast( capacity, tiny_uint ) );

        state = vk::Check( vkGetPipelineCacheData( logical, cache, tiny_rvalue( capacity ), storage.data( ) ) );
    }

    return state;
}

bool vk::CreateCommandBuffer( VkDevice logical, VkLogicalQueue& queue, VkLogicalCommandBuffer& command_buffer ) {
    auto buffer_info = VkCommandBufferAllocateInfo{ VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO };

    buffer_info.pNext              = VK_NULL_HANDLE;
    buffer_info.commandPool        = queue.CommandPool;
    buffer_info.level              = !vk::GetIsValid( queue.CommandBuffer.Buffer ) ? VK_COMMAND_BUFFER_LEVEL_PRIMARY : VK_COMMAND_BUFFER_LEVEL_SECONDARY;
    buffer_info.commandBufferCount = 1;

    auto state = vk::Check( vkAllocateCommandBuffers( logical, tiny_rvalue( buffer_info ), tiny_rvalue( command_buffer.Buffer ) ) );

    if ( state )
        command_buffer.State = VK_COMMAND_BUFFER_STATE_PENDING;

    return state;
}

bool vk::ResetCommandBuffer( VkLogicalCommandBuffer& command_buffer ) {
    auto state = vk::GetIsValid( command_buffer.Buffer );

    if ( state ) {
        state = vk::Check( vkResetCommandBuffer( command_buffer.Buffer, VK_COMMAND_BUFFER_RESET_RELEASE_RESOURCES_BIT ) );

        if ( state )
            command_buffer.State = VK_COMMAND_BUFFER_STATE_PENDING;
    }

    return state;
}

bool vk::BeginCommandBuffer( VkLogicalCommandBuffer& command_buffer ) {
    auto state = vk::GetIsBuffer( command_buffer, VK_COMMAND_BUFFER_STATE_PENDING );

    if ( state ) {
        auto begin_info = VkCommandBufferBeginInfo{ VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO };

        begin_info.pNext            = VK_NULL_HANDLE;
        begin_info.flags            = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
        begin_info.pInheritanceInfo = VK_NULL_HANDLE;

        state = vk::Check( vkBeginCommandBuffer( command_buffer.Buffer, tiny_rvalue( begin_info ) ) );

        if ( state )
            command_buffer.State = VK_COMMAND_BUFFER_STATE_RECORD;
    }

    return state;
}

bool vk::EndCommandBuffer( VkLogicalCommandBuffer& command_buffer ) {
    auto state = vk::GetIsBuffer( command_buffer, VK_COMMAND_BUFFER_STATE_RECORD );

    if ( state ) {
        state = vk::Check( vkEndCommandBuffer( command_buffer.Buffer ) );

        if ( state )
            command_buffer.State = VK_COMMAND_BUFFER_STATE_SUBMIT;
    }

    return state;
}

void vk::DestroyCommandBuffer( VkDevice logical, VkLogicalQueue& queue, VkLogicalCommandBuffer& command_buffer ) {
    if ( vk::GetIsValid( command_buffer.Buffer ) )
        vkFreeCommandBuffers( logical, queue.CommandPool, 1, &command_buffer.Buffer );
}

bool vk::GetIsBuffer( const VkLogicalCommandBuffer& command_buffer, VkCommandBufferStates state ) {
    return vk::GetIsValid( command_buffer.Buffer ) && command_buffer.State == state;
}

bool vk::GetPipelineCacheData( VkDevice logical, VkPipelineCache pipeline_cache, tiny_list<tiny_ubyte>& storage ) {
    auto capacity = tiny_cast( 0, tiny_ulong );
    auto state    = vk::Check( vkGetPipelineCacheData( logical, pipeline_cache, tiny_rvalue( capacity ), VK_NULL_HANDLE ) );

    if ( state ) {
        storage.resize( tiny_cast( capacity, tiny_uint ) );

        state = vk::Check( vkGetPipelineCacheData( logical, pipeline_cache, tiny_rvalue( capacity ), storage.data( ) ) );
    }

    return state;
}

VkClearColorValue vk::CastColor( const tiny_color& color ) {
    auto color_value = VkClearColorValue{ };

    auto* src = color.Channels;
    auto* dst = color_value.float32;

    Tiny::Memcpy( src, dst, 4 * tiny_sizeof( float ) );

    return color_value;
}

#define VK_TO_STRING( ENUM_VAL )\
    case ENUM_VAL: text = #ENUM_VAL; break;

native_string vk::CastFormat( const VkFormat format ) {
    auto text = "UNDEFINED";

    switch ( format ) {
        VK_TO_STRING( VK_FORMAT_R4G4_UNORM_PACK8 );

        VK_TO_STRING( VK_FORMAT_R4G4B4A4_UNORM_PACK16 );
        VK_TO_STRING( VK_FORMAT_B4G4R4A4_UNORM_PACK16 );
        VK_TO_STRING( VK_FORMAT_R5G6B5_UNORM_PACK16 );
        VK_TO_STRING( VK_FORMAT_B5G6R5_UNORM_PACK16 );
        VK_TO_STRING( VK_FORMAT_R5G5B5A1_UNORM_PACK16 );
        VK_TO_STRING( VK_FORMAT_B5G5R5A1_UNORM_PACK16 );
        VK_TO_STRING( VK_FORMAT_A1R5G5B5_UNORM_PACK16 );
        VK_TO_STRING( VK_FORMAT_R8_UNORM );
        VK_TO_STRING( VK_FORMAT_R8_SNORM );
        VK_TO_STRING( VK_FORMAT_R8_USCALED );
        VK_TO_STRING( VK_FORMAT_R8_SSCALED );
        VK_TO_STRING( VK_FORMAT_R8_UINT );
        VK_TO_STRING( VK_FORMAT_R8_SINT );
        VK_TO_STRING( VK_FORMAT_R8_SRGB );
        VK_TO_STRING( VK_FORMAT_R8G8_UNORM );
        VK_TO_STRING( VK_FORMAT_R8G8_SNORM );
        VK_TO_STRING( VK_FORMAT_R8G8_USCALED );
        VK_TO_STRING( VK_FORMAT_R8G8_SSCALED );
        VK_TO_STRING( VK_FORMAT_R8G8_UINT );
        VK_TO_STRING( VK_FORMAT_R8G8_SINT );
        VK_TO_STRING( VK_FORMAT_R8G8_SRGB );
        VK_TO_STRING( VK_FORMAT_R8G8B8_UNORM );
        VK_TO_STRING( VK_FORMAT_R8G8B8_SNORM );
        VK_TO_STRING( VK_FORMAT_R8G8B8_USCALED );
        VK_TO_STRING( VK_FORMAT_R8G8B8_SSCALED );
        VK_TO_STRING( VK_FORMAT_R8G8B8_UINT );
        VK_TO_STRING( VK_FORMAT_R8G8B8_SINT );
        VK_TO_STRING( VK_FORMAT_R8G8B8_SRGB );
        VK_TO_STRING( VK_FORMAT_B8G8R8_UNORM );
        VK_TO_STRING( VK_FORMAT_B8G8R8_SNORM );
        VK_TO_STRING( VK_FORMAT_B8G8R8_USCALED );
        VK_TO_STRING( VK_FORMAT_B8G8R8_SSCALED );
        VK_TO_STRING( VK_FORMAT_B8G8R8_UINT );
        VK_TO_STRING( VK_FORMAT_B8G8R8_SINT );
        VK_TO_STRING( VK_FORMAT_B8G8R8_SRGB );
        VK_TO_STRING( VK_FORMAT_R8G8B8A8_UNORM );
        VK_TO_STRING( VK_FORMAT_R8G8B8A8_SNORM );
        VK_TO_STRING( VK_FORMAT_R8G8B8A8_USCALED );
        VK_TO_STRING( VK_FORMAT_R8G8B8A8_SSCALED );
        VK_TO_STRING( VK_FORMAT_R8G8B8A8_UINT );
        VK_TO_STRING( VK_FORMAT_R8G8B8A8_SINT );
        VK_TO_STRING( VK_FORMAT_R8G8B8A8_SRGB );
        VK_TO_STRING( VK_FORMAT_B8G8R8A8_UNORM );
        VK_TO_STRING( VK_FORMAT_B8G8R8A8_SNORM );
        VK_TO_STRING( VK_FORMAT_B8G8R8A8_USCALED );
        VK_TO_STRING( VK_FORMAT_B8G8R8A8_SSCALED );
        VK_TO_STRING( VK_FORMAT_B8G8R8A8_UINT );
        VK_TO_STRING( VK_FORMAT_B8G8R8A8_SINT );
        VK_TO_STRING( VK_FORMAT_B8G8R8A8_SRGB );
        VK_TO_STRING( VK_FORMAT_A8B8G8R8_UNORM_PACK32 );
        VK_TO_STRING( VK_FORMAT_A8B8G8R8_SNORM_PACK32 );
        VK_TO_STRING( VK_FORMAT_A8B8G8R8_USCALED_PACK32 );
        VK_TO_STRING( VK_FORMAT_A8B8G8R8_SSCALED_PACK32 );
        VK_TO_STRING( VK_FORMAT_A8B8G8R8_UINT_PACK32 );
        VK_TO_STRING( VK_FORMAT_A8B8G8R8_SINT_PACK32 );
        VK_TO_STRING( VK_FORMAT_A8B8G8R8_SRGB_PACK32 );
        VK_TO_STRING( VK_FORMAT_A2R10G10B10_UNORM_PACK32 );
        VK_TO_STRING( VK_FORMAT_A2R10G10B10_SNORM_PACK32 );
        VK_TO_STRING( VK_FORMAT_A2R10G10B10_USCALED_PACK32 );
        VK_TO_STRING( VK_FORMAT_A2R10G10B10_SSCALED_PACK32 );
        VK_TO_STRING( VK_FORMAT_A2R10G10B10_UINT_PACK32 );
        VK_TO_STRING( VK_FORMAT_A2R10G10B10_SINT_PACK32 );
        VK_TO_STRING( VK_FORMAT_A2B10G10R10_UNORM_PACK32 );
        VK_TO_STRING( VK_FORMAT_A2B10G10R10_SNORM_PACK32 );
        VK_TO_STRING( VK_FORMAT_A2B10G10R10_USCALED_PACK32 );
        VK_TO_STRING( VK_FORMAT_A2B10G10R10_SSCALED_PACK32 );
        VK_TO_STRING( VK_FORMAT_A2B10G10R10_UINT_PACK32 );
        VK_TO_STRING( VK_FORMAT_A2B10G10R10_SINT_PACK32 );
        VK_TO_STRING( VK_FORMAT_R16_UNORM );
        VK_TO_STRING( VK_FORMAT_R16_SNORM );
        VK_TO_STRING( VK_FORMAT_R16_USCALED );
        VK_TO_STRING( VK_FORMAT_R16_SSCALED );
        VK_TO_STRING( VK_FORMAT_R16_UINT );
        VK_TO_STRING( VK_FORMAT_R16_SINT );
        VK_TO_STRING( VK_FORMAT_R16_SFLOAT );
        VK_TO_STRING( VK_FORMAT_R16G16_UNORM );
        VK_TO_STRING( VK_FORMAT_R16G16_SNORM );
        VK_TO_STRING( VK_FORMAT_R16G16_USCALED );
        VK_TO_STRING( VK_FORMAT_R16G16_SSCALED );
        VK_TO_STRING( VK_FORMAT_R16G16_UINT );
        VK_TO_STRING( VK_FORMAT_R16G16_SINT );
        VK_TO_STRING( VK_FORMAT_R16G16_SFLOAT );
        VK_TO_STRING( VK_FORMAT_R16G16B16_UNORM );
        VK_TO_STRING( VK_FORMAT_R16G16B16_SNORM );
        VK_TO_STRING( VK_FORMAT_R16G16B16_USCALED );
        VK_TO_STRING( VK_FORMAT_R16G16B16_SSCALED );
        VK_TO_STRING( VK_FORMAT_R16G16B16_UINT );
        VK_TO_STRING( VK_FORMAT_R16G16B16_SINT );
        VK_TO_STRING( VK_FORMAT_R16G16B16_SFLOAT );
        VK_TO_STRING( VK_FORMAT_R16G16B16A16_UNORM );
        VK_TO_STRING( VK_FORMAT_R16G16B16A16_SNORM );
        VK_TO_STRING( VK_FORMAT_R16G16B16A16_USCALED );
        VK_TO_STRING( VK_FORMAT_R16G16B16A16_SSCALED );
        VK_TO_STRING( VK_FORMAT_R16G16B16A16_UINT );
        VK_TO_STRING( VK_FORMAT_R16G16B16A16_SINT );
        VK_TO_STRING( VK_FORMAT_R16G16B16A16_SFLOAT );
        VK_TO_STRING( VK_FORMAT_R32_UINT );
        VK_TO_STRING( VK_FORMAT_R32_SINT );
        VK_TO_STRING( VK_FORMAT_R32_SFLOAT );
        VK_TO_STRING( VK_FORMAT_R32G32_UINT );
        VK_TO_STRING( VK_FORMAT_R32G32_SINT );
        VK_TO_STRING( VK_FORMAT_R32G32_SFLOAT );
        VK_TO_STRING( VK_FORMAT_R32G32B32_UINT );
        VK_TO_STRING( VK_FORMAT_R32G32B32_SINT );
        VK_TO_STRING( VK_FORMAT_R32G32B32_SFLOAT );
        VK_TO_STRING( VK_FORMAT_R32G32B32A32_UINT );
        VK_TO_STRING( VK_FORMAT_R32G32B32A32_SINT );
        VK_TO_STRING( VK_FORMAT_R32G32B32A32_SFLOAT );
        VK_TO_STRING( VK_FORMAT_R64_UINT );
        VK_TO_STRING( VK_FORMAT_R64_SINT );
        VK_TO_STRING( VK_FORMAT_R64_SFLOAT );
        VK_TO_STRING( VK_FORMAT_R64G64_UINT );
        VK_TO_STRING( VK_FORMAT_R64G64_SINT );
        VK_TO_STRING( VK_FORMAT_R64G64_SFLOAT );
        VK_TO_STRING( VK_FORMAT_R64G64B64_UINT );
        VK_TO_STRING( VK_FORMAT_R64G64B64_SINT );
        VK_TO_STRING( VK_FORMAT_R64G64B64_SFLOAT );
        VK_TO_STRING( VK_FORMAT_R64G64B64A64_UINT );
        VK_TO_STRING( VK_FORMAT_R64G64B64A64_SINT );
        VK_TO_STRING( VK_FORMAT_R64G64B64A64_SFLOAT );
        VK_TO_STRING( VK_FORMAT_B10G11R11_UFLOAT_PACK32 );
        VK_TO_STRING( VK_FORMAT_E5B9G9R9_UFLOAT_PACK32 );
        VK_TO_STRING( VK_FORMAT_D16_UNORM );
        VK_TO_STRING( VK_FORMAT_X8_D24_UNORM_PACK32 );
        VK_TO_STRING( VK_FORMAT_D32_SFLOAT );
        VK_TO_STRING( VK_FORMAT_S8_UINT );
        VK_TO_STRING( VK_FORMAT_D16_UNORM_S8_UINT );
        VK_TO_STRING( VK_FORMAT_D24_UNORM_S8_UINT );
        VK_TO_STRING( VK_FORMAT_D32_SFLOAT_S8_UINT );
        VK_TO_STRING( VK_FORMAT_BC1_RGB_UNORM_BLOCK );
        VK_TO_STRING( VK_FORMAT_BC1_RGB_SRGB_BLOCK );
        VK_TO_STRING( VK_FORMAT_BC1_RGBA_UNORM_BLOCK );
        VK_TO_STRING( VK_FORMAT_BC1_RGBA_SRGB_BLOCK );
        VK_TO_STRING( VK_FORMAT_BC2_UNORM_BLOCK );
        VK_TO_STRING( VK_FORMAT_BC2_SRGB_BLOCK );
        VK_TO_STRING( VK_FORMAT_BC3_UNORM_BLOCK );
        VK_TO_STRING( VK_FORMAT_BC3_SRGB_BLOCK );
        VK_TO_STRING( VK_FORMAT_BC4_UNORM_BLOCK );
        VK_TO_STRING( VK_FORMAT_BC4_SNORM_BLOCK );
        VK_TO_STRING( VK_FORMAT_BC5_UNORM_BLOCK );
        VK_TO_STRING( VK_FORMAT_BC5_SNORM_BLOCK );
        VK_TO_STRING( VK_FORMAT_BC6H_UFLOAT_BLOCK );
        VK_TO_STRING( VK_FORMAT_BC6H_SFLOAT_BLOCK );
        VK_TO_STRING( VK_FORMAT_BC7_UNORM_BLOCK );
        VK_TO_STRING( VK_FORMAT_BC7_SRGB_BLOCK );
        VK_TO_STRING( VK_FORMAT_ETC2_R8G8B8_UNORM_BLOCK );
        VK_TO_STRING( VK_FORMAT_ETC2_R8G8B8_SRGB_BLOCK );
        VK_TO_STRING( VK_FORMAT_ETC2_R8G8B8A1_UNORM_BLOCK );
        VK_TO_STRING( VK_FORMAT_ETC2_R8G8B8A1_SRGB_BLOCK );
        VK_TO_STRING( VK_FORMAT_ETC2_R8G8B8A8_UNORM_BLOCK );
        VK_TO_STRING( VK_FORMAT_ETC2_R8G8B8A8_SRGB_BLOCK );
        VK_TO_STRING( VK_FORMAT_EAC_R11_UNORM_BLOCK );
        VK_TO_STRING( VK_FORMAT_EAC_R11_SNORM_BLOCK );
        VK_TO_STRING( VK_FORMAT_EAC_R11G11_UNORM_BLOCK );
        VK_TO_STRING( VK_FORMAT_EAC_R11G11_SNORM_BLOCK );
        VK_TO_STRING( VK_FORMAT_ASTC_4x4_UNORM_BLOCK );
        VK_TO_STRING( VK_FORMAT_ASTC_4x4_SRGB_BLOCK );
        VK_TO_STRING( VK_FORMAT_ASTC_5x4_UNORM_BLOCK );
        VK_TO_STRING( VK_FORMAT_ASTC_5x4_SRGB_BLOCK );
        VK_TO_STRING( VK_FORMAT_ASTC_5x5_UNORM_BLOCK );
        VK_TO_STRING( VK_FORMAT_ASTC_5x5_SRGB_BLOCK );
        VK_TO_STRING( VK_FORMAT_ASTC_6x5_UNORM_BLOCK );
        VK_TO_STRING( VK_FORMAT_ASTC_6x5_SRGB_BLOCK );
        VK_TO_STRING( VK_FORMAT_ASTC_6x6_UNORM_BLOCK );
        VK_TO_STRING( VK_FORMAT_ASTC_6x6_SRGB_BLOCK );
        VK_TO_STRING( VK_FORMAT_ASTC_8x5_UNORM_BLOCK );
        VK_TO_STRING( VK_FORMAT_ASTC_8x5_SRGB_BLOCK );
        VK_TO_STRING( VK_FORMAT_ASTC_8x6_UNORM_BLOCK );
        VK_TO_STRING( VK_FORMAT_ASTC_8x6_SRGB_BLOCK );
        VK_TO_STRING( VK_FORMAT_ASTC_8x8_UNORM_BLOCK );
        VK_TO_STRING( VK_FORMAT_ASTC_8x8_SRGB_BLOCK );
        VK_TO_STRING( VK_FORMAT_ASTC_10x5_UNORM_BLOCK );
        VK_TO_STRING( VK_FORMAT_ASTC_10x5_SRGB_BLOCK );
        VK_TO_STRING( VK_FORMAT_ASTC_10x6_UNORM_BLOCK );
        VK_TO_STRING( VK_FORMAT_ASTC_10x6_SRGB_BLOCK );
        VK_TO_STRING( VK_FORMAT_ASTC_10x8_UNORM_BLOCK );
        VK_TO_STRING( VK_FORMAT_ASTC_10x8_SRGB_BLOCK );
        VK_TO_STRING( VK_FORMAT_ASTC_10x10_UNORM_BLOCK );
        VK_TO_STRING( VK_FORMAT_ASTC_10x10_SRGB_BLOCK );
        VK_TO_STRING( VK_FORMAT_ASTC_12x10_UNORM_BLOCK );
        VK_TO_STRING( VK_FORMAT_ASTC_12x10_SRGB_BLOCK );
        VK_TO_STRING( VK_FORMAT_ASTC_12x12_UNORM_BLOCK );
        VK_TO_STRING( VK_FORMAT_ASTC_12x12_SRGB_BLOCK );
        VK_TO_STRING( VK_FORMAT_G8B8G8R8_422_UNORM );
        VK_TO_STRING( VK_FORMAT_B8G8R8G8_422_UNORM );
        VK_TO_STRING( VK_FORMAT_G8_B8_R8_3PLANE_420_UNORM );
        VK_TO_STRING( VK_FORMAT_G8_B8R8_2PLANE_420_UNORM );
        VK_TO_STRING( VK_FORMAT_G8_B8_R8_3PLANE_422_UNORM );
        VK_TO_STRING( VK_FORMAT_G8_B8R8_2PLANE_422_UNORM );
        VK_TO_STRING( VK_FORMAT_G8_B8_R8_3PLANE_444_UNORM );
        VK_TO_STRING( VK_FORMAT_R10X6_UNORM_PACK16 );
        VK_TO_STRING( VK_FORMAT_R10X6G10X6_UNORM_2PACK16 );
        VK_TO_STRING( VK_FORMAT_R10X6G10X6B10X6A10X6_UNORM_4PACK16 );
        VK_TO_STRING( VK_FORMAT_G10X6B10X6G10X6R10X6_422_UNORM_4PACK16 );
        VK_TO_STRING( VK_FORMAT_B10X6G10X6R10X6G10X6_422_UNORM_4PACK16 );
        VK_TO_STRING( VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_420_UNORM_3PACK16 );
        VK_TO_STRING( VK_FORMAT_G10X6_B10X6R10X6_2PLANE_420_UNORM_3PACK16 );
        VK_TO_STRING( VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_422_UNORM_3PACK16 );
        VK_TO_STRING( VK_FORMAT_G10X6_B10X6R10X6_2PLANE_422_UNORM_3PACK16 );
        VK_TO_STRING( VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_444_UNORM_3PACK16 );
        VK_TO_STRING( VK_FORMAT_R12X4_UNORM_PACK16 );
        VK_TO_STRING( VK_FORMAT_R12X4G12X4_UNORM_2PACK16 );
        VK_TO_STRING( VK_FORMAT_R12X4G12X4B12X4A12X4_UNORM_4PACK16 );
        VK_TO_STRING( VK_FORMAT_G12X4B12X4G12X4R12X4_422_UNORM_4PACK16 );
        VK_TO_STRING( VK_FORMAT_B12X4G12X4R12X4G12X4_422_UNORM_4PACK16 );
        VK_TO_STRING( VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_420_UNORM_3PACK16 );
        VK_TO_STRING( VK_FORMAT_G12X4_B12X4R12X4_2PLANE_420_UNORM_3PACK16 );
        VK_TO_STRING( VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_422_UNORM_3PACK16 );
        VK_TO_STRING( VK_FORMAT_G12X4_B12X4R12X4_2PLANE_422_UNORM_3PACK16 );
        VK_TO_STRING( VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_444_UNORM_3PACK16 );
        VK_TO_STRING( VK_FORMAT_G16B16G16R16_422_UNORM );
        VK_TO_STRING( VK_FORMAT_B16G16R16G16_422_UNORM );
        VK_TO_STRING( VK_FORMAT_G16_B16_R16_3PLANE_420_UNORM );
        VK_TO_STRING( VK_FORMAT_G16_B16R16_2PLANE_420_UNORM );
        VK_TO_STRING( VK_FORMAT_G16_B16_R16_3PLANE_422_UNORM );
        VK_TO_STRING( VK_FORMAT_G16_B16R16_2PLANE_422_UNORM );
        VK_TO_STRING( VK_FORMAT_G16_B16_R16_3PLANE_444_UNORM );
        VK_TO_STRING( VK_FORMAT_G8_B8R8_2PLANE_444_UNORM );
        VK_TO_STRING( VK_FORMAT_G10X6_B10X6R10X6_2PLANE_444_UNORM_3PACK16 );
        VK_TO_STRING( VK_FORMAT_G12X4_B12X4R12X4_2PLANE_444_UNORM_3PACK16 );
        VK_TO_STRING( VK_FORMAT_G16_B16R16_2PLANE_444_UNORM );
        VK_TO_STRING( VK_FORMAT_A4R4G4B4_UNORM_PACK16 );
        VK_TO_STRING( VK_FORMAT_A4B4G4R4_UNORM_PACK16 );
        VK_TO_STRING( VK_FORMAT_ASTC_4x4_SFLOAT_BLOCK );
        VK_TO_STRING( VK_FORMAT_ASTC_5x4_SFLOAT_BLOCK );
        VK_TO_STRING( VK_FORMAT_ASTC_5x5_SFLOAT_BLOCK );
        VK_TO_STRING( VK_FORMAT_ASTC_6x5_SFLOAT_BLOCK );
        VK_TO_STRING( VK_FORMAT_ASTC_6x6_SFLOAT_BLOCK );
        VK_TO_STRING( VK_FORMAT_ASTC_8x5_SFLOAT_BLOCK );
        VK_TO_STRING( VK_FORMAT_ASTC_8x6_SFLOAT_BLOCK );
        VK_TO_STRING( VK_FORMAT_ASTC_8x8_SFLOAT_BLOCK );
        VK_TO_STRING( VK_FORMAT_ASTC_10x5_SFLOAT_BLOCK );
        VK_TO_STRING( VK_FORMAT_ASTC_10x6_SFLOAT_BLOCK );
        VK_TO_STRING( VK_FORMAT_ASTC_10x8_SFLOAT_BLOCK );
        VK_TO_STRING( VK_FORMAT_ASTC_10x10_SFLOAT_BLOCK );
        VK_TO_STRING( VK_FORMAT_ASTC_12x10_SFLOAT_BLOCK );
        VK_TO_STRING( VK_FORMAT_ASTC_12x12_SFLOAT_BLOCK );
        VK_TO_STRING( VK_FORMAT_PVRTC1_2BPP_UNORM_BLOCK_IMG );
        VK_TO_STRING( VK_FORMAT_PVRTC1_4BPP_UNORM_BLOCK_IMG );
        VK_TO_STRING( VK_FORMAT_PVRTC2_2BPP_UNORM_BLOCK_IMG );
        VK_TO_STRING( VK_FORMAT_PVRTC2_4BPP_UNORM_BLOCK_IMG );
        VK_TO_STRING( VK_FORMAT_PVRTC1_2BPP_SRGB_BLOCK_IMG );
        VK_TO_STRING( VK_FORMAT_PVRTC1_4BPP_SRGB_BLOCK_IMG );
        VK_TO_STRING( VK_FORMAT_PVRTC2_2BPP_SRGB_BLOCK_IMG );
        VK_TO_STRING( VK_FORMAT_PVRTC2_4BPP_SRGB_BLOCK_IMG );
        VK_TO_STRING( VK_FORMAT_R16G16_S10_5_NV );
        VK_TO_STRING( VK_FORMAT_A1B5G5R5_UNORM_PACK16_KHR );
        VK_TO_STRING( VK_FORMAT_A8_UNORM_KHR );

        default : break;
    }

    return text;
}

native_string vk::CastColorSpace( const VkColorSpaceKHR color_space ) {
    auto text = tiny_string{ "UNDEFINED" };

    switch ( color_space ) {
        VK_TO_STRING( VK_COLOR_SPACE_SRGB_NONLINEAR_KHR );
        VK_TO_STRING( VK_COLOR_SPACE_DISPLAY_P3_NONLINEAR_EXT );
        VK_TO_STRING( VK_COLOR_SPACE_EXTENDED_SRGB_LINEAR_EXT );
        VK_TO_STRING( VK_COLOR_SPACE_DISPLAY_P3_LINEAR_EXT );
        VK_TO_STRING( VK_COLOR_SPACE_DCI_P3_NONLINEAR_EXT );
        VK_TO_STRING( VK_COLOR_SPACE_BT709_LINEAR_EXT );
        VK_TO_STRING( VK_COLOR_SPACE_BT709_NONLINEAR_EXT );
        VK_TO_STRING( VK_COLOR_SPACE_BT2020_LINEAR_EXT );
        VK_TO_STRING( VK_COLOR_SPACE_HDR10_ST2084_EXT );
        VK_TO_STRING( VK_COLOR_SPACE_DOLBYVISION_EXT );
        VK_TO_STRING( VK_COLOR_SPACE_HDR10_HLG_EXT );
        VK_TO_STRING( VK_COLOR_SPACE_ADOBERGB_LINEAR_EXT );
        VK_TO_STRING( VK_COLOR_SPACE_ADOBERGB_NONLINEAR_EXT );
        VK_TO_STRING( VK_COLOR_SPACE_PASS_THROUGH_EXT );
        VK_TO_STRING( VK_COLOR_SPACE_EXTENDED_SRGB_NONLINEAR_EXT );
        VK_TO_STRING( VK_COLOR_SPACE_DISPLAY_NATIVE_AMD );

        default: break;
    }

    return text;
}

native_string vk::CastPresentMode( const VkPresentModeKHR present_mode ) {
    auto text = "UNDEFINED";

    switch ( present_mode ) {
        VK_TO_STRING( VK_PRESENT_MODE_IMMEDIATE_KHR );
        VK_TO_STRING( VK_PRESENT_MODE_MAILBOX_KHR );
        VK_TO_STRING( VK_PRESENT_MODE_FIFO_KHR );
        VK_TO_STRING( VK_PRESENT_MODE_FIFO_RELAXED_KHR );
        VK_TO_STRING( VK_PRESENT_MODE_SHARED_DEMAND_REFRESH_KHR );
        VK_TO_STRING( VK_PRESENT_MODE_SHARED_CONTINUOUS_REFRESH_KHR );

        default : break;
    }

    return text;
}

native_string vk::CastLayout( const VkImageLayout layout ) {
    auto text = "UNDEFINED";

    switch ( layout ) {
        VK_TO_STRING( VK_IMAGE_LAYOUT_GENERAL );
        VK_TO_STRING( VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL );
        VK_TO_STRING( VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL );
        VK_TO_STRING( VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL );
        VK_TO_STRING( VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL );
        VK_TO_STRING( VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL );
        VK_TO_STRING( VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL );
        VK_TO_STRING( VK_IMAGE_LAYOUT_PREINITIALIZED );
        VK_TO_STRING( VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_STENCIL_ATTACHMENT_OPTIMAL );
        VK_TO_STRING( VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_STENCIL_READ_ONLY_OPTIMAL );
        VK_TO_STRING( VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL );
        VK_TO_STRING( VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_OPTIMAL );
        VK_TO_STRING( VK_IMAGE_LAYOUT_STENCIL_ATTACHMENT_OPTIMAL );
        VK_TO_STRING( VK_IMAGE_LAYOUT_STENCIL_READ_ONLY_OPTIMAL );
        VK_TO_STRING( VK_IMAGE_LAYOUT_READ_ONLY_OPTIMAL );
        VK_TO_STRING( VK_IMAGE_LAYOUT_ATTACHMENT_OPTIMAL );
        VK_TO_STRING( VK_IMAGE_LAYOUT_PRESENT_SRC_KHR );
        VK_TO_STRING( VK_IMAGE_LAYOUT_VIDEO_DECODE_DST_KHR );
        VK_TO_STRING( VK_IMAGE_LAYOUT_VIDEO_DECODE_SRC_KHR );
        VK_TO_STRING( VK_IMAGE_LAYOUT_VIDEO_DECODE_DPB_KHR );
        VK_TO_STRING( VK_IMAGE_LAYOUT_SHARED_PRESENT_KHR );
        VK_TO_STRING( VK_IMAGE_LAYOUT_FRAGMENT_DENSITY_MAP_OPTIMAL_EXT );
        VK_TO_STRING( VK_IMAGE_LAYOUT_FRAGMENT_SHADING_RATE_ATTACHMENT_OPTIMAL_KHR );
        VK_TO_STRING( VK_IMAGE_LAYOUT_ATTACHMENT_FEEDBACK_LOOP_OPTIMAL_EXT );

        default: break;
    }

    return text;
}

native_string vk::CastAspect( const VkImageAspectFlags aspect ) {
    auto text = "UNDEFINED";

    switch ( aspect ) {
        VK_TO_STRING( VK_IMAGE_ASPECT_COLOR_BIT );
        VK_TO_STRING( VK_IMAGE_ASPECT_DEPTH_BIT );
        VK_TO_STRING( VK_IMAGE_ASPECT_STENCIL_BIT );
        VK_TO_STRING( VK_IMAGE_ASPECT_METADATA_BIT );
        VK_TO_STRING( VK_IMAGE_ASPECT_PLANE_0_BIT );
        VK_TO_STRING( VK_IMAGE_ASPECT_PLANE_1_BIT );
        VK_TO_STRING( VK_IMAGE_ASPECT_PLANE_2_BIT );
        VK_TO_STRING( VK_IMAGE_ASPECT_NONE );
        VK_TO_STRING( VK_IMAGE_ASPECT_MEMORY_PLANE_0_BIT_EXT );
        VK_TO_STRING( VK_IMAGE_ASPECT_MEMORY_PLANE_1_BIT_EXT );
        VK_TO_STRING( VK_IMAGE_ASPECT_MEMORY_PLANE_2_BIT_EXT );
        VK_TO_STRING( VK_IMAGE_ASPECT_MEMORY_PLANE_3_BIT_EXT );

        default : break;
    }

    return text;
}

native_string vk::CastSamples( const VkSampleCountFlags samples ) {
    auto text = "UNDEFINED";

    switch ( samples ) {
        VK_TO_STRING( VK_SAMPLE_COUNT_1_BIT );
        VK_TO_STRING( VK_SAMPLE_COUNT_2_BIT );
        VK_TO_STRING( VK_SAMPLE_COUNT_4_BIT );
        VK_TO_STRING( VK_SAMPLE_COUNT_8_BIT );
        VK_TO_STRING( VK_SAMPLE_COUNT_16_BIT );
        VK_TO_STRING( VK_SAMPLE_COUNT_32_BIT );
        VK_TO_STRING( VK_SAMPLE_COUNT_64_BIT );

        default : break;
    }

    return text;
}

native_string vk::CastTiling( const VkImageTiling tiling ) {
    auto text = "UNDEFINED";

    switch ( tiling ) {
        VK_TO_STRING( VK_IMAGE_TILING_OPTIMAL );
        VK_TO_STRING( VK_IMAGE_TILING_LINEAR );
        VK_TO_STRING( VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT );

        default: break;
    }

    return text;
}
