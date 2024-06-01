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
 * @creation : 18/10/2023
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
TinyGraphicTexture::TinyGraphicTexture( )
	: m_image{ VK_NULL_HANDLE },
	m_descriptor{ },
	m_properties{ },
	m_memory{ }
{ }

bool TinyGraphicTexture::Create( 
	TinyGraphicWrapper& graphic,
	const TinyGraphicTextureProperties& properties
) {
	m_descriptor.imageLayout = properties.Layout;
	m_properties			 = properties;
	
	auto state = false;

	if ( GetIsCopy( ) )
		state = CreateImageCopy( );
	else {
		state = CreateImage( graphic.Logical, graphic.Queues )		&&
				graphic.Memory.Allocate( graphic, m_memory, m_image ) &&
				CreateView( graphic.Logical );
	}

	if ( state )
		state = CreateImageSampler( graphic.Logical );

	return state;
}

bool TinyGraphicTexture::Create( 
	TinyGraphicWrapper& graphic,
	const TinyGraphicTextureSpecification& specification,
	const TinyGraphicBufferStaging& stagging
) {
	return  Create( graphic, specification.Properties ) &&
			Fill( graphic, stagging );
}

bool TinyGraphicTexture::Fill( 
	TinyGraphicWrapper& graphic,
	const TinyGraphicBufferStaging& staging
) {
	auto final_layout = m_properties.Layout;
	auto burner		  = TinyGraphicBurner{ graphic, VK_QUEUE_TYPE_GRAPHIC };
	
	m_properties.Layout = VK_IMAGE_LAYOUT_UNDEFINED;

	burner.Transit( tiny_self, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL );
	burner.Upload( staging, tiny_self );
	burner.Transit( tiny_self, final_layout );

	auto state = burner.Execute( );

	if ( state ) {
		GenerateMipmaps( graphic.Logical );

		m_properties.Layout = final_layout;
	}

	return state;
}

void TinyGraphicTexture::Terminate( TinyGraphicWrapper& graphic ) {
	if ( vk::GetIsValid( m_descriptor.sampler ) ) {
		vkDestroySampler( graphic.Logical, m_descriptor.sampler, vk::GetAllocator( ) );

		m_descriptor.sampler = VK_NULL_HANDLE;
	}

	if ( !GetIsCopy( ) ) {
		if ( vk::GetIsValid( m_descriptor.imageView ) ) {
			vkDestroyImageView( graphic.Logical, m_descriptor.imageView, vk::GetAllocator( ) );

			m_descriptor.imageView = VK_NULL_HANDLE;
		}

		if ( vk::GetIsValid( m_image ) ) {
			vkDestroyImage( graphic.Logical, m_image, vk::GetAllocator( ) );

			m_image = VK_NULL_HANDLE;
		}

		graphic.Memory.DeAllocate( graphic, m_memory );
	}
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyGraphicTexture::CreateImageCopy( ) {
	m_image				   = m_properties.Image;
	m_descriptor.imageView = m_properties.View;

	return vk::GetIsValid( m_image ) && vk::GetIsValid( m_descriptor.imageView );
}

bool TinyGraphicTexture::CreateImage( 
	const TinyGraphicLogical& logical, 
	const TinyGraphicQueueManager& queues
) {
	auto image_info		  = VkImageCreateInfo{ VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO };
	auto ressource_queues = queues.GetRessourceQueues( );
	auto is_cube		  = m_properties.Type == TGT_TYPE_TEXTURE_CUBEMAP;

	image_info.pNext				 = VK_NULL_HANDLE;
	image_info.flags				 = is_cube ? VK_IMAGE_CREATE_CUBE_COMPATIBLE_BIT : VK_NULL_FLAGS;
	image_info.imageType			 = GetImageType( );
	image_info.format				 = m_properties.Format;
	image_info.extent.width			 = m_properties.Width;
	image_info.extent.height		 = m_properties.Height;
	image_info.extent.depth			 = m_properties.Depth;
	image_info.mipLevels			 = m_properties.Levels;
	image_info.arrayLayers			 = is_cube ? 6 : 1;
	image_info.samples				 = m_properties.Samples;
	image_info.tiling				 = m_properties.Tiling;
	image_info.usage				 = tiny_cast( m_properties.Usage, VkImageUsageFlags );
	image_info.sharingMode			 = tiny_cast( ressource_queues.Sharing, VkSharingMode );
	image_info.queueFamilyIndexCount = ressource_queues.Queues.size( );
	image_info.pQueueFamilyIndices   = ressource_queues.Queues.data( );
	image_info.initialLayout		 = VK_IMAGE_LAYOUT_UNDEFINED;

	return vk::Check( vkCreateImage( logical, tiny_rvalue( image_info ), vk::GetAllocator( ), tiny_rvalue( m_image ) ) );
}

bool TinyGraphicTexture::CreateView( const TinyGraphicLogical& logical ) {
	auto view_info = VkImageViewCreateInfo{ VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO };

	view_info.pNext							  = VK_NULL_HANDLE;
	view_info.flags							  = VK_NULL_FLAGS;
	view_info.image							  = m_image;
	view_info.viewType						  = GetViewType( );
	view_info.format						  = m_properties.Format;
	view_info.components.r					  = VK_COMPONENT_SWIZZLE_R;
	view_info.components.g					  = VK_COMPONENT_SWIZZLE_G;
	view_info.components.b					  = VK_COMPONENT_SWIZZLE_B;
	view_info.components.a					  = VK_COMPONENT_SWIZZLE_A;
	view_info.subresourceRange.aspectMask	  = m_properties.Aspect;
	view_info.subresourceRange.baseMipLevel   = 0;
	view_info.subresourceRange.levelCount	  = m_properties.Levels;
	view_info.subresourceRange.baseArrayLayer = 0;
	view_info.subresourceRange.layerCount	  = m_properties.Type == TGT_TYPE_TEXTURE_CUBEMAP ? 6 : 1;

	return vk::Check( vkCreateImageView( logical, tiny_rvalue( view_info ), vk::GetAllocator( ), tiny_rvalue( m_descriptor.imageView ) ) );
}

bool TinyGraphicTexture::CreateImageSampler( const TinyGraphicLogical& logical ) {
	auto sampler_info = VkSamplerCreateInfo{ VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO };
	auto& properties  = m_properties.Sampler;

	sampler_info.pNext					 = VK_NULL_HANDLE;
	sampler_info.flags					 = VK_NULL_FLAGS;
	sampler_info.magFilter				 = properties.MagFilter;
	sampler_info.minFilter				 = properties.MinFilter;
	sampler_info.mipmapMode				 = properties.MipmapMode;
	sampler_info.addressModeU			 = tiny_cast( properties.WrapU, VkSamplerAddressMode );
	sampler_info.addressModeV			 = tiny_cast( properties.WrapV, VkSamplerAddressMode );
	sampler_info.addressModeW			 = tiny_cast( properties.WrapW, VkSamplerAddressMode );
	sampler_info.mipLodBias				 = properties.MipLodBias;
	sampler_info.anisotropyEnable		 = properties.UseAnisotropy ? VK_TRUE : VK_FALSE;
	sampler_info.maxAnisotropy			 = properties.MaxAnisotropy;
	sampler_info.compareEnable			 = properties.UseCompare ? VK_TRUE : VK_FALSE;
	sampler_info.compareOp				 = properties.CompareOp;
	sampler_info.minLod					 = properties.MinLod;
	sampler_info.maxLod					 = properties.MaxLod;
	sampler_info.borderColor			 = properties.BorderColor;
	sampler_info.unnormalizedCoordinates = properties.Unnormalized ? VK_TRUE : VK_FALSE;

	return vk::Check( vkCreateSampler( logical, tiny_rvalue( sampler_info ), vk::GetAllocator( ), tiny_rvalue( m_descriptor.sampler ) ) );
}

void TinyGraphicTexture::GenerateMipmaps( const TinyGraphicLogical& logical ) {
}

void TinyGraphicTexture::SetLayout( VkImageLayout layout ) { m_properties.Layout = layout; }

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyGraphicTexture::GetIsCopy( ) const { 
	return vk::GetIsValid( m_properties.Image ) && vk::GetIsValid( m_properties.View );
}

const VkImage TinyGraphicTexture::GetImage( ) const { return m_image; }

const VkImageView TinyGraphicTexture::GetView( ) const { return m_descriptor.imageView; }

const VkSampler TinyGraphicTexture::GetSampler( ) const { return m_descriptor.sampler; }

VkDescriptorType TinyGraphicTexture::GetDescriptorType( ) const {
	auto type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
	
	if ( !vk::GetIsValid( m_descriptor.sampler ) )
		type = VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE;

	return type;
}

const VkDescriptorImageInfo* TinyGraphicTexture::GetDescriptor( ) const {
	return tiny_rvalue( m_descriptor );
}

const TinyGraphicTextureProperties& TinyGraphicTexture::GetProperties( ) const {
	return m_properties;
}

VkImageLayout TinyGraphicTexture::GetLayout( ) const { return m_properties.Layout; }

TinyGraphicTextureProperties& TinyGraphicTexture::GetEditProperties( ) {
	return m_properties;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE GET ===
////////////////////////////////////////////////////////////////////////////////////////////
VkImageType TinyGraphicTexture::GetImageType( ) const {
	auto type = VK_IMAGE_TYPE_2D;

	switch ( m_properties.Type ) {
		case TGT_TYPE_TEXTURE_2D	  : 
		case TGT_TYPE_TEXTURE_CUBEMAP : type = VK_IMAGE_TYPE_2D; break;
		case TGT_TYPE_TEXTURE_3D	  : type = VK_IMAGE_TYPE_3D; break;

		default : break;
	}

	return type;
}

VkImageViewType TinyGraphicTexture::GetViewType( ) const {
	auto type = VK_IMAGE_VIEW_TYPE_2D;

	switch ( m_properties.Type ) {
		case TGT_TYPE_TEXTURE_2D	  : type = VK_IMAGE_VIEW_TYPE_2D;   break;
		case TGT_TYPE_TEXTURE_3D	  : type = VK_IMAGE_VIEW_TYPE_3D;   break;
		case TGT_TYPE_TEXTURE_CUBEMAP : type = VK_IMAGE_VIEW_TYPE_CUBE; break;

		default: break;
	}

	return type;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	OPERATOR ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyGraphicTexture::operator const VkImage ( ) const { return GetImage( ); }
