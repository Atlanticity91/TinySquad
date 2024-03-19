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
 * @creation : 24/11/2023
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
TinyGraphicDescriptorManager::TinyGraphicDescriptorManager( )
	: _pool{ VK_NULL_HANDLE },
	_sets{ }
{ }

bool TinyGraphicDescriptorManager::Create(
	TinyGraphicLogical& logical, 
	const TinyLimitsStack& limits,
	const TinyDescriptorLayout& layout,
	tiny_uint set_count
) {
	auto state = CreatePool( logical, limits, layout, set_count );
	
	if ( state ) {
		auto set_id = layout.size( );

		_sets = set_id;

		while ( state && set_id-- > 0 )
			state = _sets[ set_id ].Create( logical, _pool, layout[ set_id ], set_count );
	}

	return state;
}

void TinyGraphicDescriptorManager::Terminate( const TinyGraphicLogical& logical ) {
	if ( vk::GetIsValid( _pool ) ) {
		for ( auto& set : _sets )
			set.Terminate( logical, _pool );

		vkDestroyDescriptorPool( logical, _pool, vk::GetAllocator( ) );
	}
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyGraphicDescriptorManager::CreatePool( 
	TinyGraphicLogical& logical,
	const TinyLimitsStack& limits,
	const TinyDescriptorLayout& layout,
	tiny_uint set_instance_count
) {
	auto pool_info = VkDescriptorPoolCreateInfo{ VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO };

	pool_info.pNext			= VK_NULL_HANDLE;
	pool_info.flags			= VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
	pool_info.maxSets		= layout.size( ) * set_instance_count;
	pool_info.poolSizeCount = limits.size( );
	pool_info.pPoolSizes	= limits.data( );
	
	return vk::Check( vkCreateDescriptorPool( logical, tiny_rvalue( pool_info ), vk::GetAllocator( ), tiny_rvalue( _pool ) ) );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
tiny_list<VkDescriptorSetLayout> TinyGraphicDescriptorManager::GetLayouts( ) {
	auto layout_count = _sets.size( );
	auto layouts	  = tiny_list<VkDescriptorSetLayout>{ };

	layouts = layout_count;

	while ( layout_count-- > 0 )
		layouts[ layout_count ] = _sets[ layout_count ].GetLayout( );

	return layouts;
}

tiny_list<VkDescriptorSet> TinyGraphicDescriptorManager::GetSets(
	tiny_uint work_id
) const {
	auto set_id = _sets.size( );
	auto sets   = tiny_list<VkDescriptorSet>{ };

	sets = _sets.size( );

	while ( set_id-- > 0 ) 
		sets[ set_id ] = _sets[ set_id ].Get( work_id );

	return sets;
}

const tiny_list<VkDescriptorSet>& TinyGraphicDescriptorManager::GetSet(
	tiny_uint set_id 
) const {
	return _sets[ set_id ].Get( );
}
