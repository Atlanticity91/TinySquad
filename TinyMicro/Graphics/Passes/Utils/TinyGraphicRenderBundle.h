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
 * @creation : 20/10/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include <TinyMicro/Graphics/Passes/Renderpass/TinyGraphicRenderpassManager.h>

#define TP_TYPE_RENDER 0
#define TP_STAGE_COLOR 0

tiny_enum( TinyRenderTargetTypes ) {

	TRT_TYPE_OUT = 0,
	TRT_TYPE_COLOR,
	TRT_TYPE_DEPTH,
	TRT_TYPE_EXTERNAL,

};

tiny_enum( TinyRenderTargetLoads ) {

	TRT_LOAD_LOAD = 0,
	TRT_LOAD_CLEAR,
	TRT_LOAD_NONE

};

tm_struct TinyGraphicRenderTargetDescriptor {

	std::string Name		   = "";
	TinyRenderTargetTypes Type = TRT_TYPE_COLOR;
	VkFormat Format			   = VK_FORMAT_R8G8B8A8_UNORM;
	VkSampleCountFlagBits MSAA = VK_SAMPLE_COUNT_1_BIT;
	TinyRenderTargetLoads Load = TRT_LOAD_CLEAR;
	VkClearValue Clear{ };

};

tiny_enum( TinyGraphicRenderpassAccesses ) {

	TGR_ACCESS_WRITE = TINY_LEFT_SHIFT( 1 ),
	TGR_ACCESS_READ  = TINY_LEFT_SHIFT( 2 )

};

tiny_enum( TinyGraphicRenderpassTypes ) {

	TGR_TYPE_RENDER  = VK_PIPELINE_BIND_POINT_GRAPHICS,
	TGR_TYPE_COMPUTE = VK_PIPELINE_BIND_POINT_COMPUTE

};

tiny_enum( TinyGraphicRenderpassTargetStages ) {
	
	TGR_STAGE_BEGIN			 = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
	TGR_STAGE_VERTEX		 = VK_PIPELINE_STAGE_VERTEX_SHADER_BIT,
	TGR_STAGE_FRAGMENT		 = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT,
	TGR_STAGE_GEOMETRY		 = VK_PIPELINE_STAGE_GEOMETRY_SHADER_BIT,
	TGR_STAGE_COMPUTE		 = VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT,
	TGR_STAGE_FRAGMENT_EARLY = VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT,
	TGR_STAGE_FRAGMENT_LATE  = VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT,
	TGR_STAGE_END			 = VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT

};

tm_struct TinyGraphicRenderpassTarget {

	std::string Name = "";
	TinyGraphicRenderpassAccesses Access = TGR_ACCESS_WRITE;

};

tm_struct TinyGraphicRenderpassDescriptor {

	TinyGraphicRenderpassTypes Type			= TGR_TYPE_RENDER;
	TinyGraphicRenderpassTargetStages Stage = TGR_STAGE_BEGIN;
	tiny_list<TinyGraphicRenderpassTarget> Targets{ };

};

tm_struct TinyGraphicRenderBundle {

	tiny_list<TinyGraphicRenderTargetDescriptor> Targets{ };
	tiny_list<TinyGraphicRenderpassDescriptor> Passes{ };

};

tm_struct TinyGraphicRenderPassReferences {

	VkPipelineBindPoint Bindpoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
	tiny_uint InputCount		  = 0;
	tiny_uint InputOffset		  = 0;
	tiny_uint ColorCount		  = 0;
	tiny_uint ColorOffset		  = 0;
	tiny_uint DepthOffset		  = TINY_UINT_MAX;

};

tm_struct TinyGraphicRenderReferences {

	tiny_list<VkAttachmentReference> References{ };
	tiny_list<TinyGraphicRenderPassReferences> Passes{ };

};
