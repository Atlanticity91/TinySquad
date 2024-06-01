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

#pragma once

#include "TinyVulkan.h"

tm_struct TinyGraphicWrapper {

	class TinyGraphicBoundaries& Boundaries;
	class TinyGraphicInstance& Instance;
	class TinyGraphicSurface& Surface;
	class TinyGraphicPhysical& Physical;
	class TinyGraphicLogical& Logical;
	class TinyGraphicQueueManager& Queues;
	class TinyGraphicMemoryManager& Memory;
	class TinyGraphicSwapchainManager& Swapchain;
	class TinyGraphicRenderManager& Passes;
	class TinyGraphicPipelineManager& Pipelines;

};
