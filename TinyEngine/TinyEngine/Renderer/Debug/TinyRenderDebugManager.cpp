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

#include <TinyEngine/__tiny_engine_pch.h>

#define TinyRenderLine "vb_debug_lines"
#define TinyRenderCircleIndex "ib_debug_circles"
#define TinyRenderCircleBuffer "vb_debug_circles"

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyRenderDebugManager::TinyRenderDebugManager( )
	: _line_width{ 1.f },
	_pipelines{ },
	_lines{ },
	_circles_indexes{ },
	_circles_buffer{ },
	_shaders{ }
{ }

bool TinyRenderDebugManager::Initialize( 
	TinyGraphicManager& graphics, 
	TinyRenderUniformManager& uniforms
) {
	return  BuildShaders( graphics )  && 
			BuildPipeline( graphics ) &&
			uniforms.Create( graphics, { TGB_TYPE_VERTEX, Line_t::Size, TinyRenderLine } ) &&
			uniforms.Create( graphics, { TGB_TYPE_INDEX, CircleIndex_t::Size,TinyRenderCircleIndex } ) &&
			uniforms.Create( graphics, { TGB_TYPE_VERTEX, CircleBuffer_t::Size, TinyRenderCircleBuffer } );
}

void TinyRenderDebugManager::SetLineWidth( float width ) {
	if ( width > 0.f )
		_line_width = width; 
}

void TinyRenderDebugManager::Draw( const TinyRenderDebugPrimitive& primitive ) {
	if ( primitive.Type == TRD_PRIMITIVE_LINE )
		PushLine( primitive.Src, primitive.Dst, primitive.Color );
	else if ( primitive.Type == TRD_PRIMITIVE_RECTANGLE ) {
		auto rect_x = primitive.Src.x;
		auto rect_y = primitive.Src.y;
		auto size_x = primitive.Dst.x;
		auto size_y = primitive.Dst.y;

		PushLine( { rect_x		   , rect_y			 }, { rect_x + size_x, rect_y		   }, primitive.Color );
		PushLine( { rect_x + size_x, rect_y			 }, { rect_x + size_x, rect_y + size_y }, primitive.Color );
		PushLine( { rect_x + size_x, rect_y + size_y }, { rect_x		 , rect_y + size_y }, primitive.Color );
		PushLine( { rect_x		   , rect_y + size_y }, { rect_x		 , rect_y		   }, primitive.Color );
	} else
		PushCircle( primitive.Src, primitive.Dst, primitive.Color );
}

void TinyRenderDebugManager::Flush( 
	TinyGame* game,
	TinyRenderUniformManager& uniforms, 
	TinyRenderBatchManager& batchs 
) {
	auto& graphics	   = game->GetGraphics( );
	auto& work_context = graphics.GetWorkdContext( );

	if ( _lines.size( ) > 0 ) {
		DrawLines( graphics, work_context, uniforms, batchs );

		_lines.clear( );
	}

	if ( _circles_indexes.size( ) > 0 ) {
		DrawCircles( graphics, work_context, uniforms, batchs );

		_circles_indexes.clear( );
		_circles_buffer.clear( );
	}
}

void TinyRenderDebugManager::Terminate( TinyGraphicManager& graphics ) {
	auto context = graphics.GetContext( );
	auto idx	 = PIPELINE_COUNT;

	while ( idx-- > 0 )
		_pipelines[ idx ].Terminate( context );

	idx = SHADER_COUNT;

	while ( idx-- > 0 ) {
		if ( vk::GetIsValid( _shaders[ idx ].module ) )
			vkDestroyShaderModule( context.Logical, _shaders[ idx ].module, vk::GetAllocator( ) );
	}
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyRenderDebugManager::CompileShader( 
	TinyGraphicManager& graphics, 
	const TinyRenderDebugShader& shader
) {
	auto shader_properties = TinyGraphicShaderProperties{ };
	auto shader_info	   = VkShaderModuleCreateInfo{ VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO };
	auto compilation	   = TinyGraphicShaderCompilationContext{ shader.Name, shader.Source };
	auto& logical		   = graphics.GetLogical( );
	auto state			   = graphics.CompileShader( compilation, shader_properties );

	if ( state ) {
		shader_info.pNext	 = VK_NULL_HANDLE;
		shader_info.flags	 = VK_NULL_FLAGS;
		shader_info.codeSize = shader_properties.Code.size( );
		shader_info.pCode	 = tiny_cast( shader_properties.Code.data( ), const tiny_uint* );

		state = vk::Check( vkCreateShaderModule( logical, tiny_rvalue( shader_info ), vk::GetAllocator( ), tiny_rvalue( _shaders[ shader.ShaderID ].module ) ) );
	}

	return state;
}

bool TinyRenderDebugManager::BuildShader(
	TinyGraphicManager& graphics, 
	const TinyRenderDebugShader& shader
) {
	auto& _shader = _shaders[ shader.ShaderID ];

	_shader.sType			    = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	_shader.pNext			    = VK_NULL_HANDLE;
	_shader.flags			    = VK_NULL_FLAGS;
	_shader.stage			    = shader.Stage;
	_shader.module			    = VK_NULL_HANDLE;
	_shader.pName			    = "main";
	_shader.pSpecializationInfo = VK_NULL_HANDLE;

	return CompileShader( graphics, shader );
}

bool TinyRenderDebugManager::BuildShaders( TinyGraphicManager& graphics ) {
	return  BuildShader( graphics, { 0, VK_SHADER_STAGE_VERTEX_BIT,   "sv_debug_line",   TinyDebugLineVertex	 } ) &&
			BuildShader( graphics, { 1, VK_SHADER_STAGE_FRAGMENT_BIT, "sf_debug_line",   TinyDebugLineFragment   } ) &&
			BuildShader( graphics, { 2, VK_SHADER_STAGE_VERTEX_BIT,	  "sv_debug_circle", TinyDebugCircleVertex	 } ) &&
			BuildShader( graphics, { 3, VK_SHADER_STAGE_FRAGMENT_BIT, "sf_debug_circle", TinyDebugCircleFragment } );
}

bool TinyRenderDebugManager::BuildPipeline( TinyGraphicManager& graphics ) {
	auto context = graphics.GetContext( );
	auto limits  = graphics.GetPipelineLimits( );
	auto bundle  = graphics.CreatePipeline( TGP_TYPE_NONE, TINY_OUTPASS_NAME, 1 );

	bundle.Topology		 = VK_PRIMITIVE_TOPOLOGY_LINE_LIST;
	bundle.Shaders		 = 2;
	bundle.Shaders[ 0 ]  = _shaders[ 0 ];
	bundle.Shaders[ 1 ]  = _shaders[ 1 ];

	TinyGraphicPipeline::CreateBinding( bundle, { 0, tiny_sizeof( TinyRenderDebugLineVertice ) } );
	TinyGraphicPipeline::CreateAttribute( 
		bundle,
		{
			{ 0, 0, TPA_TYPE_VEC4, tiny_offset_of( TinyRenderDebugLineVertice, Position ) },
			{ 1, 0, TPA_TYPE_VEC4, tiny_offset_of( TinyRenderDebugLineVertice, Color	) }
		}
	);
	TinyGraphicPipeline::CreateSetBind( bundle, 0, { 0, TGBP_TYPE_UNIFORM, 1, TGS_STAGE_VERTEX } );

	bundle.DepthEnable   = false;
	bundle.StencilEnable = false;
	bundle.Dynamics.emplace_back( VK_DYNAMIC_STATE_LINE_WIDTH );

	auto state = _pipelines[ 0 ].Create( context, limits, bundle );

	if ( state ) {
		bundle.Topology		= VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP;
		bundle.Shaders[ 0 ] = _shaders[ 2 ];
		bundle.Shaders[ 1 ] = _shaders[ 3 ];

		bundle.InputBinding.clear( );
		bundle.InputAttributes.clear( );
		
		TinyGraphicPipeline::CreateBinding( bundle, { 0, tiny_sizeof( TinyRenderDebugCircleVertice ) } );
		TinyGraphicPipeline::CreateAttribute(
			bundle,
			{
				{ 0, 0, TPA_TYPE_VEC4, tiny_offset_of( TinyRenderDebugCircleVertice, Position ) },
				{ 1, 0, TPA_TYPE_VEC4, tiny_offset_of( TinyRenderDebugCircleVertice, Circle   ) },
				{ 2, 0, TPA_TYPE_VEC4, tiny_offset_of( TinyRenderDebugCircleVertice, Color    ) }
			}
		);

		bundle.Dynamics.pop_back( );

		state = _pipelines[ 1 ].Create( context, limits, bundle );
	}

	return state;
}

void TinyRenderDebugManager::PushLine( 
	const tiny_vec2& start,
	const tiny_vec2& stop,
	const tiny_color& color
) {
	auto vertex = TinyRenderDebugLine{ };
	
	vertex.Vertice[ 0 ].Position = tiny_vec4{ start.x, start.y, .0f, 1.f };
	vertex.Vertice[ 0 ].Color	 = color;
	
	vertex.Vertice[ 1 ].Position = tiny_vec4{ stop.x, stop.y, .0f, 1.f };
	vertex.Vertice[ 1 ].Color	 = color;

	_lines.push( vertex );
}

void TinyRenderDebugManager::PushCircleIndex( ) {
	auto indexes = TinyRenderDebugIndex{ };

	auto index_id = TINY_QUAD_INDEX_COUNT;
	auto offset   = index_id * _circles_indexes.size( );

	while ( index_id-- > 0 )
		indexes.Index[ index_id ] += offset;

	_circles_indexes.push( indexes );
}

void TinyRenderDebugManager::PushCircle(
	const tiny_vec2& location,
	const tiny_vec2& circle,
	const tiny_color& color
) {
	auto _circle = TinyRenderDebugCircle{ };
	auto _offset   = circle.x * .5f;
	auto transform = glm::translate( tiny_vec3{ location.x + _offset, location.y + _offset, 0.f } );

	transform	  *= glm::scale( tiny_vec3{ circle.x, circle.x, 1.f } );

	_circle.Vertice[ 0 ].Position = transform * TinyQuadVertex[ 0 ];
	_circle.Vertice[ 0 ].Circle	  = tiny_vec4{ -1.f, -1.f, circle.x, circle.y };
	_circle.Vertice[ 0 ].Color	  = color;

	_circle.Vertice[ 1 ].Position = transform * TinyQuadVertex[ 1 ];
	_circle.Vertice[ 1 ].Circle	  = tiny_vec4{  1.f, -1.f , circle.x, circle.y };
	_circle.Vertice[ 1 ].Color	  = color;

	_circle.Vertice[ 2 ].Position = transform * TinyQuadVertex[ 2 ];
	_circle.Vertice[ 2 ].Circle	  = tiny_vec4{  1.f,  1.f , circle.x, circle.y };
	_circle.Vertice[ 2 ].Color	  = color;

	_circle.Vertice[ 3 ].Position = transform * TinyQuadVertex[ 3 ];
	_circle.Vertice[ 3 ].Circle   = tiny_vec4{ -1.f,  1.f , circle.x, circle.y };
	_circle.Vertice[ 3 ].Color	  = color;

	_circles_buffer.push( _circle );

	PushCircleIndex( );
}

void TinyRenderDebugManager::DrawLines(
	TinyGraphicManager& graphics,
	TinyGraphicWorkContext& work_context,
	TinyRenderUniformManager& uniforms,
	TinyRenderBatchManager& batchs 
) {
	auto& pipeline = _pipelines[ 0 ];
	auto& staging  = batchs.GetStaging( );
	auto& vertex   = uniforms[ TinyRenderLine  ];
	auto& core	   = uniforms[ TinyCoreUniform ];

	{
		auto vert_size = _lines.size( ) * tiny_sizeof( TinyRenderDebugLine );
		auto context   = graphics.GetContext( );

		staging.Map( context, vert_size );
		Tiny::Memcpy( _lines.data( ), staging.GetAccess( ), vert_size );
		staging.UnMap( context );

		auto burner = TinyGraphicBurner{ context, VK_QUEUE_TYPE_TRANSFER };
		auto copie  = VkBufferCopy{ 0, 0, vert_size };

		burner.Upload( staging, vertex, copie );
	}

	pipeline.Mount( work_context );
	pipeline.SetLineWidth( work_context, _line_width );
	pipeline.BindVertex( work_context, vertex );
	pipeline.Bind( work_context, core );
	pipeline.Draw( work_context, { TGD_MODE_DIRECT, 2 * _lines.size( ) } );
}

void TinyRenderDebugManager::DrawCircles(
	TinyGraphicManager& graphics,
	TinyGraphicWorkContext& work_context,
	TinyRenderUniformManager& uniforms,
	TinyRenderBatchManager& batchs
) {
	auto& pipeline = _pipelines[ 1 ];
	auto& staging  = batchs.GetStaging( );
	auto& indexes  = uniforms[ TinyRenderCircleIndex ];
	auto& vertex   = uniforms[ TinyRenderCircleBuffer ];
	auto& core	   = uniforms[ TinyCoreUniform ];

	{
		auto inst_size = _circles_indexes.size( ) * tiny_sizeof( TinyRenderDebugIndex );
		auto vert_size = _circles_buffer.size( )  * tiny_sizeof( TinyRenderDebugCircle );
		auto context   = graphics.GetContext( );

		auto* inst = tiny_cast( _circles_indexes.data( ), tiny_pointer );
		auto* vert = tiny_cast( _circles_buffer.data( ) , tiny_pointer );

		staging.Map( context, inst_size + vert_size );

		auto* staging_addr = tiny_cast( staging.GetAccess( ), tiny_pointer );

		Tiny::Memcpy( inst, staging_addr			, inst_size );
		Tiny::Memcpy( vert, staging_addr + inst_size, vert_size );
		staging.UnMap( context );

		auto burner	= TinyGraphicBurner{ context, VK_QUEUE_TYPE_TRANSFER };

		VkBufferCopy copies[ 2 ] = {
			{ 0		   , 0, inst_size },
			{ inst_size, 0, vert_size }
		};

		burner.Upload( staging, indexes, copies[ 0 ] );
		burner.Upload( staging, vertex , copies[ 1 ] );
	}

	pipeline.Mount( work_context );
	pipeline.BindGeometry( work_context, indexes, vertex );
	pipeline.Bind( work_context, core );
	pipeline.Draw( work_context, { TGD_MODE_INDEXED, 6, _circles_indexes.size( ) } );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
float TinyRenderDebugManager::GetLineWidth( ) const { return _line_width; }
