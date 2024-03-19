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
 * @creation : 11/10/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#include <TinyMicro/__tiny_micro_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyGraphicPipeline::TinyGraphicPipeline( )
	: _pipeline{ VK_NULL_HANDLE },
	_layout{ VK_NULL_HANDLE },
	_properties{ },
	_descriptors{ }
{ }

bool TinyGraphicPipeline::Create( 
	TinyGraphicContext& graphic, 
	const TinyLimitsStack& limits,
	const TinyGraphicPipelineBundle& bundle
) {
	auto state = GetPipelineLayout( graphic.Logical, limits, bundle );

	if ( state ) {
		if ( bundle.PassType == TGR_TYPE_RENDER )
			state = CreateRenderPipeline( graphic, bundle );
		else if ( bundle.PassType == TGR_TYPE_COMPUTE )
			state = CreateComputePipeline( graphic, bundle );

		if ( state ) 
			GrabProperties( bundle );
	}

	return state;
}

void TinyGraphicPipeline::Mount( TinyGraphicWorkContext& work_context ) {
	auto bindpoint = tiny_cast( _properties.Type, VkPipelineBindPoint );
	auto sets	   = _descriptors.GetSets( work_context.WorkID );

	vkCmdBindPipeline( work_context.Queue->CommandBuffer, bindpoint, _pipeline );

	if ( sets.size( ) > 0 ) {
		vkCmdBindDescriptorSets(
			work_context.Queue->CommandBuffer,
			bindpoint, _layout,
			0,
			sets.size( ), sets.data( ),
			0, VK_NULL_HANDLE
		);
	}
}

void TinyGraphicPipeline::SetViewport( 
	TinyGraphicWorkContext& work_context,
	const VkViewport& viewport 
) {
	SetViewport( work_context, { viewport } );
}

void TinyGraphicPipeline::SetViewport( 
	TinyGraphicWorkContext& work_context, 
	tiny_init<VkViewport> viewports 
) {
	if ( viewports.size( ) > 0 ) {
		vkCmdSetViewport(
			work_context.Queue->CommandBuffer,
			0, 
			tiny_cast( viewports.size( ), tiny_uint ),
			viewports.begin( )
		);
	}
}

void TinyGraphicPipeline::SetScissor( 
	TinyGraphicWorkContext& work_context, 
	const VkScissor& scissor 
) {
	SetScissor( work_context, { scissor } );
}

void TinyGraphicPipeline::SetScissor( 
	TinyGraphicWorkContext& work_context, 
	tiny_init<VkScissor> scissors 
) {
	if ( scissors.size( ) > 0 ) {
		vkCmdSetScissor(
			work_context.Queue->CommandBuffer,
			0, 
			tiny_cast( scissors.size( ), tiny_uint ),
			scissors.begin( )
		);
	}
}

void TinyGraphicPipeline::SetCullMode( 
	TinyGraphicWorkContext& work_context, 
	VkCullModeFlags cull_mode 
) {
	vkCmdSetCullMode( work_context.Queue->CommandBuffer, cull_mode );
}

void TinyGraphicPipeline::SetFrontFace( 
	TinyGraphicWorkContext& work_context, 
	VkFrontFace front_face 
) {
	vkCmdSetFrontFace( work_context.Queue->CommandBuffer, front_face );
}

void TinyGraphicPipeline::SetPrimitiveRestartEnable( 
	TinyGraphicWorkContext& work_context, 
	bool is_active 
) {
	vkCmdSetPrimitiveRestartEnable( work_context.Queue->CommandBuffer, is_active ? VK_TRUE : VK_FALSE );
}

void TinyGraphicPipeline::SetPrimitiveTopology( 
	TinyGraphicWorkContext& work_context, 
	VkPrimitiveTopology topology 
) {
	vkCmdSetPrimitiveTopology( work_context.Queue->CommandBuffer, topology );
}

void TinyGraphicPipeline::SetRasterizerDiscardEnable( 
	TinyGraphicWorkContext& work_context, 
	bool is_active 
) {
	vkCmdSetRasterizerDiscardEnable( work_context.Queue->CommandBuffer, is_active ? VK_TRUE : VK_FALSE );
}

void TinyGraphicPipeline::SetBlendConstants( 
	TinyGraphicWorkContext& work_context, 
	const float* constants 
) {
	vkCmdSetBlendConstants( work_context.Queue->CommandBuffer, constants );
}

void TinyGraphicPipeline::SetBlendConstants(
	TinyGraphicWorkContext& work_context, 
	const tiny_vec4& constant 
) {
	vkCmdSetBlendConstants( work_context.Queue->CommandBuffer, tiny_rvalue( constant.r ) );
}

void TinyGraphicPipeline::SetDepthTestEnable( 
	TinyGraphicWorkContext& work_context, 
	bool is_active 
) {
	vkCmdSetDepthTestEnable( work_context.Queue->CommandBuffer, is_active ? VK_TRUE : VK_FALSE );
}

void TinyGraphicPipeline::SetDepthCompareOp( 
	TinyGraphicWorkContext& work_context, 
	VkCompareOp operation 
) {
	vkCmdSetDepthCompareOp( work_context.Queue->CommandBuffer, operation );
}

void TinyGraphicPipeline::SetDepthWriteEnable( 
	TinyGraphicWorkContext& work_context, 
	bool is_active 
) {
	vkCmdSetDepthWriteEnable( work_context.Queue->CommandBuffer, is_active ? VK_TRUE : VK_FALSE );
}

void TinyGraphicPipeline::SetDepthBias( 
	TinyGraphicWorkContext& work_context, 
	float constant, 
	float clamp, 
	float slope 
) {
	vkCmdSetDepthBias( work_context.Queue->CommandBuffer, constant, clamp, slope );
}

void TinyGraphicPipeline::SetDepthBounds( 
	TinyGraphicWorkContext& work_context, 
	float minimum, 
	float maximum 
) {
	vkCmdSetDepthBounds( work_context.Queue->CommandBuffer, minimum, maximum );
}

void TinyGraphicPipeline::SetDeviceMask( 
	TinyGraphicWorkContext& work_context, 
	tiny_uint mask 
) {
	vkCmdSetDeviceMask( work_context.Queue->CommandBuffer, mask );
}

void TinyGraphicPipeline::SetLineWidth(
	TinyGraphicWorkContext& work_context, 
	float width 
) {
	vkCmdSetLineWidth( work_context.Queue->CommandBuffer, width );
}

void TinyGraphicPipeline::SetStencilOp(
	TinyGraphicWorkContext& work_context,
	VkStencilFaceFlags face_mask,
	VkStencilOp fail_operation,
	VkStencilOp pass_operation,
	VkStencilOp depth_fail_operation,
	VkCompareOp compare_operation
) {
	vkCmdSetStencilOp(
		work_context.Queue->CommandBuffer,
		face_mask,
		fail_operation,
		pass_operation,
		depth_fail_operation,
		compare_operation
	);
}

void TinyGraphicPipeline::SetStencilCompareMask(
	TinyGraphicWorkContext& work_context,
	VkStencilFaceFlags face_mask,
	tiny_uint compare_mask
) {
	vkCmdSetStencilCompareMask( work_context.Queue->CommandBuffer, face_mask, compare_mask );
}

void TinyGraphicPipeline::SetStencilReference(
	TinyGraphicWorkContext& work_context,
	VkStencilFaceFlags face_mask,
	tiny_uint reference
) {
	vkCmdSetStencilReference( work_context.Queue->CommandBuffer, face_mask, reference );
}

void TinyGraphicPipeline::SetStencilWriteMask(
	TinyGraphicWorkContext& work_context,
	VkStencilFaceFlags face_mask,
	tiny_uint write_mask
) {
	vkCmdSetStencilWriteMask( work_context.Queue->CommandBuffer, face_mask, write_mask );
}

void TinyGraphicPipeline::Push(
	TinyGraphicWorkContext& work_context,
	const TinyGraphicPipelineConstant& constant 
) {
	if ( constant.Value ) {
		vkCmdPushConstants( 
			work_context.Queue->CommandBuffer,
			_layout,
			constant.Stage,
			constant.Offset,
			constant.Size, 
			constant.Value
		);
	}
}

void TinyGraphicPipeline::Bind(
	TinyGraphicLogical& logical,
	TinyGraphicWorkContext& work_context,
	const TinyGraphicPipelineBindpoint& bindpoint
) {
	Bind( logical, work_context, { bindpoint } );
}

void TinyGraphicPipeline::Bind(
	TinyGraphicLogical& logical,
	TinyGraphicWorkContext& work_context,
	tiny_init<TinyGraphicPipelineBindpoint> bindpoints
) {
	auto descriptor_id = tiny_cast( bindpoints.size( ), tiny_uint );

	if ( descriptor_id > 0 ) {
		auto descriptors = tiny_list<VkWriteDescriptorSet>{ };

		descriptors = descriptor_id;

		while ( descriptor_id-- > 0 ) {
			GrabBindpoint( 
				descriptors[ descriptor_id ],
				tiny_lvalue( bindpoints.begin( ) + descriptor_id ),
				work_context.WorkID 
			);
		}

		vkUpdateDescriptorSets( 
			logical, 
			descriptors.size( ), descriptors.data( ), 
			0, VK_NULL_HANDLE 
		);
	}
}

void TinyGraphicPipeline::Bind(
	TinyGraphicLogical& logical,
	TinyGraphicWorkContext& work_context,
	tiny_list<TinyGraphicPipelineBindpoint> bindpoints
) {
	auto descriptor_id = tiny_cast( bindpoints.size( ), tiny_uint );

	if ( descriptor_id > 0 ) {
		auto descriptors = tiny_list<VkWriteDescriptorSet>{ };

		descriptors = descriptor_id;

		while ( descriptor_id-- > 0 ) {
			GrabBindpoint(
				descriptors[ descriptor_id ],
				tiny_lvalue( bindpoints.begin( ) + descriptor_id ),
				work_context.WorkID
			);
		}

		vkUpdateDescriptorSets(
			logical,
			descriptors.size( ), descriptors.data( ),
			0, VK_NULL_HANDLE
		);
	}
}

void TinyGraphicPipeline::Bind(
	TinyGraphicLogical& logical,
	TinyGraphicWorkContext& work_context,
	tiny_uint count,
	TinyGraphicPipelineBindpoint* bindpoints
) {
	auto descriptors = tiny_list<VkWriteDescriptorSet>{ };

	descriptors = count;

	while ( count-- > 0 ) {
		GrabBindpoint(
			descriptors[ count ],
			tiny_lvalue( bindpoints + count ),
			work_context.WorkID
		);
	}

	vkUpdateDescriptorSets(
		logical,
		descriptors.size( ), descriptors.data( ),
		0, VK_NULL_HANDLE
	);
}

void TinyGraphicPipeline::BindVertex(
	TinyGraphicWorkContext& work_context,
	const TinyGraphicBuffer& buffer
) {
	BindVertex( work_context, 0, buffer );
}

void TinyGraphicPipeline::BindVertex(
	TinyGraphicWorkContext& work_context,
	tiny_uint binding,
	const TinyGraphicBuffer& buffer 
) {
	auto vertex = buffer.Get( );
	auto offset = VkDeviceSize{ 0 };

	vkCmdBindVertexBuffers( work_context.Queue->CommandBuffer, binding, 1, tiny_rvalue( vertex ), tiny_rvalue( offset ) );
}

void TinyGraphicPipeline::BindVertex(
	TinyGraphicWorkContext& work_context,
	const TinyGraphicPipelineVertex& vertex
) { 
	BindVertex( work_context, 0, vertex );
}

void TinyGraphicPipeline::BindVertex(
	TinyGraphicWorkContext& work_context,
	tiny_uint binding,
	const TinyGraphicPipelineVertex& vertex
) {
	auto _vertex = vertex.Buffer.Get( );
	auto offset  = VkDeviceSize{ vertex.Offset };

	vkCmdBindVertexBuffers( work_context.Queue->CommandBuffer, binding, 1, tiny_rvalue( _vertex ), tiny_rvalue( offset ) );
}

void TinyGraphicPipeline::BindVertex(
	TinyGraphicWorkContext& work_context,
	tiny_init<TinyGraphicPipelineVertex> vertexes
) { 
	BindVertex( work_context, 0, vertexes );
}

void TinyGraphicPipeline::BindVertex(
	TinyGraphicWorkContext& work_context,
	tiny_uint binding,
	tiny_init<TinyGraphicPipelineVertex> vertexes
) {
	auto vertex_count = tiny_cast( vertexes.size( ), tiny_uint );
	auto vertex		  = tiny_list<VkBuffer>{ vertex_count };
	auto offsets	  = tiny_list<VkDeviceSize>{ vertex_count };
	auto idx		  = vertex_count;

	while ( idx-- > 0 ) {
		auto& _vertex = tiny_lvalue( vertexes.begin( ) + idx );

		vertex[ idx ]  = _vertex.Buffer;
		offsets[ idx ] = _vertex.Offset;
	}

	vkCmdBindVertexBuffers( work_context.Queue->CommandBuffer, binding, vertex_count, vertex.data( ), offsets.data( ) );
}

void TinyGraphicPipeline::BindIndex(
	TinyGraphicWorkContext& work_context, 
	const TinyGraphicBuffer& buffer 
) {
	vkCmdBindIndexBuffer( work_context.Queue->CommandBuffer, buffer, 0, VK_INDEX_TYPE_UINT32 );
}

void TinyGraphicPipeline::BindGeometry(
	TinyGraphicWorkContext& work_context,
	const TinyGraphicBuffer& vertex,
	const TinyGraphicBuffer& index
) {
	BindVertex( work_context, vertex );
	BindIndex( work_context, index );
}

void TinyGraphicPipeline::Draw(
	TinyGraphicWorkContext& work_context,
	const TinyGraphicPipelineDrawcall& draw_call
) {
	if ( draw_call.Mode == TGD_MODE_INDEXED ) {
		vkCmdDrawIndexed( 
			work_context.Queue->CommandBuffer, 
			draw_call.Indexes,
			draw_call.Count, 
			draw_call.StartIndex,
			draw_call.StartVertex, 
			draw_call.StartInstance 
		);
	} else if ( draw_call.Mode == TGD_MODE_DIRECT ) {
		vkCmdDraw( 
			work_context.Queue->CommandBuffer, 
			draw_call.Indexes,
			draw_call.Count,
			draw_call.StartVertex, 
			draw_call.StartInstance 
		);
	}
}

void TinyGraphicPipeline::Draw(
	TinyGraphicLogical& logical,
	TinyGraphicWorkContext& work_context,
	const TinyGraphicPipelineDrawcall& draw_call,
	tiny_init<TinyGraphicPipelineBindpoint> bindpoints
) {
	Bind( logical, work_context, bindpoints );
	Draw( work_context, draw_call );
}

void TinyGraphicPipeline::Draw(
	TinyGraphicLogical& logical,
	TinyGraphicWorkContext& work_context,
	const TinyGraphicPipelineDrawcall& draw_call,
	tiny_list<TinyGraphicPipelineBindpoint> bindpoints
) {
	Bind( logical, work_context, bindpoints );
	Draw( work_context, draw_call );
}

void TinyGraphicPipeline::Terminate( TinyGraphicContext& context ) {
	_descriptors.Terminate( context.Logical );

	if ( vk::GetIsValid( _layout ) )
		vkDestroyPipelineLayout( context.Logical, _layout, vk::GetAllocator( ) );

	if ( vk::GetIsValid( _pipeline ) )
		vkDestroyPipeline( context.Logical, _pipeline, vk::GetAllocator( ) );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyGraphicPipeline::CreateRenderPipeline(
	TinyGraphicContext& graphic,
	const TinyGraphicPipelineBundle& bundle
) {
	auto pipeline_info	 = VkGraphicsPipelineCreateInfo{ VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO };
	auto& pipeline_cache = graphic.Pipelines.GetCache( );
	
	auto vertex_state		 = GetVertexInputState( bundle );
	auto assembly_state		 = GetInputAssemblyState( bundle );
	auto tessellation_state  = GetTessellationState( bundle );
	auto viewport			 = GetViewport( );
	auto rasterization_state = GetRasterizationState( );
	auto multisample_state   = GetMultisampleState( );
	auto depth_stencil_state = GetDepthStencilState( graphic.Boundaries, bundle );
	auto color_blend_state   = GetColorBlendState( bundle );
	auto dynamics			 = GetDynamicStates( bundle );

	pipeline_info.pNext				  = VK_NULL_HANDLE;
	pipeline_info.flags				  = VK_NULL_FLAGS;
	pipeline_info.stageCount		  = bundle.Shaders.size( );
	pipeline_info.pStages			  = bundle.Shaders.data( );
	pipeline_info.pVertexInputState   = tiny_rvalue( vertex_state );
	pipeline_info.pInputAssemblyState = tiny_rvalue( assembly_state );
	pipeline_info.pTessellationState  = tiny_rvalue( tessellation_state );
	pipeline_info.pViewportState	  = tiny_rvalue( viewport );
	pipeline_info.pRasterizationState = tiny_rvalue( rasterization_state );
	pipeline_info.pMultisampleState   = tiny_rvalue( multisample_state );
	pipeline_info.pDepthStencilState  = tiny_rvalue( depth_stencil_state );
	pipeline_info.pColorBlendState    = tiny_rvalue( color_blend_state );
	pipeline_info.pDynamicState		  = tiny_rvalue( dynamics );
	pipeline_info.layout			  = _layout;
	pipeline_info.renderPass		  = bundle.Pass;
	pipeline_info.subpass			  = bundle.Subpass;
	pipeline_info.basePipelineHandle  = VK_NULL_HANDLE;
	pipeline_info.basePipelineIndex   = 0;

	return vk::Check( vkCreateGraphicsPipelines( 
		graphic.Logical,
		pipeline_cache, 
		1, 
		tiny_rvalue( pipeline_info ),
		vk::GetAllocator( ),
		tiny_rvalue( _pipeline ) 
	) );
}

bool TinyGraphicPipeline::CreateComputePipeline(
	TinyGraphicContext& graphic,
	const TinyGraphicPipelineBundle& bundle
) {
	auto pipeline_info   = VkComputePipelineCreateInfo{ VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO };
	auto& pipeline_cache = graphic.Pipelines.GetCache( );

	pipeline_info.pNext				 = VK_NULL_HANDLE;
	pipeline_info.flags				 = VK_NULL_FLAGS;
	pipeline_info.stage				 = bundle.Shaders[ 0 ];
	pipeline_info.layout			 = _layout;
	pipeline_info.basePipelineHandle = VK_NULL_HANDLE;
	pipeline_info.basePipelineIndex  = 0;

	return vk::Check( vkCreateComputePipelines( 
		graphic.Logical,
		pipeline_cache,
		1, 
		tiny_rvalue( pipeline_info ),
		vk::GetAllocator( ),
		tiny_rvalue( _pipeline )
	) );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyGraphicPipeline::GetIsValid( ) const { 
	return vk::GetIsValid( _pipeline ) && vk::GetIsValid( _layout );
}

const VkPipeline TinyGraphicPipeline::Get( ) const { return _pipeline; }

const VkPipelineLayout TinyGraphicPipeline::GetLayout( ) const { return _layout; }

VkDescriptorSet TinyGraphicPipeline::GetSet( 
	TinyGraphicWorkContext& work_context,
	tiny_uint set_id 
) const {
	return GetSet( set_id, work_context.WorkID );
}

VkDescriptorSet TinyGraphicPipeline::GetSet( tiny_uint set_id, tiny_uint work_id ) const {
	auto& sets = _descriptors.GetSet( set_id );

	return sets[ work_id ];
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE GET ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyGraphicPipeline::GetPipelineLayout( 
	TinyGraphicLogical& logical,
	const TinyLimitsStack& limits,
	const TinyGraphicPipelineBundle& bundle
) {
	auto state = true;
	
	if ( bundle.Descriptors.size( ) > 0 )
		state =_descriptors.Create( logical, limits, bundle.Descriptors, bundle.DescriptorCount );

	if ( state ) { 
		auto layout_info = VkPipelineLayoutCreateInfo{ VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO };
		auto layouts	 = _descriptors.GetLayouts( );

		layout_info.pNext				   = VK_NULL_HANDLE;
		layout_info.flags				   = VK_NULL_FLAGS;
		layout_info.setLayoutCount		   = layouts.size( );
		layout_info.pSetLayouts			   = layouts.data( );
		layout_info.pushConstantRangeCount = bundle.Constants.size( );
		layout_info.pPushConstantRanges	   = bundle.Constants.data( );

		state = vk::Check( vkCreatePipelineLayout( logical, tiny_rvalue( layout_info ), vk::GetAllocator( ), tiny_rvalue( _layout ) ) );
	}

	return state;
}

VkPipelineVertexInputStateCreateInfo TinyGraphicPipeline::GetVertexInputState( 
	const TinyGraphicPipelineBundle& bundle
) const {
	auto vertex_inputs = VkPipelineVertexInputStateCreateInfo{ VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO };

	vertex_inputs.pNext							  = VK_NULL_HANDLE;
	vertex_inputs.flags							  = VK_NULL_FLAGS;
	vertex_inputs.vertexBindingDescriptionCount   = bundle.InputBinding.size( );
	vertex_inputs.pVertexBindingDescriptions	  = bundle.InputBinding.data( );
	vertex_inputs.vertexAttributeDescriptionCount = bundle.InputAttributes.size( );
	vertex_inputs.pVertexAttributeDescriptions	  = bundle.InputAttributes.data( );

	return vertex_inputs;
}

VkPipelineInputAssemblyStateCreateInfo TinyGraphicPipeline::GetInputAssemblyState(
	const TinyGraphicPipelineBundle& bundle
) const {
	auto assembly_state = VkPipelineInputAssemblyStateCreateInfo{ VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO };

	assembly_state.pNext				  = VK_NULL_HANDLE;
	assembly_state.flags				  = VK_NULL_FLAGS;
	assembly_state.topology				  = bundle.Topology;

	if (
		bundle.Topology == VK_PRIMITIVE_TOPOLOGY_LINE_STRIP				   ||
		bundle.Topology == VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP			   ||
		bundle.Topology == VK_PRIMITIVE_TOPOLOGY_TRIANGLE_FAN			   ||
		bundle.Topology == VK_PRIMITIVE_TOPOLOGY_LINE_STRIP_WITH_ADJACENCY ||
		bundle.Topology == VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP_WITH_ADJACENCY
	)
		assembly_state.primitiveRestartEnable = VK_TRUE;
	else 
		assembly_state.primitiveRestartEnable = VK_FALSE;

	return assembly_state;
}

VkPipelineTessellationStateCreateInfo TinyGraphicPipeline::GetTessellationState(
	const TinyGraphicPipelineBundle& bundle
) const {
	auto tessellation_state = VkPipelineTessellationStateCreateInfo{ VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_STATE_CREATE_INFO };

	tessellation_state.pNext			  = VK_NULL_HANDLE;
	tessellation_state.flags			  = VK_NULL_FLAGS;
	tessellation_state.patchControlPoints = bundle.Tessellation;

	return tessellation_state;
}

VkPipelineViewportStateCreateInfo TinyGraphicPipeline::GetViewport( ) const {
	auto viewport = VkPipelineViewportStateCreateInfo{ VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO };

	viewport.pNext		   = VK_NULL_HANDLE;
	viewport.flags		   = VK_NULL_FLAGS;
	viewport.viewportCount = 1;
	viewport.pViewports	   = VK_NULL_HANDLE;
	viewport.scissorCount  = 1;
	viewport.pScissors	   = VK_NULL_HANDLE;

	return viewport;
}

VkPipelineRasterizationStateCreateInfo TinyGraphicPipeline::GetRasterizationState( ) const {
	auto rasterization_state = VkPipelineRasterizationStateCreateInfo{ VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO };

	rasterization_state.pNext					= VK_NULL_HANDLE;
	rasterization_state.flags					= VK_NULL_FLAGS;
	rasterization_state.depthClampEnable		= VK_FALSE;
	rasterization_state.rasterizerDiscardEnable = VK_FALSE;
	rasterization_state.polygonMode				= VK_POLYGON_MODE_FILL;
	rasterization_state.cullMode				= VK_CULL_MODE_FRONT_BIT;
	rasterization_state.frontFace				= VK_FRONT_FACE_COUNTER_CLOCKWISE;
	rasterization_state.depthBiasEnable			= VK_FALSE;
	rasterization_state.depthBiasConstantFactor =  .0f;
	rasterization_state.depthBiasClamp			=  .0f;
	rasterization_state.depthBiasSlopeFactor	=  .0f;
	rasterization_state.lineWidth				= 1.f;

	return rasterization_state;
}

VkPipelineMultisampleStateCreateInfo TinyGraphicPipeline::GetMultisampleState( ) const {
	auto multisample_state = VkPipelineMultisampleStateCreateInfo{ VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO };
	
	multisample_state.pNext				    = VK_NULL_HANDLE;
	multisample_state.flags				    = VK_NULL_FLAGS;
	multisample_state.rasterizationSamples  = VK_SAMPLE_COUNT_1_BIT;
	multisample_state.sampleShadingEnable   = VK_FALSE;
	multisample_state.minSampleShading	    = .0f;
	multisample_state.pSampleMask			= VK_NULL_HANDLE;
	multisample_state.alphaToCoverageEnable = VK_FALSE;
	multisample_state.alphaToOneEnable		= VK_FALSE;

	return multisample_state;
}

VkPipelineDepthStencilStateCreateInfo TinyGraphicPipeline::GetDepthStencilState( 
	const TinyGraphicBoundaries& boundaries,
	const TinyGraphicPipelineBundle& bundle
) const {
	auto depth_stencil_state = VkPipelineDepthStencilStateCreateInfo{ VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO };
	auto depth_state		 = bundle.DepthEnable ? VK_TRUE : VK_FALSE;
	auto& viewport			 = boundaries.GetSwapViewport( );

	depth_stencil_state.pNext				  = VK_NULL_HANDLE;
	depth_stencil_state.flags				  = VK_NULL_FLAGS;
	depth_stencil_state.depthTestEnable		  = depth_state;
	depth_stencil_state.depthWriteEnable	  = depth_state;
	depth_stencil_state.depthCompareOp		  = bundle.DepthOperation;
	depth_stencil_state.depthBoundsTestEnable = depth_state;
	depth_stencil_state.stencilTestEnable	  = bundle.StencilEnable ? VK_TRUE : VK_FALSE;
	depth_stencil_state.front				  = bundle.DepthStencilFront;
	depth_stencil_state.back				  = bundle.DepthStencilBack;
	depth_stencil_state.minDepthBounds		  = viewport.minDepth;
	depth_stencil_state.maxDepthBounds		  = viewport.maxDepth;

	return depth_stencil_state;
}

VkPipelineColorBlendStateCreateInfo TinyGraphicPipeline::GetColorBlendState(
	const TinyGraphicPipelineBundle& bundle
) const {
	auto color_blend_state = VkPipelineColorBlendStateCreateInfo{ VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO };

	color_blend_state.pNext			  = VK_NULL_HANDLE;
	color_blend_state.flags			  = VK_NULL_FLAGS;
	color_blend_state.logicOpEnable   = VK_FALSE;
	color_blend_state.logicOp		  = VK_LOGIC_OP_COPY;
	color_blend_state.attachmentCount = bundle.ColorBlends.size( );
	color_blend_state.pAttachments	  = bundle.ColorBlends.data( );
	color_blend_state.blendConstants[ 0 ] = 1.f;
	color_blend_state.blendConstants[ 1 ] = 1.f;
	color_blend_state.blendConstants[ 2 ] = 1.f;
	color_blend_state.blendConstants[ 3 ] = 1.f;

	return color_blend_state;
}

VkPipelineDynamicStateCreateInfo TinyGraphicPipeline::GetDynamicStates( 
	const TinyGraphicPipelineBundle& bundle
) {
	auto states = VkPipelineDynamicStateCreateInfo{ VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO };

	states.pNext			 = VK_NULL_HANDLE;
	states.flags			 = VK_NULL_FLAGS;
	states.dynamicStateCount = bundle.Dynamics.size( );
	states.pDynamicStates    = bundle.Dynamics.data( );

	return states;
}

void TinyGraphicPipeline::GrabProperties( const TinyGraphicPipelineBundle& bundle ) {
	_properties.Type	 = bundle.Type;
	_properties.PassType = bundle.PassType;
	_properties.Dynamics = bundle.Dynamics;
}

void TinyGraphicPipeline::GrabBindpoint(
	VkWriteDescriptorSet& descriptor,
	const TinyGraphicPipelineBindpoint& bindpoint,
	tiny_uint work_id
) const {
	descriptor.sType			= VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
	descriptor.pNext			= VK_NULL_HANDLE;
	descriptor.dstSet			= GetSet( bindpoint.Set, work_id );
	descriptor.dstBinding		= bindpoint.Binding;
	descriptor.dstArrayElement  = 0;
	descriptor.descriptorCount  = 1;
	descriptor.descriptorType   = tiny_cast( bindpoint.Description, VkDescriptorType );
	descriptor.pTexelBufferView = VK_NULL_HANDLE;

	if ( bindpoint.Type == TGB_TYPE_TEXTURE ) {
		descriptor.pImageInfo  = tiny_cast( bindpoint.Value, VkDescriptorImageInfo* );
		descriptor.pBufferInfo = VK_NULL_HANDLE;
	} else if ( bindpoint.Type == TGB_TYPE_BUFFER ) {
		descriptor.pImageInfo  = VK_NULL_HANDLE;
		descriptor.pBufferInfo = tiny_cast( bindpoint.Value, VkDescriptorBufferInfo* );
	}
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	OPERATOR ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyGraphicPipeline::operator const VkPipeline( ) const { return Get( ); }

TinyGraphicPipeline::operator const VkPipelineLayout ( ) const { return GetLayout( ); }
