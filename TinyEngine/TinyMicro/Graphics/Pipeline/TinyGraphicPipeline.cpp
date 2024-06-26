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
	TinyGraphicWrapper& graphic,
	const TinyLimitsStack& limits,
	const TinyGraphicPipelineSpecification& specification
) {
	auto state = GetPipelineLayout( graphic.Logical, limits, specification );

	if ( state ) {
		if ( specification.PassType == TGR_TYPE_RENDER )
			state = CreateRenderPipeline( graphic, specification );
		else if ( specification.PassType == TGR_TYPE_COMPUTE )
			state = CreateComputePipeline( graphic, specification );

		if ( state ) 
			GrabProperties( specification );
	}

	return state;
}

void TinyGraphicPipeline::Mount( TinyGraphicWorkContext& work_context ) {
	auto bindpoint = tiny_cast( _properties.PassType, VkPipelineBindPoint );
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
	auto* data = viewports.begin( );
	auto count = tiny_cast( viewports.size( ), tiny_uint );

	if ( count > 0 ) 
		vkCmdSetViewport( work_context.Queue->CommandBuffer, 0, count, data );
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
	auto* data = scissors.begin( );
	auto count = tiny_cast( scissors.size( ), tiny_uint );

	if ( count > 0 )
		vkCmdSetScissor( work_context.Queue->CommandBuffer, 0, count, data );
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
	TinyGraphicWorkContext& work_context,
	const TinyGraphicPipelineBindpoint& bindpoint
) {
	Bind( work_context, { bindpoint } );
}

void TinyGraphicPipeline::Bind(
	TinyGraphicWorkContext& work_context,
	tiny_init<TinyGraphicPipelineBindpoint> bindpoints
) {
	auto descriptor_id = tiny_cast( bindpoints.size( ), tiny_uint );

	if ( descriptor_id > 0 ) {
		auto descriptors = tiny_list<VkWriteDescriptorSet>{ };

		descriptors = descriptor_id;

		while ( descriptor_id-- > 0 )
			GrabBindpoint( descriptors[ descriptor_id ], tiny_lvalue( bindpoints.begin( ) + descriptor_id ), work_context.WorkID );

		auto* data = descriptors.data( );
		auto size  = descriptors.size( );

		vkUpdateDescriptorSets( tiny_lvalue( work_context.Logical ), size, data, 0, VK_NULL_HANDLE );
	}
}

void TinyGraphicPipeline::Bind(
	TinyGraphicWorkContext& work_context,
	tiny_list<TinyGraphicPipelineBindpoint> bindpoints
) {
	auto descriptor_id = tiny_cast( bindpoints.size( ), tiny_uint );

	if ( descriptor_id > 0 ) {
		auto descriptors = tiny_list<VkWriteDescriptorSet>{ };

		descriptors = descriptor_id;

		while ( descriptor_id-- > 0 )
			GrabBindpoint( descriptors[ descriptor_id ], tiny_lvalue( bindpoints.begin( ) + descriptor_id ), work_context.WorkID );

		auto* data = descriptors.data( );
		auto size  = descriptors.size( );

		vkUpdateDescriptorSets( tiny_lvalue( work_context.Logical ), size, data, 0, VK_NULL_HANDLE );
	}
}

void TinyGraphicPipeline::Bind(
	TinyGraphicWorkContext& work_context,
	tiny_uint count,
	TinyGraphicPipelineBindpoint* bindpoints
) {
	auto descriptors = tiny_list<VkWriteDescriptorSet>{ };

	descriptors = count;

	while ( count-- > 0 )
		GrabBindpoint( descriptors[ count ], tiny_lvalue( bindpoints + count ), work_context.WorkID );

	auto* data = descriptors.data( );
	auto size  = descriptors.size( );

	vkUpdateDescriptorSets( tiny_lvalue( work_context.Logical ), count, data, 0, VK_NULL_HANDLE );
}

void TinyGraphicPipeline::Bind(
	TinyGraphicWorkContext& work_context,
	tiny_uint set,
	tiny_uint binding,
	tiny_init<VkDescriptorBufferInfo> buffers
) {
	auto* data = buffers.begin( );
	auto size  = tiny_cast( buffers.size( ), tiny_uint );

	Bind( work_context, set, binding, size, data );
}

void TinyGraphicPipeline::Bind(
	TinyGraphicWorkContext& work_context,
	tiny_uint set,
	tiny_uint binding,
	tiny_uint count,
	const VkDescriptorBufferInfo* buffers
) { 
	auto descriptor = VkWriteDescriptorSet{ VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET };

	descriptor.pNext			= VK_NULL_HANDLE;
	descriptor.dstSet			= GetSet( set, work_context.WorkID );
	descriptor.dstBinding		= binding;
	descriptor.dstArrayElement  = 0;
	descriptor.descriptorCount  = count;
	descriptor.descriptorType   = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
	descriptor.pTexelBufferView = VK_NULL_HANDLE;
	descriptor.pImageInfo		= VK_NULL_HANDLE;
	descriptor.pBufferInfo		= buffers;

	vkUpdateDescriptorSets( tiny_lvalue( work_context.Logical ), 1, tiny_rvalue( descriptor ), 0, VK_NULL_HANDLE );
}

void TinyGraphicPipeline::Bind(
	TinyGraphicWorkContext& work_context,
	tiny_uint set,
	tiny_uint binding,
	tiny_init<VkDescriptorImageInfo> samplers
) {
	auto* data = samplers.begin( );
	auto size  = tiny_cast( samplers.size( ), tiny_uint );

	Bind( work_context, set, binding, size, data );
}

void TinyGraphicPipeline::Bind(
	TinyGraphicWorkContext& work_context,
	tiny_uint set,
	tiny_uint binding,
	tiny_uint count,
	const VkDescriptorImageInfo* samplers
) { 
	auto descriptor = VkWriteDescriptorSet{ VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET };

	descriptor.pNext			= VK_NULL_HANDLE;
	descriptor.dstSet			= GetSet( set, work_context.WorkID );
	descriptor.dstBinding		= binding;
	descriptor.dstArrayElement  = 0;
	descriptor.descriptorCount  = count;
	descriptor.descriptorType   = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
	descriptor.pTexelBufferView = VK_NULL_HANDLE;
	descriptor.pImageInfo		= samplers;
	descriptor.pBufferInfo		= VK_NULL_HANDLE;

	vkUpdateDescriptorSets( tiny_lvalue( work_context.Logical ), 1, tiny_rvalue( descriptor ), 0, VK_NULL_HANDLE );
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

		vertex[ idx  ] = _vertex.Buffer;
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
	const TinyGraphicBuffer& index,
	const TinyGraphicBuffer& vertex
) {
	BindIndex( work_context, index );
	BindVertex( work_context, vertex );
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
	TinyGraphicWorkContext& work_context,
	const TinyGraphicPipelineDrawcall& draw_call,
	tiny_init<TinyGraphicPipelineBindpoint> bindpoints
) {
	Bind( work_context, bindpoints );
	Draw( work_context, draw_call );
}

void TinyGraphicPipeline::Draw(
	TinyGraphicWorkContext& work_context,
	const TinyGraphicPipelineDrawcall& draw_call,
	tiny_list<TinyGraphicPipelineBindpoint> bindpoints
) {
	Bind( work_context, bindpoints );
	Draw( work_context, draw_call );
}

void TinyGraphicPipeline::Terminate( TinyGraphicWrapper& graphic ) {
	_descriptors.Terminate( graphic.Logical );

	if ( vk::GetIsValid( _layout ) )
		vkDestroyPipelineLayout( graphic.Logical, _layout, vk::GetAllocator( ) );

	if ( vk::GetIsValid( _pipeline ) )
		vkDestroyPipeline( graphic.Logical, _pipeline, vk::GetAllocator( ) );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC STATIC ===
////////////////////////////////////////////////////////////////////////////////////////////
void TinyGraphicPipeline::CreateBinding(
	TinyGraphicPipelineSpecification& specification,
	const TinyGraphicPipelineBinding& binding
) {
	CreateBinding( specification, binding.Binding, binding.Stride, binding.IsVertex );
}

void TinyGraphicPipeline::CreateBinding(
	TinyGraphicPipelineSpecification& specification,
	tiny_init<TinyGraphicPipelineBinding> bindings
) {
	auto count = tiny_cast( bindings.size( ), tiny_uint );

	if ( count > 0 ) {
		specification.InputBinding = count;

		for ( auto& binding : bindings ) {
			auto rate = binding.IsVertex ? VK_VERTEX_INPUT_RATE_VERTEX : VK_VERTEX_INPUT_RATE_INSTANCE;

			specification.InputBinding[ binding.Binding ] = {
				binding.Binding,
				binding.Stride,
				rate
			};
		}
	}
}

void TinyGraphicPipeline::CreateBinding(
	TinyGraphicPipelineSpecification& specification,
	tiny_uint binding,
	tiny_uint stride,
	bool is_vertex
) {
	auto rate = is_vertex ? VK_VERTEX_INPUT_RATE_VERTEX : VK_VERTEX_INPUT_RATE_INSTANCE;

	specification.InputBinding.emplace_back( { binding, stride, rate } );
}

void TinyGraphicPipeline::CreateAttribute(
	TinyGraphicPipelineSpecification& specification,
	const TinyGraphicPipelineAttribute& attribute
) {
	CreateAttribute( specification, attribute.Location, attribute.Binding, attribute.Type, attribute.Offset );
}

void TinyGraphicPipeline::CreateAttribute(
	TinyGraphicPipelineSpecification& specification,
	tiny_init<TinyGraphicPipelineAttribute> attributes
) {
	auto count = tiny_cast( attributes.size( ), tiny_uint );

	if ( count > 0 ) {
		specification.InputAttributes = count;

		for ( auto& attribute : attributes ) {
			specification.InputAttributes[ attribute.Location ] = {
				attribute.Location,
				attribute.Binding,
				tiny_cast( attribute.Type, VkFormat ),
				attribute.Offset
			};
		}
	}
}

void TinyGraphicPipeline::CreateAttribute(
	TinyGraphicPipelineSpecification& specification,
	tiny_uint location,
	tiny_uint binding,
	TinyPipelineAttributeTypes type,
	tiny_uint offset
) {
	specification.InputAttributes.emplace_back( { 
		location, 
		binding, 
		tiny_cast( type, VkFormat ), 
		offset 
	} );
}

void TinyGraphicPipeline::CreateSetBind(
	TinyGraphicPipelineSpecification& specification,
	tiny_uint set,
	const TinyGraphicPipelineSetBind& set_bind
) {
	CreateSetBind( specification, set, set_bind.Binding, set_bind.Type, set_bind.Count, set_bind.Stage );
}

void TinyGraphicPipeline::CreateSetBind(
	TinyGraphicPipelineSpecification& specification,
	tiny_uint set,
	tiny_init<TinyGraphicPipelineSetBind> set_binds
) {
	auto count = set_binds.size( );

	if ( count > 0 ) {
		if ( set == count )
			specification.Descriptors.emplace_back( { } );

		auto& descriptor_set = specification.Descriptors[ set ];

		for ( auto& set_bind : set_binds ) {
			auto stage = tiny_cast( set_bind.Stage, VkShaderStageFlags );
			auto type  = tiny_cast( set_bind.Type, VkDescriptorType );

			descriptor_set.emplace_back( { set_bind.Binding, type, set_bind.Count, stage, VK_NULL_HANDLE } );
		}
	}
}

void TinyGraphicPipeline::CreateSetBind(
	TinyGraphicPipelineSpecification& specification,
	tiny_uint set,
	tiny_uint binding,
	TinyGraphicBindTypes type,
	TinyGraphicShaderStages stage
) {
	CreateSetBind( specification, set, binding, type, 1, stage );
}

void TinyGraphicPipeline::CreateSetBind(
	TinyGraphicPipelineSpecification& specification,
	tiny_uint set,
	tiny_uint binding,
	TinyGraphicBindTypes type,
	tiny_uint count,
	TinyGraphicShaderStages stage
) {
	auto stage_ = tiny_cast( stage, VkShaderStageFlags );
	auto type_  = tiny_cast( type, VkDescriptorType );

	if ( set == specification.Descriptors.size( ) )
		specification.Descriptors.create_back( );

	specification.Descriptors[ set ].create_back( binding, type_, count, stage_, VK_NULL_HANDLE );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyGraphicPipeline::CreateRenderPipeline(
	TinyGraphicWrapper& graphic,
	const TinyGraphicPipelineSpecification& specification
) {
	auto pipeline_info	 = VkGraphicsPipelineCreateInfo{ VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO };
	auto& pipeline_cache = graphic.Pipelines.GetCache( );
	
	auto vertex_state		 = GetVertexInputState( specification );
	auto assembly_state		 = GetInputAssemblyState( specification );
	auto tessellation_state  = GetTessellationState( specification );
	auto viewport			 = GetViewport( );
	auto rasterization_state = GetRasterizationState( );
	auto multisample_state   = GetMultisampleState( );
	auto depth_stencil_state = GetDepthStencilState( graphic.Boundaries, specification );
	auto color_blend_state   = GetColorBlendState( specification );
	auto dynamics			 = GetDynamicStates( specification );

	pipeline_info.pNext				  = VK_NULL_HANDLE;
	pipeline_info.flags				  = VK_NULL_FLAGS;
	pipeline_info.stageCount		  = specification.Shaders.size( );
	pipeline_info.pStages			  = specification.Shaders.data( );
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
	pipeline_info.renderPass		  = specification.Pass;
	pipeline_info.subpass			  = specification.Subpass;
	pipeline_info.basePipelineHandle  = VK_NULL_HANDLE;
	pipeline_info.basePipelineIndex   = 0;

	return vk::Check( vkCreateGraphicsPipelines( graphic.Logical, pipeline_cache, 1, tiny_rvalue( pipeline_info ), vk::GetAllocator( ), tiny_rvalue( _pipeline ) ) );
}

bool TinyGraphicPipeline::CreateComputePipeline(
	TinyGraphicWrapper& graphic,
	const TinyGraphicPipelineSpecification& specification
) {
	auto pipeline_info   = VkComputePipelineCreateInfo{ VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO };
	auto& pipeline_cache = graphic.Pipelines.GetCache( );

	pipeline_info.pNext				 = VK_NULL_HANDLE;
	pipeline_info.flags				 = VK_NULL_FLAGS;
	pipeline_info.stage				 = specification.Shaders[ 0 ];
	pipeline_info.layout			 = _layout;
	pipeline_info.basePipelineHandle = VK_NULL_HANDLE;
	pipeline_info.basePipelineIndex  = 0;

	return vk::Check( vkCreateComputePipelines( graphic.Logical, pipeline_cache, 1, tiny_rvalue( pipeline_info ), vk::GetAllocator( ), tiny_rvalue( _pipeline ) ) );
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
	const TinyGraphicPipelineSpecification& specification
) {
	auto state = true;
	
	if ( specification.Descriptors.size( ) > 0 )
		state =_descriptors.Create( logical, limits, specification.Descriptors, specification.DescriptorCount );

	if ( state ) { 
		auto layout_info = VkPipelineLayoutCreateInfo{ VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO };
		auto layouts	 = _descriptors.GetLayouts( );

		layout_info.pNext				   = VK_NULL_HANDLE;
		layout_info.flags				   = VK_NULL_FLAGS;
		layout_info.setLayoutCount		   = layouts.size( );
		layout_info.pSetLayouts			   = layouts.data( );
		layout_info.pushConstantRangeCount = specification.Constants.size( );
		layout_info.pPushConstantRanges	   = specification.Constants.data( );

		state = vk::Check( vkCreatePipelineLayout( logical, tiny_rvalue( layout_info ), vk::GetAllocator( ), tiny_rvalue( _layout ) ) );
	}

	return state;
}

VkPipelineVertexInputStateCreateInfo TinyGraphicPipeline::GetVertexInputState( 
	const TinyGraphicPipelineSpecification& specification
) const {
	auto vertex_inputs = VkPipelineVertexInputStateCreateInfo{ VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO };

	vertex_inputs.pNext							  = VK_NULL_HANDLE;
	vertex_inputs.flags							  = VK_NULL_FLAGS;
	vertex_inputs.vertexBindingDescriptionCount   = specification.InputBinding.size( );
	vertex_inputs.pVertexBindingDescriptions	  = specification.InputBinding.data( );
	vertex_inputs.vertexAttributeDescriptionCount = specification.InputAttributes.size( );
	vertex_inputs.pVertexAttributeDescriptions	  = specification.InputAttributes.data( );

	return vertex_inputs;
}

VkPipelineInputAssemblyStateCreateInfo TinyGraphicPipeline::GetInputAssemblyState(
	const TinyGraphicPipelineSpecification& specification
) const {
	auto assembly_state = VkPipelineInputAssemblyStateCreateInfo{ VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO };

	assembly_state.pNext				  = VK_NULL_HANDLE;
	assembly_state.flags				  = VK_NULL_FLAGS;
	assembly_state.topology				  = specification.Topology;

	if (
		specification.Topology == VK_PRIMITIVE_TOPOLOGY_LINE_STRIP				   ||
		specification.Topology == VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP			   ||
		specification.Topology == VK_PRIMITIVE_TOPOLOGY_TRIANGLE_FAN			   ||
		specification.Topology == VK_PRIMITIVE_TOPOLOGY_LINE_STRIP_WITH_ADJACENCY ||
		specification.Topology == VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP_WITH_ADJACENCY
	)
		assembly_state.primitiveRestartEnable = VK_TRUE;
	else 
		assembly_state.primitiveRestartEnable = VK_FALSE;

	return assembly_state;
}

VkPipelineTessellationStateCreateInfo TinyGraphicPipeline::GetTessellationState(
	const TinyGraphicPipelineSpecification& specification
) const {
	auto tessellation_state = VkPipelineTessellationStateCreateInfo{ VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_STATE_CREATE_INFO };

	tessellation_state.pNext			  = VK_NULL_HANDLE;
	tessellation_state.flags			  = VK_NULL_FLAGS;
	tessellation_state.patchControlPoints = specification.Tessellation;

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
	const TinyGraphicPipelineSpecification& specification
) const {
	auto depth_stencil_state = VkPipelineDepthStencilStateCreateInfo{ VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO };
	auto depth_state		 = specification.DepthEnable ? VK_TRUE : VK_FALSE;
	auto& viewport			 = boundaries.GetSwapViewport( );

	depth_stencil_state.pNext				  = VK_NULL_HANDLE;
	depth_stencil_state.flags				  = VK_NULL_FLAGS;
	depth_stencil_state.depthTestEnable		  = depth_state;
	depth_stencil_state.depthWriteEnable	  = depth_state;
	depth_stencil_state.depthCompareOp		  = specification.DepthOperation;
	depth_stencil_state.depthBoundsTestEnable = depth_state;
	depth_stencil_state.stencilTestEnable	  = specification.StencilEnable ? VK_TRUE : VK_FALSE;
	depth_stencil_state.front				  = specification.DepthStencilFront;
	depth_stencil_state.back				  = specification.DepthStencilBack;
	depth_stencil_state.minDepthBounds		  = viewport.minDepth;
	depth_stencil_state.maxDepthBounds		  = viewport.maxDepth;

	return depth_stencil_state;
}

VkPipelineColorBlendStateCreateInfo TinyGraphicPipeline::GetColorBlendState(
	const TinyGraphicPipelineSpecification& specification
) const {
	auto color_blend_state = VkPipelineColorBlendStateCreateInfo{ VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO };

	color_blend_state.pNext			  = VK_NULL_HANDLE;
	color_blend_state.flags			  = VK_NULL_FLAGS;
	color_blend_state.logicOpEnable   = VK_FALSE;
	color_blend_state.logicOp		  = VK_LOGIC_OP_COPY;
	color_blend_state.attachmentCount = specification.ColorBlends.size( );
	color_blend_state.pAttachments	  = specification.ColorBlends.data( );
	color_blend_state.blendConstants[ 0 ] = 1.f;
	color_blend_state.blendConstants[ 1 ] = 1.f;
	color_blend_state.blendConstants[ 2 ] = 1.f;
	color_blend_state.blendConstants[ 3 ] = 1.f;

	return color_blend_state;
}

VkPipelineDynamicStateCreateInfo TinyGraphicPipeline::GetDynamicStates( 
	const TinyGraphicPipelineSpecification& specification
) {
	auto states = VkPipelineDynamicStateCreateInfo{ VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO };

	states.pNext			 = VK_NULL_HANDLE;
	states.flags			 = VK_NULL_FLAGS;
	states.dynamicStateCount = specification.Dynamics.size( );
	states.pDynamicStates    = specification.Dynamics.data( );

	return states;
}

void TinyGraphicPipeline::GrabProperties( const TinyGraphicPipelineSpecification& specification ) {
	_properties.PassType = specification.PassType;
	_properties.Dynamics = specification.Dynamics;
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
