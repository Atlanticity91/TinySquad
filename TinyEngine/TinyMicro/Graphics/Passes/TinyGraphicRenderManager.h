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

#include "Utils/TinyGraphicClearAttachement.h"

#define TINY_OUTPASS_NAME "OutPass"

static const tiny_hash TINY_OUTPASS_HASH = tiny_hash{ TINY_OUTPASS_NAME };

tm_class TinyGraphicRenderManager final {

	using BundleMap  = tiny_map<TinyGraphicRenderBundle>;
	using BundleNode = BundleMap::under_node;

private:
	BundleMap _bundles;
	TinyGraphicRenderTargetManager	   _targets;
	TinyGraphicRenderBarrierManager	   _barriers;
	TinyGraphicRenderpassManager	   _passes;
	TinyGraphicRenderFrameManager	   _frames;

public:
	TinyGraphicRenderManager( );

	~TinyGraphicRenderManager( ) = default;

	void AddBundle( const tiny_string& name, const TinyGraphicRenderBundle& bundle );

	bool Create( TinyGraphicContext& graphic );

	void ReCreate( TinyGraphicContext& graphic );

	bool Begin( const tiny_hash pass_name, TinyGraphicWorkContext& work_context );

	bool NextSubpass( TinyGraphicWorkContext& work_context );

	void End( TinyGraphicWorkContext& work_context );

	void Clear(
		const tiny_hash pass_name,
		TinyGraphicWorkContext& work_context,
		tiny_init<TinyGraphicClearRegion> attachements
	);

	void Clear(
		const tiny_hash pass_name,
		TinyGraphicWorkContext& work_context,
		tiny_init<TinyGraphicClearAttachement> attachements
	);

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

	TinyGraphicRenderReferences CreatePassReferences( 
		const TinyGraphicRenderBundle& bundle 
	);
	
	tiny_list<VkAttachmentDescription> CreatePassAttachments( 
		const TinyGraphicRenderBundle& bundle
	);
	
	tiny_list<VkSubpassDescription> CreatePassSubpasses( 
		const TinyGraphicRenderReferences& references
	);

	tiny_list<VkSubpassDependency> CreatePassDependencies( 
		const TinyGraphicRenderBundle& bundle 
	);

	bool CreatePasse( 
		TinyGraphicContext& graphic,
		const VkViewport& viewport,
		const VkScissor& scissor,
		const BundleNode& bundle
	);

	bool CreateFrame( 
		TinyGraphicContext& graphic,
		const VkScissor& scissor,
		const BundleNode& bundle
	);

	bool InternalCreate( TinyGraphicContext& graphic );

	void ClearAttachements(
		TinyGraphicWorkContext& work_context,
		const tiny_list<VkClearAttachment>& images,
		const tiny_list<VkClearRect>& bounds
	);

	void InternalTerminate( TinyGraphicContext& graphic );

public:
	const BundleMap& GetBundles( ) const;

	TinyGraphicRenderpass& GetPass( const tiny_string& pass_name );

	TinyGraphicRenderpass& GetPass( const TinyGraphicWorkContext& work_context );

private:
	bool GetUseOut( const TinyGraphicRenderBundle& bundle ) const;

};
