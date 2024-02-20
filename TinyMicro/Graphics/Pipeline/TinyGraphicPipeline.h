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

#define _pCreateSetBind2( SET, BINDING, TYPE, COUNT, STAGE )\
	SET[ BINDING ].binding			  = BINDING;\
	SET[ BINDING ].descriptorType	  = tiny_cast( TYPE, VkDescriptorType );\
	SET[ BINDING ].descriptorCount	  = COUNT;\
	SET[ BINDING ].stageFlags		  = tiny_cast( STAGE, VkShaderStageFlagBits );\
	SET[ BINDING ].pImmutableSamplers = VK_NULL_HANDLE

#define _pCreateSetBind( SET, BINDING, TYPE, STAGE )\
	_pCreateSetBind2( SET, BINDING, TYPE, 1, STAGE )

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
