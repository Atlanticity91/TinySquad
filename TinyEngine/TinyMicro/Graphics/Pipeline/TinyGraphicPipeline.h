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

#define _pCreateBinding( BUNDLE, BINDING, STRIDE, RATE )\
	BUNDLE##.InputBinding[ BINDING ].binding   = tiny_cast( BINDING, tiny_uint );\
	BUNDLE##.InputBinding[ BINDING ].stride    = tiny_cast( STRIDE, tiny_uint );\
	BUNDLE##.InputBinding[ BINDING ].inputRate = RATE

#define _pCreateAttribute( BUNDLE, LOCATION, BINDING, FORMAT, OFFSET )\
	BUNDLE##.InputAttributes[ LOCATION ].location = tiny_cast( LOCATION, tiny_uint );\
	BUNDLE##.InputAttributes[ LOCATION ].binding  = bundle.InputBinding[ tiny_cast( BINDING, tiny_uint ) ].binding;\
	BUNDLE##.InputAttributes[ LOCATION ].format   = tiny_cast( FORMAT, VkFormat );\
	BUNDLE##.InputAttributes[ LOCATION ].offset   = OFFSET

#define _pCreateSetBind2( BUNDLE, SET, BINDING, TYPE, COUNT, STAGE )\
	BUNDLE##.Descriptors[ SET ][ BINDING ].binding			  = tiny_cast( BINDING, tiny_uint );\
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
		TinyGraphicWorkContext& work_context,
		const TinyGraphicPipelineBindpoint& bindpoint
	);

	void Bind( 
		TinyGraphicWorkContext& work_context,
		tiny_init<TinyGraphicPipelineBindpoint> bindpoints
	);

	void Bind(
		TinyGraphicWorkContext& work_context,
		tiny_list<TinyGraphicPipelineBindpoint> bindpoints
	);

	void Bind(
		TinyGraphicWorkContext& work_context,
		tiny_uint count,
		TinyGraphicPipelineBindpoint* bindpoints
	);

	tiny_inline void Bind(
		TinyGraphicWorkContext& work_context,
		tiny_uint set,
		tiny_uint binding,
		tiny_init<VkDescriptorBufferInfo> buffers
	);

	void Bind(
		TinyGraphicWorkContext& work_context,
		tiny_uint set,
		tiny_uint binding,
		tiny_uint count,
		const VkDescriptorBufferInfo* buffers
	);

	tiny_inline void Bind(
		TinyGraphicWorkContext& work_context,
		tiny_uint set,
		tiny_uint binding,
		tiny_init<VkDescriptorImageInfo> samplers
	);

	void Bind(
		TinyGraphicWorkContext& work_context,
		tiny_uint set,
		tiny_uint binding,
		tiny_uint count,
		const VkDescriptorImageInfo* samplers
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

	tiny_inline void BindGeometry( 
		TinyGraphicWorkContext& work_context,
		const TinyGraphicBuffer& index,
		const TinyGraphicBuffer& vertex
	);

	void Draw(
		TinyGraphicWorkContext& work_context,
		const TinyGraphicPipelineDrawcall& draw_call 
	);

	tiny_inline void Draw(
		TinyGraphicWorkContext& work_context,
		const TinyGraphicPipelineDrawcall& draw_call,
		tiny_init<TinyGraphicPipelineBindpoint> bindpoints
	);

	tiny_inline void Draw(
		TinyGraphicWorkContext& work_context,
		const TinyGraphicPipelineDrawcall& draw_call,
		tiny_list<TinyGraphicPipelineBindpoint> bindpoints
	);

	void Terminate( TinyGraphicContext& context );

public:
	static void CreateBinding( 
		TinyGraphicPipelineBundle& bundle, 
		const TinyGraphicPipelineBinding& binding 
	);

	static void CreateBinding(
		TinyGraphicPipelineBundle& bundle,
		tiny_init<TinyGraphicPipelineBinding> bindings
	);

	static void CreateBinding(
		TinyGraphicPipelineBundle& bundle,
		tiny_uint binding,
		tiny_uint stride,
		bool is_vertex
	);

	static void CreateAttribute(
		TinyGraphicPipelineBundle& bundle,
		const TinyGraphicPipelineAttribute& attribute
	);

	static void CreateAttribute(
		TinyGraphicPipelineBundle& bundle,
		tiny_init<TinyGraphicPipelineAttribute> attributes
	);

	static void CreateAttribute( 
		TinyGraphicPipelineBundle& bundle,
		tiny_uint location,
		tiny_uint binding,
		TinyPipelineAttributeTypes type,
		tiny_uint offset
	);

	static void CreateSetBind(
		TinyGraphicPipelineBundle& bundle,
		tiny_uint set,
		const TinyGraphicPipelineSetBind& set_bind
	);

	static void CreateSetBind(
		TinyGraphicPipelineBundle& bundle,
		tiny_uint set,
		tiny_init<TinyGraphicPipelineSetBind> set_binds
	);

	static void CreateSetBind(
		TinyGraphicPipelineBundle& bundle,
		tiny_uint set,
		tiny_uint binding,
		TinyGraphicBindTypes type,
		TinyGraphicShaderStages stage
	);

	static void CreateSetBind(
		TinyGraphicPipelineBundle& bundle,
		tiny_uint set,
		tiny_uint binding,
		TinyGraphicBindTypes type,
		tiny_uint count,
		TinyGraphicShaderStages stage
	);

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
