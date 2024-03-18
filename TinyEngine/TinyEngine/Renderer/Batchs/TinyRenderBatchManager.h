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

#include "TinyRenderDrawContext.h"

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
	using BatchTransform_t = TinyRenderBatch<TinyRenderTransform, TINY_MAX_INSTANCE>;
	using BatchIndex_t	   = TinyRenderBatch<TinyRenderIndex, TINY_MAX_INDEX>;
	using BatchVertex_t	   = TinyRenderBatch<TinyRenderVertex, TINY_MAX_VERTICES>;
	using BatchUV_t		   = TinyRenderBatch<TinyRenderUV, TINY_MAX_VERTICES>;
	using BatchSprite_t	   = TinyRenderBatch<TinyRenderSprite, TINY_MAX_INSTANCE>;
	using BatchTexture_t   = TinyRenderBatch<TinyGraphicPipelineBindpoint, TINY_MAX_INSTANCE>;
	using BatchLight_t	   = TinyRenderBatch<TinyRenderLight, TINY_MAX_LIGHT>;

private:
	tiny_hash				 _render_pass;
	TinyGraphicBufferStaging _staging;
	BatchTransform_t		 _transforms;
	BatchIndex_t			 _indexes;
	BatchVertex_t			 _vertices;
	BatchUV_t				 _uvs;
	BatchSprite_t			 _sprites;
	BatchTexture_t			 _textures;
	BatchLight_t			 _lights;
	TinyRenderFlushContext   _flush_context;

public:
	TinyRenderBatchManager( );

	~TinyRenderBatchManager( ) = default;

	bool Initialize( TinyGraphicManager& graphics );

	void Prepare( TinyGame* game, const tiny_hash render_pass, FlushMethod_t flush_method );

	void Draw( TinyGame* game, const TinyRenderDraw2DContext& draw_context );

	void Draw( TinyGame* game, const TinyRenderDraw3DContext& draw_context );

	tiny_array<VkBufferCopy, 2> Flush2D( 
		TinyGraphicContext& context, 
		tiny_uint& vertex_count
	);

	tiny_array<VkBufferCopy, 3> Flush3D(
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

	BatchVertex_t& GetVertices( );

	BatchUV_t& GetUVs( );

	BatchSprite_t& GetSprites( );

	BatchTexture_t& GetTextures( );

	TinyMaterial* GetMaterial( TinyAssetManager& assets );

};
