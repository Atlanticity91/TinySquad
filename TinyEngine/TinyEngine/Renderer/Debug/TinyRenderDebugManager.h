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
 * @creation : 12/03/2024
 * @version  : 2024.2.6
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "TinyRenderDebugShader.h"

te_class TinyRenderDebugManager final {

	static const tiny_uint PIPELINE_COUNT = 2;
	static const tiny_uint SHADER_COUNT   = 4;

private:
	float							 _line_width;
	TinyGraphicPipeline				 _pipelines[ PIPELINE_COUNT ];
	tiny_list<TinyRenderDebugVertex> _lines;
	tiny_list<TinyRenderDebugVertex> _circles;
	VkPipelineShaderStageCreateInfo	 _shaders[ SHADER_COUNT ];

public:
	TinyRenderDebugManager( );

	~TinyRenderDebugManager( ) = default;

	bool Initialize( TinyGraphicManager& graphics );

	void SetLineWidth( float width );

	void Draw( const TinyRenderDebugPrimitive& primitive );

	void Flush( 
		TinyGame* game,
		TinyRenderUniformManager& uniforms, 
		TinyRenderBatchManager& batchs 
	);

	void Terminate( TinyGraphicManager& graphics );

private:
	bool CompileShader( TinyGraphicManager& graphics, const TinyRenderDebugShader& shader );

	bool BuildShader( TinyGraphicManager& graphics, const TinyRenderDebugShader& shader );

	bool BuildShaders( TinyGraphicManager& graphics );

	bool BuildPipeline( TinyGraphicManager& graphics );

	void DrawLines( 
		TinyGraphicManager& graphics,
		TinyGraphicWorkContext& work_context,
		TinyRenderUniformManager& uniforms,
		TinyRenderBatchManager& batchs 
	);

	void DrawCircles( 
		TinyGraphicManager& graphics,
		TinyGraphicWorkContext& work_context,
		TinyRenderUniformManager& uniforms,
		TinyRenderBatchManager& batchs 
	);

public:
	float GetLineWidth( ) const;

public:
	operator bool( ) const;

};
