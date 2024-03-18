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

#include "TinyGraphicBufferStaging.h"

tiny_enum( TinyGraphicWrapModes ) {

	TGW_MODE_REPEAT			   = VK_SAMPLER_ADDRESS_MODE_REPEAT,
	TGW_MODE_MIRROR_REPEAT	   = VK_SAMPLER_ADDRESS_MODE_MIRRORED_REPEAT,
	TGW_MODE_CLAMP_EDGE		   = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE,
	TGW_MODE_CLAMP_BORDER	   = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER,
	TGW_MODE_CLAMP_MIRROR_EDGE = VK_SAMPLER_ADDRESS_MODE_MIRROR_CLAMP_TO_EDGE

};

tm_struct TinyGraphicSamplerProperties {

	VkFilter MagFilter			   = VK_FILTER_NEAREST;
	VkFilter MinFilter			   = VK_FILTER_NEAREST;
	VkSamplerMipmapMode MipmapMode = VK_SAMPLER_MIPMAP_MODE_NEAREST;
	TinyGraphicWrapModes WrapU	   = TGW_MODE_MIRROR_REPEAT;
	TinyGraphicWrapModes WrapV	   = TGW_MODE_MIRROR_REPEAT;
	TinyGraphicWrapModes WrapW	   = TGW_MODE_MIRROR_REPEAT;
	float MipLodBias			   = .0f;
	float MaxAnisotropy			   = 1.f;
	VkCompareOp CompareOp		   = VK_COMPARE_OP_NEVER;
	float MinLod				   = .0f;
	float MaxLod				   = .25f;
	VkBorderColor BorderColor	   = VK_BORDER_COLOR_INT_TRANSPARENT_BLACK;
	bool UseAnisotropy			   = false;
	bool UseCompare				   = false;
	bool Unnormalized			   = false;

};
