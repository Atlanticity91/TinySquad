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

#include <TinyMicro/Graphics/Swapchain/TinyGraphicSwapchainManager.h>

tm_struct TinyGraphicWorkContext {

	tiny_uint WorkID;
	tiny_uint WorkImage;
	tiny_uint WorkPass;
	tiny_hash WorkRender;
	VkQueueTypes Type;
	TinyGraphicLogical* Logical;
	VkLogicalQueue* Queue;
	TinyGraphicSwapchainSync* Sync;

	TinyGraphicWorkContext( TinyGraphicLogical* logical );

	void Acquire( TinyGraphicQueueManager& queues, VkQueueTypes type );

	void Submit( TinyGraphicQueueManager& queues, tiny_init<VkPipelineStageFlags> stages );

	void Flush( TinyGraphicQueueManager& queues, tiny_init<VkPipelineStageFlags> stages );

	void Release( TinyGraphicQueueManager& queues );

};
