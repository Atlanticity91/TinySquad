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
	: m_use_cache{ true },
	m_cache{ VK_NULL_HANDLE },
	m_limits{ }
{ }

bool TinyGraphicPipelineManager::Initialize( 
	TinyFilesystem& filesystem, 
	TinyGraphicLogical& logical
) {
	auto state = CreateCache( filesystem, logical );

	if ( state )
		CreateDescriptorLimits( );

	return state;
}


void TinyGraphicPipelineManager::EnableCache( ) { m_use_cache = true; }

void TinyGraphicPipelineManager::DisableCache( ) { m_use_cache = false; }

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
	TinyGraphicLogical& logical
) {
	if ( m_use_cache && vk::GetIsValid( m_cache ) ) {
		WriteCache( filesystem, logical );

		vkDestroyPipelineCache( logical, m_cache, vk::GetAllocator( ) );
	}
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE ===
////////////////////////////////////////////////////////////////////////////////////////////
tiny_list<tiny_ubyte> TinyGraphicPipelineManager::LoadCache( TinyFilesystem& filesystem ) {
	auto cache_data = tiny_list<tiny_ubyte>{ };
	auto cache_path = filesystem.GetCachePath( );

	if ( m_use_cache && filesystem.GetFileExist( cache_path ) ) {
		auto file = filesystem.OpenFile( cache_path, TF_ACCESS_BINARY_READ );
		auto length = tiny_cast( file.GetSize( ), tiny_uint );

		cache_data = length;

		auto* data = tiny_cast( cache_data.data( ), native_pointer );

		file.ReadAll( length, data );
	}

	return cache_data;
}

void TinyGraphicPipelineManager::WriteCache( 
	TinyFilesystem& filesystem, 
	TinyGraphicLogical& logical
) {
	auto cache_data = tiny_list<tiny_ubyte>{ };
	auto cache_path = filesystem.GetCachePath( );

	if ( vk::GetPipelineCache( logical, m_cache, cache_data ) ) {
		auto* data  = tiny_cast( cache_data.data( ), const native_pointer );
		auto length = tiny_cast( cache_data.size( ), tiny_uint );

		filesystem.Dump( cache_path, length, data );
	}
}

bool TinyGraphicPipelineManager::CreateCache( 
	TinyFilesystem& filesystem, 
	TinyGraphicLogical& logical 
) {
	auto cache_data = LoadCache( filesystem );
	auto cache_info = VkPipelineCacheCreateInfo{ VK_STRUCTURE_TYPE_PIPELINE_CACHE_CREATE_INFO };

	cache_info.pNext		   = VK_NULL_HANDLE;
	cache_info.flags		   = VK_NULL_FLAGS;
	cache_info.initialDataSize = cache_data.size( );
	cache_info.pInitialData	   = cache_data.data( );

	return vk::Check( vkCreatePipelineCache( logical, tiny_rvalue( cache_info ), vk::GetAllocator( ), tiny_rvalue( m_cache ) ) );
}

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
bool TinyGraphicPipelineManager::GetUseCache( ) const { return m_use_cache; }

const VkPipelineCache& TinyGraphicPipelineManager::GetCache( ) const { return m_cache; }

const TinyLimitsStack& TinyGraphicPipelineManager::GetLimits( ) const { return m_limits; }
