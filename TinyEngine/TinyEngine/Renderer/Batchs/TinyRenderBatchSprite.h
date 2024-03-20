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
 * @creation : 19/03/2024
 * @version  : 2024.2.7
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "TinyRenderBatchInstance.h"

#define TinySpriteIndexBuffer "ib_sprite_indexes"
#define TinySpriteVertexBuffer "ib_sprite_vertex"

te_class TinyRenderBatchSprite final 
	: tiny_inherit( TinyRenderBatchInstance<TinyRenderSpriteContext, TINY_MAX_VERTEX> )
{

public:
	using Index_t  = TinyRenderBatch<TinyRenderSpriteIndex, TINY_MAX_VERTEX>;
	using Vertex_t = TinyRenderBatch<TinyRenderSpriteVertex, TINY_MAX_VERTEX>;

	static const tiny_uint Size = Vertex_t::Size + Index_t::Size;

private:
	Index_t  _indexes;
	Vertex_t _vertex;

public:
	TinyRenderBatchSprite( );

	~TinyRenderBatchSprite( ) = default;

	tiny_implement( bool Create( 
		TinyGraphicManager& graphics,
		TinyRenderUniformManager& uniforms
	) );

	tiny_implement( void Draw(
		TinyGame* game,
		TinyGraphicBufferStaging& staging,
		TinyRenderUniformManager& uniforms,
		const TinyRenderSpriteContext& draw_context
	) );

	tiny_implement( void Terminate( ) );

protected:
	tiny_implement( tiny_uint UploadBuffers(
		TinyGraphicManager& graphics,
		TinyGraphicBufferStaging& staging,
		TinyRenderUniformManager& uniforms
	) );

private:
	void PushIndex( );

	void PushVertex( const TinyRenderSpriteContext& draw_context, tiny_uint texture_count );

};
