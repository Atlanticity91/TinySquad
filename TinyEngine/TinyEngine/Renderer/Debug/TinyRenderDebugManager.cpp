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
	_circles{ },
	_shaders{ }
{ }

bool TinyRenderDebugManager::Initialize( 
	TinyGraphicManager& graphics, 
	TinyRenderUniformManager& uniforms
) {
	return  BuildShaders( graphics )  && 
			BuildPipeline( graphics ) &&
			uniforms.Create( graphics, { TGB_TYPE_VERTEX, Line_t::Size, TinyRenderLine } ) &&
			uniforms.Create( graphics, { TGB_TYPE_VERTEX, Circle_t::Size, TinyRenderCircleBuffer } );
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

	if ( _circles.size( ) > 0 ) {
		DrawCircles( graphics, work_context, uniforms, batchs );

		_circles.clear( );
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
	auto shader_properties = TinyGraphicShaderSpecification{ };
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
	auto builder = graphics.CreatePipeline( TGP_TYPE_NONE, TINY_OUTPASS_NAME, 1 );
	auto context = graphics.GetContext( );
	auto limits  = graphics.GetPipelineLimits( );

	builder.Topology		 = VK_PRIMITIVE_TOPOLOGY_LINE_LIST;
	builder.Shaders		 = 2;
	builder.Shaders[ 0 ]  = _shaders[ 0 ];
	builder.Shaders[ 1 ]  = _shaders[ 1 ];

	TinyGraphicPipeline::CreateBinding( builder, { 0, tiny_sizeof( TinyRenderDebugLineVertice ) } );
	TinyGraphicPipeline::CreateAttribute( 
		builder,
		{
			{ 0, 0, TPA_TYPE_VEC4, tiny_offset_of( Position, TinyRenderDebugLineVertice ) },
			{ 1, 0, TPA_TYPE_VEC4, tiny_offset_of( Color   , TinyRenderDebugLineVertice ) }
		}
	);
	TinyGraphicPipeline::CreateSetBind( builder, TRS_ID_CORE, { 0, TGBP_TYPE_UNIFORM, 1, TGS_STAGE_VERTEX } );

	builder.DepthEnable   = false;
	builder.StencilEnable = false;
	builder.Dynamics.emplace_back( VK_DYNAMIC_STATE_LINE_WIDTH );

	auto state = _pipelines[ 0 ].Create( context, limits, builder );

	if ( state ) {
		builder.Topology		= VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
		builder.Shaders[ 0 ] = _shaders[ 2 ];
		builder.Shaders[ 1 ] = _shaders[ 3 ];

		builder.InputBinding.clear( );
		builder.InputAttributes.clear( );
		
		TinyGraphicPipeline::CreateBinding( builder, { 0, tiny_sizeof( TinyRenderDebugCircleVertice ) } );
		TinyGraphicPipeline::CreateAttribute(
			builder,
			{
				{ 0, 0, TPA_TYPE_VEC4, tiny_offset_of( Position, TinyRenderDebugCircleVertice ) },
				{ 1, 0, TPA_TYPE_VEC4, tiny_offset_of( Circle  , TinyRenderDebugCircleVertice ) },
				{ 2, 0, TPA_TYPE_VEC4, tiny_offset_of( Color   , TinyRenderDebugCircleVertice ) }
			}
		);

		builder.Dynamics.pop_back( );

		state = _pipelines[ 1 ].Create( context, limits, builder );
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

void TinyRenderDebugManager::PushCircle(
	const tiny_vec2& location,
	const tiny_vec2& circle,
	const tiny_color& color
) {
	auto _circle   = TinyRenderDebugCircle{ };
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

	_circles.push( _circle );
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
	auto& indexes  = uniforms[ TinyQuadIndexBuffer ];
	auto& vertex   = uniforms[ TinyRenderCircleBuffer ];
	auto& core	   = uniforms[ TinyCoreUniform ];
	auto instance  = _circles.size( );

	{
		auto context = graphics.GetContext( );
		auto size	 = instance * tiny_sizeof( TinyRenderDebugCircle );
		
		staging.Map( context, size );

		auto* staging_addr = tiny_cast( staging.GetAccess( ), tiny_pointer );
		auto* vertex_addr  = tiny_cast( _circles.data( )	, tiny_pointer );

		Tiny::Memcpy( vertex_addr, staging_addr, size );

		staging.UnMap( context );

		auto burner	= TinyGraphicBurner{ context, VK_QUEUE_TYPE_TRANSFER };
		auto copie  = VkBufferCopy{ 0, 0, size };

		burner.Upload( staging, vertex , copie );
	}

	pipeline.Mount( work_context );
	pipeline.BindGeometry( work_context, indexes, vertex );
	pipeline.Bind( work_context, core );
	pipeline.Draw( work_context, { TGD_MODE_INDEXED, TinyQuadIndexCount * instance } );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
float TinyRenderDebugManager::GetLineWidth( ) const { return _line_width; }
