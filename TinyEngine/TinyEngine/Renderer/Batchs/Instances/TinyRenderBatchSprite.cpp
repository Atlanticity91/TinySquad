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

#include <TinyEngine/__tiny_engine_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyRenderBatchSprite::TinyRenderBatchSprite( )
	: TinyRenderBatchInstance{ },
	m_max_texture_slots{ 0 },
	m_textures{ },
	m_vertex{ }
{ }

bool TinyRenderBatchSprite::Create( 
	TinyGraphicManager& graphics, 
	TinyRenderUniformManager& uniforms
) {
	auto& physical = graphics.GetPhysical( );
	auto& limits   = physical.GetLimits( );

	auto image_count   = limits.maxPerStageDescriptorSampledImages;
	auto sampler_count = limits.maxPerStageDescriptorSamplers;

	m_max_texture_slots = image_count < sampler_count ? image_count : sampler_count;

	return  m_textures.Create( ) &&
			m_vertex.Create( )	&&
			uniforms.Create( graphics, { TGB_TYPE_VERTEX, Vertex_t::Size, TinySpriteVertexBuffer } );
}

void TinyRenderBatchSprite::Draw(
	TinyGame* game,
	TinyGraphicBufferStaging& staging,
	TinyRenderUniformManager& uniforms,
	const TinyRenderSpriteContext& draw_context
) {
	auto texture_count = draw_context.Textures.size( );

	if (
		m_material == draw_context.Material &&
		m_vertex.GetHasSpace( )			   &&
		m_textures.GetHasSpace( texture_count )
	) {
		auto texture_slot = PushTextures( draw_context.Textures );

		PushVertex( draw_context, texture_slot, texture_count );
	} else {
		auto& graphics = game->GetGraphics( );
		auto& assets = game->GetAssets( );

		Flush( assets, graphics, staging, uniforms );

		m_material = draw_context.Material;

		Draw( game, staging, uniforms, draw_context );
	}
}

void TinyRenderBatchSprite::Terminate( ) {
	m_textures.Terminate( );
	m_vertex.Terminate( );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PROTECTED ===
////////////////////////////////////////////////////////////////////////////////////////////
tiny_uint TinyRenderBatchSprite::UploadBuffers(
	TinyGraphicManager& graphics,
	TinyGraphicBufferStaging& staging,
	TinyRenderUniformManager& uniforms
) {
	auto vertex  = m_vertex.Flush( );
	
	if ( vertex.Count > 0 ) {
		auto graphic = graphics.GetWrapper( );
		auto size	 = vertex.Count  * tiny_sizeof( TinyRenderSpriteVertex );

		staging.Map( graphic, size );

		auto* dst = staging.GetAccess( );

		Tiny::Memcpy( vertex.Values, dst, size );

		staging.UnMap( graphic );

		{
			auto burner = TinyGraphicBurner{ graphic, VK_QUEUE_TYPE_TRANSFER };
			auto copie  = VkBufferCopy{ 0, 0, size };

			burner.Upload( staging, uniforms[ TinySpriteVertexBuffer ], copie );
		}
	}

	return vertex.Count;
}

void TinyRenderBatchSprite::OnFlush(
	TinyGraphicWorkContext& work_context,
	TinyMaterial& material
) {
	auto textures = m_textures.Flush( );

	material.Bind( work_context, TRS_ID_TEXTURE-1, 0, textures.Count, tiny_cast( textures.Values, VkDescriptorImageInfo* ) );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE ===
////////////////////////////////////////////////////////////////////////////////////////////
tiny_uint TinyRenderBatchSprite::PushTextures( const tiny_list<TinyTexture2D*>& textures ) {
	auto& texture = tiny_lvalue( textures[ 0 ] );
	auto* slots   = tiny_cast( m_textures.GetData( ), TinyTexture2D* );
	auto slot	  = m_textures.GetCount( );

	while ( slot-- > 0 ) {
		if ( texture != slots + slot )
			continue;

		break;
	}

	if ( slot > m_textures.GetCount( ) ) {
		slot = m_textures.GetCount( );

		for ( auto& texture : textures ) {
			auto descriptor = tiny_lvalue( texture->GetDescriptor( ) );

			m_textures.Push( descriptor );
		}
	}

	return slot;
}

void TinyRenderBatchSprite::PushVertex(
	const TinyRenderSpriteContext& draw_context, 
	tiny_uint texture_slot,
	tiny_uint texture_count
) {
	auto vertex = TinyRenderSpriteVertex{ };
	auto slot   = tiny_cast( tiny_cast( texture_slot , tiny_int ), float );
	auto count  = tiny_cast( tiny_cast( texture_count, tiny_int ), float );
	auto& uv	= draw_context.Sprite.UV;

	vertex.Quad[ 0 ].Position = draw_context.Tranform * TinyQuadVertex[ 0 ];
	vertex.Quad[ 0 ].Texture  = { uv.x, uv.y, slot, count };
	vertex.Quad[ 0 ].Color	  = draw_context.Sprite.Color;

	vertex.Quad[ 1 ].Position = draw_context.Tranform * TinyQuadVertex[ 1 ];
	vertex.Quad[ 1 ].Texture  = { uv.z, uv.y, slot, count };
	vertex.Quad[ 1 ].Color	  = draw_context.Sprite.Color;

	vertex.Quad[ 2 ].Position = draw_context.Tranform * TinyQuadVertex[ 2 ];
	vertex.Quad[ 2 ].Texture  = { uv.z, uv.w, slot, count };
	vertex.Quad[ 2 ].Color	  = draw_context.Sprite.Color;

	vertex.Quad[ 3 ].Position = draw_context.Tranform * TinyQuadVertex[ 3 ];
	vertex.Quad[ 3 ].Texture  = { uv.x, uv.w, slot, count };
	vertex.Quad[ 3 ].Color	  = draw_context.Sprite.Color;

	m_vertex.Push( vertex );
}
