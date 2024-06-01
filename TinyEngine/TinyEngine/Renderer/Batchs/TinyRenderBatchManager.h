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
 * @creation : 26/11/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "Instances/TinyRenderBatchText.h"

tiny_enum( TinyRenderBatchTypes ) { 

	TRB_TYPE_SPRITES = 0,
	TRB_TYPE_VERTEX,
	TRB_TYPE_LIGHT,
	TRB_TYPE_TEXT

};

te_class TinyRenderBatchManager final {

public:
	using Callback_t = TinyRenderBatchSprite::Callback_t;

private:
	TinyGraphicBufferStaging m_staging;
	TinyRenderBatchSprite m_sprites;
	TinyRenderBatchText m_text;

public:
	TinyRenderBatchManager( );

	~TinyRenderBatchManager( ) = default;

	bool Initialize( TinyGraphicManager& graphics, TinyRenderUniformManager& uniforms );

	void Prepare(
		TinyGame* game,
		TinyRenderBatchTypes type,
		const tiny_hash render_pass,
		Callback_t callback,
		TinyRenderUniformManager& uniforms
	);

	void Draw( 
		TinyGame* game, 
		TinyRenderUniformManager& uniforms,
		const TinyRenderSpriteContext& draw_context
	);

	void Draw( 
		TinyGame* game, 
		TinyRenderUniformManager& uniforms, 
		const TinyRenderVertexContext& draw_context 
	);

	void Draw( 
		TinyGame* game,
		TinyRenderUniformManager& uniforms, 
		const TinyRenderLightContext& draw_context 
	);

	void Draw( 
		TinyGame* game,
		TinyRenderUniformManager& uniforms, 
		const TinyRenderTextContext& draw_context 
	);

	void Flush( 
		TinyGame* game,
		TinyRenderBatchTypes type, 
		TinyRenderUniformManager& uniforms 
	);

	void Flush( TinyGame* game, TinyRenderUniformManager& uniforms );

	void Terminate( TinyGraphicManager& graphics );

public:
	TinyGraphicBufferStaging& GetStaging( );

	TinyRenderBatchSprite& GetSprites( );

};
