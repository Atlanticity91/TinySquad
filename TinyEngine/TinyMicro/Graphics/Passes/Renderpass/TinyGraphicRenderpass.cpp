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
TinyGraphicRenderpass::TinyGraphicRenderpass( )
	: _handle{ VK_NULL_HANDLE },
	_properties{ }
{ }

bool TinyGraphicRenderpass::Create( const TinyGraphicLogical& logical, const TinyGraphicRenderpassBundle& bundle ) {
	GetProperties( bundle );

	auto pass_info = VkRenderPassCreateInfo{ VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO };

	pass_info.pNext			  = VK_NULL_HANDLE;
	pass_info.flags			  = VK_NULL_FLAGS;
	pass_info.attachmentCount = bundle.Attachments.size( );
	pass_info.pAttachments	  = bundle.Attachments.data( );
	pass_info.subpassCount	  = bundle.Subpasses.size( );
	pass_info.pSubpasses	  = bundle.Subpasses.data( );
	pass_info.dependencyCount = bundle.Dependencies.size( );
	pass_info.pDependencies   = bundle.Dependencies.data( );

	return vk::Check( vkCreateRenderPass( logical, &pass_info, vk::GetAllocator( ), &_handle ) );
}

void TinyGraphicRenderpass::SetClearValue( tiny_uint attachement, const tiny_color& color ) {
	auto clear_value = VkClearValue{ };

	clear_value.color = vk::CastColor( color );

	SetClearValue( attachement, clear_value );
}

void TinyGraphicRenderpass::SetClearValue( tiny_uint attachement, const VkClearColorValue& color ) {
	auto clear_value = VkClearValue{ };

	clear_value.color = color;

	SetClearValue( attachement, clear_value );
}

void TinyGraphicRenderpass::SetClearValue( tiny_uint attachement, const VkClearDepthStencilValue& depth_value ) {
	auto clear_value = VkClearValue{ };

	clear_value.depthStencil = depth_value;

	SetClearValue( attachement, clear_value );
}

void TinyGraphicRenderpass::SetClearValue( tiny_uint attachement, const VkClearValue& clear_value ) {
	if ( attachement < _properties.ClearValues.size( ) )
		_properties.ClearValues[ attachement ] = clear_value;
}

TinyGraphicRenderpass& TinyGraphicRenderpass::Begin( TinyGraphicWorkContext& work_context, const TinyGraphicRenderFrameManager& frames ) {
	auto begin_info  = VkRenderPassBeginInfo{ VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO };
	auto framebuffer = frames.GetFramebuffer( _properties.Frame, work_context );

	begin_info.pNext		   = VK_NULL_HANDLE;
	begin_info.renderPass	   = _handle;
	begin_info.framebuffer	   = framebuffer;
	begin_info.renderArea	   = _properties.Scissor;
	begin_info.clearValueCount = _properties.ClearValues.size( );
	begin_info.pClearValues	   = _properties.ClearValues.data( );

	vkCmdBeginRenderPass( work_context.Queue->CommandBuffer, &begin_info, VK_SUBPASS_CONTENTS_INLINE );
	vkCmdSetViewport( work_context.Queue->CommandBuffer, 0, 1, &_properties.Viewport );
	vkCmdSetScissor( work_context.Queue->CommandBuffer, 0, 1, &_properties.Scissor );

	return tiny_self;
}

void TinyGraphicRenderpass::Terminate( const TinyGraphicLogical& logical ) {
	if ( vk::GetIsValid( _handle ) )
		vkDestroyRenderPass( logical, _handle, vk::GetAllocator( ) );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
const VkRenderPass TinyGraphicRenderpass::Get( ) const { return _handle; }

const TinyGraphicRenderpassProperties& TinyGraphicRenderpass::GetProperties( ) const {
	return _properties;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE GET ===
////////////////////////////////////////////////////////////////////////////////////////////
void TinyGraphicRenderpass::GetProperties( const TinyGraphicRenderpassBundle& bundle ) {
	_properties.Subpass		= bundle.Subpasses.size( );
	_properties.Frame		= bundle.Frame;
	_properties.Scissor		= bundle.Scissor;
	_properties.Viewport    = bundle.Viewport;
	_properties.ClearValues = bundle.ClearValues;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	OPERATOR ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyGraphicRenderpass::operator const VkRenderPass ( ) const { return Get( ); }
