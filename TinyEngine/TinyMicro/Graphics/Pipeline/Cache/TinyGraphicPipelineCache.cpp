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
 * @creation : 26/07/2024
 * @version  : 2024.2.8
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#include <TinyMicro/__tiny_micro_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyGraphicPipelineCache::TinyGraphicPipelineCache( )
	: m_use_cache{ true },
	m_cache{ VK_NULL_HANDLE } 
{ }

void TinyGraphicPipelineCache::Enable( ) { m_use_cache = true; }

void TinyGraphicPipelineCache::Disable( ) { m_use_cache = false; }

bool TinyGraphicPipelineCache::Create(
	TinyFilesystem& filesystem,
	TinyGraphicPhysical& physical,
	TinyGraphicLogical& logical
) {
	auto cache_data = Load( filesystem, physical );
	auto cache_info = VkPipelineCacheCreateInfo{ VK_STRUCTURE_TYPE_PIPELINE_CACHE_CREATE_INFO };
	auto state		= false;

	cache_info.pNext		   = VK_NULL_HANDLE;
	cache_info.flags		   = VK_NULL_FLAGS;

	if ( cache_data.GetIsValid( ) ) {
		cache_info.initialDataSize = cache_data.Capacity;
		cache_info.pInitialData    = cache_data.GetAddress( );
	} else {
		cache_info.initialDataSize = tiny_cast( 0, tiny_ulong );
		cache_info.pInitialData    = VK_NULL_HANDLE;
	}
	
	state = vk::Check( vkCreatePipelineCache( logical, tiny_rvalue( cache_info ), vk::GetAllocator( ), tiny_rvalue( m_cache ) ) );

	if ( cache_data.GetIsValid( ) )
		tiny_deallocate( cache_data );

	return state;
}

void TinyGraphicPipelineCache::Terminate(
	TinyFilesystem& filesystem,
	TinyGraphicPhysical& physical,
	TinyGraphicLogical& logical 
) {
	if ( vk::GetIsValid( m_cache ) ) {
		if ( m_use_cache )
			Save( filesystem, physical, logical );

		vkDestroyPipelineCache( logical, m_cache, vk::GetAllocator( ) );
	}
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE ===
////////////////////////////////////////////////////////////////////////////////////////////
tiny_storage TinyGraphicPipelineCache::Load(
	TinyFilesystem& filesystem,
	TinyGraphicPhysical& physical
) {
	auto cache_path = filesystem.GetCachePath( );
	auto cache_data = tiny_storage{ TS_TYPE_HEAP };

	if ( m_use_cache && filesystem.GetFileExist( cache_path ) ) {
		auto header = TinyGraphicPipelineCacheHeader{ };

		TINY_OPEN_FILE( file, filesystem, cache_path, TF_ACCESS_BINARY_READ );

		file->Read( header );

		if ( strcmp( header.Magic, TINY_VULKAN_PIPELINE_CACHE ) == 0 ) {
			auto& properties = physical.GetProperties( );

			if (
				header.Vendor == properties.vendorID &&
				header.Device == properties.deviceID
			) {
				if ( tiny_allocate( cache_data, header.Size ) ) {
					auto* data = cache_data.GetAddress( );

					file->Read( header.Size, data );

					auto new_crc = TinyMath::CRC32( header.Size, data );

					if ( header.CRC != new_crc )
						tiny_deallocate( cache_data );
				}
			}
		}
	}

	return cache_data;
}

void TinyGraphicPipelineCache::Save(
	TinyFilesystem& filesystem,
	TinyGraphicPhysical& physical,
	TinyGraphicLogical& logical
) {
	auto cache_data = tiny_storage{ TS_TYPE_HEAP };
	auto capacity   = tiny_cast( 0, tiny_ulong );
	
	if ( 
		vk::Check( vkGetPipelineCacheData( logical, m_cache, tiny_rvalue( capacity ), VK_NULL_FLAGS ) ) && 
		tiny_allocate( cache_data, capacity )
	) {
		auto* data = cache_data.GetAddress( );

		if ( vk::Check( vkGetPipelineCacheData( logical, m_cache, tiny_rvalue( capacity ), data ) ) ) {
			auto cache_path = filesystem.GetCachePath( );
			auto header		= TinyGraphicPipelineCacheHeader{ };

			TINY_OPEN_FILE( file, filesystem, cache_path, TF_ACCESS_BINARY_WRITE );

			if ( file->GetIsValid( ) ) {
				auto& properties = physical.GetProperties( );

				header.CRC    = TinyMath::CRC32( capacity, data );
				header.Vendor = properties.vendorID;
				header.Device = properties.deviceID;
				header.Size   = capacity;

				file->Write( header );
				file->Write( capacity, data );
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyGraphicPipelineCache::GetUseCache( ) const { return m_use_cache; }

const VkPipelineCache& TinyGraphicPipelineCache::Get( ) const { return m_cache; }

////////////////////////////////////////////////////////////////////////////////////////////
//		===	OPERATOR ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyGraphicPipelineCache::operator const VkPipelineCache& ( ) const { return Get( ); }
