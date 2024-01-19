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
 * @creation : 22/10/2023
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
TinyGraphicRenderBarrierManager::TinyGraphicRenderBarrierManager( )
	: _barriers{ }
{ }

void TinyGraphicRenderBarrierManager::Create( 
	const tiny_string& pass, 
	const tiny_list<TinyGraphicRenderBarrierBundle>& bundles
) {
	if ( !_barriers.find( pass ) ) {
		auto barrier = TinyGraphicRenderBarrier{ };

		barrier.Create( bundles );

		_barriers.emplace( pass, barrier );
	}
}

void TinyGraphicRenderBarrierManager::Transit( TinyGraphicWorkContext& work_context ) {
	if ( _barriers.find( work_context.WorkRender ) )
		_barriers[ work_context.WorkRender ].Transit( work_context );
}

void TinyGraphicRenderBarrierManager::Terminate( ) { _barriers.clear( ); }
