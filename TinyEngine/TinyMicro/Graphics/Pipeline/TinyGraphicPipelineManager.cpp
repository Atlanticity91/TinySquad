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

#include <TinyMicro/__tiny_micro_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyGraphicPipelineManager::TinyGraphicPipelineManager( )
	: m_cache{ },
	m_limits{ }
{ }

bool TinyGraphicPipelineManager::Initialize( 
	TinyFilesystem& filesystem,
	TinyGraphicPhysical& physical,
	TinyGraphicLogical& logical
) {
	auto state = m_cache.Create( filesystem, physical, logical );

	if ( state )
		CreateDescriptorLimits( );

	return state;
}


void TinyGraphicPipelineManager::EnableCache( ) { m_cache.Enable( ); }

void TinyGraphicPipelineManager::DisableCache( ) { m_cache.Disable( ); }

TinyGraphicPipelineSpecification TinyGraphicPipelineManager::Create(
	const TinyGraphicPipelineTypes type 
) {
	auto pipeline = TinyGraphicPipelineSpecification{ };

	switch ( type ) {
		case TGP_TYPE_2D	  : pipeline = CreatePipeline2D( );		 break;
		case TGP_TYPE_3D	  : pipeline = CreatePipeline3D( );		 break;
		case TGP_TYPE_COMPUTE : pipeline = CreatePipelineCompute( ); break;

		default : break;
	}

	return pipeline;
}

void TinyGraphicPipelineManager::Terminate(
	TinyFilesystem& filesystem,
	TinyGraphicPhysical& physical,
	TinyGraphicLogical& logical
) {
	m_cache.Terminate( filesystem, physical, logical );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE ===
////////////////////////////////////////////////////////////////////////////////////////////
void TinyGraphicPipelineManager::CreateDescriptorLimits( ) {
	const tiny_uint MAX_DESCRIPTOR = 128;

	m_limits.create( VK_DESCRIPTOR_TYPE_SAMPLER,				MAX_DESCRIPTOR );
	m_limits.create( VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, MAX_DESCRIPTOR );
	m_limits.create( VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE,		    MAX_DESCRIPTOR );
	m_limits.create( VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,		    MAX_DESCRIPTOR );
	m_limits.create( VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,		    MAX_DESCRIPTOR );
	m_limits.create( VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT,	    MAX_DESCRIPTOR );
}

TinyGraphicPipelineSpecification TinyGraphicPipelineManager::CreatePipeline2D( ) {
	auto pipeline = TinyGraphicPipelineSpecification{ };

	pipeline.InputBinding = 1;
	pipeline.InputBinding[ 0 ].binding   = tiny_cast( 0, tiny_uint );
	pipeline.InputBinding[ 0 ].stride	 = tiny_sizeof( VkVertex2D );
	pipeline.InputBinding[ 0 ].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

	pipeline.InputAttributes = 2;
	pipeline.InputAttributes[ 0 ].location = 0;
	pipeline.InputAttributes[ 0 ].binding  = pipeline.InputBinding[ 0 ].binding;
	pipeline.InputAttributes[ 0 ].format   = VK_FORMAT_R32G32_SFLOAT;
	pipeline.InputAttributes[ 0 ].offset   = tiny_offset_of( Location, VkVertex2D );

	pipeline.InputAttributes[ 1 ].location = 1;
	pipeline.InputAttributes[ 1 ].binding  = pipeline.InputBinding[ 0 ].binding;
	pipeline.InputAttributes[ 1 ].format   = VK_FORMAT_R32G32_SFLOAT;
	pipeline.InputAttributes[ 1 ].offset   = tiny_offset_of( UV, VkVertex2D );

	return pipeline;
}

TinyGraphicPipelineSpecification TinyGraphicPipelineManager::CreatePipeline3D( ) {
	auto pipeline = TinyGraphicPipelineSpecification{ };

	pipeline.InputBinding = 1;
	pipeline.InputBinding[ 0 ].binding   = tiny_cast( 0, tiny_uint );
	pipeline.InputBinding[ 0 ].stride    = tiny_sizeof( VkVertex3D );
	pipeline.InputBinding[ 0 ].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

	pipeline.InputAttributes = 2;
	pipeline.InputAttributes[ 0 ].location = 0;
	pipeline.InputAttributes[ 0 ].binding  = pipeline.InputBinding[ 0 ].binding;
	pipeline.InputAttributes[ 0 ].format   = VK_FORMAT_R32G32B32_SFLOAT;
	pipeline.InputAttributes[ 0 ].offset   = tiny_offset_of( Location, VkVertex3D );

	pipeline.InputAttributes[ 1 ].location = 1;
	pipeline.InputAttributes[ 1 ].binding  = pipeline.InputBinding[ 0 ].binding;
	pipeline.InputAttributes[ 1 ].format   = VK_FORMAT_R32G32_SFLOAT;
	pipeline.InputAttributes[ 1 ].offset   = tiny_offset_of( UV, VkVertex3D );

	return pipeline;
}

TinyGraphicPipelineSpecification TinyGraphicPipelineManager::CreatePipelineCompute( ) {
	auto pipeline = TinyGraphicPipelineSpecification{ };

	return pipeline;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyGraphicPipelineManager::GetUseCache( ) const { return m_cache.GetUseCache( ); }

const VkPipelineCache& TinyGraphicPipelineManager::GetCache( ) const { return m_cache; }

const TinyLimitsStack& TinyGraphicPipelineManager::GetLimits( ) const { return m_limits; }
