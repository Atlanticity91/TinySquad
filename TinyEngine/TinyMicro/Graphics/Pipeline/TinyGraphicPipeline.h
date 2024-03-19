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
 * @creation : 20/10/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "Utils/TinyGraphicPipelineDrawcall.h"

#define _pCreateSetBind2( BUNDLE, SET, BINDING, TYPE, COUNT, STAGE )\
	BUNDLE##.Descriptors[ SET ][ BINDING ].binding			  = BINDING;\
	BUNDLE##.Descriptors[ SET ][ BINDING ].descriptorType	  = tiny_cast( TYPE, VkDescriptorType );\
	BUNDLE##.Descriptors[ SET ][ BINDING ].descriptorCount	  = COUNT;\
	BUNDLE##.Descriptors[ SET ][ BINDING ].stageFlags		  = tiny_cast( STAGE, VkShaderStageFlagBits );\
	BUNDLE##.Descriptors[ SET ][ BINDING ].pImmutableSamplers = VK_NULL_HANDLE

#define _pCreateSetBind( BUNDLE, SET, BINDING, TYPE, STAGE )\
	_pCreateSetBind2( BUNDLE, SET, BINDING, TYPE, 1, STAGE )

tm_class TinyGraphicPipeline { 

private:
	VkPipeline					  _pipeline;
	VkPipelineLayout			  _layout;
	TinyGraphicPipelineProperties _properties;
	TinyGraphicDescriptorManager  _descriptors;

public:
	TinyGraphicPipeline( );

	~TinyGraphicPipeline( ) = default;

	bool Create( 
		TinyGraphicContext& graphic,
		const TinyLimitsStack& limits,
		const TinyGraphicPipelineBundle& bundle
	);

	void Mount( TinyGraphicWorkContext& work_context );

	tiny_inline void SetViewport( 
		TinyGraphicWorkContext& work_context,
		const VkViewport& viewport 
	);

	void SetViewport( 
		TinyGraphicWorkContext& work_context, 
		tiny_init<VkViewport> viewport 
	);

	tiny_inline void SetScissor( 
		TinyGraphicWorkContext& work_context, 
		const VkScissor& scissor 
	);

	void SetScissor( 
		TinyGraphicWorkContext& work_context, 
		tiny_init<VkScissor> scissor 
	);

	void SetCullMode(
		TinyGraphicWorkContext& work_context, 
		VkCullModeFlags cull_mode 
	);

	void SetFrontFace( 
		TinyGraphicWorkContext& work_context, 
		VkFrontFace front_face 
	);

	void SetPrimitiveRestartEnable( 
		TinyGraphicWorkContext& work_context, 
		bool is_active 
	);

	void SetPrimitiveTopology( 
		TinyGraphicWorkContext& work_context, 
		VkPrimitiveTopology topology 
	);

	void SetRasterizerDiscardEnable(
		TinyGraphicWorkContext& work_context, 
		bool is_active 
	);

	void SetBlendConstants( 
		TinyGraphicWorkContext& work_context, 
		const float* constants 
	);

	void SetBlendConstants( 
		TinyGraphicWorkContext& work_context, 
		const tiny_vec4& constant 
	);

	void SetDepthTestEnable( 
		TinyGraphicWorkContext& work_context, 
		bool is_active 
	);

	void SetDepthCompareOp( TinyGraphicWorkContext& work_context, VkCompareOp operation );

	void SetDepthWriteEnable( TinyGraphicWorkContext& work_context, bool is_active );

	void SetDepthBias( 
		TinyGraphicWorkContext& work_context,
		float constant,
		float clamp, 
		float slope 
	);

	void SetDepthBounds( TinyGraphicWorkContext& work_context, float minimum, float maximum );

	void SetDeviceMask( TinyGraphicWorkContext& work_context, tiny_uint mask );

	void SetLineWidth( TinyGraphicWorkContext& work_context, float width );

	void SetStencilOp(
		TinyGraphicWorkContext& work_context,
		VkStencilFaceFlags face_mask,
		VkStencilOp fail_operation,
		VkStencilOp pass_operation,
		VkStencilOp depth_fail_operation,
		VkCompareOp compare_operation
	);

	void SetStencilCompareMask( 
		TinyGraphicWorkContext& work_context, 
		VkStencilFaceFlags face_mask, 
		tiny_uint compare_mask 
	);

	void SetStencilReference( 
		TinyGraphicWorkContext& work_context, 
		VkStencilFaceFlags face_mask, 
		tiny_uint reference 
	);

	void SetStencilWriteMask(
		TinyGraphicWorkContext& work_context, 
		VkStencilFaceFlags face_mask, 
		tiny_uint write_mask 
	);

	void Push( 
		TinyGraphicWorkContext& work_context, 
		const TinyGraphicPipelineConstant& constant 
	);

	tiny_inline void Bind(
		TinyGraphicLogical& logical,
		TinyGraphicWorkContext& work_context,
		const TinyGraphicPipelineBindpoint& bindpoint
	);

	void Bind( 
		TinyGraphicLogical& logical,
		TinyGraphicWorkContext& work_context,
		tiny_init<TinyGraphicPipelineBindpoint> bindpoints
	);

	void Bind(
		TinyGraphicLogical& logical,
		TinyGraphicWorkContext& work_context,
		tiny_list<TinyGraphicPipelineBindpoint> bindpoints
	);

	void Bind(
		TinyGraphicLogical& logical,
		TinyGraphicWorkContext& work_context,
		tiny_uint count,
		TinyGraphicPipelineBindpoint* bindpoints
	);

	tiny_inline void BindVertex(
		TinyGraphicWorkContext& work_context,
		const TinyGraphicBuffer& buffer
	);

	void BindVertex(
		TinyGraphicWorkContext& work_context,
		tiny_uint binding,
		const TinyGraphicBuffer& buffer 
	);

	tiny_inline void BindVertex(
		TinyGraphicWorkContext& work_context,
		const TinyGraphicPipelineVertex& vertex
	);

	void BindVertex(
		TinyGraphicWorkContext& work_context,
		tiny_uint binding,
		const TinyGraphicPipelineVertex& vertex
	);

	tiny_inline void BindVertex(
		TinyGraphicWorkContext& work_context,
		tiny_init<TinyGraphicPipelineVertex> vertexes
	);

	void BindVertex(
		TinyGraphicWorkContext& work_context,
		tiny_uint binding,
		tiny_init<TinyGraphicPipelineVertex> vertexes
	);

	void BindIndex( 
		TinyGraphicWorkContext& work_context, 
		const TinyGraphicBuffer& buffer 
	);

	void BindGeometry( 
		TinyGraphicWorkContext& work_context,
		const TinyGraphicBuffer& vertex,
		const TinyGraphicBuffer& index
	);

	void Draw(
		TinyGraphicWorkContext& work_context,
		const TinyGraphicPipelineDrawcall& draw_call 
	);

	tiny_inline void Draw( 
		TinyGraphicLogical& logical,
		TinyGraphicWorkContext& work_context,
		const TinyGraphicPipelineDrawcall& draw_call,
		tiny_init<TinyGraphicPipelineBindpoint> bindpoints
	);

	tiny_inline void Draw(
		TinyGraphicLogical& logical,
		TinyGraphicWorkContext& work_context,
		const TinyGraphicPipelineDrawcall& draw_call,
		tiny_list<TinyGraphicPipelineBindpoint> bindpoints
	);

	void Terminate( TinyGraphicContext& context );

private:
	bool CreateRenderPipeline( 
		TinyGraphicContext& graphic,
		const TinyGraphicPipelineBundle& bundle
	);

	bool CreateComputePipeline( 
		TinyGraphicContext& graphic,
		const TinyGraphicPipelineBundle& bundle
	);

public:
	template<typename Type>
	void Push( 
		TinyGraphicWorkContext& work_context, 
		VkShaderStageFlags stage, 
		const Type& data 
	) {
		Push<Type>( work_context, stage, 0, data );
	};

	template<typename Type>
	void Push(
		TinyGraphicWorkContext& work_context,
		VkShaderStageFlags stage, 
		tiny_uint offset, 
		const Type& data 
	) {
		Push( work_context, { stage, offset, data } );
	};

public:
	bool GetIsValid( ) const;

	const VkPipeline Get( ) const;

	const VkPipelineLayout GetLayout( ) const;

	VkDescriptorSet GetSet( 
		TinyGraphicWorkContext& work_context,
		tiny_uint set_id 
	) const;

	VkDescriptorSet GetSet(
		tiny_uint set_id,
		tiny_uint work_id
	) const;

private:
	bool GetPipelineLayout( 
		TinyGraphicLogical& logical,
		const TinyLimitsStack& limits,
		const TinyGraphicPipelineBundle& bundle 
	);

	VkPipelineVertexInputStateCreateInfo GetVertexInputState( 
		const TinyGraphicPipelineBundle& bundle
	) const;

	VkPipelineInputAssemblyStateCreateInfo GetInputAssemblyState ( 
		const TinyGraphicPipelineBundle& bundle
	) const;

	VkPipelineTessellationStateCreateInfo GetTessellationState( 
		const TinyGraphicPipelineBundle& bundle
	) const;

	VkPipelineViewportStateCreateInfo GetViewport( ) const;

	VkPipelineRasterizationStateCreateInfo GetRasterizationState( ) const;

	VkPipelineMultisampleStateCreateInfo GetMultisampleState( ) const;

	VkPipelineDepthStencilStateCreateInfo GetDepthStencilState(
		const TinyGraphicBoundaries& boundaries, 
		const TinyGraphicPipelineBundle& bundle
	) const;

	VkPipelineColorBlendStateCreateInfo GetColorBlendState( 
		const TinyGraphicPipelineBundle& bundle
	) const;

	VkPipelineDynamicStateCreateInfo GetDynamicStates( const TinyGraphicPipelineBundle& bundle );

	void GrabProperties( const TinyGraphicPipelineBundle& bundle );

	void GrabBindpoint(
		VkWriteDescriptorSet& descriptor,
		const TinyGraphicPipelineBindpoint& bindpoint,
		tiny_uint work_id
	) const;

public:
	operator const VkPipeline ( ) const;

	operator const VkPipelineLayout ( ) const;

};
