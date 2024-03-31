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
 * @creation : 19/11/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "PostProcess/TinyRenderPostProcessor.h"

te_class TinyRenderer final {

	using Callback_t = TinyRenderBatchManager::Callback_t;

private:
	TinyRenderCameraManager  _cameras;
	TinyRenderUniformManager _uniforms;
	TinyRenderBatchManager   _batchs;
	TinyRenderDebugManager	 _debug;
	TinyRenderPostProcessor  _post_process;

public:
	TinyRenderer( );

	~TinyRenderer( ) = default;

	bool Initialize( TinyGraphicManager& graphics, TinyFilesystem filesystem );

	TinyMaterialBuilder CreateMaterial( 
		TinyGame* game, 
		const tiny_string& pass_name, 
		tiny_uint subpass 
	);

	tiny_inline TinyRenderProjection& CreateProjection( const tiny_string& alias );

	tiny_inline void RemoveProjection( const tiny_string& alias );

	tiny_inline void RemoveProjection( const tiny_hash hash );

	tiny_inline TinyRenderCamera& CreateCamera( const tiny_string& entity_name );

	tiny_inline TinyRenderCamera& CreateCamera(
		const tiny_string& entity_name,
		const tiny_string& projection
	);

	tiny_inline void RemoveCamera( const tiny_string& entity_name );

	tiny_inline void RemoveCamera( const tiny_hash entity_hash );

	tiny_inline void ReCalculate( );

	tiny_inline void ReCalculate( const tiny_hash entity_hash );

	tiny_inline void ReCalculateCurrent( );

	tiny_inline void SetDebugLineWidth( float width );

	tiny_inline void Prepare( TinyGraphicManager& graphics );

	tiny_inline void Prepare(
		TinyGame* game, 
		TinyRenderBatchTypes type,
		const tiny_string& render_pass,
		Callback_t callback
	);

	tiny_inline void Prepare( 
		TinyGame* game,
		TinyRenderBatchTypes type,
		const tiny_hash render_pass,
		Callback_t callback
	);

	tiny_inline void Draw( TinyGame* game, const TinyRenderSpriteContext& draw_context );

	tiny_inline void Draw( TinyGame* game, const TinyRenderVertexContext& draw_context );

	tiny_inline void Draw( TinyGame* game, const TinyRenderLightContext& draw_context );

	tiny_inline void Draw( TinyGame* game, const TinyRenderTextContext& draw_context );

	tiny_inline void Flush( TinyGame* game, TinyRenderBatchTypes type );

	tiny_inline void DrawDebug( const TinyRenderDebugPrimitive& primitive );

	void Compose( TinyGame* game);

	void Terminate( TinyGraphicManager& graphics );

private:
	void PushShaderMacros( TinyGraphicManager& graphics );

public:
	TinyRenderCameraManager& GetCameras( );
	
	TinyRenderUniformManager& GetUniforms( );

	TinyRenderBatchManager& GetBatchs( );

	TinyRenderPostProcessor& GetPostProcess( );

	tiny_inline TinyGraphicBufferStaging& GetStaging( );

	tiny_inline bool FindProjection( const tiny_string& alias ) const;

	tiny_inline bool FindProjection( const tiny_hash hash ) const;

	tiny_inline bool FindCamera( const tiny_string& entity_name ) const;

	tiny_inline bool FindCamera( const tiny_hash entity_hash ) const;

	tiny_inline TinyRenderProjection& GetProjection( const tiny_string& alias );

	tiny_inline const TinyRenderProjection& GetProjection( const tiny_string& alias ) const;

	tiny_inline TinyRenderProjection& GetProjection( const tiny_hash hash );

	tiny_inline const TinyRenderProjection& GetProjection( const tiny_hash hash ) const;

	tiny_inline TinyRenderCamera& GetCamera( const tiny_string& entity_name );

	tiny_inline const TinyRenderCamera& GetCamera( const tiny_string& entity_name ) const;

	tiny_inline TinyRenderCamera& GetCamera( const tiny_hash entity_hash );

	tiny_inline const TinyRenderCamera& GetCamera( const tiny_hash entity_hash ) const;

	tiny_inline TinyRenderProjection& GetCurrentProjection( );

	tiny_inline const TinyRenderProjection& GetCurrentProjection( ) const;

	tiny_inline TinyRenderCamera& GetCurrentCamera( );

	tiny_inline const TinyRenderCamera& GetCurrentCamera( ) const;

	tiny_inline const tiny_mat4& GetCameraMatrix( ) const;

	tiny_inline float GetDebugLineWidth( ) const;

};
