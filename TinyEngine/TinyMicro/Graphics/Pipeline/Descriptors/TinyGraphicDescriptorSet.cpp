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
TinyGraphicDescriptorSet::TinyGraphicDescriptorSet( )
	: _layout{ VK_NULL_HANDLE },
	_sets{ }
{ }

bool TinyGraphicDescriptorSet::Create( 
	TinyGraphicLogical& logical, 
	VkDescriptorPool& descriptor_pool,
	const TinyDescriptorSet& layout,
	tiny_uint set_count
) {
	return  CreateLayout( logical, layout ) &&
			CreateSet( logical, layout, descriptor_pool, set_count );
}

void TinyGraphicDescriptorSet::Terminate(
	const TinyGraphicLogical& logical,
	VkDescriptorPool& descriptor_pool
) {
	if ( _sets.size( ) > 0 && vk::GetIsValid( _sets[ 0 ] ) )
		vk::Check( vkFreeDescriptorSets( logical, descriptor_pool, _sets.size( ), _sets.data( ) ) );

	if ( vk::GetIsValid( _layout ) )
		vkDestroyDescriptorSetLayout( logical, _layout, vk::GetAllocator( ) );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE ===
////////////////////////////////////////////////////////////////////////////////////////////
void TinyGraphicDescriptorSet::CreateIndexing(
	VkDescriptorSetLayoutBindingFlagsCreateInfo& binding_flags,
	tiny_list<VkDescriptorBindingFlags>& indexing,
	const TinyDescriptorSet& layout
) {
	auto variable_flags = VK_DESCRIPTOR_BINDING_PARTIALLY_BOUND_BIT | VK_DESCRIPTOR_BINDING_VARIABLE_DESCRIPTOR_COUNT_BIT_EXT;
	auto binding_id		= layout.size( );

	indexing = binding_id;

	while ( binding_id-- > 0 ) {
		if ( layout[ binding_id ].descriptorCount == 1 )
			indexing[ binding_id ] = VK_NULL_FLAGS;
		else
			indexing[ binding_id ] = variable_flags;
	}

	binding_flags.pNext			= VK_NULL_HANDLE;
	binding_flags.bindingCount  = indexing.size( );
	binding_flags.pBindingFlags = indexing.data( );
}

bool TinyGraphicDescriptorSet::CreateLayout( 
	TinyGraphicLogical& logical,
	const TinyDescriptorSet& layout
) {
	auto binding_flags = VkDescriptorSetLayoutBindingFlagsCreateInfo{ VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_BINDING_FLAGS_CREATE_INFO };
	auto layout_info   = VkDescriptorSetLayoutCreateInfo{ VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO };
	auto indexing	   = tiny_list<VkDescriptorBindingFlags>{ };

	CreateIndexing( binding_flags, indexing, layout );

	layout_info.pNext		 = tiny_rvalue( binding_flags );
	layout_info.flags		 = VK_NULL_FLAGS;
	layout_info.bindingCount = layout.size( );
	layout_info.pBindings    = layout.data( );

	return vk::Check( vkCreateDescriptorSetLayout( logical, tiny_rvalue( layout_info ), vk::GetAllocator( ), tiny_rvalue( _layout ) ) );
}

void TinyGraphicDescriptorSet::CreateVariableSet(
	VkDescriptorSetVariableDescriptorCountAllocateInfo& variable_info,
	tiny_list<tiny_uint>& variable_size,
	const TinyDescriptorSet& layout,
	tiny_uint set_count
) {
	while ( set_count-- > 0 ) {
		auto binding_id = layout.size( );

		while ( binding_id-- > 0 ) {
			auto count = layout[ binding_id ].descriptorCount;

			if ( count > 1 )
				variable_size.emplace_back( count );
		}
	}

	variable_info.pNext				 = VK_NULL_HANDLE;
	variable_info.descriptorSetCount = variable_size.size( );
	variable_info.pDescriptorCounts  = variable_size.data( );
}

void TinyGraphicDescriptorSet::CreateSetLayout(
	tiny_list<VkDescriptorSetLayout>& layouts,
	tiny_uint set_count
) {
	_sets   = set_count;
	layouts = set_count;

	for ( auto& layout : layouts )
		layout = _layout;
}

bool TinyGraphicDescriptorSet::CreateSet( 
	TinyGraphicLogical& logical,
	const TinyDescriptorSet& layout,
	VkDescriptorPool& descriptor_pool,
	tiny_uint set_count
) {
	auto variable_info = VkDescriptorSetVariableDescriptorCountAllocateInfo{ VK_STRUCTURE_TYPE_DESCRIPTOR_SET_VARIABLE_DESCRIPTOR_COUNT_ALLOCATE_INFO };
	auto variable_size = tiny_list<tiny_uint>{ };
	auto set_info	   = VkDescriptorSetAllocateInfo{ VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO };
	auto layouts	   = tiny_list<VkDescriptorSetLayout>{ };

	CreateVariableSet( variable_info, variable_size, layout, set_count );
	CreateSetLayout( layouts, set_count );
	
	set_info.pNext				= tiny_rvalue( variable_info );
	set_info.descriptorPool		= descriptor_pool;
	set_info.descriptorSetCount = set_count;
	set_info.pSetLayouts		= layouts.data( );

	return vk::Check( vkAllocateDescriptorSets( logical, tiny_rvalue( set_info ), _sets.data( ) ) );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
VkDescriptorSet TinyGraphicDescriptorSet::Get( tiny_uint work_id ) const {
	return _sets[ work_id ];
}

const tiny_list<VkDescriptorSet>& TinyGraphicDescriptorSet::Get( ) const { return _sets; }

const VkDescriptorSetLayout& TinyGraphicDescriptorSet::GetLayout( ) const { 
	return _layout; 
}
