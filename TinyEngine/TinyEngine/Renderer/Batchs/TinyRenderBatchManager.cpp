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
	: m_staging{ },
	m_sprites{ },
	m_text{ }
{ }

bool TinyRenderBatchManager::Initialize( 
	TinyGraphicManager& graphics,
	TinyRenderUniformManager& uniforms 
) {
	auto graphic = graphics.GetWrapper( );
	auto size_2d = TinyRenderBatchSprite::Size + TINY_QUAD_INDEX_SIZE;
	//constexpr auto size_3d = BatchIndex_t::Size + BatchVertex_t::Size;
	//constexpr auto size    = size_2d < size_3d ? size_3d : size_2d;
	
	return  m_staging.Create( graphic, size_2d )   &&
			m_sprites.Create( graphics, uniforms ) &&
			m_text.Create( graphics, uniforms );
}

void TinyRenderBatchManager::Prepare(
	TinyGame* game, 
	TinyRenderBatchTypes type,
	const tiny_hash render_pass, 
	Callback_t callback,
	TinyRenderUniformManager& uniforms
) {
	auto& graphics = game->GetGraphics( );

	Flush( game, type, uniforms );

	switch ( type ) {
		case TRB_TYPE_SPRITES : m_sprites.Prepare( graphics, render_pass, callback ); break;
		case TRB_TYPE_VERTEX  : break;
		case TRB_TYPE_LIGHT	  : break;
		case TRB_TYPE_TEXT	  : m_text.Prepare( graphics, render_pass, callback ); break;

		default : break;
	}
}

void TinyRenderBatchManager::Draw( 
	TinyGame* game,
	TinyRenderUniformManager& uniforms,
	const TinyRenderSpriteContext& draw_context 
) {
	m_sprites.Draw( game, m_staging, uniforms, draw_context );
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
	m_text.Draw( game, m_staging, uniforms, draw_context );
}

void TinyRenderBatchManager::Flush( 
	TinyGame* game, 
	TinyRenderBatchTypes type,
	TinyRenderUniformManager& uniforms
) {
	auto& graphics = game->GetGraphics( );
	auto& assets = game->GetAssets( );

	switch ( type ) {

		case TRB_TYPE_SPRITES : m_sprites.Flush( assets, graphics, m_staging, uniforms ); break;
		case TRB_TYPE_VERTEX  : break;
		case TRB_TYPE_LIGHT   : break;
		case TRB_TYPE_TEXT	  : m_text.Flush( assets, graphics, m_staging, uniforms ); break;

		default: break;
	}
}

void TinyRenderBatchManager::Flush( TinyGame* game, TinyRenderUniformManager& uniforms ) {
	auto& graphics = game->GetGraphics( );
	auto& assets   = game->GetAssets( );

	m_sprites.Flush( assets, graphics, m_staging, uniforms );
}

void TinyRenderBatchManager::Terminate( TinyGraphicManager& graphics ) {
	auto graphic = graphics.GetWrapper( );

	m_staging.Terminate( graphic );
	m_sprites.Terminate( ); 
	m_text.Terminate( );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyGraphicBufferStaging& TinyRenderBatchManager::GetStaging( ) { return m_staging; }

TinyRenderBatchSprite& TinyRenderBatchManager::GetSprites( ) { return m_sprites; }
