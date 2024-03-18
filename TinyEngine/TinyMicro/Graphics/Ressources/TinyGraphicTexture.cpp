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
	: _image{ VK_NULL_HANDLE },
	_descriptor{ },
	_properties{ },
	_memory{ }
{ }

bool TinyGraphicTexture::Create( 
	TinyGraphicContext& context,
	const TinyGraphicTextureProperties& properties
) {
	_descriptor.imageLayout = properties.Layout;
	_properties				= properties;
	
	auto state = false;

	if ( GetIsCopy( ) )
		state = CreateImageCopy( );
	else {
		state = CreateImage( context.Logical, context.Queues )		&&
				context.Memory.Allocate( context, _memory, _image ) &&
				CreateView( context.Logical );
	}

	if ( state )
		state = CreateImageSampler( context.Logical );

	return state;
}

bool TinyGraphicTexture::Create( 
	TinyGraphicContext& context,
	const TinyGraphicTextureBuilder& builder,
	const TinyGraphicBufferStaging& stagging
) {
	return  Create( context, builder.Properties ) &&
			Fill( context, stagging );
}

bool TinyGraphicTexture::Fill( 
	TinyGraphicContext& context, 
	const TinyGraphicBufferStaging& staging
) {
	auto final_layout = _properties.Layout;
	auto burner		  = TinyGraphicBurner{ context, VK_QUEUE_TYPE_GRAPHIC };
	
	_properties.Layout = VK_IMAGE_LAYOUT_UNDEFINED;

	burner.Transit( tiny_self, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL );
	burner.Upload( staging, tiny_self );
	burner.Transit( tiny_self, final_layout );

	auto state = burner.Execute( );

	if ( state )
		GenerateMipmaps( context.Logical );

	return state;
}

void TinyGraphicTexture::Terminate( TinyGraphicContext& context ) {
	if ( vk::GetIsValid( _descriptor.sampler ) ) {
		vkDestroySampler( context.Logical, _descriptor.sampler, vk::GetAllocator( ) );

		_descriptor.sampler = VK_NULL_HANDLE;
	}

	if ( !GetIsCopy( ) ) {
		if ( vk::GetIsValid( _descriptor.imageView ) ) {
			vkDestroyImageView( context.Logical, _descriptor.imageView, vk::GetAllocator( ) );

			_descriptor.imageView = VK_NULL_HANDLE;
		}

		if ( vk::GetIsValid( _image ) ) {
			vkDestroyImage( context.Logical, _image, vk::GetAllocator( ) );

			_image = VK_NULL_HANDLE;
		}

		context.Memory.DeAllocate( context, _memory );
	}
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyGraphicTexture::CreateImageCopy( ) {
	_image				  = _properties.Image;
	_descriptor.imageView = _properties.View;

	return vk::GetIsValid( _image ) && vk::GetIsValid( _descriptor.imageView );
}

bool TinyGraphicTexture::CreateImage( 
	const TinyGraphicLogical& logical, 
	const TinyGraphicQueueManager& queues
) {
	auto image_info		  = VkImageCreateInfo{ VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO };
	auto ressource_queues = queues.GetRessourceQueues( );
	auto is_cube		  = _properties.Type == TGT_TYPE_TEXTURE_CUBEMAP;

	image_info.pNext				 = VK_NULL_HANDLE;
	image_info.flags				 = is_cube ? VK_IMAGE_CREATE_CUBE_COMPATIBLE_BIT : VK_NULL_FLAGS;
	image_info.imageType			 = GetImageType( );
	image_info.format				 = _properties.Format;
	image_info.extent.width			 = _properties.Width;
	image_info.extent.height		 = _properties.Height;
	image_info.extent.depth			 = _properties.Depth;
	image_info.mipLevels			 = _properties.Levels;
	image_info.arrayLayers			 = is_cube ? 6 : 1;
	image_info.samples				 = _properties.Samples;
	image_info.tiling				 = _properties.Tiling;
	image_info.usage				 = tiny_cast( _properties.Usage, VkImageUsageFlags );
	image_info.sharingMode			 = tiny_cast( ressource_queues.Sharing, VkSharingMode );
	image_info.queueFamilyIndexCount = ressource_queues.Queues.size( );
	image_info.pQueueFamilyIndices   = ressource_queues.Queues.data( );
	image_info.initialLayout		 = VK_IMAGE_LAYOUT_UNDEFINED;

	return vk::Check( vkCreateImage( logical, &image_info, vk::GetAllocator( ), &_image ) );
}

bool TinyGraphicTexture::CreateView( const TinyGraphicLogical& logical ) {
	auto view_info = VkImageViewCreateInfo{ VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO };

	view_info.pNext							  = VK_NULL_HANDLE;
	view_info.flags							  = VK_NULL_FLAGS;
	view_info.image							  = _image;
	view_info.viewType						  = GetViewType( );
	view_info.format						  = _properties.Format;
	view_info.components.r					  = VK_COMPONENT_SWIZZLE_R;
	view_info.components.g					  = VK_COMPONENT_SWIZZLE_G;
	view_info.components.b					  = VK_COMPONENT_SWIZZLE_B;
	view_info.components.a					  = VK_COMPONENT_SWIZZLE_A;
	view_info.subresourceRange.aspectMask	  = _properties.Aspect;
	view_info.subresourceRange.baseMipLevel   = 0;
	view_info.subresourceRange.levelCount	  = _properties.Levels;
	view_info.subresourceRange.baseArrayLayer = 0;
	view_info.subresourceRange.layerCount	  = _properties.Type == TGT_TYPE_TEXTURE_CUBEMAP ? 6 : 1;

	return vk::Check( vkCreateImageView( logical, &view_info, vk::GetAllocator( ), &_descriptor.imageView ) );
}

bool TinyGraphicTexture::CreateImageSampler( const TinyGraphicLogical& logical ) {
	auto sampler_info = VkSamplerCreateInfo{ VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO };
	auto& properties  = _properties.Sampler;

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

	return vk::Check( vkCreateSampler( logical, &sampler_info, vk::GetAllocator( ), &_descriptor.sampler ) );
}

void TinyGraphicTexture::GenerateMipmaps( const TinyGraphicLogical& logical ) {
}

void TinyGraphicTexture::SetLayout( VkImageLayout layout ) { _properties.Layout = layout; }

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyGraphicTexture::GetIsCopy( ) const { 
	return vk::GetIsValid( _properties.Image ) && vk::GetIsValid( _properties.View );
}

const VkImage TinyGraphicTexture::GetImage( ) const { return _image; }

const VkImageView TinyGraphicTexture::GetView( ) const { return _descriptor.imageView; }

const VkSampler TinyGraphicTexture::GetSampler( ) const { return _descriptor.sampler; }

VkDescriptorType TinyGraphicTexture::GetDescriptorType( ) const {
	auto type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
	
	if ( !vk::GetIsValid( _descriptor.sampler ) )
		type = VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE;

	return type;
}

const VkDescriptorImageInfo* TinyGraphicTexture::GetDescriptor( ) const {
	return &_descriptor;
}

const TinyGraphicTextureProperties& TinyGraphicTexture::GetProperties( ) const {
	return _properties;
}

VkImageLayout TinyGraphicTexture::GetLayout( ) const { return _properties.Layout; }

TinyGraphicTextureProperties& TinyGraphicTexture::GetEditProperties( ) {
	return _properties;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE GET ===
////////////////////////////////////////////////////////////////////////////////////////////
VkImageType TinyGraphicTexture::GetImageType( ) const {
	auto type = VK_IMAGE_TYPE_2D;

	switch ( _properties.Type ) {
		case TGT_TYPE_TEXTURE_2D	  : 
		case TGT_TYPE_TEXTURE_CUBEMAP : type = VK_IMAGE_TYPE_2D; break;
		case TGT_TYPE_TEXTURE_3D	  : type = VK_IMAGE_TYPE_3D; break;

		default : break;
	}

	return type;
}

VkImageViewType TinyGraphicTexture::GetViewType( ) const {
	auto type = VK_IMAGE_VIEW_TYPE_2D;

	switch ( _properties.Type ) {
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
