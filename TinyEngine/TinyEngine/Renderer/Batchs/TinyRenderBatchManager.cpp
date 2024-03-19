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
 * @creation : 23/12/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#include <TinyEngine/__tiny_engine_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyRenderBatchManager::TinyRenderBatchManager( ) 
	: _staging{ },
	_sprites{ }
{ }

bool TinyRenderBatchManager::Initialize( TinyGraphicManager& graphics ) {
	constexpr auto size_2d = TinyRenderBatchSprite::Size;
	//constexpr auto size_3d = BatchIndex_t::Size + BatchVertex_t::Size;
	//constexpr auto size    = size_2d < size_3d ? size_3d : size_2d;

	auto context = graphics.GetContext( );
	
	return  _staging.Create( context, size_2d ) &&
			_sprites.Create( graphics );
}

void TinyRenderBatchManager::Prepare(
	TinyGame* game, 
	TinyRenderBatchTypes type,
	const tiny_hash render_pass, 
	Callback_t callback,
	TinyRenderUniformManager& uniforms
) {
	auto& graphics = game->GetGraphics( );
	auto& batch	   = _sprites;

	switch ( type ) {
		case TRB_TYPE_VERTEX : break;
		case TRB_TYPE_LIGHT	 : break;
		case TRB_TYPE_TEXT	 : break;

		default : break;
	}

	Flush( game, type , uniforms );

	batch.Prepare( graphics, render_pass, callback );
}

void TinyRenderBatchManager::Draw( 
	TinyGame* game,
	TinyRenderUniformManager& uniforms,
	const TinyRenderSpriteContext& draw_context 
) {
	_sprites.Draw( game, _staging, uniforms, draw_context );
}

void TinyRenderBatchManager::Draw(
	TinyGame* game,
	TinyRenderUniformManager& uniforms,
	const TinyRenderVertexContext& draw_context
) {
}

void TinyRenderBatchManager::Draw( 
	TinyGame* game,
	TinyRenderUniformManager& uniforms,
	const TinyRenderLightContext& draw_context 
) {
}

void TinyRenderBatchManager::Draw(
	TinyGame* game,
	TinyRenderUniformManager& uniforms,
	const TinyRenderTextContext& draw_context 
) {
}

void TinyRenderBatchManager::Flush( 
	TinyGame* game, 
	TinyRenderBatchTypes type,
	TinyRenderUniformManager& uniforms
) {
	auto& graphics = game->GetGraphics( );
	auto& assets = game->GetAssets( );
	auto& batch = _sprites;

	switch ( type ) {
		case TRB_TYPE_VERTEX : break;
		case TRB_TYPE_LIGHT  : break;
		case TRB_TYPE_TEXT	 : break;

		default: break;
	}

	batch.Flush( assets, graphics, _staging, uniforms );
}

void TinyRenderBatchManager::Flush( TinyGame* game, TinyRenderUniformManager& uniforms ) {
	auto& graphics = game->GetGraphics( );
	auto& assets   = game->GetAssets( );

	_sprites.Flush( assets, graphics, _staging, uniforms );
}

void TinyRenderBatchManager::Terminate( TinyGraphicManager& graphics ) {
	auto context = graphics.GetContext( );

	_staging.Terminate( context );
	_sprites.Terminate( );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyGraphicBufferStaging& TinyRenderBatchManager::GetStaging( ) { return _staging; }

TinyRenderBatchSprite& TinyRenderBatchManager::GetSprites( ) { return _sprites; }
