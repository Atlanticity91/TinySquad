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
 * @creation : 21/03/2024
 * @version  : 2024.2.7
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#include <TinyEngine/__tiny_engine_pch.h>

#define TextVertex "vb_text"
#define ParamUniform "u_text_parameters"

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyRenderBatchText::TinyRenderBatchText( )
	: TinyRenderBatchInstance{ },
	_instance{ 0 },
	_vertex{ }, 
	_parameters{ },
	_texture{ }
{ }

bool TinyRenderBatchText::Create(
	TinyGraphicManager& graphics,
	TinyRenderUniformManager& uniforms
) {
	return  _vertex.Create( )															 &&
			uniforms.Create( graphics, { TGB_TYPE_VERTEX, Vertex_t::Size, TextVertex } ) &&
			uniforms.Create( graphics, { TGB_TYPE_UNIFORM, tiny_sizeof( TinyRenderTextParameters ), ParamUniform, TRS_ID_RENDER, 0 } );
}

void TinyRenderBatchText::Draw(
	TinyGame* game,
	TinyGraphicBufferStaging& staging,
	TinyRenderUniformManager& uniforms,
	const TinyRenderTextContext& draw_context
) {
	auto& assets = game->GetAssets( );
	auto* font	 = assets.GetAssetAs<TinyFont>( draw_context.Font );
	auto char_id = draw_context.Text.length( );

	if ( 
		_material == draw_context.Font && 
		_vertex.GetHasSpace( char_id )
	) {
		while ( char_id-- > 0 ) {
			/*
			auto& geometry = font->GetGeometry( draw_context.Text[ char_id ] );

			for ( auto& vertice : geometry.Vertices )
				_vertex.Push( { vertice.Location, vertice.UV, _instance } );
			*/
		}

		_instance += 1;
	} else {
		auto& graphics = game->GetGraphics( );

		Flush( assets, graphics, staging, uniforms );

		_material = draw_context.Font;
		//_texture = font->GetTexure( );

		Draw( game, staging, uniforms, draw_context );
	}
}

void TinyRenderBatchText::Terminate( ) { _vertex.Terminate( ); }

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PROTECTED ===
////////////////////////////////////////////////////////////////////////////////////////////
tiny_uint TinyRenderBatchText::UploadBuffers(
	TinyGraphicManager& graphics,
	TinyGraphicBufferStaging& staging,
	TinyRenderUniformManager& uniforms
) {
	auto vertex = _vertex.Flush( );

	if ( vertex.Count > 0 ) {
		auto context	= graphics.GetContext( );
		auto param_size = tiny_sizeof( TinyRenderTextParameters );
		auto vert_size  = vertex.Count * tiny_sizeof( TinyRenderTextVertex );

		staging.Map( context, vert_size + param_size );

		auto* staging_addr = tiny_cast( staging.GetAccess( ), tiny_pointer );

		Tiny::Memcpy( vertex.Values			   , staging_addr			 , vert_size  );
		Tiny::Memcpy( tiny_rvalue( _parameters), staging_addr + vert_size, param_size );

		staging.UnMap( context );

		{
			auto burner = TinyGraphicBurner{ context, VK_QUEUE_TYPE_TRANSFER };

			VkBufferCopy copies[ 2 ] = {
				{ 0		   , 0, vert_size  },
				{ vert_size, 0, param_size }
			};

			burner.Upload( staging, uniforms[ TextVertex   ], copies[ 0 ] );
			burner.Upload( staging, uniforms[ ParamUniform ], copies[ 1 ] );
		}
	}

	return vertex.Count;
}

void TinyRenderBatchText::OnFlush(
	TinyGraphicWorkContext& work_context,
	TinyMaterial& material
) {
	material.Bind( work_context, _texture );
}
