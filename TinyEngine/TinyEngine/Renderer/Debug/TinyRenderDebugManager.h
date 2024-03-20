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

#define TINY_MAX_DEBUG_COUNT 512

te_class TinyRenderDebugManager final {

	static const tiny_uint PIPELINE_COUNT = 2;
	static const tiny_uint SHADER_COUNT   = 4;

	using Line_t		 = tiny_stack<TinyRenderDebugLine, TINY_MAX_DEBUG_COUNT>;
	using CircleIndex_t  = tiny_stack<TinyRenderDebugIndex, TINY_MAX_DEBUG_COUNT>;
	using CircleBuffer_t = tiny_stack<TinyRenderDebugCircle, TINY_MAX_DEBUG_COUNT>;

private:
	float							_line_width;
	TinyGraphicPipeline				_pipelines[ PIPELINE_COUNT ];
	Line_t							_lines;
	CircleIndex_t					_circles_indexes;
	CircleBuffer_t					_circles_buffer;
	VkPipelineShaderStageCreateInfo	_shaders[ SHADER_COUNT ];

public:
	TinyRenderDebugManager( );

	~TinyRenderDebugManager( ) = default;

	bool Initialize( TinyGraphicManager& graphics, TinyRenderUniformManager& uniforms );

	void SetLineWidth( float width );

	void Draw( const tiny_mat4& camera, const TinyRenderDebugPrimitive& primitive );

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

	void PushLine(
		const tiny_mat4& camera,
		const tiny_vec2& start,
		const tiny_vec2& stop, 
		const tiny_color& color
	);

	void PushCircle(
		const tiny_mat4& camera,
		const tiny_vec2& location,
		const tiny_vec2& circle,
		const tiny_color& color
	);

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

};
