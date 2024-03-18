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
 * @creation : 23/10/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "TinyGraphicMemory.h"

tm_class TinyGraphicMemoryManager final {

private:
	VkPhysicalDeviceMemoryProperties _properties;

public:
	TinyGraphicMemoryManager( );

	~TinyGraphicMemoryManager( ) = default;

	bool Create( const TinyGraphicContext& graphic );

	bool Allocate( TinyGraphicContext& graphic, TinyGraphicMemory& memory, VkImage& image );

	bool Allocate( TinyGraphicContext& graphic, TinyGraphicMemory& memory, VkBuffer& buffer );

	void DeAllocate( TinyGraphicContext& graphic, TinyGraphicMemory& memory );

	void Terminate( const TinyGraphicContext& graphic );

private:
	bool Allocate( 
		TinyGraphicContext& graphic,
		TinyGraphicMemory& memory, 
		VkMemoryRequirements& requirements 
	);

private:
	tiny_uint GetMemoryFamily( 
		TinyGraphicContext& graphic, 
		TinyGraphicMemoryUsages usage, 
		VkMemoryRequirements& requirements 
	);

};
