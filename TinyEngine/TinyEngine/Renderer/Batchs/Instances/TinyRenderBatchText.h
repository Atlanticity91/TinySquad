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

#pragma once

#include "TinyRenderBatchVertex.h"

te_class TinyRenderBatchText final
	: tiny_inherit( TinyRenderBatchInstance<TinyRenderTextContext> ) {

public:
	using Parameters_t = TinyRenderBatch<TinyRenderTextParameters, TinyMaxFonts>;
	using Texture_t	   = TinyRenderBatch<VkDescriptorImageInfo, TinyMaxFonts>;
	using Vertex_t	   = TinyRenderBatch<TinyRenderTextVertex, TINY_MAX_VERTEX>;

	static const tiny_uint Size = Vertex_t::Size + Parameters_t::Size;

private:
	Texture_t m_textures;
	Vertex_t m_vertex;
	Parameters_t m_parameters;

public:
	TinyRenderBatchText( );

	~TinyRenderBatchText( ) = default;
	
	tiny_implement( bool Create(
		TinyGraphicManager& graphics,
		TinyRenderUniformManager& uniforms
	) );

	tiny_implement( void Draw(
		TinyGame* game,
		TinyGraphicBufferStaging& staging,
		TinyRenderUniformManager& uniforms,
		const TinyRenderTextContext& draw_context
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
	tiny_uint PushTexture( TinyFont* font );

	void PushVertex( 
		const TinyRenderTextContext & draw_context, 
		TinyFont* font,
		tiny_uint font_id 
	);

	void PushParameters( 
		const TinyRenderTextContext& draw_context,
		TinyFont* font,
		tiny_uint font_id
	);

};
