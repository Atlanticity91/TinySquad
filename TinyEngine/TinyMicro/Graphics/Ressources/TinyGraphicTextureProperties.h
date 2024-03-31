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

#pragma once

#include "TinyGraphicSamplerSpecification.h"

tiny_enum( TinyGraphicTextureTypes ) {

	TGT_TYPE_TEXTURE_2D = 0,
	TGT_TYPE_TEXTURE_3D,
	TGT_TYPE_TEXTURE_CUBEMAP

};

tiny_enum( TinyGraphicTextureUsages ) {

	TGT_USAGE_TEXTURE = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT,
	
	TGT_USAGE_TARGET  = VK_IMAGE_USAGE_TRANSFER_SRC_BIT | VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT | 
					    VK_IMAGE_USAGE_SAMPLED_BIT	    | VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,

	TGT_USAGE_DEPTH  = VK_IMAGE_USAGE_TRANSFER_SRC_BIT | VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT | 
					   VK_IMAGE_USAGE_SAMPLED_BIT	   | VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT

};

tm_struct TinyGraphicTextureProperties {

	VkImage Image;
	VkImageView View;
	TinyGraphicTextureTypes Type;
	VkFormat Format;
	VkImageLayout Layout;
	tiny_uint Width;
	tiny_uint Height;
	tiny_uint Depth;
	VkImageAspectFlags Aspect;
	tiny_uint Levels;
	VkSampleCountFlagBits Samples;
	VkImageTiling Tiling;
	TinyGraphicTextureUsages Usage;
	TinyGraphicSamplerSpecification Sampler;

	TinyGraphicTextureProperties( );

};
