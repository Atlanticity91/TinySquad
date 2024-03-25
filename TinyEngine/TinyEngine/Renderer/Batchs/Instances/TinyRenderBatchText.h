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
	using Vertex_t = TinyRenderBatch<TinyRenderTextVertex, TINY_MAX_VERTEX>;

	static const tiny_uint Size = Vertex_t::Size + tiny_sizeof( TinyRenderTextParameters );

private:
	tiny_uint					 _instance;
	Vertex_t					 _vertex;
	TinyRenderTextParameters	 _parameters;
	TinyGraphicPipelineBindpoint _texture;

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
		const TinyRenderTextContext & draw_context
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

};
