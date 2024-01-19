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

#include "Utils/TinyGraphicRenderBundle.h"

tm_class TinyGraphicRenderManager final {

private:
	tiny_list<TinyGraphicRenderBundle> _bundles;
	TinyGraphicRenderTargetManager	   _targets;
	TinyGraphicRenderBarrierManager	   _barriers;
	TinyGraphicRenderpassManager	   _passes;
	TinyGraphicRenderFrameManager	   _frames;

public:
	TinyGraphicRenderManager( );

	~TinyGraphicRenderManager( ) = default;

	void AddBundle( const TinyGraphicRenderBundle& bundle );

	bool Create( TinyGraphicContext& graphic );

	void ReCreate( TinyGraphicContext& graphic );

	bool Begin( tiny_hash pass_name, TinyGraphicWorkContext& work_context );

	bool NextSubpass( TinyGraphicWorkContext& work_context );

	void End( TinyGraphicWorkContext& work_context );

	void Terminate( TinyGraphicContext& graphic );

private:
	void CreateOutPass( );

	void CreateTargetTexture( 
		TinyGraphicTextureProperties& texture, 
		const VkScissor& scissor,
		const TinyGraphicRenderTargetDescriptor& target 
	);

	bool CreateTargets( 
		TinyGraphicContext& graphic,
		const VkScissor& scissor,
		const tiny_list<TinyGraphicRenderTargetDescriptor>& targets
	);

	void CreateBarrierImage(
		TinyGraphicRenderBarrierImage& image,
		TinyRenderTargetTypes type,
		const tiny_string& target,
		bool read_only
	);

	void CreateBarriers( 
		const TinyGraphicRenderBundle& bundle,
		const TinyGraphicRenderReferences& references 
	);

	tiny_list<VkClearValue> CreatePassClears( const TinyGraphicRenderBundle& bundle );

	TinyGraphicRenderReferences CreatePassReferences( const TinyGraphicRenderBundle& bundle );
	
	tiny_list<VkAttachmentDescription> CreatePassAttachments( const TinyGraphicRenderBundle& bundle );
	
	tiny_list<VkSubpassDescription> CreatePassSubpasses( 
		const TinyGraphicRenderReferences& references
	);

	tiny_list<VkSubpassDependency> CreatePassDependencies( const TinyGraphicRenderBundle& bundle );

	bool CreatePasse( 
		TinyGraphicContext& graphic,
		const VkViewport& viewport,
		const VkScissor& scissor,
		const TinyGraphicRenderBundle& bundle
	);

	bool CreateFrame( 
		TinyGraphicContext& graphic,
		const VkScissor& scissor,
		const TinyGraphicRenderBundle& bundle
	);

	bool InternalCreate( TinyGraphicContext& graphic );

	void InternalTerminate( TinyGraphicContext& graphic );

public:
	const tiny_list<TinyGraphicRenderBundle>& GetBundles( ) const;

	TinyGraphicRenderpass& GetPass( const tiny_string& pass_name );

	TinyGraphicRenderpass& GetPass( const TinyGraphicWorkContext& work_context );

private:
	bool GetUseOut( const TinyGraphicRenderBundle& bundle ) const;

};
