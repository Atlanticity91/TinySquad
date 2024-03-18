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

#include <TinyMicro/__tiny_micro_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyGraphicQueueManager::TinyGraphicQueueManager( )
	: _queues{ },
	_ressources{ }
{ }

bool TinyGraphicQueueManager::Create( 
	const TinyGraphicPhysical& physical,
	const TinyGraphicLogical& logical 
) {
	auto state = CreateQueues( physical, logical );
	
	if ( state )
		CreateRessources( );

	return state;
}

void TinyGraphicQueueManager::Release( VkQueueTypes type, VkLogicalQueue* queue ) {
	if ( queue ) {
		auto queue_id = _queues.find(
			[ type ]( const TinyGraphicQueue& queue ) {
				return queue.GetPhysical( ).Type == type;
			}
		);

		if ( _queues.exist( queue_id ) )
			_queues[ queue_id ].Release( queue );
	}
}

void TinyGraphicQueueManager::Terminate( const TinyGraphicLogical& logical ) {
	for ( auto& queue : _queues )
		queue.Terminate( logical );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyGraphicQueueManager::CreateQueues(
	const TinyGraphicPhysical& physical, 
	const TinyGraphicLogical& logical
) {
	auto queue_id = tiny_cast( 0, tiny_uint );
	auto& queues  = physical.GetQueues( );
	auto state	  = false;

	_queues.resize( queues.size( ) );

	for ( auto& queue : queues ) {
		state = _queues[ queue_id++ ].Create( logical, queue );

		if ( !state )
			break;
	}

	return state;
}

void TinyGraphicQueueManager::CreateRessources( ) {
	auto graphic  = GetPhysicalQueue( VK_QUEUE_TYPE_GRAPHIC );
	auto transfer = GetPhysicalQueue( VK_QUEUE_TYPE_TRANSFER );

	if ( graphic.Family != transfer.Family ) {
		_ressources.Sharing = VK_SHARING_MODE_CONCURRENT;
		_ressources.Queues  = 2;
		_ressources.Queues[ 0 ] = graphic.Family;
		_ressources.Queues[ 1 ] = transfer.Family;
	} else {
		_ressources.Sharing = VK_SHARING_MODE_EXCLUSIVE;
		_ressources.Queues  = 1;
		_ressources.Queues[ 0 ] = graphic.Family;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
const VkPhysicalDeviceQueue& TinyGraphicQueueManager::GetPhysicalQueue(
	VkQueueTypes type 
) const {
	if ( _queues.size( ) > 1 ) {
		auto queue_id = _queues.find(
			[ type ]( const TinyGraphicQueue& queue ) {
				return queue.GetPhysical( ).Type == type;
			}
		);
		
		if ( _queues.exist( queue_id ) )
			return _queues[ queue_id ].GetPhysical( );
	}

	return _queues[ 0 ].GetPhysical( );
}

VkLogicalQueue* TinyGraphicQueueManager::Acquire( VkQueueTypes type ) {
	auto queue_id = tiny_cast( 0, tiny_uint );
	auto* queue   = tiny_cast( nullptr, VkLogicalQueue* );

	if ( _queues.size( ) > 1 ) {
		auto queue_id = _queues.find( 
			[ type ]( const TinyGraphicQueue& queue ) {  
				return queue.GetPhysical( ).Type == type;
			} 
		);

		if ( _queues.exist( queue_id ) )
			queue = _queues[ queue_id ].Acquire( );
	} else
		queue = _queues[ 0 ].Acquire( );

	return queue;
}

const TinyGraphicRessourceQueues& TinyGraphicQueueManager::GetRessourceQueues( ) const {
	return _ressources;
}
