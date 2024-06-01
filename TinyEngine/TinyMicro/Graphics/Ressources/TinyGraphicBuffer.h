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
 * @creation : 13/10/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "TinyGraphicBufferSpecification.h"

tm_class TinyGraphicBuffer final {

private:
	VkDescriptorBufferInfo m_descriptor;
	TinyGraphicBufferSpecification m_properties;
	TinyGraphicMemory m_memory;

public:
	TinyGraphicBuffer( );

	~TinyGraphicBuffer( ) = default;

	bool Create( 
		TinyGraphicWrapper& graphic,
		const TinyGraphicBufferSpecification& properties
	);

	void Terminate( TinyGraphicWrapper& graphic );

private:
	bool CreateBuffer( 
		const TinyGraphicLogical& logical, 
		const TinyGraphicQueueManager& queues 
	);

	bool AllocateBuffer( TinyGraphicWrapper& graphic );

public:
	bool GetIsValid( ) const;

	const VkBuffer Get( ) const;

	VkDescriptorType GetDescriptorType( ) const;

	const VkDescriptorBufferInfo* GetDescriptor( ) const;

	const TinyGraphicBufferSpecification& GetProperties( ) const;

	const TinyGraphicMemory& GetMemory( ) const;

public:
	operator bool ( ) const;

	operator const VkBuffer ( ) const;

	operator const VkDescriptorBufferInfo* ( ) const;

};
