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

bool TinyRenderDebugManager::Initialize( TinyGraphicManager& graphics ) {
	return BuildShaders( graphics ) && BuildPipeline( graphics );
}

void TinyRenderDebugManager::SetLineWidth( float width ) {
	if ( width > 0.f )
		_line_width = width; 
}

void TinyRenderDebugManager::Draw( const TinyRenderDebugPrimitive& primitive ) {
	if ( primitive.Type == TRD_PRIMITIVE_LINE ) {
		_lines.emplace_back( { { primitive.Src.x, primitive.Src.y, .0f, 1.f }, primitive.Color } );
		_lines.emplace_back( { { primitive.Dst.x, primitive.Dst.y, .0f, 1.f }, primitive.Color } );
	} else if ( primitive.Type == TRD_PRIMITIVE_RECTANGLE ) {
		auto rect_x = primitive.Src.x;
		auto rect_y = primitive.Src.y;
		auto size_x = primitive.Dst.x;
		auto size_y = primitive.Dst.y;

		_lines.emplace_back( { { rect_x			, rect_y		 , .0f, 1.f }, primitive.Color } );
		_lines.emplace_back( { { rect_x + size_x, rect_y		 , .0f, 1.f }, primitive.Color } );

		_lines.emplace_back( { { rect_x + size_x, rect_y		 , .0f, 1.f }, primitive.Color } );
		_lines.emplace_back( { { rect_x + size_x, rect_y + size_y, .0f, 1.f }, primitive.Color } );

		_lines.emplace_back( { { rect_x + size_x, rect_y + size_y, .0f, 1.f }, primitive.Color } );
		_lines.emplace_back( { { rect_x			, rect_y + size_y, .0f, 1.f }, primitive.Color } );

		_lines.emplace_back( { { rect_x			, rect_y + size_y, .0f, 1.f }, primitive.Color } );
		_lines.emplace_back( { { rect_x			, rect_y		 , .0f, 1.f }, primitive.Color } );
	} else {
		_circles.emplace_back( { 
			primitive.Color,
			{
				primitive.Src.x,
				primitive.Src.y,
				primitive.Dst.x,
				primitive.Dst.y
			}
		} );
	}
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
	auto bundle  = graphics.CreatePipeline( TGP_TYPE_2D, TINY_OUTPASS_NAME, 1 );

	bundle.Topology		 = VK_PRIMITIVE_TOPOLOGY_LINE_LIST;
	bundle.Shaders		 = 2;
	bundle.Shaders[ 0 ]  = _shaders[ 0 ];
	bundle.Shaders[ 1 ]  = _shaders[ 1 ];

	bundle.InputBinding				   = 1;
	bundle.InputBinding[ 0 ].binding   = tiny_cast( 0, tiny_uint );
	bundle.InputBinding[ 0 ].stride	   = tiny_sizeof( TinyRenderDebugVertex );
	bundle.InputBinding[ 0 ].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
	
	bundle.InputAttributes				 = 2;
	bundle.InputAttributes[ 0 ].location = 0;
	bundle.InputAttributes[ 0 ].binding  = bundle.InputBinding[ 0 ].binding;
	bundle.InputAttributes[ 0 ].format   = VK_FORMAT_R32G32B32A32_SFLOAT;
	bundle.InputAttributes[ 0 ].offset   = tiny_offset_of( TinyRenderDebugVertex, Position );
	bundle.InputAttributes[ 1 ].location = 1;
	bundle.InputAttributes[ 1 ].binding  = bundle.InputBinding[ 0 ].binding;
	bundle.InputAttributes[ 1 ].format   = VK_FORMAT_R32G32B32A32_SFLOAT;
	bundle.InputAttributes[ 1 ].offset   = tiny_offset_of( TinyRenderDebugVertex, Color );
	
	bundle.DepthEnable   = false;
	bundle.StencilEnable = false;
	bundle.Dynamics.emplace_back( VK_DYNAMIC_STATE_LINE_WIDTH );

	bundle.Descriptors = 1;
	bundle.Descriptors[ TINY_RENDER_SET_CORE ] = 1;
	
	_pCreateSetBind( bundle, TINY_RENDER_SET_CORE, 0, TGBP_TYPE_UNIFORM, TGS_STAGE_VERTEX );

	auto state = _pipelines[ 0 ].Create( context, limits, bundle );

	if ( state ) {
		bundle.Topology		= VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP;
		bundle.Shaders[ 0 ] = _shaders[ 2 ];
		bundle.Shaders[ 1 ] = _shaders[ 3 ];

		bundle.InputBinding.clear( );
		bundle.InputAttributes.clear( );
		bundle.Dynamics.pop_back( );

		bundle.Descriptors.clear( );
		bundle.Descriptors = 2;
		bundle.Descriptors[ TINY_RENDER_SET_CORE   ] = 1;
		bundle.Descriptors[ TINY_RENDER_SET_RENDER ] = 2;

		_pCreateSetBind( bundle, TINY_RENDER_SET_CORE,   0, TGBP_TYPE_UNIFORM, TGS_STAGE_VERTEX );
		_pCreateSetBind( bundle, TINY_RENDER_SET_RENDER, 0, TGBP_TYPE_UNIFORM, TGS_STAGE_VERTEX );
		_pCreateSetBind( bundle, TINY_RENDER_SET_RENDER, 1, TGBP_TYPE_UNIFORM, TGS_STAGE_VERTEX );

		state = _pipelines[ 1 ].Create( context, limits, bundle );
	}

	return state;
}

void TinyRenderDebugManager::DrawLines(
	TinyGraphicManager& graphics,
	TinyGraphicWorkContext& work_context,
	TinyRenderUniformManager& uniforms,
	TinyRenderBatchManager& batchs 
) {
	auto& ubo_context = uniforms.GetUniform( "ubo_context" );
	auto& transforms  = uniforms.GetUniform( "ib_vertex" );
	auto& pipeline	  = _pipelines[ 0 ];
	auto& logical	  = graphics.GetLogical( );
	auto& staging	  = batchs.GetStaging( );

	pipeline.Mount( work_context );
	pipeline.SetLineWidth( work_context, _line_width );

	{
		auto context = graphics.GetContext( );
		auto burner  = TinyGraphicBurner{ context, VK_QUEUE_TYPE_TRANSFER };
		auto size	 = _lines.size( ) * tiny_sizeof( TinyRenderDebugVertex );
		auto copie   = VkBufferCopy{ 0, 0, size };

		staging.Map( context, size );
		Tiny::Memcpy( _lines.data( ), staging.GetAccess( ), size );
		staging.UnMap( context );

		burner.Upload( staging, transforms, copie );
	}

	pipeline.BindVertex( work_context, transforms );
	pipeline.Bind( logical, work_context, ubo_context );
	pipeline.Draw( work_context, { TGD_MODE_DIRECT, _lines.size( ) } );
}

void TinyRenderDebugManager::DrawCircles(
	TinyGraphicManager& graphics,
	TinyGraphicWorkContext& work_context,
	TinyRenderUniformManager& uniforms,
	TinyRenderBatchManager& batchs 
) {
	auto& ubo_context = uniforms.GetUniform( "ubo_context" );
	auto& transforms  = uniforms.GetUniform( "ubo_sprites" );
	auto& pipeline	  = _pipelines[ 1 ]; 
	auto& logical	  = graphics.GetLogical( );
	auto& staging	  = batchs.GetStaging( );

	pipeline.Mount( work_context );

	{
		auto context = graphics.GetContext( );
		auto burner  = TinyGraphicBurner{ context, VK_QUEUE_TYPE_TRANSFER };
		auto size	 = _circles.size( ) * tiny_sizeof( TinyRenderDebugVertex );
		auto copie   = VkBufferCopy{ 0, 0, size };

		staging.Map( context, size );
		Tiny::Memcpy( _circles.data( ), staging.GetAccess( ), size );
		staging.UnMap( context );

		burner.Upload( staging, transforms, copie );
	}

	pipeline.Bind( logical, work_context, { ubo_context, transforms } );
	pipeline.Draw( work_context, { TGD_MODE_DIRECT, 6, _circles.size( ) } );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
float TinyRenderDebugManager::GetLineWidth( ) const { return _line_width; }

////////////////////////////////////////////////////////////////////////////////////////////
//		===	OPERATOR ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyRenderDebugManager::operator bool( ) const {
	return _lines.size( ) > 0 || _circles.size( ) > 0;
}
