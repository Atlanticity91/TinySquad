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

#include <TinyMicro/Graphics/Passes/Targets/TinyGraphicRenderTargetManager.h>

typedef tiny_list<VkImageView> TinyGraphicRenderFrameTargets;

tm_struct TinyGraphicRenderFrameProperties {

	VkRenderPass Pass;
	tiny_uint Width;
	tiny_uint Height;
	tiny_list<TinyGraphicRenderFrameTargets> Targets;

};

tm_class TinyGraphicRenderFrame final {

private:
	tiny_list<VkFramebuffer> m_framebuffers;

public:
	TinyGraphicRenderFrame( );

	~TinyGraphicRenderFrame( ) = default;

	bool Create( const TinyGraphicLogical& logical, const TinyGraphicRenderFrameProperties& properties );

	void Terminate( const TinyGraphicLogical& logical );

private:
	bool InternalCreate(
		VkFramebuffer& framebuffer,
		const TinyGraphicLogical& logical,
		const TinyGraphicRenderFrameProperties& properties,
		const TinyGraphicRenderFrameTargets& targets
	);

public:
	const VkFramebuffer Get( tiny_uint framebuffer ) const;

};
