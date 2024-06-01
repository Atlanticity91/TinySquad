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

#define TinySpriteVertexBuffer "vb_sprite"

te_class TinyRenderBatchSprite final 
	: tiny_inherit( TinyRenderBatchInstance<TinyRenderSpriteContext> )
{

public:
	using Texture_t = TinyRenderBatch<VkDescriptorImageInfo, TINY_MAX_VERTEX>;
	using Vertex_t  = TinyRenderBatch<TinyRenderSpriteVertex, TINY_MAX_VERTEX>;

	static const tiny_uint Size = Vertex_t::Size;

private:
	tiny_uint m_max_texture_slots;
	Texture_t m_textures;
	Vertex_t m_vertex;

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

	tiny_implement( void OnFlush(
		TinyGraphicWorkContext& work_context,
		TinyMaterial& material
	) );

private:
	tiny_uint PushTextures( const tiny_list<TinyTexture2D*>&textures );

	void PushVertex(
		const TinyRenderSpriteContext& draw_context, 
		tiny_uint texture_slot,
		tiny_uint texture_count 
	);

};
