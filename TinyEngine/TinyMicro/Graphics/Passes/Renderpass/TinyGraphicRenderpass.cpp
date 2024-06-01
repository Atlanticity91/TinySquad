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
	: m_handle{ VK_NULL_HANDLE },
	m_properties{ }
{ }

bool TinyGraphicRenderpass::Create( 
	const TinyGraphicLogical& logical,
	const TinyGraphicRenderpassBundle& bundle 
) {
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

	return vk::Check( vkCreateRenderPass( logical, tiny_rvalue( pass_info ), vk::GetAllocator( ), tiny_rvalue( m_handle ) ) );
}

void TinyGraphicRenderpass::SetClearValue( tiny_uint attachement, const tiny_color& color ) {
	auto clear_value = VkClearValue{ };

	clear_value.color = vk::CastColor( color );

	SetClearValue( attachement, clear_value );
}

void TinyGraphicRenderpass::SetClearValue(
	tiny_uint attachement,
	const VkClearColorValue& color
) {
	auto clear_value = VkClearValue{ };

	clear_value.color = color;

	SetClearValue( attachement, clear_value );
}

void TinyGraphicRenderpass::SetClearValue(
	tiny_uint attachement, 
	const VkClearDepthStencilValue& depth_value 
) {
	auto clear_value = VkClearValue{ };

	clear_value.depthStencil = depth_value;

	SetClearValue( attachement, clear_value );
}

void TinyGraphicRenderpass::SetClearValue( 
	tiny_uint attachement,
	const VkClearValue& clear_value 
) {
	if ( attachement < m_properties.ClearValues.size( ) )
		m_properties.ClearValues[ attachement ] = clear_value;
}

TinyGraphicRenderpass& TinyGraphicRenderpass::Begin( 
	TinyGraphicWorkContext& work_context, 
	const TinyGraphicRenderFrameManager& frames 
) {
	auto begin_info  = VkRenderPassBeginInfo{ VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO };
	auto framebuffer = frames.GetFramebuffer( work_context, m_properties.Frame );

	begin_info.pNext		   = VK_NULL_HANDLE;
	begin_info.renderPass	   = m_handle;
	begin_info.framebuffer	   = framebuffer;
	begin_info.renderArea	   = m_properties.Scissor;
	begin_info.clearValueCount = m_properties.ClearValues.size( );
	begin_info.pClearValues	   = m_properties.ClearValues.data( );

	vkCmdBeginRenderPass( work_context.Queue->CommandBuffer, tiny_rvalue( begin_info ), VK_SUBPASS_CONTENTS_INLINE );
	vkCmdSetViewport( work_context.Queue->CommandBuffer, 0, 1, tiny_rvalue( m_properties.Viewport ) );
	vkCmdSetScissor( work_context.Queue->CommandBuffer, 0, 1, tiny_rvalue( m_properties.Scissor ) );

	return tiny_self;
}

void TinyGraphicRenderpass::Terminate( const TinyGraphicLogical& logical ) {
	if ( vk::GetIsValid( m_handle ) )
		vkDestroyRenderPass( logical, m_handle, vk::GetAllocator( ) );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
const VkRenderPass TinyGraphicRenderpass::Get( ) const { return m_handle; }

const TinyGraphicRenderpassProperties& TinyGraphicRenderpass::GetProperties( ) const {
	return m_properties;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE GET ===
////////////////////////////////////////////////////////////////////////////////////////////
void TinyGraphicRenderpass::GetProperties( const TinyGraphicRenderpassBundle& bundle ) {
	m_properties.Subpass	 = bundle.Subpasses.size( );
	m_properties.Frame		 = bundle.Frame;
	m_properties.Scissor	 = bundle.Scissor;
	m_properties.Viewport    = bundle.Viewport;
	m_properties.ClearValues = bundle.ClearValues;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	OPERATOR ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyGraphicRenderpass::operator const VkRenderPass ( ) const { return Get( ); }
