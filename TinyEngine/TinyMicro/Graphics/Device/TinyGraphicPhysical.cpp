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
TinyGraphicPhysical::TinyGraphicPhysical( )
	: m_handle{ VK_NULL_HANDLE },
	m_features{ VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2 },
	m_properties{ },
	m_queues{ },
	m_indexing{ VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DESCRIPTOR_INDEXING_FEATURES_EXT }
{ }

bool TinyGraphicPhysical::Initialize(
	const TinyGraphicInstance& instance,
	const TinyGraphicSurface& surface 
) {
	auto state = GetPhysicalDevice( instance );
	
	if ( state ) {
		CreateIndexing( );

		GetQueuesFamilies( surface );
	}

	return state;
}

void TinyGraphicPhysical::Terminate( ) { }

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE ===
////////////////////////////////////////////////////////////////////////////////////////////
void TinyGraphicPhysical::CreateIndexing( ) {
	m_indexing.pNext											  = VK_NULL_HANDLE;
	m_indexing.shaderUniformBufferArrayNonUniformIndexing		  = VK_TRUE;
	m_indexing.shaderSampledImageArrayNonUniformIndexing		  = VK_TRUE;
	m_indexing.shaderStorageBufferArrayNonUniformIndexing		  = VK_TRUE;
	m_indexing.shaderStorageImageArrayNonUniformIndexing		  = VK_TRUE;
	m_indexing.descriptorBindingUniformBufferUpdateAfterBind	  = VK_TRUE;
	m_indexing.descriptorBindingSampledImageUpdateAfterBind		  = VK_TRUE;
	m_indexing.descriptorBindingStorageImageUpdateAfterBind		  = VK_TRUE;
	m_indexing.descriptorBindingStorageBufferUpdateAfterBind	  = VK_TRUE;
	m_indexing.descriptorBindingUniformTexelBufferUpdateAfterBind = VK_TRUE;
	m_indexing.descriptorBindingStorageTexelBufferUpdateAfterBind = VK_TRUE;
	m_indexing.descriptorBindingUpdateUnusedWhilePending		  = VK_TRUE;
	m_indexing.descriptorBindingPartiallyBound					  = VK_TRUE;
	m_indexing.descriptorBindingVariableDescriptorCount			  = VK_TRUE;
	m_indexing.runtimeDescriptorArray							  = VK_TRUE;

	m_features.pNext = tiny_rvalue( m_indexing );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyGraphicPhysical::GetIsValid( ) const {
	return  m_properties.deviceType   == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU &&
			m_features.features.geometryShader == VK_TRUE					  &&
			GetHasExtensions( )												  && 
			GetHasDepth( );
}

VkPhysicalDevice TinyGraphicPhysical::Get( ) const { return m_handle; }


tiny_string TinyGraphicPhysical::GetVendor( ) const {
	auto vendor = tiny_string{ "Unspecified" };

	switch ( m_properties.vendorID ) {
		case 0x1002 : vendor = "AMD"; break;
		case 0x1010 : vendor = "ImgTec"; break;
		case 0x10DE : vendor = "NVIDIA"; break;
		case 0x13B5 : vendor = "ARM"; break;
		case 0x5143 : vendor = "Qualcomm"; break;
		case 0x8086 : vendor = "INTEL"; break;

		default: break;
	}
		 
	return vendor;
}

const VkPhysicalDeviceFeatures2* TinyGraphicPhysical::GetFeatures( ) const { 
	return tiny_rvalue( m_features ); 
}

const VkPhysicalDeviceFeatures& TinyGraphicPhysical::GetFeatureCore( ) const {
	return m_features.features;
}

const VkPhysicalDeviceDescriptorIndexingFeatures& TinyGraphicPhysical::GetFeatureIndexing( 
) const {
	return m_indexing;
}

const VkPhysicalDeviceProperties& TinyGraphicPhysical::GetProperties( ) const {
	return m_properties; 
}

const VkPhysicalDeviceLimits& TinyGraphicPhysical::GetLimits( ) const {
	return m_properties.limits;
}

const TinyGraphicPhysical::VkPhysicalDeviceQueues& TinyGraphicPhysical::GetQueues( ) const {
	return m_queues; 
}

VkSampleCountFlagBits TinyGraphicPhysical::GetSamplesLimit( ) const {
	return tiny_cast( m_properties.limits.framebufferColorSampleCounts & m_properties.limits.framebufferDepthSampleCounts, VkSampleCountFlagBits );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE GET ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyGraphicPhysical::GetHasExtensions( ) const {
	auto extension_size  = tiny_size_array( vk::EXTENSIONS );
	auto extensions		 = tiny_list<VkExtensionProperties>{ };

	vk::EnumerateDeviceExtensionProperties( m_handle, extensions );

	for ( auto extension : vk::EXTENSIONS ) {
		for ( auto& properties : extensions ) {
			if ( strcmp( extension, properties.extensionName ) == 0 )
				extension_size -= 1;
		}
	}

	return extension_size == 0;
}

bool TinyGraphicPhysical::GetHasDepth( ) const {
	auto state = false;

	for ( auto format : vk::DEPTH_FORMATS ) {
		auto prop_info = VkFormatProperties{ };

		vkGetPhysicalDeviceFormatProperties( m_handle, format, tiny_rvalue( prop_info ) );

		state =
			( ( prop_info.linearTilingFeatures  & vk::DEPTH_FLAGS ) == vk::DEPTH_FLAGS ) ||
			( ( prop_info.optimalTilingFeatures & vk::DEPTH_FLAGS ) == vk::DEPTH_FLAGS );

		if ( state ) break;
	}

	return state;
}

bool TinyGraphicPhysical::GetPhysicalDevice( const TinyGraphicInstance& instance ) {
	auto device_list = tiny_list<VkPhysicalDevice>{ };
	auto state		 = false;

	vk::EnumeratePhysicalDevices( instance, device_list );

	for ( auto device : device_list ) {
		m_handle = device;

		vkGetPhysicalDeviceFeatures2( m_handle, tiny_rvalue( m_features ) );
		vkGetPhysicalDeviceProperties( m_handle, tiny_rvalue( m_properties ) );

		state = GetIsValid( );

		if ( state )
			break;
	}

	return state;
}

void TinyGraphicPhysical::GetQueuesFamilies( const TinyGraphicSurface& surface ) {
	auto families	 = tiny_list<VkQueueFamilyProperties>{ };
	auto famility_id = tiny_cast( 0, tiny_uint );
	auto max_count   = tiny_size_array( vk::QUEUES_PRIORITIES );

	vk::GetPhysicalDeviceQueueFamilyProperties( m_handle, families );

	while ( famility_id < families.size( ) ) {
		auto present_support = VK_FALSE;
		auto properties		 = families[ famility_id ];
		
		vk::Check( vkGetPhysicalDeviceSurfaceSupportKHR( m_handle, famility_id, surface, tiny_rvalue( present_support ) ) );

		auto count = properties.queueCount < max_count ? properties.queueCount : max_count;

		if ( present_support && !( properties.queueFlags & VK_QUEUE_GRAPHICS_BIT ) )
			m_queues.create_back( VK_QUEUE_TYPE_PRESENT, famility_id, count );

		if ( properties.queueFlags & VK_QUEUE_GRAPHICS_BIT )
			m_queues.create_back( VK_QUEUE_TYPE_GRAPHIC, famility_id, count );

		if (
			properties.queueFlags & VK_QUEUE_TRANSFER_BIT			   &&
			!present_support										   &&
			!( properties.queueFlags & VK_QUEUE_VIDEO_DECODE_BIT_KHR ) &&
			!( properties.queueFlags & VK_QUEUE_GRAPHICS_BIT )
		)
			m_queues.create_back( VK_QUEUE_TYPE_TRANSFER, famility_id, count );

		if (
			properties.queueFlags & VK_QUEUE_VIDEO_DECODE_BIT_KHR &&
			!present_support &&
			!( properties.queueFlags & VK_QUEUE_GRAPHICS_BIT )
		)
			m_queues.create_back( VK_QUEUE_TYPE_DECODE, famility_id, count );

		famility_id += 1;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	OPERATOR ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyGraphicPhysical::operator VkPhysicalDevice ( ) const { return Get( ); }
