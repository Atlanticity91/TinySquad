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
 * @creation : 17/10/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include <TinyMicro/Graphics/Device/TinyGraphicLogical.h>

tm_class TinyGraphicQueue final {

private:
	VkPhysicalDeviceQueue	  _physical;
	VkSharingMode			  _sharing_mode;
	tiny_list<VkLogicalQueue> _queues;

public:
	TinyGraphicQueue( );

	~TinyGraphicQueue( ) = default;

	bool Create( const TinyGraphicLogical& logical, const VkPhysicalDeviceQueue& physical );

	void Release( VkLogicalQueue* queue );

	void Terminate( const TinyGraphicLogical& logical );

private:
	bool CreateQueuePool( 
		const TinyGraphicLogical& logical,
		const VkPhysicalDeviceQueue& physical,
		VkLogicalQueue& queue 
	);

	bool CreateQueueCommands( const TinyGraphicLogical& logical, VkLogicalQueue& queue );

	bool CreateQueues( 
		const TinyGraphicLogical& logical, 
		const VkPhysicalDeviceQueue& physical 
	);

public:
	const VkPhysicalDeviceQueue& GetPhysical( ) const;

	VkLogicalQueue* Acquire( );

	const VkLogicalQueue& GetQueue( tiny_uint queue_id ) const;

public:
	const VkLogicalQueue& operator[]( tiny_uint queue_id ) const;

};
