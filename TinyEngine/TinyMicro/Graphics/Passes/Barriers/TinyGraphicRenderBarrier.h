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

#include <TinyMicro/Graphics/Passes/Frames/TinyGraphicRenderFrameManager.h>

tm_struct TinyGraphicRenderBarrierImage {

	VkAccessFlags AccessSource;
	VkAccessFlags AccessTarget;
	VkImageLayout Source;
	VkImageLayout Target;
	VkImageAspectFlags Aspect;
	tiny_list<VkImage> Images;

};

tm_struct TinyGraphicRenderBarrierBundle { 

	VkPipelineStageFlags Source = VK_PIPELINE_STAGE_NONE;
	VkPipelineStageFlags Target = VK_PIPELINE_STAGE_NONE;
	tiny_list<TinyGraphicRenderBarrierImage> Images{ };

};

tm_struct TinyGraphicRenderBarrierData {

	VkPipelineStageFlags Source = VK_PIPELINE_STAGE_NONE;
	VkPipelineStageFlags Target = VK_PIPELINE_STAGE_NONE;
	tiny_list<tiny_list<VkImageMemoryBarrier>> Barriers{ };

};

tm_class TinyGraphicRenderBarrier final {

private:
	tiny_list<TinyGraphicRenderBarrierData> m_barriers;

public:
	TinyGraphicRenderBarrier( );

	~TinyGraphicRenderBarrier( ) = default;

	void Create( const tiny_list<TinyGraphicRenderBarrierBundle>& bundles );

	void Transit( TinyGraphicWorkContext& work_context );

private:
	tiny_list<VkImageMemoryBarrier> CreateBarriers( 
		tiny_uint image_id, 
		const tiny_list<TinyGraphicRenderBarrierImage>& images 
	);

};
