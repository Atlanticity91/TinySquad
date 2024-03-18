/*************************\*****************************************************************
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
 * @creation : 25/10/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include <TinyMicro/Graphics/Queues/TinyGraphicQueueManager.h>

tiny_enum( TinyGraphicMemoryUsages ) {

	TGM_USAGE_GPU_ONLY = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
	TGM_USAGE_CPU_ONLY = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
	TGM_USAGE_SHARE	   = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT

};

tm_struct TinyGraphicMemory {

	TinyGraphicMemoryUsages Usage;
	VkDeviceMemory Memory;
	tiny_uint Size;

	TinyGraphicMemory( );

	operator VkDeviceMemory ( );

	operator const VkDeviceMemory( ) const;

};
