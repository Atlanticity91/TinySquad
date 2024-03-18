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
TinyGraphicRenderpassManager::TinyGraphicRenderpassManager( )
	: _passes{ }
{ }

bool TinyGraphicRenderpassManager::Create( 
	const TinyGraphicLogical& logical,
	const tiny_string& name, 
	const TinyGraphicRenderpassBundle& bundle 
) {
	auto pass  = TinyGraphicRenderpass{ };
	auto state = pass.Create( logical, bundle );

	if ( state )
		_passes.emplace( name, pass );

	return state;
}

TinyGraphicRenderpass& TinyGraphicRenderpassManager::Begin(
	TinyGraphicWorkContext& work_context,
	const TinyGraphicRenderFrameManager& frames
) {
	return _passes[ work_context.WorkRender ].Begin( work_context, frames );
}

void TinyGraphicRenderpassManager::Terminate( const TinyGraphicLogical& logical ) {
	for ( auto& pass : _passes )
		pass.Data.Terminate( logical );
	_passes.clear( );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyGraphicRenderpassManager::GetExist( tiny_hash pass_name ) { 
	return _passes.find( pass_name );
}

TinyGraphicRenderpass& TinyGraphicRenderpassManager::GetPass( tiny_hash pass_name ) {
	return _passes[ pass_name ];
}
