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

#pragma once

#include <TinyMicro/Graphics/Pipeline/Shaders/TinyGraphicShader.h>

typedef tiny_list<VkDescriptorSetLayoutBinding> TinyDescriptorSet;
typedef tiny_list<TinyDescriptorSet> TinyDescriptorLayout;

tm_class TinyGraphicDescriptorSet final {

private:
	VkDescriptorSetLayout	   _layout;
	tiny_list<VkDescriptorSet> _sets;

public:
	TinyGraphicDescriptorSet( );

	~TinyGraphicDescriptorSet( ) = default;

	bool Create( 
		TinyGraphicLogical& logical,
		VkDescriptorPool& descriptor_pool,
		const TinyDescriptorSet& layout,
		tiny_uint set_count
	);

	void Terminate( 
		const TinyGraphicLogical& logical, 
		VkDescriptorPool& descriptor_pool 
	);

private:
	bool CreateLayout( 
		TinyGraphicLogical& logical,
		const TinyDescriptorSet& layout
	);

	bool CreateSet( 
		TinyGraphicLogical& logical,
		VkDescriptorPool& descriptor_pool,
		tiny_uint set_count
	);

public:
	VkDescriptorSet Get( tiny_uint work_id ) const;

	const tiny_list<VkDescriptorSet>& Get( ) const;

	const VkDescriptorSetLayout& GetLayout( ) const;

};
