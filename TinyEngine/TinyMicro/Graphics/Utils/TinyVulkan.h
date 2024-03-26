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

#pragma once

#include <TinyMicro/Audio/TinyAudioManager.h>

#define VK_NULL_FLAGS 0

#define TINY_VK_API VK_API_VERSION_1_3
#define TINY_APP_VERSION VK_MAKE_VERSION( 1, 0, 0 )
#define TINY_ENG_VERSION VK_MAKE_VERSION( 1, 0, 0 )
#define TINY_DESIRED_BUFFERING 3

typedef VkRect2D VkScissor;

tiny_enum( VkQueueTypes ) {

	VK_QUEUE_TYPE_UNDEFINED = 0,
	VK_QUEUE_TYPE_PRESENT,
	VK_QUEUE_TYPE_GRAPHIC,
	VK_QUEUE_TYPE_TRANSFER,
	VK_QUEUE_TYPE_DECODE

};

tm_struct VkPhysicalDeviceQueue {

	VkQueueTypes Type = VK_QUEUE_TYPE_UNDEFINED;
	tiny_uint Family  = 0;
	tiny_uint Count   = 0;

};

tiny_enum( VkCommandBufferStates ) { 

	VK_COMMAND_BUFFER_STATE_UNDEFINED = 0,
	VK_COMMAND_BUFFER_STATE_PENDING,
	VK_COMMAND_BUFFER_STATE_RECORD,
	VK_COMMAND_BUFFER_STATE_SUBMIT

};

tm_struct VkLogicalCommandBuffer {

	VkCommandBuffer Buffer		= VK_NULL_HANDLE;
	VkCommandBufferStates State = VK_COMMAND_BUFFER_STATE_UNDEFINED;

	operator const VkCommandBuffer ( ) const { return Buffer; };

	operator const VkCommandBuffer* ( ) const { return &Buffer; };

};

tm_struct VkLogicalQueue {

	VkBool32 InUse			  = VK_FALSE;
	VkQueue	Queue			  = VK_NULL_HANDLE;
	VkCommandPool CommandPool = VK_NULL_HANDLE;
	VkLogicalCommandBuffer CommandBuffer{ };

};

tm_struct VkAllocationStas {

	tiny_ulong Size;
	tiny_ulong Alloc;
	tiny_ulong ReAlloc;
	tiny_ulong Free;

};

namespace vk {

	static constexpr c_string LAYERS[] = {

		"VK_LAYER_KHRONOS_validation"

	};

	static constexpr c_string EXTENSIONS[] = {
		
		VK_KHR_MAINTENANCE3_EXTENSION_NAME,
		VK_EXT_DESCRIPTOR_INDEXING_EXTENSION_NAME,
		VK_KHR_SWAPCHAIN_EXTENSION_NAME

	};

	static constexpr VkFormat DEPTH_FORMATS[] = { 

		VK_FORMAT_D24_UNORM_S8_UINT,
		VK_FORMAT_D32_SFLOAT_S8_UINT

	};

	static constexpr VkFormatFeatureFlagBits DEPTH_FLAGS = VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT;

	static constexpr float QUEUES_PRIORITIES[] = { 
		1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 
		1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f 
	};

	template<typename Type>
	bool GetIsValid( Type handle ) { return handle != VK_NULL_HANDLE; };

	tm_dll bool Check( VkResult result );

	tm_dll VkAllocationCallbacks* GetAllocator( );

	tm_dll VkAllocationStas* GetAllocationStas( );

	tm_dll bool CreateDebugReport( VkInstance instance );

	tm_dll void DestroyDebugReport( VkInstance instance );

	tm_dll void DumpAllocationStats( );

	tm_dll bool EnumeratePhysicalDevices( VkInstance instance, tiny_list<VkPhysicalDevice>& storage );

	tm_dll bool EnumerateDeviceExtensionProperties( VkPhysicalDevice physical, tiny_list<VkExtensionProperties>& storage );

	tm_dll void GetPhysicalDeviceQueueFamilyProperties( VkPhysicalDevice physical, tiny_list<VkQueueFamilyProperties>& storage );

	tm_dll bool GetIsQueue( const VkPhysicalDeviceQueue& queue, tiny_init<VkQueueTypes> types );

	tm_dll bool GetPhysicalDeviceSurfaceFormats( VkPhysicalDevice physical, VkSurfaceKHR surface, tiny_list<VkSurfaceFormatKHR>& storage );

	tm_dll bool GetSwapchainImages( VkDevice logical, VkSwapchainKHR swapchain, tiny_list<VkImage>& storage );

	tm_dll bool GetPipelineCache( VkDevice logical, VkPipelineCache cache, tiny_list<tiny_ubyte>& storage );

	tm_dll bool CreateCommandBuffer( VkDevice logical, VkLogicalQueue& queue, VkLogicalCommandBuffer& command_buffer );

	tm_dll bool ResetCommandBuffer( VkLogicalCommandBuffer& command_buffer );

	tm_dll bool BeginCommandBuffer( VkLogicalCommandBuffer& command_buffer );

	tm_dll bool EndCommandBuffer( VkLogicalCommandBuffer& command_buffer );

	tm_dll void DestroyCommandBuffer( VkDevice logical, VkLogicalQueue& queue, VkLogicalCommandBuffer& command_buffer );

	tm_dll bool GetIsBuffer( const VkLogicalCommandBuffer& command_buffer, VkCommandBufferStates state );

	tm_dll bool GetPipelineCacheData( VkDevice logical, VkPipelineCache pipeline_cache, tiny_list<tiny_ubyte>& storage );

	tm_dll VkClearColorValue CastColor( const tiny_color& color );

	tm_dll c_string CastFormat( const VkFormat format );

	tm_dll c_string CastColorSpace( const VkColorSpaceKHR color_space );

	tm_dll c_string CastPresentMode( const VkPresentModeKHR present_mode );

	tm_dll c_string CastLayout( const VkImageLayout layout );

	tm_dll c_string CastAspect( const VkImageAspectFlags aspect );

	tm_dll c_string CastSamples( const VkSampleCountFlags samples );

	tm_dll c_string CastTiling( const VkImageTiling tiling );

};
