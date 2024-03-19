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
TinyGraphicRenderFrameManager::TinyGraphicRenderFrameManager( )
	: _frames{ }
{ }

bool TinyGraphicRenderFrameManager::Create( 
	const TinyGraphicLogical& logical, 
	const TinyGraphicRenderFrameProperties& frame 
) {
	auto new_frame = TinyGraphicRenderFrame{ };
	auto state = new_frame.Create( logical, frame );

	if ( state )
		_frames.emplace_back( new_frame );

	return state;
}

void TinyGraphicRenderFrameManager::Terminate( const TinyGraphicLogical& logical ) {
	for ( auto& frame : _frames )
		frame.Terminate( logical );
	_frames.clear( );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
tiny_uint TinyGraphicRenderFrameManager::GetCount( ) const { return _frames.size( ); }

const VkFramebuffer TinyGraphicRenderFrameManager::GetFramebuffer(
	TinyGraphicWorkContext& work_context,
	tiny_uint frame 
) const {
	return _frames[ frame ].Get( work_context.WorkID );
}
