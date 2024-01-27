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

#include <TinyMicro/__tiny_micro_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyGraphicRenderManager::TinyGraphicRenderManager( )
	: _bundles{ },
	_targets{ },
	_barriers{ },
	_passes{ },
	_frames{ }
{ }

void TinyGraphicRenderManager::AddBundle( const TinyGraphicRenderBundle& bundle ) {
	_bundles.emplace_back( bundle );
}

bool TinyGraphicRenderManager::Create( TinyGraphicContext& graphic ) {
	CreateOutPass( );

	return  InternalCreate( graphic );
}

void TinyGraphicRenderManager::ReCreate( TinyGraphicContext& graphic ) {
	InternalTerminate( graphic );
	InternalCreate( graphic );
}

bool TinyGraphicRenderManager::Begin( tiny_hash pass_name, TinyGraphicWorkContext& work_context ) {
	auto state = _passes.GetExist( pass_name );

	if ( state ) {
		work_context.WorkPass   = 0;
		work_context.WorkRender = pass_name;

		_barriers.Transit( work_context );
		_passes.Begin( work_context, _frames );
	}

	return state;
}

bool TinyGraphicRenderManager::NextSubpass( TinyGraphicWorkContext& work_context ) {
	auto properties = _passes.GetPass( work_context.WorkRender ).GetProperties( );
	auto state		= work_context.WorkPass + 1 < properties.Subpass;

	if ( state ) {
		work_context.WorkPass += 1;

		_barriers.Transit( work_context );

		vkCmdNextSubpass( work_context.Queue->CommandBuffer, VK_SUBPASS_CONTENTS_INLINE );
	}

	return state;
}

void TinyGraphicRenderManager::End( TinyGraphicWorkContext& work_context ) {
	work_context.WorkPass += 1;

	_barriers.Transit( work_context );

	vkCmdEndRenderPass( work_context.Queue->CommandBuffer );
	
	work_context.WorkRender = 0;
}

void TinyGraphicRenderManager::Terminate( TinyGraphicContext& graphic ) {
	InternalTerminate( graphic );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE ===
////////////////////////////////////////////////////////////////////////////////////////////
void TinyGraphicRenderManager::CreateOutPass( ) {
	auto out_bundle = TinyGraphicRenderBundle{ };

	out_bundle.Name = "OutPass";

	out_bundle.Targets = 1;
	out_bundle.Targets[ 0 ].Name  = "OutTarget";
	out_bundle.Targets[ 0 ].Type  = TRT_TYPE_OUT;
	out_bundle.Targets[ 0 ].Clear = TinyPalettes::ASBESTOS;

	out_bundle.Passes = 2;

	out_bundle.Passes[ 0 ].Type	   = TGR_TYPE_RENDER;
	out_bundle.Passes[ 0 ].Stage   = TGR_STAGE_BEGIN;
	out_bundle.Passes[ 0 ].Targets = 1;
	out_bundle.Passes[ 0 ].Targets[ 0 ] = { "OutTarget", TGR_ACCESS_WRITE };

	out_bundle.Passes[ 1 ].Type	   = TGR_TYPE_RENDER;
	out_bundle.Passes[ 1 ].Stage   = TGR_STAGE_BEGIN;
	out_bundle.Passes[ 1 ].Targets = 1;
	out_bundle.Passes[ 1 ].Targets[ 0 ] = { "OutTarget", TGR_ACCESS_WRITE };

	_bundles.emplace_front( out_bundle );
}

void TinyGraphicRenderManager::CreateTargetTexture(
	TinyGraphicTextureProperties& texture, 
	const VkScissor& scissor,
	const TinyGraphicRenderTargetDescriptor& target
) {
	texture.Type	= TGT_TYPE_TEXTURE_2D;
	texture.Format  = target.Format;
	texture.Width   = scissor.extent.width;
	texture.Height  = scissor.extent.height;
	texture.Depth   = 0;
	texture.Levels  = 1;
	texture.Samples = target.MSAA;
	texture.Tiling  = VK_IMAGE_TILING_OPTIMAL;
	texture.Sampler = TinyGraphicSamplerProperties{ };

	if ( target.Type == TRT_TYPE_COLOR ) {
		texture.Layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
		texture.Aspect = VK_IMAGE_ASPECT_COLOR_BIT;
		texture.Usage  = TGT_USAGE_TARGET;
	} else if ( target.Type == TRT_TYPE_DEPTH ) {
		texture.Layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
		texture.Aspect = VK_IMAGE_ASPECT_DEPTH_BIT | VK_IMAGE_ASPECT_STENCIL_BIT;
		texture.Usage  = TGT_USAGE_DEPTH;
	}
}

bool TinyGraphicRenderManager::CreateTargets(
	TinyGraphicContext& graphic,
	const VkScissor& scissor,
	const tiny_list<TinyGraphicRenderTargetDescriptor>& targets
) {
	auto textures = tiny_list<TinyGraphicTextureProperties>{ };
	auto state	  = false;

	textures = graphic.Swapchain.GetProperties( ).Capacity;

	for ( const auto& target : targets ) {
		auto* name_str = target.Name.c_str( );

		if ( target.Type != TRT_TYPE_EXTERNAL ) {
			if ( target.Type != TRT_TYPE_OUT ) {
				for ( auto& texture : textures )
					CreateTargetTexture( texture, scissor, target );
			} else {
				auto swap_target = (tiny_uint)0;

				for ( auto& texture : textures )
					texture = graphic.Swapchain.GetTargetProperties( swap_target++ );
			}

			state = _targets.Create( graphic, name_str, textures );
		} else
			state = _targets.GetExist( name_str );

		if ( !state )
			break;
	}

	return state;
}

void TinyGraphicRenderManager::CreateBarrierImage( 
	TinyGraphicRenderBarrierImage& image, 
	TinyRenderTargetTypes type, 
	const tiny_string& target,
	bool read_only
) {
	if ( type == TRT_TYPE_OUT ) {
		image.AccessSource = read_only ? VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT : VK_ACCESS_COLOR_ATTACHMENT_READ_BIT;
		image.AccessTarget = read_only ? VK_ACCESS_COLOR_ATTACHMENT_READ_BIT : VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
		image.Source = read_only ? VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL : VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
		image.Target = read_only ? VK_IMAGE_LAYOUT_PRESENT_SRC_KHR : VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
		image.Aspect = VK_IMAGE_ASPECT_COLOR_BIT;
	} else if ( type == TRT_TYPE_COLOR ) {
		image.AccessSource = read_only ? VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT : VK_ACCESS_COLOR_ATTACHMENT_READ_BIT;
		image.AccessTarget = read_only ? VK_ACCESS_COLOR_ATTACHMENT_READ_BIT  : VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
		image.Source = read_only ? VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL : VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
		image.Target = read_only ? VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL : VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
		image.Aspect = VK_IMAGE_ASPECT_COLOR_BIT;
	} else {
		image.AccessSource = read_only ? VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT : VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT;
		image.AccessTarget = read_only ? VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT  : VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
		image.Source = read_only ? VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL : VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL;
		image.Target = read_only ? VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL  : VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
		image.Aspect = VK_IMAGE_ASPECT_DEPTH_BIT | VK_IMAGE_ASPECT_STENCIL_BIT;
	}

	image.Images = _targets.GetImages( target );
}

void TinyGraphicRenderManager::CreateBarriers( 
	const TinyGraphicRenderBundle& bundle,
	const TinyGraphicRenderReferences& references 
) {
	auto barrier_count = references.Passes.size( );
	auto barriers	   = tiny_list<TinyGraphicRenderBarrierBundle>{ barrier_count + 1 };

	//_barriers.Create( bundle.Name.c_string( ), barriers );
}

tiny_list<VkClearValue> TinyGraphicRenderManager::CreatePassClears(
	const TinyGraphicRenderBundle& bundle
) {
	auto clears		 = tiny_list<VkClearValue>{ };
	auto clear_count = bundle.Targets.size( );

	clears = clear_count;

	while ( clear_count-- > 0 )
		clears[ clear_count ] = bundle.Targets[ clear_count ].Clear;

	return clears;
}

TinyGraphicRenderReferences TinyGraphicRenderManager::CreatePassReferences(
	const TinyGraphicRenderBundle& bundle
) {
	auto references = TinyGraphicRenderReferences{ };
	auto pass_id	= (tiny_uint)0;

	references.Passes = bundle.Passes.size( );

	for ( auto& pass : bundle.Passes ) {
		auto& reference = references.Passes[ pass_id++ ];

		reference.Bindpoint   = (VkPipelineBindPoint)pass.Type;
		reference.InputOffset = references.References.size( );
		reference.ColorOffset = reference.InputOffset;

		for ( auto& target : pass.Targets ) {
			auto name_str	 = target.Name.c_str( );
			auto layout		 = _targets.GetTarget( name_str ).GetLayout( );
			auto attachement = bundle.Targets.find( 
				[ target ]( const auto& _target ) {
					return _target.Name == target.Name;
				}
			);

			if ( bundle.Targets[ attachement ].Type == TRT_TYPE_OUT )
				layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

			if ( bundle.Targets[ attachement ].Type != TRT_TYPE_DEPTH ) { 
				if ( target.Access & TGR_ACCESS_WRITE )
					reference.ColorCount += 1;
				else if ( target.Access & TGR_ACCESS_READ )
					reference.InputCount += 1;
			} else 
				reference.DepthOffset = references.References.size( );

			references.References.emplace_back( { attachement, layout } );
		}

		reference.ColorOffset += reference.InputCount;
	}

	return references;
}

tiny_list<VkAttachmentDescription> TinyGraphicRenderManager::CreatePassAttachments( 
	const TinyGraphicRenderBundle& bundle 
) {
	auto attachements = tiny_list<VkAttachmentDescription>{ };
	auto target_id	  = (tiny_uint)0;

	attachements = bundle.Targets.size( );

	for ( auto& attachement : attachements ) {
		auto& target	  = bundle.Targets[ target_id++ ];
		auto* target_name = target.Name.c_str( );

		attachement.flags		  = VK_NULL_FLAGS;
		attachement.format		  = target.Format;
		attachement.samples		  = target.MSAA;
		attachement.loadOp		  = (VkAttachmentLoadOp)target.Load;
		attachement.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;

		if ( target.Type != TRT_TYPE_DEPTH ) {
			attachement.storeOp		   = VK_ATTACHMENT_STORE_OP_STORE;
			attachement.stencilLoadOp  = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
			attachement.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		} else {
			attachement.storeOp		   = VK_ATTACHMENT_STORE_OP_DONT_CARE;
			attachement.stencilLoadOp  = VK_ATTACHMENT_LOAD_OP_CLEAR;
			attachement.stencilStoreOp = VK_ATTACHMENT_STORE_OP_STORE;
		}

		attachement.finalLayout = _targets.GetTarget( target_name ).GetLayout( );
	}

	return attachements;
}

tiny_list<VkSubpassDescription> TinyGraphicRenderManager::CreatePassSubpasses(
	const TinyGraphicRenderReferences& references
) {

	auto subpass = tiny_list<VkSubpassDescription>{ };
	auto pass_id = (tiny_uint)0;

	subpass = references.Passes.size( );

	for ( auto& pass : subpass ) {
		auto& pass_ref = references.Passes[ pass_id ];

		pass.flags				  = VK_NULL_FLAGS;
		pass.pipelineBindPoint	  = pass_ref.Bindpoint;
		pass.inputAttachmentCount = pass_ref.InputCount;
		pass.pInputAttachments	  = references.References.data( ) + pass_ref.InputOffset;
		pass.colorAttachmentCount = pass_ref.ColorCount;
		pass.pColorAttachments	  = references.References.data( ) + pass_ref.ColorOffset;
		pass.pResolveAttachments  = VK_NULL_HANDLE;

		if ( pass_ref.DepthOffset < TINY_UINT_MAX )
			pass.pDepthStencilAttachment = references.References.data( ) + pass_ref.DepthOffset;
		else
			pass.pDepthStencilAttachment = VK_NULL_HANDLE;

		pass.preserveAttachmentCount = 0;
		pass.pPreserveAttachments	 = VK_NULL_HANDLE;

		pass_id += 1;
	}

	return subpass;
}

tiny_list<VkSubpassDependency> TinyGraphicRenderManager::CreatePassDependencies( 
	const TinyGraphicRenderBundle& bundle 
) {
	auto dependencies  = tiny_list<VkSubpassDependency>{ };
	auto dependency	   = (tiny_uint)0;
	
	dependencies = bundle.Passes.size( ) + 1;

	while ( dependency < bundle.Passes.size( ) ) {
		auto& _dependency = dependencies[ dependency ];
		auto previous	  = dependency - 1;

		_dependency.srcSubpass		= dependency > 0 ? previous : VK_SUBPASS_EXTERNAL;
		_dependency.dstSubpass		= dependency;
		_dependency.dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT;

		if ( dependency > 0 ) {
			_dependency.srcStageMask  = dependencies[ previous ].dstStageMask;
			_dependency.srcAccessMask = dependencies[ previous ].dstAccessMask;
		} else {
			_dependency.srcStageMask  = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
			_dependency.srcAccessMask = VK_ACCESS_SHADER_READ_BIT;
		}

		// TODO : CORRECT DEPENDENCIES

		/*
		_dependency.dstAccessMask = VK_ACCESS_INDEX_READ_BIT			| 
									VK_ACCESS_VERTEX_ATTRIBUTE_READ_BIT | 
									VK_ACCESS_INPUT_ATTACHMENT_READ_BIT | 
									VK_ACCESS_SHADER_READ_BIT			| 
									VK_ACCESS_SHADER_WRITE_BIT;
		*/
		
		_dependency.dstStageMask  = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
		_dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

		/*
		if ( bundle.Passes[ dependency ].Targets[ 0 ].Access & TGR_ACCESS_WRITE )
			_dependency.dstAccessMask |=  VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
		else if ( bundle.Passes[ dependency ].Targets[ 0 ].Access & TGR_ACCESS_READ )
			_dependency.dstAccessMask |= VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT;
		*/

		/*
		dependencies[0].srcSubpass = VK_SUBPASS_EXTERNAL;
		dependencies[0].dstSubpass = 0;
		dependencies[0].srcStageMask = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
		dependencies[0].dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
		dependencies[0].srcAccessMask = VK_ACCESS_SHADER_READ_BIT;
		dependencies[0].dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
		dependencies[0].dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT;
		*/

		dependency += 1;
	}

	auto& _dependency = dependencies[ dependency ];

	_dependency.srcSubpass		= dependency - 1;
	_dependency.dstSubpass		= VK_SUBPASS_EXTERNAL;
	_dependency.srcStageMask	= dependencies[ dependency - 1 ].dstStageMask;
	_dependency.dstStageMask	= VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
	_dependency.srcAccessMask   = dependencies[ dependency - 1 ].dstAccessMask;
	_dependency.dstAccessMask   = VK_ACCESS_SHADER_READ_BIT;
	_dependency.dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT;

	return dependencies;
}

bool TinyGraphicRenderManager::CreatePasse( 
	TinyGraphicContext& graphic,
	const VkViewport& viewport,
	const VkScissor& scissor,
	const TinyGraphicRenderBundle& bundle
) {
	auto renderpass = TinyGraphicRenderpassBundle{ };
	auto references = CreatePassReferences( bundle );
	auto* name_str  = bundle.Name.c_str( );
	
	renderpass.Frame		= _frames.GetCount( );
	renderpass.Viewport		= viewport;
	renderpass.Scissor		= scissor;
	renderpass.ClearValues  = CreatePassClears( bundle );
	renderpass.Attachments  = CreatePassAttachments( bundle );
	renderpass.Subpasses    = CreatePassSubpasses( references );
	renderpass.Dependencies = CreatePassDependencies( bundle );

	auto state = _passes.Create( graphic.Logical, name_str, renderpass );
	
	if ( state ) 
		CreateBarriers( bundle, references );

	return state;
}

bool TinyGraphicRenderManager::CreateFrame(
	TinyGraphicContext& graphic,
	const VkScissor& scissor,
	const TinyGraphicRenderBundle& bundle
) {
	auto* name_str = bundle.Name.c_str( );
	auto frame	   = TinyGraphicRenderFrameProperties{ };

	frame.Pass	  = GetPass( name_str );
	frame.Width   = scissor.extent.width;
	frame.Height  = scissor.extent.height;
	frame.Targets = graphic.Swapchain.GetProperties( ).Capacity;

	for ( auto& target : bundle.Targets ) {
		name_str = target.Name.c_str( );

		auto views	 = _targets.GetViews( name_str );
		auto view_id = views.size( );

		while ( view_id-- > 0 )
			frame.Targets[ view_id ].emplace_back( views[ view_id ] );
	}

	return _frames.Create( graphic.Logical, frame );
}

bool TinyGraphicRenderManager::InternalCreate( TinyGraphicContext& graphic ) {
	auto state = false;

	for ( const auto& bundle : _bundles ) {
		auto use_out   = GetUseOut( bundle );
		auto& viewport = use_out ? graphic.Boundaries.GetSwapViewport( ) : graphic.Boundaries.GetViewport( );
		auto& scissor  = use_out ? graphic.Boundaries.GetSwapScissor( )  : graphic.Boundaries.GetScissor( );

		state = CreateTargets( graphic, scissor, bundle.Targets );

		if ( state ) state = CreatePasse( graphic, viewport, scissor, bundle );
		if ( state ) state = CreateFrame( graphic, scissor, bundle );

		if ( !state )
			break;
	}

	return state;
}

void TinyGraphicRenderManager::InternalTerminate( TinyGraphicContext& graphic ) {
	_frames.Terminate( graphic.Logical );
	_passes.Terminate( graphic.Logical );
	_barriers.Terminate( );
	_targets.Terminate( graphic );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
const tiny_list<TinyGraphicRenderBundle>& TinyGraphicRenderManager::GetBundles( ) const {
	return _bundles;
}

TinyGraphicRenderpass& TinyGraphicRenderManager::GetPass( const tiny_string& pass_name ) {
	auto hash = tiny_hash{ pass_name };

	return _passes.GetPass( hash );
}

TinyGraphicRenderpass& TinyGraphicRenderManager::GetPass( const TinyGraphicWorkContext& work_context ) {
	return _passes.GetPass( work_context.WorkRender );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE GET ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyGraphicRenderManager::GetUseOut( const TinyGraphicRenderBundle& bundle ) const {
	auto state = false;

	for ( auto& target : bundle.Targets ) {
		if ( target.Type != TRT_TYPE_EXTERNAL )
			state = target.Type == TRT_TYPE_OUT;
		else {
			auto find = false;

			for ( auto& bundle : _bundles ) {
				for ( auto& pass_target : bundle.Targets ) {
					if ( target.Name != pass_target.Name )
						continue;

					state = pass_target.Type == TRT_TYPE_OUT;
					find  = true;

					break;
				}

				if ( find )
					break;
			}
		}

		if ( state )
			break;
	}

	return state;
}
