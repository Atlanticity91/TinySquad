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
	_vertex{ },
	_instance{ }
{ }

bool TinyRenderBatchSprite::Create( TinyGraphicManager& graphics ) {
	return  TinyRenderBatchInstance::Create( graphics ) &&
			_vertex.Create( )							&&
			_instance.Create( );
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
		PushVertex( draw_context );
		PushInstance( draw_context, texture_count );
		
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

	_vertex.Terminate( );
	_instance.Terminate( );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PROTECTED ===
////////////////////////////////////////////////////////////////////////////////////////////
tiny_uint TinyRenderBatchSprite::UploadBuffers(
	TinyGraphicManager& graphics,
	TinyGraphicBufferStaging& staging,
	TinyRenderUniformManager& uniforms
) {
	auto vertex   = _vertex.Flush( );
	auto instance = _instance.Flush( );
	
	if ( vertex.Count > 0 ) {
		auto* staging_addr = tiny_cast( staging.GetAccess( ), tiny_pointer );
		auto vert_size	   = vertex.Count   * tiny_sizeof( TinyRenderSpriteVertex );
		auto inst_size	   = instance.Count * tiny_sizeof( TinyRenderSpriteInstance );
		auto context	   = graphics.GetContext( );

		staging.Map( context, vert_size + inst_size );
		Tiny::Memcpy( vertex.Values  , staging_addr			   , vert_size );
		Tiny::Memcpy( instance.Values, staging_addr + vert_size, inst_size );
		staging.UnMap( context );

		{
			auto burner = TinyGraphicBurner{ context, VK_QUEUE_TYPE_TRANSFER };

			VkBufferCopy copies[ 2 ] = {
				{ 0		   , 0, vert_size },
				{ vert_size, 0, inst_size }
			};

			burner.Upload( staging, uniforms.GetUniform( "ubo_transforms" ), copies[ 0 ] );
			burner.Upload( staging, uniforms.GetUniform( "ubo_sprites" ), copies[ 1 ] );
		}
	}

	return vertex.Count;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE ===
////////////////////////////////////////////////////////////////////////////////////////////
void TinyRenderBatchSprite::PushVertex( const TinyRenderSpriteContext& draw_context ) {
	auto vertex = TinyRenderSpriteVertex{ };
	auto& uv	= draw_context.Sprite.UV;

	vertex.Quad[ 0 ] = { { -.5f, -.5f, .0f, 1.f }, { uv.x, uv.y } };
	vertex.Quad[ 1 ] = { {  .5f, -.5f, .0f, 1.f }, { uv.z, uv.y } };
	vertex.Quad[ 2 ] = { {  .5f,  .5f, .0f, 1.f }, { uv.z, uv.w } };
	vertex.Quad[ 3 ] = { { -.5f,  .5f, .0f, 1.f }, { uv.x, uv.w } };

	auto vertice = tiny_cast( 4, tiny_uint );

	while ( vertice-- > 0 )
		vertex.Quad[ vertice ].Position = draw_context.Tranform.World * vertex.Quad[ vertice ].Position;

	_vertex.Push( vertex );
}

void TinyRenderBatchSprite::PushInstance(
	const TinyRenderSpriteContext& draw_context,
	tiny_uint texture_count 
) {
	auto instance = TinyRenderSpriteInstance{ };

	Tiny::Memcpy( tiny_rvalue( draw_context.Tranform ), tiny_rvalue( instance.Transform ), 1 );

	instance.Color = draw_context.Sprite.Color;
	instance.TextureSlot = _textures.GetCount( );
	instance.TextureCount = texture_count;

	_instance.Push( instance );
}
