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
 * @creation : 26/11/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "TinyRenderBatch.h"

typedef std::function<void(
	TinyGraphicManager&,
	TinyAssetManager&,
	TinyRenderUniformManager&,
	class TinyRenderBatchManager&
)> FlushMethod_t;

te_struct TinyRenderFlushContext {

	TinyAsset Material;
	FlushMethod_t Flush;

};

te_class TinyRenderBatchManager final {

public:
	using BatchTransform_t = TinyRenderBatch<TinyRenderTransform, TinyMaxVertices>;
	using BatchIndex_t	   = TinyRenderBatch<TinyRenderIndex, TinyMaxVertices>;
	using BatchVertex_t	   = TinyRenderBatch<TinyRenderVertice, TinyMaxVertices>;
	using BatchSprite_t	   = TinyRenderBatch<TinyRenderSprite, TinyMaxVertices>;
	using BatchTexture_t   = TinyRenderBatch<TinyGraphicPipelineBindpoint, TinyMaxVertices>;
	using BatchLight_t	   = TinyRenderBatch<TinyRenderLight, TinyMaxLight>;

private:
	tiny_hash				 _render_pass;
	TinyGraphicBufferStaging _staging;
	BatchTransform_t		 _transforms;
	BatchIndex_t			 _indexes;
	BatchVertex_t			 _vertices;
	BatchSprite_t			 _sprites;
	BatchTexture_t			 _textures;
	BatchLight_t			 _lights;
	TinyRenderFlushContext   _flush_context;

public:
	TinyRenderBatchManager( );

	~TinyRenderBatchManager( ) = default;

	bool Initialize( TinyGraphicManager& graphics );

	void Prepare( TinyGame* game, const tiny_hash render_pass, FlushMethod_t flush_method );

	void Draw( TinyGame* game, const TinyRenderSpriteContext& draw_context );

	void Draw( TinyGame* game, const TinyRenderVertexContext& draw_context );

	void Draw( TinyGame* game, const TinyRenderLightContext& draw_context );

	void Draw( TinyGame* game, const TinyRenderTextContext& draw_context );

	tiny_array<VkBufferCopy, 2> Flush2D( 
		TinyGraphicContext& context, 
		tiny_uint& vertex_count
	);

	tiny_array<VkBufferCopy, 2> Flush3D(
		TinyGraphicContext& context,
		tiny_uint& index_count, 
		tiny_uint& vertex_count 
	);

	tiny_inline TinyRenderBatchFlush FlushTextures( );

	VkBufferCopy FlushLight( TinyGraphicContext& context );

	void Flush( TinyGame* game );

	void Terminate( TinyGraphicManager& graphics );

public:
	TinyGraphicBufferStaging& GetStaging( );

	BatchTransform_t& GetTransforms( );

	BatchIndex_t& GetIndexes( );

	BatchVertex_t& GetVertex( );

	BatchSprite_t& GetSprites( );

	BatchTexture_t& GetTextures( );

	BatchLight_t& GetLight( );

	TinyMaterial* GetMaterial( TinyAssetManager& assets );

};
