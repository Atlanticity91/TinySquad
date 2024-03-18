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

#include "TinyGraphicQueue.h"

tm_struct TinyGraphicRessourceQueues {

	tiny_uint Sharing = 0;
	tiny_list<tiny_uint> Queues{ };

};

tm_class TinyGraphicQueueManager final {

private:
	tiny_list<TinyGraphicQueue> _queues;
	TinyGraphicRessourceQueues  _ressources;

public:
	TinyGraphicQueueManager( );

	~TinyGraphicQueueManager( ) = default;

	bool Create(
		const TinyGraphicPhysical& physical,
		const TinyGraphicLogical& logical 
	);

	void Release( VkQueueTypes type, VkLogicalQueue* queue );

	void Terminate( const TinyGraphicLogical& logical );

private:
	bool CreateQueues( 
		const TinyGraphicPhysical& physical,
		const TinyGraphicLogical& logical 
	);

	void CreateRessources( );

public:
	const VkPhysicalDeviceQueue& GetPhysicalQueue( VkQueueTypes type ) const;

	VkLogicalQueue* Acquire( VkQueueTypes type );

	const TinyGraphicRessourceQueues& GetRessourceQueues( ) const;

};
