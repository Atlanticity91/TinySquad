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

#include <TinyMicro/Graphics/Passes/Barriers/TinyGraphicRenderBarrierManager.h>

tm_struct TinyGraphicRenderpassBundle {

	tiny_uint Frame = 0;
	VkViewport Viewport{ };
	VkRect2D Scissor{ };
	tiny_list<VkClearValue> ClearValues{ };
	tiny_list<VkAttachmentDescription> Attachments{ };
	tiny_list<VkSubpassDescription> Subpasses{ };
	tiny_list<VkSubpassDependency> Dependencies{ };

};

tm_struct TinyGraphicRenderpassProperties {

	tiny_uint Subpass = 0;
	tiny_uint Frame   = 0;
	VkViewport Viewport{ };
	VkRect2D Scissor{ };
	tiny_list<VkClearValue> ClearValues{ };

};
