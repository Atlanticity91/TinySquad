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
			CreateSet( logical, descriptor_pool, set_count );
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

bool TinyGraphicDescriptorSet::CreateLayout( 
	TinyGraphicLogical& logical,
	const TinyDescriptorSet& layout
) {
	auto layout_info = VkDescriptorSetLayoutCreateInfo{ VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO };

	layout_info.pNext		 = VK_NULL_HANDLE;
	layout_info.flags		 = VK_NULL_FLAGS;
	layout_info.bindingCount = layout.size( );
	layout_info.pBindings    = layout.data( );

	return vk::Check( vkCreateDescriptorSetLayout( logical, &layout_info, vk::GetAllocator( ), &_layout ) );
}

bool TinyGraphicDescriptorSet::CreateSet( 
	TinyGraphicLogical& logical,
	VkDescriptorPool& descriptor_pool,
	tiny_uint set_count
) {
	auto set_info = VkDescriptorSetAllocateInfo{ VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO };
	auto layouts  = tiny_list<VkDescriptorSetLayout>{ };

	_sets   = set_count;
	layouts = set_count;

	for ( auto& layout : layouts )
		layout = _layout;

	set_info.pNext				= VK_NULL_HANDLE;
	set_info.descriptorPool		= descriptor_pool;
	set_info.descriptorSetCount = set_count;
	set_info.pSetLayouts		= layouts.data( );

	return vk::Check( vkAllocateDescriptorSets( logical, &set_info, _sets.data( ) ) );
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
