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
 * @creation : 21/10/2023
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
TinyGraphicRenderFrame::TinyGraphicRenderFrame( )
	: _framebuffers{ }
{ }

bool TinyGraphicRenderFrame::Create( 
	const TinyGraphicLogical& logical, 
	const TinyGraphicRenderFrameProperties& properties 
) {
	auto frame_id = properties.Targets.size( );
	auto state	  = true;

	_framebuffers = frame_id;

	while ( state && frame_id-- > 0 ) {
		const auto& targets = properties.Targets[ frame_id ];

		state = InternalCreate( _framebuffers[ frame_id ], logical, properties, targets );
	}

	return state;
}

void TinyGraphicRenderFrame::Terminate( const TinyGraphicLogical& logical ) {
	for ( auto& framebuffer : _framebuffers ) {
		if ( vk::GetIsValid( framebuffer ) )
			vkDestroyFramebuffer( logical, framebuffer, vk::GetAllocator( ) );
	}
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyGraphicRenderFrame::InternalCreate( 
	VkFramebuffer& framebuffer, 
	const TinyGraphicLogical& logical,
	const TinyGraphicRenderFrameProperties& properties,
	const TinyGraphicRenderFrameTargets& targets
) {
	auto frame_info = VkFramebufferCreateInfo{ VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO };

	frame_info.pNext		   = VK_NULL_HANDLE;
	frame_info.flags		   = VK_NULL_FLAGS;
	frame_info.renderPass	   = properties.Pass;
	frame_info.attachmentCount = targets.size( );
	frame_info.pAttachments	   = targets.data( );
	frame_info.width		   = properties.Width;
	frame_info.height		   = properties.Height;
	frame_info.layers		   = 1;

	return vk::Check( vkCreateFramebuffer( logical, &frame_info, vk::GetAllocator( ), &framebuffer ) );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
const VkFramebuffer TinyGraphicRenderFrame::Get( tiny_uint framebuffer ) const { 
	return _framebuffers[ framebuffer ];
}
