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

#include "TinyGraphicDescriptorSet.h"

typedef tiny_stack<VkDescriptorPoolSize, 6> TinyLimitsStack;

tm_class TinyGraphicDescriptorManager final {

private:
	VkDescriptorPool					_pool;
	tiny_list<TinyGraphicDescriptorSet> _sets;

public:
	TinyGraphicDescriptorManager( );

	~TinyGraphicDescriptorManager( ) = default;

	bool Create( 
		TinyGraphicLogical& logical, 
		const TinyLimitsStack& limits,
		const TinyDescriptorLayout& layout,
		tiny_uint set_count
	);

	void Terminate( const TinyGraphicLogical& logical );

private:
	bool CreatePool(
		TinyGraphicLogical& logical,
		const TinyLimitsStack& limits,
		const TinyDescriptorLayout& layout,
		tiny_uint set_instance_count
	);

public:
	tiny_list<VkDescriptorSetLayout> GetLayouts( );

	tiny_list<VkDescriptorSet> GetSets( tiny_uint work_id ) const;

	const tiny_list<VkDescriptorSet>& GetSet(
		tiny_uint set_id 
	) const;

};
