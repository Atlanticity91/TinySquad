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
 * @creation : 20/12/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include <TinyEngine/Audio/TinyCueManager.h>

te_class TinyRenderBuffer final {

private:
	tiny_uint						  _chunk_size;
	TinyGraphicBuffer				  _buffer;
	tiny_list<VkDescriptorBufferInfo> _descriptors;

public:
	TinyRenderBuffer( );

	~TinyRenderBuffer( ) = default;
	
	bool Create( 
		TinyGraphicManager& graphics,
		const TinyGraphicBufferSpecification& specification
	);

	void Terminate( TinyGraphicManager& graphics );

public:
	tiny_uint GetChunkSize( ) const;

	const TinyGraphicBuffer& GetBuffer( ) const;

	VkDescriptorType GetDescriptorType( ) const;

	VkDescriptorBufferInfo* GetDescriptor( tiny_uint work_id );

public:
	VkDescriptorBufferInfo* operator[]( tiny_uint work_id );

};
