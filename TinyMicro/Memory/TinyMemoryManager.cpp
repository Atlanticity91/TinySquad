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
 * @creation : 06/12/2023
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
TinyMemoryManager::TinyMemoryManager( )
	: _block_storage{ nullptr },
	_block_count{ 0 },
	_occupancy{ 0 },
	_capacity{ 0 }
{ }

TinyMemoryManager::~TinyMemoryManager( ) {
	if ( _block_storage )
		free( _block_storage );

	printf( "[ INFO ] TinyMemoryManager Cleanup.\n" );

	tiny_dump_leaks( );
}

bool TinyMemoryManager::Initialize( tiny_ulong capacity ) {
	printf( "[ INFO ] TinyMemoryManager Initialization.\n" );

	auto header_size = MAX_BLOCKS * tiny_sizeof( TinyMemoryBlock );

	_block_storage = malloc( tiny_cast( header_size + capacity, size_t ) );
	_capacity	   = capacity;

	if ( _block_storage ) {
		auto block_count = MAX_BLOCKS;
		auto* blocks	 = tiny_cast( _block_storage, TinyMemoryBlock* );

		while ( block_count-- > 0 ) {
			auto* block = &blocks[ block_count ];

			block->Offset	  = 0;
			block->Capacity   = 0;
			block->Reference  = 0;
			block->Destructor = nullptr;
		}
	}

	return _block_storage;
}

bool TinyMemoryManager::Allocate(
	tiny_storage& storage,
	tiny_uint capacity,
	TinyMemoryBlock::DestructorCall destructor
) {
	auto* block = tiny_cast( nullptr, TinyMemoryBlock* );
	auto state  = _block_count < MAX_BLOCKS			 && 
				  capacity <= _capacity - _occupancy &&
				  FindEmpty( storage.Block, block );

	if ( state ) {
		block->Offset	  = _occupancy;
		block->Capacity	  = capacity;
		block->Reference  = 1;
		block->Destructor = destructor;

		storage.Capacity = capacity;

		_block_count += 1;
		_occupancy	 += capacity;
	} else
		storage.Block = TINY_UINT_MAX;

	return state;
}

bool TinyMemoryManager::ReAllocate( tiny_storage& storage, tiny_uint capacity ) {
	auto state = storage.GetIsValid( ) && capacity > 0;

	if ( state ) {
		auto* block = GetBlock( storage.Block );

		if ( storage.Capacity < capacity ) {
			auto offset = capacity - storage.Capacity;

			//Tiny::Memcpy( nullptr, nullptr, 0 );

			storage.Capacity += offset;

			_occupancy += offset;
		} else {
			auto offset = capacity < storage.Capacity ? storage.Capacity - capacity : storage.Capacity;

			//Tiny::Memcpy( nullptr, nullptr, 0 );
			storage.Capacity -= offset;

			_occupancy -= offset;
		}

		if ( state )
			block->Capacity = capacity;
	} else
		state = Allocate( storage, capacity, { } );

	return state;
}

void TinyMemoryManager::SetDestructor(
	const tiny_storage& storage,
	TinyMemoryBlock::DestructorCall destructor
) {
	if ( storage.GetIsValid( ) ) {
		auto* block = GetBlock( storage.Block );

		if ( block )
			block->Destructor = destructor;
	}
}

void TinyMemoryManager::DeAllocate( tiny_storage& storage ) {
	auto* block = GetBlock( storage.Block );

	if ( block ) {
		if ( block->Destructor )
			std::invoke( block->Destructor );

		//Tiny::Memcpy( nullptr, nullptr, 0 );

		block->Offset	  = 0;
		block->Capacity   = 0;
		block->Reference  = 0;
		block->Destructor = nullptr;

		storage.Block	 = TINY_UINT_MAX;
		storage.Capacity = 0;

		_block_count -= 1;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
tiny_uint TinyMemoryManager::GetBlockCount( ) const { return _block_count; }

tiny_ulong TinyMemoryManager::GetOccupancy( ) const { return _occupancy; }

tiny_ulong TinyMemoryManager::GetCapacity( ) const { return _capacity; }

TinyMemoryBlock* TinyMemoryManager::GetBlock( tiny_uint block ) const {
	auto* blocks = tiny_cast( _block_storage, TinyMemoryBlock* );
	
	return block < MAX_BLOCKS ? blocks + block : nullptr;
}

c_ptr TinyMemoryManager::GetAddress( const tiny_storage& storage ) const {
	return GetAddress( storage.Block );
}

c_ptr TinyMemoryManager::GetAddress( tiny_uint block ) const {
	auto* blocks  = tiny_cast( _block_storage, TinyMemoryBlock* );
	auto* address = tiny_cast( nullptr, c_ptr );

	if ( block < MAX_BLOCKS ) {
		auto* offset = tiny_cast( blocks + MAX_BLOCKS, tiny_ptr );

		address = tiny_cast( offset + blocks[ block ].Offset, c_ptr );
	}

	return address;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE GET ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyMemoryManager::FindEmpty( tiny_uint& block_id, TinyMemoryBlock*& block ) const {
	auto* blocks = tiny_cast( _block_storage, TinyMemoryBlock* );
	
	block_id = MAX_BLOCKS;
	block	 = nullptr;

	while ( block_id-- > 0 && blocks[ block_id ].Capacity > 0 );

	if ( blocks[ block_id ].Capacity == 0 )
		block = blocks + block_id;

	return block;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC STATIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyMemoryManager& TinyMemoryManager::GetSingleton( ) {
	static TinyMemoryManager instance{ };

	return instance;
}
