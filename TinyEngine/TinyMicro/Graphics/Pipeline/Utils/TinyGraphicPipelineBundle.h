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
 * @creation : 22/10/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include <TinyMicro/Graphics/Pipeline/Descriptors/TinyGraphicDescriptorManager.h>

#define VK_COLOR_COMP_R VK_COLOR_COMPONENT_R_BIT
#define VK_COLOR_COMP_RG VK_COLOR_COMP_R | VK_COLOR_COMPONENT_G_BIT
#define VK_COLOR_COMP_RGB VK_COLOR_COMP_RG | VK_COLOR_COMPONENT_B_BIT 
#define VK_COLOR_COMP_RGBA VK_COLOR_COMP_RGB | VK_COLOR_COMPONENT_A_BIT

tiny_enum( TinyGraphicPipelineTypes ) {

	TGP_TYPE_NONE,
	TGP_TYPE_2D,
	TGP_TYPE_3D,
	TGP_TYPE_COMPUTE

};

tiny_enum( TinyGraphicBindTypes ) {

	TGBP_TYPE_UNIFORM  = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
	TGBP_TYPE_SAMPLER  = VK_DESCRIPTOR_TYPE_SAMPLER,
	TGBP_TYPE_SAMPLED  = VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE,
	TGBP_TYPE_COMBINED = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
	TGBP_TYPE_STORAGE  = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
	TGBP_TYPE_INPUT	   = VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT

};

tiny_enum( TinyGraphicShaderStages ) {

	TGS_STAGE_VERTEX	   = VK_SHADER_STAGE_VERTEX_BIT,
	TGS_STAGE_FRAGMENT	   = VK_SHADER_STAGE_FRAGMENT_BIT,
	TGS_STAGE_GEOMETRY	   = VK_SHADER_STAGE_GEOMETRY_BIT,
	TGS_STAGE_COMPUTE	   = VK_SHADER_STAGE_COMPUTE_BIT,
	TGS_STAGE_TESS_EVAL	   = VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT,
	TGS_STAGE_TESS_CONTROL = VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT

};

tm_struct TinyGraphicPipelineBinding {

	tiny_uint Binding = 0;
	tiny_uint Stride  = 0;
	bool IsVertex	  = true;

};

tiny_enum( TinyPipelineAttributeTypes ) { 

	TPA_TYPE_INT   = VK_FORMAT_R32_SINT,
	TPA_TYPE_UINT  = VK_FORMAT_R32_UINT,
	TPA_TYPE_FLOAT = VK_FORMAT_R32_SFLOAT,

	TPA_TYPE_VEC2  = VK_FORMAT_R32G32_SFLOAT,
	TPA_TYPE_VEC3  = VK_FORMAT_R32G32B32_SFLOAT,
	TPA_TYPE_VEC4  = VK_FORMAT_R32G32B32A32_SFLOAT

};

tm_struct TinyGraphicPipelineAttribute {

	tiny_uint Location				= 0;
	tiny_uint Binding				= 0;
	TinyPipelineAttributeTypes Type = TPA_TYPE_VEC4;
	tiny_uint Offset				= 0;

};

tm_struct TinyGraphicPipelineSetBind {

	tiny_uint Binding			  = 0;
	TinyGraphicBindTypes Type	  = TGBP_TYPE_UNIFORM;
	tiny_uint Count				  = 0;
	TinyGraphicShaderStages Stage = TGS_STAGE_VERTEX;

};

tm_struct TinyGraphicPipelineBundle {

	TinyGraphicRenderpassTypes PassType;
	tiny_uint Subpass;
	VkRenderPass Pass;
	tiny_list<VkPipelineShaderStageCreateInfo> Shaders;
	tiny_list<VkVertexInputBindingDescription> InputBinding;
	tiny_list<VkVertexInputAttributeDescription> InputAttributes;
	VkPrimitiveTopology Topology;
	tiny_uint Tessellation;
	bool DepthEnable;
	bool StencilEnable;
	VkCompareOp DepthOperation;
	VkStencilOpState DepthStencilFront;
	VkStencilOpState DepthStencilBack;
	tiny_list<VkPipelineColorBlendAttachmentState> ColorBlends;
	tiny_list<VkDynamicState> Dynamics;
	tiny_uint DescriptorCount;
	TinyDescriptorLayout Descriptors;
	tiny_list<VkPushConstantRange> Constants;

	TinyGraphicPipelineBundle( );

};
