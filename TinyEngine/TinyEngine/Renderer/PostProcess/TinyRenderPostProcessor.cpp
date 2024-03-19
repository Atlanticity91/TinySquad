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
 * @creation : 15/03/2024
 * @version  : 2024.2.6
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#include <TinyEngine/__tiny_engine_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyRenderPostProcessor::TinyRenderPostProcessor( )
{ }

void TinyRenderPostProcessor::Compose( 
	TinyGame* game,
	TinyRenderUniformManager& uniforms,
	TinyRenderBatchManager& batchs 
) {
	auto& graphics = game->GetGraphics( );

	graphics.NextSubpass( ); 

	auto& renderer = game->GetRenderer( );

	renderer.DrawDebug( { { 0.f, 0.f }, 128.f, 0.001f } );
}
