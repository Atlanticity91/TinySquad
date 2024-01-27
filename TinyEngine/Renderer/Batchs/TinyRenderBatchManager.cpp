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
	_transforms{ },
	_indexes{ },
	_vertices{ },
	_uvs{ },
	_sprites{ },
	_textures{ },
	_lights{ },
	_flush_context{ }
{ }

bool TinyRenderBatchManager::Initialize( TinyGraphicContext& context ) {
	constexpr auto size_2d = BatchTransform_t::Size + BatchSprite_t::Size;
	constexpr auto size_3d = BatchIndex_t::Size + BatchVertex_t::Size + BatchUV_t::Size;
	constexpr auto size	   = size_2d < size_3d ? size_3d : size_2d;

	auto state = _staging.Create( context, size ) &&
				 _transforms.Create( )			  &&
				 _indexes.Create( )				  &&
				 _vertices.Create( )			  &&
				 _uvs.Create()					  &&
				 _sprites.Create( )				  &&
				 _textures.Create( );

	if ( state ) {
		auto& properties = context.Physical.GetProperties( );

		_textures.SetCapacity( properties.limits.maxDescriptorSetSamplers );
	}

	return state;
}

void TinyRenderBatchManager::Prepare( TinyGame* game, FlushMethod_t flush_method ) {
	Flush( game );

	_flush_context.Flush = flush_method;
}

void TinyRenderBatchManager::Draw(
	TinyGame* game,
	const TinyRenderDraw2DContext& draw_context
) {
	auto texture_count = draw_context.Textures.size( );

	if ( 
		draw_context.Material == _flush_context.Material &&
		_transforms.GetHasSpace( )						 &&
		_textures.GetHasSpace( texture_count )
	) {
		_transforms.Push( draw_context.Tranform );
		_sprites.Push( draw_context.Sprite );

		for ( auto& texture : draw_context.Textures )
			_textures.Push( { TINY_RENDER_SET_TEXTURE, _textures.GetCount( ), tiny_lvalue( texture ) } );
	} else {
		Flush( game );

		_flush_context.Material = draw_context.Material;

		Draw( game, draw_context );
	}
}

void TinyRenderBatchManager::Draw(
	TinyGame* game,
	const TinyRenderDraw3DContext& draw_context
) {
	auto texture_count = draw_context.Textures.size( );

	if (
		draw_context.Material == _flush_context.Material &&
		_textures.GetHasSpace( texture_count )
	) {
		_indexes.Push( draw_context.Indexes );
		_vertices.Push( draw_context.Vertices );
		_uvs.Push( draw_context.Uvs );

		for ( auto& texture : draw_context.Textures )
			_textures.Push( { TINY_RENDER_SET_TEXTURE, _textures.GetCount( ), tiny_lvalue( texture ) } );
	} else {
		Flush( game );

		_flush_context.Material = draw_context.Material;

		Draw( game, draw_context );
	}
}

tiny_array<VkBufferCopy, 2> TinyRenderBatchManager::Flush2D(
	TinyGraphicContext& context,
	tiny_uint& vertex_count
) {
	auto copy_destination = tiny_array<VkBufferCopy, 2>{ };
	auto transform		  = _transforms.Flush( );
	auto sprites		  = _sprites.Flush( );

	vertex_count = transform.Count;

	if ( vertex_count > 0 ) {
		auto tr_size = transform.Count * tiny_sizeof( TinyRenderTransform );
		auto sp_size = sprites.Count * tiny_sizeof( TinyRenderSprite );

		_staging.Map( context, tr_size + sp_size );
		Tiny::Memcpy( transform.Values, _staging.GetAccess( ), tr_size );
		Tiny::Memcpy( sprites.Values, tiny_cast( tiny_cast( _staging.GetAccess( ), tiny_ptr ) + tr_size, c_pointer ), sp_size );
		_staging.UnMap( context );

		copy_destination[ 0 ] = { 0, 0, tr_size };
		copy_destination[ 1 ] = { tr_size, 0, sp_size };
	}

	return copy_destination;
}

tiny_array<VkBufferCopy, 3> TinyRenderBatchManager::Flush3D(
	TinyGraphicContext& context,
	tiny_uint& index_count, 
	tiny_uint& vertex_count
) {
	auto copy_destination = tiny_array<VkBufferCopy, 3>{ };
	auto indexes		  = _indexes.Flush( );
	auto vertices		  = _vertices.Flush( );
	auto uvs			  = _uvs.Flush( );

	index_count  = indexes.Count;
	vertex_count = vertices.Count;

	if ( index_count > 0 || vertex_count > 0 ) {
		_staging.Map( context, 0 );
		//Tiny::Memcpy( );
		//Tiny::Memcpy( );
		//Tiny::Memcpy( );
		_staging.UnMap( context );

		copy_destination[ 0 ] = { 0, 0, 0 };
		copy_destination[ 1 ] = { 0, 0, 0 };
		copy_destination[ 2 ] = { 0, 0, 0 };
	}

	return copy_destination;
}

TinyRenderBatchFlush TinyRenderBatchManager::FlushTextures( ) {
	return _textures.Flush( );
}

VkBufferCopy TinyRenderBatchManager::FlushLight( TinyGraphicContext& context ) {
	auto lights		= _lights.Flush( );
	auto light_size = lights.Count * tiny_sizeof( TinyRenderLight );

	_staging.Map( context, light_size );
	Tiny::Memcpy( lights.Values, _staging.GetAccess( ), light_size );
	_staging.UnMap( context );

	return VkBufferCopy{ 0, 0, light_size };
}

void TinyRenderBatchManager::Flush( TinyGame* game ) {
	if ( _flush_context.Flush && _flush_context.Material ) {
		auto& graphics = game->GetGraphics( );
		auto& assets   = game->GetAssets( );
		auto& uniforms = game->GetRenderer( ).GetUniforms( );
	
		std::invoke( _flush_context.Flush, graphics, assets, uniforms, tiny_self );
	}
}

void TinyRenderBatchManager::Terminate( TinyGraphicContext& context ) {
	_staging.Terminate( context );
	_transforms.Terminate( );
	_indexes.Terminate( );
	_vertices.Terminate( );
	_uvs.Terminate( );
	_sprites.Terminate( );
	_textures.Terminate( );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyGraphicBufferStaging& TinyRenderBatchManager::GetStaging( ) { return _staging; }

TinyRenderBatchManager::BatchTransform_t& TinyRenderBatchManager::GetTransforms( ) {
	return _transforms;
}

TinyRenderBatchManager::BatchIndex_t& TinyRenderBatchManager::GetIndexes( ) {
	return _indexes;
}

TinyRenderBatchManager::BatchVertex_t& TinyRenderBatchManager::GetVertices( ) {
	return _vertices;
}

TinyRenderBatchManager::BatchUV_t& TinyRenderBatchManager::GetUVs( ) { return _uvs; }

TinyRenderBatchManager::BatchSprite_t& TinyRenderBatchManager::GetSprites( ) {
	return _sprites;
}

TinyRenderBatchManager::BatchTexture_t& TinyRenderBatchManager::GetTextures( ) {
	return _textures;
}

TinyMaterial* TinyRenderBatchManager::GetMaterial( TinyAssetManager& assets ) {
	return assets.GetAssetAs<TinyMaterial>( _flush_context.Material );
}
