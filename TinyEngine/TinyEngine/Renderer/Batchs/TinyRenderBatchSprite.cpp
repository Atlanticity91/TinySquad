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
	_indexes{ },
	_vertex{ }
{ }

bool TinyRenderBatchSprite::Create( 
	TinyGraphicManager& graphics, 
	TinyRenderUniformManager& uniforms
) {
	return  TinyRenderBatchInstance::Create( graphics, uniforms )									 &&
			_indexes.Create( )																		 &&
			_vertex.Create( )																		 &&
			uniforms.Create( graphics, { TGB_TYPE_INDEX,  Index_t::Size , TinySpriteIndexBuffer  } ) &&
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
		_material == draw_context.Material &&
		_vertex.GetHasSpace( ) &&
		_textures.GetHasSpace( texture_count )
	) {
		PushIndex( );
		PushVertex( draw_context, texture_count );
		
		for ( auto& texture : draw_context.Textures )
			_textures.Push( { TRS_ID_TEXTURE, _textures.GetCount( ), tiny_lvalue( texture ) } );
	} else {
		auto& graphics = game->GetGraphics( );
		auto& assets = game->GetAssets( );

		Flush( assets, graphics, staging, uniforms );

		_material = draw_context.Material;

		Draw( game, staging, uniforms, draw_context );
	}
}

void TinyRenderBatchSprite::Terminate( ) {
	TinyRenderBatchInstance::Terminate( );

	_indexes.Terminate( );
	_vertex.Terminate( );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PROTECTED ===
////////////////////////////////////////////////////////////////////////////////////////////
tiny_uint TinyRenderBatchSprite::UploadBuffers(
	TinyGraphicManager& graphics,
	TinyGraphicBufferStaging& staging,
	TinyRenderUniformManager& uniforms
) {
	auto indexes = _indexes.Flush( );
	auto vertex  = _vertex.Flush( );
	
	if ( indexes.Count > 0 ) {
		auto* staging_addr = tiny_cast( staging.GetAccess( ), tiny_pointer );
		auto inst_size	   = indexes.Count * tiny_sizeof( TinyRenderSpriteIndex );
		auto vert_size	   = vertex.Count  * tiny_sizeof( TinyRenderSpriteVertex );
		auto context	   = graphics.GetContext( );

		staging.Map( context, inst_size + vert_size );
		Tiny::Memcpy( indexes.Values, staging_addr			  , inst_size );
		Tiny::Memcpy( vertex.Values , staging_addr + inst_size, vert_size );
		staging.UnMap( context );

		{
			auto burner = TinyGraphicBurner{ context, VK_QUEUE_TYPE_TRANSFER };

			VkBufferCopy copies[ 2 ] = {
				{ 0		   , 0, inst_size },
				{ inst_size, 0, vert_size }
			};

			burner.Upload( staging, uniforms[ TinySpriteIndexBuffer  ], copies[ 0 ] );
			burner.Upload( staging, uniforms[ TinySpriteVertexBuffer ], copies[ 1 ] );
		}
	}

	return indexes.Count;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE ===
////////////////////////////////////////////////////////////////////////////////////////////
void TinyRenderBatchSprite::PushIndex( ) {
	auto indexex = TinyRenderSpriteIndex{ };
	auto index   = tiny_cast( 6, tiny_uint );
	auto offset  = 6 * _indexes.GetCount( );

	while ( index-- > 0 )
		indexex.Index[ index ] += offset;

	_indexes.Push( indexex );
}

void TinyRenderBatchSprite::PushVertex(
	const TinyRenderSpriteContext& draw_context, 
	tiny_uint texture_count
) {
	auto vertex = TinyRenderSpriteVertex{ };
	auto slot   = tiny_cast( _textures.GetCount( ), float );
	auto count  = tiny_cast( tiny_cast( texture_count, tiny_int ), float );
	auto& uv	= draw_context.Sprite.UV;

	vertex.Quad[ 0 ].UV = { uv.x, uv.y, slot, count };
	vertex.Quad[ 1 ].UV = { uv.z, uv.y, slot, count };
	vertex.Quad[ 2 ].UV = { uv.z, uv.w, slot, count };
	vertex.Quad[ 3 ].UV = { uv.x, uv.w, slot, count };

	auto vertice = tiny_cast( 4, tiny_uint );

	while ( vertice-- > 0 ) {
		vertex.Quad[ vertice ].Position = draw_context.Tranform.World * vertex.Quad[ vertice ].Position;
		vertex.Quad[ vertice ].Color	= draw_context.Sprite.Color;
	}

	_vertex.Push( vertex );
}
