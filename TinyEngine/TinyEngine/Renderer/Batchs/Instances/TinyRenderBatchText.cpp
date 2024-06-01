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
#define ParamUniform "u_textm_parameters"

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyRenderBatchText::TinyRenderBatchText( )
	: TinyRenderBatchInstance{ },
	m_textures{ },
	m_vertex{ }, 
	m_parameters{ }
{ }

bool TinyRenderBatchText::Create(
	TinyGraphicManager& graphics,
	TinyRenderUniformManager& uniforms
) {
	return  m_textures.Create( )																				  &&
			m_vertex.Create( )																					  &&
			m_parameters.Create( )																				  &&
			uniforms.Create( graphics, { TGB_TYPE_VERTEX , Vertex_t::Size	 , TextVertex					  } ) &&
			uniforms.Create( graphics, { TGB_TYPE_UNIFORM, Parameters_t::Size, ParamUniform, TRS_ID_RENDER, 0 } );
}

void TinyRenderBatchText::Draw(
	TinyGame* game,
	TinyGraphicBufferStaging& staging,
	TinyRenderUniformManager& uniforms,
	const TinyRenderTextContext& draw_context
) {
	auto char_count = draw_context.Text.length( );
	auto& assets	= game->GetAssets( );

	if ( 
		m_material == draw_context.Material && 
		m_vertex.GetHasSpace( char_count )
	) {
		auto* font   = assets.GetAssetAs<TinyFont>( draw_context.Font );
		auto font_id = PushTexture( font );

		PushVertex( draw_context, font, font_id );
		PushParameters( draw_context, font, font_id );
	} else {
		auto& graphics = game->GetGraphics( );

		Flush( assets, graphics, staging, uniforms );

		m_material = draw_context.Material;

		Draw( game, staging, uniforms, draw_context );
	}
}

void TinyRenderBatchText::Terminate( ) { 
	m_textures.Terminate( );
	m_vertex.Terminate( ); 
	m_parameters.Terminate( );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PROTECTED ===
////////////////////////////////////////////////////////////////////////////////////////////
tiny_uint TinyRenderBatchText::UploadBuffers(
	TinyGraphicManager& graphics,
	TinyGraphicBufferStaging& staging,
	TinyRenderUniformManager& uniforms
) {
	auto vertex		= m_vertex.Flush( );
	auto parameters = m_parameters.Flush( );

	if ( vertex.Count > 0 ) {
		auto graphic    = graphics.GetWrapper( );
		auto param_size = parameters.Count * tiny_sizeof( TinyRenderTextParameters );
		auto vert_size  = vertex.Count	   * tiny_sizeof( TinyRenderTextVertex );

		staging.Map( graphic, vert_size + param_size );

		auto* staging_addr = tiny_cast( staging.GetAccess( ), tiny_pointer );

		Tiny::Memcpy( vertex.Values	   , staging_addr			 , vert_size  );
		Tiny::Memcpy( parameters.Values, staging_addr + vert_size, param_size );

		staging.UnMap( graphic );

		{
			auto burner = TinyGraphicBurner{ graphic, VK_QUEUE_TYPE_TRANSFER };

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
	auto textures = m_textures.Flush( );

	material.Bind( work_context, TRS_ID_TEXTURE, 0, textures.Count, tiny_cast( textures.Values, VkDescriptorImageInfo* ) );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE ===
////////////////////////////////////////////////////////////////////////////////////////////
tiny_uint TinyRenderBatchText::PushTexture( TinyFont* font ) {
	auto* textures = tiny_cast( m_textures.GetData( ), VkDescriptorImageInfo* );
	auto font_id   = m_textures.GetCount( );
	auto texture   = font->GetTexure( );

	while ( font_id-- > 0 ) {
		if (
			texture.sampler   == textures[ font_id ].sampler && 
			texture.imageView == textures[ font_id ].imageView 
		)
			continue;

		break;
	}

	if ( font_id > m_textures.GetCount( ) )
		m_textures.Push( texture );

	return font_id;
}

void TinyRenderBatchText::PushVertex(
	const TinyRenderTextContext& draw_context,
	TinyFont* font,
	tiny_uint font_id
) {
	auto char_id  = draw_context.Text.length( );
	auto* text	  = draw_context.Text.get( );
	auto vertex   = TinyRenderTextVertex{ };
	auto location = tiny_vec3{ draw_context.Location, 0.f };
	auto scale	  = tiny_vec3{ draw_context.Size, draw_context.Size, 1.f };

	while ( char_id-- > 0 ) {
		auto char_ = tiny_lvalue( text + char_id );

		if ( char_ != '\n' && char_ != '\r' ) {
			auto& geometry = font->GetGeometry( char_ );
			auto vertex_id = TinyQuadVerticeCount;
			auto transform = glm::translate( location ) * glm::scale( scale );

			while ( vertex_id-- > 0 ) {
				vertex.Vertices[ vertex_id ].Location   = transform * geometry.Vertices[ vertex_id ].Location;
				vertex.Vertices[ vertex_id ].UV			= geometry.Vertices[ vertex_id ].UV;
				vertex.Vertices[ vertex_id ].Parameters = font_id;
			}

			m_vertex.Push( vertex );

			location.x += geometry.Advance;
		}
		
		location.y += draw_context.Size;
	}
}

void TinyRenderBatchText::PushParameters( 
	const TinyRenderTextContext& draw_context,
	TinyFont* font,
	tiny_uint font_id
) {
	auto parameters = TinyRenderTextParameters{ };
	auto* src		= tiny_rvalue( draw_context.Background );
	auto* dst		= tiny_rvalue( parameters.Background );

	Tiny::Memcpy( src, dst, 2 * tiny_sizeof( tiny_vec4 ) );

	parameters.Range = font->GetRange( ); 
	parameters.Miter = font->GetMiter( );
	parameters.Font  = font_id;

	m_parameters.Push( parameters );
}
